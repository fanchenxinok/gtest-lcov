#include "responser12.h"
#include "listener12.h"

using namespace std;

/* �û��Լ������Ӧ����1 */
responser1::responser1():resThreadId(0)
{
	pthread_create(&resThreadId, NULL, onResponser1Thread, (void*)this);
	pthread_setname_np(resThreadId, "responser1");
}

responser1::~responser1()
{
	resThreadId = 0;
}

void responser1::r1_fun1()
{

	cout << "r1_fun1() called!!!!!!!!" << endl;
}


int responser1::r1_fun2(int a, int b)
{

	cout << "r1_fun2() called!!!!!!!!" << endl;

	return a+ b;
}

void responser1::onResponser()
{
	while(1){
		pthread_mutex_lock(&mutex);
		pthread_cond_wait(&cond,&mutex);
		switch(eventMsg.eventID)
		{
			case R1_FUN1:
			{
				r1_fun1();
				/* ������Ϣ�������������ؽ�� */
				MSG_INFO msgInfo;
				msgInfo.resType = RES1;
				msgInfo.msg.eventID = L1_FUN1;
				/* ������new �����ڴ�����ΪMY_INFO �ṹ��
				    ����string ��Ա��ֻ����new ���ܵ�����
				    ���캯����*/
				MY_INFO* myinfo = new MY_INFO(); 
				myinfo->name = "fanchenxin";
				myinfo->age = 27;
				myinfo->sex = 'm';
				msgDataPack(msgInfo.msg.msgData, sizeof(MY_INFO), myinfo, -1);
				sendMsgToListener(msgInfo);
				break;
			}
			case R1_FUN2:
			{
				int a, b;
				msgDataUnPack(eventMsg.msgData, sizeof(int), &a,
					sizeof(int), &b, -1);
				int sum = r1_fun2(a, b);
				cout << "(1)The sum = " << sum << endl;

				/* ������Ϣ�������������ؽ�� */
				MSG_INFO msgInfo;
				msgInfo.resType = RES1;
				msgInfo.msg.eventID = L1_FUN2;
				msgDataPack(msgInfo.msg.msgData, sizeof(int), &sum, -1);
				sendMsgToListener(msgInfo);
				break;
			}
			default:
				break;
		}
		
		pthread_mutex_unlock(&mutex);
	}
}

void* onResponser1Thread(void* arg)
{
	responser1* pRes1 = (responser1*)arg;
	pRes1->onResponser();
}

/* Ӧ����2 */
responser2::responser2():resThreadId(0)
{
	pthread_create(&resThreadId, NULL, onResponser2Thread, (void*)this);
	pthread_setname_np(resThreadId, "responser2");
}

responser2::~responser2()
{
	resThreadId = 0;
}

double responser2::r2_fun1(double a, double b)
{
	cout << "r2_fun1() called!!!!!!!!" << endl;
	cout << " a * b = " << a * b << endl;
	return a*b;
}


int responser2::r2_fun2(int a, int b)
{

	cout << "r2_fun2() called!!!!!!!!" << endl;

	return a+ b;
}

void responser2::onResponser()
{
	while(1){
		pthread_mutex_lock(&mutex);
		pthread_cond_wait(&cond,&mutex);
		switch(eventMsg.eventID)
		{
			case R2_FUN1:
			{
				double a, b;
				msgDataUnPack(eventMsg.msgData, sizeof(double), &a,
					sizeof(double), &b, -1);
				double res = r2_fun1(a, b);

				/* ������Ϣ�������� */
				MSG_INFO msgInfo;
				msgInfo.resType = RES2;
				msgInfo.msg.eventID = L2_FUN1;
				msgDataPack(msgInfo.msg.msgData, sizeof(double), &res, -1);
				sendMsgToListener(msgInfo);
				break;
			}
			case R2_FUN2:
			{
				int c, d;
				msgDataUnPack(eventMsg.msgData, sizeof(int), &c,
					sizeof(int), &d, -1);
				int sum = r2_fun2(c, d);
				cout << "(2)The sum is " << sum << endl;

				/* ������Ϣ�������� */
				MSG_INFO msgInfo;
				msgInfo.resType = RES2;
				msgInfo.msg.eventID = L2_FUN2;
				msgDataPack(msgInfo.msg.msgData, sizeof(int), &sum, -1);
				sendMsgToListener(msgInfo);
				break;
			}
			default:
				break;
		}
		
		pthread_mutex_unlock(&mutex);
	}
}

void* onResponser2Thread(void* arg)
{
	responser2* pRes2 = (responser2*)arg;
	pRes2->onResponser();
}

