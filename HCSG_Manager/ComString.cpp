#include "stdafx.h"
#include "ComString.h"
#include <sstream>
#include <iostream>
using namespace std;

// string to CString
CString STDStr2CStr(string sVal)
{
	CString csTemp;
	csTemp.Format("%s", sVal.c_str());
	return csTemp;
}
// CString to string
string CStr2STDStr(CString csVal)
{
	string sTemp = csVal;
	return sTemp;
}

string Int2STDStr(const int &int_temp)
{
	string string_temp;
	stringstream stream;
	stream << int_temp;
	string_temp = stream.str();   //此处也可以用 stream>>string_temp 
	return string_temp;
}

int STDStr2Int(const string &string_temp)
{
	int int_temp;
	stringstream stream(string_temp);
	stream >> int_temp;
	return int_temp;
}

CString GB2Big(char* sGb)
{
	char*  pszGbt = NULL;
	char*  pszGbs = NULL;
	wchar_t*  wszUnicode = NULL;
	char*  pszBig5 = NULL;
	CString  sBig5;
	int  iLen = 0;

	pszGbs = sGb;
	iLen = MultiByteToWideChar(936, 0, pszGbs, -1, NULL, 0);
	pszGbt = new  char[iLen * 2 + 1];
	LCMapString(0x0804, LCMAP_TRADITIONAL_CHINESE, pszGbs, -1, pszGbt, iLen * 2);
	wszUnicode = new  wchar_t[iLen + 1];
	MultiByteToWideChar(936, 0, pszGbt, -1, wszUnicode, iLen);
	iLen = WideCharToMultiByte(950, 0, (PWSTR)wszUnicode, -1, NULL, 0, NULL, NULL);
	pszBig5 = new  char[iLen + 1];
	WideCharToMultiByte(950, 0, (PWSTR)wszUnicode, -1, pszBig5, iLen, NULL, NULL);
	sBig5 = pszBig5;
	delete[]  wszUnicode;
	wszUnicode = NULL;
	delete[]  pszGbt;
	pszGbt = NULL;
	delete[]  pszBig5;
	pszBig5 = NULL;

	return  sBig5;
}

string GB2Big(CString csGb)
{
	return CStr2STDStr(GB2Big((LPSTR)(LPCTSTR)csGb));
}

CString Big2GB(char* sBig5)
{
	// TODO: Add your control notification handler code here
	char buf[2048];
	char GbBuf[2048];
	WCHAR wbuf[2048];

	CString  sRetBig5;

	ZeroMemory(buf, sizeof(buf));
	ZeroMemory(GbBuf, sizeof(GbBuf));
	ZeroMemory(wbuf, sizeof(wbuf));
	MultiByteToWideChar(950, 0, (LPCTSTR)sBig5, -1, wbuf, 2046);

	//转换Unicode码到Gb码繁体，使用API函数WideCharToMultiByte
	WideCharToMultiByte(936, 0, wbuf, -1, buf, sizeof(buf), NULL, NULL);

	//转换Gb码繁体到Gb码简体，使用API函数LCMapString
	LCMapString(0x0804, LCMAP_SIMPLIFIED_CHINESE, buf, -1, GbBuf, 2048);

	sRetBig5 = GbBuf;
	return  sRetBig5;
}

string Big2GB(CString csBig5)
{
	return CStr2STDStr(Big2GB((LPSTR)(LPCTSTR)csBig5));
}

/*功能：unicode转换为utf8编码
输入：unicode类型的字符串
输出：utf8类型的char*型数据
*/
char* ASCIIToUTF8(const char* cAscii)
{
	int len = WideCharToMultiByte(CP_UTF8, 0, (LPCWSTR)cAscii, -1, NULL, 0, NULL, NULL);
	char *cUTF8 = new char[len + 1];
	//先将ASCII码转换为Unicode编码  
	int nlen = MultiByteToWideChar(CP_ACP, 0, cAscii, -1, NULL, NULL);
	wchar_t *pUnicode = new wchar_t[len+1];
	memset(pUnicode, 0, nlen*sizeof(wchar_t));
	MultiByteToWideChar(CP_ACP, 0, cAscii, -1, (LPWSTR)pUnicode, nlen);
	wstring wsUnicode = pUnicode;
	//将Unicode编码转换为UTF-8编码  
	nlen = WideCharToMultiByte(CP_UTF8, 0, wsUnicode.c_str(), -1, NULL, 0, NULL, NULL);
	WideCharToMultiByte(CP_UTF8, 0, wsUnicode.c_str(), -1, cUTF8, nlen, NULL, NULL);

	return cUTF8;
}
/*功能：utf8转换为unicode编码
输入：utf8类型的字符串
输出：unicode类型的char*型数据
*/
char* UTF8ToASCII(char* cUTF8)
{
// 	string str = cUTF8;
// 	//先将UTF8编码转换为Unicode编码  
// 	int nLen = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);
// 	wchar_t *pwcUnicode = new wchar_t[nLen];
// 	memset(pwcUnicode, 0, nLen*sizeof(wchar_t));
// 	MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, (LPWSTR)pwcUnicode, nLen);
// 	//将Unicode编码转换为ASCII编码  
// 	nLen = WideCharToMultiByte(CP_ACP, 0, pwcUnicode, -1, NULL, 0, NULL, NULL);
// 	WideCharToMultiByte(CP_ACP, 0, pwcUnicode, -1, ASCII, nLen, NULL, NULL);
	return NULL;
}