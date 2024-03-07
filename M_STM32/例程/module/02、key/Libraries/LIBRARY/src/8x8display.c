#include "8x8display.h"
#include "code.h"

//功能：向MAX7219(U3)写入字节
//入口参数：DATA 
//出口参数：无
//说明：
void Write_Max7219_byte(u8 DATA)         
{
    u8 i;    
    Max7219_pinCS_L;
    M_Delay_us(50);    
	for(i=8;i>=1;i--)
	{     
		Max7219_pinCLK_L; //=0;
		//Max7219_pinDIN=DATA&0x80;
		if(DATA&0x80)	Max7219_pinDIN_H;
		else			Max7219_pinDIN_L;

		DATA=DATA<<1;
		M_Delay_us(50);
		Max7219_pinCLK_H; //=1;
	}                                 
}

//-------------------------------------------
//功能：向MAX7219写入数据
//入口参数：address、dat
//出口参数：无
//说明：
void Write_Max7219(u8 address,u8 dat)
{ 
     Max7219_pinCS_L; //=0;
     M_Delay_us(50);
     Write_Max7219_byte(address);           //写入地址，即数码管编号
     Write_Max7219_byte(dat);               //写入数据，即数码管显示数字 
     Max7219_pinCS_H; //=1;                        
}

//-------------------------------------------
//功能：初始化点阵屏
//入口参数：
//出口参数：
//说明：
void Init_MAX7219(void)
{
	M_GPIO_Init(Max7219_pinDIN, GPIO_Mode_Out_PP);
	M_GPIO_Init(Max7219_pinCS, GPIO_Mode_Out_PP);
	M_GPIO_Init(Max7219_pinCLK, GPIO_Mode_Out_PP);
	Write_Max7219(0x09, 0x00);       //译码方式：BCD码
	Write_Max7219(0x0a, 0x03);       //亮度 
	Write_Max7219(0x0b, 0x07);       //扫描界限；8个数码管显示
	Write_Max7219(0x0c, 0x01);       //掉电模式：0，普通模式：1
	Write_Max7219(0x0f, 0x00);       //显示测试：1；测试结束，正常显示：0
}

//-------------------------------------------
//功能：清空屏幕
//入口参数：
//出口参数：
//说明：
void Clear_Display(void)
{
	u8 i;
	for(i = 1; i < 9; i++)
		Write_Max7219(i, 0x00);
}

//-------------------------------------------
//功能：电机速度显示
//入口参数：左轮速度、右轮速度
//出口参数：无
//说明：
void Motor_Display(u16 Motor_L, u16 Motor_R)
{
  //限制数据，以防显示失真
	if(Motor_L > 999)		Motor_L = 999;
	if(Motor_R > 999)		Motor_R = 999;
  //显示
  Write_Max7219(1,0xff<<(8 - 8*(Motor_L+1)/1000));
  Write_Max7219(8,0xff<<(8 - 8*(Motor_R+1)/1000));
}

//-------------------------------------------
//功能：一串数字显示(显示到小数点后两位，整数部分最多显示五位，整数位数太多小数部分会失真)
//入口参数：显示数字
//出口参数：无
//说明：
void Number_Display(float number)
{
	u8 single_digit[10],start,i,move,cutout;
	float number_replace;

	single_digit[6] = 10;   //小数点位
	single_digit[9] = 12;   //清空最后一位

	//判断符号
	if(number < 0)  single_digit[0] = 11;
	else            single_digit[0] = 12;

	//小数点后两位读数
	number_replace = number*100;
	single_digit[7] = (u16)number_replace/10%10;
	single_digit[8] = (u16)number_replace%10;
	//整数部分读数
	single_digit[1] = (u16)number/10000%10;
	single_digit[2] = (u16)number/1000%10;
	single_digit[3] = (u16)number/100%10;
	single_digit[4] = (u16)number/10%10;
	single_digit[5] = (u16)number%10;

	//(除开符号位(即第0位))判断整数最高位有效位(即非0位)
	for(start = 1; single_digit[start] == 0; start++);

	//防止整数部分全为零的情况
	if(start >= 5)  start = 5;

	//符号位和整数有效最高位对接显示
	for(move = 0; move < 8; move++){
		for(i = 1; i < 9; i++){
			Write_Max7219(i, (disp1[single_digit[0]][i-1]<<move)|(disp1[single_digit[start]][i-1]>>(8-move)));
		}
		M_Delay_ms(50);
	}

	//检测小数部分有效位
	for(cutout = 8; single_digit[cutout] == 0; cutout--);
	//小数部分只有一个有效位情况，清空第二位
	if(cutout == 7)   single_digit[8] = 12;
	//无小数部分，清空小数点和小数位
	if(cutout == 6)   {single_digit[6] = 12;single_digit[7] = 12;}

	//完整显示整数部分和小数部分
	for(; start <= cutout; start++){
		for(move = 0; move < 8; move++){
			for(i = 1; i < 9; i++){
				Write_Max7219(i, (disp1[single_digit[start]][i-1]<<move)|(disp1[single_digit[start + 1]][i-1]>>(8-move)));
			}
			M_Delay_ms(50);
		}
	}
}
