#ifndef __RECEIVER__
#define __RECEIVER__
#include "comDef.h"

class responser;
/* ��Ϣ������(��Ϣת������) */
class receiver
{
public:
	receiver();
	~receiver();
	void processResMsg();  //������Ϣ������(Ӧ����) ����Ϣת����Ӧ����
	void addResponser(RES_TYPE resType, RES_PRIOR res_prior, responser* const pRes); //ע��Ӧ����
	void deleteResponser(RES_TYPE resType); //ɾ��Ӧ����
	void addMsgIntoResQue(MSG_INFO msgInfo);  //����Ϣ����ȴ�����

private:
	typedef std::map<RES_TYPE, responser* const> RES_MAP; //�������ͼ�����ָ��ӳ��
	RES_MAP resMap;   
	RES_PRIOR *priortyMap;   //�洢Ӧ���������ȼ�
	#if 0
	std::queue<MSG_INFO> resHighQueue;   // ��Ϣ����-- ���ȼ���
	std::queue<MSG_INFO> resMidQueue;   // ��Ϣ����-- ���ȼ���ͨ
	std::queue<MSG_INFO> resLowQueue;   // ��Ϣ����-- ���ȼ���
       #else
       typedef std::queue<MSG_INFO> RES_QUE;
       RES_QUE resQueues[HIGH+1];
       #endif

	pthread_t recThreadId;
	pthread_mutex_t mutex;
	static int responserMaxNum;  //��������ɵ�Ӧ��������
	int responserNum;
};

receiver* getReceiverInstance();
#endif
