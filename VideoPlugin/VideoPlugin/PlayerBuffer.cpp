#include "stdafx.h"
#include "get_data.h"
int RTP2h264(char * rtpdata,int size,char * h264buff,int* sqnum,int* timeStamp, bool * isstart, bool * isend,unsigned short* FrameType,long * id,int *topsqnum);

SecondLevelBuffer SecondBuffer;
FisrtLevelBuffer firstBuffer;
const int firstbuffersize=20000;
const int GOPSIZE=25;
const int FrameBufferSize=3;
//CRITICAL_SECTION recvLock;

int rrt=20;

bool FisrtLevelBuffer::initFirstLevelBuffer(int totalSize){
	bool result =true;
	m_datas=std::vector<DataCell>(totalSize);
	for(int i=0;i<m_datas.size();i++){
		m_datas[i].initDataCell();
	}
	m_totalSize=totalSize;
	InitializeCriticalSection(&CS);
	return result;
}

void DataCell::initDataCell(){
	InitializeCriticalSection(&CS);
	m_isEmpty=true;
}
void DataCell::writeData(char*data,int size,int sqNum,int topsqNum, int timeStamp,bool isstart,bool isend,unsigned short FrameType,long id){
	EnterCriticalSection( &CS);
	memcpy(m_H264Data,data,size);
	m_sqNum=sqNum;
	m_topsqNum=topsqNum;
	m_timeStamp=timeStamp;
	m_dataSize=size;
	m_isEmpty=false;         //标记DataCell非空
	m_isstart=isstart;
	m_isend=isend;
	m_FrameType=FrameType;
	m_id=id;
	LeaveCriticalSection( &CS);
}

void DataCell::readData(char*data,int*size,long*id){
	EnterCriticalSection( &CS);
	memcpy(data,m_H264Data,m_dataSize);
	*size=m_dataSize;
	*id=m_id;
	LeaveCriticalSection( &CS);
}


void  DataCell::remove(){
	EnterCriticalSection( &CS);
	m_isEmpty=true;
	m_dataSize=0;
	m_frame=NULL;
	LeaveCriticalSection( &CS);
}

int FisrtLevelBuffer::findEmptyCell(){
	for(int i=0;i<m_totalSize;i++){
		if(m_datas[i].m_isEmpty)return i;
	}
	return -1;
}

void  FisrtLevelBuffer::FreeCell(DataCell* dc){
	EnterCriticalSection( &CS);
	dc->remove();
	LeaveCriticalSection( &CS);
}

bool FisrtLevelBuffer::writeBuffer(char* rtpPacket,int size,long * biggest_id){     //输入是RTP包的数据和长度
	//缓冲区溢出，需要补充动态调整缓冲区策略
	EnterCriticalSection( &CS);
	int emptyPos=findEmptyCell();
	if(emptyPos<0){
		printf("no empty");
		LeaveCriticalSection( &CS);
		return false;
	}
	
	char h264buff[1500];
	int sqnum; 
	int timeStamp;
	bool  isstart=false;
	bool isend=false;
	int h264size;
	int topSqnum;
	unsigned short FrameType;
	long id;
	h264size=RTP2h264(rtpPacket,size,h264buff,&sqnum,&timeStamp,&isstart,&isend,&FrameType,&id,&topSqnum);   //收到的RTP包转成264数据包
	

	if(id < *biggest_id){
		RetransUnit tmpUnit;
		tmpUnit.self_sqnum = sqnum;
		tmpUnit.self_timestmp = timeStamp;
	    g_retrans_treator.retransDataArrive(tmpUnit);
	}
	else{
		*biggest_id = id;
	}

	m_datas[emptyPos].writeData(h264buff,h264size,sqnum,topSqnum,timeStamp,isstart,isend,FrameType,id);
	if(!SecondBuffer.writeData(&m_datas[emptyPos])){                         //?
		//2级缓冲写入失败，删除回滚
		//printf("roll back type:%d\n",m_datas[emptyPos].m_FrameType);
		m_datas[emptyPos].remove();
		
	}
	LeaveCriticalSection( &CS);
	return true;
}



