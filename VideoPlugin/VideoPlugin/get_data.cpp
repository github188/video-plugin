#include "stdafx.h"
#include "get_data.h"
#include "tinyxml.h"
//#include <conio.h>
#include <string.h>

char uid [10];
char cRecvBuff[1500];//udp数据包
char h264buff[1500];//转换后的数据
int flag=1;
bool play;
bool getflag;
bool audio_get_flag;
//解码的相关参数
AVFrame  *pFrame=avcodec_alloc_frame(); 
int   frameFinished;
AVCodec *codec;
AVCodecContext *c= NULL;

int port1=38000;
int userRandomId;

char ServIP[100] = "116.228.186.78";
// = "192.168.1.144";
int ServPort = 35000;

SOCKET socksrv;   //发送指令的socket
SOCKADDR_IN addrSrv;   //服务器的地址

//
char audioRTP[1500]; 
char g711buff[1500];
AVCodecContext *aCodecCtx;   
AVCodec *aCodec;                      
//

long video_id=0;
long audio_id=0;

//std::ofstream fout("C:\\Users\\hp\\Desktop\\test.txt");

void decode_initialize()     //初始化codec和c
{
	av_register_all();
	codec = avcodec_find_decoder(CODEC_ID_H264);
	if (!codec) {
		fprintf(stderr, "codec not found\n");
		exit(1);
	}
	c= avcodec_alloc_context();
	c->bit_rate = 0;
	
	c->width = 1920;
	c->height = 1080;
	c->time_base.den=25;
	c->time_base.num=1;
	c->gop_size = 12; 
	c->codec_type=::CODEC_TYPE_VIDEO;
	//c->bit_rate=9600;
	c->max_b_frames=0;
	c->pix_fmt = PIX_FMT_YUV420P;

	if(codec->capabilities&CODEC_CAP_TRUNCATED)
		c->flags|= CODEC_FLAG_TRUNCATED; 


	if (avcodec_open(c, codec) < 0)
	{
		fprintf(stderr, "could not open codec\n");
		exit(1);
	}

	//************音频解码设置**************
	aCodecCtx=avcodec_alloc_context();
	aCodecCtx->sample_rate=8000;
	aCodecCtx->channels=1;
	aCodecCtx->bit_rate=0;
	aCodec = avcodec_find_decoder(CODEC_ID_PCM_MULAW);
	if(!aCodec)
	{
		fprintf(stderr, "Unsupported codec!/n"); 
	   exit(1);
	}
	avcodec_open(aCodecCtx, aCodec);
	//**************************************


	::firstBuffer.initFirstLevelBuffer(firstbuffersize);
	::SecondBuffer.initSecondLevelBuffer(GOPSIZE);

}


DWORD WINAPI getdata(LPVOID lpParameter)
{
	//SOCKET sockListener;

	long biggest_id=0;

	itoa(userRandomId,  uid, 10 ); 
	std::string command;
	port1=38000;
	SOCKADDR_IN sin,saClient;
	int TimeOut=3000;
	int nSize,nbSize;
	int iAddrLen=sizeof(saClient);
	
	WORD wVersionRequested; 
	WSADATA wsaData; 
	int err; 
	wVersionRequested = MAKEWORD(1,1); 
	err = WSAStartup(wVersionRequested,&wsaData); 
	if ( err != 0 ) { 
		return -1; 
	} 
	if ( LOBYTE( wsaData.wVersion ) != 1 || 
		HIBYTE( wsaData.wVersion ) != 1) { 
			WSACleanup( ); 
			return -1; 
	} 

	SOCKET sockListener;    //客户端socket
	sockListener=socket(AF_INET, SOCK_DGRAM,0);
	//sin.sin_family = AF_INET;
	//sin.sin_port = htons(port1);     //固定客户端发命令的端口号
	//sin.sin_addr.s_addr = htonl(INADDR_ANY);
	//bind(sockListener,(sockaddr*)&sin,sizeof(SOCKADDR)); 

	command=command+"0,"+uid+",test";
	sendto(sockListener,command.c_str(),command.length()+1,0,(SOCKADDR*)&addrSrv,sizeof(SOCKADDR));//发送指令
	
	SOCKADDR_IN addr1;
	int len=sizeof(SOCKADDR_IN);
	getsockname(sockListener, (struct sockaddr *)&addr1, &len);

	//port1=addr1.sin_port;

	int p1 = ntohs(addr1.sin_port);
	 
	//printf("port %d get normal data\n",p1);
	printf("vedio：%d,%d\n",addr1.sin_addr,addr1.sin_port);

	::setsockopt(sockListener,SOL_SOCKET,SO_RCVTIMEO,(char*)&TimeOut,sizeof(TimeOut));



	int count=1;
	while(getflag)
   {
	   
	   count++;
	   nSize = sizeof ( SOCKADDR_IN );
	   if((nbSize=recvfrom (sockListener,cRecvBuff,1500,0,(SOCKADDR FAR *) &saClient,&nSize))==SOCKET_ERROR) //若接收失败则提示错误
	  {
		  printf("Recive Error1\n");
	  }

	   if(nbSize>0)
	   {
		   long id;
		   memcpy(&id,cRecvBuff,sizeof(long));
		   std::cout<<"id:"<<id<<std::endl;

		   firstBuffer.writeBuffer(cRecvBuff,nbSize,&biggest_id);
		   
		   //心跳信息
		   if(count%1000==0)
		   {
			   command="";
			   command=command+"3,"+uid+",test";
			   sendto(socksrv,command.c_str(),command.length()+1,0,(SOCKADDR*)&addrSrv,sizeof(SOCKADDR));
		   }
	   }
	}
	closesocket(sockListener);
	// SecondBuffer.cleanup();
	// printf("clean up:video\n");
	return 0;
}



