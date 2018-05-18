#pragma once

// 如果结构体里面有对齐设置的话，这个方法不适用，结构体定义的时候需要1字节对齐

template <class TYPE>
BOOL StructCmp(const TYPE &data1, const TYPE &data2)
{
	return (memcmp(reinterpret_cast<const VOID *>(&data1), reinterpret_cast<const VOID *>(&data2), sizeof(TYPE)) == 0);
}
