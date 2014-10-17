/*
 * =====================================================================================
 *       Copyright (C), 2010, islab@ZJU
 *
 *       FileName:  ter_sdk.h
 *
 *		   Author:  zsz (Islab)
 *			 Date:	2010��10��6�� 14ʱ56��09�� CST
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

/*ͷ�ļ�������ͬ*/
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

/*windows ����ɶ�̬���ӿ�*/
#if (PLATFORM == Linux)
	#define SDKAPI
#elif (PLATFORM == Windows)
	#define SDKAPI __declspec(dllexport)
#endif

/*�����Windows���û�ע�ⳬʱ�ص�������*/
#if (PLATFORM == Windows)
	typedef void (*callback_fun_t)(void);
#endif

/*src��dstid���ֽ���*/
#define ID_BYTE_NUM 8
/*linuxƽ̨���ظ��û������ݽṹ*/
struct ret_data_st
{
	unsigned short magic_num;
	char src_id[ID_BYTE_NUM];
	char dst_id[ID_BYTE_NUM];
};

/*�������������־*/
#define _IN_
/*��������Ϊ����*/
#define _OUT_


/*SDK�ӿ�*/
/* 
 * =========================================================================
 * 	   Function: TER_SDK_Login() 
 *  Description: Login �ӿ�
 *		  Calls:
 *	  Called By: 
 *	  	  Input: servip - �ն�ip��ַ
 *	  	  		 servport - �ն˶˿ں�
 *	  	  		 username - �û������û���
 *	  	  		 password - �û���������
 *	     Output: outdata -  �����linuxƽ̨����sdk�贫���ָ�룬
 *							sdk����Ӧ���ݷ��ظ�������,windowsƽ̨���Դ�NULL
 *	     Return: sdk�Ĵ����룬�ο�term_error_define.h
 *       Others:
 * =========================================================================
 */
SDKAPI ret_info TER_SDK_Login(_IN_ char *servip, _IN_ unsigned short servport, _IN_ char *username, _IN_ char *password, _OUT_ struct ret_data_st *outdata);

#if (PLATFORM == Linux)
/* 
 * =========================================================================
 *     Function: TER_SDK_Communicate_Init
 *  Description: Linuxƽ̨�д�api��������ÿ�ε���sdk�ӿڻ�ȡ���������ò���
 *				 ���Ƿ�������ʱ����ô˺�������sdk��ʼ������ʼ��ʱ�贫��Ĳ�������
 *        Calls:
 *    Called By:
 *        Input: in_data - ��������ݣ�Ҳ����login�ɹ���sdk���ظ������ߵ�
 *        		 sequence - ��Ϣ�����кţ���Ҫ��ͣ���ۼ�
 *        		 servip - �ն˵�ip
 *        		 servport - �ն˽�����Ϣ��port
 *       Output:
 *       Return: sdk�Ĵ����룬�ο�term_error_define.h
 *       Others:
 * =========================================================================
 */
SDKAPI ret_info TER_SDK_Communicate_Init(_IN_ struct ret_data_st *indata, _IN_ unsigned short sequence,_IN_ char *servip, _IN_ unsigned short servport);

/* 
 * =========================================================================
 * 	   Function:  TER_SDK_Keepalive_Send()
 *  Description:  Linuxƽ̨�±���Ľӿڣ����ʱ�ɵ���������sdk�ṩ���ͱ�����Ϣ�Ľӿ�
 *		  Calls:
 *	  Called By:
 *	  	  Input: indata - login�ɹ��󷵻ظ�web������
 *	  	  		 servip - �ն�ip
 *	  	  		 servport - �ն�port
 *	  	  		 sequence - ��Ϣ���кţ���Ҫ�ۼ�
 *	     Output:
 *	     Return: sdk�Ĵ����룬�ο�term_error_define.h
 *       Others:
 * =========================================================================
 */
SDKAPI ret_info TER_SDK_Keepalive_Send(_IN_ struct ret_data_st *indata, _IN_ char *servip, _IN_ unsigned short servport, unsigned short sequence);
#endif

