#ifndef __APL_MY_LISTENER__
#define __APL_MY_LISTENER__
#include "comDef.h"

/* �������ĸ��� */
class listener
{
public:
	listener();
	~listener();
	virtual void onListener() = 0;  //���麯��ʹ responser ����ʵ����
	void addEventMsgIntoQue(EVENT_MSG event_msg);
       void clearEventMsgQue();
	void msgDataUnPack(char* msgData, ...);
       pthread_cond_t* getSignalCond();
protected:
	pthread_cond_t	cond;
	pthread_mutex_t mutex;
       std::queue<EVENT_MSG>  lisQueue;
};
#endif

