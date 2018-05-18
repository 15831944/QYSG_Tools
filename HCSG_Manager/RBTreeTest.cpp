#include "stdafx.h"
#include <iostream>
#include "xTreeTest.h"
#include "RBTree.h"


static TestStruct aTestStruct[] = {
	{ 10, 'h' },
	{ 40, 'q' },
	{ 30, 'l' },
	{ 60, 'x' },
	{ 20, 'e' },
	{ 89, 'z' },
	{ 7, 'a' },
	{ 1024, 's' },
};

int RBTreeTest(void)
{
	int iLen = ARRAYSIZE(aTestStruct);
	CRBTree<TestStruct, int>* pRBTree = new CRBTree<TestStruct, int>(TestStructCmp, TestStructDump);

	for (int i = 0; i < iLen; i++)
	{
		//pRBTree->insert(aTestStruct[i], TestStructCmp);
		pRBTree->insert(aTestStruct[i], aTestStruct[i].iData);
	}

	//pRBTree->dump(TestStructDump);
	pRBTree->dump();

	TRACE("Tree Height: %d\n", pRBTree->getHeight());

	RBTNode<TestStruct, int> *res;
	res = pRBTree->iterativeSearch(20);

	TestStructDump(res->data);

	// ���ٺ����
	pRBTree->destroy();

	return EXIT_SUCCESS;
}

int IntCompare(void * a, void * b)
{
	return *(int *)a - *(int *)b;
}

void IntDump(int a)
{
	TRACE("%d\n", a);
}

int RBTreeTest_1(void)
{
	int a[] = { 10, 40, 30, 60, 90, 70, 20, 50, 80, 11, 55, 89, 104, 501, 7, 59, 1024 };
	int check_insert = 1;    // "����"�����ļ�⿪��(0���رգ�1����)
	int check_remove = 0;    // "ɾ��"�����ļ�⿪��(0���رգ�1����)
	int i;
	int ilen = (sizeof(a)) / (sizeof(a[0]));
	CRBTree<int, int>* tree = new CRBTree<int, int>();
	
	TRACE("== ԭʼ����: \n");
	for (i = 0; i < ilen; i++)
		TRACE("%d\n", a[i]);

	for (i = 0; i < ilen; i++)
	{
		tree->insert(a[i], IntCompare);
		// ����check_insert=1,����"��Ӻ���"
		if (check_insert)
		{
			TRACE("== ��ӽڵ�: %d \n", a[i]);
 			TRACE("== ������ϸ��Ϣ:");
 			tree->dump(IntDump);
			cout << endl;
		}

	}

// 	cout << "== ������ϸ��Ϣ: " << endl;
// 	tree->dump();

	RBTNode<int, int> *res;
	res = tree->iterativeSearch(80);
	TRACE("res: %d\n", res->data);
	// ����check_remove=1,����"ɾ������"
// 	if (check_remove)
// 	{
// 		for (i = 0; i < ilen; i++)
// 		{
// 			tree->remove(a[i]);
// 
// 			cout << "== ɾ���ڵ�: " << a[i] << endl;
// 			cout << "== ������ϸ��Ϣ: " << endl;
// 			tree->dump();
// 			cout << endl;
// 		}
// 	}

	// ���ٺ����
	tree->destroy();
	
	return 0;
}

