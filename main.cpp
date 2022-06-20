#include "myComDef.h"
#include "responser12.h"
#include "listener12.h"

extern "C" {
	#include "log_out.h"
}
#include <unistd.h>

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

static responser1 res1_instance;
static responser2 res2_instance;

static listener1 lis1_instance;
static listener2 lis2_instance;

 int main(void)
 {
       /* ע��Ӧ������receiver */
	BOOL res = FALSE;
	res = apl_registResponser(RES1, RES_MID, &res1_instance);
	if(res == TRUE){
		LOGOUT_NOTICE("regist responser 1 success !!!!!!");
	}else{
		LOGOUT_ERROR("regist responser 1 fail !!!!!!");
	}
	
	res = apl_registResponser(RES2, RES_HIGH, &res2_instance);
	if(res == TRUE){
		LOGOUT_NOTICE("regist responser 2 success !!!!!!");
	}else{
		LOGOUT_ERROR("regist responser 2 fail !!!!!!");
	}
	

       /* ������ע�� */
	apl_registListener(RES1, &res1_instance, &lis1_instance);
	apl_registListener(RES2, &res2_instance, &lis2_instance);
 	while(1){
		 MSG_INFO msgInfo;
		 char msgData[128];

		 msgInfo.resType = RES1;  //���ö�������
		 msgInfo.msg.eventID = R1_FUN1; //����Ӧ����ʲô����
		 apl_sendMessage(RES1, R1_FUN1, msgData); //���Ϳ�ʼ��Ϣ����������

		 //apl_unRegistResponser(RES1);

		 msgInfo.msg.eventID = R1_FUN2;
		 int a = 10, b = 122;
		 apl_msgPacker(msgData,
		 	sizeof(int), &a,
		 	sizeof(int), &b, -1);
		 apl_sendMessage(RES1, R1_FUN2, msgData);

		 msgInfo.resType = RES2;
		 msgInfo.msg.eventID = R2_FUN1;
		 double c = 4.23, d = 2.32;
		 apl_msgPacker(msgData,
		 	sizeof(double), &c,
		 	sizeof(double), &d, -1);
		 apl_sendMessage(RES2, R2_FUN1, msgData);

		 msgInfo.msg.eventID = R2_FUN2;
		 a = 20;
		 b = 30;
		 apl_msgPacker(msgData,
		 	sizeof(int), &a,
		 	sizeof(int), &b, -1);
		 apl_sendMessage(RES2, R2_FUN2, msgData);

		 sleep(1);
 	}
	return 0;
 } 

