/*
 * =====================================================================================
 *       Copyright (C), 2010, islab@ZJU
 *
 *       FileName:  ter_sdk_struct.h
 *
 *		   Author:  zsz (Islab)
 *			 Date:	2010��10��16�� 14ʱ56��09�� CST
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

#ifndef  TER_SDK_STRUCT_INC
#define  TER_SDK_STRUCT_INC

#ifdef __cplusplus
extern "C"{
#endif

#include "ter_sdk.h"
#include "term_error_define.h"

#define MAX_PACKET_LEN		(65536)

/*ͨ������*/
#define MAX_CHANNEL_NUM		(16)

/*�����������*/
#define MAX_NAME_LEN		(32)
#define MAX_DESC_LEN		(64)
#define IPADDR_LEN			(16)
#define MAX_LIST_LEN		(32)
#define IPSAN_PASSWD_LEN	(32)

/* ��������ĺ� */
#define KERNEL_UPDATE		(0x01)
#define RAMDISK_UPDATE		(0x02)
#define FPGA_UPDATE			(0x04)
#define CPLD_UPDATE			(0x08)

#define MAX_AREA_MASK                 (1024)
#define MAX_OSD_VALUE                 (64)
#define MAX_IQN_LEN   (128)

/*��ȡ�����ò������������*/
enum
{
	PARAM_DEFINE_BEGIN                    = 0x0000,
    SYSTEM_INFO_COFIG					  = 0x0001,
    EC_CONFIG_GROUP_ID					  = 0x0002,
    DECODER_CONFIG_ID					  = 0x0003,
    PARAM_TEMPE_ALARM_CONIFG              = 0x0004,
    PHYOUT_CHANNEL_CONFIG                 = 0x0005,
    AIN_CONFIG_GROUP_ID                   = 0x0006,
    AOUT_CONFIG_GROUP_ID                  = 0x0007,
    CAMERACFG_GROUP_ID                    = 0x0008,
    PTZCFG_GROUP_ID                       = 0x0009,
    AUDIOCOMMR_INPUT_GROUP_ID             = 0x000A,
    AUDIOCOMMR_OUTPUT_GROUP_ID            = 0x000B,
    TRANCFG_GROUP_ID                      = 0x000C,
    SERIALCFG_GROUP_ID                    = 0x000D,
    VIDEOCFG_GROUP_ID                     = 0x000E,
    PARAM_MOTION_DETEC_CONFIG             = 0x000F,
    PARAM_PRIVACY_MASK_CONFIG             = 0x0010,
    PARAM_OSD_TIME_CONFIG                 = 0x0011,
    PARAM_OSD_FIELD_CONFIG                = 0x0012,
    SEMA_INPUT_GROUP_ID                   = 0x0013,
    SEMA_OUTPUT_GROUP_ID                  = 0x0014,
    CRUISEPATH_GROUP_ID                   = 0x0015,
    PARAM_CRUISE_PLAN_CONFIG              = 0x0016,
    PARAM_CRUISE_EXT_PLAN_CONFIG          = 0x0017,
    PARAM_STORAGE_INFO_CONFIG             = 0x0018,
    PARAM_STORAGE_IPSAN_CONFIG            = 0x0019,
    PARAM_ALARM_STORAGE_CONFIG            = 0x001A,
    PARAM_STORAGE_PLAN_CONFIG             = 0x001B,
    PARAM_STORAGE_EXT_PLAN_CONFIG         = 0x001C,
    ALARM_LINKAGE_GROUP_ID                = 0x001D,
    LINKAGE_ACTION_GROUP_ID               = 0x001E,
    PARAM_ALARM_PLAN_CONFIG               = 0x001F,
    PARAM_ALARM_EXT_PLAN_CONFIG           = 0x0020,
	RESERVED             		 		  = 0x0021,
	LIVE_RECOVER_INFO					  = 0x0022,
	PARAM_IMAGE_LOOPBACK_CONFIG           = 0x0023,
	IPC_OPTICAL_CONFIG             		  = 0x0024,
	PARAM_ANALOG_EXTEND_CONFIG			  = 0x0025,
	PARAM_DIGITAL_IN_EXTEND_CONFIG	 	  = 0x0026,
	PARAM_DIGITAL_OUT_EXTENF_CONFIG		  = 0x0027,
    PARAM_GATE_FORBID_DEVICE_CONFIG	      = 0x0028,
	PARAM_EXTEND_SEMA_INPUT_CONFIG		  = 0x0029,
	PARAM_HIDE_DETECT_ALM_CONFIG		  = 0x002a,
	PARAM_SNAPSHOT_CONFIG                 = 0x002b,

	PARAM_DEFINE_END,

    /*TODO: add extral parameters here*/
	PARMA_DEVICE_CAPABILITY_CONFIG        = 0x0081,
    NETIPCFG_GROUP_ID					  = 0x0082,
    NETCARDCFG_GROUP_ID                   = 0x0083,
    DEVICECFG_GROUP_ID                    = 0x0084,
    VERSION_GROUP_ID                      = 0x0085,
    DEVICE_TYPE_GROUP_ID                  = 0x0086,
	WEB_PASSWD_CONFIG_GROUP_ID			  = 0x0087,
    PARAM_EXTRAL_DEFINE_END               = 0x0088,

