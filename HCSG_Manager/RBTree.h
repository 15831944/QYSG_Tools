#pragma once
#include "stdafx.h"
#include <iomanip>
#include <iostream>
using namespace std;

/*
* Red black tree���������
* 1��֧�ּ��������ͣ�int��char��float...���ͽṹ�����ͣ�struct��
* 2�����ݱ���ڵ��У����м�ֵ����ֻ������һ��
* 3�����������ͣ����ݺͼ�ֵһ������������������Ҫ�������ü�ֵ
* 4����Ҫ�Ľ������ϵĽڵ�ֻ��¼���ݵ�ָ�룬��ֻ��Ϊ������ÿ������������Ӧ��һ����
*/

enum RBTColor
{
	RED,
	BLACK
};

template <class T, class K>
class RBTNode{
public:
	K key;             // �ؼ���(��ֵ)
	T data;            // ���ݣ������Ǽ�����Ҳ�����ǽṹ��ȸ�������
	RBTColor color;    // ��ɫ
	RBTNode *left;     // ����
	RBTNode *right;    // �Һ���
	RBTNode *parent;   // �����

	RBTNode(T d, K k, RBTColor c, RBTNode *p, RBTNode *l, RBTNode *r) :
		data(d), key(k), color(c), parent(), left(l), right(r) {}
};

template <class T, class K>
class CRBTree
{
private:
	RBTNode<T, K> *mRoot;    // �����
	int m_iSize = 0;	// �ڵ�����
	//int (*m_compare)(T a, T b) = NULL;	 // �ڵ�ȽϽӿ�
	int(*m_compare)(void * a, void * b) = NULL;	 // ��ֵ�ȽϽӿ�
	void (*m_node_dump)(T data) = NULL;		// �ڵ��ӡ�ӿ�

public:
	CRBTree(void);
	~CRBTree(void);
	//CRBTree(int(*compare)(T a, T b), int(*compare)(K a, K b), void(*node_dump)(T a));
	CRBTree(int(*compare)(void * a, void * b));
	CRBTree(int(*compare)(void * a, void * b), void(*node_dump)(T a));

	//void set_compare(int(*compare)(T a, T b));
	void set_compare(int(*compare)(void * a, void * b));
	void set_node_dump(void(*node_dump)(T a));

	// ǰ�����"�����"
	void preOrder();
	// �������"�����"
	void inOrder();
	// �������"�����"
	void postOrder();

	// �����(dataΪ�ڵ��ֵ)���뵽�������
	// ���ڼ��������ͣ�data��keyֵ��һ���ģ�����ֻ��Ҫ����һ������ֹ�����ض���
	int insert(T data);
	int insert(T data, int(*compare)(void * a, void * b));
	// ���ڸ����������ͣ�data��keyֵ�ǲ�һ���ģ�������Ҫ����data��keyֵ
	int insert(T data, K key);
	int insert(T data, K key, int(*compare)(void * a, void * b));

	// (�ݹ�ʵ��)����"�����"��data������key�Ľڵ�
	RBTNode<T, K>* search(K key);
	// (�ǵݹ�ʵ��)����"�����"��data������key�Ľڵ�
	RBTNode<T, K>* iterativeSearch(K key);

	// ɾ�����(dataΪ�ڵ��ֵ)
	void remove(T data);

	// ���ٺ����
	void destroy();

	// ��ӡ�����, ����ʹ����data���Ǽ��������͵����
	void dump();
	void dump(void(*NodeDump)(T data));

	// ��ȡ����
	int getHeight();

	// ��ȡ�ڵ���
	int getSize();

private:
	int keycompare(K key1, K key2) const;

	// ǰ�����"�����"
	void _preOrder(RBTNode<T, K>* node) const;
	// �������"�����"
	void _inOrder(RBTNode<T, K>* node) const;
	// �������"�����"
	void _postOrder(RBTNode<T, K>* node) const;

	// (�ݹ�ʵ��)����"�����x"�м�ֵΪkey�Ľڵ�, ���ڼ��������ͣ�key����data�����ڸ�������������ʹ�����õ�keyֵ
	RBTNode<T, K>* _search(RBTNode<T, K>* x, K key) const;
	RBTNode<T, K>* _iterativeSearch(RBTNode<T, K>* x, K key) const;

	// ����
	void _leftRotate(RBTNode<T, K>* &root, RBTNode<T, K>* x);

