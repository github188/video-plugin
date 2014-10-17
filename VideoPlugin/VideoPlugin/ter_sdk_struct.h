/*
 * =====================================================================================
 *       Copyright (C), 2010, islab@ZJU
 *
 *       FileName:  ter_sdk_struct.h
 *
 *		   Author:  zsz (Islab)
 *			 Date:	2010年10月16日 14时56分09秒 CST
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

/*通道总数*/
#define MAX_CHANNEL_NUM		(16)

/*摄像机名长度*/
#define MAX_NAME_LEN		(32)
#define MAX_DESC_LEN		(64)
#define IPADDR_LEN			(16)
#define MAX_LIST_LEN		(32)
#define IPSAN_PASSWD_LEN	(32)

/* 升级镜像的宏 */
#define KERNEL_UPDATE		(0x01)
#define RAMDISK_UPDATE		(0x02)
#define FPGA_UPDATE			(0x04)
#define CPLD_UPDATE			(0x08)

#define MAX_AREA_MASK                 (1024)
#define MAX_OSD_VALUE                 (64)
#define MAX_IQN_LEN   (128)

/*获取或设置参数表的索引号*/
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
	PARAM_ELEC_ALM_DEPLOY				  = 0x00b6, //电力协议告警布撤防配置
	PARAM_ELEC_ALM_SUBCRIPT				  = 0x00b7, //电力协议告警订阅配置
	PARAM_ELEC_ENV_DEV_CONFIG			  = 0x00b8, //电力协议环境量设备配置
	PARAM_ELEC_NTP_SERVER_CONFIG		  = 0x00b9, //电力协议NTP服务器配置
	PARAM_ELEC_TIME_ZONE_CONFIG			  = 0x00ba, //电力协议时区配置
	PARAM_RPU_USER_INFOR				  = 0x00bb,	//电力协议rpu用户信息
	PARAM_ELEC_DEV_ALARM				  = 0x00bc, //电力协议设备报警配置
	PARAM_ELEC_DEFINE_END,
	/* add end */
};


/*camera_type: 摄像机类型*/
enum
{
    CAMERA_WITH_PTZ,      /*带云台*/
    CAMERA_WITHOUT_PTZ,   /*不带云台*/
    CAMERA_TYPE_END
};


/*Ptz:云台协议*/
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

/*云台命令*/
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

/*serial_type: 串口类型*/
enum
{
    SER_RS232,
    SER_RS422,
    SER_RS485,
    SER_TYPE_END
};

/*serial_mode: 串口模式*/
enum
{
    SER_MODE_CONSOLE,     /*用作控制台*/
    SER_MODE_TRANSCH,     /*用作透明通道*/
    SER_MODE_PTZ_CTRL,    /*用作云台控制*/
	SER_MODE_EXTERN_MOUDLE,/*扩展模块使用*/
    SER_MODE_END
};

/*serial.baudrate: 串口波特率*/
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


/*serial.stopbit:　串口停止位*/
enum
{
    STOPBIT_1BIT,
    STOPBIT_1P5_BIT,
    STOPBIT_2BIT,
    STOPBIT_END
};

/*serial.paritybit: 串口校验位*/
enum
{
    PARIYT_NONE,     /*无校验*/
    PARIYT_ODD,      /*奇校验*/
    PARIYT_EVEN,     /*偶校验*/
	PARIYT_SYMBOL,	 /*标志校验*/
	PARIYT_BLANK,	 /*空格校验*/
    PARIYT_END
};

/*video stream_type: 视频码流封装类型*/
enum
{
    STREAM_PKT_RTP,
    STREAM_PKT_TS,
    STREAM_PKT_PS,
    STREAM_PKT_ES,
    STREAM_PKT_END
};

/*video encode_format: 视频编码格式*/
enum
{
    VIDEO_H264,
    VIDEO_H263,
    VIDEO_MJPEG,
    VIDEO_MPEG2,
    VIDEO_MPEG4,
    VIDEO_ENCODE_END
};

/*video resoution: 视频分辨率*/
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

/*video gop_mode: GOP模式*/
enum
{
    GOP_MODE_I,
    GOP_MODE_IP,
    GOP_MODE_IBP,
    GOP_MODE_IBBP,
    GOP_MODE_END
};

/*video encode_mode: 视频编码模式*/
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

/*video priority:　视频编码优先级*/
enum
{
    VPRIO_FRAMERATE_FIRST,    /*帧率优先*/
    VPRIO_BITRATE_FIRST,      /*码率优先*/
    VPRIO_END
};

/*smooth_value: 码流平滑使能开关*/
enum
{
	BITSTREAM_SMOOTH_DISABLE,
	BITSTREAM_SMOOTH_ENABLE,
	BITSTREAM_SMOOTH_END
};