	/* add by zsz : elec prtocol parameter */
	PARAM_ELEC_DEFINE_BEGIN		  		  = 0x00b0,
	PARAM_ELEC_HOST_DEVICE_CONFIG		  = 0x00b1,
	PARAM_ELEC_IPC_SERVER_CONFIG		  = 0x00b2,
	PARAM_CONNECT_RPU_CONFIG			  = 0x00b3,
	PARAM_DNS_SERVER_CONFIG				  = 0x00b4,
	PARAM_ELEC_SUB_DEV					  = 0x00b5,
	PARAM_ELEC_ALM_DEPLOY				  = 0x00b6, //����Э��澯����������
	PARAM_ELEC_ALM_SUBCRIPT				  = 0x00b7, //����Э��澯��������
	PARAM_ELEC_ENV_DEV_CONFIG			  = 0x00b8, //����Э�黷�����豸����
	PARAM_ELEC_NTP_SERVER_CONFIG		  = 0x00b9, //����Э��NTP����������
	PARAM_ELEC_TIME_ZONE_CONFIG			  = 0x00ba, //����Э��ʱ������
	PARAM_RPU_USER_INFOR				  = 0x00bb,	//����Э��rpu�û���Ϣ
	PARAM_ELEC_DEV_ALARM				  = 0x00bc, //����Э���豸��������
	PARAM_ELEC_DEFINE_END,
	/* add end */
};


/*camera_type: ���������*/
enum
{
    CAMERA_WITH_PTZ,      /*����̨*/
    CAMERA_WITHOUT_PTZ,   /*������̨*/
    CAMERA_TYPE_END
};


/*Ptz:��̨Э��*/
enum
{
	PTZ_PROTO_ALEC,
	PTZ_PROTO_ALEC_D,
	PTZ_PROTO_ALEC_P,
	PTZ_PROTO_MINKING_D,
	PTZ_PROTO_MINKING_P,
	PTZ_PROTO_PELCO_D,
	PTZ_PROTO_PELCO_P,
	PTZ_PROTO_VISCA,
	PTZ_PROTO_DM368BALL,
	PTZ_PROTO_END
};

/*��̨����*/
enum
{	PTZ_CMD_NULL=0X00,

	PTZ_CMD_IRIS_CLOSE_STOP,	
	PTZ_CMD_IRIS_CLOSE,
	PTZ_CMD_IRIS_OPEN_STOP,
 	PTZ_CMD_IRIS_OPEN,
	PTZ_CMD_FOCUS_NEAR_STOP,
	PTZ_CMD_FOCUS_NEAR,
	PTZ_CMD_FOCUS_FAR_STOP,
	PTZ_CMD_FOCUS_FAR,
	PTZ_CMD_ZOOM_TELE_STOP,
	PTZ_CMD_ZOOM_TELE,
	PTZ_CMD_ZOOM_WIDE_STOP,
	PTZ_CMD_ZOOM_WIDE,

	PTZ_CMD_TILT_UP,
	PTZ_CMD_TILT_DOWN,
	PTZ_CMD_PAN_RIGHT,
	PTZ_CMD_PAN_LEFT,
	PTZ_CMD_LEFT_UP,
	PTZ_CMD_LEFT_DOWN,
	PTZ_CMD_RIGHT_UP,
	PTZ_CMD_RIGHT_DOWN,
	
	PTZ_CMD_TILT_UP_STOP,
	PTZ_CMD_TILT_DOWN_STOP,
	PTZ_CMD_PAN_RIGHT_STOP,
	PTZ_CMD_PAN_LEFT_STOP,
	PTZ_CMD_LEFT_UP_STOP,
	PTZ_CMD_LEFT_DOWN_STOP, 
	PTZ_CMD_RIGHT_UP_STOP,
	PTZ_CMD_RIGHT_DOWN_STOP,

	PTZ_CMD_SET_PRESET,
	PTZ_CMD_CALL_PRESET,
	PTZ_CMD_DEL_PRESET,
	
	PTZ_CMD_DO_CRUISE,
	PTZ_CMD_STOP_CRUISE,

	PTZ_CMD_BRUSH_ON,
	PTZ_CMD_BRUSH_OFF,
	PTZ_CMD_LIGHT_ON,
	PTZ_CMD_LIGHT_OFF,
	PTZ_CMD_INFRARED_ON,
	PTZ_CMD_INFRARED_OFF,
	PTZ_CMD_HEATER_ON,
	PTZ_CMD_HEATER_OFF,

	PTZ_CMD_SET_PAN_SPEED,
	PTZ_CMD_SET_TILT_SPEED,
	PTZ_CMD_SET_FOUCE_SPEED,
	PTZ_CMD_SET_ZOOM_SPEED,
	PTZ_CMD_LOCK,
	PTZ_CMD_UNLOCK,

	PTZ_CMD_SUM

} ;

/*serial_type: ��������*/
enum
{
    SER_RS232,
    SER_RS422,
    SER_RS485,
    SER_TYPE_END
};

/*serial_mode: ����ģʽ*/
enum
{
    SER_MODE_CONSOLE,     /*��������̨*/
    SER_MODE_TRANSCH,     /*����͸��ͨ��*/
    SER_MODE_PTZ_CTRL,    /*������̨����*/
	SER_MODE_EXTERN_MOUDLE,/*��չģ��ʹ��*/
    SER_MODE_END
};

