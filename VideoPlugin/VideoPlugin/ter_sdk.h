/*
 * =====================================================================================
 *       Copyright (C), 2010, islab@ZJU
 *
 *       FileName:  ter_sdk.h
 *
 *		   Author:  zsz (Islab)
 *			 Date:	2010年10月6日 14时56分09秒 CST
 *        Version:  1.0
 *
 *    Description:  
 *		   Others:
 *  Function List:
 *			1.-------
 *        History: 
 *			<Author>  <Time>  <Version>  <Description>
 *
 * =====================================================================================
 */

#ifndef  TER_SDK_INC
#define  TER_SDK_INC

#ifdef __cplusplus
extern "C"{
#endif


#define Linux 1
#define Windows 2

//#define PLATFORM Linux
#define PLATFORM Windows

/*头文件包含不同*/
#if (PLATFORM == Linux)
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include "ter_sdk_types.h"
	#include "ter_sdk_struct.h"
	#include "term_error_define.h"
#elif (PLATFORM == Windows)
	#include <winsock2.h>
	#include <stdio.h>
	#include <windows.h>
	#include "ter_sdk_types.h"
	#include "ter_sdk_struct.h"
	#include "term_error_define.h"
#endif

/*windows 编译成动态链接库*/
#if (PLATFORM == Linux)
	#define SDKAPI
#elif (PLATFORM == Windows)
	#define SDKAPI __declspec(dllexport)
#endif

/*如果是Windows，用户注测超时回调的类型*/
#if (PLATFORM == Windows)
	typedef void (*callback_fun_t)(void);
#endif

/*src、dstid的字节数*/
#define ID_BYTE_NUM 8
/*linux平台返回给用户的数据结构*/
struct ret_data_st
{
	unsigned short magic_num;
	char src_id[ID_BYTE_NUM];
	char dst_id[ID_BYTE_NUM];
};

/*函数参数传入标志*/
#define _IN_
/*函数参数为传出*/
#define _OUT_


/*SDK接口*/
/* 
 * =========================================================================
 * 	   Function: TER_SDK_Login() 
 *  Description: Login 接口
 *		  Calls:
 *	  Called By: 
 *	  	  Input: servip - 终端ip地址
 *	  	  		 servport - 终端端口号
 *	  	  		 username - 用户登入用户名
 *	  	  		 password - 用户登入密码
 *	     Output: outdata -  如果是linux平台调用sdk需传入该指针，
 *							sdk将相应数据返回给调用者,windows平台可以传NULL
 *	     Return: sdk的错误码，参考term_error_define.h
 *       Others:
 * =========================================================================
 */
SDKAPI ret_info TER_SDK_Login(_IN_ char *servip, _IN_ unsigned short servport, _IN_ char *username, _IN_ char *password, _OUT_ struct ret_data_st *outdata);

#if (PLATFORM == Linux)
/* 
 * =========================================================================
 *     Function: TER_SDK_Communicate_Init
 *  Description: Linux平台有此api函数，在每次调用sdk接口获取参数、设置参数
 *				 或是发送命令时需调用此函数进行sdk初始化，初始化时需传入的参数如下
 *        Calls:
 *    Called By:
 *        Input: in_data - 传入的数据，也就是login成功后sdk返回给调用者的
 *        		 sequence - 消息的序列号，需要不停的累加
 *        		 servip - 终端的ip
 *        		 servport - 终端接受消息的port
 *       Output:
 *       Return: sdk的错误码，参考term_error_define.h
 *       Others:
 * =========================================================================
 */
SDKAPI ret_info TER_SDK_Communicate_Init(_IN_ struct ret_data_st *indata, _IN_ unsigned short sequence,_IN_ char *servip, _IN_ unsigned short servport);

/* 
 * =========================================================================
 * 	   Function:  TER_SDK_Keepalive_Send()
 *  Description:  Linux平台下保活的接口，保活定时由调用者做，sdk提供发送保活消息的接口
 *		  Calls:
 *	  Called By:
 *	  	  Input: indata - login成功后返回给web的数据
 *	  	  		 servip - 终端ip
 *	  	  		 servport - 终端port
 *	  	  		 sequence - 消息序列号，需要累加
 *	     Output:
 *	     Return: sdk的错误码，参考term_error_define.h
 *       Others:
 * =========================================================================
 */
SDKAPI ret_info TER_SDK_Keepalive_Send(_IN_ struct ret_data_st *indata, _IN_ char *servip, _IN_ unsigned short servport, unsigned short sequence);
#endif

#if (PLATFORM == Windows)
/* 
 * =========================================================================
 * 	   Function:  TER_SDK_Register_Callback()
 *  Description:  Windows平台下注册保活失败的回调函数的sdk接口，当保活失败时会
 *				  sdk会自动调用此函数
 *		  Calls:
 *	  Called By:
 *	  	  Input:  fun - 回调函数的指针，函数类型为void (*callback_fun_t)(void)
 *	     Output:
 *	     Return:  
 *       Others:
 * =========================================================================
 */
SDKAPI void TER_SDK_Register_Callback(_IN_ callback_fun_t fun);


/* 
 * =========================================================================
 * 	   Function:  TER_SDK_Timeout_Cleanup()
 *  Description:  保活失败后调用此函数进行资源释放
 *		  Calls:
 *	  Called By:
 *	  	  Input:  无
 *	     Output:  无
 *	     Return:  无
 *       Others:
 * =========================================================================
 */

SDKAPI void TER_SDK_Timeout_Cleanup();

#endif


/* 
 * =========================================================================
 * 	   Function:  TER_SDK_Logout()
 *  Description:  用户Logout 接口
 *		  Calls:
 *	  Called By:
 *	  	  Input: 无
 *	     Output: 无
 *	     Return: sdk的错误码，参考term_error_define.h
 *       Others:
 * =========================================================================
 */
SDKAPI ret_info TER_SDK_Logout();


/* 
 * =========================================================================
 * 	   Function:  
 *  Description: 获取参数接口
 *		  Calls: 
 *	  Called By:
 *	  	  Input: param_index - 参数表的索引号
 *	  	  		 buflen - 参数缓存区长度	  		
 *	  	  		 item_main_index - 参数索引号或通道号，获取全部参数时填写-0xff
 *				 item_sub_index - 该通道下的主辅流索引或是巡航路线索引，无效时填0，获取全部参数时全部填写0xff
 *	     Output: buf – 获取的参数的缓存区指针
 *				 getlen - 接受到的参数长度
 *	     Return: sdk的错误码，参考term_error_define.h
 *       Others:
 * =========================================================================
 */

SDKAPI ret_info TER_SDK_GetConfig(_IN_ int param_index, _OUT_ void *buf, _IN_ int buflen, _OUT_ int *getlen, _IN_ unsigned char item_main_index, _IN_ unsigned char item_sub_index);

/* 
 * =========================================================================
 * 	   Function:  
 *  Description:  设置参数接口
 *		  Calls:
 *	  Called By:
 *	  	  Input: param_index - 参数表的索引号
 *	  	  		 buf – 用户传进来的设置参数的缓存区
 *	  	  		 setlen - 设置参数的长度
 *	  	  		 item_main_index - 参数设置的主索引号比如通道号,设置全部参数时填写0xff
 *				 item_sub_index - 该通道下的主辅流索引或是巡航路线索引，无效时填0，设置全部参数时全部填写0xff
 *	     Output:
 *	     Return: sdk的错误码，参考term_error_define.h
 *       Others:
 * =========================================================================
 */
SDKAPI ret_info TER_SDK_SetConfig(_IN_ int param_index, _IN_ void *buf, _IN_ int setlen, _IN_ unsigned char item_main_index, _IN_ unsigned char item_sub_index);

/* 
* =========================================================================
* 	   Function: TER_SDK_SetTime()
*  Description: 设置终端时间函数  
*		  Calls:
*	  Called By:
*	  	  Input: year  -  年
*				 month -  月
*				 day   -  日
*				 hour  -  时
*				 min   -  分
*				 sec   -  秒
*	     Output:
*	     Return: sdk的错误码，参考term_error_define.h
*       Others:
* =========================================================================
 */
SDKAPI ret_info TER_SDK_SetTime(unsigned short year, unsigned char month, unsigned char day, unsigned char hour, unsigned char min, unsigned char sec );

/* 
* =========================================================================
* 	   Function: TER_SDK_GetTime()
*  Description: 设置终端时间函数  
*		  Calls:
*	  Called By:
*	  	  Input: year  -  年，输出参数
*				 month -  月，输出参数
*				 day   -  日，输出参数
*				 hour  -  时，输出参数
*				 min   -  分，输出参数
*				 sec   -  秒，输出参数
*	     Output:
*	     Return: sdk的错误码，参考term_error_define.h
*       Others:
* =========================================================================
 */
SDKAPI ret_info TER_SDK_GetTime(unsigned short *year, unsigned char *month, unsigned char *day, unsigned char *hour, unsigned char *min, unsigned char *sec );

/* 
 * =========================================================================
 * 	   Function: TER_SDK_Reboot()
 *  Description: 系统重启命令接口函数
 *		  Calls:
 *	  Called By:
 *	  	  Input: 无
 *	     Output: 无
 *	     Return: sdk的错误码，参考term_error_define.h
 *       Others:
 * =========================================================================
 */
SDKAPI ret_info TER_SDK_Reboot();

/* 
* =========================================================================
*     Function: TER_SDK_ReDefaultConf()
*  Description: 恢复默认配置函数接口
*        Calls:
*    Called By:
*        Input: 无
*       Output: 无
*       Return: sdk的错误码，参考term_error_define.h
*       Others:
* =========================================================================
*/
SDKAPI ret_info TER_SDK_ReDefaultConf();

/* 
 * =========================================================================
 * 	   Function:  TER_SDK_LogExport()
 *  Description:  日志导出函数
 *		  Calls:
 *	  Called By:
 *	  	  Input:  ip - 日志导出服务器的ip
 *	  	  		  username - user_name, required for ftp
 *	  	  		  password - passwd, required for ftp
 *	     Output:
 *	     Return:
 *       Others:
 * =========================================================================
 */
SDKAPI ret_info TER_SDK_LogExport(char *ip, char *username, char *password);

/* 
 * =========================================================================
 * 	   Function:  
 *  Description: 启动EC实况单播接口函数
 *		  Calls:
 *	  Called By:
 *	  	  Input: channel - 实况视频的输入通道
 *	  	  		 main_sub_flag - 主辅流 0 - 主流 1 - 辅流
 *	  	  		 trans_mode - 传输方式 0 - udp 1 - tcp
 *	  	  		 streaming_type - 码流类型 0 - RTP 1 - TS 2 - PS 3 - ES
 *	  	  		 dst_ip - 目的的ip指针比如："192.168.0.1"
 *	  	  		 dst_port - 目的的port
 *	  	  		 remain_flag - logout实况不停止的标志 
 *	  	  		 			   0 - logout后实况停止
 *	  	  		 			   1 - logout后实况不停止,
 *	  	  		 			   并且终端重启后会恢复该路实况
 *	     Output:
 *	     Return: sdk的错误码，参考term_error_define.h
 *       Others:
 * =========================================================================
 */
SDKAPI ret_info TER_SDK_EC_LiveStreamStartCmd(_IN_ unsigned char channel, _IN_ unsigned char main_sub_flag, _IN_ unsigned char trans_mode, _IN_ unsigned char streaming_type, _IN_ char *dst_ip, _IN_ unsigned short dst_port, unsigned char remain_flag);


/* 
 * =========================================================================
 * 	   Function:  
 *  Description: 启动EC实况组播命令接口函数
 *		  Calls:
 *	  Called By:
 *	  	  Input: channel - 实况的输入通道
 *	  	  		 main_sub_flag - 主辅流
 *	  	  		 trans_mode - 传输方式 0 - udp 1 - tcp
 *	  	  		 streaming_type - 码流类型 0 - RTP 1 - TS 2 - PS 3 - ES
 *				 mc_ip - 组播ip指针比如："192.168.0.1"
 *	  	  		 mc_port - 组播port 
 *	  	  		 remain_flag - logout实况不停止的标志 
 *	  	  		 			   0 - logout后实况停止
 *	  	  		 			   1 - logout后实况不停止，
 *	  	  		 			   并且终端重启后会恢复该路实况
 *	     Output:
 *	     Return: sdk的错误码，参考term_error_define.h
 *       Others:
 * =========================================================================
 */

SDKAPI ret_info TER_SDK_EC_LiveStream_MultiCast(_IN_ unsigned char channel, _IN_ unsigned char main_sub_flag, _IN_ unsigned char trans_mode, _IN_ unsigned char streaming_type, _IN_ char *mc_ip, _IN_ unsigned short mc_port,_IN_  unsigned char remain_flag);

/* 
 * =========================================================================
 * 	   Function:  
 *  Description: 启动DC组播或单播实况接口函数
 *		  Calls:
 *	  Called By:
 *	  	  Input: channel - 实况的输入通道
 *	  	  		 trans_mode - 传输方式 0 - udp 1 - tcp
 *	  	  		 streaming_type - 码流类型 0 - RTP 1 - TS  2 - PS 3 - ES
 *	  	  		 mc_flag - 组播标志
 *	  	  		 mc_ip - 组播时目的的ip，单播时填NULL
 *	  	  		 mc_port - 组播时目的的port，单播时填0
 *	  	 Output:
 *	     Return: sdk的错误码，参考term_error_define.h
 *       Others:
 * =========================================================================
 */
SDKAPI ret_info TER_SDK_DC_LiveStreamStartCmd(_IN_ unsigned char channel, _IN_ unsigned char trans_mode, _IN_ unsigned char streaming_type, _IN_ unsigned char mc_flag, _IN_ char *mc_ip, _IN_ unsigned short mc_port);

/* 
 * =========================================================================
 * 	   Function:  
 *  Description: 结束(EC、DC)实况命令接口函数
 *		  Calls:
 *	  Called By:
 *	  	  Input: channel - 实况的输入通道
 *	  	  		 main_sub_flag - 主辅流
 *	  	  		 dst_ip - 单播或组播时目的的ip
 *	  	  		 dst_port - 单播或组播时目的的port
 *	     Output:
 *	     Return: sdk的错误码，参考term_error_define.h
 *       Others:
 * =========================================================================
 */
SDKAPI ret_info TER_SDK_LiveStreamStopCmd(_IN_ unsigned char channel, _IN_ unsigned char main_sub_flag, _IN_ char *dst_ip, _IN_ unsigned short dst_port);

/* 
* =========================================================================
* 	   Function: TER_SDK_SaveLiveQuery() 
*  Description: 查询保存的需要恢复的实况
*		  Calls:
*	  Called By:
*	  	  Input: channel - 查询保存的实况的通道号,
*					       如果是0xff表示查询所有通道的保存的实况
*	  	  		 buf - 查询结果填写的缓存区，为输出参数
*	  	  		 maxitem - 该buf可允许查询的最大个数
*	  	  		 retitem - 实际查询到的实况个数
*	     Output:
*	     Return: sdk的错误码，参考term_error_define.h
*       Others:
* =========================================================================
*/
SDKAPI ret_info TER_SDK_SaveLiveQuery(_IN_ unsigned char channel, _OUT_ struct live_recover *buf, _IN_ int maxitem, _OUT_ int *retitem);

/* 
 * =========================================================================
 * 	   Function:  
 *  Description: 云台控制命令接口函数 
 *		  Calls:
 *	  Called By:
 *	  	  Input: channel - 云台的通道号
 *				 command - 云台命令号
 *				 index - 命令的参数值,比如：速度设定命令是为设定的速度值，
 *						 调用预置点时为预置点索引号，调用巡航路线时为巡航路线索引号
 *	     Output:
 *	     Return: sdk的错误码，参考term_error_define.h
 *       Others:
 * =========================================================================
 */
SDKAPI ret_info TER_SDK_PtzCmd(_IN_ int channel, _IN_ int command, _IN_ int index );


/* 
* =========================================================================
* 	   Function:  
*  Description: 云台控制命令接口函数 
*		  Calls:
*	  Called By:
*	  	  Input: channel - 云台的通道号
*				 command - 云台命令号
*				 ptz_status_data - 保存查询回应得到的云台状态
*						
*	     Output:
*	     Return: sdk的错误码，参考term_error_define.h
*       Others:
* =========================================================================
 */
SDKAPI ret_info TER_SDK_PtzStatusQuery(_IN_ int channel, _IN_ int command, _OUT_  struct ptz_run_status *ptz_status_data);
/* 
* =========================================================================
* 	   Function:  
*  Description: s2ip模式的透明通道建立接口 
*		  Calls:
*	  Called By:
*	  	  Input: serial_index - 建立s2ip模式透明通道串口端的串口号
*				 dst_ip - 建立s2ip模式透明通道ip端的ip
*				 dst_port - 建立s2ip模式透明通道ip端的port
*	     Output:
*	     Return: sdk的错误码，参考term_error_define.h
*       Others:
* =========================================================================
*/
SDKAPI ret_info TER_SDK_Trans_Setup(_IN_ unsigned char serial_index, _IN_ char *dst_ip, _IN_ unsigned short dst_port);


/* 
* =========================================================================
* 	   Function:  
*  Description: s2ip模式的透明通道撤销接口 
*		  Calls:
*	  Called By:
*	  	  Input: serial_index - 建立s2ip模式透明通道串口端的串口号
*	     Output:
*	     Return: sdk的错误码，参考term_error_define.h
*       Others:
* =========================================================================
*/
SDKAPI ret_info TER_SDK_Trans_Clear(_IN_ unsigned char serial_index);

/* 
* =========================================================================
* 	   Function:  
*  Description: 保存建立的透明通道，保存的透明通道在系统重启后会自动恢复 
*		  Calls:
*	  Called By:
*	  	  Input: serial_index - 建立s2ip模式透明通道串口端的串口号
*				 dst_ip - 建立s2ip模式透明通道ip端的ip
*				 dst_port - 建立s2ip模式透明通道ip端的port
*	     Output:
*	     Return: sdk的错误码，参考term_error_define.h
*       Others:
* =========================================================================
*/
SDKAPI ret_info TER_SDK_Trans_Save(_IN_ unsigned char serial_index, _IN_ char *dst_ip, _IN_ unsigned short dst_port);

/* 
* =========================================================================
* 	   Function:  
*  Description:  删除保存的透明通道
*		  Calls:
*	  Called By:
*	  	  Input: serial_index - 建立s2ip模式透明通道串口端的串口号
*	     Output:
*	     Return: sdk的错误码，参考term_error_define.h
*       Others:
* =========================================================================
*/
SDKAPI ret_info TER_SDK_Trans_SaveCancel(_IN_ unsigned char serial_index);

/* 
* =========================================================================
* 	   Function:  
*  Description:  查询保存的透明通道接口
*		  Calls:
*	  Called By:
*	  	  Input: buf - 保存查询到的透明通道，该参数是输出参数
*				 maxitem - buf可以查询最大的透明通道个数，该参数是输入参数
*				 queryitem - 实际上查询到的透明通道的个数，该参数是输出参数
*	     Output:
*	     Return: sdk的错误码，参考term_error_define.h
*       Others:
* =========================================================================
*/
SDKAPI ret_info TER_SDK_Trans_Query(_OUT_ struct trans_save_query *buf, _IN_ int maxitem, _OUT_ int *queryitem);


/* 
 * =========================================================================
 *     Function:  
 *  Description: 对讲开始命令控制函数接口
 *        Calls:
 *    Called By:
 *        Input: stream_type - 对讲音频传输协议 0 - udp 1 - tcp
 *				 dst_ip - 对讲目的ip,比如：“192.168.0.1”
 *				 dst_port - 对讲目的port
 *       Output:
 *       Return: sdk的错误码，参考term_error_define.h
 *       Others:
 * =========================================================================
 */
SDKAPI ret_info TER_SDK_AudiocomStartCmd(_IN_ unsigned char stream_type, _IN_ char *dst_ip, _IN_ unsigned short dst_port );

/* 
 * =========================================================================
 *     Function:  
 *  Description: 对讲结束命令控制函数接口
 *        Calls:
 *    Called By:
 *        Input: dst_ip - 对讲目的ip,比如：“192.168.0.1”
 *				 dst_port - 对讲目的port
 *       Output:
 *       Return: sdk的错误码，参考term_error_define.h
 *       Others:
 * =========================================================================
 */
SDKAPI ret_info TER_SDK_AudiocomStopCmd(_IN_ char *dst_ip, _IN_ unsigned short dst_port );

/* 
 * =========================================================================
 *     Function:  
 *  Description: 设备物理信息查处接口
 *        Calls:
 *    Called By:
 *        Input: dev_info - 获取设备信息的指针
 *       Output: 
 *       Return: sdk的错误码，参考term_error_define.h
 *       Others:
 * =========================================================================
 */

SDKAPI ret_info TER_SDK_Get_devinfo(_OUT_ struct get_type_info *dev_info);

/* 
 * =========================================================================
 * 	   Function: 
 *  Description:  通过ftp升级内核镜像的函数接口  
 *		  Calls:
 *	  Called By:  
 *	  	  Input:  ftp_ip       -  镜像放置的ftp服务器的地址
 *	  	  		  user         -  登入ftp服务器的用户名
 *	  	  		  passwd       -  登入ftp服务器的密码
 *	  	  		  kerner_name  -  升级内核镜像的名称，如果此处填NULL则采用默认内核升级名称
 *	     Output:
 *	     Return:  sdk的错误码，参考term_error_define.h
 *       Others:  user passwd kernel_name 字符串长度最长为32
 * =========================================================================
 */
SDKAPI ret_info TER_SDK_Kernel_Update(_IN_ char *ftp_ip, _IN_ char * user, _IN_ char *passwd, _IN_ char *kernel_name);

/* 
 * =========================================================================
 * 	   Function: 
 *  Description:  通过ftp升级ramdisk镜像的函数接口  
 *		  Calls:
 *	  Called By:  
 *	  	  Input:  ftp_ip       -  镜像放置的ftp服务器的地址
 *	  	  		  user         -  登入ftp服务器的用户名
 *	  	  		  passwd       -  登入ftp服务器的密码
 *	  	  		  ramdisk_name  -  升级ramdisk镜像的名称，如果此处填NULL则采用默认ramdisk升级名称
 *	     Output:
 *	     Return:  sdk的错误码，参考term_error_define.h
 *       Others:  user passwd ramdisk_name 字符串长度最大为32
 * =========================================================================
 */
SDKAPI ret_info TER_SDK_Ramdisk_Update(_IN_ char *ftp_ip, _IN_ char * user, _IN_ char *passwd, _IN_ char *ramdisk_name);

/* 
 * =========================================================================
 * 	   Function: 
 *  Description:  通过ftp升级cpld镜像的函数接口  
 *		  Calls:
 *	  Called By:  
 *	  	  Input:  ftp_ip       -  镜像放置的ftp服务器的地址
 *	  	  		  user         -  登入ftp服务器的用户名
 *	  	  		  passwd       -  登入ftp服务器的密码
 *	  	  		  cpld_name    -  升级cpld镜像的名称，如果此处填NULL则采用默认cpld升级名称
 *	     Output:
 *	     Return:  sdk的错误码，参考term_error_define.h
 *       Others:  user passwd ramdisk_name 字符串长度最大为32
 * =========================================================================
 */
SDKAPI ret_info TER_SDK_Cpld_Update(_IN_ char *ftp_ip, _IN_ char * user, _IN_ char *passwd, _IN_ char *cpld_name);

/* 
 * =========================================================================
 * 	   Function: 
 *  Description:  通过ftp升级fpga镜像的函数接口  
 *		  Calls:
 *	  Called By:  
 *	  	  Input:  ftp_ip       -  镜像放置的ftp服务器的地址
 *	  	  		  user         -  登入ftp服务器的用户名
 *	  	  		  passwd       -  登入ftp服务器的密码
 *	  	  		  fpga_name    -  升级fpga镜像的名称，如果此处填NULL则采用默认fpga升级名称
 *	     Output:
 *	     Return:  sdk的错误码，参考term_error_define.h
 *       Others:  user passwd ramdisk_name 字符串长度最大为32
 * =========================================================================
 */
SDKAPI ret_info TER_SDK_Fpga_Vpdate(_IN_ char *ftp_ip, _IN_ char * user, _IN_ char *passwd, _IN_ char *fpga_name);

/* 
* =========================================================================
* 	   Function: 
*  Description:  通过ftp升级镜像的函数接口,可以选择升级的镜像类型  
*		  Calls:
*	  Called By:  
*	  	  Input:  ftp_ip       -  镜像放置的ftp服务器的地址
*	  	  		  user         -  登入ftp服务器的用户名
*	  	  		  passwd       -  登入ftp服务器的密码
*				  image_type   -  升级镜像的类型，如果要升级某镜像，与上相应的宏
*	  	  		  kernel_name  -  升级内核镜像的名称，填NULL则采用默认内核升级名称；
*								  如果不升级内核也填NULL
*	  	  		  ramdisk_name -  升级ramdisk镜像的名称，填NULL则采用默认ramdisk升级名称；
*								  如果不升级ramdisk也填NULL
*	  	  		  fpga_name    -  升级fpga镜像的名称，填NULL则采用默认fpga升级名称；
*								  如果不升级fpga也填NULL
*	  	  		  cpld_name	   -  升级cpld镜像的名称，填NULL则采用默认cpld升级名称；
*								  如果不升级cpld也填NULL
*				  result 	   -  该参数是输出参数，如果该函数返回成功，镜像的更新
*				  				  结果会填写在次结构体中
*				  				 
*	     Output:
*	     Return:  TERM_SDK_SUCCESS - 版本升级成功 
*	     		  TERM_UPDATE_IMAGE_FAILED - 至少有一个镜像更新失败，失败原因返回在result中
*	     		  others - 其他错误原因
*       Others:  user passwd 镜像名称的字符串长度最长为32
* =========================================================================
*/
SDKAPI ret_info TER_SDK_Image_Update(_IN_ char *ftp_ip, _IN_ char * user, _IN_ char *passwd, _IN_ char image_type, _IN_ char *kernel_name, _IN_ char *ramdisk_name, _IN_ char *fpga_name, _IN_ char *cpld_name, _OUT_ struct image_update_result *result);

/* 
* =========================================================================
* 	   Function: 
*   Description: 终端版本号查询
*		  Calls:
*	  Called By:  
*	  	  Input: version_info - 终端版本信息结构体，该参数是输出参数 		  
*	     Output:
*	     Return: sdk的错误码，参考term_error_define.h
*        Others:  
* =========================================================================
*/
SDKAPI ret_info TER_SDK_Version_Query(struct version_report_pl *version_info);

#ifdef __cplusplus
}
#endif
#endif   /* ----- #ifndef TER_SDK_INC  ----- */

