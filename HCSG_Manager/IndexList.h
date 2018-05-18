#pragma once
#include "afxwin.h"
#include <iostream>
#include "utilts.h"
#include "BinarySearch.h"
#include "TTree.h"
#include "RBTree.h"

using namespace std;

// ������������
// ֻ֧�����ڽṹ��
// T ֻ���ǽṹ��, K�ǰ����ؼ��ֳ�Ա�ڽṹ���е�ƫ��λ�õ�����

struct COffset2Tree
{
	int m_iOffset;	// ��Ա�ֶ���Խṹ����ʼλ�õ�ƫ�ƣ���ѯʱ��Ҫ�������ֵ����ѡ��������
	void *m_pIndexTree;	// ʹ��void��������Ÿ��ֲ�ͬ���͵ĵ�����ָ�룬��ʹ��ǰ��Ҫ�Ƚ���ǿת
};
#define INDEX_TREE_MAX_MUN 20

template <typename T, typename K>
class CIndexList:public CList<T, T>
{
public:
	CIndexList();
	~CIndexList();

	int CreateIndexStr(K* keys);
	int CreateIndexInt(K* keys);

	int CreateRBTIndexStr(K* keys);
	int CreateRBTIndexInt(K* keys);

	// TTree
	T& Search(const int iOffset, const string key);
	T& Search(const int iOffset, const int key);

	// BRTree
	T& RBTSearch(const int iOffset, const string key);
	T& RBTSearch(const int iOffset, const int key);

protected:
	struct COffset2Tree m_aOffset2tree[INDEX_TREE_MAX_MUN]; //�ṹ�������������
	int m_iIndexTreeNum = 0;

	void* FindOffset2pTree(int ioffset);
	int AddOffset2pTree(int ioffset, void* pIndexTree);
};

template <typename T, typename K>
CIndexList<T, K>::CIndexList()
{
	memset(m_aOffset2tree, 0, sizeof(m_aOffset2tree));
}

template <typename T, typename K>
CIndexList<T, K>::~CIndexList()
{
}

template <typename T, typename K>
void* CIndexList<T, K>::FindOffset2pTree(int ioffset)
{
	int iIndex = BSearch(m_aOffset2tree, m_iIndexTreeNum, ioffset, Offset2pTreeCompare, NULL);

	if (iIndex != INVALID_INDEX)
		return m_aOffset2tree[iIndex].m_pIndexTree;

	return NULL;
}

template <typename T, typename K>
int CIndexList<T, K>::AddOffset2pTree(int ioffset, void* pIndexTree)
{
	if (m_iIndexTreeNum == 0)
	{
		m_aOffset2tree[0].m_iOffset = ioffset;
		m_aOffset2tree[0].m_pIndexTree = pIndexTree;
		m_iIndexTreeNum++;
		return EXIT_SUCCESS;
	}
	else
	{
		int iIndex = FindInsertIndex(m_aOffset2tree, m_iIndexTreeNum, ioffset, Offset2pTreeCompare, NULL);    //����Ѱ�Ҳ����λ��  

		int i = m_iIndexTreeNum;
		struct COffset2Tree temp = m_aOffset2tree[i];
		while (i > iIndex)    // Ų��λ��  
		{
			m_aOffset2tree[i] = m_aOffset2tree[i - 1];
			i--;
		}
		m_aOffset2tree[iIndex].m_iOffset = ioffset;
		m_aOffset2tree[iIndex].m_pIndexTree = pIndexTree;
		m_iIndexTreeNum++;
		return EXIT_SUCCESS;
	}

	return EXIT_FAILURE;
}

template <typename T, typename K>
int CIndexList<T, K>::CreateIndexStr(K* keys)
{
	int i = 0;
	while (keys[i].m_iOffset != INDEX_KEYS_END)
	{
		CTtree<POSITION, string> *cTtreeChar = (CTtree<POSITION, string> *)FindOffset2pTree(keys[i].m_iOffset);

		if (cTtreeChar)
			cTtreeChar->Clear();
		else
		{
			cTtreeChar = new CTtree<POSITION, string>(keys[i].compare);
			AddOffset2pTree(keys[i].m_iOffset, (void*)cTtreeChar);
		}

		POSITION pos = this->GetHeadPosition();
		while (pos != NULL)
		{
			POSITION curPos = pos;
			T cData = this->GetNext(pos);
			string key = (char *)((char *)&cData + keys[i].m_iOffset);
			cTtreeChar->Insert(key, curPos);
		}
		i++;

		// Testing...
		int nSize = cTtreeChar->GetNodeSize();
		int nDepth = cTtreeChar->Depth();
		const TTreeNode<POSITION, string> *pNode = cTtreeChar->GetMinNode();
	}

	return EXIT_SUCCESS;
}

