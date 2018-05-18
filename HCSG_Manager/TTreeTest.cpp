#include "stdafx.h"
#include "TTree.h"
#include "xTreeTest.h"

static int a[] = { 30, 28, 45, 15, 16, 17, 19, 90, 25, 36, 31, 32, 20, 95, 23, 91, 21, 11, 12, 13, 10, 8, 9, 7 };
//				    0   1   2   3	4	5	6	7	8	9  10  11  12  13  14  15  16  17  18  19  20  21 22 23


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

int TTreeTest()
{
	CTtree<TestStruct, int> *cTtree = new CTtree<TestStruct, int>();
	int nSize = _countof(aTestStruct);
	for (int i = 0; i < nSize; i++)
	{
		int key = aTestStruct[i].iData;
		TestStruct data = aTestStruct[i];
		cTtree->Insert(key, data);
	}
	cTtree->TraverseTree(LevelOrder);
	int datakey = 90;
	int nDepth = cTtree->Depth();
	TestStruct dataindex = cTtree->Find(datakey);
	const TTreeNode<TestStruct, int> *pNode = cTtree->GetMinNode();
	datakey = 7;
	cTtree->Delete(datakey);

	return EXIT_SUCCESS;
}


int TTreeTest_int()
{
	CTtree<int, int> cTtree;
	int nSize = _countof(a);
	for (int i = 0; i < nSize; i++)
	{
		int key = a[i];
		int data = i;
		cTtree.Insert(key, data);
	}
	cTtree.TraverseTree(LevelOrder);
	int datakey = 90;
	int nDepth = cTtree.Depth();
	int dataindex = cTtree.Find(datakey);
	const TTreeNode<int, int> *pNode = cTtree.GetMinNode();
	datakey = 7;
	cTtree.Delete(datakey);

	return EXIT_SUCCESS;
}
