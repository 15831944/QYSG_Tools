#pragma once

#include <math.h>
#include <assert.h>
#include "LinkQueue.h"

// 最大的弊端，支持简单数据类型(int, char, float...)和结构体类型

enum
{
	pageSize = 255,
	minItems = pageSize - 2 // minimal number of items in internal node
};

enum TraverseOrder
{
	PreOrder,
	InOrder,
	PostOrder,
	LevelOrder
};

template <typename T, typename K>
class TTreeNode{
public:
	K key[pageSize];             // 关键字(键值)组
	T data[pageSize];            // 数据，可以是简单类型也可以是结构体等复杂类型
	unsigned short int nItems;   // 键值数
	TTreeNode *left;     // 左孩子
	TTreeNode *right;    // 右孩子
	char bf;             // Balace factor(bf = right subtree height - left subtree height)

	TTreeNode(T d, K k, TTreeNode *l, TTreeNode *r) :
		data(d), key(k), left(l), right(r) {}

	TTreeNode(){}
};

template <typename T, typename K>
class CTtree
{
public:

	// Constructor. 
	CTtree();
	CTtree(int(*compare)(void * a, void * b));
	CTtree(int(*compare)(void * a, void * b), void(*node_dump)(T a));

	//void set_compare(int(*compare)(T a, T b));
	void set_compare(int(*compare)(void * a, void * b));
	void set_node_dump(void(*node_dump)(T a));

	// Destructor.
	virtual ~CTtree();

public:
	// Insert key with data into T-Tree.
	void Insert(K key, T data);

	// Delete node with key from T-Tree.
	void Delete(K key);

	// Find a node with key, return value = -1 if not found, >=0 found.
	T Find(K key);

	// Traversing T-tree.
	void TraverseTree(TraverseOrder order);

	// return the current size of the t-tree's node.
	int GetNodeSize();

	// Get t-tree's depth.
	int Depth();

	// Get the minimum node.
	const TTreeNode<T, K> *GetMinNode();

	// Get the maximum node.
	const TTreeNode<T, K> *GetMaxNode();

	// Depending on the application, you can inherit your comparison function.
	virtual int keycompare(K key1, K key2);

	// Clean the whole T-Tree's nodes.
	void Clear();

	// Test if the tree is logically empty.Return true if empty, false otherwise.
	bool IsEmpty() const;

	// Traverse nodes
private:

	// Pre-order traverse.
	void PreOrderTraverse(TTreeNode<T, K> *pNode) const;

	// In-order traverse.
	void InOrderTraverse(TTreeNode<T, K> *pNode) const;

	// Post-order traverse.
	void PostOrderTraverse(TTreeNode<T, K> *pNode) const;

	// Level-order traverse.
	// void LevelOrderTraverse(TTreeNode<T, K> *pNode) const;

private:

	int(*m_compare)(void * a, void * b) = NULL;	 // 键值比较接口

	void(*m_node_dump)(T data) = NULL;		// 节点打印接口

	// Malloc node space from memory buffer.
	TTreeNode<T, K> *MallocNode();

	// Free node from memory buffer.
	void FreeNode(TTreeNode<T, K> *pNode);

	// To obtain the maximum value of a, b.
	int Max(int a, int b) const;

	bool _insert(TTreeNode<T, K> *&pNode, K key, T data);

	int remove(TTreeNode<T, K> *&pNode, K key);

	void _earse(TTreeNode<T, K> *pNode);

	TTreeNode<T, K>* FindMin(TTreeNode<T, K> *pNode);

	TTreeNode<T, K>* FindMax(TTreeNode<T, K> *pNode);

	// Rotate operate
private:

	// Get balace factor of node.
	int BalanceFactor(TTreeNode<T, K> *pNode) const;

	// LL (clock wise) type adjustment.
	TTreeNode<T, K> *SingleRotateLeft(TTreeNode<T, K> *pNode);

	// RR (counter clock wise) type adjustment.
	TTreeNode<T, K> *SingleRotateRight(TTreeNode<T, K> *pNode);

	// LR (after the first reverse cis) type adjustment.
	TTreeNode<T, K> *DoubleRotateLeft(TTreeNode<T, K> *pNode);

	// RL (Soon after the first reverse) type adjustment.
	TTreeNode<T, K> *DoubleRotateRight(TTreeNode<T, K> *pNode);

	// Balance T-tree's right branch.
	int BalanceRightBranch(TTreeNode<T, K> *&pNode);

