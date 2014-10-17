#include "stdafx.h"
#include "audioPktQueue.h"

audioPktQueue audioq;
//audioPktQueue audioqRec;   //9.29
int quit = 0;

void packet_queue_init(audioPktQueue *q)
{
	memset(q, 0, sizeof(audioPktQueue));
	q->mutex = SDL_CreateMutex();
	q->cond = SDL_CreateCond();
}

/*int packet_queue_put(audioPktQueue *q, audioPkt *pkt)
{
	audioPktList *pkt1;

	pkt1 = (audioPktList *)malloc(sizeof(audioPktList));
	if (!pkt1)
		return -1;
	pkt1->pkt = *pkt;
	pkt1->next = NULL;
	SDL_LockMutex(q->mutex);

	audioPktList *current_itr=q->first_pkt;
	audioPktList *previous_itr;
	

	if(!q->last_pkt)
	{
		q->first_pkt = pkt1;
		q->last_pkt = pkt1;
	}
	else if(q->first_pkt->pkt.id > pkt->id)
	{
		pkt1->next=q->first_pkt;
		q->first_pkt=pkt1;
	}
	else
	{
		previous_itr=current_itr;
		current_itr=current_itr->next;
		//printf("queue size %d \n",q->nb_packets);
		while(current_itr!= NULL && current_itr->pkt.buff!=NULL)
		{
			//printf("insert audio packet %d \n",pkt->id);
			if(current_itr->pkt.id > pkt->id)
			{
				pkt1->next=current_itr;
				previous_itr->next=pkt1;
				break;
			}
			previous_itr=current_itr;
			current_itr=current_itr->next;
		}
		if(current_itr==NULL)
		{
			q->last_pkt->next = pkt1;
			q->last_pkt = pkt1;
		}
	}
	q->nb_packets++;
	q->size += pkt1->pkt.buffsize;
	SDL_CondSignal(q->cond);
	SDL_UnlockMutex(q->mutex);
	return 0;
}*/

int packet_queue_put(audioPktQueue *q, audioPkt *pkt)
{
	audioPktList *pkt1;

	pkt1 = (audioPktList *)malloc(sizeof(audioPktList));
	if (!pkt1)
		return -1;
	pkt1->pkt = *pkt;
	pkt1->next = NULL;
	SDL_LockMutex(q->mutex);

	audioPktList *current_itr=q->first_pkt;
	//audioPktList *previous_itr;
	

	if(!q->last_pkt)
	{
		q->first_pkt = pkt1;
		q->last_pkt = pkt1;
	}
	else if(q->first_pkt->pkt.id > pkt->id)
	{
		pkt1->next=q->first_pkt;
		q->first_pkt=pkt1;
	}
	else
	{
		while(current_itr->next!= NULL)
		{
			if(current_itr->next->pkt.id > pkt->id)
			{
				pkt1->next=current_itr->next;
				current_itr->next=pkt1;
				break;
			}
			current_itr=current_itr->next;
		}
		if(current_itr->next==NULL)
		{
			current_itr->next=pkt1;
			//q->last_pkt->next = pkt1;
			q->last_pkt = pkt1;
		}
	}
	q->nb_packets++;
	q->size += pkt1->pkt.buffsize;
	SDL_CondSignal(q->cond);
	SDL_UnlockMutex(q->mutex);
	return 0;
}


int packet_queue_get(audioPktQueue *q, audioPkt *pkt, int block)
{
	audioPktList *pkt1;
	int ret;
	SDL_LockMutex(q->mutex);
	for(;;)
	{
		if(quit)
		{
			ret = -1;
			break;
		}
		pkt1 = q->first_pkt;
		if (pkt1)
		{
			q->first_pkt = pkt1->next;
			if (!q->first_pkt)
				q->last_pkt = NULL;
			q->nb_packets--;
			q->size -= pkt1->pkt.buffsize;
			*pkt = pkt1->pkt;
			free(pkt1);   //10.23   原本这句注销了，后取消注销
			ret = 1;
			break;
		}
		else if (!block)
		{
			ret = 0;
			break;
		}
		else
		{
			SDL_CondWait(q->cond, q->mutex);
		}
	}
	SDL_UnlockMutex(q->mutex);
	return ret;
}

void packet_clear(audioPktQueue *q)
{
		audioPkt *pkt;
		while(q->nb_packets>0)
		{
			 packet_queue_get(q,pkt,1);
		}
}