#if (PLATFORM == Windows)
/* 
 * =========================================================================
 * 	   Function:  TER_SDK_Register_Callback()
 *  Description:  Windowsƽ̨��ע�ᱣ��ʧ�ܵĻص�������sdk�ӿڣ�������ʧ��ʱ��
 *				  sdk���Զ����ô˺���
 *		  Calls:
 *	  Called By:
 *	  	  Input:  fun - �ص�������ָ�룬��������Ϊvoid (*callback_fun_t)(void)
 *	     Output:
 *	     Return:  
 *       Others:
 * =========================================================================
 */
SDKAPI void TER_SDK_Register_Callback(_IN_ callback_fun_t fun);


/* 
 * =========================================================================
 * 	   Function:  TER_SDK_Timeout_Cleanup()
 *  Description:  ����ʧ�ܺ���ô˺���������Դ�ͷ�
 *		  Calls:
 *	  Called By:
 *	  	  Input:  ��
 *	     Output:  ��
 *	     Return:  ��
 *       Others:
 * =========================================================================
 */

SDKAPI void TER_SDK_Timeout_Cleanup();

#endif


/* 
 * =========================================================================
 * 	   Function:  TER_SDK_Logout()
 *  Description:  �û�Logout �ӿ�
 *		  Calls:
 *	  Called By:
 *	  	  Input: ��
 *	     Output: ��
 *	     Return: sdk�Ĵ����룬�ο�term_error_define.h
 *       Others:
 * =========================================================================
 */
SDKAPI ret_info TER_SDK_Logout();


/* 
 * =========================================================================
 * 	   Function:  
 *  Description: ��ȡ�����ӿ�
 *		  Calls: 
 *	  Called By:
 *	  	  Input: param_index - �������������
 *	  	  		 buflen - ��������������	  		
 *	  	  		 item_main_index - ���������Ż�ͨ���ţ���ȡȫ������ʱ��д-0xff
 *				 item_sub_index - ��ͨ���µ���������������Ѳ��·����������Чʱ��0����ȡȫ������ʱȫ����д0xff
 *	     Output: buf �C ��ȡ�Ĳ����Ļ�����ָ��
 *				 getlen - ���ܵ��Ĳ�������
 *	     Return: sdk�Ĵ����룬�ο�term_error_define.h
 *       Others:
 * =========================================================================
 */

SDKAPI ret_info TER_SDK_GetConfig(_IN_ int param_index, _OUT_ void *buf, _IN_ int buflen, _OUT_ int *getlen, _IN_ unsigned char item_main_index, _IN_ unsigned char item_sub_index);

/* 
 * =========================================================================
 * 	   Function:  
 *  Description:  ���ò����ӿ�
 *		  Calls:
 *	  Called By:
 *	  	  Input: param_index - �������������
 *	  	  		 buf �C �û������������ò����Ļ�����
 *	  	  		 setlen - ���ò����ĳ���
 *	  	  		 item_main_index - �������õ��������ű���ͨ����,����ȫ������ʱ��д0xff
 *				 item_sub_index - ��ͨ���µ���������������Ѳ��·����������Чʱ��0������ȫ������ʱȫ����д0xff
 *	     Output:
 *	     Return: sdk�Ĵ����룬�ο�term_error_define.h
 *       Others:
 * =========================================================================
 */
SDKAPI ret_info TER_SDK_SetConfig(_IN_ int param_index, _IN_ void *buf, _IN_ int setlen, _IN_ unsigned char item_main_index, _IN_ unsigned char item_sub_index);

/* 
* =========================================================================
* 	   Function: TER_SDK_SetTime()
*  Description: �����ն�ʱ�亯��  
*		  Calls:
*	  Called By:
*	  	  Input: year  -  ��
*				 month -  ��
*				 day   -  ��
*				 hour  -  ʱ
*				 min   -  ��
*				 sec   -  ��
*	     Output:
*	     Return: sdk�Ĵ����룬�ο�term_error_define.h
*       Others:
* =========================================================================
 */
SDKAPI ret_info TER_SDK_SetTime(unsigned short year, unsigned char month, unsigned char day, unsigned char hour, unsigned char min, unsigned char sec );

