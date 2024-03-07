#include "ultrasonic.h"
#include "timer32.h"

ULS ULS_Distance;

void UL_Init(void)
{
		P5DIR |= GPIO_PIN4|GPIO_PIN5;
		GPIO_setAsOutputPin(GPIO_PORT_P5, GPIO_PIN4);
		GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN4);
	  GPIO_setAsInputPin(GPIO_PORT_P5, GPIO_PIN5);
	
   	GPIO_setAsOutputPin(GPIO_PORT_P8, GPIO_PIN4);
		GPIO_setOutputLowOnPin(GPIO_PORT_P8, GPIO_PIN4);
	  GPIO_setAsInputPin(GPIO_PORT_P8, GPIO_PIN5);
	
	  GPIO_setAsOutputPin(GPIO_PORT_P8, GPIO_PIN6);
		GPIO_setOutputLowOnPin(GPIO_PORT_P8, GPIO_PIN6);
	  GPIO_setAsInputPin(GPIO_PORT_P8, GPIO_PIN7);
	  
}

double Calc_Barrier_Distance(void)
{
		uint32_t count = 0;
		double distance = 0;
		uint32_t now = 0;
		uint8_t flag = 0;
	
		GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN4);
		Delay_us(12);
		GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN4);
	
		
		while (!GPIO_getInputPinValue(GPIO_PORT_P5, GPIO_PIN5));
		while (GPIO_getInputPinValue(GPIO_PORT_P5, GPIO_PIN5))
		{
				if (flag == 0)
				{
						now = GetSysTime_us();				
						flag = 1;
				}
		}
		count = GetSysTime_us() - now;
		distance = 0.017*count;	//340m/s = 34000cm/s = 0.034cm/us
			
		return distance;
}
//Òì²½4-5us·Ç×èÈû
double Calc_ULS_Conclude()
{
	static int flag=1;
	double distance;
	static int Ticks;
  static double dis_o;
	if(flag)
	{
			GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN4);
			Delay_us(12);
			GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN4);
		  flag = 0;
  }
	if(!flag)
	{
		static int flag1 = 1;
		if(GPIO_getInputPinValue(GPIO_PORT_P5, GPIO_PIN5)&&flag1)
		{
			Ticks = GetSysTime_us();
			flag1=0;
		}
		if( ( !GPIO_getInputPinValue(GPIO_PORT_P5, GPIO_PIN5) )&&(!flag1) )
		{
			  distance = (GetSysTime_us()-Ticks)*0.017;flag1=1;flag=1;dis_o = distance ; return distance;
		}
		else
			return dis_o;
	}
}

//Òì²½4-5us·Ç×èÈû
double Calc_ULS_Conclude_Tim(int usT,int *flag)
{
//	static int flag=1;
	double distance;
	static int Ticks;
  static double dis_o;
//	if(flag)
//	{
//			GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN4);
//			Delay_us(12);
//			GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN4);
//		  flag = 0;
//  }
	if(!(*flag))
	{
		static int flag1 = 1;
		if(GPIO_getInputPinValue(GPIO_PORT_P5, GPIO_PIN5)&&flag1)
		{
			Ticks = usT;
			flag1=0;
		}
		if( ( !GPIO_getInputPinValue(GPIO_PORT_P5, GPIO_PIN5) )&&(!flag1) )
		{
			  distance = 10*(usT-Ticks)*0.017;flag1=1;*flag=1;dis_o = distance ; return distance;
		}
		else
			return dis_o;
	}
}
//Òì²½10Us·Ç×èÈû
void ULS_Acquire(ULS *Dir)
{
	static int flag=1;
	static int Ticks[3];
  static double dis_o[3];
	if(flag)
	{
			GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN4);
		  GPIO_setOutputHighOnPin(GPIO_PORT_P8, GPIO_PIN4);
		  GPIO_setOutputHighOnPin(GPIO_PORT_P8, GPIO_PIN6);
			Delay_us(12);
			GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN4);
		  GPIO_setOutputLowOnPin(GPIO_PORT_P8, GPIO_PIN4);
		  GPIO_setOutputLowOnPin(GPIO_PORT_P8, GPIO_PIN6);
		  flag = 0;
  }
	if(!flag)
	{
		static int flag1[3] = {1,1,1};
		if(GPIO_getInputPinValue(GPIO_PORT_P5, GPIO_PIN5)&&flag1[0])//front_distance
		{
			Ticks[0] = GetSysTime_us();
			flag1[0]=0;
		}
		if(GPIO_getInputPinValue(GPIO_PORT_P8, GPIO_PIN5)&&flag1[1])//left_distance
		{
			Ticks[1] = GetSysTime_us();
			flag1[1]=0;
		}
		if(GPIO_getInputPinValue(GPIO_PORT_P8, GPIO_PIN7)&&flag1[2])//right_distance
		{
			Ticks[2] = GetSysTime_us();
			flag1[2]=0;
		}
		
		                                                            //¾àÀë²âËã
		if( ( !GPIO_getInputPinValue(GPIO_PORT_P5, GPIO_PIN5) )&&(!flag1[0]) )
		{
		  Dir->dis_front = (GetSysTime_us()-Ticks[0])*0.17;flag1[0]=1;dis_o[0]= Dir->dis_front;
		}
		else
		{
			 Dir->dis_front = dis_o[0];
		}
		if( ( !GPIO_getInputPinValue(GPIO_PORT_P8, GPIO_PIN5) )&&(!flag1[1]) )
		{
		  Dir->dis_left = (GetSysTime_us()-Ticks[1])*0.017;flag1[1]=1;dis_o[1]= Dir->dis_left;
		}
		else
		{
			 Dir->dis_left = dis_o[1];
		}
		if( ( !GPIO_getInputPinValue(GPIO_PORT_P8, GPIO_PIN7) )&&(!flag1[2]) )
		{
		  Dir->dis_right = (GetSysTime_us()-Ticks[2])*0.017;flag1[2]=1;dis_o[2]= Dir->dis_right;
		}
		else
		{
			 Dir->dis_right = dis_o[2];
		}
		if(flag1[0]/*&flag1[1]&&flag1[2]*/)
			flag = 1;
	}
}

