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
///	������
///===============================================================
void KeyPad_SetROW_IN(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	__HAL_RCC_GPIOF_CLK_ENABLE();
	//ROW0-ROW3���ó���������
	GPIO_InitStruct.Pin = Key_ROW1_Pin | Key_ROW2_Pin | Key_ROW3_Pin | Key_ROW4_Pin; //KEY0-KEY3
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);
}
///===============================================================
///	�����
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
///������
///===============================================================
void KeyPad_SetCol_IN(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	__HAL_RCC_GPIOG_CLK_ENABLE();

	//C0-3���ó���������
	/*Configure GPIO pins : PCPin PCPin PCPin PCPin */
	GPIO_InitStruct.Pin = Key_COL1_Pin | Key_COL2_Pin | Key_COL3_Pin | Key_COL4_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);
}
///===============================================================
///�����
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
//����ɨ�����
//��C�Ͷ�R״̬����R�Ͷ�C״̬���ж����Ǹ���������
//
///===============================================================

uint8_t KeyPad_KEY_Scan(void)
{
	uint8_t keycode, keycode_temp;

	//C�Ͷ�ROW
	KeyPad_SetCol_Out();
	keycode = KEYPADROW & 0x0f;
	//R�Ͷ�COL
	KeyPad_SetROW_Out();
	KeyPad_SetCol_IN();

	keycode_temp = KEYPADCOL;

	keycode |= (keycode_temp << 4 & 0xf0);

	KeyPad_SetROW_IN();

	return keycode;
}

///===============================================================
//��ֵת���û������ֵ
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
//�õ���ֵ
///===============================================================
uint8_t KeyPad_GetKeyValue(void)
{
	uint8_t KeyValue = 0;

	//	HAL_Delay(10);
	if (KeyPad_KEY_Scan() == D_NO_KEY_CODE) //û�а���/����̧��
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
			//���������0�� ������
			keypad_status.KeyValue_New = 0xF2;
			keypad_status.KeyValue_Old = 0xF2;
			keypad_status.KeyPress = 0;
		}
		return 0xF0;
	}
	KeyValue = KeyPad_KeyTrueLableGet(KeyValue);
	keypad_status.KeyPress = 1;
	//�ж��Ƿ��ǵ�һ�ΰ���
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
��ʱ���ж��е��ô˺���
----------------------------------------------------------------*/
uint8_t longkeytime = 0;
uint8_t Keypad_Scan_TimCallBack(void)
{
	uint8_t key = 0;
	key_status Press_status;

	switch (Press_status)
	{
	case key_no_Press:
		if (KeyPad_GetKeyValue()) //�а�������
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
		if (KeyPad_GetKeyValue()) //�а�������,��һ�����������а������£���Ϊ������Ч
		{
			Press_status++;
			key = KeyPad_GetKeyValue();
		}
		break;
	case key_PressCheck:
		if (KeyPad_GetKeyValue()) //���а�������,�����������жϣ�Ŀǰ�԰��ն̰�����ֵ�������޸�
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
		if (KeyPad_GetKeyValue()) //�а������£����а�������,�����������жϣ�Ŀǰ�԰��ն̰�����ֵ�������޸�
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