/* 
* =========================================================================
* 	   Function: TER_SDK_GetTime()
*  Description: �����ն�ʱ�亯��  
*		  Calls:
*	  Called By:
*	  	  Input: year  -  �꣬�������
*				 month -  �£��������
*				 day   -  �գ��������
*				 hour  -  ʱ���������
*				 min   -  �֣��������
*				 sec   -  �룬�������
*	     Output:
*	     Return: sdk�Ĵ����룬�ο�term_error_define.h
*       Others:
* =========================================================================
 */
SDKAPI ret_info TER_SDK_GetTime(unsigned short *year, unsigned char *month, unsigned char *day, unsigned char *hour, unsigned char *min, unsigned char *sec );

/* 
 * =========================================================================
 * 	   Function: TER_SDK_Reboot()
 *  Description: ϵͳ��������ӿں���
 *		  Calls:
 *	  Called By:
 *	  	  Input: ��
 *	     Output: ��
 *	     Return: sdk�Ĵ����룬�ο�term_error_define.h
 *       Others:
 * =========================================================================
 */
SDKAPI ret_info TER_SDK_Reboot();

/* 
* =========================================================================
*     Function: TER_SDK_ReDefaultConf()
*  Description: �ָ�Ĭ�����ú����ӿ�
*        Calls:
*    Called By:
*        Input: ��
*       Output: ��
*       Return: sdk�Ĵ����룬�ο�term_error_define.h
*       Others:
* =========================================================================
*/
SDKAPI ret_info TER_SDK_ReDefaultConf();

/* 
 * =========================================================================
 * 	   Function:  TER_SDK_LogExport()
 *  Description:  ��־��������
 *		  Calls:
 *	  Called By:
 *	  	  Input:  ip - ��־������������ip
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
 *  Description: ����ECʵ�������ӿں���
 *		  Calls:
 *	  Called By:
 *	  	  Input: channel - ʵ����Ƶ������ͨ��
 *	  	  		 main_sub_flag - ������ 0 - ���� 1 - ����
 *	  	  		 trans_mode - ���䷽ʽ 0 - udp 1 - tcp
 *	  	  		 streaming_type - �������� 0 - RTP 1 - TS 2 - PS 3 - ES
 *	  	  		 dst_ip - Ŀ�ĵ�ipָ����磺"192.168.0.1"
 *	  	  		 dst_port - Ŀ�ĵ�port
 *	  	  		 remain_flag - logoutʵ����ֹͣ�ı�־ 
 *	  	  		 			   0 - logout��ʵ��ֹͣ
 *	  	  		 			   1 - logout��ʵ����ֹͣ,
 *	  	  		 			   �����ն��������ָ���·ʵ��
 *	     Output:
 *	     Return: sdk�Ĵ����룬�ο�term_error_define.h
 *       Others:
 * =========================================================================
 */
SDKAPI ret_info TER_SDK_EC_LiveStreamStartCmd(_IN_ unsigned char channel, _IN_ unsigned char main_sub_flag, _IN_ unsigned char trans_mode, _IN_ unsigned char streaming_type, _IN_ char *dst_ip, _IN_ unsigned short dst_port, unsigned char remain_flag);


/* 
 * =========================================================================
 * 	   Function:  
 *  Description: ����ECʵ���鲥����ӿں���
 *		  Calls:
 *	  Called By:
 *	  	  Input: channel - ʵ��������ͨ��
 *	  	  		 main_sub_flag - ������
 *	  	  		 trans_mode - ���䷽ʽ 0 - udp 1 - tcp
 *	  	  		 streaming_type - �������� 0 - RTP 1 - TS 2 - PS 3 - ES
 *				 mc_ip - �鲥ipָ����磺"192.168.0.1"
 *	  	  		 mc_port - �鲥port 
 *	  	  		 remain_flag - logoutʵ����ֹͣ�ı�־ 
 *	  	  		 			   0 - logout��ʵ��ֹͣ
 *	  	  		 			   1 - logout��ʵ����ֹͣ��
 *	  	  		 			   �����ն��������ָ���·ʵ��
 *	     Output:
 *	     Return: sdk�Ĵ����룬�ο�term_error_define.h
 *       Others:
 * =========================================================================
 */

