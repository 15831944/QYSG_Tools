#include "stdafx.h"
#include "HCSG_Manager.h"
#include "RcsManager.h"
#include "ComString.h"
#include "utilts.h"

struct CRcsFilesDefine g_cRcsFilesDefine[] = {
	{ RCS_TPYE_DEF, "item.h", UpdateItems },
	{ RCS_TPYE_DEF, "stage.h", UpdateStageInfo },
	{ RCS_TYPE_DATA, "players.dat", UpdatePlayersInfo },
	{ RCS_TYPE_DATA, "organize.dat", NULL },
	//	{ RCS_TYPE_DATA, "item.dat", NULL },
	//	{ RCS_TYPE_DATA, "store.dat", NULL },
	{ RCS_TYPE_INI, "LoginHistory.ini", NULL },
	{ RCS_TYPE_INI, "LoginServer.ini", NULL },
};

int UpdateItems(CRcsFile * pCRcsFile)
{
	CString strPathName = pCRcsFile->m_csFileName;
	struct ItemDef l_cItemDef;
	int ret = 0;

	CString szLine = "";
	CString strGap = _T(" ");
	TickStart();

	//检查文件是否存在
	DWORD dwRe = GetFileAttributes(strPathName);
	if (dwRe != (DWORD)-1)
	{
		//ShellExecute(NULL, NULL, strFilePath, NULL, NULL, SW_RESTORE); 
	}
	else
	{
		TRACE(strPathName + " 文件不存在！");
		return EXIT_FAILURE;
	}

	//打开文件
	CStdioFile StdFile;
	StdFile.Open(strPathName, CFile::modeRead | CFile::shareDenyNone);

	g_pCRcsManager->WriteItem(TRANS_BEGAN, NULL);
	//逐行读取字符串
	while (StdFile.ReadString(szLine))
	{
		CStringArray strResult;
		szLine.Replace('\t', ' ');
		int nPos = szLine.Find(strGap);
		CString strLeft = _T("");
		while (0 <= nPos)
		{
			strLeft = szLine.Left(nPos);
			if (!strLeft.IsEmpty())
				strResult.Add(strLeft);

			szLine = szLine.Right(szLine.GetLength() - nPos - 1);
			nPos = szLine.Find(strGap);
		}

		if (!szLine.IsEmpty()) {
			strResult.Add(szLine);
		}

		if (!strResult.IsEmpty() && strResult[0].Compare("#define") == 0)
		{
			l_cItemDef.Name = strResult[1];
			l_cItemDef.ID = strResult[2];
			g_pCRcsManager->WriteItem(TRANS_DATA, &l_cItemDef);
		}
	}

	g_pCRcsManager->WriteItem(TRANS_END, NULL);
	//关闭文件
	StdFile.Close();
	TickEnd();

	return EXIT_SUCCESS;
}

int UpdateStageInfo(CRcsFile * pCRcsFile)
{
	CString strPathName = pCRcsFile->m_csFileName;
	struct StageDef l_cStageDef;
	int ret = 0;

	CString szLine = "";
	CString strGap = _T(" ");
	TickStart();

	//检查文件是否存在
	DWORD dwRe = GetFileAttributes(strPathName);
	if (dwRe != (DWORD)-1)
	{
		//ShellExecute(NULL, NULL, strFilePath, NULL, NULL, SW_RESTORE); 
	}
	else
	{
		TRACE(strPathName + " 文件不存在！");
		return EXIT_FAILURE;
	}

	//打开文件
	CStdioFile StdFile;
	StdFile.Open(strPathName, CFile::modeRead | CFile::shareDenyNone);

	g_pCRcsManager->WriteStage(TRANS_BEGAN, NULL);
	//逐行读取字符串
	while (StdFile.ReadString(szLine))
	{
		CStringArray strResult;
		szLine.Replace('\t', ' ');
		int nPos = szLine.Find(strGap);
		CString strLeft = _T("");
		while (0 <= nPos)
		{
			strLeft = szLine.Left(nPos);
			if (!strLeft.IsEmpty())
				strResult.Add(strLeft);

			szLine = szLine.Right(szLine.GetLength() - nPos - 1);
			nPos = szLine.Find(strGap);
		}

		if (!szLine.IsEmpty()) {
			strResult.Add(szLine);
		}

		if (!strResult.IsEmpty() && strResult[0].Compare("#define") == 0)
		{
			l_cStageDef.Name = strResult[1];
			l_cStageDef.ID = strResult[2];
			g_pCRcsManager->WriteStage(TRANS_DATA, &l_cStageDef);
		}
	}

	g_pCRcsManager->WriteStage(TRANS_END, NULL);
	//关闭文件
	StdFile.Close();
	TickEnd();

	return EXIT_SUCCESS;
}

