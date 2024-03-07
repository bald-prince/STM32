#include "myiic.h"
#include "delay.h"
	

//��ʼ��IIC
//SDA PE15
//SCL PD9
void IIC_Init(void)
{			
  GPIO_InitTypeDef  GPIO_InitStructure;
  //RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
  //RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();

  GPIO_InitStructure.Pin = GPIO_PIN_9;
  GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP ;//��ͨ���ģʽ
  GPIO_InitStructure.Pull = GPIO_PULLUP;//�������
  GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_VERY_HIGH;//100MHz
  HAL_GPIO_Init(GPIOD, &GPIO_InitStructure);//��ʼ��
  GPIO_InitStructure.Pin = GPIO_PIN_15;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStructure);//��ʼ��
  IIC_SCL=1;
  IIC_SDA=1;
}

//����IIC��ʼ�ź�
void IIC_Start(void)
{
	SDA_OUT();     //sda�����
	IIC_SDA=1;	  	  
	IIC_SCL=1;  
	delay_us(2);
 	IIC_SDA=0;     //START:when CLK is high,DATA change form high to low 
	delay_us(2);
	IIC_SCL=0;     //ǯסI2C���ߣ�׼�����ͻ�������� 
}	  


//����IICֹͣ�ź�
void IIC_Stop(void)
{
	SDA_OUT();//sda�����
	IIC_SCL=0;
	IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
 	delay_us(2);
	IIC_SCL=1; 
	IIC_SDA=1;//����I2C���߽����ź�
	delay_us(2);							   					   	
}


//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�

u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	SDA_IN();      //SDA����Ϊ����  
	IIC_SDA=1;delay_us(1);   
	IIC_SCL=1;delay_us(1);	
  
	while(READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 1;
		}
	}
	IIC_SCL=0;//ʱ�����0 	   
	return 0;  
} 

//����ACKӦ��
void IIC_Ack(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=0;
	delay_us(4);
	IIC_SCL=1;
	delay_us(4);
	IIC_SCL=0;
}

//������ACKӦ��		    
void IIC_NAck(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=1;
	delay_us(4);
	IIC_SCL=1;
	delay_us(4);
	IIC_SCL=0;
}					 				     
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			
u8 test=0;
void IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
	  SDA_OUT(); 	    
    IIC_SCL=0;//����ʱ�ӿ�ʼ���ݴ���
	 
    for(t=0;t<8;t++)
    {             
			if((txd&0x80)>>7)
        IIC_SDA=1;
			else 
				IIC_SDA=0;
			
        txd<<=1; 	 
	    delay_us(5);
		IIC_SCL=1;
		delay_us(5); 
		IIC_SCL=0;	
		delay_us(5);
    }	 
} 	    



//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   

u8 IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	 SDA_IN();//SDA����Ϊ����
    for(i=0;i<8;i++ )
	{
        IIC_SCL=0; 
        delay_us(5);
		    IIC_SCL=1;
        receive<<=1;
		     
        if(READ_SDA)receive++;   
		   delay_us(5); 
    }					 
    if (!ack)
        IIC_NAck();//����nACK
    else
        IIC_Ack(); //����ACK   
    return receive;
}
//һ����ֲ
void IN_CHG(void)
{
	 GPIO_InitTypeDef  GPIO_InitStructure;
	 GPIO_InitStructure.Pin = GPIO_PIN_15;
	 GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
	 HAL_GPIO_Init(GPIOE,&GPIO_InitStructure);
}

void OUT_CHG(void)
{
	 GPIO_InitTypeDef  GPIO_InitStructure;
	 GPIO_InitStructure.Pin = GPIO_PIN_15;
	 GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	 HAL_GPIO_Init(GPIOE,&GPIO_InitStructure);
}






















