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

	// 销毁红黑树
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
	int check_insert = 1;    // "插入"动作的检测开关(0，关闭；1，打开)
	int check_remove = 0;    // "删除"动作的检测开关(0，关闭；1，打开)
	int i;
	int ilen = (sizeof(a)) / (sizeof(a[0]));
	CRBTree<int, int>* tree = new CRBTree<int, int>();
	
	TRACE("== 原始数据: \n");
	for (i = 0; i < ilen; i++)
		TRACE("%d\n", a[i]);

	for (i = 0; i < ilen; i++)
	{
		tree->insert(a[i], IntCompare);
		// 设置check_insert=1,测试"添加函数"
		if (check_insert)
		{
			TRACE("== 添加节点: %d \n", a[i]);
 			TRACE("== 树的详细信息:");
 			tree->dump(IntDump);
			cout << endl;
		}

	}

// 	cout << "== 树的详细信息: " << endl;
// 	tree->dump();

	RBTNode<int, int> *res;
	res = tree->iterativeSearch(80);
	TRACE("res: %d\n", res->data);
	// 设置check_remove=1,测试"删除函数"
// 	if (check_remove)
// 	{
// 		for (i = 0; i < ilen; i++)
// 		{
// 			tree->remove(a[i]);
// 
// 			cout << "== 删除节点: " << a[i] << endl;
// 			cout << "== 树的详细信息: " << endl;
// 			tree->dump();
// 			cout << endl;
// 		}
// 	}

	// 销毁红黑树
	tree->destroy();
	
	return 0;
}