SDKAPI ret_info TER_SDK_EC_LiveStream_MultiCast(_IN_ unsigned char channel, _IN_ unsigned char main_sub_flag, _IN_ unsigned char trans_mode, _IN_ unsigned char streaming_type, _IN_ char *mc_ip, _IN_ unsigned short mc_port,_IN_  unsigned char remain_flag);

/* 
 * =========================================================================
 * 	   Function:  
 *  Description: ����DC�鲥�򵥲�ʵ���ӿں���
 *		  Calls:
 *	  Called By:
 *	  	  Input: channel - ʵ��������ͨ��
 *	  	  		 trans_mode - ���䷽ʽ 0 - udp 1 - tcp
 *	  	  		 streaming_type - �������� 0 - RTP 1 - TS  2 - PS 3 - ES
 *	  	  		 mc_flag - �鲥��־
 *	  	  		 mc_ip - �鲥ʱĿ�ĵ�ip������ʱ��NULL
 *	  	  		 mc_port - �鲥ʱĿ�ĵ�port������ʱ��0
 *	  	 Output:
 *	     Return: sdk�Ĵ����룬�ο�term_error_define.h
 *       Others:
 * =========================================================================
 */
SDKAPI ret_info TER_SDK_DC_LiveStreamStartCmd(_IN_ unsigned char channel, _IN_ unsigned char trans_mode, _IN_ unsigned char streaming_type, _IN_ unsigned char mc_flag, _IN_ char *mc_ip, _IN_ unsigned short mc_port);

/* 
 * =========================================================================
 * 	   Function:  
 *  Description: ����(EC��DC)ʵ������ӿں���
 *		  Calls:
 *	  Called By:
 *	  	  Input: channel - ʵ��������ͨ��
 *	  	  		 main_sub_flag - ������
 *	  	  		 dst_ip - �������鲥ʱĿ�ĵ�ip
 *	  	  		 dst_port - �������鲥ʱĿ�ĵ�port
 *	     Output:
 *	     Return: sdk�Ĵ����룬�ο�term_error_define.h
 *       Others:
 * =========================================================================
 */
SDKAPI ret_info TER_SDK_LiveStreamStopCmd(_IN_ unsigned char channel, _IN_ unsigned char main_sub_flag, _IN_ char *dst_ip, _IN_ unsigned short dst_port);

/* 
* =========================================================================
* 	   Function: TER_SDK_SaveLiveQuery() 
*  Description: ��ѯ�������Ҫ�ָ���ʵ��
*		  Calls:
*	  Called By:
*	  	  Input: channel - ��ѯ�����ʵ����ͨ����,
*					       �����0xff��ʾ��ѯ����ͨ���ı����ʵ��
*	  	  		 buf - ��ѯ�����д�Ļ�������Ϊ�������
*	  	  		 maxitem - ��buf�������ѯ��������
*	  	  		 retitem - ʵ�ʲ�ѯ����ʵ������
*	     Output:
*	     Return: sdk�Ĵ����룬�ο�term_error_define.h
*       Others:
* =========================================================================
*/
SDKAPI ret_info TER_SDK_SaveLiveQuery(_IN_ unsigned char channel, _OUT_ struct live_recover *buf, _IN_ int maxitem, _OUT_ int *retitem);

/* 
 * =========================================================================
 * 	   Function:  
 *  Description: ��̨��������ӿں��� 
 *		  Calls:
 *	  Called By:
 *	  	  Input: channel - ��̨��ͨ����
 *				 command - ��̨�����
 *				 index - ����Ĳ���ֵ,���磺�ٶ��趨������Ϊ�趨���ٶ�ֵ��
 *						 ����Ԥ�õ�ʱΪԤ�õ������ţ�����Ѳ��·��ʱΪѲ��·��������
 *	     Output:
 *	     Return: sdk�Ĵ����룬�ο�term_error_define.h
 *       Others:
 * =========================================================================
 */