	// Balance T-tree's left branch.
	int BalanceLeftBranch(TTreeNode<T, K> *&pNode);

	// Attributes
protected:

	// T-tree's root.
	TTreeNode<T, K>	*m_Root;

	// T-tree's current already alloc node size.
	int			m_nSize;
};

template <typename T, typename K>
TTreeNode<T, K>* CTtree<T, K>::FindMin(TTreeNode<T, K> *pNode)
{
	if (pNode != NULL)
	{
		if (pNode->left == NULL)
		{
			return pNode;
		}
		else
		{
			return FindMin(pNode->left);
		}
	}
	return NULL;
}

template <typename T, typename K>
TTreeNode<T, K>* CTtree<T, K>::FindMax(TTreeNode<T, K> *pNode)
{
	if (pNode != NULL)
	{
		if (pNode->right == NULL)TTreeNode
		{
			return pNode;
		}
		else
		{
			return FindMax(pNode->right);
		}
	}
	return NULL;
}

template <typename T, typename K>
CTtree<T, K>::CTtree()
{
	m_Root = NULL;
	m_nSize = 0;
}

template <class T, class K>
CTtree<T, K>::CTtree(int(*compare)(void * a, void * b))
{
	m_compare = compare;
}

template <class T, class K>
CTtree<T, K>::CTtree(int(*compare)(void * a, void * b), void(*node_dump)(T a))
{
	m_compare = compare;
	m_node_dump = node_dump;
}

template <typename T, typename K>
CTtree<T, K>::~CTtree()
{
	Clear();
	m_Root = NULL;
	m_nSize = 0;
}

template <class T, class K>
void  CTtree<T, K>::set_compare(int(*compare)(void * a, void * b))
{
	m_compare = compare;
}

template <typename T, typename K>
int CTtree<T, K>::GetNodeSize()
{
	return m_nSize;
}

template <typename T, typename K>
T CTtree<T, K>::Find(K key)
{
	TTreeNode<T, K> *pNode = m_Root;
	while (pNode != NULL)
	{
		int n = pNode->nItems;
		K keymin = pNode->key[0];
		K keymax = pNode->key[n > 0 ? n - 1 : 0];
		int nDiff1 = keycompare(key, keymin);
		int nDiff2 = keycompare(key, keymax);
		if (nDiff1 >= 0 && nDiff2 <= 0)
		{
			int l = 0, r = n - 1;
			// Binary search.
			while (l <= r)
			{
				int i = (l + r) >> 1;
				int nDiff = keycompare(key, pNode->key[i]);
				if (nDiff == 0)
				{
					return pNode->data[i];
				}
				else if (nDiff > 0)
				{
					l = i + 1;
				}
				else
				{
					r = i - 1;
				}
			}
			break;
		}
		else if (nDiff1 < 0)
		{
			pNode = pNode->left;
		}
		else if (nDiff2 > 0)
		{
			pNode = pNode->right;
		}
	}
	return pNode->data[0];
}

template <typename T, typename K>
int CTtree<T, K>::BalanceFactor(TTreeNode<T, K> *pNode) const
{
	int l, r;
	TTreeNode<T, K> *p1, *p2;
	l = r = 0;
	p1 = p2 = pNode;
	if (p1 != NULL)
	{
		while (p1->left != NULL)
		{
			p1 = p1->left;
			l++;
		}
	}
	if (p2 != NULL)
	{
		while (p2->right != NULL)
		{
			p2 = p2->right;
			r++;
		}
	}
	return (r - l);
}

template <typename T, typename K>
int CTtree<T, K>::Depth()
{
	int l, r;
	TTreeNode<T, K> *p1, *p2;
	l = r = 0;
	p1 = p2 = m_Root;
	if (p1 != NULL)
	{
		while (p1->left != NULL)
		{
			p1 = p1->left;
			l++;
		}
	}
	if (p2 != NULL)
	{
		while (p2->right != NULL)
		{
			p2 = p2->right;
			r++;
		}
	}
	return max(l, r);
}

template <typename T, typename K>
const TTreeNode<T, K> *CTtree<T, K>::GetMinNode()
{
	return FindMin(m_Root);
}

template <typename T, typename K>
const TTreeNode<T, K> *CTtree<T, K>::GetMaxNode()
{
	return FindMax(m_Root);
}

template <typename T, typename K>
int CTtree<T, K>::Max(int a, int b) const
{
	return (a > b ? a : b);
}

