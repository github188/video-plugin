/*
 * =====================================================================================
 *       Copyright (C), 2010, islab@ZJU
 *
 *       FileName:  types.h
 *
 *		   Author:  liuqw (Islab)
 *			 Date:	2010年08月06日 14时52分56秒 CST
 *        Version:  1.0
 *
 *    Description:  终端系统的基本类型定义
 *		   Others:
 *  Function List:
 *			1.-------
 *        History: 
 *			<Author>  <Time>  <Version>  <Description>
 *
 * =====================================================================================
 */

#ifndef  TYPES_INC
#define  TYPES_INC

#ifdef __cplusplus
extern "C"{
#endif


#if(PLATFORM == Windows)
#define FALSE 0
#define TRUE  1

typedef unsigned char           UCHAR;
typedef char             		CHAR;
typedef unsigned int            UINT;
typedef int              		INT;
typedef unsigned long           ULONG;
typedef long             		LONG;
typedef unsigned __int64        ULONGLONG;
typedef __int64					LONGLONG;

typedef unsigned char           Uint8;
typedef char             		Int8;
typedef unsigned short          Uint16;
typedef short            		Int16;
typedef unsigned int            Uint32;
typedef int              		Int32;
#ifdef IS_64BIT_OS
typedef unsigned long           Uint64;
typedef long             		Int64;
#else
typedef unsigned __int64		Uint64;
typedef __int64					Int64;
#endif
typedef float	                FLOAT;
typedef double                  DOUBLE;

typedef struct
{
	Uint16 year;
	Uint8  month;
	Uint8  day;
} Date_t;

/*时间戳类型*/
typedef Uint64  Timestamp_t;

/*将每天分为24x2个半小时，每半小时占1bit，用作计划和例外计划*/
typedef Uint8  Schedule_t[24*2/8];

/*8位的位图类型*/
typedef Uint8  Bitmap8_t;
typedef Uint8  BBitmap8_t;

typedef enum
{
	Ret_OK = 0,						//成功
	Ret_ERROR_UNKNOWN = -1,			//未知错误
	Ret_ERROR_BADPARAM = -2,		//非法参数
	Ret_ERROR_NULLPTR= -3,			//空指针
	Ret_ERROR_OUTOFRANGE = -4,		//超出范围限制
	Ret_ERROR_INVALID_HANDLE = -5,	//非法句柄
	Ret_ERROR_NORESOURCES = -6		//没有资源
}ret_status;

#elif(PLATFORM == Linux)
#define FALSE 0
#define TRUE  1

typedef unsigned char           BOOL;
typedef unsigned char           UCHAR;
typedef char             		CHAR;
typedef unsigned int            UINT;
typedef int              		INT;
typedef unsigned long           ULONG;
typedef long             		LONG;
typedef unsigned long long      ULONGLONG;
typedef long long        		LONGLONG;

typedef unsigned char           Uint8;
typedef char             		Int8;
typedef unsigned short          Uint16;
typedef short            		Int16;
typedef unsigned int            Uint32;
typedef int              		Int32;
#ifdef IS_64BIT_OS
typedef unsigned long           Uint64;
typedef long             		Int64;
#else
typedef unsigned long long      Uint64;
typedef long long        		Int64;
#endif
typedef float	                FLOAT;
typedef double                  DOUBLE;

/*时间戳类型*/
typedef Uint64  Timestamp_t;


/*日期类型*/
typedef struct
{
    Uint16 year;
    Uint8  month;
    Uint8  day;
} Date_t;


/*时间类型*/
typedef struct
{
    Uint16 year;
    Uint8  month;
    Uint8  day;
    Uint8  hour;
    Uint8  min;
    Uint8  sec;
    Uint16 msec;
} Time_t;


/*将每天分为24x2个半小时，每半小时占1bit，用作计划和例外计划*/
typedef Uint8  Schedule_t[24*2/8];


/*8位的位图类型*/
typedef Uint8  Bitmap8_t;
typedef Uint8  BBitmap8_t;

/*告警事件类型*/
typedef struct
{
	Uint8   alarm_type;
	Uint32  param1;
	Uint32  param2;
	Uint32  param3;
} alarm_event_t;


/*告警联动类型*/
typedef struct
{
	Uint8   action_type;
	Uint32  param1;
	Uint32  param2;
	Uint32  param3;
} alarm_action_t;


typedef enum
{
	Ret_OK = 0,						//成功
	Ret_ERROR_UNKNOWN = -1,			//未知错误
	Ret_ERROR_BADPARAM = -2,		//非法参数
	Ret_ERROR_NULLPTR= -3,			//空指针
	Ret_ERROR_OUTOFRANGE = -4,		//超出范围限制
	Ret_ERROR_INVALID_HANDLE = -5,	//非法句柄
	Ret_ERROR_NORESOURCES = -6		//没有资源
}ret_status;
#endif

#ifdef __cplusplus
}
#endif
#endif   /* ----- #ifndef TYPES_INC  ----- */