void _AccAttrDump(struct AccAttr cAccAtrr)
{
	TRACE("Account: %s\n \
		  Name: %s\n \
		  Gold: %d\n",
		  cAccAtrr.Account, cAccAtrr.Name, cAccAtrr.Gold);
}

int UpdatePlayersInfo(CRcsFile * pCRcsFile)
{
	CString strPathName = pCRcsFile->m_csFileName;
	struct AccAttr l_cAccAtrr = {0};
	char Head[32];
	int ret = 0;

	TickStart();

	//检查文件是否存在
	DWORD dwRe = GetFileAttributes(strPathName);
	if (dwRe != (DWORD)-1)
	{
		//ShellExecute(NULL, NULL, strFilePath, NULL, NULL, SW_RESTORE); 
	}
	else
	{
		TRACE(strPathName + " 文件不存在！");
		return EXIT_FAILURE;
	}

	CopyFile(strPathName, ".\\Temp\\players.dat", FALSE);

	CFile iFile(".\\Temp\\players.dat", CFile::modeRead | CFile::modeNoTruncate | CFile::shareDenyNone);
	CArchive iar(&iFile, CArchive::load);

	g_pCRcsManager->InsetPlayerInfo(TRANS_BEGAN, l_cAccAtrr);
	ret = sizeof(l_cAccAtrr);
	ret = iar.Read(Head, sizeof(Head));
	for (; ret > 0;)
	{
		ret = iar.Read(&l_cAccAtrr, sizeof(l_cAccAtrr));
		if (ret <= 0) break;

		g_pCRcsManager->InsetPlayerInfo(TRANS_DATA, l_cAccAtrr);
	}

	g_pCRcsManager->InsetPlayerInfo(TRANS_END, l_cAccAtrr);

	iar.Close();
	iFile.Close();
	TickEnd();
	return EXIT_SUCCESS;
}

int CRcsManager::WriteItem(int iToken, struct ItemDef* pItemDef)
{
	if (iToken == TRANS_BEGAN)
		m_CSqliteHelper.DeleteAllItems();
	
	if (pItemDef)
	{
		if (m_CSqliteHelper.WriteItem(iToken, CStr2STDStr(pItemDef->ID), CStr2STDStr(pItemDef->Name), Big2GB(pItemDef->Name)))
		{
			return EXIT_FAILURE;
		}
	}
	else
	{
		m_CSqliteHelper.WriteItem(iToken, "", "", "");
	}

	return EXIT_SUCCESS;
}

int CRcsManager::WriteStage(int iToken, struct StageDef* pStageDef)
{
	if (iToken == TRANS_BEGAN)
		m_CSqliteHelper.DeleteAllStages();

	if (pStageDef)
	{
		if (m_CSqliteHelper.WriteStage(iToken, CStr2STDStr(pStageDef->ID), CStr2STDStr(pStageDef->Name), Big2GB(pStageDef->Name)))
		{
			return EXIT_FAILURE;
		}
	}
	else
	{
		m_CSqliteHelper.WriteStage(iToken, "", "", "");
	}

	return EXIT_SUCCESS;
}

int CRcsManager::InsetPlayerInfo(int iToken, struct AccAttr cAccAtrr)
{
	if (m_pIndexListPlayerInfo == NULL)
		m_pIndexListPlayerInfo = new CIndexList<struct AccAttr, struct CKeys>();

	if (iToken == TRANS_BEGAN)
		m_pIndexListPlayerInfo->RemoveAll();
	else if (iToken == TRANS_DATA)
		m_pIndexListPlayerInfo->AddTail(cAccAtrr);
	else
	{

		struct CKeys caPlayerInfoKeys[] = {
			{ offsetof(struct AccAttr, Account), StringCompare },
			{ offsetof(struct AccAttr, Name), StringCompare },
			{ INDEX_KEYS_END },
		};
		TickStart();
		m_pIndexListPlayerInfo->CreateIndexStr(caPlayerInfoKeys);
		TickEnd();

		TickStart();
		struct AccAttr tmp = m_pIndexListPlayerInfo->Search(offsetof(struct AccAttr, Account), "1394600");
		TickEnd();
		CString csAcc = tmp.Account;

// 		TickStart();
// 		m_pIndexListPlayerInfo->CreateRBTIndexStr(caPlayerInfoKeys);
// 		TickEnd();
// 
// 		TickStart();
// 		struct AccAttr tmp = m_pIndexListPlayerInfo->RBTSearch(offsetof(struct AccAttr, Account), "1394600");
// 		TickEnd();
// 		CString csAcc = tmp.Account;
	}

	return EXIT_SUCCESS;
}

