/*
 * *@ :file explain:
 * *@ :name --> fs_soft_timer_driver.c
 * *@ :version -->V0.0.1
 * *@ :point --> 1.实现了基于一个硬件定时器，多个软定时器的创建、删除，和硬件定时器的功能类似。
 * *@ :point --> 2.内存采用动态开辟的方式，不使用不创建，不用了就释放，初始只有两个空指针。
 * *@ :point --> 3.数据结构采用单向循环链表，增删改查。 
 * *@ :point --> 4.依赖文件只有 stdilib.h 和 stdint.h。
 * *@ :point --> 5.这里的软定时器定时周期，和硬件定时器单次溢出时间一致。
 * *@ :point --> 6.操作函数是在 fs_soft_timer_module_init 里面添加的，要增加也在这里面增加。
 * *@ :point --> 7.回调函数是可以传入参数的，自己在回调函数中把void 类型转换为原本的类型就行了。 
 */

/*
 * * change record:-->1
 * * time and author:21.10.4 lanxin
 * * what changed:创建初始版本。
 * * point:
 */

/*
 * * change record:-->1
 * * time and author:21.10.9 lanxin
 * * what changed:修改初始化函数
 * * point:1.提供了更简单的初始化过程
 */

/****************************how to use****************************/
/*
 *1.-->添加文件后直接编译，正常不会报错。
 *2.调用 fs_soft_timer_module_init();判断返回值为SOFT_TIMER_STATE_OK后就可以正常使用了，否则不能使用。
 *3.把 tim_ops->timer_handle();放到while(1)里面或者哪能周期性调用的地方。
 *4. SOFT_CHECK_PARA_NULL(tim_ops);//这个是防止在未完成初始化之前就调用tim_ops->timer_heart();直接进硬件错误。
*****tim_ops->timer_heart();这两个放硬件定时器中断里面。
 *5.添加你自己的soft timer，要想之后还需要操作这个timer，就定义为全局变量。
****c_soft_timer_t *my_timer_1=tim_ops->add_new_timer(SOFT_TIMER_WORK_PERIOD,1000,0,test);//添加第一个timer
****回调函数 名字随意，参数必须有void *para，这个保证了回调函数里面可以传入参数
****void test(void* para)
****{
********HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_2);
****}	
 */

/* source .h file */
#include "fs_soft_timer_driver.h"
#include "stdlib.h" //malloc/free is in this .h file

/* check define */
/* 注意返回类型是 e_soft_timer_state_t，并且不对外开放接口 */
#define TIMER_CHECK_WORKMODE(mode)             \
	do                                         \
	{                                          \
		if (mode >= SOFT_TIMER_WORK_MODE_ERR)  \
		{                                      \
			return SOFT_TIMER_WORK_MODE_ERROR; \
		}                                      \
	} while (0)

#define TIMER_CHECK_NULL(para)              \
	do                                      \
	{                                       \
		if (para == 0x00)                   \
		{                                   \
			return SOFT_TIMER_PARA_IS_NULL; \
		}                                   \
	} while (0)

/* function declaration */
e_soft_timer_state_t fs_soft_timer_module_init(void);
static e_soft_timer_state_t fs_soft_timer_heart(void);
static e_soft_timer_state_t fs_soft_timer_handle(void);

static c_soft_timer_t *fs_malloc_new_soft_timer(void);

static e_soft_timer_state_t fs_add_new_soft_timer(e_timer_work_mode_t mode, uint16_t tim, void *para, soft_timer_call_back tim_cb);
static c_soft_timer_t *add_new_timer(e_timer_work_mode_t mode, uint16_t tim, void *para, soft_timer_call_back tim_cb);
static e_soft_timer_state_t delete_timer(c_soft_timer_t *timer);

static e_soft_timer_state_t fs_timer_set_period(c_soft_timer_t *timer, uint16_t period);
static e_soft_timer_state_t fs_timer_reload_cnt(c_soft_timer_t *timer, uint16_t tim_cnt);

static e_soft_timer_state_t fs_soft_timer_module_stop(void);
static e_soft_timer_state_t fs_soft_timer_module_start(void);

static e_soft_timer_state_t fs_soft_timer_enable(c_soft_timer_t *timer);
static e_soft_timer_state_t fs_soft_timer_disable(c_soft_timer_t *timer);

/* variable declaration */
c_soft_timer_ops_t *tim_ops = 0x00;
static c_soft_timer_manage_t *soft_timer_manage = 0x00;

