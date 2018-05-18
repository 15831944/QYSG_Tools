#pragma once

using namespace std;

// Binary Search algorithm

#define INVALID_INDEX -1

// �ݹ鷽��
template<class T, class K> // ʹ��ģ��
int BSearch(const T* theArray, // ��Ҫ���ҵ�����, Ĭ�Ͼ�������
	int low, // ������ʼ����
	int high, // �����������
	const K& key, // ��Ҫ���ҵ� key �����Ϳ��Բ�����������ͬ
	int(*compare)(const T&, const K&, void* param), // �ȽϺ����ĺ���ָ��
	void *param) // ���ӱȽϲ������������� compare �и����ж�
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
		//�м�Ԫ��С�� key����ʾԪ�����ұ�  
		indexRet = BSearch(theArray, mid + 1, high, key, compare, param);
	}
	else
	{
		indexRet = BSearch(theArray, low, mid - 1, key, compare, param);
	}

	return indexRet;
}

// �ǵݹ鷽��
template<class T, class K> // ʹ��ģ��
int BSearch(const T* theArray, // ��Ҫ���ҵ�����, Ĭ�Ͼ�������
	int length, // ����Ԫ�ظ���
	const K& key, // ��Ҫ���ҵ� key �����Ϳ��Բ�����������ͬ
	int(*compare)(const T&, const K&, void* param), // �ȽϺ����ĺ���ָ��
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

//������ֵiData�ڳ���ΪiLen��pDataArray�����еĲ���λ��
template<class T, class K> // ʹ��ģ��
int FindInsertIndex(const T* pDataArray,
	int iLen,
	const K& key,
	int(*compare)(const T&, const K&, void* param), // �ȽϺ����ĺ���ָ��
	void *param)
{
	int iBegin = 0;
	int iEnd = iLen - 1;
	int index = -1;    //��¼����λ��  
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