/**
* Rotate T-tree node with left child.this is a single rotation for case LL.
* Update balance factor, then return new root.
*/
template <typename T, typename K>
TTreeNode<T, K> *CTtree<T, K>::SingleRotateLeft(TTreeNode<T, K> *pNode)
{
	TTreeNode<T, K> *K = pNode->left;
	pNode->left = K->right;
	K->right = pNode;

	// Adjust the balance factor.
	pNode->bf = BalanceFactor(pNode);
	K->bf = BalanceFactor(K);

	return K;  // new root
}

/**
* Rotate T-tree node with right child.this is a single rotation for case RR.
* Update balance factor, then return new root.
*/
template <typename T, typename K>
TTreeNode<T, K> *CTtree<T, K>::SingleRotateRight(TTreeNode<T, K> *pNode)
{
	TTreeNode<T, K> *K = pNode->right;
	pNode->right = K->left;
	K->left = pNode;

	// Adjust the balance factor.
	pNode->bf = BalanceFactor(pNode);
	K->bf = BalanceFactor(K);

	return K;  // new root
}

/**
* Rotate T-tree node with left child.this is a double rotation for case LR.
* Update balance factor, then return new root.
*/
template <typename T, typename K>
TTreeNode<T, K> *CTtree<T, K>::DoubleRotateLeft(TTreeNode<T, K> *pNode)
{
	pNode->left = SingleRotateRight(pNode->left);

	// Adjust the balance factor.
	pNode->bf = BalanceFactor(pNode);

	return SingleRotateLeft(pNode);
}

/**
* Rotate T-tree node with right child.this is a double rotation for case RL.
* Update balance factor, then return new root.
*/
template <typename T, typename K>
TTreeNode<T, K> *CTtree<T, K>::DoubleRotateRight(TTreeNode<T, K> *pNode)
{
	pNode->right = SingleRotateLeft(pNode->right);

	// Adjust the balance factor.
	pNode->bf = BalanceFactor(pNode);

	return SingleRotateRight(pNode);
}

template <typename T, typename K>
void CTtree<T, K>::Insert(K key, T data)
{
	if (m_Root == NULL)
	{
		m_Root = MallocNode();
		m_Root->key[0] = key;
		m_Root->data[0] = data;
		m_Root->nItems = 1;
		m_Root->left = NULL;
		m_Root->right = NULL;
	}
	else
	{
		TTreeNode<T, K> *pNode = m_Root;
		bool bRet = _insert(pNode, key, data);
		if (pNode != m_Root)
		{
			m_Root = pNode;
		}
	}
}

template <typename T, typename K>
void CTtree<T, K>::FreeNode(TTreeNode<T, K> *pNode)
{
	if (pNode)
	{
		delete pNode;
		pNode = NULL;
	}
}

template <typename T, typename K>
TTreeNode<T, K> *CTtree<T, K>::MallocNode()
{
	TTreeNode<T, K> *pNode = new TTreeNode<T, K>();
	memset(pNode, 0, sizeof(TTreeNode<T, K>));
	m_nSize++;

	return (pNode);
}

