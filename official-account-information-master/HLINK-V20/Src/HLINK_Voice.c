/**
  ******************************************************************************
  * @file             HLINK_Voice.c
  * @brief            海凌科离线语音模块协议解析
  ******************************************************************************
  *author：	Embeded小飞哥
	*data 	 	2021-02-09
	*version 	V1.0.01  
  ******************************************************************************
  */
#include "HLINK_voice.h"
#include "stdlib.h"
#include "stdio.h"
#include <string.h>
#include "main.h"

extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim7;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;

typedef struct {
	char Rxbuff[100];
	uint8_t RxData;
	uint8_t RxCnt;
	uint8_t RxTimCnt;
	uint8_t RxRecFlag;
	uint8_t	RxEndFlag;
}uart2_para;


uart2_para Voice_RevPara;
/**
  * @brief  语音模块串口接收定时器接收超时函数
  *         
  * @param  timeout
  * @param  
  * @retval none
  */
void Voice_RecTimCallBack(uint16_t timeout)  //timeout ms
{
	 if(Voice_RevPara.RxRecFlag){    	//有数据到来
			if(Voice_RevPara.RxTimCnt>=timeout){  //判断定时器是否超时，100ms

			Voice_RevPara.RxTimCnt = 0;    //定时器计数器清零，计数器为人为设置，1ms+1
			Voice_RevPara.RxRecFlag = 0;  	

			Voice_RevPara.RxEndFlag = 1;   	//接接收完成标志
			}
		Voice_RevPara.RxTimCnt++;
	 }
}
/**
  * @brief  语音模块串口中断回调函数
  *         
  * @param  none
  * @param  none
  * @retval none
  */
void Voice_RecUartCallBack(void)	
{
	 Voice_RevPara.RxTimCnt = 0;
	 Voice_RevPara.RxRecFlag = 1;     
	 Voice_RevPara.Rxbuff[Voice_RevPara.RxCnt] = Voice_RevPara.RxData;
	 Voice_RevPara.RxCnt++;
	 if(Voice_RevPara.RxCnt>=100){
			Voice_RevPara.RxCnt=0;
	 }
		HAL_UART_Receive_IT(&huart2,&Voice_RevPara.RxData,1);
}	
/**
  * @brief  语音模块串口接收初始化
  *         
  * @param  none
  * @param  none
  * @retval none
  */
void  Voice_RecUartInit(void)
{
		HAL_UART_Receive_IT(&huart2,&Voice_RevPara.RxData,1);

		HAL_TIM_Base_Start(&htim7);
		HAL_TIM_Base_Start_IT(&htim7);
}
/**
  * @brief  语音模块串口命令处理完成
  *         
  * @param  none
  * @param  none
  * @retval none
  */
void commandfinish(void)
{
	 Voice_RevPara.RxEndFlag = 0;
	 Voice_RevPara.RxCnt = 0;
	 memset(Voice_RevPara.Rxbuff,0,sizeof(Voice_RevPara.Rxbuff));
}
/**
  * @brief  语音模块串口接收数据协议解析
  *         
  * @param  none
  * @param  none
  * @retval error status
  */

uint16_t PWM_Value;