SDKAPI ret_info TER_SDK_PtzCmd(_IN_ int channel, _IN_ int command, _IN_ int index );


/* 
* =========================================================================
* 	   Function:  
*  Description: ��̨��������ӿں��� 
*		  Calls:
*	  Called By:
*	  	  Input: channel - ��̨��ͨ����
*				 command - ��̨�����
*				 ptz_status_data - �����ѯ��Ӧ�õ�����̨״̬
*						
*	     Output:
*	     Return: sdk�Ĵ����룬�ο�term_error_define.h
*       Others:
* =========================================================================
 */
SDKAPI ret_info TER_SDK_PtzStatusQuery(_IN_ int channel, _IN_ int command, _OUT_  struct ptz_run_status *ptz_status_data);
/* 
* =========================================================================
* 	   Function:  
*  Description: s2ipģʽ��͸��ͨ�������ӿ� 
*		  Calls:
*	  Called By:
*	  	  Input: serial_index - ����s2ipģʽ͸��ͨ�����ڶ˵Ĵ��ں�
*				 dst_ip - ����s2ipģʽ͸��ͨ��ip�˵�ip
*				 dst_port - ����s2ipģʽ͸��ͨ��ip�˵�port
*	     Output:
*	     Return: sdk�Ĵ����룬�ο�term_error_define.h
*       Others:
* =========================================================================
*/
SDKAPI ret_info TER_SDK_Trans_Setup(_IN_ unsigned char serial_index, _IN_ char *dst_ip, _IN_ unsigned short dst_port);


/* 
* =========================================================================
* 	   Function:  
*  Description: s2ipģʽ��͸��ͨ�������ӿ� 
*		  Calls:
*	  Called By:
*	  	  Input: serial_index - ����s2ipģʽ͸��ͨ�����ڶ˵Ĵ��ں�
*	     Output:
*	     Return: sdk�Ĵ����룬�ο�term_error_define.h
*       Others:
* =========================================================================
*/
SDKAPI ret_info TER_SDK_Trans_Clear(_IN_ unsigned char serial_index);

/* 
* =========================================================================
* 	   Function:  
*  Description: ���潨����͸��ͨ���������͸��ͨ����ϵͳ��������Զ��ָ� 
*		  Calls:
*	  Called By:
*	  	  Input: serial_index - ����s2ipģʽ͸��ͨ�����ڶ˵Ĵ��ں�
*				 dst_ip - ����s2ipģʽ͸��ͨ��ip�˵�ip
*				 dst_port - ����s2ipģʽ͸��ͨ��ip�˵�port
*	     Output:
*	     Return: sdk�Ĵ����룬�ο�term_error_define.h
*       Others:
* =========================================================================
*/
SDKAPI ret_info TER_SDK_Trans_Save(_IN_ unsigned char serial_index, _IN_ char *dst_ip, _IN_ unsigned short dst_port);

/* 
* =========================================================================
* 	   Function:  
*  Description:  ɾ�������͸��ͨ��
*		  Calls:
*	  Called By:
*	  	  Input: serial_index - ����s2ipģʽ͸��ͨ�����ڶ˵Ĵ��ں�
*	     Output:
*	     Return: sdk�Ĵ����룬�ο�term_error_define.h
*       Others:
* =========================================================================
*/
SDKAPI ret_info TER_SDK_Trans_SaveCancel(_IN_ unsigned char serial_index);

/* 
* =========================================================================
* 	   Function:  
*  Description:  ��ѯ�����͸��ͨ���ӿ�
*		  Calls:
*	  Called By:
*	  	  Input: buf - �����ѯ����͸��ͨ�����ò������������
*				 maxitem - buf���Բ�ѯ����͸��ͨ���������ò������������
*				 queryitem - ʵ���ϲ�ѯ����͸��ͨ���ĸ������ò������������
*	     Output:
*	     Return: sdk�Ĵ����룬�ο�term_error_define.h
*       Others:
* =========================================================================
*/
SDKAPI ret_info TER_SDK_Trans_Query(_OUT_ struct trans_save_query *buf, _IN_ int maxitem, _OUT_ int *queryitem);


