#include "stdafx.h"
#include "RetransTreater.h"
#include "get_data.h"
int RTT = 100;
int commondport=35010;
bool g_retran_ruuning=true;
int requestsize = 100;


DWORD WINAPI RetranmitRequest(LPVOID lpParameter){
	/*
	winsock≥ı ºªØ
	*/
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

	SOCKADDR_IN server_retran_addr;
	SOCKET retrans_socket;    
	retrans_socket=socket(AF_INET, SOCK_DGRAM,0);
    server_retran_addr.sin_family = AF_INET;
    server_retran_addr.sin_port = htons(commondport); 
	server_retran_addr.sin_addr.s_addr = inet_addr(ServIP);

	while(g_retran_ruuning){
		std::vector<RetransUnit> RequestVector = g_retrans_treator.getReTransList(RTT);
		//printf("out get size:%d\n",RequestVector.size());
		char requestcommand[1500];

		int counter = 0;
		int packet_pos = 0;
		int packetsize = 0;
		
		 memcpy(requestcommand+packetsize,&userRandomId,sizeof(userRandomId));
		 packetsize = packetsize+sizeof(userRandomId);
		
		
		while (true){
			if(packet_pos==RequestVector.size())break;

			long id = RequestVector[packet_pos].top_id;
		    memcpy(requestcommand+packetsize,&id,sizeof(long));
		    packetsize = packetsize+sizeof(id);

			int sqnum=RequestVector[packet_pos].self_sqnum;
		    memcpy(requestcommand+packetsize,&sqnum,sizeof(sqnum));
		    packetsize=packetsize+sizeof(sqnum);

			int timestmp=RequestVector[packet_pos].self_timestmp;
		    memcpy(requestcommand+packetsize,&timestmp,sizeof(timestmp));
	    	packetsize=packetsize+sizeof(timestmp);

			packet_pos++;
			counter++;
			if(counter == requestsize){
				
				int re = sendto(retrans_socket,requestcommand,packetsize,0,(SOCKADDR*)&server_retran_addr,sizeof(SOCKADDR));
				//printf("send retrans request %d %d\n",sqnum,re);
				packetsize = 0;
				counter = 0;
				memcpy(requestcommand+packetsize,&userRandomId,sizeof(userRandomId));
	            packetsize = packetsize+sizeof(userRandomId);
				if(packet_pos==RequestVector.size()){
					break;
				}
			}
			if(packet_pos==RequestVector.size()){
				if(counter>0){
				//	printf("send retrans request %d size:%d\n ",sqnum,RequestVector.size());
					sendto(retrans_socket,requestcommand,packetsize,0,(SOCKADDR*)&server_retran_addr,sizeof(SOCKADDR));
					packetsize = 0;
					counter = 0;
				}
				break;
			}
		}
		Sleep(10);
	}

	return 0;
	
}