#ifndef RETRANSTREATOR
#define RETRANSTREATOR
#include "get_data.h"

#define RESIZE 500

#define AddRETSUSS 1
#define RETFULL 0

#define RETRANSUCC 2
#define RETRANTIMEOUT 3

class RetransUnit{
public:
    int self_timestmp;
	bool isvalid;
	DWORD last_check_time;
	int top_sqnum;
	int top_id;
	int self_sqnum;
};

class RetransTreator{
public:
	RetransTreator();
	int addRetransRequest(RetransUnit);
    std::vector<RetransUnit> getReTransList(int checkgap);
	int retransDataArrive(RetransUnit);
	int cleanTimeOut( int timestmp);
private:
	int m_len ;
	RetransUnit m_units[RESIZE];
	CRITICAL_SECTION m_CS;
};

extern RetransTreator g_retrans_treator;
extern DWORD WINAPI RetranmitRequest(LPVOID lpParameter);
extern bool g_retran_ruuning;
#endif