template <typename T, typename K>
bool CTtree<T, K>::_insert(TTreeNode<T, K> *&pNode, K key, T data)
{
	int n = pNode->nItems;
	K keymin = pNode->key[0];
	K keymax = pNode->key[n > 0 ? n - 1 : 0];
	int nDiff = keycompare(key, keymin);
	if (nDiff <= 0)
	{
		TTreeNode<T, K> *pLeftId = pNode->left;
		if ((pLeftId == 0 || nDiff == 0) && pNode->nItems != pageSize)
		{
			for (int i = n; i > 0; i--)
			{
				pNode->key[i] = pNode->key[i - 1];
				pNode->data[i] = pNode->data[i - 1];
			}
			pNode->key[0] = key;
			pNode->data[0] = data;
			pNode->nItems += 1;
			return false;
		}
		if (pLeftId == 0)
		{
			pLeftId = MallocNode();
			pLeftId->key[0] = key;
			pLeftId->data[0] = data;
			pLeftId->nItems += 1;
			pNode->left = pLeftId;
		}
		else
		{
			TTreeNode<T, K> *pChildId = pLeftId;
			bool bGrow = _insert(pChildId, key, data);
			if (pChildId != pLeftId)
			{
				pNode->left = pLeftId = pChildId;
			}
			if (!bGrow)
			{
				return false;
			}
		}
		if (pNode->bf > 0)
		{
			pNode->bf = 0;
			return false;
		}
		else if (pNode->bf == 0)
		{
			pNode->bf = -1;
			return true;
		}
		else
		{
			if (pLeftId->bf < 0)
			{
				pNode = SingleRotateLeft(pNode); // single LL turn
			}
			else
			{
				pNode = DoubleRotateLeft(pNode); // double LR turn	
			}
			return false;
		}

	}
	nDiff = keycompare(key, keymax);
	if (nDiff >= 0)
	{
		TTreeNode<T, K> *pRightId = pNode->right;
		if ((pRightId == 0 || nDiff == 0) && pNode->nItems != pageSize)
		{
			pNode->key[n] = key;
			pNode->data[n] = data;
			pNode->nItems += 1;
			return false;
		}
		if (pRightId == 0)
		{
			pRightId = MallocNode();
			pRightId->key[0] = key;
			pRightId->data[0] = data;
			pRightId->nItems += 1;
			pNode->right = pRightId;
		}
		else
		{
			TTreeNode<T, K> *pChildId = pRightId;
			bool bGrow = _insert(pChildId, key, data);
			if (pChildId != pRightId)
			{
				pNode->right = pRightId = pChildId;
			}
			if (!bGrow)
			{
				return false;
			}
		}
		if (pNode->bf < 0)
		{
			pNode->bf = 0;
			return false;
		}
		else if (pNode->bf == 0)
		{
			pNode->bf = 1;
			return true;
		}
		else
		{
			if (pRightId->bf > 0)
			{
				pNode = SingleRotateRight(pNode); // single RR turn
			}
			else
			{
				pNode = DoubleRotateRight(pNode); // double RL turn	
			}
			return false;
		}
	}

	// Node appears in the middle of the primary key points.
	int l = 1, r = n - 1;
	while (l < r)
	{
		int i = (l + r) >> 1;
		nDiff = keycompare(key, pNode->key[i]);
		if (nDiff > 0)
		{
			l = i + 1;
		}
		else
		{
			r = i;
			if (nDiff == 0)
			{
				break;
			}
		}
	}

	// Insert before key[r]
	if (n != pageSize)
	{
		for (int i = n; i > r; i--)
		{
			pNode->key[i] = pNode->key[i - 1];
			pNode->data[i] = pNode->data[i - 1];
		}
		pNode->key[r] = key;
		pNode->data[r] = data;
		pNode->nItems += 1;
		return false;
	}
	else
	{
		K reinsertId;
		T reinsertData;
		// The right than the left subtree subtree weight, into the left equilibrium.
		if (pNode->bf >= 0)
		{
			// Node in the value of the most left out, 
			// key inserted into its position in the r-1.
			// Value will be inserted into the left of its left subtree.
			reinsertId = pNode->key[0];
			reinsertData = pNode->data[0];
			for (int i = 1; i < r; i++)
			{
				pNode->key[i - 1] = pNode->key[i];
				pNode->data[i - 1] = pNode->data[i];
			}
			pNode->key[r - 1] = key;
			pNode->data[r - 1] = data;

			return _insert(pNode, reinsertId, reinsertData);
		}
		else // The left than the right subtree subtree re-insert the right balance.
		{
			// Node in the value of the most right out, 
			// key inserted into the location of its r.
			// The right value will be inserted to its right subtree.
			reinsertId = pNode->key[n - 1];
			reinsertData = pNode->data[n - 1];
			for (int i = n - 1; i > r; i--)
			{
				pNode->key[i] = pNode->key[i - 1];
				pNode->data[i] = pNode->data[i - 1];
			}
			pNode->key[r] = key;
			pNode->data[r] = data;

			return _insert(pNode, reinsertId, reinsertData);
		}
	}
}

template <typename T, typename K>
void CTtree<T, K>::Clear()
{
	_earse(m_Root);
}

template <typename T, typename K>
void CTtree<T, K>::_earse(TTreeNode<T, K> *pNode)
{
	if (pNode == NULL)
	{
		return;
	}

	_earse(pNode->left);

	_earse(pNode->right);

	FreeNode(pNode);
}

template <typename T, typename K>
void CTtree<T, K>::Delete(K key)
{
	TTreeNode<T, K> *pNode = m_Root;
	int h = remove(pNode, key);
	assert(h >= 0);
	if (pNode != m_Root)
	{
		m_Root = pNode;
	}
}