template <typename T, typename K>
int CIndexList<T, K>::CreateIndexInt(K* keys)
{
	int i = 0;
	while (keys[i].m_iOffset != INDEX_KEYS_END)
	{
		CTtree<POSITION, int> *cTtreeInt = (CTtree<POSITION, int> *)FindOffset2pTree(keys[i].m_iOffset);

		if (cTtreeInt)
			cTtreeInt->Clear();
		else
		{
			cTtreeInt = new CTtree<POSITION, int>(keys[i].compare);
			AddOffset2pTree(keys[i].m_iOffset, (void*)cTtreeInt);
		}

		POSITION pos = this->GetHeadPosition();
		while (pos != NULL)
		{
			POSITION curPos = pos;
			T cData = this->GetNext(pos);
			int key = *(int *)((char *)&cData + keys[i].m_iOffset);
			cTtreeInt->Insert(key, curPos);
		}

		i++;

		int nSize = cTtreeInt->GetNodeSize();

		//cTtree->TraverseTree(LevelOrder);
		//int datakey = 50;
		int nDepth = cTtreeInt->Depth();
		//POSITION DataPos = cTtreeInt.Find(datakey);
		const TTreeNode<POSITION, int> *pNode = cTtreeInt->GetMinNode();
		//datakey = 7;
		//cTtreeInt->Delete(datakey);
	}

	return EXIT_SUCCESS;
}

template <typename T, typename K>
int CIndexList<T, K>::CreateRBTIndexStr(K* keys)
{
	int i = 0;
	while (keys[i].m_iOffset != INDEX_KEYS_END)
	{
		CRBTree<POSITION, string> *pRBTree = (CRBTree<POSITION, string> *)FindOffset2pTree(keys[i].m_iOffset);

		if (pRBTree)
			pRBTree->destroy();
		else
		{
			pRBTree = new CRBTree<POSITION, string>(keys[i].compare);
			AddOffset2pTree(keys[i].m_iOffset, (void*)pRBTree);
		}

		POSITION pos = this->GetHeadPosition();
		while (pos != NULL)
		{
			POSITION curPos = pos;
			T cData = this->GetNext(pos);
			string key = (char *)((char *)&cData + keys[i].m_iOffset);
			pRBTree->insert(curPos, key);
		}
		
		i++;

		// TRACE("Tree Height: %d\n", pRBTree->getHeight());

		// 	RBTNode<TestStruct, int> *res;
		// 	res = pRBTree->iterativeSearch(20);
	}

	return EXIT_SUCCESS;
}

template <typename T, typename K>
int CIndexList<T, K>::CreateRBTIndexInt(K* keys)
{
	int i = 0;
	while (keys[i].m_iOffset != INDEX_KEYS_END)
	{
		CRBTree<POSITION, int> *pRBTree = (CRBTree<POSITION, int> *)FindOffset2pTree(keys[i].m_iOffset);

		if (pRBTree)
			pRBTree->destroy();
		else
		{
			pRBTree = new CRBTree<POSITION, int>(keys[i].compare);
			AddOffset2pTree(keys[i].m_iOffset, (void*)pRBTree);
		}

		POSITION pos = this->GetHeadPosition();
		while (pos != NULL)
		{
			POSITION curPos = pos;
			T cData = this->GetNext(pos);
			int key = *(int *)((char *)&cData + keys[i].m_iOffset);
			pRBTree->insert(curPos, key);
		}

		i++;

		TRACE("Tree Height: %d\n", pRBTree->getHeight());

		// 	RBTNode<TestStruct, int> *res;
		// 	res = pRBTree->iterativeSearch(20);
	}

	return EXIT_SUCCESS;
}

// template <typename T, typename K>
// int CIndexList<T, K>::CreateIndex(K* keys)
// {
// 	CTtree<POSITION, K> cTtree;
// 	
// 	int i;
// 	POSITION pos = this->GetHeadPosition();
// 	for (i = 0; i < this->GetCount(); i++)
// 	{
// 		POSITION curPos = pos;
// 		T cData = this->GetNext(pos);
// 		K key = *(&cData + keys[0]);
// 		cTtree.Insert(key, curPos);
// 	}
// 
// 	int nSize = cTtree.GetNodeSize();
// 
// 	cTtree.TraverseTree(LevelOrder);
// 	int datakey = 50;
// 	int nDepth = cTtree.Depth();
// 	POSITION DataPos = cTtree.Find(datakey);
// 	const TTreeNode<POSITION, K> *pNode = cTtree.GetMinNode();
// 	datakey = 7;
// 	cTtree.Delete(datakey);
// 
// 	TickEnd();
// 
// 	return EXIT_SUCCESS;
// }

template <typename T, typename K>
T& CIndexList<T, K>::Search(const int iOffset, const string key)
{
	CTtree<POSITION, string> *cpTtree = (CTtree<POSITION, string> *)FindOffset2pTree(iOffset);

	POSITION DataPos = cpTtree->Find(key);

	return this->GetAt(DataPos);
}

template <typename T, typename K>
T& CIndexList<T, K>::Search(const int iOffset, const int key)
{
	CTtree<POSITION, int> *cpTtree = (CTtree<POSITION, int> *)FindOffset2pTree(iOffset);

	POSITION DataPos = cpTtree->Find(key);

	return this->GetAt(DataPos);
}

template <typename T, typename K>
T& CIndexList<T, K>::RBTSearch(const int iOffset, const string key)
{
	CRBTree<POSITION, string> *cpTree = (CRBTree<POSITION, string> *)FindOffset2pTree(iOffset);

	POSITION DataPos = cpTree->iterativeSearch(key)->data;

	return this->GetAt(DataPos);
}

template <typename T, typename K>
T& CIndexList<T, K>::RBTSearch(const int iOffset, const int key)
{
	CRBTree<POSITION, int> *cpTree = (CRBTree<POSITION, int> *)FindOffset2pTree(iOffset);

	POSITION DataPos = cpTree->iterativeSearch(key)->data;

	return this->GetAt(DataPos);
}
