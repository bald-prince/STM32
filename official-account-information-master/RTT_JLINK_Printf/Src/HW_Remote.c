#include "HW_Remote.h"
#include "main.h"
#include "stdio.h"


extern TIM_HandleTypeDef htim4;

typedef struct Remote{

	uint8_t  RmtSta;	  	  
	uint16_t Dval;						//下降沿时计数器的值
	uint32_t RmtRec;					//红外接收到的数据	   		    
	uint8_t  RmtCnt;					//按键按下的次数	 

}Remotepara;

Remotepara RemoteParameters;

void RemoteInit()
{
	HAL_TIM_Base_Start_IT(&htim4);
	HAL_TIM_IC_Start_IT(&htim4,TIM_CHANNEL_4);   																//开始捕获TIM4的通道4
	Remotepara RemoteParameters = {0};
}

void RemoteDataTimerCallBack()
{
	 	if(RemoteParameters.RmtSta&0x80)																					//上次有数据被接收到了
		{	
			RemoteParameters.RmtSta&=~0X10;																					//取消上升沿已经被捕获标记
			if((RemoteParameters.RmtSta&0X0F)==0X00)RemoteParameters.RmtSta|=1<<6;	//标记已经完成一次按键的键值信息采集
			if((RemoteParameters.RmtSta&0X0F)<14)RemoteParameters.RmtSta++;
			else
			{
				RemoteParameters.RmtSta&=~(1<<7);				//清空引导标识
				RemoteParameters.RmtSta&=0XF0;					//清空计数器	
			}						 	   	
		}	
}

//定时器输入捕获中断回调函数

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)				//捕获中断发生时执行
{
	if(htim->Instance==TIM4)
	{
		if(RDATA)																										//上升沿捕获
		{
			TIM_RESET_CAPTUREPOLARITY(&htim4,TIM_CHANNEL_4);   							//一定要先清除原来的设置！！
			TIM_SET_CAPTUREPOLARITY(&htim4,TIM_CHANNEL_4,TIM_ICPOLARITY_FALLING);		//CC4P=1 设置为下降沿捕获
			__HAL_TIM_SET_COUNTER(&htim4,0);  											//清空定时器值   	  
		  RemoteParameters.RmtSta|=0X10;												//标记上升沿已经被捕获
		}else //下降沿捕获
		{
			RemoteParameters.Dval=HAL_TIM_ReadCapturedValue(&htim4,TIM_CHANNEL_4);		//读取CCR4也可以清CC4IF标志位
			TIM_RESET_CAPTUREPOLARITY(&htim4,TIM_CHANNEL_4);   							//一定要先清除原来的设置！！
			TIM_SET_CAPTUREPOLARITY(&htim4,TIM_CHANNEL_4,TIM_ICPOLARITY_RISING);		//配置TIM4通道4上升沿捕获
			if(RemoteParameters.RmtSta&0X10)											//完成一次高电平捕获 
			{
 				if(RemoteParameters.RmtSta&0X80)										//接收到了引导码
				{
					
					if(RemoteParameters.Dval>300&&RemoteParameters.Dval<800)			//560为标准值,560us
					{
						RemoteParameters.RmtRec<<=1;									//左移一位.
						RemoteParameters.RmtRec|=0;										//接收到0	   
					}
					else if(RemoteParameters.Dval>1400&&RemoteParameters.Dval<1800)	//1680为标准值,1680us
					{
						RemoteParameters.RmtRec<<=1;									//左移一位.
						RemoteParameters.RmtRec|=1;										//接收到1
					}
					else if(RemoteParameters.Dval>2200&&RemoteParameters.Dval<2600)	//得到按键键值增加的信息 2500为标准值2.5ms
					{
						RemoteParameters.RmtCnt++; 													//按键次数增加1次
						RemoteParameters.RmtSta&=0XF0;									//清空计时器		
					}
 				}
				else if(RemoteParameters.Dval>4200&&RemoteParameters.Dval<4700)		//4500为标准值4.5ms
				{
					RemoteParameters.RmtSta|=1<<7;										//标记成功接收到了引导码
					RemoteParameters.RmtCnt=0;											//清除按键次数计数器
				}						 
			}
			RemoteParameters.RmtSta&=~(1<<4);
		}
	}
}

//处理红外键盘
//返回值:
//0,没有任何按键按下
//其他,按下的按键键值.
uint8_t Remote_Scan(void)
{        
	uint8_t sta=0;       
	uint8_t t1,t2;  
	if(RemoteParameters.RmtSta&(1<<6))									//得到一个按键的所有信息了
	{ 
	    t1=RemoteParameters.RmtRec>>24;									//得到地址码
	    t2=(RemoteParameters.RmtRec>>16)&0xff;							//得到地址反码 
 	    if((t1==(uint8_t)~t2)&&t1==REMOTE_ID)							//检验遥控识别码(ID)及地址 
	    { 
	        t1=RemoteParameters.RmtRec>>8;
	        t2=RemoteParameters.RmtRec; 	
	        if(t1==(uint8_t)~t2)sta=t1;//键值正确	 
					RemoteParameters.RmtRec=0;
		}   
		if((sta==0)||((RemoteParameters.RmtSta&0X80)==0))//按键数据错误/遥控已经没有按下了
		{
		 	RemoteParameters.RmtSta&=~(1<<6);//清除接收到有效按键标识
			RemoteParameters.RmtCnt=0;		//清除按键次数计数器
			RemoteParameters.RmtRec=0;
		}
	}  
  return sta;
}

char *KeyValueConvert(uint8_t keyValue)
{
	char *str=0;
	switch (keyValue)
	{
		case 162:
			str = "1";
		break;
		case 98:
			str = "2";
		break;
		case 226:
			str = "3";
		break;	
		case 34:
			str = "4";
		break;
		case 2:
			str = "5";
		break;
		case 194:
			str = "6";
		break;
		case 224:
			str = "7";
		break;
		case 168:
			str = "8";
		break;
		case 144:
			str = "9";
		break;
		case 104:
			str = "*";
		break;
		case 152:
			str = "0";
		break;
		case 176:
			str = "#";
		break;
		case 24:
			str = "UP";
		break;
		case 16:
			str = "LEFT";
		break;
		case 56:
			str = "OK";
		break;
		case 90:
			str = "RIGHT";
		break;
		case 74:
			str = "DOWN";
		break;
	}
	//printf("The KeyValue is %s \r\n",(char *)(str));
	
	return str;
}
