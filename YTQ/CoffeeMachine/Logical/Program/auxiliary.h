#ifndef __AUXILIARY_H
#define __AUXILIARY_H

#include <iostream>
#include <string.h>

using namespace std;

/*@note
	��춴惦�Ñ�ݔ��ă���
*/ 
typedef struct
	{
		char OperationType[11];
		char CSName[11];
		float para1;
		float para2;
		float para3;
	}InputCom;

extern InputCom input;

InputCom Input();
float Extraction(char str[40]);
float Index1(int n);
float Index2(int n);

#endif

