#include "StdAfx.h"
#include "VideoUtil.h"
#include "RetransTreater.h"
#include <string.h>
#include <sstream>
#include <atlconv.h>
#include <vector>
//#include <conio.h>

#include "sdl\SDL.h"
#include "sdl\SDL_thread.h"
#include "get_data.h"
#include <atlstr.h>

#define SDL_AUDIO_BUFFER_SIZE 1024
#define LIVE_VIDE_TYPE 1
#define RECORD_TYPE 2

using namespace std;

SDL_Overlay     *bmp;
SDL_Surface     *screen;
SDL_Rect        rect;
SDL_Event       event;

CRITICAL_SECTION m_cs;

int play_height = 406;
int play_width = 720;

bool m_bStarted = false;
bool m_bFullScreen = false;
bool m_bPrintBmp = false;

CStatic* m_Player;

// 存放ip地址
//vector<string> ipvector;

#ifdef __MINGW32__
#undef main /* Prevents SDL from overriding main() */
#endif

CVideoUtil::CVideoUtil()
	: m_bStarted(false)
	, m_bRecord(false)
	, m_bEndfile(false)
	, m_bLiveVideo(false)
{
	//AllocConsole();
	InitializeCriticalSection(&m_cs);
}


CVideoUtil::~CVideoUtil(void)
{
}

/************************************************************************/
/* 获取屏幕的大小                                                       */
/************************************************************************/
//RECT CVideoUtil::SetScreenSize(void)
//{
//	RECT rc;
//
//	EnterCriticalSection(&m_cs);
//	m_Player->GetWindowRect(&rc);
//	play_width = rc.right-rc.left;
//	play_height = rc.bottom - rc.top;
//	LeaveCriticalSection(&m_cs);
//
//	_cprintf("play_width=%d\n", play_width);
//	_cprintf("play_height=%d\n\n", play_height);
//
//	return rc;
//}

RECT SetScreenSize(void)
{
	RECT rc;

	EnterCriticalSection(&m_cs);
	m_Player->GetWindowRect(&rc);
	play_width = rc.right-rc.left;
	play_height = rc.bottom - rc.top;
	LeaveCriticalSection(&m_cs);

	//_cprintf("play_width=%d\n", play_width);
	//_cprintf("play_height=%d\n\n", play_height);

	return rc;
}


/************************************************************************/
/* 将系统时间变成字符串形式返回                                         */
/************************************************************************/
string GetFormatTime(void)
{
	SYSTEMTIME sys;//localtime
	GetLocalTime( &sys );

	//用vector保存时间信息
	vector<int> vecTime;
	vecTime.push_back(sys.wYear);
	vecTime.push_back(sys.wMonth);
	vecTime.push_back(sys.wDay);
	vecTime.push_back(sys.wHour);
	vecTime.push_back(sys.wMinute);
	vecTime.push_back(sys.wSecond);
	vecTime.push_back(sys.wMilliseconds);

	stringstream streamTmp;
	string strTime="";
	string timeTmp="";

	for (int i = 0; i < vecTime.size(); i++ )
	{
		streamTmp<<vecTime[i];
		streamTmp>>timeTmp;
		strTime+=timeTmp;

		streamTmp.clear();
		timeTmp="";
	}

	return strTime;
}

