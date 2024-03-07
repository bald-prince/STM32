#ifndef _DEBUG_H
#define _DEBUG_H
/************************************************************
  * @brief   debug.h
  * @author  jiejie
  * @github  https://github.com/jiejieTop
  * @date    2018-xx-xx
  * @version v1.0
  * @note    此文件用于打印日志信�?
  ***********************************************************/
/**
* @name Debug print 
* @{
*/
#define PRINT_DEBUG_ENABLE		0		/* 打印调试信息 */
#define PRINT_ERR_ENABLE			0	  /* 打印错�??信息 */
#define PRINT_INFO_ENABLE			1		/* 打印�?人信�? */



#if PRINT_DEBUG_ENABLE
#define PRINT_DEBUG(fmt, args...) 	 do{(printf("\n[DEBUG] >> "), printf(fmt, ##args));}while(0)     
#else
#define PRINT_DEBUG(fmt, args...)	     
#endif

#if PRINT_ERR_ENABLE
#define PRINT_ERR(fmt, args...) 	 do{(printf("\n[ERR] >> "), printf(fmt, ##args));}while(0)     
#else
#define PRINT_ERR(fmt, args...)	       
#endif

#if PRINT_INFO_ENABLE
#define PRINT_INFO(fmt, args...) 	 do{(printf("\n[BOOT] >>>>  "), printf(fmt, ##args));}while(0)     
#else
#define PRINT_INFO(fmt, args...)	       
#endif

/**@} */
	
//针�?�不同的编译器调用不同的stdint.h文件
#if defined(__ICCARM__) || defined(__CC_ARM) || defined(__GNUC__)
    #include <stdint.h>
#endif

/* �?言 Assert */
#define AssertCalled(char,int) 	printf("\nError:%s,%d\r\n",char,int)
#define ASSERT(x)   if((x)==0)  AssertCalled(__FILE__,__LINE__)
  
typedef enum 
{
	ASSERT_ERR = 0,								/* 错�?? */
	ASSERT_SUCCESS = !ASSERT_ERR	/* 正确 */
} Assert_ErrorStatus;

typedef enum 
{
	FALSE = 0,		/* �? */
	TRUE = !FALSE	/* �? */
}ResultStatus;



#endif /* __DEBUG_H */