int Voice_DataFrame(void)
{
	if(Voice_RevPara.RxEndFlag)
	{
		//判断数据头
		if(memcmp(Voice_RevPara.Rxbuff,"uArTcP",strlen("uArTcP")))
		{
			return Err_Head;
		}
		else       //判断具体是什么指令
		{
			if(!memcmp(Voice_RevPara.Rxbuff+16,"wakeup_uni",strlen("wakeup_uni")))
			{
				printf("the meseeage is wake up           唤醒模块\r\n");
			}
			else if(!memcmp(Voice_RevPara.Rxbuff+16,"openElectricfan",strlen("openElectricfan")))  //打开风扇，对应离线命令词与播报答复列表序号1功能
			{
				printf("the meseeage is openElectricfan   打开风扇\r\n");
			}
			else if(!memcmp(Voice_RevPara.Rxbuff+16,"closElectricfan",strlen("closElectricfan")))  //关闭风扇，对应离线命令词与播报答复列表序号2功能
			{
				printf("the meseeage is openElectricfan   关闭风扇\r\n");
			}
			else if(!memcmp(Voice_RevPara.Rxbuff+16,"AdjustGearmin",strlen("AdjustGearmin")))   //风扇调到最小，对应离线命令词与播报答复列表序号3功能
			{
				printf("the meseeage is AdjustGearmin     风扇调到最小\r\n");
			}
			else if(!memcmp(Voice_RevPara.Rxbuff+16,"AdjustGearmax",strlen("AdjustGearmax")))   //风扇调到最大，对应离线命令词与播报答复列表序号4功能
			{
				printf("the meseeage is AdjustGearmax     风扇调到最大\r\n");
			}
			else if(!memcmp(Voice_RevPara.Rxbuff+16,"settiCLonehonor",strlen("settiCLonehonor")))  //定时一小时关灯，对应离线命令词与播报答复列表序号5功能
			{
				printf("the meseeage is settiCLonehonor   定时一小时关灯\r\n");
			}
			else if(!memcmp(Voice_RevPara.Rxbuff+16,"settiOPonehonor",strlen("settiOPonehonor")))  //定时一小时开灯，对应离线命令词与播报答复列表序号6功能
			{
				printf("the meseeage is settiOPonehonor   定时一小时开灯\r\n");
			}
			else if(!memcmp(Voice_RevPara.Rxbuff+16,"volumeUpUni",strlen("volumeUpUni")))    //音量增大，对应离线命令词与播报答复列表序号7功能
			{
				printf("the meseeage is volumeUpUni   	  音量增大\r\n");
			}
			else if(!memcmp(Voice_RevPara.Rxbuff+16,"volumeDownUni",strlen("volumeDownUni")))   //音量减小，对应离线命令词与播报答复列表序号8功能
			{
				printf("the meseeage is volumeDownUni     音量减小\r\n");
			}
			else if(!memcmp(Voice_RevPara.Rxbuff+16,"openkongtiao",strlen("openkongtiao")))   	//打开空调，对应离线命令词与播报答复列表序号9功能
			{
				printf("the meseeage is openkongtiao      打开空调\r\n");
			}
			else if(!memcmp(Voice_RevPara.Rxbuff+16,"closekongtiao",strlen("closekongtiao")))   //关闭空调，对应离线命令词与播报答复列表序号10功能
			{
				printf("the meseeage is closekongtiao     关闭空调\r\n");
			}
			else if(!memcmp(Voice_RevPara.Rxbuff+16,"zhidongmos",strlen("zhidongmos")))    	//自动模式，对应离线命令词与播报答复列表序号11功能
			{
				printf("the meseeage is zhidongmos   	    自动模式\r\n");  
			}
			else if(!memcmp(Voice_RevPara.Rxbuff+16,"zhilenmos",strlen("zhilenmos")))      //制冷模式，对应离线命令词与播报答复列表序号12功能
			{
				printf("the meseeage is zhilenmos   	   制冷模式\r\n");  
			}
			else if(!memcmp(Voice_RevPara.Rxbuff+16,"zhirmos",strlen("zhirmos")))  	     	//制热模式，对应离线命令词与播报答复列表序号13功能
			{
				printf("the meseeage is zhirmos           制热模式\r\n");   
			}
			else if(!memcmp(Voice_RevPara.Rxbuff+16,"shenggaowendu",strlen("shenggaowendu")))   	//升高温度，对应离线命令词与播报答复列表序号14功能
			{
				printf("the meseeage is shenggaowendu  	  升高温度\r\n");  
			}
			else if(!memcmp(Voice_RevPara.Rxbuff+16,"jiandiwendu",strlen("jiandiwendu")))    //降低温度，对应离线命令词与播报答复列表序号15功能
			{
				printf("the meseeage is jiandiwendu       降低温度\r\n");  
			}
			else if(!memcmp(Voice_RevPara.Rxbuff+16,"turnon",strlen("turnon")))       //打开台灯，对应离线命令词与播报答复列表序号16功能
			{
				PWM_Value = 100;
				printf("the meseeage is turnon    	     打开台灯\r\n");  
			}
			else if(!memcmp(Voice_RevPara.Rxbuff+16,"turnoff",strlen("turnoff")))      	//关闭台灯，对应离线命令词与播报答复列表序号17功能
			{
				PWM_Value = 0;
				printf("the meseeage is turnoff           关闭台灯\r\n");  
			}
			else if(!memcmp(Voice_RevPara.Rxbuff+16,"openled",strlen("openled")))      	//打开灯，对应离线命令词与播报答复列表序号18功能
			{
				Relay_Ctrl(Relay_Ctrl_OPEN);
				RedLed_Ctrl(0);
				printf("the meseeage is openled           打开灯\r\n");  
			}
			else if(!memcmp(Voice_RevPara.Rxbuff+16,"closeled",strlen("closeled")))      //关闭灯，对应离线命令词与播报答复列表序号19功能
			{
				RedLed_Ctrl(0);
				Relay_Ctrl(Relay_Ctrl_CLOSE);
				printf("the meseeage is closeled          关闭灯\r\n");  
			}
			else if(!memcmp(Voice_RevPara.Rxbuff+16,"setmaxld",strlen("setmaxld")))      //调到最亮，对应离线命令词与播报答复列表序号20功能
			{			
				PWM_Value=500;
				printf("the meseeage is setmaxld          调到最亮\r\n");  
			}
			else if(!memcmp(Voice_RevPara.Rxbuff+16,"setminld",strlen("setminld")))      //调到最暗，对应离线命令词与播报答复列表序号21功能
			{
				PWM_Value = 10;
				printf("the meseeage is setminld          调到最暗\r\n");  
			}
			else if(!memcmp(Voice_RevPara.Rxbuff+16,"zengjialiangdu",strlen("zengjialiangdu")))   //增加亮度，对应离线命令词与播报答复列表序号22功能
			{
				
				if(PWM_Value>=500)
					PWM_Value = 500;
				else				
					PWM_Value+=100;
				printf("the meseeage is zengjialiangdu    增加亮度\r\n");  
			}
			else if(!memcmp(Voice_RevPara.Rxbuff+16,"jianxiaoliangdu",strlen("jianxiaoliangdu")))  	//减小亮度，对应离线命令词与播报答复列表序号23功能
			{	
				if(PWM_Value<=50)
				{
					PWM_Value = 50;
				}
				else
				PWM_Value-=100;
				printf("the meseeage is jianxiaoliangdu   减小亮度\r\n");  
			}
			else if(!memcmp(Voice_RevPara.Rxbuff+16,"setcolorred",strlen("setcolorred")))    	//灯调为红色，对应离线命令词与播报答复列表序号24功能
			{
				RedLed_Ctrl(1);
				Relay_Ctrl(Relay_Ctrl_CLOSE);
			printf("the meseeage is setcolorred       灯调为红色\r\n");  
			}
			else if(!memcmp(Voice_RevPara.Rxbuff+16,"dakaiyuba",strlen("dakaiyuba")))     	//打开浴霸，对应离线命令词与播报答复列表序号25功能
			{
				printf("the meseeage is dakaiyuba   	   打开浴霸\r\n");  
			}
			else if(!memcmp(Voice_RevPara.Rxbuff+16,"guanbiyuba",strlen("guanbiyuba")))     //关闭浴霸，对应离线命令词与播报答复列表序号26功能
			{
				printf("the meseeage is guanbiyuba   	   关闭浴霸\r\n");  
			}
			else if(!memcmp(Voice_RevPara.Rxbuff+16,"dakaizaoming",strlen("dakaizaoming")))   	//打开照明，对应离线命令词与播报答复列表序号27功能
			{
				printf("the meseeage is dakaizaoming      打开照明\r\n");  
			}
			else if(!memcmp(Voice_RevPara.Rxbuff+16,"guanbizhaoming",strlen("guanbizhaoming")))   //关闭照明，对应离线命令词与播报答复列表序号28功能
			{
				printf("the meseeage is dakaiyuba   	   关闭照明\r\n");  
			}

			else if(!memcmp(Voice_RevPara.Rxbuff+16,"dakainuanqi",strlen("dakainuanqi")))    	//打开暖气，对应离线命令词与播报答复列表序号29功能
			{
				printf("the meseeage is dakainuanqi       打开暖气\r\n");  
			}

			 else if(!memcmp(Voice_RevPara.Rxbuff+16,"guanbinuanq",strlen("guanbinuanq")))   //关闭暖气，对应离线命令词与播报答复列表序号30功能
			{
				printf("the meseeage is guanbinuanq       关闭暖气\r\n");  
			}

			else if(!memcmp(Voice_RevPara.Rxbuff+16,"dakaicfeng",strlen("dakaicfeng")))     //打开吹风，对应离线命令词与播报答复列表序号31功能
			{
				printf("the meseeage is dakaicfeng   	   打开吹风\r\n");  
			}	
			else if(!memcmp(Voice_RevPara.Rxbuff+16,"guanbicfeng",strlen("guanbicfeng")))    	//关闭吹风，对应离线命令词与播报答复列表序号32功能
			{
				printf("the meseeage is guanbinuanq       关闭吹风\r\n");  
			}  

			else if(!memcmp(Voice_RevPara.Rxbuff+16,"dakaiyingsji",strlen("dakainuanqi")))    //打开饮水机，对应离线命令词与播报答复列表序号33功能
			{
				printf("the meseeage is dakainuanqi       打开饮水机\r\n");  
			}
			else if(!memcmp(Voice_RevPara.Rxbuff+16,"guanbiyingsji",strlen("guanbiyingsji")))    	//关闭饮水机，对应离线命令词与播报答复列表序号34功能
			{
				printf("the meseeage is guanbiyingsji  	  关闭饮水机\r\n");  
			}

			else if(!memcmp(Voice_RevPara.Rxbuff+16,"kaishichus",strlen("kaishichus")))     //开始出水，对应离线命令词与播报答复列表序号35功能
			{
				printf("the meseeage is kaishichus   	   开始出水\r\n");  
			}
			else if(!memcmp(Voice_RevPara.Rxbuff+16,"tingzchus",strlen("tingzchus")))     	//停止出水，对应离线命令词与播报答复列表序号36功能
			{
				printf("the meseeage is tingzchus   	   停止出水\r\n");  
			}

			else if(!memcmp(Voice_RevPara.Rxbuff+16,"dakdianfangbao",strlen("dakdianfangbao")))   //打开电饭煲，对应离线命令词与播报答复列表序号37功能
			{
				printf("the meseeage is dakdianfangbao    打开电饭煲\r\n");  
			}
			else if(!memcmp(Voice_RevPara.Rxbuff+16,"guabdianfangbao",strlen("guabdianfangbao")))  	//关闭电饭煲，对应离线命令词与播报答复列表序号38功能
			{
				printf("the meseeage is guabdianfangbao   关闭电饭煲\r\n");  
			}

			else if(!memcmp(Voice_RevPara.Rxbuff+16,"baowenmos",strlen("baowenmos")))     	//保温模式，对应离线命令词与播报答复列表序号39功能
			{
				printf("the meseeage is baowenmos   	   保温模式\r\n");  
			}
			else if(!memcmp(Voice_RevPara.Rxbuff+16,"baotangmos",strlen("baotangmos")))     //煲汤模式，对应离线命令词与播报答复列表序号40功能
			{
				printf("the meseeage is baotangmos   	   煲汤模式\r\n");  
			}	
			else if(!memcmp(Voice_RevPara.Rxbuff+16,"zhufangmos",strlen("zhufangmos")))     //煮饭模式，对应离线命令词与播报答复列表序号41功能
			{
				printf("the meseeage is zhufangmos   	   煮饭模式\r\n");  
			}
			else if(!memcmp(Voice_RevPara.Rxbuff+16,"zhuzhoumos",strlen("zhuzhoumos")))     //煮粥模式，对应离线命令词与播报答复列表序号42功能
			{
				printf("the meseeage is baotangmos   	  煮粥模式\r\n");  
			}

			else if(!memcmp(Voice_RevPara.Rxbuff+16,"dakaikaiguan",strlen("dakaikaiguan")))    //打开开关，对应离线命令词与播报答复列表序号43功能
			{
				printf("the meseeage is dakaikaiguan      打开开关\r\n");  
			}
			else if(!memcmp(Voice_RevPara.Rxbuff+16,"guanbikaiguan",strlen("guanbikaiguan")))   	//关闭开关，对应离线命令词与播报答复列表序号44功能
			{
				printf("the meseeage is guanbikaiguan  	  关闭开关\r\n");  
			}

			else if(!memcmp(Voice_RevPara.Rxbuff+16,"dakaishaj",strlen("dakaishaj")))     	//打开杀菌，对应离线命令词与播报答复列表序号45功能
			{
				printf("the meseeage is dakaishaj   	   打开杀菌\r\n");  
			}
			else if(!memcmp(Voice_RevPara.Rxbuff+16,"guanbishaj",strlen("guanbishaj")))     //关闭杀菌，对应离线命令词与播报答复列表序号46功能
			{ 
				printf("the meseeage is guanbishaj   	   关闭杀菌\r\n");  
			}

			else if(!memcmp(Voice_RevPara.Rxbuff+16,"dakaihonggan",strlen("dakaihonggan")))    //打开烘干，对应离线命令词与播报答复列表序号47功能
			{
			printf("the meseeage is dakaihonggan      打开烘干\r\n");  
			}
			else if(!memcmp(Voice_RevPara.Rxbuff+16,"guanbihonggan",strlen("guanbihonggan")))   	//关闭烘干，对应离线命令词与播报答复列表序号48功能
			{
			printf("the meseeage is guanbishaj   	  关闭烘干\r\n");  
			}

			else if(!memcmp(Voice_RevPara.Rxbuff+16,"dakaichuchou",strlen("dakaichuchou")))    //打开除臭，对应离线命令词与播报答复列表序号49功能
			{
				printf("the meseeage is dakaichuchou      打开除臭\r\n");  
			}
			else if(!memcmp(Voice_RevPara.Rxbuff+16,"guanbichuchou",strlen("guanbichuchou")))   	//关闭除臭，对应离线命令词与播报答复列表序号50功能
			{
				printf("the meseeage is guanbichuchou  	  关闭除臭\r\n");  
			}

			else if(!memcmp(Voice_RevPara.Rxbuff+16,"volumeMaxUni",strlen("volumeMaxUni")))    //最大音量，对应离线命令词与播报答复列表序号51功能
			{
				printf("the meseeage is volumeMaxUni      最大音量\r\n");  
			}
			else if(!memcmp(Voice_RevPara.Rxbuff+16,"volumeMinUni",strlen("volumeMinUni")))    //最小音量，对应离线命令词与播报答复列表序号52功能
			{
				printf("the meseeage is volumeMinUni      最小音量\r\n");  
			}

			else if(!memcmp(Voice_RevPara.Rxbuff+16,"settiOonehonor",strlen("settiOonehonor")))   //一小时后开机，对应离线命令词与播报答复列表序号53功能
			{
				printf("the meseeage is settiOonehonor    一小时后开机\r\n");  
			}
			else if(!memcmp(Voice_RevPara.Rxbuff+16,"settiConehonor",strlen("settiConehonor")))   //一小时后关机，对应离线命令词与播报答复列表序号54功能
			{
				printf("the meseeage is settiConehonor    一小时后关机\r\n");  
			}

			else if(!memcmp(Voice_RevPara.Rxbuff+16,"tempset20",strlen("tempset20")))     	//温度设置为20度，对应离线命令词与播报答复列表序号55功能
			{
				printf("the meseeage is tempset20         温度设置为20度\r\n");  
			}
			else if(!memcmp(Voice_RevPara.Rxbuff+16,"TempSet15",strlen("TempSet15")))     	//温度设置为15度，对应离线命令词与播报答复列表序号56功能
			{
				printf("the meseeage is TempSet15         温度设置为15度\r\n");  
			}

			else if(!memcmp(Voice_RevPara.Rxbuff+16,"exitUni",strlen("exitUni")))      	//退下，对应离线命令词与播报答复列表序号57功能
			{
				printf("the meseeage is exitUni           退下，再见\r\n");  
			}
			__HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_3,PWM_Value);				//blue
			commandfinish();
			}
		}
	return Err_None;
}
/**
  * @brief  语音控制继电器开关，高电平触发
  *         
  * @param  Switch
  * @param  
  * @retval none
  */
void Relay_Ctrl(uint8_t Switch)
{
	if(Switch)
	{
		HAL_GPIO_WritePin(Relay_Ctr_GPIO_Port,Relay_Ctr_Pin,GPIO_PIN_SET);
	}
	else
	{
		HAL_GPIO_WritePin(Relay_Ctr_GPIO_Port,Relay_Ctr_Pin,GPIO_PIN_RESET);
	}
}
/**
  * @brief  语音控制继电器开关，切换红灯，高电平触发
  *         
  * @param  Switch
  * @param  
  * @retval none
  */
void RedLed_Ctrl(uint8_t Switch)
{
	if(Switch)
	{
		HAL_GPIO_WritePin(led_run_GPIO_Port,led_run_Pin,GPIO_PIN_SET);
	}
	else
	{
		HAL_GPIO_WritePin(led_run_GPIO_Port,led_run_Pin,GPIO_PIN_RESET);
	}
}

