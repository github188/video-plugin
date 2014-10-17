/*帧类型*/
#define FRAME_I_TYPE	0x03   //NRI:2 = 11b: I Frame
#define FRAME_P_TYPE	0x02   //NRI:2 = 10b: P Frame
#define FRAME_B_TYPE	0x02
/*PPS SPS 包头*/
#define FRAME_I_SPS     0x07
#define FRAME_I_PPS     0x08
/*三种I帧标识*/
#define RTSP_FRAME_I_TYPE    0x67
#define RTSP_FRAME_IMID_TYPE 0x68
#define RTSP_FRAME_IEND_TYPE 0x65
#define RTSP_FRAME_P_TYPE	 0x41
#define RTSP_FRAME_PONU_TYPE 0x61

//帧标志
typedef enum __FRAME_FLAG_
{
	FRAME_MID		= 0,	/* 帧中间 */
	FRAME_START		= 1,	/* 帧头 */
	FRAME_END		= 2,	/* 帧尾 */
	FRAME_START_END	= 3		/* 既是帧头，又是帧尾 */
}FRAME_FALG;

typedef struct RTPHeader
{
    unsigned char csrccount:4;
    unsigned char extension:1;
    unsigned char padding:1;
    unsigned char version:2;
    unsigned char payloadtype:7;
    unsigned char marker:1;       
    unsigned short seq;
    unsigned int timestamp;
    unsigned int ssrc;
} RTP_Header, *PRTP_header;

typedef struct _RTPPAYLOAD_HEADER_
{
	unsigned char Type1:5;
	unsigned char NRI:2;
	unsigned char F:1;
	unsigned char Type2:5;
	unsigned char R:1;
	unsigned char E:1;
	unsigned char S:1;	
}rtppayload_header;