CRcsManager::CRcsManager()
{
	m_CSqliteHelper.Open();
}

CRcsManager::~CRcsManager()
{
	m_CSqliteHelper.Close();
	m_pRBTreePlayerInfo->destroy();
}

bool CRcsManager::RcsFileIsLatest(CRcsFile * pCRcsFile)
{
	//检查文件是否存在
	DWORD dwRe = GetFileAttributes(pCRcsFile->m_csFileName);
	if (dwRe == (DWORD)-1)
	{
		TRACE("文件 %s 不存在！\n", pCRcsFile->m_csFileName);
		return true;
	}
	// 获取文件的修改时间
	SYSTEMTIME FileTime;
	WIN32_FILE_ATTRIBUTE_DATA wFileAttDate;
	GetFileAttributesEx(pCRcsFile->m_csFileName, GetFileExInfoStandard, &wFileAttDate);
	FileTimeToSystemTime(&wFileAttDate.ftLastWriteTime, &FileTime);
	CString sFileTimeStamp;
	sFileTimeStamp.Format("%04d-%02d-%02d %02d:%02d:%02d", FileTime.wYear, FileTime.wMonth, FileTime.wDay, FileTime.wHour, FileTime.wMinute, FileTime.wSecond);
	//获取数据库中的文件修改时间	
	string buffer;
	m_CSqliteHelper.ReadProfileFile(CStr2STDStr(pCRcsFile->m_csFileName), buffer);
	CString sFileTimeStamp2 = STDStr2CStr(buffer);
	if (sFileTimeStamp <= sFileTimeStamp2)
		return true;
	pCRcsFile->m_csModTimeStamp = sFileTimeStamp;
	return false;
}

int CRcsManager::UpdateRcsFileTimeStamp(CRcsFile * pCRcsFile)
{
	if (m_CSqliteHelper.WriteProfileFile(CStr2STDStr(pCRcsFile->m_csFileName), CStr2STDStr(pCRcsFile->m_csModTimeStamp)))
		return EXIT_FAILURE;
	return EXIT_SUCCESS;
}

int CRcsManager::SyncSQLite3db()
{
	int i;
	int iFileType;
	CRcsFile cRcsFile;
	for (i = 0; i < ARRAYSIZE(g_cRcsFilesDefine); i++)
	{
		iFileType = g_cRcsFilesDefine[i].m_iFileType;
		switch (iFileType)
		{
		case RCS_TPYE_DEF:
			cRcsFile.m_csFileName.Format("%s%s", CONFIG_FILE_PATH, g_cRcsFilesDefine[i].m_csFileName);
			break;
		case RCS_TYPE_DATA:
			cRcsFile.m_csFileName.Format("%sDataBase\\saves\\%s", g_pSettings->GetServerRootPath(), g_cRcsFilesDefine[i].m_csFileName);
			break;
		case RCS_TYPE_INI:
			cRcsFile.m_csFileName.Format("%slogin\\%s", g_pSettings->GetServerRootPath(), g_cRcsFilesDefine[i].m_csFileName);
			break;
		default:
			TRACE("不支持的选项！\n"); // 绝对不允许跑到这里来
			break;
		}

		if (iFileType == RCS_TYPE_DATA || !RcsFileIsLatest(&cRcsFile))
		{
			if (!g_cRcsFilesDefine[i].update)
				continue;	// 没有更新接口，不更新数据库
			if (g_cRcsFilesDefine[i].update(&cRcsFile))
				continue;	// 更新数据库失败，不更新文件时间戳
			UpdateRcsFileTimeStamp(&cRcsFile);
		}			
	}
	return EXIT_SUCCESS;
}
