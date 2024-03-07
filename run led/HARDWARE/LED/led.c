#include "led.h"
#include "delay.h"

u8 table[4][8]={																															//������ˮ������
	                  {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80},     
										{0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01},
										{0x81,0xc3,0xe7,0xff,0xff,0xe7,0xc3,0x81},
										{0x81,0x42,0x24,0x18,0x18,0x24,0x42,0x81},
               };
u8 HYLSD_code[4][8]={
											{0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80},
											{0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80},
											{0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01},
											{0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff},
										};

void LED_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;
    __HAL_RCC_GPIOC_CLK_ENABLE();           							 //����GPIOCʱ��
	
    GPIO_Initure.Pin=GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;						  		//PC0~7
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  							//�������
    GPIO_Initure.Pull=GPIO_PULLUP;          							//����
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     							//����
    HAL_GPIO_Init(GPIOC,&GPIO_Initure);
	
    Write_Pin(0Xff);		
}
//switsh case ���ʵ����ˮ��
void LED_light(int num)
{
	  switch(num)
		{
			case 0:
					LED0=0;
					break;
			case 1:
					LED1=0;
					break;
			case 2:
					LED2=0;
					break;
			case 3:
					LED3=0;
					break;
			case 4:
					LED4=0;
					break;
			case 5:
					LED5=0;
					break;
			case 6:
					LED6=0;
					break;
			case 7:
					LED7=0;
					break;
			case 8:
					LED6=0;
					break;
			case 9:
					LED5=0;
					break;
			case 10:
					LED4=0;
					break;
			case 11:
					LED3=0;
					break;
			case 12:
					LED2=0;
					break;
			case 13:
					LED1=0;
					break;
			default:
					break;
			
		}
		
}


//����
u8 youyi_led(u8 dat,u8 number)
{
	u8 temp;
	while(number--)
	{	
		 if (dat&0x01)
			 temp=(dat>>1)|0x80;
		 else
			 temp=dat>>1;
		 dat=temp;
  }
	return temp;
		
}

//����
u8 zuoyi_led(u8 dat,u8 number)
{
	u8 temp;
	while(number--)
	{	
		 if(dat & 0x80)
			 temp = (dat<<1) | 0x01;
		 else
			 temp = dat<<1;
		 dat = temp;
  }
	return temp;	
}


void Write_Pin(u8 dat)
{
	GPIOC->ODR &= ~0xff;                              //�Ե�8λ���㣬ͬʱ����λ���仯
	GPIOC->ODR |= dat;                                //�Ե�8λ��ֵ
}


//���鷽ʽʵ�ֻ�����ˮ��
void shuzu_Led(void)
{
	u8 i,j;
	for(i=0;i<4;i++)
	{
		for(j=0;j<8;j++)
		{
			Write_Pin(~HYLSD_code[i][j]);
			delay_ms(200);
		}
	}
}

//�ɿص���ˮ�仯,direct=1���ƣ�direct=0���ƣ�
void kekong_Led(u8 Led_dat,u8 direct)
{
	u8 i;
	//������ˮ��
	if(direct)
		for(i=0;i<8;i++)
		{
			Write_Pin(Led_dat);
			delay_ms(300);
			Led_dat = zuoyi_led(Led_dat,1);
		}
	else
		//������ˮ��
		for(i=0;i<8;i++)
		{
			Write_Pin(Led_dat);
			delay_ms(300);
			Led_dat = youyi_led(Led_dat,1);
		}
}

//һ������λ
void Flow_Led(u8 Led_dat)
{
	u8 i;
	//������ˮ��
	for(i=0;i<4;i++)
	{
		Write_Pin(Led_dat);
		delay_ms(300);
		Led_dat=zuoyi_led(Led_dat,2);
	}
}


void kekong_Led_led(u8 Led_dat)
{
	u8 i;
	//������ˮ��
	 for(i=0;i<7;i++)
		{
			Write_Pin(Led_dat);
			delay_ms(300);
			Led_dat=zuoyi_led(Led_dat,1);
		}
}


