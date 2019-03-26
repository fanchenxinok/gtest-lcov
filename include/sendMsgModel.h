#ifndef __MAIN_API_H__
#define __MAIN_API_H__
#include <iostream>
#include <queue>
#include <map>
#include <pthread.h>
using namespace std;

typedef enum enum_bool
{
    FALSE = 0,
    TRUE = 1
}BOOL;

typedef unsigned short RES_TYPE;
typedef unsigned short APL_RES_TYPE;

typedef enum
{
    RES_LOW = 0,
    RES_MID,
    RES_HIGH
}APL_RES_PRIOR;

enum
{
    APL_RES_MIN = 0,
    APL_RES_MAX = 10
};

typedef struct msg
{
	int eventID;
	char msgData[128];
}EVENT_MSG;

typedef struct msgInfo
{
	RES_TYPE resType;
	EVENT_MSG msg;
}MSG_INFO;


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



/**
* @brief function: ע��responser ����Ϣת������
* @param[in] resType: responser Ӧ������ʶ
* @param[in] resPrior: responser Ӧ����������Ϣ�����ȼ�
* @param[in] pRes: ��Ҫע���responser Ӧ����ָ�롣
* @return BOOL: �ɹ�����TRUE, ʧ�ܷ���FALSE��
*/
BOOL apl_registResponser(
	APL_RES_TYPE resType,    /* responser type: must in the range [0, APL_RES_MAX] */
	APL_RES_PRIOR resPrior,  /* priority: must be the value RES_LOW, RES_MID, RES_HIGH */
	responser* const pRes    /* responser pointer */
);

 /**
 * @brief function: ע��responser
 * @param[in] resType: responser Ӧ������ʶ
 * @return BOOL: �ɹ�����TRUE, ʧ�ܷ���FALSE��
 */
 BOOL apl_unRegistResponser(APL_RES_TYPE resType);


/**
* @brief function: ע��listener ������ (һ��Ӧ������Ӧһ��������)
* @param[in] resType: ��������Ӧ��responser Ӧ������ʶ
* @param[in] pRes: ��������Ӧ��Ӧ����ָ��
* @param[in] pListener: ��Ҫע���listener ������ָ�롣
* @return BOOL: �ɹ�����TRUE, ʧ�ܷ���FALSE��
*/
BOOL apl_registListener(
	 APL_RES_TYPE resType,	  /* responser type: must in the range [0, APL_RES_MAX] */
	 responser* const pRes,         /* responser pointer */
	 listener* const pListener	  /* listener pointer */
 );

 /**
* @brief function: ע��listener ������
* @param[in] resType: ��������Ӧ��responser Ӧ������ʶ
* @param[in] pRes: ��������Ӧ��Ӧ����ָ��
* @return BOOL: �ɹ�����TRUE, ʧ�ܷ���FALSE��
*/
 BOOL apl_unRegistListener(
	  APL_RES_TYPE resType,    /* responser type: must in the range [0, APL_RES_MAX] */
	  responser* const pRes		 /* responser pointer */
  );

/**
* @brief function: ��Ϣ�����
* @param[in] msgData: �����洢�������Ϣ
* @return void.
*/
void apl_msgPacker(char* msgData, ...);


/**
* @brief function: ��Ϣ�����
* @param[in] msgData: �����洢�������Ϣ
* @return void.
*/
void apl_msgUnPacker(char* msgData, ...);

/**
* @brief function: ������Ϣ����
* @param[in] resType: Ӧ������ʶ
* @param[in] eventID: Ӧ����ִ�е�event id.
* @param[in] msgData: ��Ҫ���͵���Ϣ
* @return BOOL: �ɹ�����TRUE, ���򷵻�FALSE.
*/
BOOL apl_sendMessage(
	APL_RES_TYPE resType,
	int eventID,
	char* msgData
);
#endif