/*serial.baudrate: ���ڲ�����*/
enum
{
    BAUDRATE_1200,
    BAUDRATE_2400,
    BAUDRATE_4800,
    BAUDRATE_9600,
    BAUDRATE_14400,
    BAUDRATE_19200,
    BAUDRATE_38400,
    BAUDRATE_57600,
    BAUDRATE_115200,
    BAUDRATE_END
};


/*serial.stopbit:������ֹͣλ*/
enum
{
    STOPBIT_1BIT,
    STOPBIT_1P5_BIT,
    STOPBIT_2BIT,
    STOPBIT_END
};

/*serial.paritybit: ����У��λ*/
enum
{
    PARIYT_NONE,     /*��У��*/
    PARIYT_ODD,      /*��У��*/
    PARIYT_EVEN,     /*żУ��*/
	PARIYT_SYMBOL,	 /*��־У��*/
	PARIYT_BLANK,	 /*�ո�У��*/
    PARIYT_END
};

/*video stream_type: ��Ƶ������װ����*/
enum
{
    STREAM_PKT_RTP,
    STREAM_PKT_TS,
    STREAM_PKT_PS,
    STREAM_PKT_ES,
    STREAM_PKT_END
};

/*video encode_format: ��Ƶ�����ʽ*/
enum
{
    VIDEO_H264,
    VIDEO_H263,
    VIDEO_MJPEG,
    VIDEO_MPEG2,
    VIDEO_MPEG4,
    VIDEO_ENCODE_END
};

/*video resoution: ��Ƶ�ֱ���*/
enum
{
    VIDEO_RES_QCIF,
    VIDEO_RES_CIF,
    VIDEO_RES_2CIF,
    VIDEO_RES_4CIF,
    VIDEO_RES_D1,
    VIDEO_RES_720P,
    VIDEO_RES_1080I,
    VIDEO_RES_1080P,
    VIDEO_RES_END
};

/*video gop_mode: GOPģʽ*/
enum
{
    GOP_MODE_I,
    GOP_MODE_IP,
    GOP_MODE_IBP,
    GOP_MODE_IBBP,
    GOP_MODE_END
};

/*video encode_mode: ��Ƶ����ģʽ*/
enum
{
    VIDEO_CBR,
    VIDEO_VBR_BEST,
    VIDEO_VBR_BETTER,
    VIDEO_VBR_GOOD,
    VIDEO_VBR_BAD,
    VIDEO_VBR_WORSE,
    VIDEO_EC_MODE_END
};

/*video priority:����Ƶ�������ȼ�*/
enum
{
    VPRIO_FRAMERATE_FIRST,    /*֡������*/
    VPRIO_BITRATE_FIRST,      /*��������*/
    VPRIO_END
};

/*smooth_value: ����ƽ��ʹ�ܿ���*/
enum
{
	BITSTREAM_SMOOTH_DISABLE,
	BITSTREAM_SMOOTH_ENABLE,
	BITSTREAM_SMOOTH_END
};


/*Ip��ȡ��ʽ*/
enum
{
	IP_PPPOE = 0,
	IP_DHCP,
	IP_STATIC,
	IP_END
};

/*����ģʽ*/
enum net_card_type
{

	SPEED10_DUPLEX_HALF = 0,
	SPEED10_DUPLEX_FULL,
	SPEED100_DUPLEX_HALF,
	SPEED100_DUPLEX_FULL,
	SPEED1000_DUPLEX_HALF,
	SPEED1000_DUPLEX_FULL,
	SPEED_DUPLEX_TYPE_END
};

/*encoder*/
enum
{
	EC_STREAM_H264 = 0,
	EC_STREAM_H263,
	EC_STREAM_MJPEG,
	EC_STREAM_MPEG2,
	EC_STREAM_MPEG4,
	EC_STREAM_END
};

/*alarm_type:*/
enum
{
	ALARM_TYPE_TEMPE_ALERT,       /*�¶ȸ澯*/
	ALARM_TYPE_VIDEO_LOSS,        /*��Ƶ��ʧ*/
	ALARM_TYPE_VIDEO_MOTION,      /*�˶����*/
	ALARM_TYPE_SEMA_INPUT,        /*����������*/
	ALARM_TYPE_FAN_ALERT,         /*���ȸ澯*/
	ALARM_TYPE_STORAGE_FAILED,    /*�洢ʧ��*/
	ALARM_TYPE_DISK_ERROR,        /* ���̹��� */
	ALARM_TYPE_VIDEO_RECOVER,     /*��Ƶ�ָ�*/
	ALARM_TYPE_TEMPE_RECOVER,     /*�¶Ȼָ�*/
	ALARM_TYPE_OTHER,             /*����*/
	ALARM_TYPE_END		
};

/*action_type:*/
enum
{
	ACTION_TYPE_STORAGE,          /*�����洢*/
	ACTION_TYPE_PTZ_PRESET,       /*����Ԥ�õ�*/
	ACTION_TYPE_PTZ_PATROL,       /*����Ѳ��*/
	ACTION_TYPE_SEMA_OUTPUT,      /*�������������*/
	ACTION_TYPE_SNAPSHOT,         /*����ץ��*/
	ACTION_TYPE_OTHER,            /*��������*/
	ACTION_TYPE_END
};