//播放程序
DWORD WINAPI vedio_play(LPVOID lpParameter)
{
	//与audio相关的SDL
	SDL_AudioSpec wanted_spec, spec;   
	wanted_spec.freq = aCodecCtx->sample_rate;
	wanted_spec.format = AUDIO_S16SYS;
	wanted_spec.channels = aCodecCtx->channels;
	wanted_spec.silence = 0;
	wanted_spec.samples = SDL_AUDIO_BUFFER_SIZE;
	wanted_spec.callback = audio_callback;
	wanted_spec.userdata = aCodecCtx;
	if(SDL_OpenAudio(&wanted_spec, &spec) < 0)
	{
		fprintf(stderr, "SDL_OpenAudio: %s/n", SDL_GetError());
		return -1;
	}
	SDL_PauseAudio(0);  //将该语句调入循环体内

	static struct SwsContext *img_convert_ctx;
	int len;
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER))
	{
		fprintf(stderr, "Could not initialize SDL - %s\n", SDL_GetError());
		exit(1);
	}

	//先设置为非全屏模式
	screen = SDL_SetVideoMode(play_width, play_height, 0, SDL_HWSURFACE | SDL_RESIZABLE | SDL_DOUBLEBUF);
	if(!screen)
	{
		fprintf(stderr, "SDL: could not set video mode - exiting\n");
		exit(1);
	}

	bmp = SDL_CreateYUVOverlay(play_width, play_height, SDL_YV12_OVERLAY, screen);

	uint8_t*buffer_ptr;
	//package pkg;
	int buf_size;
	img_convert_ctx = sws_getContext(c->width, c->height,c->pix_fmt, play_width, play_height, PIX_FMT_YUV420P, SWS_BICUBIC, NULL, NULL, NULL);
	int i=0;
	int tmp=0;
	bool tmpfull = false;

	while(play)
	{
		DWORD  dwBegin, dwEnd;  
		dwBegin = timeGetTime();  
		i++;
	
		FrameCell tempframe;
		int canread=SecondBuffer.readFrameData(&tempframe);
		int i=0;
		
		if(canread>=0)
		{
			tmp++;
			int size=0;
			bool checked=false;
			std::list<DataCell*>::iterator it;
			char data[1500];
		
			while(1)
			{
				size=tempframe.readData(data,&checked,&it,&video_id);
				buffer_ptr=(uint8_t *)data;
				
				if(size<0)break;
				while(size>0)
				{
					len=avcodec_decode_video(c, pFrame, &frameFinished,buffer_ptr, size);
					if(len<0){
						printf("frame %d error\n",tempframe.m_timeStamp);
					}
					
					if (frameFinished) 
					{
						SDL_LockYUVOverlay(bmp);

						AVPicture pict;
						pict.data[0] = bmp->pixels[0];
						pict.data[1] = bmp->pixels[2];
						pict.data[2] = bmp->pixels[1];

						pict.linesize[0] = bmp->pitches[0];
						pict.linesize[1] = bmp->pitches[2];
						pict.linesize[2] = bmp->pitches[1];

						sws_scale(img_convert_ctx, pFrame->data, pFrame->linesize,0, 1600, pict.data, pict.linesize);
						
						SDL_UnlockYUVOverlay(bmp);
						rect.x = 0;
						rect.y = 0;
						rect.w = play_width;
						rect.h = play_height;
						SDL_DisplayYUVOverlay(bmp, &rect);
						dwEnd = timeGetTime();
						
						if(35>dwEnd-dwBegin)
						{
							Sleep(35-(dwEnd-dwBegin));
						}
						else
						{
							Sleep(1);
						}

						if(m_bPrintBmp)//printscreen
						{
							m_bPrintBmp = false;
							string bmpName = "capture/";

							bmpName += GetFormatTime();
							bmpName += ".bmp";
							
							SDL_SaveBMP(screen,bmpName.c_str());
						}

						//判断窗口是否发生变化，即全屏到非全屏、非全屏到全屏的变化
						if(tmpfull!=m_bFullScreen)
						{
							Sleep(500);
							//重新获取窗口控件的大小
							SetScreenSize();
							tmpfull = m_bFullScreen;

							if (m_bFullScreen)
							{
								//设置全屏模式
								screen = SDL_SetVideoMode(play_width, play_height, 0, SDL_HWSURFACE | SDL_RESIZABLE | SDL_FULLSCREEN | SDL_DOUBLEBUF);
							} 
							else
							{
								//设置非全屏模式
								screen = SDL_SetVideoMode(play_width, play_height, 0, SDL_HWSURFACE | SDL_RESIZABLE | SDL_DOUBLEBUF);
							}

							bmp = SDL_CreateYUVOverlay(play_width, play_height, SDL_YV12_OVERLAY, screen);
							img_convert_ctx = sws_getContext(c->width, c->height,c->pix_fmt, play_width, play_height, PIX_FMT_YUV420P, SWS_BICUBIC, NULL, NULL, NULL);
						}
					}
				   size -= len;
				   buffer_ptr =buffer_ptr+ len;
				}
			}
			SDL_PollEvent(&event);
		}
	}
	SDL_CloseAudio();
	SDL_Quit();
	// printf("clean up\n");
	// SecondBuffer.cleanup();

	return 0;
}

