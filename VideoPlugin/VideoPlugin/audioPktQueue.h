#include "sdl\SDL.h"
#include "sdl\SDL_thread.h"
class audioPkt
{
public:
	 char buff[1500];
	 int buffsize;
	 long id;
};

typedef struct audioPktList
{
	audioPkt pkt;
	audioPktList* next;
}audioPktList;


typedef struct audioPktQueue
{
	audioPktList *first_pkt, *last_pkt;
	int nb_packets;      //packet的数
	int size;                    //PacketQueue的字节数
	SDL_mutex *mutex;
	SDL_cond *cond;
} audioPktQueue;

extern audioPktQueue audioq;
extern int quit;

void packet_queue_init(audioPktQueue *q);
int packet_queue_put(audioPktQueue *q, audioPkt *pkt);
int packet_queue_get(audioPktQueue *q, audioPkt *pkt, int block);
void packet_clear(audioPktQueue *q);