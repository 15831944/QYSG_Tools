#pragma once
#include "stdafx.h"
#include <iomanip>
#include <iostream>
using namespace std;

/*
* Red black tree（红黑树）
* 1、支持简单数据类型（int，char，float...）和结构体类型（struct）
* 2、数据保存节点中，所有键值索引只能设置一个
* 3、简单数据类型，数据和键值一样，复杂数据类型需要单独设置键值
* 4、需要改进成树上的节点只记录数据的指针，树只作为索引，每个索引建立相应的一棵树
*/

enum RBTColor
{
	RED,
	BLACK
};

template <class T, class K>
class RBTNode{
public:
	K key;             // 关键字(键值)
	T data;            // 数据，可以是简单类型也可以是结构体等复杂类型
	RBTColor color;    // 颜色
	RBTNode *left;     // 左孩子
	RBTNode *right;    // 右孩子
	RBTNode *parent;   // 父结点

	RBTNode(T d, K k, RBTColor c, RBTNode *p, RBTNode *l, RBTNode *r) :
		data(d), key(k), color(c), parent(), left(l), right(r) {}
};

template <class T, class K>
class CRBTree
{
private:
	RBTNode<T, K> *mRoot;    // 根结点
	int m_iSize = 0;	// 节点数量
	//int (*m_compare)(T a, T b) = NULL;	 // 节点比较接口
	int(*m_compare)(void * a, void * b) = NULL;	 // 键值比较接口
	void (*m_node_dump)(T data) = NULL;		// 节点打印接口

public:
	CRBTree(void);
	~CRBTree(void);
	//CRBTree(int(*compare)(T a, T b), int(*compare)(K a, K b), void(*node_dump)(T a));
	CRBTree(int(*compare)(void * a, void * b));
	CRBTree(int(*compare)(void * a, void * b), void(*node_dump)(T a));

	//void set_compare(int(*compare)(T a, T b));
	void set_compare(int(*compare)(void * a, void * b));
	void set_node_dump(void(*node_dump)(T a));

	// 前序遍历"红黑树"
	void preOrder();
	// 中序遍历"红黑树"
	void inOrder();
	// 后序遍历"红黑树"
	void postOrder();

	// 将结点(data为节点键值)插入到红黑树中
	// 对于简单数据类型，data和key值是一样的，参数只需要设置一个，防止出现重定义
	int insert(T data);
	int insert(T data, int(*compare)(void * a, void * b));
	// 对于复杂数据类型，data和key值是不一样的，参数需要传入data和key值
	int insert(T data, K key);
	int insert(T data, K key, int(*compare)(void * a, void * b));

	// (递归实现)查找"红黑树"中data里面有key的节点
	RBTNode<T, K>* search(K key);
	// (非递归实现)查找"红黑树"中data里面有key的节点
	RBTNode<T, K>* iterativeSearch(K key);

	// 删除结点(data为节点键值)
	void remove(T data);

	// 销毁红黑树
	void destroy();

	// 打印红黑树, 不能使用在data不是简单数据类型的情况
	void dump();
	void dump(void(*NodeDump)(T data));

	// 获取树高
	int getHeight();

	// 获取节点数
	int getSize();

private:
	int keycompare(K key1, K key2) const;

	// 前序遍历"红黑树"
	void _preOrder(RBTNode<T, K>* node) const;
	// 中序遍历"红黑树"
	void _inOrder(RBTNode<T, K>* node) const;
	// 后序遍历"红黑树"
	void _postOrder(RBTNode<T, K>* node) const;

	// (递归实现)查找"红黑树x"中键值为key的节点, 对于简单数据类型，key就是data，对于复杂数据类型则使用设置的key值
	RBTNode<T, K>* _search(RBTNode<T, K>* x, K key) const;
	RBTNode<T, K>* _iterativeSearch(RBTNode<T, K>* x, K key) const;

	// 左旋
	void _leftRotate(RBTNode<T, K>* &root, RBTNode<T, K>* x);

	// 右旋
	void _rightRotate(RBTNode<T, K>* &root, RBTNode<T, K>* y);

	// 插入修正函数
	int _insertFixUp(RBTNode<T, K>* &root, RBTNode<T, K>* node);

	// 插入函数
	int _insert(RBTNode<T, K>* &root, RBTNode<T, K>* node);
	int _insert(RBTNode<T, K>* &root, RBTNode<T, K>* node, int (*compare)(void * a, void * b));

	// 删除修正函数
	void _removeFixUp(RBTNode<T, K>* &root, RBTNode<T, K> *node, RBTNode<T, K> *parent);

	// 删除函数
	void _remove(RBTNode<T, K>* &root, RBTNode<T, K> *node);