/************************************************************************/
/* 启动视频直播                                                         */
/************************************************************************/
void CVideoUtil::RunLiveVideo(void)
{
	SetScreenSize();

	//SDL默认会自动创建绘图窗口，可以通过设置环境变量，让其在指定窗口绘图。
	char variable[256];
	sprintf(variable, "SDL_WINDOWID=0x%lx", m_Player->GetSafeHwnd());
	SDL_putenv(variable);

	if (!m_bStarted)
	{
		connect();
		srand((unsigned)time(NULL));
		userRandomId=rand();

		decode_initialize();
		
		play=true;
		getflag=true;
		m_bStarted = true;
		m_bLiveVideo = true;
		g_retran_ruuning =true;
		
		StartThread(LIVE_VIDE_TYPE);
	}
}

/************************************************************************/
/* 停止视频直播                                                         */
/************************************************************************/
void CVideoUtil::StopLiveVideo(void)
{
	if (m_bStarted)
	{
		//设置标志变量
		play=false;
		getflag=false;
		m_bStarted=false;
		m_bLiveVideo = false;
		g_retran_ruuning = false;


		s_command="";
		s_command=s_command+"1,"+uid+",test";

		sendto(socksrv,s_command.c_str(),s_command.length()+1,0,(SOCKADDR*)&addrSrv,sizeof(SOCKADDR));

		//Sleep(1000);
		StopThread(LIVE_VIDE_TYPE);

		//视频框内容清空
		m_Player->SetBitmap(NULL);
	}
}

void CVideoUtil::RecordVideo(void)
{

}

/************************************************************************/
/* 判断是否在录制视频                                                   */
/************************************************************************/
bool CVideoUtil::IsRecord(void)
{
	return m_bRecord;
}

/************************************************************************/
/* 判断程序是否启动（直播/录制）                                        */
/************************************************************************/
bool CVideoUtil::IsStarted(void)
{
	return m_bStarted;
}


void CVideoUtil::StopThread(int runTpye)
{
	if (runTpye == LIVE_VIDE_TYPE)
	{
		play = false;
		m_bStarted=false;
		m_bLiveVideo = false;
		WaitForSingleObject(m_hThVideoPlay,3000);
		
		//TerminateThread(m_hThVideoPlay,0);
		//CloseHandle(m_hThVideoPlay);
	}
	else if (runTpye == RECORD_TYPE)
	{
	}

	getflag = false;
	g_retran_ruuning = false;

	WaitForSingleObject(m_hThAudioData,2500);
	WaitForSingleObject(m_hThGetData,2500);
	WaitForSingleObject(m_hThReTrans,2500);

	SecondBuffer.cleanup();
	closesocket(socksrv);
	//TerminateThread(m_hThGetData,0);
	//CloseHandle(m_hThGetData);

	//TerminateThread(m_hThAudioData,0);
	//CloseHandle(m_hThAudioData);
}

/************************************************************************/
/* 启动线程                                                             */
/************************************************************************/
void CVideoUtil::StartThread(int runTpye)
{
	if (runTpye == LIVE_VIDE_TYPE)
	{
		m_hThGetData=CreateThread(NULL,0,getdata,0,0,&m_IdGetData);
		m_hThReTrans=CreateThread(NULL,0,RetranmitRequest,0,0,&m_IdReTrans);
		m_hThAudioData=CreateThread(NULL,0,getAudioData,0,0,&m_IdAudioData);
		m_hThVideoPlay=CreateThread(NULL,0,vedio_play,0,0,&m_IdVideoPlay);

		SetThreadPriority(m_hThGetData, THREAD_PRIORITY_ABOVE_NORMAL);
		SetThreadPriority(m_hThVideoPlay,THREAD_PRIORITY_HIGHEST );
		SetThreadPriority(m_hThAudioData, THREAD_PRIORITY_NORMAL);
	} 
	else if (runTpye == RECORD_TYPE)
	{
	}
	
}

/************************************************************************/
/* 判断是否在直播视频                                                   */
/************************************************************************/
bool CVideoUtil::IsLiveVideo(void)
{
	return m_bLiveVideo;
}


void CVideoUtil::StopThread(void)
{
	if (IsStarted())
	{
		if (IsLiveVideo())
		{
			StopThread(LIVE_VIDE_TYPE);
		} 
		else if (IsRecord())
		{
			StopThread(RECORD_TYPE);
		}
	} 
}