	// ����
	void _rightRotate(RBTNode<T, K>* &root, RBTNode<T, K>* y);

	// ������������
	int _insertFixUp(RBTNode<T, K>* &root, RBTNode<T, K>* node);

	// ���뺯��
	int _insert(RBTNode<T, K>* &root, RBTNode<T, K>* node);
	int _insert(RBTNode<T, K>* &root, RBTNode<T, K>* node, int (*compare)(void * a, void * b));

	// ɾ����������
	void _removeFixUp(RBTNode<T, K>* &root, RBTNode<T, K> *node, RBTNode<T, K> *parent);

	// ɾ������
	void _remove(RBTNode<T, K>* &root, RBTNode<T, K> *node);

	// ���ٺ����
	void _destroy(RBTNode<T, K>* &node);

	// ��ӡ�����
	void _dump(RBTNode<T, K>* node, T data);
	void _dump(RBTNode<T, K>* node, T data, void(*NodeDump)(T data));

	// ��ȡ����
	int _getHeight(RBTNode<T, K>* node);

	// ��ȡ�ڵ���
	int _getSize(RBTNode<T, K>* node);

#define rb_parent(r)   ((r)->parent)
#define rb_color(r) ((r)->color)
#define rb_is_red(r)   ((r)->color==RED)
#define rb_is_black(r)  ((r)->color==BLACK)
#define rb_set_black(r)  do { (r)->color = BLACK; } while (0)
#define rb_set_red(r)  do { (r)->color = RED; } while (0)
#define rb_set_parent(r,p)  do { (r)->parent = (p); } while (0)
#define rb_set_color(r,c)  do { (r)->color = (c); } while (0)
};

template <class T, class K>
CRBTree<T, K>::CRBTree(void)
{
	mRoot = NULL;
}


template <class T, class K>
CRBTree<T, K>::~CRBTree(void)
{
	destroy();
}

template <class T, class K>
CRBTree<T, K>::CRBTree(int(*compare)(void * a, void * b))
{
	m_compare = compare;
}

template <class T, class K>
CRBTree<T, K>::CRBTree(int(*compare)(void * a, void * b), void(*node_dump)(T a))
{
	m_compare = compare;
	m_node_dump = node_dump;
}

template <class T, class K>
void  CRBTree<T, K>::set_compare(int(*compare)(void * a, void * b))
{
	m_compare = compare;
}

template <class T, class K>
void CRBTree<T, K>::set_node_dump(void(*node_dump)(T a))
{
	m_node_dump = node_dump;
}

template <class T, class K>
int CRBTree<T, K>::keycompare(K key1, K key2) const
{
	K p = key1;
	K q = key2;

	if (m_compare)
		return m_compare((void*)&key1, (void*)&key2);

	return p < q ? -1 : p == q ? 0 : 1;
}


template <class T, class K>
RBTNode<T, K>* CRBTree<T, K>::search(K key)
{
	return _search(mRoot, key);
}

template <class T, class K>
RBTNode<T, K>* CRBTree<T, K>::iterativeSearch(K key)
{
	return _iterativeSearch(mRoot, key);
}

/*
* �����(dataΪ�ڵ��ֵ)���뵽�������
*
* ����˵����
*     node ������ĸ����
*     data ������ļ�ֵ
*/
template <class T, class K>
int CRBTree<T, K>::insert(T data)
{
	RBTNode<T, K> *z = NULL;

	// ����½����ʧ�ܣ��򷵻ء�
	if ((z = new RBTNode<T, K>(data, data, BLACK, NULL, NULL, NULL)) == NULL)
		return EXIT_FAILURE;

	return _insert(mRoot, z);
}

/*
* �����(dataΪ�ڵ��ֵ)���뵽�������
*
* ����˵����
*     node ������ĸ����
*     data ������ļ�ֵ
*     compare ���ݱȽϺ���
*/
template <class T, class K>
int CRBTree<T, K>::insert(T data, int(*compare)(void * a, void * b))
{
	RBTNode<T, K> *z = NULL;

	// ����½����ʧ�ܣ��򷵻ء�
	if ((z = new RBTNode<T, K>(data, data, BLACK, NULL, NULL, NULL)) == NULL)
		return EXIT_FAILURE;

	return _insert(mRoot, z, compare);
}