/*Ip获取方式*/
enum
{
	IP_PPPOE = 0,
	IP_DHCP,
	IP_STATIC,
	IP_END
};

/*网卡模式*/
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
	ALARM_TYPE_TEMPE_ALERT,       /*温度告警*/
	ALARM_TYPE_VIDEO_LOSS,        /*视频丢失*/
	ALARM_TYPE_VIDEO_MOTION,      /*运动侦测*/
	ALARM_TYPE_SEMA_INPUT,        /*开关量输入*/
	ALARM_TYPE_FAN_ALERT,         /*风扇告警*/
	ALARM_TYPE_STORAGE_FAILED,    /*存储失败*/
	ALARM_TYPE_DISK_ERROR,        /* 磁盘故障 */
	ALARM_TYPE_VIDEO_RECOVER,     /*视频恢复*/
	ALARM_TYPE_TEMPE_RECOVER,     /*温度恢复*/
	ALARM_TYPE_OTHER,             /*其它*/
	ALARM_TYPE_END		
};

/*action_type:*/
enum
{
	ACTION_TYPE_STORAGE,          /*联动存储*/
	ACTION_TYPE_PTZ_PRESET,       /*联动预置点*/
	ACTION_TYPE_PTZ_PATROL,       /*联动巡航*/
	ACTION_TYPE_SEMA_OUTPUT,      /*联动开关量输出*/
	ACTION_TYPE_SNAPSHOT,         /*联动抓拍*/
	ACTION_TYPE_OTHER,            /*联动其它*/
	ACTION_TYPE_END
};

/*standard: 制式*/
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

/*回复set/get/cmd的状态*/
typedef struct _reply_status
{
	Uint8	status;         //状态：成功，失败
	Uint8	err_mask;       //错误mask
	Uint16	err_code;      	//错误码
} reply_status_t;

/* ptz状态查询 */
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

/*ip信息配置结构体*/
struct net_ip_config
{
    Uint8  ip[IPADDR_LEN];
    Uint8  mask[IPADDR_LEN];
    Uint8  gateway[IPADDR_LEN];

    CHAR   pppoe_username[128];
    CHAR   pppoe_passwd[128];

    Uint8  get_ip_mode;//获取方式
    Uint8  eth_idx;
    Uint8  ip_version; //ip类型，ipv4或ipv6
};

/*终端网卡参数配置结构体*/
struct ethernet_config
{
	Uint32  mode;
	Uint32  mtu;//MTU设置
	Uint8   eth_idx;
	Uint8   reserved[3];
};


/*终端设备参数结构体*/
struct device_config
{
	Uint8   vm_server_ipaddr[IPADDR_LEN];	//VM服务器ip
	Uint16  vm_server_port;				//VM服务器端口号
	Uint8   device_run_mode;			//设备运行模式 0 - 独立运行模式 1 -托管模式
	Uint8   ip_version;					//ip类型，
	CHAR    device_id[64];				//设备ID号

	CHAR    rn_id[MAX_NAME_LEN];        //环ID
	Uint8   rn_enable;                  // 环网使能
	Uint8   rn_node_mode;               //节点工作模式 0-主 1-从 
	Uint8   rn_timeout_count;           // 

	Uint8   vlan_enable;                //
	Uint16  net_default_vid;            //网口1的默认vid
	Uint16  cpu_default_vid;            //cpu的默认vid
	Uint16  net2_default_vid;           //网口2的默认vid
	Uint16  net3_default_vid;           //网口3的默认vid
	Uint8	reserved[16];				//保留

};


/*2. EC信息*/
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

/*3. DC信息*/
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

/*4. 温度告警配置*/
struct tempe_alarm_config
{
	Uint32   tempe_alarm_upper;
	Uint32   tempe_alarm_lower;
	CHAR    tempe_alarm_desc[MAX_DESC_LEN];
	Uint8    is_enable;
	Uint8   reserved[3];
};

/*5. 物理通道输出*/
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

/*6. 音频输入通道*/
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


/*7. 音频输出通道*/
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

/*8. 摄像机配置*/
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

/*9. 摄像机PTZ信息*/
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

/*10. 音频对讲输入配置*/
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

/*11.音频对讲输出配置*/
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

/*12.透明通道保存配置信息查询*/
struct trans_save_query
{
	Uint8   ip_addr[IPADDR_LEN]; // 注意是按四字节ip方式存储的
	Uint16  ip_port;
	Uint8   serial_index;
	Uint8   enable;
};

/*13.串口基本信息*/
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

/*14.视频流配置*/
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

/*15.运动侦测配置*/
struct motion_detec_config
{
	Uint8   vin_channel_index;
	Uint8   motion_area_index;
	Uint8    is_enable;
	Uint8   sensitivity;
	CHAR    area_name[MAX_NAME_LEN];
	BBitmap8_t  area_mask[MAX_AREA_MASK];
};


