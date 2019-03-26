#ifndef __APL_MY_RESPONSER__
#define __APL_MY_RESPONSER__
#include "comDef.h"
class listener;

typedef std::map<RES_TYPE, listener* const>  LIS_MAP;

/* ��ϢӦ��ĸ��� */
class responser
{
public:
	responser();
	~responser();
	virtual void onResponser() = 0;  //���麯��ʹ responser ����ʵ����
	void msgDataUnPack(char* msgData, ...);
       void msgDataPack(char* msgData, ...);
	void setEventMsg(const EVENT_MSG* srcMsg);
       pthread_cond_t* getPthreadCond();

       void sendMsgToListener(MSG_INFO msgInfo);  //������Ϣ��������
	void addListener(RES_TYPE resType, listener* const pListener); //ע�������
	void deleteListener(RES_TYPE resType); //ɾ��������

protected:
	EVENT_MSG eventMsg;
	pthread_cond_t	cond;
	pthread_mutex_t mutex;

       static LIS_MAP lisMap;
       pthread_mutex_t listener_mutex;
};
#endif