/*standard: ��ʽ*/
enum
{
	/* SD standard */
    STANDARD_PAL,
    STANDARD_NTSC,

	/* HD standard */
	STANDARD_720P25,
	STANDARD_720P30,
	STANDARD_720P50,
	STANDARD_720P60,
	STANDARD_1080I50,
	STANDARD_1080P25,
	STANDARD_1080I60,
	STANDARD_1080P30,
	STANDARD_1080P50,
	STANDARD_1080P60,

    STANDARD_END
};

#pragma pack(1)

/*�ظ�set/get/cmd��״̬*/
typedef struct _reply_status
{
	Uint8	status;         //״̬���ɹ���ʧ��
	Uint8	err_mask;       //����mask
	Uint16	err_code;      	//������
} reply_status_t;

/* ptz״̬��ѯ */
struct ptz_run_status
{
	Uint8   panspeed;
	Uint8   tiltspeed;
	Uint8   focusspeed;
	Uint8   zoomspeed;
	Uint8   lock_status;
	Uint8   light_status;
	Uint8   infrared_status;
	Uint8   brush_status;
	Uint8   heat_status;
	Uint8   reserved1;
	Uint8   reserved2;
	Uint8   reserved3;
};

/*ip��Ϣ���ýṹ��*/
struct net_ip_config
{
    Uint8  ip[IPADDR_LEN];
    Uint8  mask[IPADDR_LEN];
    Uint8  gateway[IPADDR_LEN];

    CHAR   pppoe_username[128];
    CHAR   pppoe_passwd[128];

    Uint8  get_ip_mode;//��ȡ��ʽ
    Uint8  eth_idx;
    Uint8  ip_version; //ip���ͣ�ipv4��ipv6
};

/*�ն������������ýṹ��*/
struct ethernet_config
{
	Uint32  mode;
	Uint32  mtu;//MTU����
	Uint8   eth_idx;
	Uint8   reserved[3];
};


/*�ն��豸�����ṹ��*/
struct device_config
{
	Uint8   vm_server_ipaddr[IPADDR_LEN];	//VM������ip
	Uint16  vm_server_port;				//VM�������˿ں�
	Uint8   device_run_mode;			//�豸����ģʽ 0 - ��������ģʽ 1 -�й�ģʽ
	Uint8   ip_version;					//ip���ͣ�
	CHAR    device_id[64];				//�豸ID��

	CHAR    rn_id[MAX_NAME_LEN];        //��ID
	Uint8   rn_enable;                  // ����ʹ��
	Uint8   rn_node_mode;               //�ڵ㹤��ģʽ 0-�� 1-�� 
	Uint8   rn_timeout_count;           // 

	Uint8   vlan_enable;                //
	Uint16  net_default_vid;            //����1��Ĭ��vid
	Uint16  cpu_default_vid;            //cpu��Ĭ��vid
	Uint16  net2_default_vid;           //����2��Ĭ��vid
	Uint16  net3_default_vid;           //����3��Ĭ��vid
	Uint8	reserved[16];				//����

};


/*2. EC��Ϣ*/
struct encoder_config
{
    Uint8   language_set;
    Uint8   enable_localcache;
    Uint8   encode_set;
    Uint8   standard;
    Uint8   audiocommr_id;
    Uint8   audiobroadcast_id;
    Uint8    enable_alarm;
    Uint8    is_multicast;
    //FIXME
    Uint16  keepalive_interval;
    Uint8    is_autofit;
    Uint8   reserved;
};

/*3. DC��Ϣ*/
struct decoder_config
{
    Uint8   language_set;
    Uint8   encode_set;
    Uint8   standard;
    Uint8    enable_alarm;
    Uint16  keepalive_interval;
    Uint8    is_multicast;
    Uint8    is_autofit;
};

/*4. �¶ȸ澯����*/
struct tempe_alarm_config
{
	Uint32   tempe_alarm_upper;
	Uint32   tempe_alarm_lower;
	CHAR    tempe_alarm_desc[MAX_DESC_LEN];
	Uint8    is_enable;
	Uint8   reserved[3];
};

/*5. ����ͨ�����*/
struct phyout_channel_config
{
    Uint8   phyout_mode;
    Uint8   fill_method;
    Uint8   decode_format;
    Uint8   audio_format;
    Uint8   audio_track;
    Uint8    is_silent;
    Uint8   volume;
    Uint8   output_index;
    //FIXME
    Uint8   stream_type;
    Uint8   resolution;
    Uint16  smooth_value;
	CHAR    monitor_name[MAX_NAME_LEN];
    CHAR    monitor_desc[MAX_DESC_LEN];
};

/*6. ��Ƶ����ͨ��*/
struct ain_channel_config
{
    Uint8    is_silent;
    Uint8    is_enable;
    Uint8   audio_coding;
    Uint8   audio_track;
    Uint32  sampling_rate;
    CHAR    audioin_desc[MAX_DESC_LEN];
    Uint16   increments;
    Uint8   audio_bitrate;
    Uint8   reserved[1];
};