DWORD WINAPI getAudioData(LPVOID lpParameter)
{
	std::string command;


	WORD wVersionRequested; 
	WSADATA wsaData; 
	int err; 
	wVersionRequested = MAKEWORD(1,1); 
	err = WSAStartup(wVersionRequested,&wsaData); 
	if ( err != 0 ) { 
		return -1; 
	} 
	if ( LOBYTE( wsaData.wVersion ) != 1 || 
		HIBYTE( wsaData.wVersion ) != 1) { 
			WSACleanup( ); 
			return -1; 
	} 

	SOCKET audioSockLisn=socket(AF_INET,SOCK_DGRAM,0);

	command=command+"5,"+uid+",test";
	sendto(audioSockLisn,command.c_str(),command.length()+1,0,(SOCKADDR*)&addrSrv,sizeof(SOCKADDR));


	int audioSize;
	audioPkt audioPacket;
	int ns;
	SOCKADDR_IN sock;
	//***************************************************

	while(getflag)
	{
	   ns=sizeof ( SOCKADDR_IN );
	   if((audioSize=recvfrom (audioSockLisn,audioRTP,1500,0,(SOCKADDR FAR *) &sock,&ns))==SOCKET_ERROR)
	   {
		   printf("Recive Error2\n");
	   }
		if(audioSize>0)
	   {
			//RTP_Header* rtp_header = (RTP_Header*)(audioRTP);
			//printf("sqnum: %d  timestamp:%d\n",rtp_header->seq,rtp_header->timestamp);
			printf("get the audio pkg!------%d\n",audioSize);
			int re=RTP2g711(audioSize);
			audioPacket.buffsize=re;    //有效数据的长度
			memcpy(&audioPacket.id,audioRTP,sizeof(long));

			memcpy(audioPacket.buff,g711buff,re);
			packet_queue_put(&audioq, &audioPacket);
			//std::cout<<"put:"<<re<<std::endl;
			memset(g711buff,0,1500);
			memset(audioRTP,0,1500);
	   }
	}
	closesocket(audioSockLisn);
	// printf("clean up :audio\n");
	return 0;
}


void connect()
{
//	InitializeCriticalSection(&recvLock);
	WORD wVersionRequested; 
	WSADATA wsaData; 
	int err; 

	SOCKADDR_IN saClient;

	wVersionRequested = MAKEWORD(1,1); 

	err = WSAStartup(wVersionRequested,&wsaData); 
	if ( err != 0 ) { 
		return ; 
	} 

	if ( LOBYTE( wsaData.wVersion ) != 1 || 
		HIBYTE( wsaData.wVersion ) != 1) { 
			WSACleanup( ); 
			return ; 
	}

	//AllocConsole();

	//TiXmlDocument* myDocument = new TiXmlDocument();
	//bool result = myDocument->LoadFile("config.xml");
	//TiXmlElement* rootElement = myDocument->RootElement();
	//TiXmlNode* serverNode = rootElement->FirstChild("server");
	//TiXmlNode* ipNode = serverNode->FirstChild("ip-address");
	//const char* strServIP = ipNode->ToElement()->GetText();
	////_cprintf("strServIP=%s\n", strServIP);
	//strncpy(ServIP, strServIP,strlen(strServIP));

	socksrv=socket(AF_INET,SOCK_DGRAM,0);
	addrSrv.sin_addr.S_un.S_addr=inet_addr(ServIP);  //服务器的地址
	addrSrv.sin_family=AF_INET;
	addrSrv.sin_port=htons(ServPort);
	int len=sizeof(SOCKADDR); 
}


