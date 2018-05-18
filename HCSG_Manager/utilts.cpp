#include "stdafx.h"
#include "utilts.h"
#include "IndexList.h"

static long lTickCounter;
static LARGE_INTEGER lStartFrequency;

// GetTickCount() 精度只能达到毫秒
void TickStart_ms()
{
	lTickCounter = GetTickCount();
}

void TickEnd_ms()
{
	long lTickNow = GetTickCount();
	TRACE("用时：%d - %d = %d 毫秒\n", lTickNow, lTickCounter, lTickNow - lTickCounter);
}


// 使用QueryPerformanceCounter() 精度可以达到微妙
void TickStart()
{
	QueryPerformanceCounter(&lStartFrequency);
}

void TickEnd()
{
	LARGE_INTEGER lEndFrequency, tc;
	QueryPerformanceFrequency(&tc);
	QueryPerformanceCounter(&lEndFrequency);
	TRACE("用时: %f 毫秒\n", (lEndFrequency.QuadPart - lStartFrequency.QuadPart)*1000.0 / tc.QuadPart);
}

int IntCompare(int a, int b, void* param)
{
	return a - b;
}

int StringCompare(void * a, void * b)
{
	string key1 = *(string *)a;
	string key2 = *(string *)b;
	return key1 == key2 ? 0 : (key1 > key2 ? 1 : -1);
}

int Offset2pTreeCompare(const struct COffset2Tree& a, const int& b, void* param)
{
	return a.m_iOffset - b;
}