bool FisrtLevelBuffer::writeRetran(char* rtpPacket,int size){
	
	EnterCriticalSection( &CS);
	
	int emptyPos=findEmptyCell();
	if(emptyPos<0){
		printf("no empty");
		LeaveCriticalSection( &CS);
		return false;
	}

	char h264buff[1500];
	memset(h264buff,0,1500);
	int sqnum; 
	int timeStamp;
	bool  isstart=false;
	bool isend=false;
	int h264size;
	unsigned short FrameType;
	long id;
	int topsqnum;
	h264size=RTP2h264(rtpPacket,size,h264buff,&sqnum,&timeStamp,&isstart,&isend,&FrameType,&id,&topsqnum);
	if(sqnum<0){    //？
		
		LeaveCriticalSection( &CS);
		return true;
	}

	m_datas[emptyPos].writeData(h264buff,h264size,sqnum,topsqnum,timeStamp,isstart,isend,FrameType,id);
	//printf("retran write second buff sqnum:%d timestmp:%d size:%d id:%ld %c\n",sqnum,timeStamp,h264size,id,h264buff[h264size-10]);


	
	if(SecondBuffer.writeRetran(&m_datas[emptyPos])==TIMEOUT){    //?
		//printf("retran roll back\n");
		m_datas[emptyPos].remove();     //这样就可以删除掉datacell
		LeaveCriticalSection( &CS);
		return false;
	}
	LeaveCriticalSection( &CS);
	return true;
}


struct MissFrameNoAndTopNum{
	std::vector <MissFrameNo> *missFramenums;
	int nexttop;
};

DWORD WINAPI Retan(LPVOID lpParameter){

	//TODO
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

	MissFrameNoAndTopNum* ms=(MissFrameNoAndTopNum*)lpParameter;
	if(ms->missFramenums->size()<=0)return 0;
	int nexttop=ms->nexttop;
	//printf("try getmiss data ,sqnum is:%d timestmp:%d \n",ms->missFramenums->front().sqnum,ms->missFramenums->front().timestmp);



	char command[1500];     //记录内容为 丢包数+id+序列号+时间戳
	int num=0;                        //command的字节数
	int retranport=35010;

	SOCKADDR_IN sin,saClient;
	SOCKET sockListener;    //客户端socket
	sockListener=socket(AF_INET, SOCK_DGRAM,0);
	SOCKADDR_IN csin,caddrSrv;
	//客户端地址
    /*csin.sin_family = AF_INET;
    csin.sin_port = htons(40000); 
	csin.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	if(bind(sockListener,(sockaddr*)&csin,sizeof(SOCKADDR))==-1)
	{
		printf("bind error");
	}
	*/
	caddrSrv.sin_addr.S_un.S_addr=inet_addr(ServIP);  //服务器的地址
    caddrSrv.sin_family=AF_INET;
    caddrSrv.sin_port=htons(retranport);

	int size=ms->missFramenums->size();
	if(size>=100)size=100;    //为什么？
	memcpy(command,&size,sizeof(size));
	num=num+sizeof(ms->missFramenums->size());
	int timestmp;
	int i=0;
	//printf("need size is %d\n",ms->missFramenums->size());
	while(i<ms->missFramenums->size()&&i<=100){
		//printf("need %d %d  ",(*ms->missFramenums)[i].sqnum,(*ms->missFramenums)[i].timestmp);
		long id=(*ms->missFramenums)[i].id;
		memcpy(command+num,&id,sizeof(long));
		num=num+sizeof(id);

		int sqnum=(*ms->missFramenums)[i].sqnum;
		memcpy(command+num,&sqnum,sizeof(sqnum));
		num=num+sizeof(sqnum);

		timestmp=(*ms->missFramenums)[i].timestmp;
		memcpy(command+num,&timestmp,sizeof(timestmp));
		num=num+sizeof(timestmp);
		i++;
	}
	
	//printf("send retran comm\n");
	//EnterCriticalSection( &recvLock);
	sendto(sockListener,command,num,0,(SOCKADDR*)&caddrSrv,sizeof(SOCKADDR));

	::setsockopt(sockListener,SOL_SOCKET,SO_RCVTIMEO,(char*)&rrt,sizeof(rrt));
	//int bu=50000;
	//setsockopt(socksrv,SOL_SOCKET,SO_RCVBUF ,(char*)&bu,sizeof(bu));
	//DWORD time1=timeGetTime();
	int missnum=i;
	delete ms->missFramenums;
	delete ms;
	while(missnum>0){
		int nbSize=0;
		int nSize=sizeof ( SOCKADDR_IN );
		if((nbSize=recvfrom (sockListener,cRecvBuff,1500,0,(SOCKADDR*) &saClient,&nSize))==SOCKET_ERROR){
			//printf("get single retran package timeout\n");
			break;
		}

		unsigned short port;
		SOCKADDR_IN addr;
		int len=sizeof(SOCKADDR_IN);
        getsockname(sockListener, (struct sockaddr *)&addr, &len);
		int port1 = ntohs(addr.sin_port);

		int countnum;
		memcpy(&countnum,cRecvBuff,sizeof(int));
		char buff[1500];
		memcpy(buff,cRecvBuff+sizeof(int),nbSize-sizeof(int));
        long tmpid;
		memcpy(&tmpid,buff,sizeof(long));
		//printf("port %d get retran from port %d size:%d countnum is %d id is %ld\n",port1,ntohs(saClient.sin_port),nbSize,countnum,tmpid);
		//nbSize--;
		//int code=0;
		//memcpy(&code,buff,sizeof(int));
		//if(code==-200)return 0;
		/*char h264buff[1500];
	    int sqnum; 
	    int timeStamp;
		long id;
		bool  isstart=false;
	    bool isend=false;
		int h264size;
	    unsigned short FrameType;
	    h264size=RTP2h264(cRecvBuff,nbSize,h264buff,&sqnum,&timeStamp,&isstart,&isend,&FrameType,&id);*/
		//printf("get retran sqnum:%d\n",sqnum);
		//memset(cRecvBuff,0,nbSize);
		//printf("before write\n");
		
		//printf("end write\n");
		bool result=firstBuffer.writeRetran(buff,nbSize-sizeof(int));
		if(!result){
			//printf("retran time out giveup! timestp: %d\n",timestmp);
			//LeaveCriticalSection( &recvLock);
			return 0;

		}
		
		missnum--;
	}
	//LeaveCriticalSection( &recvLock);
	::closesocket(sockListener);
	SecondBuffer.checkFrameComplete(nexttop,timestmp);
	//printf("out while\n");
	return 0;
}