/*7. ��Ƶ���ͨ��*/
struct aout_channel_config
{
    Uint8    is_silent;
    Uint8    is_enable;
    Uint8   audio_coding;
    Uint8   audio_track;
    CHAR    audioout_desc[MAX_DESC_LEN];
    Uint16   increments;
    Uint8   reserved[2];
};

/*8. ���������*/
struct camera_config
{
    Uint32  longitude;
    Uint32  latitude;
    CHAR    camera_name[MAX_NAME_LEN];
    CHAR    camera_desc[MAX_DESC_LEN];
    Uint8    is_enable;
    Uint8   brightness;
    Uint8   contrast;
    Uint8   saturation;
    Uint8   tone;
    Uint8   white_blance;
    Uint8   camera_type;
    Uint8   reserved[1];
};

/*9. �����PTZ��Ϣ*/
struct ptz_config
{
    Uint32  ptz_addrcode;
    Uint32  auto_guard_interval;
    CHAR    preset_name[128][MAX_NAME_LEN];
    Uint8   preset_enable_list[16];
    Uint8   serial_index;
    Uint8   guard_position;
    Uint8   ptz_protocol;
    Uint8   ptz_translate_mode;
};

/*10. ��Ƶ�Խ���������*/
struct audiocommr_input_config
{
    Uint8   audiocommr_res;
    Uint8    is_silent;
    Uint8   audiocommr_input_method;
    Uint8   audiocommr_encode_format;
    CHAR    audiocommr_res_desc[MAX_DESC_LEN];
    Uint32  audiocommr_sample_rate;
    Uint32  audiocommr_bitrate;
    Uint16   audiocommr_input_increments;
    Uint8   audiocommr_input_track;
    Uint8   reserved[1];
};

/*11.��Ƶ�Խ��������*/
struct audiocommr_output_config
{
    Uint8   audiocommr_res;
    Uint8    is_silent;
    Uint8   audiocommr_output_method;
    Uint8   audiocommr_encode_format;
    CHAR    audiocommr_res_desc[MAX_DESC_LEN];
    Uint32  audiocommr_bitrate;
    Uint16   audiocommr_output_increments;
    Uint8   audiocommr_output_track;
    Uint8   reserved[1];
};

/*12.͸��ͨ������������Ϣ��ѯ*/
struct trans_save_query
{
	Uint8   ip_addr[IPADDR_LEN]; // ע���ǰ����ֽ�ip��ʽ�洢��
	Uint16  ip_port;
	Uint8   serial_index;
	Uint8   enable;
};

/*13.���ڻ�����Ϣ*/
struct serial_config
{
    CHAR    serial_name[MAX_NAME_LEN];
    Uint8   serial_type;
    Uint8   serial_mode;
    Uint8   baudrate;
    Uint8   databit;
    Uint8   stopbit;
    Uint8   paritybit;
    Uint8   flowcontrol;
    Uint8    reserved[1];
};

/*14.��Ƶ������*/
struct video_stream_config
{
    Uint8   vin_channel_index;
    Uint8   stream_index;
	Uint8    enable_stream;
    Uint8   stream_trantype;
    Uint8   stream_type;
    Uint8   encode_format;
    Uint8   resolution;
    Uint8   frame_rate;
    Uint32  bit_rate;
    Uint32  i_frame_interval;
    Uint32  image_quality;
    Uint8   encode_mode;
    Uint8   priority;
    Uint8   smooth_value;
    Uint8   gop_mode;
    //FIXME
    Uint8   quality_level;
    Uint8   addr_type;

    Uint16  multicast_port;
    Uint8   multicast_addr[IPADDR_LEN];
};

/*15.�˶��������*/
struct motion_detec_config
{
	Uint8   vin_channel_index;
	Uint8   motion_area_index;
	Uint8    is_enable;
	Uint8   sensitivity;
	CHAR    area_name[MAX_NAME_LEN];
	BBitmap8_t  area_mask[MAX_AREA_MASK];
};


/*16.��˽�ڸ�����*/
struct privacy_mask_config
{
	Uint8   vin_channel_index;
	Uint8   mask_area_index;
	Uint8    is_enable;
	Uint8   mask_color;
	Uint16  top_left_x;
	Uint16  top_left_y;
	Uint16  bottom_right_x;
	Uint16  bottom_right_y;
};

/*17.OSDʱ������*/
struct osd_time_config
{
	Uint8   stream_index;
	Uint8    is_enable;
	Uint8   osd_time_format;
	Uint8   osd_date_format;
	Uint16  start_x;
	Uint16  start_y;
	Uint8   osd_color;
	Uint8   osd_transparence;
	Uint8   osd_time_freq;
	Uint8   reserved[1];
};


/*18.OSD������Ϣ*/
struct osd_field_config
{
	Uint8   stream_index;
	Uint8    is_enable;
	Uint8   osd_color;
	Uint8   osd_transparence;
	Uint16  start_x;
	Uint16  start_y;
	Uint32  switch_interval;
	CHAR    osd_main_value[MAX_OSD_VALUE];
	CHAR    osd_sub_value[MAX_OSD_VALUE];
	Uint8   osd_main_type;
	Uint8   osd_sub_type;
	Uint8   reserved[2];

};