/*
 * *@ author:lanxin
 * *@ brief:sotf timer module init
 * *@ note:初始化完成之后，就可以使用全部的功能了
 * *@ param:NONE
 * *@ retval:result != SOFT_TIMER_STATE_OK faild
 */
e_soft_timer_state_t fs_soft_timer_module_init(void)
{
	/* creat timer operation index */
	static c_soft_timer_ops_t *timer_ops_temp = 0X00;
	timer_ops_temp = (c_soft_timer_ops_t *)malloc(sizeof(c_soft_timer_ops_t));
	if (timer_ops_temp != 0x00)
	{
		/* add soft timer operate function*/
		timer_ops_temp->add_new_timer = add_new_timer;
		timer_ops_temp->delete_timer = delete_timer;
		timer_ops_temp->timer_heart = fs_soft_timer_heart;
		timer_ops_temp->timer_handle = fs_soft_timer_handle;
		timer_ops_temp->timer_start = fs_soft_timer_module_start;
		timer_ops_temp->timer_stop = fs_soft_timer_module_stop;
		timer_ops_temp->timer_set_period = fs_timer_set_period;
		timer_ops_temp->timer_disable = fs_soft_timer_disable;
		timer_ops_temp->timer_enable = fs_soft_timer_enable;
		timer_ops_temp->timer_reload_cnt = fs_timer_reload_cnt;
	}
	/* creat timer manage index*/
	c_soft_timer_manage_t *timer_manage_temp = 0x00;
	timer_manage_temp = (c_soft_timer_manage_t *)malloc(sizeof(c_soft_timer_manage_t));
	/* 添加信息 */
	if (timer_manage_temp != 0x00)
	{
		timer_manage_temp->timer_head = 0x00;
		timer_manage_temp->timer_total_num = 0;
		timer_manage_temp->timer_module_enable = SOFT_TIMER_MODULE_START;
		soft_timer_manage = timer_manage_temp;
	}
	else
	{
		free(timer_manage_temp);
		free(timer_ops_temp);
		return SOFT_TIMER_STATE_ERR;
	}
	tim_ops = timer_ops_temp;
	return SOFT_TIMER_STATE_OK;
}
/*
 * *@ author:lanxin
 * *@ brief:开辟一个timer的空间
 * *@ note:
 * *@ param:NONE
 * *@ retval:成功开辟就是新的空间的地址否则返回0
 */
static c_soft_timer_t *fs_malloc_new_soft_timer(void)
{
	/* 创建新的timer */
	static c_soft_timer_t *new_soft_timer = 0x00;
	new_soft_timer = (c_soft_timer_t *)malloc(sizeof(c_soft_timer_t));
	if (new_soft_timer == 0x00)
	{
		return 0;
	}
	return new_soft_timer;
}
/*
 * *@ author:lanxin
 * *@ brief:创建新的timer，参数正确后添加到timer链表里面
 * *@ note:
 * *@ param:mode 工作模式
 * *@ param:tim 定时周期
 * *@ param:para 回调函数的参数
 * *@ param:tim_cb 回调函数
 * *@ retval:result != SOFT_TIMER_STATE_OK add faild
 */
static e_soft_timer_state_t fs_add_new_soft_timer(e_timer_work_mode_t mode, uint16_t tim, void *para, soft_timer_call_back tim_cb)
{
	/* 先检查在开辟空间 */
	TIMER_CHECK_WORKMODE(mode);			 //检查工作模式
	TIMER_CHECK_NULL(tim_cb);			 //检查回调函数
	TIMER_CHECK_NULL(soft_timer_manage); //检查是否为空
	/* 创建新的timer */
	static c_soft_timer_t *timer_dev_temp = 0x00;
	timer_dev_temp = fs_malloc_new_soft_timer();
	TIMER_CHECK_NULL(timer_dev_temp); //检查是否为空

	/* 第一次添加timer */
	if (soft_timer_manage->timer_total_num == 0)
	{
		soft_timer_manage->timer_head = timer_dev_temp; //第一个timer，作为头结点，以后删除timer的时候，通过这个遍历整个timer链表

		timer_dev_temp->timer_next = timer_dev_temp; //目前就一个timer所有指向它本身
	}
	else
	{
		c_soft_timer_t *timer_head_temp = 0x00;
		c_soft_timer_t *timer_add_temp = 0x00;

		timer_head_temp = soft_timer_manage->timer_head; //找到第一个timer

		timer_add_temp = timer_head_temp->timer_next; //找到未增加前第一个timer后面的timer

		timer_head_temp->timer_next = timer_dev_temp; //添加新的timer 到第一个timer 后面

		timer_dev_temp->timer_next = timer_add_temp; //将第一个timer原本的timer放在新增加的timer后面
	}
	soft_timer_manage->timer_total_num++; //timer总数加1
	/* 拷贝信息 */
	timer_dev_temp->mode = mode;
	timer_dev_temp->timer_cb = tim_cb;
	timer_dev_temp->cnt_aim = tim / SOFT_TIME_PERIOD; //实际的计数次数
	timer_dev_temp->cnt_now = tim / SOFT_TIME_PERIOD;
	timer_dev_temp->para = para;
	timer_dev_temp->enable = SOFT_TIMER_ENABLE; //默认timer 使能状态
	return SOFT_TIMER_STATE_OK;
}
/*
 * *@ author:lanxin
 * *@ brief:添加新的timer
 * *@ note:如果之后要操作这个定时器，就得保存下来timer句柄，不操作就不用管。
 * *@ param:mode 工作模式
 * *@ param:tim 定时周期
 * *@ param:para 回调函数的参数
 * *@ param:tim_cb 回调函数
* *@ retval:新的timer 的句柄，
 */
