/*
 * *@ :file explain:
 * *@ :name -->
 * *@ :version -->
 * *@ :point --> 1.
 */
#ifndef _fs_soft_timer_driver_H
#define _fs_soft_timer_driver_H

#include "stdint.h"//uint8_t 等类型变量在这里面

#define SOFT_TIME_PERIOD  10//单位ms 与实际硬件定时器单次定时周期保持一致，用于软定时器的定时周期同步

/* soft timer callback */
typedef void	(soft_timer_call_back)(void* para);

/* 检查参数是否为空 */
#define SOFT_CHECK_PARA_NULL(para)  do {\
	if(para == 0x00)  			\
	{							\
		return ;				\
	}							\
}while(0)

/* soft timer state enum define */
typedef enum{

	SOFT_TIMER_PARA_IS_NULL = 0X00,//参数为空
	SOFT_TIMER_ADD_FAIL,//添加失败
	SOFT_TIMER_DELETE_NOT_FOUND,//要删除的timer不存在
	SOFT_TIMER_WORK_MODE_ERROR,//配置的工作模式错误
	
	SOFT_TIMER_TIMEOUT,//到达计时时间
	
	SOFT_TIMER_MODULE_STOP,//模块处于关闭状态
	SOFT_TIMER_MODULE_START,//模块处于开启状态
	
	SOFT_TIMER_ENABLE,//表示timer使能
	SOFT_TIMER_DISABLE,//表示timer失能
	
	SOFT_TIMER_STATE_ERR,//失败
	SOFT_TIMER_STATE_OK,//成功
}e_soft_timer_state_t;

/* soft timer work mode enum define */
typedef enum {

    SOFT_TIMER_WORK_ONE_TIMER   =0X00,//单次工作
    SOFT_TIMER_WORK_PERIOD      ,//周期性工作
    SOFT_TIMER_WORK_MODE_ERR    ,//错误的工作模式
}e_timer_work_mode_t;

/* soft timer device */
typedef struct class_soft_timer {

    e_timer_work_mode_t mode;//工作模式
	uint16_t cnt_aim;//目标计数值
	uint16_t cnt_now;//当前的计数值
	uint8_t timeout;//表示到计数值了
	uint8_t enable;//表示timer是否开启
	
	struct class_soft_timer *timer_next;//指向下一个timer
	
	void *para;//回调函数的参数
    soft_timer_call_back *timer_cb;//回调函数
}c_soft_timer_t;

/* soft timer manage */
typedef struct class_soft_timer_manage{

    c_soft_timer_t *timer_head;//timer device
    uint8_t timer_total_num;//当前timer的总数 
	uint8_t timer_module_enable;//是不是开启
}c_soft_timer_manage_t;

/* soft timer operate define */
typedef struct class_sotft_timer_operation {
	
	c_soft_timer_t		 *(*add_new_timer)(e_timer_work_mode_t mode,uint16_t tim,void *para,soft_timer_call_back tim_cb);//添加一个新的timer
	e_soft_timer_state_t (*delete_timer)(c_soft_timer_t *timer);//删除一个timer
	
	e_soft_timer_state_t (*timer_set_period)(c_soft_timer_t *timer,uint16_t period);//设置定时周期
	e_soft_timer_state_t (*timer_reload_cnt)(c_soft_timer_t *timer,uint16_t tim_cnt);//重新设置计数值
	
	e_soft_timer_state_t (*timer_heart)(void);//soft timer heart
	e_soft_timer_state_t (*timer_handle)(void);//soft timer handle
	
	e_soft_timer_state_t (*timer_start)(void);//soft timer module start
	e_soft_timer_state_t (*timer_stop)(void);//soft timer module stop
	
	e_soft_timer_state_t (*timer_enable)(c_soft_timer_t *timer);//timer enable
	e_soft_timer_state_t (*timer_disable)(c_soft_timer_t *timer);//timer disable
}c_soft_timer_ops_t;

/* function and variable declaration for other file */

extern c_soft_timer_ops_t *tim_ops;

extern e_soft_timer_state_t fs_soft_timer_module_init(void);

#endif /* _fs_soft_timer_driver_H */
