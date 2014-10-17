/*
 * =====================================================================================
 *       Copyright (C), 2010, islab@ZJU
 *
 *       FileName:  term_error_value.h
 *
 *		   Author:  rhk (ISLAB)
 *			 Date:	2010��11��10�� 21ʱ36��23�� CST
 *        Version:  1.0
 *
 *    Description:  �����ö��
 *		   Others:
 *  Function List:
 *			1.-------
 *        History: 
 *			<Author>  <Time>  <Version>  <Description>
 *
 * =====================================================================================
 */

#ifndef  TERM_ERROR_VALUE_INC
#define  TERM_ERROR_VALUE_INC

#ifdef __cplusplus
extern "C"{
#endif

typedef enum _term_error
{
	/* ��ģ�鶼���ܷ����Ĺ������� */
	TERM_SDK_SUCCESS					= 0x0000,	// û�д���
	TERM_COMMON_CHANNEL_ERROR			= 0x0001,	// ͨ���Ŵ���
	TERM_CONNON_ERROR_END,
	
	/* �������Ĵ��� */
	TERM_MGRCENTER_INVALID_MAGICNUM		= 0x0101,	// magicnum��ƥ��
	TERM_MGRCENTER_PASSWORD_ERROR		= 0x0102,	// �û����������
	TERM_MGRCENTER_USER_FULL			= 0x0103,	// �û�������
	TERM_MGRCENTER_NOENOUGHPRI			= 0x0104,	// Ȩ�޲���
	TERM_MGRCENTER_NOINIT				= 0x0105,	// û�г�ʼ��
	TERM_MGRCENTER_FAIL_CONNECT			= 0x0106,	// ���ӷ�����ʧ��
	TERM_MGRCENTER_SEND_ERROR			= 0x0107,	// �����������ʧ��
	TERM_MGRCENTER_RECV_ERROR			= 0x0108,	// ���������������ʧ��
	TERM_MGRCENTER_UPDATEVER_ERROR		= 0x0109,	// ���²����汾ʧ��
	TERM_MGRCENTER_SETGROUP_ERROR		= 0x010A,	// ������������groupʧ��
	TERM_MGRCENTER_SETITEM_ERROR		= 0x010B,	// ���õ�������itemʧ��
	TERM_MGRCENTER_GETGROUP_ERROR		= 0x010C,	// ��ȡ��������groupʧ��
	TERM_MGRCENTER_GETITEM_ERROR		= 0x010D,	// ��ȡ��������itemʧ��
	TERM_MGRCENTER_INVALID_GROUPID		= 0x010E,	// ��Ч��groupid	
	TERM_MGRCENTER_FORBID_LOGIN			= 0x010F,	// ��ֹ����
	TERM_MGRCENTER_ERROR_END,

	/* ʵ�����̴��� */
	TERM_LIVE_NOINIT					= 0x0201,	// û�г�ʼ��
	TERM_LIVE_CHAN_MAXLINK				= 0x0202,	// ����ʵ������ʱ,���Ͷ����ӵ���Ӧͨ���ĵ����ͻ������ﵽ���
	TERM_LIVE_TOTAL_MAXLINK				= 0x0203,	// ����ʵ������ʱ,���Ͷ����ӵ���ӦDSP�ĵ����ͻ������ﵽ���
	TERM_LIVE_NOCLIENT					= 0x0204,	// ����ʵ����ֹ����ʱ,���Ͷ˶�Ӧ�����û������в����ڶ�Ӧ�û�
	TERM_LIVE_RECV_STARTED				= 0x0205,	// ����ʵ������ʱ,���ն˶�Ӧͨ���Ѿ��ڽ�������
	TERM_LIVE_RECV_STOPED				= 0x0206,	// ����ʵ����ֹ����ʱ,���ն˶�Ӧͨ�����ڽ�������
	TERM_LIVE_MULTICAST_STARTED			= 0x0207,	// �鲥ʵ������ʱ,����ͨ���������Ѿ����鲥
	TERM_LIVE_MULTICAST_DISABLED		= 0x0208,	// �鲥ʵ������ʱ,��֧���鲥
	TERM_LIVE_MULTICAST_JOINFAILED		= 0x0209,	// �鲥ʵ������ʱ,�����鲥��ʧ��
	TERM_LIVE_MULTICAST_NOTEXIST		= 0x020A,	// �鲥ʵ����ֹ����ʱ,���Ͷ˶�Ӧ�û������в������鲥
	TERM_LIVE_CLIENT_EXISTED			= 0x020B,	// ����ʵ������ʱ,��Ӧ���û��Ѿ�����
	TERM_LIVE_MAIN_SUB_INVALID			= 0x020C,	// ʵ������ʱ,��������־���Ϸ�
	TERM_LIVE_TRANS_MODE_INVALID		= 0x020D,	// ʵ������ʱ,����ģʽ���Ϸ�
	TERM_LIVE_STREAMING_TYPE_INVALID	= 0x020E,	// ʵ������ʱ,������������Ͳ��Ϸ�
	TERM_LIVE_DST_IP_INVALID			= 0x020F,	// ʵ������ʱ,����Ŀ��IP���Ϸ�
	TERM_LIVE_RESOLUTION_INVALID		= 0x0210,	// ʵ������ʱ,�ֱ��ʲ��Ϸ�
	TERM_LIVE_FORMAT_INVALID			= 0x0211,	// ʵ������ʱ,��ʽ���Ϸ�
	TERM_LIVE_ERROR_END,
	
	/* �洢���̴��� */		
	TERM_RECORD_NOINIT					= 0x0301,	// �洢����δ��ʼ��
	TERM_RECORD_NOIPSAN					= 0x0302,	// û��IPSAN
	TERM_RECORD_IPSAN_FULL				= 0x0303,	// IPSAN��
	TERM_RECORD_IPSAN_OFFLINE			= 0x0304,	// IPSAN����
	TERM_RECORD_IPSAN_ERROR				= 0x0305,	// IPSAN����
	TERM_RECORD_LOCAL_FULL				= 0x0306,	// ���ش洢��
	TERM_RECORD_LOCAL_ERROR				= 0x0307,	// ���ش洢����
	TERM_RECORD_ALARM_STARTED			= 0x0308,	// ���յ��ֶ��洢����ʱ,���ڽ��и澯�洢
	TERM_RECORD_MANUAL_STARTED			= 0x0309,	// ���յ��ֶ��洢����ʱ,���ڽ����ֶ��洢
	TERM_RECORD_MANUAL_STOPPED			= 0x030A,	// ���յ��ֶ��洢��ֹ����ʱ,�ֶ��洢�Ѿ���ֹ
	TERM_RECORD_ERROR_END,
	
	/* �澯���̴��� */
	TERM_ALERT_NOINIT					= 0x0401,	// �澯����δ��ʼ��
	TERM_ALERT_ERROR_END,	

	/* PTZ��͸��ͨ�����̴��� */
	TERM_PTZ_NOINIT						= 0x0501,	// PTZ��͸��ͨ������δ��ʼ��
	TERM_PTZ_ALARM_STARTED				= 0x0502,	// ���յ��ֶ�PTZ����ʱ,���ڽ��и澯PTZ
	TERM_PTZ_LOCKED						= 0x0503,	// ���յ��ֶ�PTZ����ʱ,PTZ������
	TERM_PTZ_CRUISE_PATH_DISABLED		= 0x0504,	// ���յ��ֶ�PTZ����ʱ,Ѳ��·����ʹ��
	TERM_PTZ_TRANSCHANNEL_BUILED		= 0x0505,	// ���յ�����͸��ͨ������ʱ,͸��ͨ���Ѿ�����
	TERM_PTZ_CMD_NOT_EXIST              = 0X0506,   // ���յ���PTZ�������
	TERM_PTZ_CHANNEL_INVALID            = 0X0507,   // ���յ���ͨ���Ų���ȷ
	TERM_PTZ_PATH_INVALID				= 0X0508,   // ���յ���Ѳ��·�߲���ȷ
	TERM_PTZ_PRESET_INVALID				= 0X0509,   // ���õ�Ԥ�õ㲻��ȷ
	TERM_PTZ_NO_CRUISE_NOW				= 0X050A,   // û��Ѳ��·������
	TERM_PTZ_TRANSCHANNEL_NOT_EXIST		= 0X050B,   // ͸��ͨ������
	TERM_PTZ_TRANS_SERIAL_MODE_WRONG	= 0X050C,	// ����͸��ͨ���Ĵ���ģʽ����
	TERM_PTZ_TRANS_DEV_VALID_FLAG_ERROR = 0X050D,	// �豸��ʶ����,1��2
	TERM_PTZ_TRANS_CHANNEL_WRONG		= 0X050E,	// ͸��ͨ���Ŵ���0~3
	TERM_PTZ_SERIAL_WRONG				= 0X050F,	// PTZ����ģʽ����������
	TERM_PTZ_ERROR_END,
	
	/* �������ƽ��̴��� */
	TERM_PARAMCTRL_NOINIT				= 0x0601,	// �������ƽ���δ��ʼ��
	TERM_PARAMCTRL_ERROR_END,
	
	/* �Խ����̴��� */
	TERM_AUDIOCOMMR_NOINIT				= 0x0701,	// �Խ�����δ��ʼ��
	TERM_AUDIOCOMMR_STARTED				= 0x0702,	// �����Խ���ʼ����ʱ,�Խ�ͨ���Ѿ�����
	TERM_AUDIOCOMMR_UNSTART				= 0x0703,	// �����Խ�ֹͣ����ʱ,�Խ�ͨ����δ����
	TERM_AUDIOCOMMR_BROADCAST_STARTED	= 0x0704,	// �����㲥��ʼ����ʱ,�㲥ͨ���Ѿ�����
	TERM_AUDIOCOMMR_BROADCAST_UNSTART	= 0x0705,	// �����㲥ֹͣ����ʱ,�㲥ͨ����δ����
	TERM_AUDIOCOMMR_ERROR_END,
	
	/* ��־���̴��� */
	TERM_LOG_TFTP_PROCESS_ERROR         = 0x0800, 	// tftp�������д���
	TERM_LOG_TFTP_CONNECT_OVERTIME		= 0x0801,	// tftp���ӳ�ʱ
	TERM_LOG_ERROR_END,
	
	/* ���½��̴��� */
	TERM_VERUPDATE_NOINIT				= 0x0901,	// ���½���δ��ʼ��
	TERM_VERUPDATE_CONNECT_TIMEOUT		= 0x0902,	// ����FTP��ʱ
	TERM_VERUPDATE_IMAGE_NOT_EXIST		= 0x0903,	// ���񲻴���
	TERM_VERUPDATE_IMAGE_LEN_ZERO		= 0x0904,	// �����СΪ0
	TERM_VERUPDATE_IMAGE_TOO_LARGE		= 0x0905,	// ����̫��
	TERM_VERUPDATE_IMAGE_LEN_INVALID	= 0x0906,	// ���񳤶��������ĳ��Ȳ����
	TERM_VERUPDATE_IMAGE_CRC_FAILED		= 0x0907,	// ����CRCУ�����
	TERM_VERUPDATE_IMAGE_WRITE_FAILED	= 0x0908,	// ������д����
	TERM_VERUPDATE_IMAGE_LOGIN_FAILED   = 0x0909,   // FTP��½ʧ��
	TERM_VERUPDATE_UPDATING				= 0x0910,	// �Ѵ�������״̬
	TERM_VERUPDATE_ERROR_END,
	
	/* misc���̴��� */
	TERM_MISC_NOINIT					= 0x0A01,	// misc����δ��ʼ��
	TERM_MISC_IPMODE_INVALID			= 0x0A02,	// IP����ģʽ���Ϸ�
	TERM_MISC_NETIP_SET_FAILED			= 0x0A03,	// �����������ʧ��
	TERM_MISC_NETCARDMODE_SET_FAILED	= 0x0A04,	// ��������ģʽ����ʧ��
	TERM_MISC_NETCARDMTU_SET_FAILED		= 0x0A05,	// ����MTU����ʧ��
	TERM_MISC_SYSTIME_SET_FAILED		= 0x0A06,	// ϵͳʱ������ʧ��
	TERM_MISC_ERROR_END,
	
	/* �������� */
	TERM_THREAD_CREATE_FAILED			= 0x0B01,	// �����̴߳���ʧ��
	TERM_SOCKET_INIT_FAILED				= 0x0B02,	// �׽��ִ���ʧ��
	TERM_SEND_MESSAGE_FIALED			= 0x0B03,	// ������Ϣ���ն�ʧ��
	TERM_REPLY_OVER_TIME				= 0x0B04,	// ���糬ʱ
	TERM_SDK_RECVMEM_ERROR				= 0x0B05,	// ������Ϣ�Ŀռ�̫С
	TERM_SDK_KEEPALIVE_FAILED			= 0x0B06,	// ����ʧ��
	TERM_NULL_POINTER_ERROR				= 0x0B07,	// ��ָ��
	TERM_UPDATE_IMAGE_FAILED			= 0x0B08,	// ���¾���ʧ��
	TERM_UNKOWN_ERROR					= 0x0B09,
	TERM_ERROR_END,
}ret_info;

#ifdef __cplusplus
}
#endif
#endif   /* ----- #ifndef TERM_ERROR_VALUE_INC  ----- */