/*19.�������澯����*/
struct sema_input_config
{
    CHAR    sema_name[MAX_NAME_LEN];
    CHAR    sema_input_desc[MAX_DESC_LEN];
    Uint8    is_enable;
    Uint8   trigger_mode;
    Uint8   enable_detect;
	Uint8   work_mode;
};
    

/*20.�������澯���*/
struct sema_output_config
{
    CHAR    sema_name[MAX_NAME_LEN];
    CHAR    sema_output_desc[MAX_DESC_LEN];
    Uint32  sema_output_time;
    Uint8    is_enable;
    Uint8   trigger_mode;
    Uint8    enable_detect;
	Uint8   work_mode;
};

/*21.Ѳ��·������*/
struct cruise_path_config
{
    Uint32  preset_intervallist[MAX_LIST_LEN];
    Uint8   vin_channel_index;
    Uint8   cruise_path_index;
    Uint8    is_enable;
    Uint8   preset_count;
    Uint8   preset_list[MAX_LIST_LEN];
    Uint8   status;
    Uint8   reserved[3];
	CHAR    cruise_path_name[MAX_NAME_LEN];
};

/*22.Ѳ���ƻ�ʱ��*/
struct cruise_plan_config
{
	Uint8   vin_channel_index;
	Uint8    enable_plan;
	Uint8   path1_path_index;
	Uint8   path2_path_index;
	Schedule_t  path1_time_schedule[7];
	Schedule_t  path2_time_schedule[7];
	Schedule_t  path3_time_schedule[7];
	Schedule_t  path4_time_schedule[7];
	Uint8   path3_path_index;
	Uint8   path4_path_index;
	Uint8   plan_type;      /* �ܼƻ� or �ռƻ� ƽ̨ʹ�� */
	Uint8   reserved;
	CHAR    cruise_plan_name[MAX_NAME_LEN];
};

/*23.Ѳ���ƻ�����ʱ��*/
struct cruise_ext_plan_config
{
	Date_t  ext_date;
	Uint8   vin_channel_index;
	Uint8    enable_ext_plan;
	Uint8   path1_path_index;
	Uint8   path2_path_index;
	Schedule_t  path1_time_schedule;
	Schedule_t  path2_time_schedule;
	Schedule_t  path3_time_schedule;
	Schedule_t  path4_time_schedule;
	Uint8   path3_path_index;
	Uint8   path4_path_index;
	Uint8   reserved[2];
};

/*24.�洢������Ϣ*/
struct storage_info_config
{
	Uint8   storage_mode;
	Uint8   plan_stream_type;
	Uint8   manual_stream_type;
	Uint8   evnent_stream_type;
	Uint8   storage_medium_type;
	Uint8   full_policy;
	Uint8   reserved[2];
};

/*25.IPSAN�洢����*/
struct storage_ipsan_config
{
	Uint8   ipsan_address[IPADDR_LEN];
	CHAR    target_name[MAX_IQN_LEN];
	CHAR    initiator_name[MAX_IQN_LEN];
	Uint32  space;
	Uint32  lun_id;
	Uint16  ipsan_port;
	Uint8   addr_type;
	Uint8   reserved[1];
};


/*26.�澯�洢����*/
struct alarm_storage_config
{
	Uint32  pre_alarm_time;
	Uint32  after_alarm_time;
	Uint32  bit_rate;
	Uint8   vin_channel_index;
	Uint8   stream_type;
	Uint8   frame_rate;
	Uint8   reserved[1];
};

/*27.�洢�ƻ�ʱ��*/
struct storage_plan_config
{
	Uint8   vin_channel_index;
	Uint8   stream_type;
	Schedule_t  plan_time_schedule[7];
	Uint8    enable_plan;
	Uint8   plan_type;      /* �ܼƻ� or �ռƻ� ƽ̨ʹ��*/
	Uint8   reserved[2];
	CHAR    storage_plan_name[MAX_NAME_LEN];
};


/*28.�洢�ƻ�����ʱ��*/
struct storage_ext_plan_config
{
	Date_t  ext_date;
	Schedule_t  ext_plan_schedule;
	Uint8   vin_channel_index;
	//FIXME
	Uint8   stream_type;
	Uint8    enable_plan;
	Uint8   reserved[3];
};

/*29.�澯����������*/
struct alarm_linkage_config
{
    Uint64 alarm_source_index;
    Uint32  param1;
    Uint32  param2;
    Uint32  param3;
    Uint8   execute_type;
    Uint8    is_enable;
    Uint8   alarm_type;
    Uint8   reserved[1];
};


/*30.����������*/
struct linkage_action_table
{
    Uint64 alarm_source_index;
    Uint32  param1;
    Uint32  param2;
    Uint32  param3;
    Uint32  delay_time;
    Uint8   action_type;
    Uint8   reserved[3];
};

/*31.��������ʱ��*/
struct alarm_plan_config
{
	Uint32  param1;
	Uint32  param2;
	Uint32  param3;
	Schedule_t  plan_time_schedule[7];
	Uint8   vin_channel_index;
	Uint8   alarm_type;
	Uint8    enable_plan;
	Uint8   plan_type;      /* �ܼƻ� or �ռƻ� ƽ̨ʹ�� */
	Uint8   reserved[2];
	CHAR    alarm_plan_name[MAX_NAME_LEN];
};

