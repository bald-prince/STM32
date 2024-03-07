#include "stm32f10x.h"
#include "LED.h"
#include "delay.h"

 int main(void)
 {	
	 
	 
	 LED_Init();
	 delay_init();

  while(1){

	PAout(8)=1;
	PDout(2)=1;
  delay_ms(500);
		
	PAout(8)=0;
	PDout(2)=0;
	delay_ms(500);
		
	}
	
 }
 

