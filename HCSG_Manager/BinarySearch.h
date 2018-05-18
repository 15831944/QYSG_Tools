#pragma once

using namespace std;

// Binary Search algorithm

#define INVALID_INDEX -1

// 递归方法
template<class T, class K> // 使用模板
int BSearch(const T* theArray, // 需要查找的数组, 默认就是数组
	int low, // 数组起始坐标
	int high, // 数组结束坐标
	const K& key, // 需要查找的 key ，类型可以不必与数组相同
	int(*compare)(const T&, const K&, void* param), // 比较函数的函数指针
	void *param) // 附加比较参数，将被传入 compare 中辅助判断
{
	if (theArray == NULL || low > high)
		return INVALID_INDEX;

	int indexRet = INVALID_INDEX;
	int mid = (low + high) / 2;
	int cmp = compare(theArray[mid], key, param);

	if (cmp == 0)
	{
		indexRet = mid;
	}
	else if (cmp < 0)
	{
		//中间元素小于 key，表示元素在右边  
		indexRet = BSearch(theArray, mid + 1, high, key, compare, param);
	}
	else
	{
		indexRet = BSearch(theArray, low, mid - 1, key, compare, param);
	}

	return indexRet;
}

// 非递归方法
template<class T, class K> // 使用模板
int BSearch(const T* theArray, // 需要查找的数组, 默认就是数组
	int length, // 数组元素个数
	const K& key, // 需要查找的 key ，类型可以不必与数组相同
	int(*compare)(const T&, const K&, void* param), // 比较函数的函数指针
	void *param)
{
	if (theArray == NULL || length == 0)
		return INVALID_INDEX;

	int low = 0;
	int high = length - 1;
	int mid = 0;

	while (low <= high)
	{
		mid = (low + high) / 2;

		if (compare(theArray[mid], key, param) < 0)
			low = mid + 1;
		else if (compare(theArray[mid], key, param) > 0)
			high = mid - 1;
		else
			return mid;
	}

	return INVALID_INDEX;
}

//查找数值iData在长度为iLen的pDataArray数组中的插入位置
template<class T, class K> // 使用模板
int FindInsertIndex(const T* pDataArray,
	int iLen,
	const K& key,
	int(*compare)(const T&, const K&, void* param), // 比较函数的函数指针
	void *param)
{
	int iBegin = 0;
	int iEnd = iLen - 1;
	int index = -1;    //记录插入位置  
	while (iBegin <= iEnd)
	{
		index = (iBegin + iEnd) / 2;
		if (compare(pDataArray[index], key, param) > 0)
			iEnd = index - 1;
		else
			iBegin = index + 1;
	}
	if (compare(pDataArray[index], key, param) <= 0)
		index++;
	return index;
}