#ifndef __SENDER__
#define __SENDER__
#include "comDef.h"

class receiver;

/* ��Ϣ������ */
class sender
{
public:
	sender();
	~sender();
	void msgDataPack(char* msgData, ...);  //����ϢӦ�������ͣ�ִ�еĺ������ͼ��������
	void sendMsg(receiver *rec, MSG_INFO *pMsgInfo); //������Ϣ����Ϣ������
};

sender* getSenderInstance();
#endif

