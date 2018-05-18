#include "stdafx.h"
#include "utilts.h"
#include "IndexList.h"

static long lTickCounter;
static LARGE_INTEGER lStartFrequency;

// GetTickCount() ����ֻ�ܴﵽ����
void TickStart_ms()
{
	lTickCounter = GetTickCount();
}

void TickEnd_ms()
{
	long lTickNow = GetTickCount();
	TRACE("��ʱ��%d - %d = %d ����\n", lTickNow, lTickCounter, lTickNow - lTickCounter);
}


// ʹ��QueryPerformanceCounter() ���ȿ��Դﵽ΢��
void TickStart()
{
	QueryPerformanceCounter(&lStartFrequency);
}

void TickEnd()
{
	LARGE_INTEGER lEndFrequency, tc;
	QueryPerformanceFrequency(&tc);
	QueryPerformanceCounter(&lEndFrequency);
	TRACE("��ʱ: %f ����\n", (lEndFrequency.QuadPart - lStartFrequency.QuadPart)*1000.0 / tc.QuadPart);
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