/*
* �����(dataΪ�ڵ��ֵ)���뵽�������
*
* ����˵����
*     node ������ĸ����
*     data ������ļ�ֵ
*/
template <class T, class K>
int CRBTree<T, K>::insert(T data, K key)
{
	RBTNode<T, K> *z = NULL;

	// ����½����ʧ�ܣ��򷵻ء�
	if ((z = new RBTNode<T, K>(data, key, BLACK, NULL, NULL, NULL)) == NULL)
		return EXIT_FAILURE;

	return _insert(mRoot, z);
}

/*
* �����(dataΪ�ڵ��ֵ)���뵽�������
*
* ����˵����
*     node ������ĸ����
*     data ������ļ�ֵ
*     compare ���ݱȽϺ���
*/
template <class T, class K>
int CRBTree<T, K>::insert(T data, K key, int (*compare)(void * a, void * b))
{
	RBTNode<T, K> *z = NULL;

	// ����½����ʧ�ܣ��򷵻ء�
	if ((z = new RBTNode<T, K>(data, key, BLACK, NULL, NULL, NULL)) == NULL)
		return EXIT_FAILURE;

	return _insert(mRoot, z, compare);
}

/*
* ɾ��������м�ֵΪdata�Ľڵ�
*
* ����˵����
*     node ������ĸ����
*/
template <class T, class K>
void CRBTree<T, K>::remove(T data)
{
	RBTNode<T, K> *node;

	// ����data��Ӧ�Ľڵ�(node)���ҵ��Ļ���ɾ���ýڵ�
	if ((node = _search(mRoot, data)) != NULL)
		_remove(mRoot, node);
}


template <class T, class K>
void CRBTree<T, K>::destroy()
{
	_destroy(mRoot);
}

template <class T, class K>
void CRBTree<T, K>::dump()
{
	if (mRoot != NULL)
		_dump(mRoot, mRoot->data);
}

template <class T, class K>
void CRBTree<T, K>::dump(void(*NodeDump)(T data))
{
	if (mRoot != NULL)
		_dump(mRoot, mRoot->data, NodeDump);
}

template <class T, class K>
void CRBTree<T, K>::preOrder()
{
	_preOrder(mRoot);
}

template <class T, class K>
void CRBTree<T, K>::inOrder()
{
	_inOrder(mRoot);
}

template <class T, class K>
void CRBTree<T, K>::postOrder()
{
	_postOrder(mRoot);
}

// ��ȡ����
template <class T, class K>
int CRBTree<T, K>::getHeight()
{
	return _getHeight(mRoot);
}

// ��ȡ�ڵ���
template <class T, class K>
int getSize()
{
	return _getHeight(mRoot);
}

/*
* ���ٺ����
*/
template <class T, class K>
void CRBTree<T, K>::_destroy(RBTNode<T, K>* &node)
{
	if (node == NULL)
		return;

	if (node->left != NULL)
		return _destroy(node->left);
	if (node->right != NULL)
		return _destroy(node->right);

	delete node;
	node = NULL;
}

/*
* �Ժ�����Ľڵ�(x)��������ת
*
* ����ʾ��ͼ(�Խڵ�x��������)��
*      px                              px
*     /                               /
*    x                               y
*   /  \      --(����)-->           / \                #
*  lx   y                          x  ry
*     /   \                       /  \
*    ly   ry                     lx  ly
*
*
*/
template <class T, class K>
void CRBTree<T, K>::_leftRotate(RBTNode<T, K>* &root, RBTNode<T, K>* x)
{
	// ����x���Һ���Ϊy
	RBTNode<T, K> *y = x->right;
	// �� ��y�����ӡ� ��Ϊ ��x���Һ��ӡ���
	// ���y�����ӷǿգ��� ��x�� ��Ϊ ��y�����ӵĸ��ס�
	x->right = y->left;
	if (y->left != NULL)
		y->left->parent = x;

	// �� ��x�ĸ��ס� ��Ϊ ��y�ĸ��ס�
	y->parent = x->parent;

	if (x->parent == NULL)
	{
		root = y;            // ��� ��x�ĸ��ס� �ǿսڵ㣬��y��Ϊ���ڵ�
	}
	else
	{
		if (x->parent->left == x)
			x->parent->left = y;    // ��� x�������ڵ�����ӣ���y��Ϊ��x�ĸ��ڵ�����ӡ�
		else
			x->parent->right = y;    // ��� x�������ڵ�����ӣ���y��Ϊ��x�ĸ��ڵ�����ӡ�
	}

	// �� ��x�� ��Ϊ ��y�����ӡ�
	y->left = x;
	// �� ��x�ĸ��ڵ㡱 ��Ϊ ��y��
	x->parent = y;
}