/*16.隐私遮盖配置*/
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

/*17.OSD时间设置*/
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


/*18.OSD场名信息*/
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


/*19.开关量告警输入*/
struct sema_input_config
{
    CHAR    sema_name[MAX_NAME_LEN];
    CHAR    sema_input_desc[MAX_DESC_LEN];
    Uint8    is_enable;
    Uint8   trigger_mode;
    Uint8   enable_detect;
	Uint8   work_mode;
};
    

/*20.开关量告警输出*/
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

/*21.巡航路径配置*/
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

/*22.巡航计划时间*/
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
	Uint8   plan_type;      /* 周计划 or 日计划 平台使用 */
	Uint8   reserved;
	CHAR    cruise_plan_name[MAX_NAME_LEN];
};

/*23.巡航计划例外时间*/
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

/*24.存储基本信息*/
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

/*25.IPSAN存储配置*/
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


/*26.告警存储配置*/
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

/*27.存储计划时间*/
struct storage_plan_config
{
	Uint8   vin_channel_index;
	Uint8   stream_type;
	Schedule_t  plan_time_schedule[7];
	Uint8    enable_plan;
	Uint8   plan_type;      /* 周计划 or 日计划 平台使用*/
	Uint8   reserved[2];
	CHAR    storage_plan_name[MAX_NAME_LEN];
};


/*28.存储计划例外时间*/
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

/*29.告警联动表配置*/
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


/*30.联动动作表*/
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

/*31.布防策略时间*/
struct alarm_plan_config
{
	Uint32  param1;
	Uint32  param2;
	Uint32  param3;
	Schedule_t  plan_time_schedule[7];
	Uint8   vin_channel_index;
	Uint8   alarm_type;
	Uint8    enable_plan;
	Uint8   plan_type;      /* 周计划 or 日计划 平台使用 */
	Uint8   reserved[2];
	CHAR    alarm_plan_name[MAX_NAME_LEN];
};

/*32.布防策略例外时间*/
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

/*33.保留未用*/
struct reserved_config
{
	Uint32 reserved[14];
};

/*34.实况恢复配置结构体*/
struct live_recover
{
	Uint8       enable;         /*是否需要恢复的标准*/
	Uint8       channel_id;     /*通道号            */
	Uint8       sub_index;      /*实况是该通道第几路*/
	Uint8       main_sub_flag;  /*主辅流            */
	Uint8		dst_ip[16];     /*目的IP,按照四个字节方式存储的*/
	Uint16      dst_port;       /*目的port          */
	Int16       trans_mode;     /*传输模式,TCP/UDP  */
	Int16       streaming_type; /*码流类型,TS/RTP   */
	Uint8       mc_flag;        /*是否组播          */
	Uint8       reserved;       /*对齐              */
};

/*35.枪机回环输出显示结构体*/
struct image_loopback_config
{ 
	Uint16  enable;     /*0x00：disable, 0x01：enable*/ 
	Uint16  loop_mode;  /*0x00: 取D1大小区域, 0x01：压缩*/ 
	Uint16  start_x;    /*起始坐标*/ 
	Uint16  start_y; 
	Uint16  end_x;      /*终止坐标*/
	Uint16  end_y; 
	Uint8   reserved[4];
};

/*36.IPC光学参数*/
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

/*获取终端设备的物理类型信息，走命令模式*/
struct get_type_info
{
    Uint32  camera_type[32];            //摄像机类型 0 -带云台 1- 不带云台
    Uint32  player_param[32*2];         //高16位代表制式，低16位代表分辨率, 实际只使用channel_num个,
                                        //高32个字节表示主流播放器参数，低32个字节表示辅流播放器参数
    Uint32  device_type;                //设备类型 0 - EC 1 - DC 2-GUN 3-BALL
    CHAR    type_name[MAX_NAME_LEN];    //设备名字 VG1001/VG1004/VC6210...
    Uint8   channel_num;                //通道个数
	Uint8   phy_id;
	Uint8	reserved[2];
	Uint32  device_model;               //设备型号名, 前16位用于区分不同协议(普通为0x0000, 电力为0x0001), 后16位填写DEVICE_NAME 
};

/* 终端web密码管理的结构体 */
struct web_passwd_config
{
	CHAR    web_passwd[IPSAN_PASSWD_LEN];
};


/* 版本号查询，走命令模式 */
struct version_report_pl
{
	CHAR   kernel_version[32];          /* version string */
	CHAR   ramdisk_version[32];         /* version string */
	CHAR   fpga_version[32];            /* version string */
	CHAR   cpld_version[32];            /* version string */
	CHAR   dsp_version[32];             /* version string */
};

