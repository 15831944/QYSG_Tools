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
// 	clIndexList.CreateIndexInt(caKeys);  // 简单数据类型的话，偏移就是0
// 	TickEnd();

	TickStart();
	clIndexList.CreateRBTIndexInt(caKeys);  // 简单数据类型的话，偏移就是0
	TickEnd();

	return EXIT_SUCCESS;
}