
/*

#include "delay.h"
#include "sys.h"
#include "key44.h"
#include "usart.h"
 int main(void)
 {	
	int t;
	delay_init();	    	 //延时函数初始化	  
  key44_Init();
	uart_init(9600);
   	while(1)
	{
		
    t=STM32_KEYScan();
		printf("%d",t);
		delay_ms(100);
		
	} 
}


		 t=STM32_KEYScan();//得到键值	 
			switch(t)
			{
				case 0:
			//		   LED0=0;
					   printf("D\n");
				       break;
				case 1:
					   printf("C\n");
				       break;
				case 2:
					   printf("B\n");
				       break;
				case 3:
					   printf("A\n");
				       break;
				case 4:
					  printf("#\n");
				       break;
				case 5:
					  printf("9\n");
				       break;
				case 6:
					  printf("6\n");
				       break;
				case 7:
					  printf("3\n");
				       break;
				case 8:
					  printf("0\n");
				       break;			
				case 9:
					  printf("8\n");
				       break;			
			    case 10:
					  printf("5\n");
				       break;			
				case 11:
					  printf("2\n");
				       break;
				case 12:
					  printf("*\n");
				       break;			
			    case 13:
					  printf("7\n");
				       break;			
				case 14:
					  printf("4\n");
				       break;
				case 15:
					  printf("1\n");
				       break;
			}

			
	*/
	
			