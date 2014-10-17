#ifndef _GET_DATA_H
#define _GET_DATA_H

#include "Common.h"
#include <queue>
#include <windows.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include "PlayerBuffer.h"
#include "audioPktQueue.h"
#include "BuffQueue.h"
#include "RetransTreater.h"
#include <Mmsystem.h>   
#ifdef __cplusplus
extern "C" {
#endif
	#include "libavcodec/avcodec.h"
	#include "libavformat/avformat.h"
	#include "libavutil/avutil.h"
	#include "libswscale/swscale.h"
	#include "libavutil/fifo.h"
#ifdef __cplusplus
}
#endif


#define	 MAX_BUFFER_LEN 65536
#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib, "Winmm.lib")  

extern char cRecvBuff[1500];//udp���ݰ�
extern char h264buff[1500];//ת���������

//
extern char audioRTP[1500];  //���յ���audioRTP��
extern char g711buff[1500];   //��audioRTPת����G.711��
extern AVCodecContext *aCodecCtx;    //audio�ı����������
extern AVCodec *aCodec;                       //audio�ı������

void audio_callback(void *userdata, Uint8 *stream, int len);
int audio_decode_frame(AVCodecContext *aCodecCtx, unsigned char *audio_buf, int buf_size);
int RTP2g711(int size);
//
extern int flag;
extern bool play;
extern bool getflag;
extern bool audio_get_flag;
extern	char uid [10];
//�������ز���
extern AVFrame  *pFrame; 
extern int   frameFinished;
extern AVCodec *codec;
extern AVCodecContext *c;

//extern CRITICAL_SECTION recvLock;
extern int port1;
extern int userRandomId;

extern SOCKET socksrv;   //����ָ���socket
extern SOCKADDR_IN addrSrv;   //�������ĵ�ַ
//extern BuffQueue h264_buffer;

//int RTP2h264(int size);
void decode_initialize() ;
DWORD WINAPI getdata(LPVOID lpParameter);
DWORD WINAPI getAudioData(LPVOID lpParameter);
void connect();

extern SecondLevelBuffer SecondBuffer;
extern  FisrtLevelBuffer firstBuffer;
extern const int firstbuffersize;
extern const int GOPSIZE;
extern const int FrameBufferSize;

extern char ServIP [];
extern int ServPort;

extern long video_id;
extern long audio_id;

extern std::ofstream fout;

#endif