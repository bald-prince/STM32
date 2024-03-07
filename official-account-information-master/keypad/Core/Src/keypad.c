#include "keypad.h"
#include "key.h"

#define key_printf_debug

#ifdef key_printf_debug
#define key_debug_printf(format, args...) \
	do                                    \
	{                                     \
		printf(format, ##args);           \
	} while (0)
#else
#define key_debug_printf(format, args...) \
	do                                    \
	{                                     \
	} while (0)
#endif

Keypad_para keypad_status;

const uint8_t KeyTrueLable[] =
	{
		0xEE, 0xDE, 0xBE, 0x7E,
		0xED, 0xDD, 0xBD, 0x7D,
		0xEB, 0xDB, 0xBB, 0x7B,
		0xE7, 0xD7, 0xB7, 0x77};

const uint8_t KeyUserDefined[] =
	{
		1, 2, 3, 12,
		4, 5, 6, 13,
		7, 8, 9, 14,
		10, 0, 11, 15};

///===============================================================
///	行输入
///===============================================================
void KeyPad_SetROW_IN(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	__HAL_RCC_GPIOF_CLK_ENABLE();
	//ROW0-ROW3设置成上拉输入
	GPIO_InitStruct.Pin = Key_ROW1_Pin | Key_ROW2_Pin | Key_ROW3_Pin | Key_ROW4_Pin; //KEY0-KEY3
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);
}
///===============================================================
///	行输出
///===============================================================
void KeyPad_SetROW_Out(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	__HAL_RCC_GPIOF_CLK_ENABLE();

	/*Configure GPIO pins : PFPin PFPin PFPin PFPin */
	GPIO_InitStruct.Pin = Key_ROW1_Pin | Key_ROW2_Pin | Key_ROW3_Pin | Key_ROW4_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);
	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOF, Key_ROW1_Pin | Key_ROW2_Pin | Key_ROW3_Pin | Key_ROW4_Pin, GPIO_PIN_RESET);
}

///===============================================================
///列输入
///===============================================================
void KeyPad_SetCol_IN(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	__HAL_RCC_GPIOG_CLK_ENABLE();

	//C0-3设置成上拉输入
	/*Configure GPIO pins : PCPin PCPin PCPin PCPin */
	GPIO_InitStruct.Pin = Key_COL1_Pin | Key_COL2_Pin | Key_COL3_Pin | Key_COL4_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);
}
///===============================================================
///列输出
///===============================================================
void KeyPad_SetCol_Out(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	__HAL_RCC_GPIOC_CLK_ENABLE();

	GPIO_InitStruct.Pin = Key_COL1_Pin | Key_COL2_Pin | Key_COL3_Pin | Key_COL4_Pin; //KEY0-KEY3
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

	HAL_GPIO_WritePin(GPIOG, Key_COL1_Pin | Key_COL2_Pin | Key_COL3_Pin | Key_COL4_Pin, GPIO_PIN_RESET);
}

///===============================================================
//按键扫描程序
//先C低读R状态，再R低读C状态，判断是那个按键按下
//
///===============================================================

uint8_t KeyPad_KEY_Scan(void)
{
	uint8_t keycode, keycode_temp;

	//C低读ROW
	KeyPad_SetCol_Out();
	keycode = KEYPADROW & 0x0f;
	//R低读COL
	KeyPad_SetROW_Out();
	KeyPad_SetCol_IN();

	keycode_temp = KEYPADCOL;

	keycode |= (keycode_temp << 4 & 0xf0);

	KeyPad_SetROW_IN();

	return keycode;
}

///===============================================================
//键值转换用户定义键值
///===============================================================
uint8_t KeyPad_KeyTrueLableGet(uint8_t key)
{
	uint8_t i = 0, R_key_user = 0xE0;

	for (i = 0; i < D_Key_Count; i++)
	{
		if (key == KeyTrueLable[i])
		{
			R_key_user = KeyUserDefined[i];
		}
	}
	return R_key_user;
}

///===============================================================
//得到键值
///===============================================================
uint8_t KeyPad_GetKeyValue(void)
{
	uint8_t KeyValue = 0;

	//	HAL_Delay(10);
	if (KeyPad_KEY_Scan() == D_NO_KEY_CODE) //没有按键/按键抬起
	{

		if (keypad_status.KeyPress == 1)
		{
			keypad_status.KeyValue_New = 0;
			keypad_status.KeyValue_Old = 0;
			keypad_status.KeyPress = 0;
		}
		return 0xF0;
	}
	HAL_Delay(10);

	KeyValue = KeyPad_KEY_Scan();
	if (KeyValue == D_NO_KEY_CODE)
	{
		if (keypad_status.KeyPress == 1)
		{
			//解决按键“0” 的问题
			keypad_status.KeyValue_New = 0xF2;
			keypad_status.KeyValue_Old = 0xF2;
			keypad_status.KeyPress = 0;
		}
		return 0xF0;
	}
	KeyValue = KeyPad_KeyTrueLableGet(KeyValue);
	keypad_status.KeyPress = 1;
	//判断是否是第一次按下
	keypad_status.KeyValue_New = KeyValue;
	if (keypad_status.KeyValue_New == keypad_status.KeyValue_Old)
	{
		return 0xF1;
	}
	keypad_status.KeyValue_Old = KeyValue;
	printf("\r\nkeycode is:%0x\r\n", KeyValue);

	return KeyValue;
}

/*----------------------------------------------------------------
定时器中断中调用此函数
----------------------------------------------------------------*/
uint8_t longkeytime = 0;
uint8_t Keypad_Scan_TimCallBack(void)
{
	uint8_t key = 0;
	key_status Press_status;

	switch (Press_status)
	{
	case key_no_Press:
		if (KeyPad_GetKeyValue()) //有按键按下
		{
			Press_status++;
			key = 0;
		}
		else
		{
			Press_status = key_no_Press;
			key = 0;
		}
		break;
	case key_Press:
		if (KeyPad_GetKeyValue()) //有按键按下,第一次消抖，仍有按键按下，认为按键有效
		{
			Press_status++;
			key = KeyPad_GetKeyValue();
		}
		break;
	case key_PressCheck:
		if (KeyPad_GetKeyValue()) //仍有按键按下,可做长按键判断，目前仍按照短按键键值处理，可修改
		{
			//Press_status++;
			longkeytime++;
			if (longkeytime > 200)
			{
				key = 25;
			}
			//key = KeyPad_GetKeyValue();
		}
		else
			Press_status++;

		break;
	case key_Release:
		if (KeyPad_GetKeyValue()) //有按键按下，仍有按键按下,可做长按键判断，目前仍按照短按键键值处理，可修改
		{
			Press_status = key_no_Press;
			key = 0;
		}
		break;
	default:
		Press_status = key_no_Press;
		key = 0;
	}
	if (key != 0)
	{
		key_debug_printf("key value is %d\r\n", key);
	}
	return key;
}