/* 
 * =========================================================================
 *     Function:  
 *  Description: �Խ���ʼ������ƺ����ӿ�
 *        Calls:
 *    Called By:
 *        Input: stream_type - �Խ���Ƶ����Э�� 0 - udp 1 - tcp
 *				 dst_ip - �Խ�Ŀ��ip,���磺��192.168.0.1��
 *				 dst_port - �Խ�Ŀ��port
 *       Output:
 *       Return: sdk�Ĵ����룬�ο�term_error_define.h
 *       Others:
 * =========================================================================
 */
SDKAPI ret_info TER_SDK_AudiocomStartCmd(_IN_ unsigned char stream_type, _IN_ char *dst_ip, _IN_ unsigned short dst_port );

/* 
 * =========================================================================
 *     Function:  
 *  Description: �Խ�����������ƺ����ӿ�
 *        Calls:
 *    Called By:
 *        Input: dst_ip - �Խ�Ŀ��ip,���磺��192.168.0.1��
 *				 dst_port - �Խ�Ŀ��port
 *       Output:
 *       Return: sdk�Ĵ����룬�ο�term_error_define.h
 *       Others:
 * =========================================================================
 */
SDKAPI ret_info TER_SDK_AudiocomStopCmd(_IN_ char *dst_ip, _IN_ unsigned short dst_port );

/* 
 * =========================================================================
 *     Function:  
 *  Description: �豸������Ϣ�鴦�ӿ�
 *        Calls:
 *    Called By:
 *        Input: dev_info - ��ȡ�豸��Ϣ��ָ��
 *       Output: 
 *       Return: sdk�Ĵ����룬�ο�term_error_define.h
 *       Others:
 * =========================================================================
 */

SDKAPI ret_info TER_SDK_Get_devinfo(_OUT_ struct get_type_info *dev_info);

/* 
 * =========================================================================
 * 	   Function: 
 *  Description:  ͨ��ftp�����ں˾���ĺ����ӿ�  
 *		  Calls:
 *	  Called By:  
 *	  	  Input:  ftp_ip       -  ������õ�ftp�������ĵ�ַ
 *	  	  		  user         -  ����ftp���������û���
 *	  	  		  passwd       -  ����ftp������������
 *	  	  		  kerner_name  -  �����ں˾�������ƣ�����˴���NULL�����Ĭ���ں���������
 *	     Output:
 *	     Return:  sdk�Ĵ����룬�ο�term_error_define.h
 *       Others:  user passwd kernel_name �ַ��������Ϊ32
 * =========================================================================
 */
SDKAPI ret_info TER_SDK_Kernel_Update(_IN_ char *ftp_ip, _IN_ char * user, _IN_ char *passwd, _IN_ char *kernel_name);

/* 
 * =========================================================================
 * 	   Function: 
 *  Description:  ͨ��ftp����ramdisk����ĺ����ӿ�  
 *		  Calls:
 *	  Called By:  
 *	  	  Input:  ftp_ip       -  ������õ�ftp�������ĵ�ַ
 *	  	  		  user         -  ����ftp���������û���
 *	  	  		  passwd       -  ����ftp������������
 *	  	  		  ramdisk_name  -  ����ramdisk��������ƣ�����˴���NULL�����Ĭ��ramdisk��������
 *	     Output:
 *	     Return:  sdk�Ĵ����룬�ο�term_error_define.h
 *       Others:  user passwd ramdisk_name �ַ����������Ϊ32
 * =========================================================================
 */
SDKAPI ret_info TER_SDK_Ramdisk_Update(_IN_ char *ftp_ip, _IN_ char * user, _IN_ char *passwd, _IN_ char *ramdisk_name);

/* 
 * =========================================================================
 * 	   Function: 
 *  Description:  ͨ��ftp����cpld����ĺ����ӿ�  
 *		  Calls:
 *	  Called By:  
 *	  	  Input:  ftp_ip       -  ������õ�ftp�������ĵ�ַ
 *	  	  		  user         -  ����ftp���������û���
 *	  	  		  passwd       -  ����ftp������������
 *	  	  		  cpld_name    -  ����cpld��������ƣ�����˴���NULL�����Ĭ��cpld��������
 *	     Output:
 *	     Return:  sdk�Ĵ����룬�ο�term_error_define.h
 *       Others:  user passwd ramdisk_name �ַ����������Ϊ32
 * =========================================================================
 */