/*
* �Ժ�����Ľڵ�(y)��������ת
*
* ����ʾ��ͼ(�Խڵ�y��������)��
*            py                               py
*           /                                /
*          y                                x
*         /  \      --(����)-->            /  \                     #
*        x   ry                           lx   y
*       / \                                   / \                   #
*      lx  rx                                rx  ry
*
*/
template <class T, class K>
void CRBTree<T, K>::_rightRotate(RBTNode<T, K>* &root, RBTNode<T, K>* y)
{
	// ����x�ǵ�ǰ�ڵ�����ӡ�
	RBTNode<T, K> *x = y->left;

	// �� ��x���Һ��ӡ� ��Ϊ ��y�����ӡ���
	// ���"x���Һ���"��Ϊ�յĻ����� ��y�� ��Ϊ ��x���Һ��ӵĸ��ס�
	y->left = x->right;
	if (x->right != NULL)
		x->right->parent = y;

	// �� ��y�ĸ��ס� ��Ϊ ��x�ĸ��ס�
	x->parent = y->parent;

	if (y->parent == NULL)
	{
		root = x;            // ��� ��y�ĸ��ס� �ǿսڵ㣬��x��Ϊ���ڵ�
	}
	else
	{
		if (y == y->parent->right)
			y->parent->right = x;    // ��� y�������ڵ���Һ��ӣ���x��Ϊ��y�ĸ��ڵ���Һ��ӡ�
		else
			y->parent->left = x;    // (y�������ڵ������) ��x��Ϊ��x�ĸ��ڵ�����ӡ�
	}

	// �� ��y�� ��Ϊ ��x���Һ��ӡ�
	x->right = y;

	// �� ��y�ĸ��ڵ㡱 ��Ϊ ��x��
	y->parent = x;
}

/*
* �����������������
*
* ���������в���ڵ�֮��(ʧȥƽ��)���ٵ��øú�����
* Ŀ���ǽ������������һ�ź������
*
* ����˵����
*     root ������ĸ�
*     node ����Ľ��        // ��Ӧ���㷨���ۡ��е�z
*/
template <class T, class K>
int CRBTree<T, K>::_insertFixUp(RBTNode<T, K>* &root, RBTNode<T, K>* node)
{
	RBTNode<T, K> *parent, *gparent;
	// �������ڵ���ڣ����Ҹ��ڵ����ɫ�Ǻ�ɫ��
	while ((parent = rb_parent(node)) && rb_is_red(parent))
	{
		gparent = rb_parent(parent);
		//�������ڵ㡱�ǡ��游�ڵ�����ӡ�
		if (parent == gparent->left)
		{
			// Case 1����������ڵ��Ǻ�ɫ
			{
				RBTNode<T, K> *uncle = gparent->right;
				if (uncle && rb_is_red(uncle))
				{
					rb_set_black(uncle);
					rb_set_black(parent);
					rb_set_red(gparent);
					node = gparent;
					continue;
				}
			}
			// Case 2�����������Ǻ�ɫ���ҵ�ǰ�ڵ����Һ���
			if (parent->right == node)
			{
				RBTNode<T, K> *tmp;
				_leftRotate(root, parent);
				tmp = parent;
				parent = node;
				node = tmp;
			}
			// Case 3�����������Ǻ�ɫ���ҵ�ǰ�ڵ������ӡ�
			rb_set_black(parent);
			rb_set_red(gparent);
			_rightRotate(root, gparent);
		}
		else//����z�ĸ��ڵ㡱�ǡ�z���游�ڵ���Һ��ӡ�
		{
			// Case 1����������ڵ��Ǻ�ɫ
			{
				RBTNode<T, K> *uncle = gparent->left;
				if (uncle && rb_is_red(uncle))
				{
					rb_set_black(uncle);
					rb_set_black(parent);
					rb_set_red(gparent);
					node = gparent;
					continue;
				}
			}

			// Case 2�����������Ǻ�ɫ���ҵ�ǰ�ڵ�������
			if (parent->left == node)
			{
				RBTNode<T, K> *tmp;
				_rightRotate(root, parent);
				tmp = parent;
				parent = node;
				node = tmp;
			}

			// Case 3�����������Ǻ�ɫ���ҵ�ǰ�ڵ����Һ��ӡ�
			rb_set_black(parent);
			rb_set_red(gparent);
			_leftRotate(root, gparent);
		}
	}
	rb_set_black(root);

	return EXIT_SUCCESS;
}