int SecondLevelBuffer::writeRetran(DataCell * dc){
	if(dc->m_sqNum<0){
		//printf("retran sqnum error\n");
		return 0;
	}
	EnterCriticalSection(&CS);
	std::list<FrameCell>::iterator it=m_Frames.begin();
	for(;it!=m_Frames.end();it++){
		if(it->m_timeStamp==dc->m_timeStamp){
			/*DataCell dc;
			dc.initDataCell();
			dc.writeData(h264buff,size,sqnum,timeStamp,isstart,isend,FrameType,id);
			*/
			
			//printf("retran write second buff\n");
			it->isretaned=true;
			it->addData(dc,it->m_base);
			//printf("retran checkcomplete\n");
	        it->iscomplete();
			//printf("retran after checkcomplete\n");
			LeaveCriticalSection(&CS);
			return 0;
		}
	}

	LeaveCriticalSection(&CS);
	return TIMEOUT;
}


void SecondLevelBuffer:: checkFrameComplete(int nexttop,int timestmp){
	EnterCriticalSection( &CS);
	if(timestmp==0){
	if(m_Frames.size()>0){
		if(m_Frames.back().m_isComplete){
			LeaveCriticalSection( &CS);
			return;
		
		}
		std::vector <MissFrameNo> missFramenums;
		
		m_Frames.back().getMissFrames(&missFramenums,nexttop);
		MissFrameNoAndTopNum * ms=new MissFrameNoAndTopNum();
		ms->missFramenums=new std::vector <MissFrameNo>(missFramenums.size());
		ms->nexttop=nexttop;
		for(int j=0;j<missFramenums.size();j++){
			/*(*ms->missFramenums)[j].id=missFramenums[j].id;
			(*ms->missFramenums)[j].sqnum=missFramenums[j].sqnum;
			(*ms->missFramenums)[j].timestmp=missFramenums[j].timestmp;*/
			RetransUnit tmpUnit;
			tmpUnit.top_id = missFramenums[j].id;
			tmpUnit.self_sqnum = missFramenums[j].sqnum;
			tmpUnit.self_timestmp = missFramenums[j].timestmp;

			g_retrans_treator.addRetransRequest(tmpUnit);

		}
		delete ms->missFramenums;
		delete ms;
		LeaveCriticalSection( &CS);
		/*HANDLE hThread1;
		DWORD  ThreadID;
		hThread1=CreateThread(NULL,0,Retan,ms,0,&ThreadID);
		::CloseHandle(hThread1);*/
		
		return;
	}
	}
	else{
		std::list<FrameCell>::iterator it=m_Frames.begin();
	for(;it!=m_Frames.end();it++){
		
		if(it->m_timeStamp==timestmp){
			if(it->m_isComplete)
			{
				//printf("again commplete! %d\n",timestmp); 
			LeaveCriticalSection( &CS);
			return;
			}
			//printf("again not  commplete %d\n",timestmp);
			std::vector <MissFrameNo> missFramenums;
			
		    it->getMissFrames(&missFramenums,nexttop);

			MissFrameNoAndTopNum * ms=new MissFrameNoAndTopNum();
		ms->missFramenums=new std::vector <MissFrameNo>(missFramenums.size());
		ms->nexttop=nexttop;
		for(int j=0;j<missFramenums.size();j++){
			/*(*ms->missFramenums)[j].id=missFramenums[j].id;
			(*ms->missFramenums)[j].sqnum=missFramenums[j].sqnum;
			(*ms->missFramenums)[j].timestmp=missFramenums[j].timestmp;*/
			RetransUnit tmpUnit;
			tmpUnit.top_id = missFramenums[j].id;
			tmpUnit.self_sqnum = missFramenums[j].sqnum;
			tmpUnit.self_timestmp = missFramenums[j].timestmp;

			g_retrans_treator.addRetransRequest(tmpUnit);
		}
		delete ms->missFramenums;
		delete ms;
		LeaveCriticalSection( &CS);
		    /*HANDLE hThread1;
		    DWORD  ThreadID;
		    hThread1=CreateThread(NULL,0,Retan,ms,0,&ThreadID);
		    ::CloseHandle(hThread1);*/
		return;
		}

	}
		//printf("again check and giveup %d\n",timestmp);
	}
	LeaveCriticalSection( &CS);
	return;
}



