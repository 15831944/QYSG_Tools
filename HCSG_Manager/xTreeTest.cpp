#include "stdafx.h"
#include "xTreeTest.h"

// int TestStructCmp(TestStruct a, TestStruct b)
// {
// 	return a.iData > b.iData ? 1 : (a.iData == b.iData ? 0 : -1);
// }

int TestStructCmp(void * a, void * b)
{
	return *(int *)a - *(int *)b;
}

void TestStructDump(TestStruct cTestStruct)
{
	TRACE("iData = %d, cData = %c\n", cTestStruct.iData, cTestStruct.cData);
}