/*
* �������뵽�������
*
* ����˵����
*     root ������ĸ����
*     node ����Ľ��        // ��Ӧ���㷨���ۡ��е�node
*/
template <class T, class K>
int CRBTree<T, K>::_insert(RBTNode<T, K>* &root, RBTNode<T, K>* node)
{
	RBTNode<T, K> *y = NULL;
	RBTNode<T, K> *x = root;

	// 1. �����������һ�Ŷ�������������ڵ���ӵ�����������С�
	while (x != NULL)
	{
		y = x;
		if (keycompare(node->key, x->key) < 0)
			x = x->left;
		else
			x = x->right;
	}

	node->parent = y;
	if (y != NULL)
	{
		if (keycompare(node->key, y->key) < 0)
			y->left = node;
		else
			y->right = node;
	}
	else
		root = node;

	// 2. ���ýڵ����ɫΪ��ɫ
	node->color = RED;

	// 3. ������������Ϊһ�Ŷ��������
	_insertFixUp(root, node);
	m_iSize++;
	return EXIT_SUCCESS;
}

/*
* �������뵽�������
*
* ����˵����
*     root ������ĸ����
*     node ����Ľ��        // ��Ӧ���㷨���ۡ��е�node
*     compare �ڵ��С�ȽϷ���
*/
template <class T, class K>
int CRBTree<T, K>::_insert(RBTNode<T, K>* &root, RBTNode<T, K>* node, int(*compare)(void * a, void * b))
{
	RBTNode<T, K> *y = NULL;
	RBTNode<T, K> *x = root;

	// 1. �����������һ�Ŷ�������������ڵ���ӵ�����������С�
	while (x != NULL)
	{
		y = x;
		if (compare((void *)&node->key, (void*)&x->key) < 0)
			x = x->left;
		else
			x = x->right;
	}

	node->parent = y;
	if (y != NULL)
	{
		if (compare((void *)&node->key, (void *)&y->key) < 0)
			y->left = node;
		else
			y->right = node;
	}
	else
		root = node;

	// 2. ���ýڵ����ɫΪ��ɫ
	node->color = RED;

	// 3. ������������Ϊһ�Ŷ��������
	_insertFixUp(root, node);
	m_iSize++;
	return EXIT_SUCCESS;
}