template <typename T, typename K>
int CTtree<T, K>::BalanceLeftBranch(TTreeNode<T, K> *&pNode)
{
	if (pNode->bf < 0)
	{
		pNode->bf = 0;
		return 1;
	}
	else if (pNode->bf == 0)
	{
		pNode->bf = 1;
		return 0;
	}
	else
	{
		TTreeNode<T, K> *pRightId = pNode->right;
		if (pRightId->bf >= 0)
		{
			pNode = SingleRotateRight(pNode); // single RR turn
			if (pRightId->bf == 0)
			{
				pNode->bf = 1;
				pRightId->bf = -1;
				return 0;
			}
			else
			{
				pNode->bf = 0;
				pRightId->bf = 0;
				return 1;
			}
		}
		else
		{
			pNode = DoubleRotateRight(pNode); // double RL turn	
			return 1;
		}
	}
}

template <typename T, typename K>
int CTtree<T, K>::BalanceRightBranch(TTreeNode<T, K> *&pNode)
{
	if (pNode->bf > 0)
	{
		pNode->bf = 0;
		return 1;
	}
	else if (pNode->bf == 0)
	{
		pNode->bf = -1;
		return 0;
	}
	else
	{
		TTreeNode<T, K> * pLeftId = pNode->left;
		if (pLeftId->bf <= 0)
		{
			pNode = SingleRotateLeft(pNode); // single LL turn
			if (pLeftId->bf == 0)
			{
				pNode->bf = -1;
				pLeftId->bf = 1;
				return 0;
			}
			else
			{
				pNode->bf = 0;
				pLeftId->bf = 0;
				return 1;
			}
		}
		else
		{
			pNode = DoubleRotateLeft(pNode); // double LR turn	
			return 1;
		}
	}
	return 0;
}

template <typename T, typename K>
int CTtree<T, K>::remove(TTreeNode<T, K> *&pNode, K key)
{
	int n = pNode->nItems;
	K keymin = pNode->key[0];
	K keymax = pNode->key[n > 0 ? n - 1 : 0];
	int nDiff = keycompare(key, keymin);
	if (nDiff <= 0)
	{
		TTreeNode<T, K> *pLeftId = pNode->left;
		if (pLeftId != 0)
		{
			TTreeNode<T, K> *pChildId = pLeftId;
			int h = remove(pChildId, key);
			if (pChildId != pLeftId)
			{
				pNode->left = pChildId;
			}
			if (h > 0)
			{
				return BalanceLeftBranch(pNode);
			}
			else if (h == 0)
			{
				return 0;
			}
		}
		assert(nDiff == 0);
	}
	nDiff = keycompare(key, keymax);
	if (nDiff <= 0)
	{
		for (int i = 0; i < n; i++)
		{
			if (pNode->key[i] == key)
			{
				if (n == 1)
				{
					if (pNode->right == 0)
					{
						TTreeNode<T, K> *pTempNode = pNode->left;
						FreeNode(pNode);
						pNode = pTempNode;
						return 1;
					}
					else if (pNode->left == 0)
					{
						TTreeNode<T, K> *pTempNode = pNode->right;
						FreeNode(pNode);
						pNode = pTempNode;
						return 1;
					}
				}
				TTreeNode<T, K> *pLeftId = pNode->left, *pRightId = pNode->right;
				if (n <= minItems)
				{
					if (pLeftId != 0 && pNode->bf <= 0)
					{
						while (pLeftId->right != 0)
						{
							pLeftId = pLeftId->right;
						}
						while (--i >= 0)
						{
							pNode->key[i + 1] = pNode->key[i];
							pNode->data[i + 1] = pNode->data[i];
						}
						pNode->key[0] = pLeftId->key[pLeftId->nItems - 1];
						pNode->data[0] = pLeftId->data[pLeftId->nItems - 1];
						key = pNode->key[0];
						TTreeNode<T, K> *pChildId = pLeftId;
						int h = remove(pChildId, pNode->key[0]);
						if (pChildId != pLeftId)
						{
							pNode->left = pChildId;
						}
						if (h > 0)
						{
							h = BalanceLeftBranch(pNode);
						}
						return h;
					}
					else if (pNode->right != 0)
					{
						while (pRightId->left != 0)
						{
							pRightId = pRightId->left;
						}
						while (++i < n)
						{
							pNode->key[i - 1] = pNode->key[i];
							pNode->data[i - 1] = pNode->data[i];
						}
						pNode->key[n - 1] = pRightId->key[0];
						pNode->data[n - 1] = pRightId->data[0];
						key = pNode->key[n - 1];

						TTreeNode<T, K> *pChildId = pRightId;
						int h = remove(pChildId, key);
						if (pChildId != pRightId)
						{
							pNode->right = pChildId;
						}
						if (h > 0)
						{
							h = BalanceRightBranch(pNode);
						}
						return h;
					}
				}
				while (++i < n)
				{
					pNode->key[i - 1] = pNode->key[i];
					pNode->data[i - 1] = pNode->data[i];
				}
				pNode->nItems -= 1;
				return 0;
			}
		}
	}
	TTreeNode<T, K> *pRightId = pNode->right;
	if (pRightId != 0)
	{
		TTreeNode<T, K> *pChildId = pRightId;
		int h = remove(pChildId, key);
		if (pChildId != pRightId)
		{
			pNode->right = pChildId;
		}
		if (h > 0)
		{
			return BalanceRightBranch(pNode);
		}
		else
		{
			return h;
		}
	}
	return -1;
}