/*32.������������ʱ��*/
struct alarm_ext_plan_config
{
	Uint32  param1;
	Uint32  param2;
	Uint32  param3;
	Date_t  policy_date;
	Schedule_t  ext_plan_schedule;
	Uint8   vin_channel_index;
	Uint8   alarm_type;
	Uint8    enable_plan;
	Uint8   reserved[3];
};

/*33.����δ��*/
struct reserved_config
{
	Uint32 reserved[14];
};

/*34.ʵ���ָ����ýṹ��*/
struct live_recover
{
	Uint8       enable;         /*�Ƿ���Ҫ�ָ��ı�׼*/
	Uint8       channel_id;     /*ͨ����            */
	Uint8       sub_index;      /*ʵ���Ǹ�ͨ���ڼ�·*/
	Uint8       main_sub_flag;  /*������            */
	Uint8		dst_ip[16];     /*Ŀ��IP,�����ĸ��ֽڷ�ʽ�洢��*/
	Uint16      dst_port;       /*Ŀ��port          */
	Int16       trans_mode;     /*����ģʽ,TCP/UDP  */
	Int16       streaming_type; /*��������,TS/RTP   */
	Uint8       mc_flag;        /*�Ƿ��鲥          */
	Uint8       reserved;       /*����              */
};

/*35.ǹ���ػ������ʾ�ṹ��*/
struct image_loopback_config
{ 
	Uint16  enable;     /*0x00��disable, 0x01��enable*/ 
	Uint16  loop_mode;  /*0x00: ȡD1��С����, 0x01��ѹ��*/ 
	Uint16  start_x;    /*��ʼ����*/ 
	Uint16  start_y; 
	Uint16  end_x;      /*��ֹ����*/
	Uint16  end_y; 
	Uint8   reserved[4];
};

/*36.IPC��ѧ����*/
struct ipc_optical_config
{
	Uint32  customData_1;
	Uint32  customData_2;
	Uint32  customData_3;
	Uint32  customData_4;
	Uint32  customData_5;
	Uint16  usr_area_left;
	Uint16  usr_area_up;
	Uint16  usr_area_right;
	Uint16  usr_area_down;
	Uint8   exposure_area;
	Uint8   brightness;
	Uint8   contrast;
	Uint8   saturation;
	Uint8   color_tone;
	Uint8   sharpness;
	Uint8   wdr_enable;
	Uint8   wdr_level;
	Uint8   mirror_flip;
	Uint8   awb_type;
	Uint8   awb_mode;
	Uint8   get_awb_r_gain;
	Uint8   get_awb_g_gain;
	Uint8   get_awb_b_gain;
	Uint8   set_awb_r_gain;
	Uint8   set_awb_g_gain;
	Uint8   set_awb_b_gain;
	Uint8   flicker_ctrl;
	Uint8   exposure_ctrl;
	Uint8   exposure_value;
	Uint8   iris_type;
	Uint8   max_exposure_time;
	Uint8   min_exposure_time;
	Uint8   max_gain;
	Uint8   min_gain;
	Uint8   max_analog_gain;
	Uint8   min_analog_gain;
	Uint8   max_digital_gain;
	Uint8   min_digital_gain;
	Uint8   get_exposure_time;
	Uint8   get_gain;
	Uint8   get_analog_gain;
	Uint8   get_digital_gain;
	Uint8   set_exposure_time;
	Uint8   set_gain;
	Uint8   set_analog_gain;
	Uint8   set_digital_gain;
	Uint8   indoor_outdoor;
	Uint8   night_scene_enhance_enable;
	Uint8   night_scene_enhance_level;
	Uint8   color_mono_chroma;
	Uint8   blc_enable;
	Uint8   blc_level;
	Uint8   light_link_mode;
	Uint8   lamb_in_en;
	Uint8   lamb_out_en;
	Uint8   ir_cut;
	Uint8   exposure_sensitivity;
	Uint8   exposure_priority;
	Uint8   cur_color_temperature;
	Uint8   reserved[178];
};

/*��ȡ�ն��豸������������Ϣ��������ģʽ*/
struct get_type_info
{
    Uint32  camera_type[32];            //��������� 0 -����̨ 1- ������̨
    Uint32  player_param[32*2];         //��16λ������ʽ����16λ����ֱ���, ʵ��ֻʹ��channel_num��,
                                        //��32���ֽڱ�ʾ������������������32���ֽڱ�ʾ��������������
    Uint32  device_type;                //�豸���� 0 - EC 1 - DC 2-GUN 3-BALL
    CHAR    type_name[MAX_NAME_LEN];    //�豸���� VG1001/VG1004/VC6210...
    Uint8   channel_num;                //ͨ������
	Uint8   phy_id;
	Uint8	reserved[2];
	Uint32  device_model;               //�豸�ͺ���, ǰ16λ�������ֲ�ͬЭ��(��ͨΪ0x0000, ����Ϊ0x0001), ��16λ��дDEVICE_NAME 
};

/* �ն�web�������Ľṹ�� */
struct web_passwd_config
{
	CHAR    web_passwd[IPSAN_PASSWD_LEN];
};


/* �汾�Ų�ѯ��������ģʽ */
struct version_report_pl
{
	CHAR   kernel_version[32];          /* version string */
	CHAR   ramdisk_version[32];         /* version string */
	CHAR   fpga_version[32];            /* version string */
	CHAR   cpld_version[32];            /* version string */
	CHAR   dsp_version[32];             /* version string */
};

