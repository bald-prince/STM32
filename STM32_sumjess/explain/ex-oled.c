/*

*******************************************************************************
================================================================================
��ƽ    ̨��stm32f103zet6_sumjessƽ̨
����    д��sumjess
��E-mail  ��1371129880@qq.com
������汾��V2.0
�������¡�2018��01��21��
�������Ϣ�ο����е�ַ��
����    վ��http://www.openedv.com/
           http://www.stmcu.org/
					 http://www.firebbs.cn/forum.php
---------------------------------------------------------------------------------
��dev.env.��MDK5.14�����ϰ汾
��Target  ��stm32f103zet6
��һ���޶���2017/11/09
�ڶ����޶���2018/01/21
---------------------------------------------------------------------------------
û�������Ĵ��룬ֻ�в��ϵķ��ף����һ��Ŭ����
����õ���������㣬��ӭ��ҷ���bug��
================================================================================
********************************************************************************




//////////////////////////////////////////////////////////////////////////////////	 
//              ˵��: 
//              ----------------------------------------------------------------
//              GND    ��Դ��
//              VCC  ��5V��3.3v��Դ
//              D0   ��PB13��SCL��
//              D1   ��PB15��SDA��
//              RES  ��PB11
//              DC   ��PB10
//              CS   ��P12               
//              ----------------------------------------------------------------
// ******************************************************************************
#include "delay.h"
#include "sys.h"
#include "sumjess_oled.h"
#include "bmp.h"
 int main(void)
 {	u8 t;
		delay_init();	    	 //��ʱ������ʼ��	  
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ� 	LED_Init();			     //LED�˿ڳ�ʼ��
		OLED_Init();			//��ʼ��OLED  
		OLED_Clear(); 
		
	while(1) 
	{		
		
		OLED_Clear();
		LED_ON;
   	OLED_ShowCHinese(63,3,90);//
		OLED_ShowCHinese(18,0,1);//
		OLED_ShowCHinese(36,0,2);//
		OLED_ShowCHinese(54,0,3);***************��ʾ����,��Ҫ�ĺ�����OLEDFONT.H�����
		OLED_ShowCHinese(72,0,4);//
		OLED_ShowCHinese(90,0,5);//
		OLED_ShowCHinese(108,0,6);//
		
		
	  OLED_ShowString(0,3,"1.3' OLED TEST");********
		OLED_ShowString(8,2,"sumjess");********(x,y,�ַ��Ŵ���
		
	  OLED_ShowString(20,4,"2014/05/01"); *******
		
		OLED_ShowString(0,6,"ASCII:");  **********
		OLED_ShowString(63,6,"CODE:");  ***********
		
		
		OLED_ShowChar(48,6,t);//��ʾASCII�ַ�	 ******** ָ��λ����ʾһ���ַ�,���������ַ�//x:0~127//y:0~63

		t++;
	if(t>'~')t=' ';
		OLED_ShowNum(103,6,t,3,16);//��ʾASCII�ַ�����ֵ(x,y,��ֵ������λ���������С�� 
			
		delay_ms(8000);
		
		
		
		
*******************************************************************************************************************		
****************ͼƬ��ʾ(ͼƬ��ʾ���ã����ɵ��ֱ�ϴ󣬻�ռ�ý϶�ռ䣬FLASH�ռ�8K��������)****************************
********************************************************ͼƬ*******************************************************
	************************************************************************************************************	
	  OLED_Clear();
		delay_ms(8000);
		LED_OFF;	
		OLED_DrawBMP(0,0,128,8,BMP1);  //
		delay_ms(8000);
		OLED_DrawBMP(0,0,128,8,BMP2);  //
		delay_ms(8000);

BMP1��BMP2��BMP.H���޸�
************������������ʾ��ʾBMPͼƬ128��64��ʼ������(x,y),x�ķ�Χ0��127��yΪҳ�ķ�Χ0��7****************

********************************************************************************************************************
_______________________________________________________________________________________________________________________
***************************************
**************OLED.c�е���**************
***************************************
#define OLED_MODE 0     //0,������ʾ;1,������ʾ
#define SIZE 16         //�����С
#define XLevelL		0x00
#define XLevelH		0x10
#define Max_Column	128  //128��
#define Max_Row		64     //64��
#define	Brightness	0xFF //����
#define X_WIDTH 	128    //x���
#define Y_WIDTH 	64	    //y���








������Դ��





#include "delay.h"
#include "sys.h"
#include "oled.h"
#include "bmp.h"
 int main(void)
 {	u8 t;
		delay_init();	    	 //��ʱ������ʼ��	  
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ� 	LED_Init();			     //LED�˿ڳ�ʼ��
		OLED_Init();			//��ʼ��OLED  
		OLED_Clear()  	; 
		
	  OLED_ShowString(30,0,"OLED TEST");
		OLED_ShowString(8,2,"ZHONGJINGYUAN");  
		OLED_ShowString(20,4,"2014/05/01");  
		OLED_ShowString(0,6,"ASCII:");  
		OLED_ShowString(63,6,"CODE:");  
		t=' '; 
		OLED_ShowCHinese(0,0,0);//��
		OLED_ShowCHinese(18,0,1);//ʾ
		OLED_ShowCHinese(36,0,2);//��
		OLED_ShowCHinese(54,0,3);//��
		OLED_ShowCHinese(72,0,4);//
		OLED_ShowCHinese(90,0,5);//
		OLED_ShowCHinese(108,0,6);//
		
		t=' ';
	while(1) 
	{		
		
		OLED_Clear();
		LED_ON;
   	OLED_ShowCHinese(0,0,0);//
		OLED_ShowCHinese(18,0,1);//
		OLED_ShowCHinese(36,0,2);//
		OLED_ShowCHinese(54,0,3);//��
		OLED_ShowCHinese(72,0,4);//ʾ
		OLED_ShowCHinese(90,0,5);//��
		OLED_ShowCHinese(108,0,6);//��
	  OLED_ShowString(0,3,"1.3' OLED TEST");
		OLED_ShowString(8,2,"sumjess");  
	  OLED_ShowString(20,4,"2014/05/01");  
		OLED_ShowString(0,6,"ASCII:");  
		OLED_ShowString(63,6,"CODE:");  
		OLED_ShowChar(48,6,t);//��ʾASCII�ַ�	   
		t++;
	if(t>'~')t=' ';
		OLED_ShowNum(103,6,t,3,16);//��ʾASCII�ַ�����ֵ 	
			
		delay_ms(8000);
	OLED_Clear();
		delay_ms(8000);
		LED_OFF;	
		OLED_DrawBMP(0,0,128,8,BMP1);  //ͼƬ��ʾ(ͼƬ��ʾ���ã����ɵ��ֱ�ϴ󣬻�ռ�ý϶�ռ䣬FLASH�ռ�8K��������)
		delay_ms(8000);
		OLED_DrawBMP(0,0,128,8,BMP2);
		delay_ms(8000);

	}	  
	
}




#include "delay.h"
#include "sys.h"
#include "sumjess_oled.h"


 int main(void)
 {	
  int t=99;
	float pitch=5.56;
	char pitch_x[20];
	delay_init();	    	 //��ʱ������ʼ��	  
  OLED_Init();
   	while(1)
	{
    OLED_Clear();//����
    //-***************��ʾ����,��Ҫ�ĺ�����OLEDFONT.H�����
		OLED_ShowCHinese(90,0,5);//����
		OLED_ShowCHinese(108,0,6);//����		

	  OLED_ShowString(0,3,"1.3' OLED TEST");//-********
		OLED_ShowString(8,5,"sumjess");//-********(x,y,�ַ��Ŵ���
		
		sprintf(pitch_x,"value=%0.3f",pitch);//��ӡר��
	  OLED_ShowString(0,0,(u8*)pitch_x);//��̬������

		OLED_ShowChar(90,7,t);//��ʾASCII�ַ�	 ******** ָ��λ����ʾһ���ַ�,���������ַ�//x:0~127//y:0~63
    delay_ms(50);//�ʵ���ʱʹOLED����
	} 
}
  




while(1)
					{
		mpu_dmp_get_data(&pitch,&roll,&yaw);
		OLED_Clear();			
		if(mpu_dmp_get_data(&pitch,&roll,& yaw)==0)
		{
			
			temp=MPU_Get_Temperature();	//�õ��¶�ֵ
		  OLED_ShowNum(60,0,temp,3,16);		
			MPU_Get_Accelerometer(&aacx,&aacy,&aacz);	//�õ����ٶȴ���������
			MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);	//�õ�����������
			//������
			pitch_oled();
      sprintf(pitch_x,"%0.3f",pitch);
		  OLED_ShowString(60,2,(u8*)pitch_x);				
			printf("%0.3f",pitch);
			printf("\n");
		  //ƫ����
			yaw_oled();
      sprintf(roll_x,"%0.3f",roll);
		  OLED_ShowString(60,4,(u8*)roll_x);				
			printf("%0.3f",roll);		
			printf("\n");
			//������
			roll_oled();
      sprintf(yaw_x,"%0.3f",yaw);
		  OLED_ShowString(60,6,(u8*)yaw_x);
			printf("%0.3f",yaw);
			printf("\n");		
			
			delay_ms(80);
			OLED_Clear();
					}
		  	}


*/





