/*
 * =====================================================================================
 *       Copyright (C), 2010, islab@ZJU
 *
 *       FileName:  term_error_value.h
 *
 *		   Author:  rhk (ISLAB)
 *			 Date:	2010年11月10日 21时36分23秒 CST
 *        Version:  1.0
 *
 *    Description:  错误号枚举
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
	/* 各模块都可能发生的公共错误 */
	TERM_SDK_SUCCESS					= 0x0000,	// 没有错误
	TERM_COMMON_CHANNEL_ERROR			= 0x0001,	// 通道号错误
	TERM_CONNON_ERROR_END,
	
	/* 管理中心错误 */
	TERM_MGRCENTER_INVALID_MAGICNUM		= 0x0101,	// magicnum不匹配
	TERM_MGRCENTER_PASSWORD_ERROR		= 0x0102,	// 用户名密码错误
	TERM_MGRCENTER_USER_FULL			= 0x0103,	// 用户数已满
	TERM_MGRCENTER_NOENOUGHPRI			= 0x0104,	// 权限不足
	TERM_MGRCENTER_NOINIT				= 0x0105,	// 没有初始化
	TERM_MGRCENTER_FAIL_CONNECT			= 0x0106,	// 连接服务器失败
	TERM_MGRCENTER_SEND_ERROR			= 0x0107,	// 向服务器发送失败
	TERM_MGRCENTER_RECV_ERROR			= 0x0108,	// 向服务器接收数据失败
	TERM_MGRCENTER_UPDATEVER_ERROR		= 0x0109,	// 更新参数版本失败
	TERM_MGRCENTER_SETGROUP_ERROR		= 0x010A,	// 设置整个参数group失败
	TERM_MGRCENTER_SETITEM_ERROR		= 0x010B,	// 设置单个参数item失败
	TERM_MGRCENTER_GETGROUP_ERROR		= 0x010C,	// 获取整个参数group失败
	TERM_MGRCENTER_GETITEM_ERROR		= 0x010D,	// 获取单个参数item失败
	TERM_MGRCENTER_INVALID_GROUPID		= 0x010E,	// 无效的groupid	
	TERM_MGRCENTER_FORBID_LOGIN			= 0x010F,	// 禁止登入
	TERM_MGRCENTER_ERROR_END,

	/* 实况进程错误 */
	TERM_LIVE_NOINIT					= 0x0201,	// 没有初始化
	TERM_LIVE_CHAN_MAXLINK				= 0x0202,	// 单播实况请求时,发送端连接到对应通道的单播客户个数达到最大
	TERM_LIVE_TOTAL_MAXLINK				= 0x0203,	// 单播实况请求时,发送端连接到对应DSP的单播客户个数达到最大
	TERM_LIVE_NOCLIENT					= 0x0204,	// 单播实况终止请求时,发送端对应单播用户链表中不存在对应用户
	TERM_LIVE_RECV_STARTED				= 0x0205,	// 单播实况请求时,接收端对应通道已经在接收码流
	TERM_LIVE_RECV_STOPED				= 0x0206,	// 单播实况终止请求时,接收端对应通道不在接收码流
	TERM_LIVE_MULTICAST_STARTED			= 0x0207,	// 组播实况请求时,对用通道的码流已经在组播
	TERM_LIVE_MULTICAST_DISABLED		= 0x0208,	// 组播实况请求时,不支持组播
	TERM_LIVE_MULTICAST_JOINFAILED		= 0x0209,	// 组播实况请求时,加入组播组失败
	TERM_LIVE_MULTICAST_NOTEXIST		= 0x020A,	// 组播实况终止请求时,发送端对应用户链表中不存在组播
	TERM_LIVE_CLIENT_EXISTED			= 0x020B,	// 单播实况请求时,对应的用户已经存在
	TERM_LIVE_MAIN_SUB_INVALID			= 0x020C,	// 实况请求时,主辅流标志不合法
	TERM_LIVE_TRANS_MODE_INVALID		= 0x020D,	// 实况请求时,传输模式不合法
	TERM_LIVE_STREAMING_TYPE_INVALID	= 0x020E,	// 实况请求时,请求的码流类型不合法
	TERM_LIVE_DST_IP_INVALID			= 0x020F,	// 实况请求时,码流目的IP不合法
	TERM_LIVE_RESOLUTION_INVALID		= 0x0210,	// 实况请求时,分辨率不合法
	TERM_LIVE_FORMAT_INVALID			= 0x0211,	// 实况请求时,制式不合法
	TERM_LIVE_ERROR_END,
	
	/* 存储进程错误 */		
	TERM_RECORD_NOINIT					= 0x0301,	// 存储进程未初始化
	TERM_RECORD_NOIPSAN					= 0x0302,	// 没有IPSAN
	TERM_RECORD_IPSAN_FULL				= 0x0303,	// IPSAN满
	TERM_RECORD_IPSAN_OFFLINE			= 0x0304,	// IPSAN掉线
	TERM_RECORD_IPSAN_ERROR				= 0x0305,	// IPSAN出错
	TERM_RECORD_LOCAL_FULL				= 0x0306,	// 本地存储满
	TERM_RECORD_LOCAL_ERROR				= 0x0307,	// 本地存储出错
	TERM_RECORD_ALARM_STARTED			= 0x0308,	// 接收到手动存储命令时,正在进行告警存储
	TERM_RECORD_MANUAL_STARTED			= 0x0309,	// 接收到手动存储命令时,正在进行手动存储
	TERM_RECORD_MANUAL_STOPPED			= 0x030A,	// 接收到手动存储终止命令时,手动存储已经终止
	TERM_RECORD_ERROR_END,
	
	/* 告警进程错误 */
	TERM_ALERT_NOINIT					= 0x0401,	// 告警进程未初始化
	TERM_ALERT_ERROR_END,	

	/* PTZ、透明通道进程错误 */
	TERM_PTZ_NOINIT						= 0x0501,	// PTZ、透明通道进程未初始化
	TERM_PTZ_ALARM_STARTED				= 0x0502,	// 接收到手动PTZ命令时,正在进行告警PTZ
	TERM_PTZ_LOCKED						= 0x0503,	// 接收到手动PTZ命令时,PTZ被锁定
	TERM_PTZ_CRUISE_PATH_DISABLED		= 0x0504,	// 接收到手动PTZ命令时,巡航路径不使能
	TERM_PTZ_TRANSCHANNEL_BUILED		= 0x0505,	// 接收到建立透明通道命令时,透明通道已经建立
	TERM_PTZ_CMD_NOT_EXIST              = 0X0506,   // 接收到的PTZ命令不存在
	TERM_PTZ_CHANNEL_INVALID            = 0X0507,   // 接收到的通道号不正确
	TERM_PTZ_PATH_INVALID				= 0X0508,   // 接收到的巡航路线不正确
	TERM_PTZ_PRESET_INVALID				= 0X0509,   // 调用的预置点不正确
	TERM_PTZ_NO_CRUISE_NOW				= 0X050A,   // 没有巡航路线在走
	TERM_PTZ_TRANSCHANNEL_NOT_EXIST		= 0X050B,   // 透明通道不存
	TERM_PTZ_TRANS_SERIAL_MODE_WRONG	= 0X050C,	// 建立透明通道的串口模式不对
	TERM_PTZ_TRANS_DEV_VALID_FLAG_ERROR = 0X050D,	// 设备标识错误,1或2
	TERM_PTZ_TRANS_CHANNEL_WRONG		= 0X050E,	// 透明通道号错误，0~3
	TERM_PTZ_SERIAL_WRONG				= 0X050F,	// PTZ串口模式或索引错误
	TERM_PTZ_ERROR_END,
	
	/* 参数控制进程错误 */
	TERM_PARAMCTRL_NOINIT				= 0x0601,	// 参数控制进程未初始化
	TERM_PARAMCTRL_ERROR_END,
	
	/* 对讲进程错误 */
	TERM_AUDIOCOMMR_NOINIT				= 0x0701,	// 对讲进程未初始化
	TERM_AUDIOCOMMR_STARTED				= 0x0702,	// 语音对讲开始请求时,对讲通道已经建立
	TERM_AUDIOCOMMR_UNSTART				= 0x0703,	// 语音对讲停止请求时,对讲通道尚未建立
	TERM_AUDIOCOMMR_BROADCAST_STARTED	= 0x0704,	// 语音广播开始请求时,广播通道已经建立
	TERM_AUDIOCOMMR_BROADCAST_UNSTART	= 0x0705,	// 语音广播停止请求时,广播通道尚未建立
	TERM_AUDIOCOMMR_ERROR_END,
	
	/* 日志进程错误 */
	TERM_LOG_TFTP_PROCESS_ERROR         = 0x0800, 	// tftp命令运行错误
	TERM_LOG_TFTP_CONNECT_OVERTIME		= 0x0801,	// tftp连接超时
	TERM_LOG_ERROR_END,
	
	/* 更新进程错误 */
	TERM_VERUPDATE_NOINIT				= 0x0901,	// 更新进程未初始化
	TERM_VERUPDATE_CONNECT_TIMEOUT		= 0x0902,	// 连接FTP超时
	TERM_VERUPDATE_IMAGE_NOT_EXIST		= 0x0903,	// 镜像不存在
	TERM_VERUPDATE_IMAGE_LEN_ZERO		= 0x0904,	// 镜像大小为0
	TERM_VERUPDATE_IMAGE_TOO_LARGE		= 0x0905,	// 镜像太大
	TERM_VERUPDATE_IMAGE_LEN_INVALID	= 0x0906,	// 镜像长度与声明的长度不相符
	TERM_VERUPDATE_IMAGE_CRC_FAILED		= 0x0907,	// 镜像CRC校验出错
	TERM_VERUPDATE_IMAGE_WRITE_FAILED	= 0x0908,	// 镜像烧写出错
	TERM_VERUPDATE_IMAGE_LOGIN_FAILED   = 0x0909,   // FTP登陆失败
	TERM_VERUPDATE_UPDATING				= 0x0910,	// 已处于升级状态
	TERM_VERUPDATE_ERROR_END,
	
	/* misc进程错误 */
	TERM_MISC_NOINIT					= 0x0A01,	// misc进程未初始化
	TERM_MISC_IPMODE_INVALID			= 0x0A02,	// IP配置模式不合法
	TERM_MISC_NETIP_SET_FAILED			= 0x0A03,	// 网络参数设置失败
	TERM_MISC_NETCARDMODE_SET_FAILED	= 0x0A04,	// 网卡工作模式设置失败
	TERM_MISC_NETCARDMTU_SET_FAILED		= 0x0A05,	// 网卡MTU设置失败
	TERM_MISC_SYSTIME_SET_FAILED		= 0x0A06,	// 系统时间设置失败
	TERM_MISC_ERROR_END,
	
	/* 其它错误 */
	TERM_THREAD_CREATE_FAILED			= 0x0B01,	// 保活线程创建失败
	TERM_SOCKET_INIT_FAILED				= 0x0B02,	// 套接字创建失败
	TERM_SEND_MESSAGE_FIALED			= 0x0B03,	// 发送消息给终端失败
	TERM_REPLY_OVER_TIME				= 0x0B04,	// 网络超时
	TERM_SDK_RECVMEM_ERROR				= 0x0B05,	// 接受信息的空间太小
	TERM_SDK_KEEPALIVE_FAILED			= 0x0B06,	// 保活失败
	TERM_NULL_POINTER_ERROR				= 0x0B07,	// 空指针
	TERM_UPDATE_IMAGE_FAILED			= 0x0B08,	// 更新镜像失败
	TERM_UNKOWN_ERROR					= 0x0B09,
	TERM_ERROR_END,
}ret_info;

#ifdef __cplusplus
}
#endif
#endif   /* ----- #ifndef TERM_ERROR_VALUE_INC  ----- */

