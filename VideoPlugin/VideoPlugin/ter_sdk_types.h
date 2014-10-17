/*
 * =====================================================================================
 *       Copyright (C), 2010, islab@ZJU
 *
 *       FileName:  types.h
 *
 *		   Author:  liuqw (Islab)
 *			 Date:	2010��08��06�� 14ʱ52��56�� CST
 *        Version:  1.0
 *
 *    Description:  �ն�ϵͳ�Ļ������Ͷ���
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

/*ʱ�������*/
typedef Uint64  Timestamp_t;

/*��ÿ���Ϊ24x2����Сʱ��ÿ��Сʱռ1bit�������ƻ�������ƻ�*/
typedef Uint8  Schedule_t[24*2/8];

/*8λ��λͼ����*/
typedef Uint8  Bitmap8_t;
typedef Uint8  BBitmap8_t;

typedef enum
{
	Ret_OK = 0,						//�ɹ�
	Ret_ERROR_UNKNOWN = -1,			//δ֪����
	Ret_ERROR_BADPARAM = -2,		//�Ƿ�����
	Ret_ERROR_NULLPTR= -3,			//��ָ��
	Ret_ERROR_OUTOFRANGE = -4,		//������Χ����
	Ret_ERROR_INVALID_HANDLE = -5,	//�Ƿ����
	Ret_ERROR_NORESOURCES = -6		//û����Դ
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

/*ʱ�������*/
typedef Uint64  Timestamp_t;


/*��������*/
typedef struct
{
    Uint16 year;
    Uint8  month;
    Uint8  day;
} Date_t;


/*ʱ������*/
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


/*��ÿ���Ϊ24x2����Сʱ��ÿ��Сʱռ1bit�������ƻ�������ƻ�*/
typedef Uint8  Schedule_t[24*2/8];


/*8λ��λͼ����*/
typedef Uint8  Bitmap8_t;
typedef Uint8  BBitmap8_t;

/*�澯�¼�����*/
typedef struct
{
	Uint8   alarm_type;
	Uint32  param1;
	Uint32  param2;
	Uint32  param3;
} alarm_event_t;


/*�澯��������*/
typedef struct
{
	Uint8   action_type;
	Uint32  param1;
	Uint32  param2;
	Uint32  param3;
} alarm_action_t;


typedef enum
{
	Ret_OK = 0,						//�ɹ�
	Ret_ERROR_UNKNOWN = -1,			//δ֪����
	Ret_ERROR_BADPARAM = -2,		//�Ƿ�����
	Ret_ERROR_NULLPTR= -3,			//��ָ��
	Ret_ERROR_OUTOFRANGE = -4,		//������Χ����
	Ret_ERROR_INVALID_HANDLE = -5,	//�Ƿ����
	Ret_ERROR_NORESOURCES = -6		//û����Դ
}ret_status;
#endif

#ifdef __cplusplus
}
#endif
#endif   /* ----- #ifndef TYPES_INC  ----- */

