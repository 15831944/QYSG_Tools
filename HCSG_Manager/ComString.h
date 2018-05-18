#pragma once
#include <iostream>
using namespace std;

// string to CString
CString STDStr2CStr(string sVal);
// CString to string
string CStr2STDStr(CString csVal);

string Int2STDStr(const int &int_temp);
int STDStr2Int(const string &string_temp);

string Big2GB(CString csBig5);
char* ASCIIToUTF8(const char* unicode);