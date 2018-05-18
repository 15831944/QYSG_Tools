#include "stdafx.h"
#include <iostream>
#include "IndexListTest.h"
#include "utilts.h"
#include "RcsManager.h"

struct CKeys caKeys[] =
{
	{ 0, NULL },
	{ INDEX_KEYS_END},
};

int IndexListTest(void)
{
	CIndexList<int, CKeys> clIndexList;
	int i;

	

	for (i = 0; i < 1000000; i++)
	{
		clIndexList.AddTail(i);
	}

// 	TickStart();
// 	clIndexList.CreateIndexInt(caKeys);  // ���������͵Ļ���ƫ�ƾ���0
// 	TickEnd();

	TickStart();
	clIndexList.CreateRBTIndexInt(caKeys);  // ���������͵Ļ���ƫ�ƾ���0
	TickEnd();

	return EXIT_SUCCESS;
}