int audio_decode_frame(AVCodecContext *aCodecCtx, unsigned char *audio_buf, int buf_size)
{
	static audioPkt pkt;
	static unsigned char *audio_pkt_data = NULL;
	static int audio_pkt_size = 0;
	int len1, data_size;
	for(;;)
	{
		while(audio_pkt_size > 0)
		{
			data_size = buf_size;
			len1 = avcodec_decode_audio2(aCodecCtx, (int16_t *)audio_buf, &data_size, audio_pkt_data, audio_pkt_size);
			if(len1 < 0)
			{ /* if error, skip frame */
				audio_pkt_size = 0;
				break;
			}
			audio_pkt_data += len1;
			audio_pkt_size -= len1;
			if(data_size <= 0)
			{ /* No data yet, get more frames */
				continue;
			} /* We have data, return it and come back for more later */
			return data_size;
		}
		if(pkt.buff)          //这个地方可能改的不对
		{
			memset(pkt.buff,0,1500);
			pkt.buffsize=0;
			//av_free_packet(&pkt);
		}

		if(quit)
		{
			return -1;
		}
		if(packet_queue_get(&audioq, &pkt, 1) < 0)
		{
			return -1;
		}
		//std::cout<<"get:"<<pkt.buffsize<<std::endl;
		//std::cout<<"size:"<<audioq.<<std::endl;
		audio_pkt_data =(unsigned char *) pkt.buff;
		audio_pkt_size = pkt.buffsize;
		audio_id=pkt.id;
		int tmp_video_id=video_id;
		while((tmp_video_id-audio_id)>100)
		{
			if(packet_queue_get(&audioq, &pkt, 1) < 0)
			{
				return -1;
			}
			audio_pkt_data =(unsigned char *) pkt.buff;
			audio_pkt_size = pkt.buffsize;
			audio_id=pkt.id;
		}
		while((audio_id-video_id)>100)
		{
			//fout<<"audio wait video:"<<audio_id<<"-----------"<<video_id<<std::endl;
			//printf("audio wait video: %d--------%d\n",audio_id,video_id);
			Sleep(5);
		}
		

	}
}


void audio_callback(void *userdata, Uint8 *stream, int len)
{
	AVCodecContext *aCodecCtx = (AVCodecContext *)userdata;
	int len1, audio_size;
	static uint8_t audio_buf[(AVCODEC_MAX_AUDIO_FRAME_SIZE * 3) / 2];
	static unsigned int audio_buf_size = 0;
	static unsigned int audio_buf_index = 0;
	while(len > 0)
	{
		if(audio_buf_index >= audio_buf_size)
		{ /* We have already sent all our data; get more */
			audio_size = audio_decode_frame(aCodecCtx, audio_buf, sizeof(audio_buf));
			if(audio_size < 0)
			{ /* If error, output silence */
				audio_buf_size = 1024; // arbitrary?
				memset(audio_buf, 0, audio_buf_size);
			}
			else
			{
				audio_buf_size = audio_size;
			}
			audio_buf_index = 0;
		}
		len1 = audio_buf_size - audio_buf_index;
		if(len1 > len)
			len1 = len;
		memcpy(stream, (uint8_t *)audio_buf + audio_buf_index, len1);
		len -= len1;
		stream += len1;
		audio_buf_index += len1;
	}
}

//RTP包转成G.711数据包
int RTP2g711(int size)
{
	const int PACKHEADLEN = sizeof(RTPHeader);
	int datalen=0;
	PRTP_header rtp_header = (PRTP_header)(audioRTP+sizeof(long));
	if(rtp_header->payloadtype==0)
	{
		datalen=size-PACKHEADLEN-sizeof(long);
		//memcpy((char*)g711buff,audioRTP,sizeof(long));
		//memcpy((char*)g711buff+sizeof(long),audioRTP+12+sizeof(long),datalen);
		memcpy((char*)g711buff,audioRTP+12+sizeof(long),datalen);
	}
	return datalen;
}