#include "print_dig.h"
//全局变量
u8 code_1[]={0,0,0,0,0,0,0,0};
void Print_digtal(char str[])
{
	u8 *p = (u8*)malloc(sizeof(u8)*8);
	sprintf((char*)p,"%s",str);
	for(i=0;i<8;i++)
	{
		*p-=48;
		code_1[i] = *p;
		if(i!=7)
		p++;
	}
	free(p);
	HC595_Disp_Number(code_1);
}