SDKAPI ret_info TER_SDK_Cpld_Update(_IN_ char *ftp_ip, _IN_ char * user, _IN_ char *passwd, _IN_ char *cpld_name);

/* 
 * =========================================================================
 * 	   Function: 
 *  Description:  ͨ��ftp����fpga����ĺ����ӿ�  
 *		  Calls:
 *	  Called By:  
 *	  	  Input:  ftp_ip       -  ������õ�ftp�������ĵ�ַ
 *	  	  		  user         -  ����ftp���������û���
 *	  	  		  passwd       -  ����ftp������������
 *	  	  		  fpga_name    -  ����fpga��������ƣ�����˴���NULL�����Ĭ��fpga��������
 *	     Output:
 *	     Return:  sdk�Ĵ����룬�ο�term_error_define.h
 *       Others:  user passwd ramdisk_name �ַ����������Ϊ32
 * =========================================================================
 */
SDKAPI ret_info TER_SDK_Fpga_Vpdate(_IN_ char *ftp_ip, _IN_ char * user, _IN_ char *passwd, _IN_ char *fpga_name);

/* 
* =========================================================================
* 	   Function: 
*  Description:  ͨ��ftp��������ĺ����ӿ�,����ѡ�������ľ�������  
*		  Calls:
*	  Called By:  
*	  	  Input:  ftp_ip       -  ������õ�ftp�������ĵ�ַ
*	  	  		  user         -  ����ftp���������û���
*	  	  		  passwd       -  ����ftp������������
*				  image_type   -  ������������ͣ����Ҫ����ĳ����������Ӧ�ĺ�
*	  	  		  kernel_name  -  �����ں˾�������ƣ���NULL�����Ĭ���ں��������ƣ�
*								  ����������ں�Ҳ��NULL
*	  	  		  ramdisk_name -  ����ramdisk��������ƣ���NULL�����Ĭ��ramdisk�������ƣ�
*								  ���������ramdiskҲ��NULL
*	  	  		  fpga_name    -  ����fpga��������ƣ���NULL�����Ĭ��fpga�������ƣ�
*								  ���������fpgaҲ��NULL
*	  	  		  cpld_name	   -  ����cpld��������ƣ���NULL�����Ĭ��cpld�������ƣ�
*								  ���������cpldҲ��NULL
*				  result 	   -  �ò������������������ú������سɹ�������ĸ���
*				  				  �������д�ڴνṹ����
*				  				 
*	     Output:
*	     Return:  TERM_SDK_SUCCESS - �汾�����ɹ� 
*	     		  TERM_UPDATE_IMAGE_FAILED - ������һ���������ʧ�ܣ�ʧ��ԭ�򷵻���result��
*	     		  others - ��������ԭ��
*       Others:  user passwd �������Ƶ��ַ��������Ϊ32
* =========================================================================
*/
SDKAPI ret_info TER_SDK_Image_Update(_IN_ char *ftp_ip, _IN_ char * user, _IN_ char *passwd, _IN_ char image_type, _IN_ char *kernel_name, _IN_ char *ramdisk_name, _IN_ char *fpga_name, _IN_ char *cpld_name, _OUT_ struct image_update_result *result);

/* 
* =========================================================================
* 	   Function: 
*   Description: �ն˰汾�Ų�ѯ
*		  Calls:
*	  Called By:  
*	  	  Input: version_info - �ն˰汾��Ϣ�ṹ�壬�ò������������ 		  
*	     Output:
*	     Return: sdk�Ĵ����룬�ο�term_error_define.h
*        Others:  
* =========================================================================
*/
SDKAPI ret_info TER_SDK_Version_Query(struct version_report_pl *version_info);

#ifdef __cplusplus
}
#endif
#endif   /* ----- #ifndef TER_SDK_INC  ----- */

