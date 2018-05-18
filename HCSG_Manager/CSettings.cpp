#include "stdafx.h"
#include "CSettings.h"
#include "ComString.h"

CSettings::CSettings()
{
	m_CSqliteHelper.Open();
}

CSettings::~CSettings()
{
	m_CSqliteHelper.Close();
}

static const struct CSettingAKV g_CSettingAKV[] = {
	{ "SQLSERVER", "SERVERIP", "" },
	{ "SQLSERVER", "ACCOUNT", "" },
	{ "SQLSERVER", "PASSWORD", "" },
	{ "SQLSERVER", "TABLE_ACCOUNT_NAME", "" },
	{ "SQLSERVER", "TABLE_XB_NAME", "" },
	{ "SERVER", "ROOTPATH", "" },
	{ "", "", "" },
};

CString CSettings::_Get(string csAppName, string csKey)
{
	string sValue;
	m_CSqliteHelper.ReadProfileValue(csAppName, csKey, sValue);
	return STDStr2CStr(sValue);
}

int CSettings::_Set(string csAppName, string csKey, CString csVal)
{
	if (m_CSqliteHelper.WriteProfileValue(csAppName, csKey, CStr2STDStr(csVal)))
		return EXIT_FAILURE;
	return EXIT_SUCCESS;
}

CString CSettings::Get(int iIndex)
{
	return _Get(g_CSettingAKV[iIndex].m_sAppName, g_CSettingAKV[iIndex].m_sKey);
}

int CSettings::Set(int iIndex, CString csVal)
{
	return _Set(g_CSettingAKV[iIndex].m_sAppName, g_CSettingAKV[iIndex].m_sKey, csVal);
}

CString CSettings::GetSQLServerIP()
{
	return Get(SQL_SERVERIP);
}

int CSettings::SetSQLServerIP(CString csVal)
{
	return Set(SQL_SERVERIP, csVal);
}

CString CSettings::GetSQLAccount()
{
	return Get(SQL_ACCOUNT);
}

int CSettings::SetSQLAccount(CString csVal)
{
	return Set(SQL_ACCOUNT, csVal);
}

CString CSettings::GetSQLPassWord()
{
	return Get(SQL_PASSWORD);
}

int CSettings::SetSQLPassWord(CString csVal)
{
	return Set(SQL_PASSWORD, csVal);
}

CString CSettings::GetTableAccountName()
{
	return Get(SQL_TABLE_ACCOUNT_NAME);
}

int CSettings::SetTableAccountName(CString csVal)
{
	return Set(SQL_TABLE_ACCOUNT_NAME, csVal);
}

CString CSettings::GetTableXbName()
{
	return Get(SQL_TABLE_XB_NAME);
}

int CSettings::SetTableXbName(CString csVal)
{
	return Set(SQL_TABLE_XB_NAME, csVal);
}

CString CSettings::GetServerRootPath()
{
	return Get(SERVER_ROOTPATH);
}

int CSettings::SetServerRootPath(CString csVal)
{
	return Set(SERVER_ROOTPATH, csVal);
}