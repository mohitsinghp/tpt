#ifndef PROXY_POLLER_H
#define PROXY_POLLER_H
/*System Headers*/
#include<sys/epoll.h>
#include<pthread.h>
/*Common Headers*/
#include<workq.h>


#define EPOLL_MAX_EVENTS 10000 /*10K*/

enum event_flag {
	EVENT_IN = 0,
	EVENT_OUT = 1,
	EVENT_INOUT = 2,
};

struct poller_info {
	int epoll_fd;
	WorkQT *workq;
	struct epoll_event *events;
	pthread_t poller_id;
	void *(*poller_routine) (void *);
};
int init_poller(struct poller_info *poller_info);
int add_to_poller(int epoll_fd, int fd, enum event_flag event_flag, void *data);
void  *proxy_default_poller(void *arg);
int destroy_poller(struct poller_info *poller_info);
#endif
