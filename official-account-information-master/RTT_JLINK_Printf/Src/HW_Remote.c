#include "HW_Remote.h"
#include "main.h"
#include "stdio.h"


extern TIM_HandleTypeDef htim4;

typedef struct Remote{

	uint8_t  RmtSta;	  	  
	uint16_t Dval;						//�½���ʱ��������ֵ
	uint32_t RmtRec;					//������յ�������	   		    
	uint8_t  RmtCnt;					//�������µĴ���	 

}Remotepara;

Remotepara RemoteParameters;

void RemoteInit()
{
	HAL_TIM_Base_Start_IT(&htim4);
	HAL_TIM_IC_Start_IT(&htim4,TIM_CHANNEL_4);   																//��ʼ����TIM4��ͨ��4
	Remotepara RemoteParameters = {0};
}

void RemoteDataTimerCallBack()
{
	 	if(RemoteParameters.RmtSta&0x80)																					//�ϴ������ݱ����յ���
		{	
			RemoteParameters.RmtSta&=~0X10;																					//ȡ���������Ѿ���������
			if((RemoteParameters.RmtSta&0X0F)==0X00)RemoteParameters.RmtSta|=1<<6;	//����Ѿ����һ�ΰ����ļ�ֵ��Ϣ�ɼ�
			if((RemoteParameters.RmtSta&0X0F)<14)RemoteParameters.RmtSta++;
			else
			{
				RemoteParameters.RmtSta&=~(1<<7);				//���������ʶ
				RemoteParameters.RmtSta&=0XF0;					//��ռ�����	
			}						 	   	
		}	
}

//��ʱ�����벶���жϻص�����

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)				//�����жϷ���ʱִ��
{
	if(htim->Instance==TIM4)
	{
		if(RDATA)																										//�����ز���
		{
			TIM_RESET_CAPTUREPOLARITY(&htim4,TIM_CHANNEL_4);   							//һ��Ҫ�����ԭ�������ã���
			TIM_SET_CAPTUREPOLARITY(&htim4,TIM_CHANNEL_4,TIM_ICPOLARITY_FALLING);		//CC4P=1 ����Ϊ�½��ز���
			__HAL_TIM_SET_COUNTER(&htim4,0);  											//��ն�ʱ��ֵ   	  
		  RemoteParameters.RmtSta|=0X10;												//����������Ѿ�������
		}else //�½��ز���
		{
			RemoteParameters.Dval=HAL_TIM_ReadCapturedValue(&htim4,TIM_CHANNEL_4);		//��ȡCCR4Ҳ������CC4IF��־λ
			TIM_RESET_CAPTUREPOLARITY(&htim4,TIM_CHANNEL_4);   							//һ��Ҫ�����ԭ�������ã���
			TIM_SET_CAPTUREPOLARITY(&htim4,TIM_CHANNEL_4,TIM_ICPOLARITY_RISING);		//����TIM4ͨ��4�����ز���
			if(RemoteParameters.RmtSta&0X10)											//���һ�θߵ�ƽ���� 
			{
 				if(RemoteParameters.RmtSta&0X80)										//���յ���������
				{
					
					if(RemoteParameters.Dval>300&&RemoteParameters.Dval<800)			//560Ϊ��׼ֵ,560us
					{
						RemoteParameters.RmtRec<<=1;									//����һλ.
						RemoteParameters.RmtRec|=0;										//���յ�0	   
					}
					else if(RemoteParameters.Dval>1400&&RemoteParameters.Dval<1800)	//1680Ϊ��׼ֵ,1680us
					{
						RemoteParameters.RmtRec<<=1;									//����һλ.
						RemoteParameters.RmtRec|=1;										//���յ�1
					}
					else if(RemoteParameters.Dval>2200&&RemoteParameters.Dval<2600)	//�õ�������ֵ���ӵ���Ϣ 2500Ϊ��׼ֵ2.5ms
					{
						RemoteParameters.RmtCnt++; 													//������������1��
						RemoteParameters.RmtSta&=0XF0;									//��ռ�ʱ��		
					}
 				}
				else if(RemoteParameters.Dval>4200&&RemoteParameters.Dval<4700)		//4500Ϊ��׼ֵ4.5ms
				{
					RemoteParameters.RmtSta|=1<<7;										//��ǳɹ����յ���������
					RemoteParameters.RmtCnt=0;											//�����������������
				}						 
			}
			RemoteParameters.RmtSta&=~(1<<4);
		}
	}
}

//����������
//����ֵ:
//0,û���κΰ�������
//����,���µİ�����ֵ.
uint8_t Remote_Scan(void)
{        
	uint8_t sta=0;       
	uint8_t t1,t2;  
	if(RemoteParameters.RmtSta&(1<<6))									//�õ�һ��������������Ϣ��
	{ 
	    t1=RemoteParameters.RmtRec>>24;									//�õ���ַ��
	    t2=(RemoteParameters.RmtRec>>16)&0xff;							//�õ���ַ���� 
 	    if((t1==(uint8_t)~t2)&&t1==REMOTE_ID)							//����ң��ʶ����(ID)����ַ 
	    { 
	        t1=RemoteParameters.RmtRec>>8;
	        t2=RemoteParameters.RmtRec; 	
	        if(t1==(uint8_t)~t2)sta=t1;//��ֵ��ȷ	 
					RemoteParameters.RmtRec=0;
		}   
		if((sta==0)||((RemoteParameters.RmtSta&0X80)==0))//�������ݴ���/ң���Ѿ�û�а�����
		{
		 	RemoteParameters.RmtSta&=~(1<<6);//������յ���Ч������ʶ
			RemoteParameters.RmtCnt=0;		//�����������������
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
