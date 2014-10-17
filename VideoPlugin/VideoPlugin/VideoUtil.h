#include <vector>
#include <string>
using namespace std;
#pragma once
class CVideoUtil
{
public:
	CVideoUtil();
	~CVideoUtil(void);
	void RunLiveVideo(void);
	void StopLiveVideo(void);
	void RecordVideo(void);
	bool IsLiveVideo(void);
	bool IsRecord(void);
	bool IsStarted(void);
	void StopThread(void);
	void StartThread(void);
	void SetSdlPlayer(CStatic* sdlPlayer);
	void SetFullScreen(bool bFullScreen);
	//RECT SetScreenSize(void);

private:
	std::string s_command;

	void StopThread(int runTpye);
	void StartThread(int runTpye);

	HANDLE m_hThGetData;	
	HANDLE m_hThVideoPlay;	
	HANDLE m_hThAudioData;
	HANDLE m_hThReTrans;

	DWORD  m_IdGetData;
	DWORD  m_IdVideoPlay;
	DWORD  m_IdAudioData;
	DWORD  m_IdReTrans;

	bool  m_bRecord;		//录像启动标志
	bool  m_bEndfile;		//文件结束标志
	bool  m_bLiveVideo;		//直播启动标志
	bool  m_bStarted;		//视频启动标志
public:
	void CaptureBmp(void);
	void MoveTurner(int direction);
	void ZoomScene(int operate);
	void GetServerIPList(char ipList[], vector<string> &ipvector);
	void connetToCarmer(string &strIp);
};

#define TURN_UP 1
#define TURN_DOWN 2
#define TURN_LEFT 3
#define TURN_RIGHT 4

#define SCENE_SHRINK 1
#define SCENE_AMPLIFY 2