/* 镜像升级返回的结果 */
struct image_update_result
{
	ret_info kernel_update_result;
   	ret_info ramdisk_update_result;
	ret_info fpga_update_result;
	ret_info cpld_update_result;	
};
/* 37.AI扩展配置*/
struct ai_inter_extend
{
	Uint32  valid_flag;
	Uint32  ai_addrcode;
	Uint32  serial_index;
	Uint32	sub_index; // 0 ~ 7 一个485上最多接8个扩展模块
	Uint32	max_num; // 该模块最后 可以接多少个子设备
	CHAR    ai_name[MAX_NAME_LEN];
};

/* 38.DI扩展配置 */
struct di_inter_extend
{
	Uint32  valid_flag;
	Uint32  di_addrcode;
	Uint32  serial_index;
	Uint32	sub_index; // 0 ~ 7 一个485上最多接8个扩展模块
	Uint32	max_num; // 该模块最后 可以接多少个子设备
	CHAR    di_name[MAX_NAME_LEN];
};

/* 39.DO扩展配置数量 */
struct do_inter_extend
{
	Uint32  valid_flag;
	Uint32  do_addrcode;
	Uint32  serial_index;
	Uint32	sub_index; // 0 ~ 7 一个485上最多接8个扩展模块
	Uint32	max_num; // 该模块最后 可以接多少个子设备
	CHAR    do_name[MAX_NAME_LEN];
};

/* 40.门禁控制器，数量485个数*8 */
struct gate_forbid_device
{
	Uint32	valid_flag;
	Uint32	dev_addrcode;
	Uint32	serial_index;
	Uint32	sub_index;
	Uint32	max_num;
	CHAR    gate_forbid_name[MAX_NAME_LEN];
};

/* 41.开关量扩展告警输入,数量485个数*8*8 */
struct sema_extern_input_config
{
	CHAR    sema_name[MAX_NAME_LEN];
	CHAR	sema_input_desc[MAX_DESC_LEN];
	BOOL	is_enable;
	Uint8	trigger_mode;
	BOOL	enable_detect;
	Uint8   work_mode;
};

/* 42.遮挡检测报警 */
struct hide_detect_alm_config
{
	Int32	enable;
	Int32	hide_detection_x;
	Int32	hide_detection_y;
	Int32	hide_detection_width;
	Int32	hide_detection_height;
};

/* 43.抓图参数配置 */
struct snapshot_config
{
	Uint8   ftpserv_ip[IPADDR_LEN];		    /* FTP服务器IP */
	CHAR    username[32];			        /* FTP服务器用户名 */
	CHAR    password[32];			        /* FTP服务器密码 */
	CHAR    path[256];                      /* FTP保存目录 */
	Uint32  num;                            /* 抓图数量1~5张 */
	Uint32  timeval;                        /* 抓图间隔50~500ms */
	Uint32  reserved[16];
};



/* **********************************************************
 *				以下结构体给电力协议使用					*
 * **********************************************************/

/* 1.添加电力协议子设备 */
struct elec_sub_dev
{
	Int64	iSubDevId;
	CHAR	szSubDevDesc[32];
	Int32	iPhyInfType; // 接口类型(0:self_di 1:ex_di 2:self_do 3:ex_do 4: self_ai 5:ex_ai)
	Int32	iPhyInfMainIdx;//自带的就是该接口在板子上的索引，扩展的指该扩展模块就在哪个485上
	Int32	iPhyInfSubIdx;//自带接口无效,扩展模块上可以接8个子设备，扩展模块的索引值
	Int32	address_code;//扩展模块的地址码	
	Int32   a1;
	Int32   a0;
};

/* 1.电力协议视频监控主设备 */
struct elec_ipc_config
{
	CHAR	szIPCName[128];//平台统一命名
	Int64	iIPCId;//平台统一编号
	Int32	iIPCMajorType;//主类型，当前为1
	Int32	iIPCMinorType;//子类型，当前为1
	CHAR	szIPCModel[32];//只读，不可更改
	CHAR	szIPCSerialID[64];//只读，不可更改
	CHAR	szIPCVerion[64];//只读，不可更改
};

/* 2.IPC服务地址信息 */
struct elec_ipc_server
{
	CHAR	szSvcIpAddr[32];
	Uint16	usSvcPort;
	Uint16	reserved;
	Int32	iHeatrBeatInterval;
};

/* 3.接入RPU配置 */
struct conn_rpu_config
{	
	Int32	iEnable;
	CHAR	svrname[128];
	CHAR	szConnPass[128];
	CHAR	szServeIpAddr[32];
	Int32	iServerPort;
}; 

/* 4.DSN服务器 */
struct dns_server
{
	char szDns[128];//可以多个，空格隔开
};

/* **********************************************************
 *				电力协议结构体结束							*
 * **********************************************************/
#pragma pack()

#ifdef __cplusplus
}
#endif
#endif   /* ----- #ifndef TER_SDK_INC  ----- */