bool SecondLevelBuffer::writeData(DataCell* datacell){
	if(datacell->m_sqNum<0){
		
		//printf("inserting data sqnum error\n");
		return false;
	}
	EnterCriticalSection( &CS);
	int size=m_Frames.size();
	bool isnew=false;
	FrameCell * cframe=isNewFrame(datacell,&isnew);
	if(isnew){
		if(m_Frames.size()==0&&datacell->m_FrameType!=PPS){
			LeaveCriticalSection( &CS);
			return false;
		}
		checkFrameComplete(datacell->m_topsqNum);
		FrameCell fcell;
		if(datacell->m_FrameType==::IFRAME)m_currentGOPPos=0;
		fcell.init(datacell,m_currentGOPPos,datacell->m_FrameType);
		fcell.m_base=datacell->m_sqNum;
		m_currentGOPPos++;
		m_Frames.push_back(fcell);	
		//printf("%d\n",m_Frames.size());
		//printf("leave cs\n");
		LeaveCriticalSection( &CS);
	}
	else{
		if(cframe!=NULL){
		    cframe->addData(datacell,cframe->m_base);
			LeaveCriticalSection( &CS);
	        return true;
		}
		else{
	  LeaveCriticalSection( &CS);
	    return false;
		}
	}

}

FrameCell* SecondLevelBuffer::isNewFrame(DataCell* datacell,bool *isnew){
	//EnterCriticalSection( &CS);
	if(m_Frames.size()==0)
	{
		*isnew=true;
		//LeaveCriticalSection( &CS);
		return NULL;
	}
	*isnew=true;
	std::list<FrameCell>::iterator it=m_Frames.begin();
	for(;it!=m_Frames.end();it++){
		if(it->m_timeStamp==datacell->m_timeStamp){
			*isnew=false;
			//LeaveCriticalSection( &CS);
			//printf("not new frame\n");
			return &(*it);
		}
		//if(it->m_timeStamp<datacell->m_timeStamp){
			//printf("it->m_timeStamp:%d datacell->m_timeStamp:%d\n",it->m_timeStamp,datacell->m_timeStamp);
		 
			*isnew=true;
		//}
	}
	//LeaveCriticalSection( &CS);
	/*if(*isnew){
	int num=((datacell->m_timeStamp>>16 )&0x0000ffff)/4096;
	  printf("stmp :%d %d\n",num,datacell->m_timeStamp);
	}*/
	return NULL;
}





