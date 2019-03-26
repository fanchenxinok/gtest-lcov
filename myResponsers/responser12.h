#include "sendMsgModel.h"
#include "myComDef.h"

/* �û��Լ������Ӧ����1 */
void* onResponser1Thread(void * arg);

class responser1: public responser
{
public:
	responser1();
	~responser1();
	/* fun1 ��fun2 Ϊ����Ӧ������Ҫִ�еĺ��� */
	void r1_fun1();
	int r1_fun2(int a, int b);
	virtual void onResponser();
private:
	pthread_t resThreadId;
};


/* Ӧ����2 */
void* onResponser2Thread(void * arg);

class responser2: public responser
{
public:
	responser2();
	~responser2();
	double r2_fun1(double a, double b);
	int r2_fun2(int a, int b);
	virtual void onResponser();
private:
	pthread_t resThreadId;
};

typedef enum
{
    RES1 = 0,
    RES2
};

typedef enum event_type
{
    R1_FUN1 = 0,
    R1_FUN2,
    R2_FUN1,
    R2_FUN2,
    RX_NULL
}EVEN_TYPE;
