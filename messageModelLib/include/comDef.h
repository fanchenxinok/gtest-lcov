#ifndef __APL_MY_COM_DEF__
#define __APL_MY_COM_DEF__

#include <iostream>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <map>
#include <queue>
#include <pthread.h>
using namespace std;

#if 0
/* Ӧ������ʶ */
typedef enum responser_type
{
	RES1 = 0,
	RES2,
	RES_MAX
}RES_TYPE;

/* Ӧ�������ȼ� */
typedef enum responser_priority
{
	LOW = 0,
	MID,
	HIGH,
	NULL_VALUE
}RES_PRIOR;
#endif

typedef unsigned short RES_TYPE;
typedef unsigned short RES_PRIOR;
enum{
    RES_MAX = 10
};

enum
{
    LOW = 0,
    MID,
    HIGH,
    NULL_VALUE
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

#endif