static c_soft_timer_t *add_new_timer(e_timer_work_mode_t mode, uint16_t tim, void *para, soft_timer_call_back tim_cb)
{
	if (fs_add_new_soft_timer(mode, tim, para, tim_cb) == SOFT_TIMER_STATE_OK)
	{
		return soft_timer_manage->timer_head->timer_next; //新添加的timer在timer 链表的第二个。
	}
	return 0x00;
}
/*
 * *@ author:lanxin
 * *@ brief:删除一个定时器
 * *@ note:立刻生效
 * *@ param:timer 要删除的timer 句柄
 * *@ retval:result != SOFT_TIMER_STATE_OK delete faild
 */
static e_soft_timer_state_t delete_timer(c_soft_timer_t *timer)
{
	TIMER_CHECK_NULL(soft_timer_manage);
	TIMER_CHECK_NULL(timer);

	uint8_t find_cnt = 0;
	if (soft_timer_manage->timer_total_num == 0)
	{
		return SOFT_TIMER_DELETE_NOT_FOUND;
	}
	/* 如果删除的是头结点，将头结点的下一个节点换为新的头结点 */
	if (soft_timer_manage->timer_head == timer)
	{
		soft_timer_manage->timer_head = soft_timer_manage->timer_head->timer_next;
	}

	static c_soft_timer_t *timer_delete_temp = 0x00;
	timer_delete_temp = soft_timer_manage->timer_head;
	for (find_cnt = 0; find_cnt < soft_timer_manage->timer_total_num; find_cnt++)
	{
		if (timer_delete_temp->timer_next == timer)
		{
			break;
		}
		timer_delete_temp = timer_delete_temp->timer_next;
	}
	if (find_cnt == soft_timer_manage->timer_total_num)
	{
		return SOFT_TIMER_DELETE_NOT_FOUND; //要删除的timer不存在
	}
	timer_delete_temp->timer_next = timer->timer_next; //原本timer_delete_temp指向要删除的timer，现在指向要删除的timer的下一个timer
	free(timer);									   //释放空间
	soft_timer_manage->timer_total_num--;			   //timer总数减1
	if (soft_timer_manage->timer_total_num == 0)
	{
		soft_timer_manage->timer_head = 0x00;
	}
	return SOFT_TIMER_STATE_OK;
}
/*
 * *@ author:lanxin
 * *@ brief:重新加载timer的计数值
 * *@ note:tim_cnt为0，则设置为初始值，可以用于单次时间设置太短，但需增加时间的情况，相当于累加
 * *@ param:timer
 * *@ param:tim_cnt 新的计数值
 * *@ retval:NONE
 */
static e_soft_timer_state_t fs_timer_reload_cnt(c_soft_timer_t *timer, uint16_t tim_cnt)
{
	TIMER_CHECK_NULL(timer);
	if (tim_cnt == 0)
	{
		timer->cnt_now = timer->cnt_aim;
	}
	else
	{
		timer->cnt_now = tim_cnt;
	}
	return SOFT_TIMER_STATE_OK;
}
/*
 * *@ author:lanxin
 * *@ brief:为soft timer 提供心跳
 * *@ note:
 * *@ param:NONE
 * *@ retval:NONE
 */
