#include "Common.h"
#include <windows.h>
#include <vector>
#include <list>


const unsigned short IFRAME=1;
const unsigned short PFRAME=2;
const unsigned short PPS=3;

const int TIMEOUT=-1;


class SecondLevelBuffer;
class FirstLevelBuffer;
class FrameCell;


class DataCell{
private:
	
	
	FrameCell * m_frame;
	CRITICAL_SECTION CS;
public:
	char m_H264Data[1500];
	int m_topsqNum;
	int m_dataSize;
	int m_sqNum;
	int m_timeStamp;
	bool m_isstart;
	bool m_isend;
	long m_id;
	unsigned short m_FrameType;
	bool m_isEmpty;
	void initDataCell();
	void writeData(char*data,int size,int sqNum,int topsqNum,int timeStamp,bool isstart,bool isend,unsigned short FrameType,long id);
	void readData(char*data,int*size,long* id);
	void remove();
};

struct MissFrameNo{
	long id;
	int sqnum;
	int timestmp;
};

class FisrtLevelBuffer{
private:
	std::vector<DataCell> m_datas;
	int m_totalSize;	
	CRITICAL_SECTION CS;
public:
	bool writeRetran(char* rtpPacket,int size);
	bool initFirstLevelBuffer(int totalSize);
	bool writeBuffer(char* rtpPacket,int size,long * biggest_id);
	int findEmptyCell(); //
	void FreeCell(DataCell* dc); //
	
};

class FrameCell{
private:
	
	std::vector<DataCell> missData;
	int m_GOPPos;
	FrameCell * m_keyframe;
public:
	bool isretaned;
	void insertMissData(DataCell);
	int m_base;
	std::list<DataCell*> m_frameData;
	bool m_isComplete;
	int m_timeStamp;

	unsigned short m_frametype;
	void init(DataCell*,int GOPPOS,unsigned short frametype);
	void addData(DataCell*,int base);
	int readData(char*,bool* checked,std::list<DataCell*>::iterator*,long* id);
	void getMissFrames(std::vector <MissFrameNo>*,int next);
	void iscomplete();
};

class SecondLevelBuffer{
	
	int m_currentGOPPos;
	int m_GOPsize;
	CRITICAL_SECTION CS;
public:
	void cleanup();
	int writeRetran(DataCell * dc);
	std::list<FrameCell> m_Frames;
	void initSecondLevelBuffer(int);
	bool writeData(DataCell*);
	FrameCell* isNewFrame(DataCell* datacell,bool *isnew);
	void checkFrameComplete(int nexttop,int timestmp=0);
	int readFrameData(FrameCell*);
};

