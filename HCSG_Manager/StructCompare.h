#pragma once

// ����ṹ�������ж������õĻ���������������ã��ṹ�嶨���ʱ����Ҫ1�ֽڶ���

template <class TYPE>
BOOL StructCmp(const TYPE &data1, const TYPE &data2)
{
	return (memcmp(reinterpret_cast<const VOID *>(&data1), reinterpret_cast<const VOID *>(&data2), sizeof(TYPE)) == 0);
}
