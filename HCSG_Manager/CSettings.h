#pragma once
#include <iostream>
using namespace std;

#include "SQLite3Helper.h"

// 用于静态配置参数名和默认值
struct CSettingAKV
{
	string m_sAppName;
	string m_sKey;
	string m_sValue;
};

enum eSettings {
	SQL_SERVERIP = 0,
	SQL_ACCOUNT,
	SQL_PASSWORD,
	SQL_TABLE_ACCOUNT_NAME,
	SQL_TABLE_XB_NAME,
	SERVER_ROOTPATH,
};

class CSettings
{
public:
	CSettings();
	~CSettings();

private:
	CSqlite3Helper m_CSqliteHelper;
	CString _Get(string csAppName, string csKey);
	int _Set(string csAppName, string csKey, CString csVal);

protected:
// #define APP_NAME_SQLSERVER "SQLSERVER"
// #define KEY_SERVERIP "SERVERIP"
// #define KET_ACCOUNT "ACCOUNT"
// #define KET_PASSWORD "PASSWORD"
// #define KET_SERVER_PATH "SERVER_PATH"
// #define KET_TABLE_ACCOUNT_NAME "TABLE_ACCOUNT_NAME"
// #define KET_TABLE_XB_NAME "TABLE_XB_NAME"
// 	CString m_csServerPath;
// 	CString m_csSQLServer;
// 	CString m_csSQLAccount;
// 	CString m_csSQLPassWord;
// 	CString m_csTableAccountName;
// 	CString m_csTableXbName;

public:
	CString Get(int iIndex);
	int Set(int iIndex, CString csVal);

	CString GetSQLServerIP();
	int SetSQLServerIP(CString csVal);
	CString GetSQLAccount();
	int SetSQLAccount(CString csVal);
	CString GetSQLPassWord();
	int SetSQLPassWord(CString csVal);
	CString GetTableAccountName();
	int SetTableAccountName(CString csVal);
	CString GetTableXbName();
	int SetTableXbName(CString csval);
	CString GetServerRootPath();
	int SetServerRootPath(CString csVal);
};
