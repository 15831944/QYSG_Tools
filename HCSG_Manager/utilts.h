#pragma once

#define INDEX_KEYS_END (-1)

void TickStart();
void TickEnd();

int IntCompare(int a, int b, void* param);
int StringCompare(void * a, void * b);

int Offset2pTreeCompare(const struct COffset2Tree& a, const int& b, void* param);