#include "stm32f10x.h"

//���Ŷ����ڿ��ļ����޸�
//Max7219_pinDIN	    B9
//Max7219_pinCS			B8
//Max7219_pinCLK	    B7

int main(void)
{	
	M_SysTick_Init();                   //Systicʱ�ӳ�ʼ��
   
    Init_MAX7219();   //��ʼ����Ļ
	Clear_Display();  //�����Ļ��ʾ
	
	while(1)
	{		
		Number_Display(35);   //������ʾ����35
	}
}