void FrameCell::getMissFrames(std::vector <MissFrameNo>* MissCells,int nexttop){
	if(!m_frameData.front()->m_isstart){
		int base=m_frameData.front()->m_topsqNum;
		int num=m_frameData.front()->m_sqNum;
		long id=m_frameData.front()->m_id;
		int tmp=m_frameData.front()->m_timeStamp;
		while(base!=num){
			MissFrameNo miss;
			miss.id=id;
			miss.sqnum=base;
			miss.timestmp=tmp;
			MissCells->push_back(miss);
			base++;
			if(base>255)base=0;
		}
	}
	if(!m_frameData.back()->m_isend){
		int base=m_frameData.back()->m_sqNum;
		int num=nexttop;
		long id=m_frameData.back()->m_id;
		int tmp=m_frameData.back()->m_timeStamp;

		while(base!=num){
			MissFrameNo miss;
			miss.id=id;
			miss.sqnum=base;
			miss.timestmp=tmp;
			MissCells->push_back(miss);
			base++;
			if(base>255)base=0;
		}
	}
	
	std::list<DataCell*>::iterator it=m_frameData.begin();
	int base=(*it)->m_sqNum;
	for(it++;it!=m_frameData.end();it++){
		int num=(*it)->m_sqNum;
		base++;
		if(base>255)base=0;
		while(base!=num){
			MissFrameNo miss;
			miss.id=(*it)->m_id;
			miss.sqnum=base;
			miss.timestmp=(*it)->m_timeStamp;
			MissCells->push_back(miss);
			base++;
			if(base>255)base=0;
		}
	}

}


void FrameCell::init(DataCell* dc,int GOPPOS,unsigned short frametype){
	isretaned=false;
	m_isComplete=false;
	m_timeStamp=dc->m_timeStamp;
	m_frametype=frametype;
	m_GOPPos=GOPPOS;
	m_frameData.push_back(dc);
	if(dc->m_isstart==false)printf("miss start on recieve\n");
}


bool isLarger(int L,int S,int base){
	int i=L;
	int j=S;
	if(i==base)return false;
	if(j==base)return true;
	if(i>base&&j<base)return false;
	if(i<base&&j>base)return true;
	if((i<base&&j<base)||(i>base&&j>base)){
		if(i>j)return true;
		else return false;
	}

	return false;
}


void  FrameCell:: addData(DataCell* dc,int b){
	//m_frameData.push_back(dc);
	std::list<DataCell*>::iterator it=m_frameData.begin();
	//std::list<DataCell*>::iterator it2=m_frameData.begin();
	
	bool isAdded=false;
	for(;it!=m_frameData.end();it++){
		//it2++;
		if((*it)->m_sqNum==dc->m_sqNum){
			isAdded=true;
			//printf("重复修正\n");
			break;
		}
		
		if(isLarger((*it)->m_sqNum,dc->m_sqNum,dc->m_topsqNum)){
			m_frameData.insert(it,dc);
			isAdded=true;
			if((*it)->m_sqNum<0){
				printf("error\n");
			}
			//printf("乱序修正 %d %d %d\n",(*it)->m_sqNum,dc->m_sqNum,dc->m_timeStamp);
			break;
		}
	}
		if(!isAdded){
			m_frameData.insert(m_frameData.end(),dc);
		}
	
	
	//需要添加，一帧有没有完整
	iscomplete();
	return;
}

void FrameCell::iscomplete(){
	if(m_frameData.front()->m_isstart==false){
		//printf("miss start\n");
		return ;
	}
	if(m_frameData.back()->m_isend==false)
	{
		m_isComplete=false;return;
	}
   std::list<DataCell*>::iterator it=m_frameData.begin();
	int base=(*it)->m_sqNum;
	bool iscomplete=true;
	
	for(it++;it!=m_frameData.end();it++){
		int num=(*it)->m_sqNum;
		if(base>num&&base-num>=255){
			base=(*it)->m_sqNum;
			base=num;
			//continue;
		}
			//std::cout<<(*it)->m_sqNum/256<<"   "<<num/256<<std::endl;
		else{
			if(num-base==1){
			base=num;
			continue;
			}
			
			iscomplete=false;
			//printf("miss %d %d\n",num,base);
			base=num;
			//break;
			
		}

			
	}
		//num=(*it)->m_sqNum;
	
	m_isComplete=iscomplete;
}


