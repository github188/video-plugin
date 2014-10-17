#include "stdafx.h"
#include "RetransTreater.h"
RetransTreator g_retrans_treator;

RetransTreator::RetransTreator(){
	InitializeCriticalSection(&m_CS);
	for(int i=0;i<RESIZE;i++){
		m_units[i].isvalid = false;
	}
	m_len = 0;
}

int RetransTreator::addRetransRequest(RetransUnit retran_unit){
	EnterCriticalSection( &m_CS);
	if(m_len>=RESIZE){
		LeaveCriticalSection(&m_CS);
		return RETFULL;
	}

	for(int i=0;i<RESIZE;i++){
		if (m_units[i].isvalid == false){
			m_units[i].isvalid = true;
			m_units[i].last_check_time = 0;
			m_units[i].self_timestmp = retran_unit.self_timestmp;
			m_units[i].top_id = retran_unit.top_id;
			m_units[i].top_sqnum = retran_unit.top_sqnum;
			m_units[i].self_sqnum = retran_unit.self_sqnum;
			m_len++;
			LeaveCriticalSection( &m_CS);
			return AddRETSUSS;
		}
	}
	LeaveCriticalSection( &m_CS);
	return RETFULL;
}

std::vector<RetransUnit>RetransTreator:: getReTransList(int checkgap){
	std::vector<RetransUnit> result;
	DWORD currenttime = timeGetTime();
	int timeline = timeGetTime()-checkgap;
	EnterCriticalSection( &m_CS);
	int count= m_len; 
	for(int i=0;i<RESIZE&&count>0;i++){
		if(m_units[i].isvalid){
			count--;
			if(m_units[i].last_check_time<=timeline){
				m_units[i].last_check_time = currenttime;
				RetransUnit tmpUnit;
				tmpUnit.self_timestmp = m_units[i].self_timestmp;
				tmpUnit.top_id = m_units[i].top_id;
				tmpUnit.top_sqnum = m_units[i].top_sqnum;
				tmpUnit.self_sqnum = m_units[i].self_sqnum;
				result.push_back(tmpUnit);
			}
		}
	}
	LeaveCriticalSection( &m_CS);
	return result;
}

int RetransTreator:: retransDataArrive(RetransUnit retran_unit){
	EnterCriticalSection(&m_CS);
	int count= m_len; 
	for(int i=0;i<RESIZE&&count>0;i++){
		if(m_units[i].isvalid){
			count --;
			if(m_units[i].self_sqnum == retran_unit.self_sqnum &&
			m_units[i].self_timestmp == retran_unit.self_timestmp){
				m_units[i].isvalid = false;
				m_len --;
				LeaveCriticalSection(&m_CS);
				printf("retran success size:%d\n",this->m_len);
				return RETRANSUCC;
			}
		}
	}
	LeaveCriticalSection(&m_CS);
	return RETRANTIMEOUT;
}

int RetransTreator::cleanTimeOut(int timestmp){
	EnterCriticalSection(&m_CS);
	int count= m_len; 
	for(int i=0;i<RESIZE&&count>0;i++){
		if(m_units[i].isvalid){
			count --;
			if(m_units[i].self_timestmp ==timestmp ){
				m_units[i].isvalid = false;
				m_len--;
			}
		}
	}
	LeaveCriticalSection(&m_CS);
	return 0 ;
}
