#include "key.h"
#include "usart.h"
#include "lcd.h"

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

uint8_t key_value = 0;

/*----------------------------------------------------------------
����IO״̬��ѯ����
----------------------------------------------------------------*/
uint8_t KEY_Scan(void)
{
    if ((KEY0 == 0 || KEY1 == 0 || KEY2 == 0 || WK_UP == 1))
    {
        if (KEY0 == 0)
            return KEY0_PRES;
        else if (KEY1 == 0)
            return KEY1_PRES;
        else if (KEY2 == 0)
            return KEY2_PRES;
        else if (WK_UP == 1)
            return WKUP_PRES;
    }
    else if (KEY0 == 1 && KEY1 == 1 && KEY2 == 1 && WK_UP == 0)
    return 0; //�ް�������
}
/*----------------------------------------------------------------
��ʱ���ж��е��ô˺���
----------------------------------------------------------------*/
uint8_t Key_Scan_TimCallBack(void)
{
    static key_status Press_status;
    uint8_t key = 0;
    switch (Press_status)
    {
    case key_no_Press:
        if (KEY_Scan()) //�а�������
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
        if (KEY_Scan()) //�а�������,��һ�����������а������£���Ϊ������Ч
        {
            Press_status++;
            key = KEY_Scan();
        }
        break;
    case key_PressCheck:
        if (KEY_Scan()) //�а������£����а�������,�����������жϣ�Ŀǰ�԰��ն̰�����ֵ�������޸�
        {
            Press_status++;
            key = KEY_Scan();
        }
        break;
    case key_Release:
        if (KEY_Scan())  //�а������£����а�������,�����������жϣ�Ŀǰ�԰��ն̰�����ֵ�������޸�
        {
            Press_status = key_no_Press;
            key = 0;
        }
        break;
    default:
        Press_status = key_no_Press;
        key = 0;
    }
    if (key)
    {
        key_debug_printf("key value is %d\r\n", key);
    }
    return key;
}