/* �����������صĽ�� */
struct image_update_result
{
	ret_info kernel_update_result;
   	ret_info ramdisk_update_result;
	ret_info fpga_update_result;
	ret_info cpld_update_result;	
};
/* 37.AI��չ����*/
struct ai_inter_extend
{
	Uint32  valid_flag;
	Uint32  ai_addrcode;
	Uint32  serial_index;
	Uint32	sub_index; // 0 ~ 7 һ��485������8����չģ��
	Uint32	max_num; // ��ģ����� ���ԽӶ��ٸ����豸
	CHAR    ai_name[MAX_NAME_LEN];
};

/* 38.DI��չ���� */
struct di_inter_extend
{
	Uint32  valid_flag;
	Uint32  di_addrcode;
	Uint32  serial_index;
	Uint32	sub_index; // 0 ~ 7 һ��485������8����չģ��
	Uint32	max_num; // ��ģ����� ���ԽӶ��ٸ����豸
	CHAR    di_name[MAX_NAME_LEN];
};

/* 39.DO��չ�������� */
struct do_inter_extend
{
	Uint32  valid_flag;
	Uint32  do_addrcode;
	Uint32  serial_index;
	Uint32	sub_index; // 0 ~ 7 һ��485������8����չģ��
	Uint32	max_num; // ��ģ����� ���ԽӶ��ٸ����豸
	CHAR    do_name[MAX_NAME_LEN];
};

/* 40.�Ž�������������485����*8 */
struct gate_forbid_device
{
	Uint32	valid_flag;
	Uint32	dev_addrcode;
	Uint32	serial_index;
	Uint32	sub_index;
	Uint32	max_num;
	CHAR    gate_forbid_name[MAX_NAME_LEN];
};

/* 41.��������չ�澯����,����485����*8*8 */
struct sema_extern_input_config
{
	CHAR    sema_name[MAX_NAME_LEN];
	CHAR	sema_input_desc[MAX_DESC_LEN];
	BOOL	is_enable;
	Uint8	trigger_mode;
	BOOL	enable_detect;
	Uint8   work_mode;
};

/* 42.�ڵ���ⱨ�� */
struct hide_detect_alm_config
{
	Int32	enable;
	Int32	hide_detection_x;
	Int32	hide_detection_y;
	Int32	hide_detection_width;
	Int32	hide_detection_height;
};

/* 43.ץͼ�������� */
struct snapshot_config
{
	Uint8   ftpserv_ip[IPADDR_LEN];		    /* FTP������IP */
	CHAR    username[32];			        /* FTP�������û��� */
	CHAR    password[32];			        /* FTP���������� */
	CHAR    path[256];                      /* FTP����Ŀ¼ */
	Uint32  num;                            /* ץͼ����1~5�� */
	Uint32  timeval;                        /* ץͼ���50~500ms */
	Uint32  reserved[16];
};



/* **********************************************************
 *				���½ṹ�������Э��ʹ��					*
 * **********************************************************/

/* 1.��ӵ���Э�����豸 */
struct elec_sub_dev
{
	Int64	iSubDevId;
	CHAR	szSubDevDesc[32];
	Int32	iPhyInfType; // �ӿ�����(0:self_di 1:ex_di 2:self_do 3:ex_do 4: self_ai 5:ex_ai)
	Int32	iPhyInfMainIdx;//�Դ��ľ��Ǹýӿ��ڰ����ϵ���������չ��ָ����չģ������ĸ�485��
	Int32	iPhyInfSubIdx;//�Դ��ӿ���Ч,��չģ���Ͽ��Խ�8�����豸����չģ�������ֵ
	Int32	address_code;//��չģ��ĵ�ַ��	
	Int32   a1;
	Int32   a0;
};

/* 1.����Э����Ƶ������豸 */
struct elec_ipc_config
{
	CHAR	szIPCName[128];//ƽ̨ͳһ����
	Int64	iIPCId;//ƽ̨ͳһ���
	Int32	iIPCMajorType;//�����ͣ���ǰΪ1
	Int32	iIPCMinorType;//�����ͣ���ǰΪ1
	CHAR	szIPCModel[32];//ֻ�������ɸ���
	CHAR	szIPCSerialID[64];//ֻ�������ɸ���
	CHAR	szIPCVerion[64];//ֻ�������ɸ���
};

/* 2.IPC�����ַ��Ϣ */
struct elec_ipc_server
{
	CHAR	szSvcIpAddr[32];
	Uint16	usSvcPort;
	Uint16	reserved;
	Int32	iHeatrBeatInterval;
};

/* 3.����RPU���� */
struct conn_rpu_config
{	
	Int32	iEnable;
	CHAR	svrname[128];
	CHAR	szConnPass[128];
	CHAR	szServeIpAddr[32];
	Int32	iServerPort;
}; 

/* 4.DSN������ */
struct dns_server
{
	char szDns[128];//���Զ�����ո����
};

/* **********************************************************
 *				����Э��ṹ�����							*
 * **********************************************************/
#pragma pack()

#ifdef __cplusplus
}
#endif
#endif   /* ----- #ifndef TER_SDK_INC  ----- */