	// 销毁红黑树
	void _destroy(RBTNode<T, K>* &node);

	// 打印红黑树
	void _dump(RBTNode<T, K>* node, T data);
	void _dump(RBTNode<T, K>* node, T data, void(*NodeDump)(T data));

	// 获取树高
	int _getHeight(RBTNode<T, K>* node);

	// 获取节点数
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
* 将结点(data为节点键值)插入到红黑树中
*
* 参数说明：
*     node 红黑树的根结点
*     data 插入结点的键值
*/
template <class T, class K>
int CRBTree<T, K>::insert(T data)
{
	RBTNode<T, K> *z = NULL;

	// 如果新建结点失败，则返回。
	if ((z = new RBTNode<T, K>(data, data, BLACK, NULL, NULL, NULL)) == NULL)
		return EXIT_FAILURE;

	return _insert(mRoot, z);
}

/*
* 将结点(data为节点键值)插入到红黑树中
*
* 参数说明：
*     node 红黑树的根结点
*     data 插入结点的键值
*     compare 数据比较函数
*/
template <class T, class K>
int CRBTree<T, K>::insert(T data, int(*compare)(void * a, void * b))
{
	RBTNode<T, K> *z = NULL;

	// 如果新建结点失败，则返回。
	if ((z = new RBTNode<T, K>(data, data, BLACK, NULL, NULL, NULL)) == NULL)
		return EXIT_FAILURE;

	return _insert(mRoot, z, compare);
}

/*
* 将结点(data为节点键值)插入到红黑树中
*
* 参数说明：
*     node 红黑树的根结点
*     data 插入结点的键值
*/
template <class T, class K>
int CRBTree<T, K>::insert(T data, K key)
{
	RBTNode<T, K> *z = NULL;

	// 如果新建结点失败，则返回。
	if ((z = new RBTNode<T, K>(data, key, BLACK, NULL, NULL, NULL)) == NULL)
		return EXIT_FAILURE;

	return _insert(mRoot, z);
}

/*
* 将结点(data为节点键值)插入到红黑树中
*
* 参数说明：
*     node 红黑树的根结点
*     data 插入结点的键值
*     compare 数据比较函数
*/
template <class T, class K>
int CRBTree<T, K>::insert(T data, K key, int (*compare)(void * a, void * b))
{
	RBTNode<T, K> *z = NULL;

	// 如果新建结点失败，则返回。
	if ((z = new RBTNode<T, K>(data, key, BLACK, NULL, NULL, NULL)) == NULL)
		return EXIT_FAILURE;

	return _insert(mRoot, z, compare);
}

/*
* 删除红黑树中键值为data的节点
*
* 参数说明：
*     node 红黑树的根结点
*/
template <class T, class K>
void CRBTree<T, K>::remove(T data)
{
	RBTNode<T, K> *node;

	// 查找data对应的节点(node)，找到的话就删除该节点
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

// 获取树高
template <class T, class K>
int CRBTree<T, K>::getHeight()
{
	return _getHeight(mRoot);
}

// 获取节点数
template <class T, class K>
int getSize()
{
	return _getHeight(mRoot);
}

/*
* 销毁红黑树
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
* 对红黑树的节点(x)进行左旋转
*
* 左旋示意图(对节点x进行左旋)：
*      px                              px
*     /                               /
*    x                               y
*   /  \      --(左旋)-->           / \                #
*  lx   y                          x  ry
*     /   \                       /  \
*    ly   ry                     lx  ly
*
*
*/
template <class T, class K>
void CRBTree<T, K>::_leftRotate(RBTNode<T, K>* &root, RBTNode<T, K>* x)
{
	// 设置x的右孩子为y
	RBTNode<T, K> *y = x->right;
	// 将 “y的左孩子” 设为 “x的右孩子”；
	// 如果y的左孩子非空，将 “x” 设为 “y的左孩子的父亲”
	x->right = y->left;
	if (y->left != NULL)
		y->left->parent = x;

	// 将 “x的父亲” 设为 “y的父亲”
	y->parent = x->parent;

	if (x->parent == NULL)
	{
		root = y;            // 如果 “x的父亲” 是空节点，则将y设为根节点
	}
	else
	{
		if (x->parent->left == x)
			x->parent->left = y;    // 如果 x是它父节点的左孩子，则将y设为“x的父节点的左孩子”
		else
			x->parent->right = y;    // 如果 x是它父节点的左孩子，则将y设为“x的父节点的左孩子”
	}

	// 将 “x” 设为 “y的左孩子”
	y->left = x;
	// 将 “x的父节点” 设为 “y”
	x->parent = y;
}

/*
* 对红黑树的节点(y)进行右旋转
*
* 右旋示意图(对节点y进行左旋)：
*            py                               py
*           /                                /
*          y                                x
*         /  \      --(右旋)-->            /  \                     #
*        x   ry                           lx   y
*       / \                                   / \                   #
*      lx  rx                                rx  ry
*
*/
template <class T, class K>
void CRBTree<T, K>::_rightRotate(RBTNode<T, K>* &root, RBTNode<T, K>* y)
{
	// 设置x是当前节点的左孩子。
	RBTNode<T, K> *x = y->left;

	// 将 “x的右孩子” 设为 “y的左孩子”；
	// 如果"x的右孩子"不为空的话，将 “y” 设为 “x的右孩子的父亲”
	y->left = x->right;
	if (x->right != NULL)
		x->right->parent = y;

	// 将 “y的父亲” 设为 “x的父亲”
	x->parent = y->parent;

	if (y->parent == NULL)
	{
		root = x;            // 如果 “y的父亲” 是空节点，则将x设为根节点
	}
	else
	{
		if (y == y->parent->right)
			y->parent->right = x;    // 如果 y是它父节点的右孩子，则将x设为“y的父节点的右孩子”
		else
			y->parent->left = x;    // (y是它父节点的左孩子) 将x设为“x的父节点的左孩子”
	}

	// 将 “y” 设为 “x的右孩子”
	x->right = y;

	// 将 “y的父节点” 设为 “x”
	y->parent = x;
}

/*
* 红黑树插入修正函数
*
* 在向红黑树中插入节点之后(失去平衡)，再调用该函数；
* 目的是将它重新塑造成一颗红黑树。
*
* 参数说明：
*     root 红黑树的根
*     node 插入的结点        // 对应《算法导论》中的z
*/
template <class T, class K>
int CRBTree<T, K>::_insertFixUp(RBTNode<T, K>* &root, RBTNode<T, K>* node)
{
	RBTNode<T, K> *parent, *gparent;
	// 若“父节点存在，并且父节点的颜色是红色”
	while ((parent = rb_parent(node)) && rb_is_red(parent))
	{
		gparent = rb_parent(parent);
		//若“父节点”是“祖父节点的左孩子”
		if (parent == gparent->left)
		{
			// Case 1条件：叔叔节点是红色
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
			// Case 2条件：叔叔是黑色，且当前节点是右孩子
			if (parent->right == node)
			{
				RBTNode<T, K> *tmp;
				_leftRotate(root, parent);
				tmp = parent;
				parent = node;
				node = tmp;
			}
			// Case 3条件：叔叔是黑色，且当前节点是左孩子。
			rb_set_black(parent);
			rb_set_red(gparent);
			_rightRotate(root, gparent);
		}
		else//若“z的父节点”是“z的祖父节点的右孩子”
		{
			// Case 1条件：叔叔节点是红色
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

			// Case 2条件：叔叔是黑色，且当前节点是左孩子
			if (parent->left == node)
			{
				RBTNode<T, K> *tmp;
				_rightRotate(root, parent);
				tmp = parent;
				parent = node;
				node = tmp;
			}

			// Case 3条件：叔叔是黑色，且当前节点是右孩子。
			rb_set_black(parent);
			rb_set_red(gparent);
			_leftRotate(root, gparent);
		}
	}
	rb_set_black(root);

	return EXIT_SUCCESS;
}

/*
* 将结点插入到红黑树中
*
* 参数说明：
*     root 红黑树的根结点
*     node 插入的结点        // 对应《算法导论》中的node
*/
template <class T, class K>
int CRBTree<T, K>::_insert(RBTNode<T, K>* &root, RBTNode<T, K>* node)
{
	RBTNode<T, K> *y = NULL;
	RBTNode<T, K> *x = root;

	// 1. 将红黑树当作一颗二叉查找树，将节点添加到二叉查找树中。
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

	// 2. 设置节点的颜色为红色
	node->color = RED;

	// 3. 将它重新修正为一颗二叉查找树
	_insertFixUp(root, node);
	m_iSize++;
	return EXIT_SUCCESS;
}

/*
* 将结点插入到红黑树中
*
* 参数说明：
*     root 红黑树的根结点
*     node 插入的结点        // 对应《算法导论》中的node
*     compare 节点大小比较方法
*/
template <class T, class K>
int CRBTree<T, K>::_insert(RBTNode<T, K>* &root, RBTNode<T, K>* node, int(*compare)(void * a, void * b))
{
	RBTNode<T, K> *y = NULL;
	RBTNode<T, K> *x = root;

	// 1. 将红黑树当作一颗二叉查找树，将节点添加到二叉查找树中。
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

	// 2. 设置节点的颜色为红色
	node->color = RED;

	// 3. 将它重新修正为一颗二叉查找树
	_insertFixUp(root, node);
	m_iSize++;
	return EXIT_SUCCESS;
}

/*
* 红黑树删除修正函数
*
* 在从红黑树中删除插入节点之后(红黑树失去平衡)，再调用该函数；
* 目的是将它重新塑造成一颗红黑树。
*
* 参数说明：
*     root 红黑树的根
*     node 待修正的节点
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
				// Case 1: x的兄弟w是红色的  
				rb_set_black(other);
				rb_set_red(parent);
				_leftRotate(root, parent);
				other = parent->right;
			}
			if ((!other->left || rb_is_black(other->left)) &&
				(!other->right || rb_is_black(other->right)))
			{
				// Case 2: x的兄弟w是黑色，且w的俩个孩子也都是黑色的  
				rb_set_red(other);
				node = parent;
				parent = rb_parent(node);
			}
			else
			{
				if (!other->right || rb_is_black(other->right))
				{
					// Case 3: x的兄弟w是黑色的，并且w的左孩子是红色，右孩子为黑色。  
					rb_set_black(other->left);
					rb_set_red(other);
					_rightRotate(root, other);
					other = parent->right;
				}
				// Case 4: x的兄弟w是黑色的；并且w的右孩子是红色的，左孩子任意颜色。
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
				// Case 1: x的兄弟w是红色的  
				rb_set_black(other);
				rb_set_red(parent);
				_rightRotate(root, parent);
				other = parent->left;
			}
			if ((!other->left || rb_is_black(other->left)) &&
				(!other->right || rb_is_black(other->right)))
			{
				// Case 2: x的兄弟w是黑色，且w的俩个孩子也都是黑色的  
				rb_set_red(other);
				node = parent;
				parent = rb_parent(node);
			}
			else
			{
				if (!other->left || rb_is_black(other->left))
				{
					// Case 3: x的兄弟w是黑色的，并且w的左孩子是红色，右孩子为黑色。  
					rb_set_black(other->right);
					rb_set_red(other);
					_leftRotate(root, other);
					other = parent->left;
				}
				// Case 4: x的兄弟w是黑色的；并且w的右孩子是红色的，左孩子任意颜色。
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
* 删除结点(node)，并返回被删除的结点
*
* 参数说明：
*     root 红黑树的根结点
*     node 删除的结点
*/
template <class T, class K>
void CRBTree<T, K>::_remove(RBTNode<T, K>* &root, RBTNode<T, K> *node)
{
	RBTNode<T, K> *child, *parent;
	RBTColor color;

	// 被删除节点的"左右孩子都不为空"的情况。
	if ((node->left != NULL) && (node->right != NULL))
	{
		// 被删节点的后继节点。(称为"取代节点")
		// 用它来取代"被删节点"的位置，然后再将"被删节点"去掉。
		RBTNode<T, K> *replace = node;

		// 获取后继节点
		replace = replace->right;
		while (replace->left != NULL)
			replace = replace->left;

		// "node节点"不是根节点(只有根节点不存在父节点)
		if (rb_parent(node))
		{
			if (rb_parent(node)->left == node)
				rb_parent(node)->left = replace;
			else
				rb_parent(node)->right = replace;
		}
		else
			// "node节点"是根节点，更新根节点。
			root = replace;

		// child是"取代节点"的右孩子，也是需要"调整的节点"。
		// "取代节点"肯定不存在左孩子！因为它是一个后继节点。
		child = replace->right;
		parent = rb_parent(replace);
		// 保存"取代节点"的颜色
		color = rb_color(replace);

		// "被删除节点"是"它的后继节点的父节点"
		if (parent == node)
		{
			parent = replace;
		}
		else
		{
			// child不为空
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
	// 保存"取代节点"的颜色
	color = node->color;

	if (child)
		child->parent = parent;

	// "node节点"不是根节点
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
* 打印"二叉查找树"
*
* data        -- 节点的键值
* direction  --  0，表示该节点是根节点;
*               -1，表示该节点是它的父结点的左孩子;
*                1，表示该节点是它的父结点的右孩子。
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
* 打印"二叉查找树"
*
* data        -- 节点的键值
* direction  --  0，表示该节点是根节点;
*               -1，表示该节点是它的父结点的左孩子;
*                1，表示该节点是它的父结点的右孩子。
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
* 获取树高
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
* 获取节点数
* @param x
* @return
*/
template <class T, class K>
int CRBTree<T, K>::_getSize(RBTNode<T, K>* node)
{
	return m_iSize;
}