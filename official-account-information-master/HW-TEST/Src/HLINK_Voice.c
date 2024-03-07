/**
  ******************************************************************************
  * @file             HLINK_Voice.c
  * @brief            �������������ģ��Э�����
  ******************************************************************************
  *author��	EmbededС�ɸ�
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
  * @brief  ����ģ�鴮�ڽ��ն�ʱ�����ճ�ʱ����
  *         
  * @param  timeout
  * @param  
  * @retval none
  */
void Voice_RecTimCallBack(uint16_t timeout)  //timeout ms
{
	 if(Voice_RevPara.RxRecFlag){    	//�����ݵ���
			if(Voice_RevPara.RxTimCnt>=timeout){  //�ж϶�ʱ���Ƿ�ʱ��100ms

			Voice_RevPara.RxTimCnt = 0;    //��ʱ�����������㣬������Ϊ��Ϊ���ã�1ms+1
			Voice_RevPara.RxRecFlag = 0;  	

			Voice_RevPara.RxEndFlag = 1;   	//�ӽ�����ɱ�־
			}
		Voice_RevPara.RxTimCnt++;
	 }
}
/**
  * @brief  ����ģ�鴮���жϻص�����
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
  * @brief  ����ģ�鴮�ڽ��ճ�ʼ��
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
  * @brief  ����ģ�鴮����������
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
  * @brief  ����ģ�鴮�ڽ�������Э�����
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
		//�ж�����ͷ
		if(memcmp(Voice_RevPara.Rxbuff,"uArTcP",strlen("uArTcP")))
		{
			return Err_Head;
		}
		else       //�жϾ�����ʲôָ��
		{
			if(!memcmp(Voice_RevPara.Rxbuff+16,"wakeup_uni",strlen("wakeup_uni")))
			{
				printf("the meseeage is wake up           ����ģ��\r\n");
			}
			else if(!memcmp(Voice_RevPara.Rxbuff+16,"openElectricfan",strlen("openElectricfan")))  //�򿪷��ȣ���Ӧ����������벥�����б����1����
			{
				printf("the meseeage is openElectricfan   �򿪷���\r\n");
			}
			else if(!memcmp(Voice_RevPara.Rxbuff+16,"closElectricfan",strlen("closElectricfan")))  //�رշ��ȣ���Ӧ����������벥�����б����2����
			{
				printf("the meseeage is openElectricfan   �رշ���\r\n");
			}
			else if(!memcmp(Voice_RevPara.Rxbuff+16,"AdjustGearmin",strlen("AdjustGearmin")))   //���ȵ�����С����Ӧ����������벥�����б����3����
			{
				printf("the meseeage is AdjustGearmin     ���ȵ�����С\r\n");
			}
			else if(!memcmp(Voice_RevPara.Rxbuff+16,"AdjustGearmax",strlen("AdjustGearmax")))   //���ȵ�����󣬶�Ӧ����������벥�����б����4����
			{
				printf("the meseeage is AdjustGearmax     ���ȵ������\r\n");
			}
			else if(!memcmp(Voice_RevPara.Rxbuff+16,"settiCLonehonor",strlen("settiCLonehonor")))  //��ʱһСʱ�صƣ���Ӧ����������벥�����б����5����
			{
				printf("the meseeage is settiCLonehonor   ��ʱһСʱ�ص�\r\n");
			}
			else if(!memcmp(Voice_RevPara.Rxbuff+16,"settiOPonehonor",strlen("settiOPonehonor")))  //��ʱһСʱ���ƣ���Ӧ����������벥�����б����6����
			{
				printf("the meseeage is settiOPonehonor   ��ʱһСʱ����\r\n");
			}
			else if(!memcmp(Voice_RevPara.Rxbuff+16,"volumeUpUni",strlen("volumeUpUni")))    //�������󣬶�Ӧ����������벥�����б����7����
			{
				printf("the meseeage is volumeUpUni   	  ��������\r\n");
			}
			else if(!memcmp(Voice_RevPara.Rxbuff+16,"volumeDownUni",strlen("volumeDownUni")))   //������С����Ӧ����������벥�����б����8����
			{
				printf("the meseeage is volumeDownUni     ������С\r\n");
			}
			else if(!memcmp(Voice_RevPara.Rxbuff+16,"openkongtiao",strlen("openkongtiao")))   	//�򿪿յ�����Ӧ����������벥�����б����9����
			{
				printf("the meseeage is openkongtiao      �򿪿յ�\r\n");
			}
			else if(!memcmp(Voice_RevPara.Rxbuff+16,"closekongtiao",strlen("closekongtiao")))   //�رտյ�����Ӧ����������벥�����б����10����
			{
				printf("the meseeage is closekongtiao     �رտյ�\r\n");
			}
			else if(!memcmp(Voice_RevPara.Rxbuff+16,"zhidongmos",strlen("zhidongmos")))    	//�Զ�ģʽ����Ӧ����������벥�����б����11����
			{
				printf("the meseeage is zhidongmos   	    �Զ�ģʽ\r\n");  
			}
			else if(!memcmp(Voice_RevPara.Rxbuff+16,"zhilenmos",strlen("zhilenmos")))      //����ģʽ����Ӧ����������벥�����б����12����
			{
				printf("the meseeage is zhilenmos   	   ����ģʽ\r\n");  
			}
			else if(!memcmp(Voice_RevPara.Rxbuff+16,"zhirmos",strlen("zhirmos")))  	     	//����ģʽ����Ӧ����������벥�����б����13����
			{
				printf("the meseeage is zhirmos           ����ģʽ\r\n");   
			}
			else if(!memcmp(Voice_RevPara.Rxbuff+16,"shenggaowendu",strlen("shenggaowendu")))   	//�����¶ȣ���Ӧ����������벥�����б����14����
			{
				printf("the meseeage is shenggaowendu  	  �����¶�\r\n");  
			}
			else if(!memcmp(Voice_RevPara.Rxbuff+16,"jiandiwendu",strlen("jiandiwendu")))    //�����¶ȣ���Ӧ����������벥�����б����15����
			{
				printf("the meseeage is jiandiwendu       �����¶�\r\n");  
			}
			else if(!memcmp(Voice_RevPara.Rxbuff+16,"turnon",strlen("turnon")))       //��̨�ƣ���Ӧ����������벥�����б����16����
			{
				PWM_Value = 100;
				printf("the meseeage is turnon    	     ��̨��\r\n");  
			}
			else if(!memcmp(Voice_RevPara.Rxbuff+16,"turnoff",strlen("turnoff")))      	//�ر�̨�ƣ���Ӧ����������벥�����б����17����
			{
				PWM_Value = 0;
				printf("the meseeage is turnoff           �ر�̨��\r\n");  
			}
			else if(!memcmp(Voice_RevPara.Rxbuff+16,"openled",strlen("openled")))      	//�򿪵ƣ���Ӧ����������벥�����б����18����
			{
				Relay_Ctrl(Relay_Ctrl_OPEN);
				RedLed_Ctrl(0);
				printf("the meseeage is openled           �򿪵�\r\n");  
			}
			else if(!memcmp(Voice_RevPara.Rxbuff+16,"closeled",strlen("closeled")))      //�رյƣ���Ӧ����������벥�����б����19����
			{
				RedLed_Ctrl(0);
				Relay_Ctrl(Relay_Ctrl_CLOSE);
				printf("the meseeage is closeled          �رյ�\r\n");  
			}
			else if(!memcmp(Voice_RevPara.Rxbuff+16,"setmaxld",strlen("setmaxld")))      //������������Ӧ����������벥�����б����20����
			{			
				PWM_Value=500;
				printf("the meseeage is setmaxld          ��������\r\n");  
			}
			else if(!memcmp(Voice_RevPara.Rxbuff+16,"setminld",strlen("setminld")))      //���������Ӧ����������벥�����б����21����
			{
				PWM_Value = 10;
				printf("the meseeage is setminld          �����\r\n");  
			}
			else if(!memcmp(Voice_RevPara.Rxbuff+16,"zengjialiangdu",strlen("zengjialiangdu")))   //�������ȣ���Ӧ����������벥�����б����22����
			{
				
				if(PWM_Value>=500)
					PWM_Value = 500;
				else				
					PWM_Value+=100;
				printf("the meseeage is zengjialiangdu    ��������\r\n");  
			}
			else if(!memcmp(Voice_RevPara.Rxbuff+16,"jianxiaoliangdu",strlen("jianxiaoliangdu")))  	//��С���ȣ���Ӧ����������벥�����б����23����
			{	
				if(PWM_Value<=50)
				{
					PWM_Value = 50;
				}
				else
				PWM_Value-=100;
				printf("the meseeage is jianxiaoliangdu   ��С����\r\n");  
			}
			else if(!memcmp(Voice_RevPara.Rxbuff+16,"setcolorred",strlen("setcolorred")))    	//�Ƶ�Ϊ��ɫ����Ӧ����������벥�����б����24����
			{
				RedLed_Ctrl(1);
				Relay_Ctrl(Relay_Ctrl_CLOSE);
			printf("the meseeage is setcolorred       �Ƶ�Ϊ��ɫ\r\n");  
			}
			else if(!memcmp(Voice_RevPara.Rxbuff+16,"dakaiyuba",strlen("dakaiyuba")))     	//��ԡ�ԣ���Ӧ����������벥�����б����25����
			{
				printf("the meseeage is dakaiyuba   	   ��ԡ��\r\n");  
			}
			else if(!memcmp(Voice_RevPara.Rxbuff+16,"guanbiyuba",strlen("guanbiyuba")))     //�ر�ԡ�ԣ���Ӧ����������벥�����б����26����
			{
				printf("the meseeage is guanbiyuba   	   �ر�ԡ��\r\n");  
			}
			else if(!memcmp(Voice_RevPara.Rxbuff+16,"dakaizaoming",strlen("dakaizaoming")))   	//����������Ӧ����������벥�����б����27����
			{
				printf("the meseeage is dakaizaoming      ������\r\n");  
			}
			else if(!memcmp(Voice_RevPara.Rxbuff+16,"guanbizhaoming",strlen("guanbizhaoming")))   //�ر���������Ӧ����������벥�����б����28����
			{
				printf("the meseeage is dakaiyuba   	   �ر�����\r\n");  
			}

			else if(!memcmp(Voice_RevPara.Rxbuff+16,"dakainuanqi",strlen("dakainuanqi")))    	//��ů������Ӧ����������벥�����б����29����
			{
				printf("the meseeage is dakainuanqi       ��ů��\r\n");  
			}

			 else if(!memcmp(Voice_RevPara.Rxbuff+16,"guanbinuanq",strlen("guanbinuanq")))   //�ر�ů������Ӧ����������벥�����б����30����
			{
				printf("the meseeage is guanbinuanq       �ر�ů��\r\n");  
			}

			else if(!memcmp(Voice_RevPara.Rxbuff+16,"dakaicfeng",strlen("dakaicfeng")))     //�򿪴��磬��Ӧ����������벥�����б����31����
			{
				printf("the meseeage is dakaicfeng   	   �򿪴���\r\n");  
			}	
			else if(!memcmp(Voice_RevPara.Rxbuff+16,"guanbicfeng",strlen("guanbicfeng")))    	//�رմ��磬��Ӧ����������벥�����б����32����
			{
				printf("the meseeage is guanbinuanq       �رմ���\r\n");  
			}  

			else if(!memcmp(Voice_RevPara.Rxbuff+16,"dakaiyingsji",strlen("dakainuanqi")))    //����ˮ������Ӧ����������벥�����б����33����
			{
				printf("the meseeage is dakainuanqi       ����ˮ��\r\n");  
			}
			else if(!memcmp(Voice_RevPara.Rxbuff+16,"guanbiyingsji",strlen("guanbiyingsji")))    	//�ر���ˮ������Ӧ����������벥�����б����34����
			{
				printf("the meseeage is guanbiyingsji  	  �ر���ˮ��\r\n");  
			}

			else if(!memcmp(Voice_RevPara.Rxbuff+16,"kaishichus",strlen("kaishichus")))     //��ʼ��ˮ����Ӧ����������벥�����б����35����
			{
				printf("the meseeage is kaishichus   	   ��ʼ��ˮ\r\n");  
			}
			else if(!memcmp(Voice_RevPara.Rxbuff+16,"tingzchus",strlen("tingzchus")))     	//ֹͣ��ˮ����Ӧ����������벥�����б����36����
			{
				printf("the meseeage is tingzchus   	   ֹͣ��ˮ\r\n");  
			}

			else if(!memcmp(Voice_RevPara.Rxbuff+16,"dakdianfangbao",strlen("dakdianfangbao")))   //�򿪵緹�ң���Ӧ����������벥�����б����37����
			{
				printf("the meseeage is dakdianfangbao    �򿪵緹��\r\n");  
			}
			else if(!memcmp(Voice_RevPara.Rxbuff+16,"guabdianfangbao",strlen("guabdianfangbao")))  	//�رյ緹�ң���Ӧ����������벥�����б����38����
			{
				printf("the meseeage is guabdianfangbao   �رյ緹��\r\n");  
			}

			else if(!memcmp(Voice_RevPara.Rxbuff+16,"baowenmos",strlen("baowenmos")))     	//����ģʽ����Ӧ����������벥�����б����39����
			{
				printf("the meseeage is baowenmos   	   ����ģʽ\r\n");  
			}
			else if(!memcmp(Voice_RevPara.Rxbuff+16,"baotangmos",strlen("baotangmos")))     //����ģʽ����Ӧ����������벥�����б����40����
			{
				printf("the meseeage is baotangmos   	   ����ģʽ\r\n");  
			}	
			else if(!memcmp(Voice_RevPara.Rxbuff+16,"zhufangmos",strlen("zhufangmos")))     //��ģʽ����Ӧ����������벥�����б����41����
			{
				printf("the meseeage is zhufangmos   	   ��ģʽ\r\n");  
			}
			else if(!memcmp(Voice_RevPara.Rxbuff+16,"zhuzhoumos",strlen("zhuzhoumos")))     //����ģʽ����Ӧ����������벥�����б����42����
			{
				printf("the meseeage is baotangmos   	  ����ģʽ\r\n");  
			}

			else if(!memcmp(Voice_RevPara.Rxbuff+16,"dakaikaiguan",strlen("dakaikaiguan")))    //�򿪿��أ���Ӧ����������벥�����б����43����
			{
				printf("the meseeage is dakaikaiguan      �򿪿���\r\n");  
			}
			else if(!memcmp(Voice_RevPara.Rxbuff+16,"guanbikaiguan",strlen("guanbikaiguan")))   	//�رտ��أ���Ӧ����������벥�����б����44����
			{
				printf("the meseeage is guanbikaiguan  	  �رտ���\r\n");  
			}

			else if(!memcmp(Voice_RevPara.Rxbuff+16,"dakaishaj",strlen("dakaishaj")))     	//��ɱ������Ӧ����������벥�����б����45����
			{
				printf("the meseeage is dakaishaj   	   ��ɱ��\r\n");  
			}
			else if(!memcmp(Voice_RevPara.Rxbuff+16,"guanbishaj",strlen("guanbishaj")))     //�ر�ɱ������Ӧ����������벥�����б����46����
			{ 
				printf("the meseeage is guanbishaj   	   �ر�ɱ��\r\n");  
			}

			else if(!memcmp(Voice_RevPara.Rxbuff+16,"dakaihonggan",strlen("dakaihonggan")))    //�򿪺�ɣ���Ӧ����������벥�����б����47����
			{
			printf("the meseeage is dakaihonggan      �򿪺��\r\n");  
			}
			else if(!memcmp(Voice_RevPara.Rxbuff+16,"guanbihonggan",strlen("guanbihonggan")))   	//�رպ�ɣ���Ӧ����������벥�����б����48����
			{
			printf("the meseeage is guanbishaj   	  �رպ��\r\n");  
			}

			else if(!memcmp(Voice_RevPara.Rxbuff+16,"dakaichuchou",strlen("dakaichuchou")))    //�򿪳�������Ӧ����������벥�����б����49����
			{
				printf("the meseeage is dakaichuchou      �򿪳���\r\n");  
			}
			else if(!memcmp(Voice_RevPara.Rxbuff+16,"guanbichuchou",strlen("guanbichuchou")))   	//�رճ�������Ӧ����������벥�����б����50����
			{
				printf("the meseeage is guanbichuchou  	  �رճ���\r\n");  
			}

			else if(!memcmp(Voice_RevPara.Rxbuff+16,"volumeMaxUni",strlen("volumeMaxUni")))    //�����������Ӧ����������벥�����б����51����
			{
				printf("the meseeage is volumeMaxUni      �������\r\n");  
			}
			else if(!memcmp(Voice_RevPara.Rxbuff+16,"volumeMinUni",strlen("volumeMinUni")))    //��С��������Ӧ����������벥�����б����52����
			{
				printf("the meseeage is volumeMinUni      ��С����\r\n");  
			}

			else if(!memcmp(Voice_RevPara.Rxbuff+16,"settiOonehonor",strlen("settiOonehonor")))   //һСʱ�󿪻�����Ӧ����������벥�����б����53����
			{
				printf("the meseeage is settiOonehonor    һСʱ�󿪻�\r\n");  
			}
			else if(!memcmp(Voice_RevPara.Rxbuff+16,"settiConehonor",strlen("settiConehonor")))   //һСʱ��ػ�����Ӧ����������벥�����б����54����
			{
				printf("the meseeage is settiConehonor    һСʱ��ػ�\r\n");  
			}

			else if(!memcmp(Voice_RevPara.Rxbuff+16,"tempset20",strlen("tempset20")))     	//�¶�����Ϊ20�ȣ���Ӧ����������벥�����б����55����
			{
				printf("the meseeage is tempset20         �¶�����Ϊ20��\r\n");  
			}
			else if(!memcmp(Voice_RevPara.Rxbuff+16,"TempSet15",strlen("TempSet15")))     	//�¶�����Ϊ15�ȣ���Ӧ����������벥�����б����56����
			{
				printf("the meseeage is TempSet15         �¶�����Ϊ15��\r\n");  
			}

			else if(!memcmp(Voice_RevPara.Rxbuff+16,"exitUni",strlen("exitUni")))      	//���£���Ӧ����������벥�����б����57����
			{
				printf("the meseeage is exitUni           ���£��ټ�\r\n");  
			}
			__HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_3,PWM_Value);				//blue
			commandfinish();
			}
		}
	return Err_None;
}
/**
  * @brief  �������Ƽ̵������أ��ߵ�ƽ����
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
  * @brief  �������Ƽ̵������أ��л���ƣ��ߵ�ƽ����
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