static e_soft_timer_state_t fs_soft_timer_heart(void)
{
	TIMER_CHECK_NULL(soft_timer_manage);
	TIMER_CHECK_NULL(soft_timer_manage->timer_total_num);
	if (soft_timer_manage->timer_module_enable == SOFT_TIMER_MODULE_STOP)
	{
		return SOFT_TIMER_MODULE_STOP;
	}
	static c_soft_timer_t *timer = 0x00;
	timer = soft_timer_manage->timer_head;
	/* 遍历所有的timer */
	for (int cnt = 0; cnt < soft_timer_manage->timer_total_num; cnt++)
	{
		if (timer->enable == SOFT_TIMER_ENABLE)
		{
			timer->cnt_now--;
		}
		if (timer->cnt_now == 0)
		{
			timer->timeout = SOFT_TIMER_TIMEOUT;
			if (timer->mode == SOFT_TIMER_WORK_PERIOD)
			{
				timer->cnt_now = timer->cnt_aim;
			}
		}
		timer = timer->timer_next;
	}
	return SOFT_TIMER_STATE_OK;
}
/*
 * *@ author:lanxin
 * *@ brief:处理定时器的中断事件
 * *@ note:放while(1)里面
 * *@ param:NONE
 * *@ retval:NONE
 */
static e_soft_timer_state_t fs_soft_timer_handle(void)
{
	TIMER_CHECK_NULL(soft_timer_manage);
	TIMER_CHECK_NULL(soft_timer_manage->timer_total_num);

	if (soft_timer_manage->timer_module_enable == SOFT_TIMER_MODULE_STOP)
	{
		return SOFT_TIMER_MODULE_STOP;
	}
	static c_soft_timer_t *timer = 0x00;
	timer = soft_timer_manage->timer_head;
	for (int cnt = 0; cnt < soft_timer_manage->timer_total_num; cnt++)
	{
		if (timer->timeout == SOFT_TIMER_TIMEOUT)
		{
			timer->timer_cb(timer->para);
			if (timer->mode == SOFT_TIMER_WORK_ONE_TIMER)
			{
				delete_timer(timer);
			}
			timer->timeout = 0;
		}
		timer = timer->timer_next;
	}
	return SOFT_TIMER_STATE_OK;
}
/*
 * *@ author:lanxin
 * *@ brief:设置timer的定时周期
 * *@ note:
 * *@ param:timer
 * *@ param:period 新的定时周期
 * *@ retval:result != SOFT_TIMER_STATE_OK change faild
 */
static e_soft_timer_state_t fs_timer_set_period(c_soft_timer_t *timer, uint16_t period)
{
	TIMER_CHECK_NULL(timer);
	timer->cnt_aim = period;
	return SOFT_TIMER_STATE_OK;
}
/*
 * *@ author:lanxin
 * *@ brief:关闭soft timer模块 
 * *@ note:
 * *@ param:NONE
 * *@ retval:NONE
 */
static e_soft_timer_state_t fs_soft_timer_module_stop(void)
{
	TIMER_CHECK_NULL(soft_timer_manage);
	soft_timer_manage->timer_module_enable = SOFT_TIMER_MODULE_STOP;
	return SOFT_TIMER_STATE_OK;
}
/*
 * *@ author:lanxin
 * *@ brief:开启soft timer 
 * *@ note:默认是开启的，手动关闭后，使用这个重新打开
 * *@ param:NONE
 * *@ retval:NONE
 */
static e_soft_timer_state_t fs_soft_timer_module_start(void)
{
	TIMER_CHECK_NULL(soft_timer_manage);
	soft_timer_manage->timer_module_enable = SOFT_TIMER_MODULE_START;
	return SOFT_TIMER_STATE_OK;
}
/*
 * *@ author:lanxin
 * *@ brief:开启 timer 
 * *@ note:默认是开启的，手动关闭后，使用这个重新打开
 * *@ param:timer
 * *@ retval:result != SOFT_TIMER_STATE_OK faild
 */
static e_soft_timer_state_t fs_soft_timer_enable(c_soft_timer_t *timer)
{
	TIMER_CHECK_NULL(timer);
	timer->enable = SOFT_TIMER_ENABLE;
	return SOFT_TIMER_STATE_OK;
}
/*
 * *@ author:lanxin
 * *@ brief:关闭 timer 
 * *@ note:默认是开启的，手动关闭后，使用fs_soft_timer_enable重新打开
 * *@ param:timer
 * *@ retval:result != SOFT_TIMER_STATE_OK faild
 */
static e_soft_timer_state_t fs_soft_timer_disable(c_soft_timer_t *timer)
{
	TIMER_CHECK_NULL(timer);
	timer->enable = SOFT_TIMER_DISABLE;
	return SOFT_TIMER_STATE_OK;
}