int count=0;
int FrameCell:: readData(char* data,bool* checked,std::list<DataCell*>::iterator *it,long* id){
	
	if(!*checked){
		/*if(isretaned){
			std::list<DataCell*>::iterator tmpit;
			 for(tmpit=m_frameData.begin();tmpit!=m_frameData.end();tmpit++){
			         firstBuffer.FreeCell(*tmpit);
		       }
			return -1;
		}*/
		if(!m_isComplete)
			{
				//printf("read miss %d\n",this->m_timeStamp);
				if(m_frametype!=PFRAME){
					
					
					std::list<DataCell*>::iterator tmpit;
					if((*(m_frameData.begin()))->m_isstart==false)printf("key frame miss miss start on read\n");
					else{
						if((m_frameData.back())->m_isend==false){
								printf("key frame miss end on read\n");
							}
						    else{
								if(isretaned)
							   printf("key frame %d still miss \n",this->m_timeStamp);
								else{
							   printf("key frame %d  miss but no retran\n",this->m_timeStamp);
								}
							}
					}
					 for(tmpit=m_frameData.begin();tmpit!=m_frameData.end();tmpit++){
			         firstBuffer.FreeCell(*tmpit);
		       }
		       return -1;
		           
					
				}
				else{
					
					if((*(m_frameData.begin()))->m_isstart==false)printf("P frame miss  start on read\n");

						else{
							if((m_frameData.back())->m_isend==false){
								printf("P frame miss end on read\n");
							}
						   if(isretaned)
							   printf("P frame %d still miss \n",this->m_timeStamp);
								else{
							   printf("P frame %d  miss but no retran\n",this->m_timeStamp);
								}	
					}
					
				
			 std::list<DataCell*>::iterator tmpit;
		        for(tmpit=m_frameData.begin();tmpit!=m_frameData.end();tmpit++){
			   firstBuffer.FreeCell(*tmpit);
		       }
		       return -1;
				}
			
				
		    }
		*checked=true;
		*it=m_frameData.begin();
		
	}
	if(*it==m_frameData.end())
	{
		std::list<DataCell*>::iterator tmpit;
		for(tmpit=m_frameData.begin();tmpit!=m_frameData.end();tmpit++){
			firstBuffer.FreeCell(*tmpit);
		}
		return -1;
	}
	int size;
	//count++;
	//if(count%5)printf("\n");
	//printf("read type:%d sq:%d\n",(**it)->m_FrameType,(**it)->m_sqNum/256);
	//printf("cell type %d  sqnum %d \t",(**it)->m_FrameType,(**it)->m_sqNum/256);	
	
	//	printf("%d ",(**it)->m_sqNum);

	(**it)->readData(data,&size,id);

	 if(isretaned){
		// printf(" sqnum:%d  timestmp:%d  size:%d id:%ld %c\n",(**it)->m_sqNum,(**it)->m_timeStamp,(**it)->m_dataSize,(**it)->m_id,(**it)->m_H264Data[(**it)->m_dataSize-10]);
		      
		}


	(*it)++;
	return size;
	
}

void SecondLevelBuffer::initSecondLevelBuffer(int gopsize){
	m_currentGOPPos=0;
	m_GOPsize=gopsize;
	InitializeCriticalSection(&CS);
}

void  SecondLevelBuffer::cleanup(){
	EnterCriticalSection( &CS);
	
	m_Frames.clear();
	m_currentGOPPos=0;
	LeaveCriticalSection( &CS);
}
int SecondLevelBuffer::readFrameData(FrameCell* frame){
	//printf("try enter read\n");
	EnterCriticalSection( &CS);
	//printf("entered read\n");
	if(m_Frames.size()<=FrameBufferSize){
		//printf("mframesize:%d\n",m_Frames.size());
		LeaveCriticalSection( &CS);
		return -1;
	}
	else{
		*frame=m_Frames.front();
		m_Frames.pop_front();
		g_retrans_treator.cleanTimeOut(frame->m_timeStamp);
		
	LeaveCriticalSection( &CS);
	return 0;
	}
}



