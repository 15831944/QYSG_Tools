#pragma once
#include "stdafx.h"

typedef struct CTestStruct
{
	int iData;
	char cData;
	// bool (*compare)(TestStruct *a, TestStruct *b);
}TestStruct;

//int TestStructCmp(TestStruct a, TestStruct b);
int TestStructCmp(void * a, void * b);
void TestStructDump(TestStruct cTestStruct);

int RBTreeTest(void);