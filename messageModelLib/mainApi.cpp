#include "comDef.h"
#include "sender.h"
#include "receiver.h"
extern "C"{
	#include "log_out.h"
}
#include "mainApi.h"
using namespace std;

/************************
һ���첽��Ϣ����ģ��:
(1) �Ƚ����ն���responser ע�ᵽ��Ϣת����(receiver)�У�
     ������ÿ��responser �����ȼ�(low, mid, high)��
(2) �����Ҫ����responser ִ������Ӧ�������صĽ����
      ��Ҫע�����������Ӧ��responser��ע��: ������
      listener ��Ӧ����responser Ҫһһ���, listener�����߳�
      ��ʼ������
(3) ͨ��sender���ͽ��յĶ���(responser)���ͣ�ִ�еĺ�
     ������������Ҫ�Ĳ�����receiver��
(4) ��Ϣת����(receiver) ����ѭ���Ӷ����а����ȼ���
     ȡ��Ϣ�����Ҹ�����Ϣ������(responser), ������Ϣ
     ת������Ӧ��responser��
(5) responer ��ע�ᵽreceiver �Ժ�Ϳ����߳��ڵȴ���Ϣ��

����ģ��ͼ:
	sender                 listener
	    |                        /\
	   \/                        |
	receiver                   |
	    |                        |
	   \/                        |
	responser            responser
*************************/

#define FUN_CALL_LOG(name) \
	do{\
		LOGOUT_NOTICE("[LOGOUT_NOTICE] %s was call in Line: %d!\n", #name, __LINE__);\
	}while(0)


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
){
	FUN_CALL_LOG(apl_registResponser);

	if(resType < APL_RES_MIN || resType >= APL_RES_MAX){
		LOGOUT_ERROR("apl_registResponser() resType is invaild !!!!\n");
		return FALSE;
	}

	if(!pRes){
		LOGOUT_ERROR("apl_registResponser() pRes is NULL !!!!\n");
		return FALSE;
	}
		
	receiver* const rec_instance = getReceiverInstance(); //���constָ�룬ָ�����ݿɱ��ַ���ɱ�
	if(rec_instance == NULL){
		LOGOUT_ERROR("apl_registResponser() get receiver pointer is NULL !!!!\n");
		return FALSE;
	}
	rec_instance->addResponser(resType, resPrior, pRes);
	return TRUE;
}

 /**
 * @brief function: ע��responser
 * @param[in] resType: responser Ӧ������ʶ
 * @return BOOL: �ɹ�����TRUE, ʧ�ܷ���FALSE��
 */
 BOOL apl_unRegistResponser(APL_RES_TYPE resType)
 {
	 if(resType < APL_RES_MIN || resType >= APL_RES_MAX){
		 LOGOUT_ERROR("apl_unregistResponser() resType is invaild !!!!\n");
		 return FALSE;
	 }
  
	 receiver* const rec_instance = getReceiverInstance(); //���constָ�룬ָ�����ݿɱ��ַ���ɱ�
	 if(rec_instance == NULL){
		 LOGOUT_ERROR("apl_unregistResponser() get receiver pointer is NULL !!!!\n");
		 return FALSE;
	 }
	 rec_instance->deleteResponser(resType);
	 return TRUE;
 }

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
 ){
	 if(resType < APL_RES_MIN || resType >= APL_RES_MAX){
		 LOGOUT_ERROR("apl_registListener() resType is invaild !!!!\n");
		 return FALSE;
	 }
 
	 if(!pRes || !pListener){
		 LOGOUT_ERROR("apl_registListener() pRes or pListener is NULL !!!!\n");
		 return FALSE;
	 }
		 
	 pRes->addListener(resType, pListener);
	 return TRUE;
 }

 /**
* @brief function: ע��listener ������
* @param[in] resType: ��������Ӧ��responser Ӧ������ʶ
* @param[in] pRes: ��������Ӧ��Ӧ����ָ��
* @return BOOL: �ɹ�����TRUE, ʧ�ܷ���FALSE��
*/
 BOOL apl_unRegistListener(
	  APL_RES_TYPE resType,    /* responser type: must in the range [0, APL_RES_MAX] */
	  responser* const pRes		 /* responser pointer */
  ){
	  if(resType < APL_RES_MIN || resType >= APL_RES_MAX){
		  LOGOUT_ERROR("apl_unregistListener() resType is invaild !!!!\n");
		  return FALSE;
	  }
  
	  if(!pRes){
		  LOGOUT_ERROR("apl_unregistListener() pRes  is NULL !!!!\n");
		  return FALSE;
	  }
		  
	  pRes->deleteListener(resType);
	  return TRUE;
  }

/**
* @brief function: ��Ϣ�����
* @param[in] msgData: �����洢�������Ϣ
* @return void.
*/
void apl_msgPacker(char* msgData, ...)
{
	if(msgData == NULL)
		return;
	va_list vaList;
	void* para;
	char* funParam = msgData;
	va_start(vaList, msgData);
	int len = va_arg(vaList, int);
	while((len != 0) && (len != -1)){
		para = va_arg(vaList, void*);
		memcpy(funParam, para, len);
		funParam += len;
		len = va_arg(vaList, int);
	}
	va_end(vaList);
	return;
}

/**
* @brief function: ��Ϣ�����
* @param[in] msgData: �����洢�������Ϣ
* @return void.
*/
void apl_msgUnPacker(char* msgData, ...)
{
	if(msgData == NULL)
		return;
	va_list vaList;
	void* para;
	char* funParam = msgData;
	va_start(vaList, msgData);
	int len = va_arg(vaList, int);
	while((len != 0) && (len != -1)){
		para = va_arg(vaList, void*);
		memcpy(para, funParam, len);
		funParam += len;
		len = va_arg(vaList, int);
	}
	va_end(vaList);
	return;
}

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
){
	sender* const send_instance = getSenderInstance();
	if(send_instance == NULL){
		LOGOUT_ERROR("apl_sendMessage() send_instance is NULL\n");
		return FALSE;
	}

	 receiver* const rec_instance = getReceiverInstance(); //���constָ�룬ָ�����ݿɱ��ַ���ɱ�
	 if(rec_instance == NULL){
		 LOGOUT_ERROR("apl_sendMessage() get receiver pointer is NULL !!!!\n");
		 return FALSE;
	 }

	MSG_INFO msgInfo;
	msgInfo.resType = resType;
	msgInfo.msg.eventID = eventID;
	memcpy(msgInfo.msg.msgData, msgData, sizeof(char) * 128);
	 
	send_instance->sendMsg(rec_instance, &msgInfo);
	return TRUE;
}