/*
* �����ɾ����������
*
* �ڴӺ������ɾ������ڵ�֮��(�����ʧȥƽ��)���ٵ��øú�����
* Ŀ���ǽ������������һ�ź������
*
* ����˵����
*     root ������ĸ�
*     node �������Ľڵ�
*/
template <class T, class K>
void CRBTree<T, K>::_removeFixUp(RBTNode<T, K>* &root, RBTNode<T, K> *node, RBTNode<T, K> *parent)
{
	RBTNode<T, K> *other;

	while ((!node || rb_is_black(node)) && node != root)
	{
		if (parent->left == node)
		{
			other = parent->right;
			if (rb_is_red(other))
			{
				// Case 1: x���ֵ�w�Ǻ�ɫ��  
				rb_set_black(other);
				rb_set_red(parent);
				_leftRotate(root, parent);
				other = parent->right;
			}
			if ((!other->left || rb_is_black(other->left)) &&
				(!other->right || rb_is_black(other->right)))
			{
				// Case 2: x���ֵ�w�Ǻ�ɫ����w����������Ҳ���Ǻ�ɫ��  
				rb_set_red(other);
				node = parent;
				parent = rb_parent(node);
			}
			else
			{
				if (!other->right || rb_is_black(other->right))
				{
					// Case 3: x���ֵ�w�Ǻ�ɫ�ģ�����w�������Ǻ�ɫ���Һ���Ϊ��ɫ��  
					rb_set_black(other->left);
					rb_set_red(other);
					_rightRotate(root, other);
					other = parent->right;
				}
				// Case 4: x���ֵ�w�Ǻ�ɫ�ģ�����w���Һ����Ǻ�ɫ�ģ�����������ɫ��
				rb_set_color(other, rb_color(parent));
				rb_set_black(parent);
				rb_set_black(other->right);
				_leftRotate(root, parent);
				node = root;
				break;
			}
		}
		else
		{
			other = parent->left;
			if (rb_is_red(other))
			{
				// Case 1: x���ֵ�w�Ǻ�ɫ��  
				rb_set_black(other);
				rb_set_red(parent);
				_rightRotate(root, parent);
				other = parent->left;
			}
			if ((!other->left || rb_is_black(other->left)) &&
				(!other->right || rb_is_black(other->right)))
			{
				// Case 2: x���ֵ�w�Ǻ�ɫ����w����������Ҳ���Ǻ�ɫ��  
				rb_set_red(other);
				node = parent;
				parent = rb_parent(node);
			}
			else
			{
				if (!other->left || rb_is_black(other->left))
				{
					// Case 3: x���ֵ�w�Ǻ�ɫ�ģ�����w�������Ǻ�ɫ���Һ���Ϊ��ɫ��  
					rb_set_black(other->right);
					rb_set_red(other);
					_leftRotate(root, other);
					other = parent->left;
				}
				// Case 4: x���ֵ�w�Ǻ�ɫ�ģ�����w���Һ����Ǻ�ɫ�ģ�����������ɫ��
				rb_set_color(other, rb_color(parent));
				rb_set_black(parent);
				rb_set_black(other->left);
				_rightRotate(root, parent);
				node = root;
				break;
			}
		}
	}
	if (node)
		rb_set_black(node);
}

/*
* ɾ�����(node)�������ر�ɾ���Ľ��
*
* ����˵����
*     root ������ĸ����
*     node ɾ���Ľ��
*/
template <class T, class K>
void CRBTree<T, K>::_remove(RBTNode<T, K>* &root, RBTNode<T, K> *node)
{
	RBTNode<T, K> *child, *parent;
	RBTColor color;

	// ��ɾ���ڵ��"���Һ��Ӷ���Ϊ��"�������
	if ((node->left != NULL) && (node->right != NULL))
	{
		// ��ɾ�ڵ�ĺ�̽ڵ㡣(��Ϊ"ȡ���ڵ�")
		// ������ȡ��"��ɾ�ڵ�"��λ�ã�Ȼ���ٽ�"��ɾ�ڵ�"ȥ����
		RBTNode<T, K> *replace = node;

		// ��ȡ��̽ڵ�
		replace = replace->right;
		while (replace->left != NULL)
			replace = replace->left;

		// "node�ڵ�"���Ǹ��ڵ�(ֻ�и��ڵ㲻���ڸ��ڵ�)
		if (rb_parent(node))
		{
			if (rb_parent(node)->left == node)
				rb_parent(node)->left = replace;
			else
				rb_parent(node)->right = replace;
		}
		else
			// "node�ڵ�"�Ǹ��ڵ㣬���¸��ڵ㡣
			root = replace;

		// child��"ȡ���ڵ�"���Һ��ӣ�Ҳ����Ҫ"�����Ľڵ�"��
		// "ȡ���ڵ�"�϶����������ӣ���Ϊ����һ����̽ڵ㡣
		child = replace->right;
		parent = rb_parent(replace);
		// ����"ȡ���ڵ�"����ɫ
		color = rb_color(replace);

		// "��ɾ���ڵ�"��"���ĺ�̽ڵ�ĸ��ڵ�"
		if (parent == node)
		{
			parent = replace;
		}
		else
		{
			// child��Ϊ��
			if (child)
				rb_set_parent(child, parent);
			parent->left = child;

			replace->right = node->right;
			rb_set_parent(node->right, replace);
		}

		replace->parent = node->parent;
		replace->color = node->color;
		replace->left = node->left;
		node->left->parent = replace;

		if (color == BLACK)
			_removeFixUp(root, child, parent);

		delete node;
		return;
	}

	if (node->left != NULL)
		child = node->left;
	else
		child = node->right;

	parent = node->parent;
	// ����"ȡ���ڵ�"����ɫ
	color = node->color;

	if (child)
		child->parent = parent;

	// "node�ڵ�"���Ǹ��ڵ�
	if (parent)
	{
		if (parent->left == node)
			parent->left = child;
		else
			parent->right = child;
	}
	else
		root = child;

	if (color == BLACK)
		_removeFixUp(root, child, parent);
	delete node;
	m_iSize--;
}

