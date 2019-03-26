#ifndef __COLOR_LOG_OUT__
#define __COLOR_LOG_OUT__

#include <stdarg.h>					
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <string.h>

/*
\033[��ʾ��ʽ;ǰ��ɫ;����ɫm

��ʾ��ʽ:0��Ĭ��ֵ����1����������22���Ǵ��壩��4���»��ߣ���24�����»��ߣ���5����˸����25������˸����7�����ԣ���27���Ƿ��ԣ�
ǰ��ɫ:30����ɫ����31����ɫ����32����ɫ���� 33����ɫ����34����ɫ����35����죩��36����ɫ����37����ɫ��
����ɫ:40����ɫ����41����ɫ����42����ɫ���� 43����ɫ����44����ɫ����45����죩��46����ɫ����47����ɫ

*/


typedef enum
{
    BLACK = 0,  //��ɫ
    RED,           //��ɫ
    GREEN,      
    YELLOW,
    BLUE,
    MAGENTA,  //���
    CYAN,        //��ɫ
    WHITE
}LOG_COLOR;


/* ����: ��ɫ������: ��ɫ */
void LOGOUT_NOTICE(char* log_format, ...); //֪ͨ

/* ����: ��ɫ������: ��ɫ*/
void LOGOUT_WARNING(char* log_format, ...);//����

/* ����: ��ɫ������: ��ɫ */
void LOGOUT_ERROR(char* log_format, ...);//����

void LOGOUT_COLOR(
    LOG_COLOR forground_color,
    LOG_COLOR background_color,
    char* log_format, ...);

#endif