/************************************************************************/
/* 启动线程                                                             */
/************************************************************************/
void CVideoUtil::StartThread(void)
{
	if (IsStarted())
	{
		if (IsLiveVideo())
		{
			StartThread(LIVE_VIDE_TYPE);
		} 
		else if (IsRecord())
		{
			StartThread(RECORD_TYPE);
		}
	} 
}


void CVideoUtil::SetSdlPlayer(CStatic* sdlPlayer)
{
	m_Player = sdlPlayer;
}


void CVideoUtil::SetFullScreen(bool bFullScreen)
{
	m_bFullScreen = bFullScreen;
}



void CVideoUtil::CaptureBmp(void)
{
	m_bPrintBmp = true;
}

/************************************************************************/
/* 云台方向控制                                                         */
/************************************************************************/
void CVideoUtil::MoveTurner(int direction)
{
	switch(direction)
	{
		//向上转
		case TURN_UP:
			s_command="2,test,test,1";
			sendto(socksrv,s_command.c_str(),s_command.length()+1,0,(SOCKADDR*)&addrSrv,sizeof(SOCKADDR));
			break;

		//向下转
		case TURN_DOWN:
			s_command="2,test,test,2";
			sendto(socksrv,s_command.c_str(),s_command.length()+1,0,(SOCKADDR*)&addrSrv,sizeof(SOCKADDR));
			break;

		//向左转
		case TURN_LEFT:
			s_command="2,test,test,4";
			sendto(socksrv,s_command.c_str(),s_command.length()+1,0,(SOCKADDR*)&addrSrv,sizeof(SOCKADDR));
			break;

		//向右转
		case TURN_RIGHT:
			s_command="2,test,test,3";
			sendto(socksrv,s_command.c_str(),s_command.length()+1,0,(SOCKADDR*)&addrSrv,sizeof(SOCKADDR));
			break;
	}
}

/************************************************************************/
/* 摄像机焦距设置                                                       */
/************************************************************************/
void CVideoUtil::ZoomScene(int operate)
{
	switch(operate)
	{
		//放大
		case SCENE_AMPLIFY:
			s_command="2,test,test,5";
			sendto(socksrv,s_command.c_str(),s_command.length()+1,0,(SOCKADDR*)&addrSrv,sizeof(SOCKADDR));
			break;

		//缩小
		case SCENE_SHRINK:
			s_command="2,test,test,6";
			sendto(socksrv,s_command.c_str(),s_command.length()+1,0,(SOCKADDR*)&addrSrv,sizeof(SOCKADDR));
			break;
	}
}


void CVideoUtil::GetServerIPList(char ipList[], vector<string> &ipvector)
{
	string striplist = ipList;

	//获取服务器ip个数
	string strTotol = striplist.substr(0, striplist.find(','));

	//_cprintf("striplist.find(',')=%d\n", striplist.find(','));
	int nTotol = atoi(strTotol.c_str());
	
	striplist = striplist.substr(striplist.find(',')+1, striplist.length());

	for (int i=0; i<nTotol; i++)
	{
		int pos = striplist.find(',');
		//判断是否是最后一个ip
		if (pos != striplist.npos)
		{
			//获取每一个ip地址及端口号
			string ipAddressPort = striplist.substr(0, striplist.find(','));
			striplist = striplist.substr(striplist.find(',')+1, striplist.length());

			ipvector.push_back(ipAddressPort);

			//ipport = ipaddress.substr(ipaddress.find(':'), ipaddress.length());
			//ipaddress = ipaddress.substr(0, ipaddress.find(':')-1);

			//int nport = atoi(ipport.c_str());

			//strncpy(ServIP, ipaddress.c_str(),strlen(ipaddress.c_str()));
			//ServPort = nport;
			
		}
		else
		{
			string ipAddressPort = striplist;
			ipvector.push_back(ipAddressPort);
		}
	}
}


void CVideoUtil::connetToCarmer(string &strIp)
{
	string ipport = strIp.substr(strIp.find(':')+1, strIp.length());
	ServPort = atoi(ipport.c_str());
	//ipaddress = ipaddress.substr(0, ipaddress.find(':')-1);

	string servip = strIp.substr(0, strIp.find(':'));
	strncpy(ServIP, servip.c_str(),strlen(servip.c_str()));

	//connect();
}