// template <class T, class K>
// RBTNode<T, K>* CRBTree<T, K>::_search(RBTNode<T, K>* x, T data) const
// {
// 	if (x == NULL || keycompare(x->data, data) == 0)
// 		return x;
// 
// 	if (keycompare(data, x->data) < 0)
// 		return _search(x->left, data);
// 	else
// 		return _search(x->right, data);
// 
// }
// 
// template <class T, class K>
// RBTNode<T, K>* CRBTree<T, K>::_iterativeSearch(RBTNode<T, K>* x, T data) const
// {
// 	while ((x != NULL) && keycompare(x->data, data) != 0)
// 	{
// 		if (keycompare(data, x->data) < 0)
// 			x = x->left;
// 		else
// 			x = x->right;
// 	}
// 
// 	return x;
// }

template <class T, class K>
RBTNode<T, K>* CRBTree<T, K>::_search(RBTNode<T, K>* x, K key) const
{
	if (x == NULL || keycompare(x->key, key) == 0)
		return x;

	if (keycompare(key, x->key) < 0)
		return _search(x->left, key);
	else
		return _search(x->right, key);

}

template <class T, class K>
RBTNode<T, K>* CRBTree<T, K>::_iterativeSearch(RBTNode<T, K>* x, K key) const
{
	while ((x != NULL) && keycompare(key, x->key) != 0)
	{
		if (keycompare(key, x->key) < 0)
			x = x->left;
		else
			x = x->right;
	}

	return x;
}

/*
* ��ӡ"���������"
*
* data        -- �ڵ�ļ�ֵ
* direction  --  0����ʾ�ýڵ��Ǹ��ڵ�;
*               -1����ʾ�ýڵ������ĸ���������;
*                1����ʾ�ýڵ������ĸ������Һ��ӡ�
*/
template <class T, class K>
void CRBTree<T, K>::_dump(RBTNode<T, K>* node, T data)
{
	if (node != NULL && m_node_dump != NULL)
	{
		m_node_dump(node->data);

		_dump(node->left, node->data);
		_dump(node->right, node->data);
	}
}

/*
* ��ӡ"���������"
*
* data        -- �ڵ�ļ�ֵ
* direction  --  0����ʾ�ýڵ��Ǹ��ڵ�;
*               -1����ʾ�ýڵ������ĸ���������;
*                1����ʾ�ýڵ������ĸ������Һ��ӡ�
*/
template <class T, class K>
void CRBTree<T, K>::_dump(RBTNode<T, K>* node, T data, void(*NodeDump)(T data))
{
	if (node != NULL)
	{
		NodeDump(node->data);

		_dump(node->left, node->data, NodeDump);
		_dump(node->right, node->data, NodeDump);
	}
}

template <class T, class K>
void CRBTree<T, K>::_preOrder(RBTNode<T, K>* node) const
{
	if (node != NULL)
	{
		if (m_node_dump)
			m_node_dump(node->data);

		preOrder(node->left);
		preOrder(node->right);
	}
}

template <class T, class K>
void CRBTree<T, K>::_inOrder(RBTNode<T, K>* node) const
{
	if (node != NULL)
	{
		preOrder(node->left);
		if (m_node_dump)
			m_node_dump(node->data);
		preOrder(node->right);
	}
}

template <class T, class K>
void CRBTree<T, K>::_postOrder(RBTNode<T, K>* node) const
{
	if (node != NULL)
	{
		preOrder(node->left);
		preOrder(node->right);
		if (m_node_dump)
			m_node_dump(node->data);
	}
}

/**
* ��ȡ����
* @param x
* @return
*/
template <class T, class K>
int CRBTree<T, K>::_getHeight(RBTNode<T, K>* node)
{
	int lh, rh, h;

	if (node == NULL)
		return 0;

	lh = _getHeight(node->left);
	rh = _getHeight(node->right);

	h = lh < rh ? lh : rh;

	return (h + 1);
}

/**
* ��ȡ�ڵ���
* @param x
* @return
*/
template <class T, class K>
int CRBTree<T, K>::_getSize(RBTNode<T, K>* node)
{
	return m_iSize;
}