template <typename T, typename K>
bool CTtree<T, K>::IsEmpty() const
{
	return m_Root == NULL;
}

template <typename T, typename K>
int CTtree<T, K>::keycompare(K key1, K key2)
{
	K p = key1;
	K q = key2;
	if (m_compare)
		return m_compare((void*)&key1, (void*)&key2);
	return p < q ? -1 : p == q ? 0 : 1;
}

template <typename T, typename K>
void CTtree<T, K>::TraverseTree(TraverseOrder order)
{
	switch (order)
	{
	case PreOrder:
		PreOrderTraverse(m_Root);
		break;
	case InOrder:
		InOrderTraverse(m_Root);
		break;
	case PostOrder:
		PostOrderTraverse(m_Root);
		break;
// 	case LevelOrder:
// 		LevelOrderTraverse(m_Root);
// 		break;
	}
}

template <typename T, typename K>
void CTtree<T, K>::InOrderTraverse(TTreeNode<T, K> *pNode) const
{
	if (pNode != NULL)
	{
		InOrderTraverse(pNode->left);
		int nSize = pNode->nItems;
		for (int i = 0; i < nSize; i++)
		{
			printf("%02d ", pNode->key[i]);
		}
		InOrderTraverse(pNode->right);
	}
}

template <typename T, typename K>
void CTtree<T, K>::PostOrderTraverse(TTreeNode<T, K> *pNode) const
{
	if (pNode != NULL)
	{
		PostOrderTraverse(pNode->left);
		PostOrderTraverse(pNode->right);
		int nSize = pNode->nItems;
		for (int i = 0; i < nSize; i++)
		{
			printf("%02d ", pNode->key[i]);
		}
	}
}

template <typename T, typename K>
void CTtree<T, K>::PreOrderTraverse(TTreeNode<T, K> *pNode) const
{
	if (pNode != NULL)
	{
		int nSize = pNode->nItems;
		for (int i = 0; i < nSize; i++)
		{
			printf("%02d ", pNode->key[i]);
		}
		PreOrderTraverse(pNode->left);
		PreOrderTraverse(pNode->right);
	}
}

// template <typename T, typename K>
// void CTtree<T, K>::LevelOrderTraverse(TTreeNode<T, K> *pNode) const
// {
// 	if (pNode == NULL)
// 	{
// 		return;
// 	}
// 	// store siblings of each node in a queue so that they are
// 	// visited in order at the next level of the tree
// 	CLinkNode<TTreeNode<T, K> *> q;
// 	TTreeNode<T, K> *p;
// 
// 	// initialize the queue by inserting the root in the queue
// 	q.push(pNode);
// 	// continue the iterative process until the queue is empty
// 	while (!q.empty())
// 	{
// 		// delete front node from queue and output the node value
// 		p = (TTreeNode<T, K> *)q.front();
// 		q.pop();
// 
// 		int nSize = p->nItems;
// 		for (int i = 0; i < nSize; i++)
// 		{
// 			TRACE("%02d\n", p->key[i]);
// 		}
// 		// if a left child exists, insert it in the queue
// 		if (p->left != NULL)
// 		{
// 			q.push(p->left);
// 		}
// 		// if a right child exists, insert next to its sibling
// 		if (p->right != NULL)
// 		{
// 			q.push(p->right);
// 		}
// 	}
// 	int n = 0;
// }