int RTP2h264(char * rtpdata,int size,char * h264buff,int* sqnum,int* timeStamp, bool * isstart, bool * isend,unsigned short* FrameType,long* id,int *topsqnum)
{
	//printf("here!!");

	//******************
	memcpy(id,rtpdata,sizeof(long));
	memcpy(topsqnum,rtpdata+sizeof(long),sizeof(int));
	rtpdata=rtpdata+sizeof(long)+sizeof(int);
	size=size-sizeof(long)-sizeof(int);
	//*******************

	const int PACKHEADLEN = sizeof(RTPHeader);
	const unsigned int FRAMEHEAD = 0x01000000;
    const unsigned char IFRAMDATAHEAD = 0x65;
	const unsigned char PFRAMDTAAHEAD = 0x41;
	
	int frameheadoffset;
	int datalen=0;
	PRTP_header rtp_header = (PRTP_header)(rtpdata);
	



	//printf("%d \n",rtp_header->seq);
	if( 96 == rtp_header->payloadtype){
		char LitHead = *(rtpdata + 12);
		rtppayload_header * payload_header = (rtppayload_header *)(rtpdata + 12);
		 unsigned int FU_FLAG = 0;
		 FU_FLAG = (rtpdata[12])&(0x1C);
		 unsigned char NAL_HEAD = 0;


		 //**************************
		 *sqnum=rtp_header->seq/256;
		// *timeStamp=((rtp_header->timestamp>>16 )&0x0000ffff)/4096;

		 
		
		*timeStamp=rtp_header->timestamp;
		// printf("timestmp:%d sqnum:%d\n",*timeStamp,*sqnum);
		//**************************



		if ((RTSP_FRAME_I_TYPE == LitHead) || (RTSP_FRAME_IMID_TYPE == LitHead)){//pps，sps偏移12个字节后加入0x00000001
			        frameheadoffset = 0;
					//memcpy(h264buff, cRecvBuff, frameheadoffset);//应该不需要RTP的头
					memcpy((char *)h264buff+frameheadoffset, (const char *)&FRAMEHEAD, 4);
					frameheadoffset += 4;
					datalen= size - PACKHEADLEN + 4;
					memcpy((char *)h264buff+frameheadoffset, rtpdata+12, datalen-4);
					*isend=true;
					*isstart=true;
					*FrameType=PPS;

		}
		else if ((RTSP_FRAME_IEND_TYPE == LitHead) || (RTSP_FRAME_P_TYPE == LitHead))  //一包一帧(小包）的处理
		{
			        frameheadoffset = 0;
					//memcpy(h264buff, cRecvBuff, frameheadoffset);
					memcpy((char *)h264buff+frameheadoffset, (const char *)&FRAMEHEAD, 4);
					frameheadoffset += 4;
					datalen = size - PACKHEADLEN;
					memcpy((char *)h264buff+frameheadoffset, rtpdata+12, datalen);
					datalen += 4;
					*isend=true;
					*isstart=true;
					if(RTSP_FRAME_IEND_TYPE == LitHead)*FrameType=IFRAME;
					else *FrameType=PFRAME;
		}
		else 
		{
			 if(1 == payload_header->E){
			 *isend=true;
			 }
			 if(1== payload_header->S){
			*isstart=true;
			}
			
			if(0x1C == FU_FLAG){
				NAL_HEAD = ((rtpdata[12])&(0xE0)) | ((rtpdata[13])&(0x1F)) ; //取第13个字节的高3位和第14字节的低5位，拼成此NALU的头
				if(NAL_HEAD==IFRAMDATAHEAD)*FrameType=IFRAME;
				if(NAL_HEAD==PFRAMDTAAHEAD)*FrameType=PFRAME;
				if(1 == payload_header->S){
                memset(h264buff, 0, sizeof (h264buff));
                h264buff[3] = 1;
                h264buff[4] = NAL_HEAD; //将NALU的头保存起来

                memcpy(&(h264buff[5]), &(rtpdata[14]), size - 14); //从第15字节开始就是NALU的数据部分，保存起来
                datalen = size - 9;
				}
				else{
				        frameheadoffset = 0;
						//memcpy(h264buff, cRecvBuff, frameheadoffset);
						datalen = size-PACKHEADLEN - 2;
						memcpy((char *)h264buff+frameheadoffset, rtpdata+14, datalen);
			}
			}
			
		}
		
	}
	return datalen;
}