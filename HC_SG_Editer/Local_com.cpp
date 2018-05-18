#include "stdafx.h"
#include "Local_com.h"

Common::Common(void)
{
}

Common::~Common(void)
{
}

BOOL Common::SanGuoServerIsRuning = FALSE;

HWND Common::DlgCwarOrg;
HWND Common::DlgCwarPlayer;
HWND Common::DlgAttr;
HWND Common::DlgCB;
HWND Common::DlgServer;
HWND Common::DlgXubao;
HWND Common::DlgLog;
HWND Common::DlgDrop;
HWND Common::DlgArmy;
HWND Common::DlgPlayer;

int Common::LogLevel = 1;

BOOL Common::IsEnConn = TRUE;
BOOL Common::IsDbConct = FALSE;

CString Common::ServerPath;

CString Common::SQLServer;
CString Common::SQLAccount;
CString Common::SQLPassWord;

CString Common::mEditAcc;
CString Common::mEditDB;
CString Common::mEditLogin;
CString Common::mEditVT;
CString Common::mEditMap1;
CString Common::mEditMap2;
CString Common::mEditMap3;
CString Common::mEditMap4;
CString Common::mEditBackup1;
CString Common::mEditBackup2;
CString Common::mEditGate;

CString Common::m_CbMinKills;
CString Common::m_CbChkMinKills;
CString Common::m_CbMinHonors;
CString Common::m_CbChkMinHonors;

CString Common::m_CWarMinKills;
CString Common::m_CWarChkMinKills;
CString Common::m_CWarMinHonors;
CString Common::m_CWarChkMinHonors;

CString Common::m_CWarAwardsChkTime;

CStringArray Common::VipAwardsPoints;

_ConnectionPtr Common::m_pConnection;
_RecordsetPtr Common::m_pRecordset;
_ConnectionPtr Common::m_pConnXb;
_RecordsetPtr Common::m_pRecordsetXb;

CList <GameAcc, GameAcc&> Common::LGameAcc;
CList <AccAttr, AccAttr&> Common::LAccAttr;
CList <AccSkills, AccSkills&> Common::LAccSkills;
CList <ItemDef, ItemDef&> Common::LItemDef;
CList <Players, Players&> Common::LPlayers;
CList <BagsDrop, BagsDrop&> Common::LBagsDrop;
CList <DropsRange, DropsRange&> Common::LDropsRange;
CList <StageDef, StageDef&> Common::LStageDef;
CList <ArmyNameDef, ArmyNameDef&> Common::LArmyNameDef;
CList <ArmyDef, ArmyDef&> Common::LArmyDef;
CList <OrganizeAttr, OrganizeAttr&> Common::LOrganizeAttr;

CString Common::strServerMapList;

ServerConfigTime Common::TimeForCB;
ServerConfigTime Common::TimeForCwar;

CString  Common::GB2Big(char*  sGb)
{  
	char*  pszGbt  =  NULL;    
	char*  pszGbs  =  NULL;    
	wchar_t*  wszUnicode  =  NULL;    
	char*  pszBig5  =  NULL;    
	CString  sBig5;    
	int  iLen=0;    

	pszGbs  =  sGb;
	iLen  =  MultiByteToWideChar(936,  0,  pszGbs,  -1,  NULL,0);
	pszGbt  =  new  char[iLen*2+1];
	LCMapString(0x0804,LCMAP_TRADITIONAL_CHINESE,  pszGbs,  -1,  pszGbt,  iLen*2);
	wszUnicode  =  new  wchar_t[iLen+1];
	MultiByteToWideChar  (936,  0,  pszGbt,  -1,  wszUnicode,iLen);
	iLen  =  WideCharToMultiByte  (950,  0,  (PWSTR)wszUnicode,  -1,  NULL,  0,  NULL,  NULL);
	pszBig5  =  new  char[iLen+1];
	WideCharToMultiByte  (950,  0,  (PWSTR)wszUnicode,  -1,  pszBig5,  iLen,  NULL,  NULL);
	sBig5  =  pszBig5;
	delete  []  wszUnicode;  
	wszUnicode  =  NULL;  
	delete  []  pszGbt;  
	pszGbt  =  NULL;  
	delete  []  pszBig5;  
	pszBig5  =  NULL;  

	return  sBig5;  
}

CString Common::Big2GB(char*  sBig5) 
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
	WideCharToMultiByte (936, 0, wbuf, -1, buf, sizeof(buf), NULL, NULL);

	//转换Gb码繁体到Gb码简体，使用API函数LCMapString
	LCMapString(0x0804, LCMAP_SIMPLIFIED_CHINESE, buf, -1, GbBuf, 2048);

	sRetBig5  =  GbBuf;
	return  sRetBig5;  
}

CString Common::convert(int n)
{ 
	static CString str = ""; 
	if(n<10) 
	{ 
		str=(char)(n%10+'0'); 
		return str; 
	} 
	else 
	{ 
		str=convert(n/10)+(char)(n%10+'0'); 
		return str; 
	} 
}

void Common::CStringGap(CString strSrc, CStringArray *strDest, CString Key, CString strGap, int Skip)
{
	int nPos = strSrc.Find(strGap);
	CString strLeft = _T("");
	while(0 <= nPos)
	{
		strLeft = strSrc.Left(nPos);
		if (Skip-- <= 0)
			strDest->Add(strLeft);

		int  len = strSrc.GetLength();
		strSrc = strSrc.Right(strSrc.GetLength() - nPos - 1);
		nPos = strSrc.Find(strGap);
	}

	if (!strSrc.IsEmpty() && Skip-- <= 0) {
		strDest->Add(strSrc);
	}
}

BOOL Common::IsDigital(LPCTSTR lpszSrc)  
{  
	CString Src = lpszSrc;  
	return (Src ==  Src.SpanIncluding( _T("0123456789" ) ));  
}

void Common::ReadConfig()
{
	CString StrValue;
	CString des="";
	::GetCurrentDirectory(1024,des.GetBuffer(1024));
	des.ReleaseBuffer();
	des += CONFIG_FILE_PATH;
	des += CONFIG_FILE;

	GetPrivateProfileString("SQLSERVER","SERVERIP","",StrValue.GetBuffer(128),128,des);
	SQLServer = StrValue;
	StrValue.ReleaseBuffer();

	GetPrivateProfileString("SQLSERVER","ACCOUNT","",StrValue.GetBuffer(128),128,des);
	SQLAccount = StrValue;
	StrValue.ReleaseBuffer();

	GetPrivateProfileString("SQLSERVER","PASSWORD","",StrValue.GetBuffer(128),128,des);
	SQLPassWord = StrValue;
	StrValue.ReleaseBuffer();

	GetPrivateProfileString("SETTING","SERVER_PATH","",StrValue.GetBuffer(128),128,des);
	ServerPath = StrValue;
	StrValue.ReleaseBuffer();


	GetPrivateProfileString("SYSTEM","Account","",StrValue.GetBuffer(128),128,des);
	mEditAcc = StrValue;
	StrValue.ReleaseBuffer();

	GetPrivateProfileString("SYSTEM","DB","",StrValue.GetBuffer(128),128,des);
	mEditDB = StrValue;
	StrValue.ReleaseBuffer();

	GetPrivateProfileString("SYSTEM","Login","",StrValue.GetBuffer(128),128,des);
	mEditLogin = StrValue;
	StrValue.ReleaseBuffer();

	GetPrivateProfileString("SYSTEM","VT","",StrValue.GetBuffer(128),128,des);
	mEditVT = StrValue;
	StrValue.ReleaseBuffer();

	GetPrivateProfileString("SYSTEM","MAP-1","",StrValue.GetBuffer(128),128,des);
	mEditMap1 = StrValue;
	StrValue.ReleaseBuffer();

	GetPrivateProfileString("SYSTEM","MAP-2","",StrValue.GetBuffer(128),128,des);
	mEditMap2 = StrValue;
	StrValue.ReleaseBuffer();

	GetPrivateProfileString("SYSTEM","MAP-3","",StrValue.GetBuffer(128),128,des);
	mEditMap3 = StrValue;
	StrValue.ReleaseBuffer();

	GetPrivateProfileString("SYSTEM","MAP-4","",StrValue.GetBuffer(128),128,des);
	mEditMap4 = StrValue;
	StrValue.ReleaseBuffer();

	GetPrivateProfileString("SYSTEM","Backup-1","",StrValue.GetBuffer(128),128,des);
	mEditBackup1 = StrValue;
	StrValue.ReleaseBuffer();

	GetPrivateProfileString("SYSTEM","Backup-2","",StrValue.GetBuffer(128),128,des);
	mEditBackup2 = StrValue;
	StrValue.ReleaseBuffer();

	GetPrivateProfileString("SYSTEM","Gate","",StrValue.GetBuffer(128),128,des);
	mEditGate = StrValue;
	StrValue.ReleaseBuffer();

	GetPrivateProfileString("HISTORY_CB","CbMinKills","",StrValue.GetBuffer(128),128,des);
	m_CbMinKills = StrValue;
	StrValue.ReleaseBuffer();

	GetPrivateProfileString("HISTORY_CB","CbChkMinKills","",StrValue.GetBuffer(128),128,des);
	m_CbChkMinKills = StrValue;
	StrValue.ReleaseBuffer();

	GetPrivateProfileString("HISTORY_CB","CbMinHonors","",StrValue.GetBuffer(128),128,des);
	m_CbMinHonors = StrValue;
	StrValue.ReleaseBuffer();

	GetPrivateProfileString("HISTORY_CB","CbChkMinHonors","",StrValue.GetBuffer(128),128,des);
	m_CbChkMinHonors = StrValue;
	StrValue.ReleaseBuffer();

	GetPrivateProfileString("HISTORY_CWAR","CWarMinKills","",StrValue.GetBuffer(128),128,des);
	m_CWarMinKills = StrValue;
	StrValue.ReleaseBuffer();

	GetPrivateProfileString("HISTORY_CWAR","CWarChkMinKills","",StrValue.GetBuffer(128),128,des);
	m_CWarChkMinKills = StrValue;
	StrValue.ReleaseBuffer();

	GetPrivateProfileString("HISTORY_CWAR","CWarMinHonors","",StrValue.GetBuffer(128),128,des);
	m_CWarMinHonors = StrValue;
	StrValue.ReleaseBuffer();

	GetPrivateProfileString("HISTORY_CWAR","CWarChkMinHonors","",StrValue.GetBuffer(128),128,des);
	m_CWarChkMinHonors = StrValue;
	StrValue.ReleaseBuffer();

	GetPrivateProfileString("HISTORY_CWAR","AWARDECHKTIME","5",StrValue.GetBuffer(128),128,des);
	m_CWarAwardsChkTime = StrValue;
	StrValue.ReleaseBuffer();

	GetPrivateProfileString("LOGSERVER","LOGLEVEL","3",StrValue.GetBuffer(128),128,des);
	LogLevel = _ttoi(StrValue);
	StrValue.ReleaseBuffer();

	GetPrivateProfileString("VIPAWARDE","VIP1","100",StrValue.GetBuffer(128),128,des);
	VipAwardsPoints.Add(StrValue);
	StrValue.ReleaseBuffer();

	GetPrivateProfileString("VIPAWARDE","VIP2","200",StrValue.GetBuffer(128),128,des);
	VipAwardsPoints.Add(StrValue);
	StrValue.ReleaseBuffer();

	GetPrivateProfileString("VIPAWARDE","VIP3","300",StrValue.GetBuffer(128),128,des);
	VipAwardsPoints.Add(StrValue);
	StrValue.ReleaseBuffer();

	GetPrivateProfileString("VIPAWARDE","VIP4","400",StrValue.GetBuffer(128),128,des);
	VipAwardsPoints.Add(StrValue);
	StrValue.ReleaseBuffer();

	GetPrivateProfileString("VIPAWARDE","VIP5","500",StrValue.GetBuffer(128),128,des);
	VipAwardsPoints.Add(StrValue);
	StrValue.ReleaseBuffer();
}

void Common::SaveConfig()
{
	CString StrValue;
	CString des="";
	::GetCurrentDirectory(1024,des.GetBuffer(1024));
	des.ReleaseBuffer();
	des += CONFIG_FILE_PATH;
	des += CONFIG_FILE;

	WritePrivateProfileString("SQLSERVER","SERVERIP",SQLServer,des);
	WritePrivateProfileString("SQLSERVER","ACCOUNT",SQLAccount,des);
	WritePrivateProfileString("SQLSERVER","PASSWORD",SQLPassWord,des);
	WritePrivateProfileString("SETTING","SERVER_PATH",ServerPath,des);

	WritePrivateProfileString("SYSTEM","Account",mEditAcc,des);
	WritePrivateProfileString("SYSTEM","DB",mEditDB,des);	
	WritePrivateProfileString("SYSTEM","Login",mEditLogin,des);
	WritePrivateProfileString("SYSTEM","VT",mEditVT,des);
	WritePrivateProfileString("SYSTEM","MAP-1",mEditMap1,des);
	WritePrivateProfileString("SYSTEM","MAP-2",mEditMap2,des);
	WritePrivateProfileString("SYSTEM","MAP-3",mEditMap3,des);
	WritePrivateProfileString("SYSTEM","MAP-4",mEditMap4,des);
	WritePrivateProfileString("SYSTEM","Backup-1",mEditBackup1,des);
	WritePrivateProfileString("SYSTEM","Backup-2",mEditBackup2,des);	
	WritePrivateProfileString("SYSTEM","Gate",mEditGate,des);
	WritePrivateProfileString("HISTORY_CB","CbMinKills",m_CbMinKills,des);
	WritePrivateProfileString("HISTORY_CB","CbChkMinKills",m_CbChkMinKills,des);	
	WritePrivateProfileString("HISTORY_CB","CbMinHonors",m_CbMinHonors,des);
	WritePrivateProfileString("HISTORY_CB","CbChkMinHonors",m_CbChkMinHonors,des);
	WritePrivateProfileString("HISTORY_CWAR","CWarMinKills",m_CWarMinKills,des);
	WritePrivateProfileString("HISTORY_CWAR","CWarChkMinKills",m_CWarChkMinKills,des);	
	WritePrivateProfileString("HISTORY_CWAR","CWarMinHonors",m_CWarMinHonors,des);
	WritePrivateProfileString("HISTORY_CWAR","CWarChkMinHonors",m_CWarChkMinHonors,des);
	WritePrivateProfileString("HISTORY_CWAR","AWARDECHKTIME",m_CWarAwardsChkTime,des);
	WritePrivateProfileString("LOGSERVER","LOGLEVEL",convert(LogLevel),des);
	WritePrivateProfileString("VIPAWARDE","VIP1",VipAwardsPoints[0],des);
	WritePrivateProfileString("VIPAWARDE","VIP2",VipAwardsPoints[1],des);
	WritePrivateProfileString("VIPAWARDE","VIP3",VipAwardsPoints[2],des);
	WritePrivateProfileString("VIPAWARDE","VIP4",VipAwardsPoints[3],des);
	WritePrivateProfileString("VIPAWARDE","VIP5",VipAwardsPoints[4],des);
}

BOOL Common::SaveAwardsConfig()
{
	CString StrValue;
	CString strFilePath="";
	::GetCurrentDirectory(1024,strFilePath.GetBuffer(1024));
	strFilePath.ReleaseBuffer();
	strFilePath += "\\AwardsConfig.xls";

	DWORD dwRe = GetFileAttributes(strFilePath);
	if ( dwRe != (DWORD)-1 )
	{
		DeleteFile(strFilePath);
	}

	//调用各个Tab的配置保存方法
// 	::SendMessage(Common::DlgCwarOrg, WM_SAVECWARORGAWARDS, 0, (LPARAM)(&strFilePath));
// 	::SendMessage(Common::DlgCwarPlayer, WM_SAVECWARPLAYERAWARDS, 0, (LPARAM)(&strFilePath));
// 	::SendMessage(Common::DlgCB, WM_SAVECBAWARDS, 0, (LPARAM)(&strFilePath));
// 	::SendMessage(Common::DlgXubao, WM_SAVEXUBAOCONFIG, 0, (LPARAM)(&strFilePath));

	return TRUE;
}

void Common::SystemInit()
{
	//ConnToSQLServer();
	GetItemDef();
	GetPlayers();
	GetDrops();
	GetBagsDrop();
	GetStageDef();
	GetArmyNameDef();
	GetArmyDef();
	GetServerMapList();
	//GetUpdateCLists();
	//GetServerConfig();
}

void Common::GetUpdateCLists()
{
	GetGameAccFormDB();
	GetAccAttr();
	GetOrganizeAttr();
}

void Common::ConnToSQLServer()
{
	if(!IsEnConn)
	{
		Common::Log(Info, "管理员已经断开数据库连接！");
		return;
	}
	if(!IsDbConct)
	{
		HRESULT hr;
		try
		{
			if(SQLServer.IsEmpty() || SQLAccount.IsEmpty() || SQLPassWord.IsEmpty())
				return;
			hr = m_pConnection.CreateInstance("ADODB.Connection");
			if (SUCCEEDED(hr))
			{ 
				//connect database
				CString StrConn;
				CString temp;
				StrConn = "Provider=SQLOLEDB.1;Server=" + SQLServer + ";DATABASE=account;UID=" 
					+ SQLAccount + ";PWD=" + SQLPassWord + ";";
				m_pConnection->Open((_bstr_t)StrConn,"","",adModeUnknown);
				Log(Info, "Account 数据库连接成功");
				IsDbConct = TRUE;
			}

			hr = m_pConnXb.CreateInstance("ADODB.Connection");
			if (SUCCEEDED(hr))
			{ 
				//connect database
				CString StrConn;
				StrConn = "Provider=SQLOLEDB.1;Server=" + SQLServer + ";DATABASE=sanvt;UID="
					+ SQLAccount + ";PWD=" + SQLPassWord + ";";
				m_pConnXb->Open((_bstr_t)StrConn,"","",adModeUnknown);
				Log(Info, "sanvt数据库连接成功");
			}
		}
		catch (_com_error e)
		{
			CString errormessage;
			errormessage.Format("连接数据库失败！\r\n错误信息:%s",e.ErrorMessage());
			Log(Error, errormessage);
			return ;
		}
	}
	else
	{
		try
		{
			if(Common::m_pConnection != NULL)
			{
				Common::m_pConnection->Close();
				Common::m_pConnection = NULL;
			}
			if(Common::m_pConnXb != NULL)
			{
				Common::m_pConnXb->Close();
				Common::m_pConnXb = NULL;
			}
			IsDbConct = FALSE;
		}
		catch (_com_error e)
		{
			CString errormessage;
			errormessage.Format("断开数据库失败！\r\n错误信息:%s",e.ErrorMessage());
			Log(Error, errormessage);
			return ;
		}
	}
}

BOOL Common::SendPoint(int nTotalPoints, CString strAccount)
{
	CString strInsert;
	CString SQLInSertCmd;

	strInsert.Format("UPDATE game_acc set point='%d' from game_acc where account='%s'", nTotalPoints, strAccount);

	SQLInSertCmd = strInsert;

	//将记录插入数据库中
	TRACE(SQLInSertCmd);
	_variant_t sql;
	sql = SQLInSertCmd;
	try
	{
		HRESULT hr = Common::m_pConnection->Execute((_bstr_t)sql, NULL, adCmdText);
		if(!SUCCEEDED(hr))
		{
			return FALSE;
		}
	}
	catch(_com_error &e) 
	{ 
		Common::Log(Info, (LPCSTR)(e.Description()));
		return FALSE;
	}
	Common::Log(Info, sql);

	return TRUE;
}

BOOL Common::SendXubao(CString strAccount, CStringArray *ItemList)
{
	CString strInsert;
	CString SQLInSertCmd;
	CStringArray TmpItemList;

	int count = ItemList->GetCount();
	int i;
	for(i=0;i<count;i++)
		TmpItemList.Add(ItemList->GetAt(i));

	for(;i<10;i++)
		TmpItemList.Add("0");

	SYSTEMTIME st;
	CString strDateTime;
	GetLocalTime(&st);
	strDateTime.Format("%4d-%2d-%2d %2d:%2d:%2d.%3d",st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond, st.wMilliseconds);

	strInsert.Format("INSERT INTO vitem(Disable,Login_time,Get_time,SName,CharName,Type,"
		"Account,Card,DataID1,Number1,"
		"DataID2,Number2,DataID3,Number3,DataID4,Number4,DataID5,Number5)"
		" values('0','2015-04-21 18:16:29.000','2015-04-21 18:16:29.000','0','0','0',"
		"'%s','%s',"
		"'%s','%s','%s','%s','%s','%s',"
		"'%s','%s','%s','%s')",
		strAccount, strDateTime, 
		TmpItemList[0], TmpItemList[1], TmpItemList[2], TmpItemList[3], TmpItemList[4], TmpItemList[5],
		TmpItemList[6], TmpItemList[7], TmpItemList[8], TmpItemList[9]);

	SQLInSertCmd = strInsert;

	//将记录插入数据库中
	TRACE(SQLInSertCmd);
	_variant_t sql;
	sql = SQLInSertCmd;
	try
	{
		HRESULT hr = m_pConnXb->Execute((_bstr_t)sql, NULL, adCmdText);
		if(!SUCCEEDED(hr))
		{
			return FALSE;
		}
	}
	catch(_com_error &e) 
	{ 
		Common::Log(Info, (LPCSTR)(e.Description())); 
		return FALSE;
	}
	Common::Log(Info, sql);

	return TRUE;
}

void Common::GetGameAccFormDB()
{
	CString strPathName;
	struct GameAcc TmpGameAcc;
	int ret = 0;
	_variant_t strValue;

	if(NULL ==  m_pConnection)
	{
		ConnToSQLServer();
	}
	try
	{
		LGameAcc.RemoveAll();
		_variant_t RecordsAffected; 

		m_pRecordset = m_pConnection->Execute("SELECT account,password,password2,duedate,enable,lock_duedate,"
			"logout_time,ip,create_time,privilege,status,sec_pwd,first_ip,point,trade_psw,IsAdult,OnlineTime,"
			"OfflineTime,LastLoginTime,LastLogoutTime from game_acc",
			&RecordsAffected,adCmdText); 

		while(!m_pRecordset->ADOEOF)
		{
			strValue = Common::m_pRecordset->GetCollect("account");
			TmpGameAcc.account = (strValue.vt != VT_NULL) ? strValue : "";
			strValue = Common::m_pRecordset->GetCollect("password");
			TmpGameAcc.password = (strValue.vt != VT_NULL) ? strValue : "";
			strValue = Common::m_pRecordset->GetCollect("password2");
			TmpGameAcc.password2 = (strValue.vt != VT_NULL) ? strValue : "";
			strValue = Common::m_pRecordset->GetCollect("duedate");
			TmpGameAcc.duedate = (strValue.vt != VT_NULL) ? strValue : "";
			strValue = Common::m_pRecordset->GetCollect("enable");
			TmpGameAcc.enable = (strValue.vt != VT_NULL) ? strValue : "";
			strValue = Common::m_pRecordset->GetCollect("lock_duedate");
			TmpGameAcc.lock_duedate = (strValue.vt != VT_NULL) ? strValue : "";
			strValue = Common::m_pRecordset->GetCollect("logout_time");
			TmpGameAcc.logout_time = (strValue.vt != VT_NULL) ? strValue : "";
			strValue = Common::m_pRecordset->GetCollect("ip");
			TmpGameAcc.ip = (strValue.vt != VT_NULL) ? strValue : "";
			strValue = Common::m_pRecordset->GetCollect("create_time");
			TmpGameAcc.create_time = (strValue.vt != VT_NULL) ? strValue : "";
			strValue = Common::m_pRecordset->GetCollect("privilege");
			TmpGameAcc.privilege = (strValue.vt != VT_NULL) ? strValue : "";
			strValue = Common::m_pRecordset->GetCollect("status");
			TmpGameAcc.status = (strValue.vt != VT_NULL) ? strValue : "";
			strValue = Common::m_pRecordset->GetCollect("sec_pwd");
			TmpGameAcc.sec_pwd = (strValue.vt != VT_NULL) ? strValue : "";
			strValue = Common::m_pRecordset->GetCollect("first_ip");
			TmpGameAcc.first_ip = (strValue.vt != VT_NULL) ? strValue : "";
			strValue = Common::m_pRecordset->GetCollect("point");
			TmpGameAcc.point = (strValue.vt != VT_NULL) ? strValue : "0";
			strValue = Common::m_pRecordset->GetCollect("trade_psw");
			TmpGameAcc.trade_psw = (strValue.vt != VT_NULL) ? strValue : "";
			strValue = Common::m_pRecordset->GetCollect("IsAdult");
			TmpGameAcc.IsAdult = (strValue.vt != VT_NULL) ? strValue : "";
			strValue = Common::m_pRecordset->GetCollect("OnlineTime");
			TmpGameAcc.OnlineTime = (strValue.vt != VT_NULL) ? strValue : "";
			strValue = Common::m_pRecordset->GetCollect("OfflineTime");
			TmpGameAcc.OfflineTime = (strValue.vt != VT_NULL) ? strValue : "";
			strValue = Common::m_pRecordset->GetCollect("LastLoginTime");
			TmpGameAcc.LastLoginTime = (strValue.vt != VT_NULL) ? strValue : "";
			strValue = Common::m_pRecordset->GetCollect("LastLogoutTime");
			TmpGameAcc.LastLogoutTime = (strValue.vt != VT_NULL) ? strValue : "";

			LGameAcc.AddTail(TmpGameAcc);
			m_pRecordset->MoveNext();
		}
		m_pRecordset->Close();
	}
	catch (_com_error e)
	{
		CString errormessage;
		errormessage.Format("查询失败！\r\n错误信息:%s",e.ErrorMessage());
		Log(Error ,errormessage);
		return ;

	}
}

void Common::GetAccAttr()
{
	CString strPathName;
	struct AccAttr TmpAccAtrr;
	char Head[32];
	int ret = 0;

	LAccAttr.RemoveAll();

	// 以下代码用于保存，暂时不实现
	// 	CString strTemp;
	// 	CFile mFile;
	// 	mFile.Open("d:\dd\try.TRY",CFile::modeCreate|CFile::modeNoTruncate|CFile::modeWrite);
	// 	CArchive oar(&mFile,CArchive::store);
	// 	oar << oar.Close();
	// 	mFile.Close();

	strPathName = Common::ServerPath + "DataBase\\saves\\players.dat";
	//检查文件是否存在
	DWORD dwRe = GetFileAttributes(strPathName);
	if ( dwRe != (DWORD)-1 )
	{
		//ShellExecute(NULL, NULL, strFilePath, NULL, NULL, SW_RESTORE); 
	}
	else 
	{
		CString errormessage;
		errormessage.Format(strPathName + " 文件不存在！");
		Log(Error, errormessage);
		return;
	}

	CFile iFile(strPathName, CFile::modeRead | CFile::modeNoTruncate | CFile::shareDenyNone);  
	CArchive iar(&iFile, CArchive::load); 

	ret = sizeof(TmpAccAtrr);
	ret = iar.Read(Head,sizeof(Head));
	for(;ret > 0;)
	{
		ret = iar.Read(&TmpAccAtrr,sizeof(TmpAccAtrr));
		if(ret <= 0) break;
		LAccAttr.AddTail(TmpAccAtrr);
	}

	iar.Close();
	iFile.Close();
}

void Common::GetAccSkills()
{
	CString strPathName;
	struct AccSkills TmpAccSkills;
	char Head[32];
	int ret = 0;

	LAccSkills.RemoveAll();

	strPathName = Common::ServerPath + "DataBase\\saves\\skill.dat";
	//检查文件是否存在
	DWORD dwRe = GetFileAttributes(strPathName);
	if (dwRe != (DWORD)-1)
	{
		//ShellExecute(NULL, NULL, strFilePath, NULL, NULL, SW_RESTORE); 
	}
	else
	{
		CString errormessage;
		errormessage.Format(strPathName + " 文件不存在！");
		Log(Error, errormessage);
		return;
	}

	CFile iFile(strPathName, CFile::modeRead | CFile::modeNoTruncate | CFile::shareDenyNone);
	CArchive iar(&iFile, CArchive::load);

	ret = sizeof(TmpAccSkills);
	ret = iar.Read(Head, sizeof(Head));
	for (; ret > 0;)
	{
		ret = iar.Read(&TmpAccSkills, sizeof(TmpAccSkills));
		if (ret <= 0) break;
		LAccSkills.AddTail(TmpAccSkills);
	}

	iar.Close();
	iFile.Close();
}

void Common::GetOrganizeAttr()
{
	CString strPathName;
	struct OrganizeAttr TmpOrganizeAttr;
	char Head[32];
	int ret = 0;

	LOrganizeAttr.RemoveAll();

	strPathName = Common::ServerPath + "DataBase\\saves\\organize.dat";
	//检查文件是否存在
	DWORD dwRe = GetFileAttributes(strPathName);
	if ( dwRe != (DWORD)-1 )
	{
		//ShellExecute(NULL, NULL, strFilePath, NULL, NULL, SW_RESTORE); 
	}
	else 
	{
		CString errormessage;
		errormessage.Format(strPathName + " 文件不存在！");
		Log(Error, errormessage);
		return;
	}

	CFile iFile(strPathName, CFile::modeRead | CFile::modeNoTruncate | CFile::shareDenyNone);  
	CArchive iar(&iFile, CArchive::load); 

	ret = sizeof(TmpOrganizeAttr);
	ret = iar.Read(Head,sizeof(Head));
	for(;ret > 0;)
	{
		ret = iar.Read(&TmpOrganizeAttr,sizeof(TmpOrganizeAttr));
		if(ret <= 0) break;
		LOrganizeAttr.AddHead(TmpOrganizeAttr);
	}

	iar.Close();
	iFile.Close();
}

void Common::GetItemDef()
{
	CString strPathName;
	struct ItemDef TmpItemDef;
	int ret = 0;

	strPathName.Format("%s%s", CONFIG_FILE_PATH, ITEM_H);
	CString szLine = "";
	CString strGap = _T(" ");
	CStringArray strResult;

	//检查文件是否存在
	DWORD dwRe = GetFileAttributes(strPathName);
	if ( dwRe != (DWORD)-1 )
	{
		//ShellExecute(NULL, NULL, strFilePath, NULL, NULL, SW_RESTORE); 
	}
	else 
	{
		CString errormessage;
		errormessage.Format(strPathName + " 文件不存在！");
		Log(Error, errormessage);
		return;
	}

	LItemDef.RemoveAll();

	//打开文件
	CStdioFile StdFile;
	StdFile.Open(strPathName,CFile::modeRead | CFile::shareDenyNone);

	//逐行读取字符串
	while( StdFile.ReadString( szLine ) )
	{
		strResult.RemoveAll();
		szLine.Replace('\t', ' ');
		int nPos = szLine.Find(strGap);
		CString strLeft = _T("");
		while(0 <= nPos)
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

		if(!strResult.IsEmpty() && strResult[0].Compare("#define") ==  0)
		{
			TmpItemDef.Name = strResult[1];
			TmpItemDef.ID = strResult[2];
			LItemDef.AddTail(TmpItemDef);
		}
	}

	//关闭文件
	StdFile.Close();
}

void Common::GetStageDef()
{
	CString strPathName;
	struct StageDef TmpStageDef;
	int ret = 0;

	strPathName.Format("%s%s", CONFIG_FILE_PATH, STAGE_H);
	CString szLine = "";
	CString strGap = _T(" ");
	CStringArray strResult;

	//检查文件是否存在
	DWORD dwRe = GetFileAttributes(strPathName);
	if ( dwRe != (DWORD)-1 )
	{
		//ShellExecute(NULL, NULL, strFilePath, NULL, NULL, SW_RESTORE); 
	}
	else 
	{
		CString errormessage;
		errormessage.Format(strPathName + " 文件不存在！");
		Log(Error, errormessage);
		return;
	}

	LStageDef.RemoveAll();

	//打开文件
	CStdioFile StdFile;
	StdFile.Open(strPathName,CFile::modeRead | CFile::shareDenyNone);

	//逐行读取字符串
	while( StdFile.ReadString( szLine ) )
	{
		strResult.RemoveAll();
		szLine.Replace('\t', ' ');
		int nPos = szLine.Find(strGap);
		CString strLeft = _T("");
		while(0 <= nPos)
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

		if(!strResult.IsEmpty() && strResult[0].Compare("#define") ==  0)
		{
			TmpStageDef.Name = strResult[1];
			TmpStageDef.ID = strResult[2];
			LStageDef.AddTail(TmpStageDef);
		}
	}

	//关闭文件
	StdFile.Close();
}

void Common::GetArmyNameDef()
{
	int index;
	CString strGap = ",";
	CString strPathName;
	struct ArmyNameDef TmpArmyNameDef;
	int ret = 0;

	strPathName.Format("%s%s", CONFIG_FILE_PATH, ARMY_NAME_TXT);
	CString szLine = "";

	//检查文件是否存在
	DWORD dwRe = GetFileAttributes(strPathName);
	if ( dwRe != (DWORD)-1 )
	{
		//ShellExecute(NULL, NULL, strFilePath, NULL, NULL, SW_RESTORE); 
	}
	else 
	{
		CString errormessage;
		errormessage.Format(strPathName + " 文件不存在！");
		Log(Error, errormessage);
		return;
	}

	LArmyNameDef.RemoveAll();

	//打开文件
	CStdioFile StdFile;
	StdFile.Open(strPathName,CFile::modeRead | CFile::shareDenyNone);

	//逐行读取字符串
	while( StdFile.ReadString( szLine ) )
	{
		szLine.Replace('\t', ' ');
		szLine.Replace(_T(" "), _T(""));
		index = szLine.Find(';');
		if(index >= 0)
			szLine.Delete(szLine.Find(';'), szLine.GetLength() - szLine.Find(';'));
		index = szLine.Find("//");
		if(index >= 0)
			szLine.Delete(szLine.Find(';'), szLine.GetLength() - szLine.Find("//"));

		if(szLine.Find("item=") == 0)  // get item
		{
			CStringArray strDest;
			szLine.Replace(_T("item="), _T(""));

			CString temp11 = szLine;
			int nPos = temp11.Find(strGap);
			CString strLeft = _T("");
			temp11 = temp11.Right(temp11.GetLength() - nPos - 1);
			TmpArmyNameDef.Name = temp11;

			nPos = szLine.Find(strGap);
			strLeft = _T("");
			while(0 <= nPos)
			{
				strLeft = szLine.Left(nPos);
				strDest.Add(strLeft);
				int  len = szLine.GetLength();
				szLine = szLine.Right(szLine.GetLength() - nPos - 1);
				nPos = szLine.Find(strGap);
			}

			if (!szLine.IsEmpty()) {
				strDest.Add(szLine);
			}
			TmpArmyNameDef.ID = strDest[0];

			if(LArmyNameDef.GetCount() == 0)
				LArmyNameDef.AddTail(TmpArmyNameDef);
			else
			{
				int i;
				POSITION pos = LArmyNameDef.GetHeadPosition();
				for (i=0;i < LArmyNameDef.GetCount();i++)  // 排序插入
				{
					POSITION curPos = pos;
					ArmyNameDef temp = LArmyNameDef.GetNext(pos);
					if(_ttoi(TmpArmyNameDef.ID) < _ttoi(temp.ID))
					{
						LArmyNameDef.InsertBefore(curPos, TmpArmyNameDef);
						break;
					}
				}
				if(i == LArmyNameDef.GetCount())
					LArmyNameDef.AddTail(TmpArmyNameDef);
			}
		}
	}

	//关闭文件
	StdFile.Close();
}

void Common::GetArmyDef()
{
	int index;
	int GetValueStep = 0;
	CString strGap = ",";
	CString strPathName;
	struct ArmyDef TmpArmyDef;
	int ret = 0;

	strPathName.Format("%s%s", CONFIG_FILE_PATH, ARMY_TXT);
	CString szLine = "";

	//检查文件是否存在
	DWORD dwRe = GetFileAttributes(strPathName);
	if ( dwRe != (DWORD)-1 )
	{
		//ShellExecute(NULL, NULL, strFilePath, NULL, NULL, SW_RESTORE); 
	}
	else 
	{
		CString errormessage;
		errormessage.Format(strPathName + " 文件不存在！");
		Log(Error, errormessage);
		return;
	}

	LArmyDef.RemoveAll();

	//打开文件
	CStdioFile StdFile;
	StdFile.Open(strPathName,CFile::modeRead | CFile::shareDenyNone);

	//逐行读取字符串
	while( StdFile.ReadString( szLine ) )
	{
		index = szLine.Find(';');
		if(index >= 0)
			szLine.Delete(szLine.Find(';'), szLine.GetLength() - szLine.Find(';'));
		index = szLine.Find("//");
		if(index >= 0)
			szLine.Delete(szLine.Find(';'), szLine.GetLength() - szLine.Find("//"));

		if(0 != GetValueStep && szLine.Find("[army]") == 0) {
			GetValueStep = 1;
			LArmyDef.AddTail(TmpArmyDef);
			TmpArmyDef.Code = "";
			TmpArmyDef.Name = "";
			TmpArmyDef.reborn_delay = "";
			TmpArmyDef.reborn_range = "";
			TmpArmyDef.disappear_time = "";
			TmpArmyDef.list = "";
			TmpArmyDef.map_list = "";
			TmpArmyDef.mission_boss = "";
			continue;
		}
		if(0 == GetValueStep && szLine.Find("[army]") == 0) {
			GetValueStep++;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("code = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 7);
			TmpArmyDef.Code = strRight;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("name = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 7);
			TmpArmyDef.Name = strRight;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("reborn_delay = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 15);
			TmpArmyDef.reborn_delay = strRight;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("reborn_range = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 15);
			TmpArmyDef.reborn_range = strRight;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("disappear_time = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 17);
			TmpArmyDef.disappear_time = strRight;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("list = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 7);
			TmpArmyDef.list = strRight;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("map = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 6);
			TmpArmyDef.map_list += strRight + ",";
			continue;
		}

		if(1 == GetValueStep && szLine.Find("mission_boss = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 15);
			TmpArmyDef.mission_boss = strRight;
			continue;
		}

	}

	LArmyDef.AddTail(TmpArmyDef);  // 最后一个army

	//关闭文件
	StdFile.Close();
}

void Common::GetPlayers()
{
	int index;
	int GetValueStep = 0;
	CString strGap = ",";
	Players TempPlayers;
	DWORD dwRe;

	CString StrValue;
	CString strPathName="";
	::GetCurrentDirectory(1024,strPathName.GetBuffer(1024));
	strPathName.ReleaseBuffer();
	strPathName += "\\PLAYERS.TXT";

// 	CString strAlldef="";
// 	::GetCurrentDirectory(1024,strAlldef.GetBuffer(1024));
// 	strAlldef.ReleaseBuffer();
// 	strAlldef += "\\Alldef.TXT";
// 
// 	dwRe = GetFileAttributes(strAlldef);
// 	if ( dwRe != (DWORD)-1 )
// 	{
// 		DeleteFile(strAlldef);
// 	}
// 
// 	//打开文件
// 	CStdioFile StdAlldef;
// 	StdAlldef.Open(strAlldef,CFile::modeCreate | CFile::modeWrite | CFile::shareDenyNone);

	CString szLine = "";

	CString Alldef = "";

	//检查文件是否存在
	dwRe = GetFileAttributes(strPathName);
	if ( dwRe != (DWORD)-1 )
	{
		//ShellExecute(NULL, NULL, strFilePath, NULL, NULL, SW_RESTORE); 
	}
	else 
	{
		CString errormessage;
		errormessage.Format("%s 文件不存在！", strPathName);
		AfxMessageBox(errormessage);
		return;
	}

	LPlayers.RemoveAll();

	//打开文件
	CStdioFile StdFile;
	StdFile.Open(strPathName,CFile::modeRead | CFile::shareDenyNone);

	//逐行读取字符串
	while( StdFile.ReadString( szLine ) )
	{
		//szLine.Replace('\t', ' ');
		//szLine.Replace(_T(" "), _T(""));
		index = szLine.Find(';');
		if(index >= 0)
			szLine.Delete(szLine.Find(';'), szLine.GetLength() - szLine.Find(';'));
		index = szLine.Find("//");
		if(index >= 0)
			szLine.Delete(szLine.Find(';'), szLine.GetLength() - szLine.Find("//"));

		if(0 != GetValueStep && szLine.Compare("[character]") == 0) {
			GetValueStep = 1;
			LPlayers.AddTail(TempPlayers);
			TempPlayers.code = "";
			TempPlayers.name = "";
			TempPlayers.level = "";
			TempPlayers.wid = "";
			TempPlayers.size = "";
			TempPlayers.Class = "";
			TempPlayers.exp = "";
			TempPlayers.hp = "";
			TempPlayers.mp = "";
			TempPlayers.attr_str = "";
			TempPlayers.attr_int = "";
			TempPlayers.attr_mind = "";
			TempPlayers.attr_con = "";
			TempPlayers.attr_dex = "";
			TempPlayers.attr_leader = "";
			TempPlayers.walk_speed = "";
			TempPlayers.run_speed = "";
			TempPlayers.attack_speed = "";
			TempPlayers.attack_delay = "";
			TempPlayers.cast_attack_delay = "";
			TempPlayers.attack_range = "";
			TempPlayers.attack_effect_range = "";
			TempPlayers.damage = "";
			TempPlayers.defense = "";
			TempPlayers.magic_attack_type = "";
			TempPlayers.ai = "";
			TempPlayers.ai_reborn_range = "";
			TempPlayers.ai_reborn_delay = "";
			TempPlayers.ai_guard_range = "";
			TempPlayers.gold = "";
			TempPlayers.drop = "";
			TempPlayers.sfx_move = "";
			TempPlayers.sfx_attack = "";
			TempPlayers.sfx_hit = "";
			TempPlayers.sfx_hurt = "";
			TempPlayers.sfx_dead = "";
			TempPlayers.country = "";
			TempPlayers.skill_exp = "";
			TempPlayers.attr_level = "";
			TempPlayers.ratio_hit = "";
			TempPlayers.height = "";
			TempPlayers.drop_mission = "";
			TempPlayers.magic_defense_type = "";
			TempPlayers.ai_call_range = "";
			TempPlayers.ratio_miss = "";
			TempPlayers.ratio_attack_x2 = "";
			TempPlayers.function = "";
			TempPlayers.set_color = "";
			TempPlayers.sex = "";
			TempPlayers.dead_horse = "";
			TempPlayers.zoom = "";
			TempPlayers.special_attack = "";
			TempPlayers.magic_power = "";
			TempPlayers.anti_status = "";
			TempPlayers.appear_time = "";
			TempPlayers.spc_flag = "";
			TempPlayers.call_sol1 = "";
			TempPlayers.call_sol2 = "";
			TempPlayers.call_sol3 = "";
			TempPlayers.call_sol_total = "";
			TempPlayers.appear_ratio = "";
			TempPlayers.no_back_off = "";
			TempPlayers.ai_help_self_ratio = "";
			TempPlayers.ai_help_self_magic = "";
			TempPlayers.ai_help_self_level = "";
			TempPlayers.equip_weapon = "";
			TempPlayers.equip_horse = "";
			TempPlayers.bp = "";
			TempPlayers.office = "";
			TempPlayers.call_sol4 = "";
			TempPlayers.ai_fast_run_ratio = "";
			TempPlayers.ai_fast_run_magic = "";
			TempPlayers.ai_fast_run_level = "";
			TempPlayers.boss_cast_all = "";
			TempPlayers.call_ratio = "";
			TempPlayers.hp_low_ratio_attack = "";
			TempPlayers.attack_spec_ratio = "";
			TempPlayers.cnpc_flag = "";
			TempPlayers.armor_bless = "";
			TempPlayers.boss_teleport = "";
			TempPlayers.equip_shield = "";
			TempPlayers.boss_call_all = "";
			TempPlayers.use_leader = "";
			TempPlayers.cnpc_cell = "";
			TempPlayers.talk_no_dir = "";
			TempPlayers.boss_soul_item = "";
			TempPlayers.call_sol5 = "";
			continue;
		}
		if(0 == GetValueStep && szLine.Compare("[character]") == 0) {
			GetValueStep++;
			continue;
		}

// 		if(1 == GetValueStep)
// 		{
// 			CString strLeft = szLine.Left(szLine.Find('='));
// 			if(Alldef.Find(strLeft) == -1)
// 			{
// 				CString strDef = strLeft;
// 				strDef.Replace(" ", "");
// 				strLeft += "= ";
// 				int nLen = strLeft.GetLength();
// 				Alldef += strLeft;
// 				CString strRet = "";
// 				strRet = "\tif(1 == GetValueStep && szLine.Find(\""+ strLeft +"\") == 0)\n" \
// 					+ "\t{\n" \
// 					+ "\t\tCString strRight = szLine.Right(szLine.GetLength() - " + convert(nLen) + ");\n" \
// 					+ "\t\tTempPlayers." + strDef + " = strRight;\n" \
// 					+ + "\t\tcontinue;\n"
// 					+ "\t}\n\n";
// 
// 				StdAlldef.WriteString(strRet);
// 			}			
// 		}

// 		if(1 == GetValueStep)
// 		{
// 			CString strLeft = szLine.Left(szLine.Find('='));
// 			if(Alldef.Find(strLeft) == -1)
// 			{
// 				CString strDef = strLeft;
// 				strDef.Replace(" ", "");
// 				Alldef += strLeft;
// 				CString strRet = "";
// 				strRet = "\tTempPlayers." + strDef + " = \"\";\n";
// 
// 				StdAlldef.WriteString(strRet);
// 			}			
// 		}

		if(1 == GetValueStep && szLine.Find("code = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 7);
			TempPlayers.code = strRight;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("name = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 7);
			TempPlayers.name = strRight;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("level = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 8);
			TempPlayers.level = strRight;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("wid = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 6);
			TempPlayers.wid = strRight;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("size = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 7);
			TempPlayers.size = strRight;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("class = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 8);
			TempPlayers.Class = strRight;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("exp = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 6);
			TempPlayers.exp = strRight;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("hp = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 5);
			TempPlayers.hp = strRight;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("mp = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 5);
			TempPlayers.mp = strRight;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("attr_str = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 11);
			TempPlayers.attr_str = strRight;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("attr_int = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 11);
			TempPlayers.attr_int = strRight;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("attr_mind = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 12);
			TempPlayers.attr_mind = strRight;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("attr_con = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 11);
			TempPlayers.attr_con = strRight;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("attr_dex = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 11);
			TempPlayers.attr_dex = strRight;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("attr_leader = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 14);
			TempPlayers.attr_leader = strRight;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("walk_speed = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 13);
			TempPlayers.walk_speed = strRight;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("run_speed = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 12);
			TempPlayers.run_speed = strRight;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("attack_speed = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 15);
			TempPlayers.attack_speed = strRight;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("attack_delay = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 15);
			TempPlayers.attack_delay = strRight;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("cast_attack_delay = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 20);
			TempPlayers.cast_attack_delay = strRight;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("attack_range = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 15);
			TempPlayers.attack_range = strRight;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("attack_effect_range = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 22);
			TempPlayers.attack_effect_range = strRight;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("damage = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 9);
			TempPlayers.damage = strRight;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("defense = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 10);
			TempPlayers.defense = strRight;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("magic_attack_type = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 20);
			TempPlayers.magic_attack_type = strRight;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("ai = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 5);
			TempPlayers.ai = strRight;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("ai_reborn_range = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 18);
			TempPlayers.ai_reborn_range = strRight;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("ai_reborn_delay = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 18);
			TempPlayers.ai_reborn_delay = strRight;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("ai_guard_range = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 17);
			TempPlayers.ai_guard_range = strRight;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("gold = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 7);
			TempPlayers.gold = strRight;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("drop = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 7);
			TempPlayers.drop = strRight;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("sfx_move = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 11);
			TempPlayers.sfx_move = strRight;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("sfx_attack = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 13);
			TempPlayers.sfx_attack = strRight;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("sfx_hit = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 10);
			TempPlayers.sfx_hit = strRight;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("sfx_hurt = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 11);
			TempPlayers.sfx_hurt = strRight;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("sfx_dead = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 11);
			TempPlayers.sfx_dead = strRight;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("country = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 10);
			TempPlayers.country = strRight;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("skill_exp = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 12);
			TempPlayers.skill_exp = strRight;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("attr_level = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 13);
			TempPlayers.attr_level = strRight;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("ratio_hit = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 12);
			TempPlayers.ratio_hit = strRight;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("height = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 9);
			TempPlayers.height = strRight;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("drop_mission = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 15);
			TempPlayers.drop_mission = strRight;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("magic_defense_type = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 21);
			TempPlayers.magic_defense_type = strRight;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("ai_call_range = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 16);
			TempPlayers.ai_call_range = strRight;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("ratio_miss = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 13);
			TempPlayers.ratio_miss = strRight;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("ratio_attack_x2 = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 18);
			TempPlayers.ratio_attack_x2 = strRight;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("function = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 11);
			TempPlayers.function = strRight;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("set_color = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 12);
			TempPlayers.set_color = strRight;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("sex = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 6);
			TempPlayers.sex = strRight;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("dead_horse = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 13);
			TempPlayers.dead_horse = strRight;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("zoom = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 7);
			TempPlayers.zoom = strRight;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("special_attack = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 17);
			TempPlayers.special_attack = strRight;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("magic_power = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 14);
			TempPlayers.magic_power = strRight;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("anti_status = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 14);
			TempPlayers.anti_status = strRight;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("appear_time = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 14);
			TempPlayers.appear_time = strRight;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("spc_flag = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 11);
			TempPlayers.spc_flag = strRight;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("call_sol1 = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 12);
			TempPlayers.call_sol1 = strRight;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("call_sol2 = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 12);
			TempPlayers.call_sol2 = strRight;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("call_sol3 = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 12);
			TempPlayers.call_sol3 = strRight;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("call_sol_total = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 17);
			TempPlayers.call_sol_total = strRight;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("appear_ratio = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 15);
			TempPlayers.appear_ratio = strRight;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("no_back_off = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 14);
			TempPlayers.no_back_off = strRight;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("ai_help_self_ratio = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 21);
			TempPlayers.ai_help_self_ratio = strRight;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("ai_help_self_magic = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 21);
			TempPlayers.ai_help_self_magic = strRight;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("ai_help_self_level = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 21);
			TempPlayers.ai_help_self_level = strRight;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("equip_weapon = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 15);
			TempPlayers.equip_weapon = strRight;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("equip_horse = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 14);
			TempPlayers.equip_horse = strRight;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("bp = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 5);
			TempPlayers.bp = strRight;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("office = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 9);
			TempPlayers.office = strRight;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("call_sol4 = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 12);
			TempPlayers.call_sol4 = strRight;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("ai_fast_run_ratio = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 20);
			TempPlayers.ai_fast_run_ratio = strRight;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("ai_fast_run_magic = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 20);
			TempPlayers.ai_fast_run_magic = strRight;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("ai_fast_run_level = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 20);
			TempPlayers.ai_fast_run_level = strRight;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("boss_cast_all = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 16);
			TempPlayers.boss_cast_all = strRight;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("call_ratio = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 13);
			TempPlayers.call_ratio = strRight;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("hp_low_ratio_attack = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 22);
			TempPlayers.hp_low_ratio_attack = strRight;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("attack_spec_ratio = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 20);
			TempPlayers.attack_spec_ratio = strRight;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("cnpc_flag = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 12);
			TempPlayers.cnpc_flag = strRight;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("armor_bless = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 14);
			TempPlayers.armor_bless = strRight;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("boss_teleport = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 16);
			TempPlayers.boss_teleport = strRight;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("equip_shield = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 15);
			TempPlayers.equip_shield = strRight;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("boss_call_all = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 16);
			TempPlayers.boss_call_all = strRight;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("use_leader = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 13);
			TempPlayers.use_leader = strRight;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("cnpc_cell = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 12);
			TempPlayers.cnpc_cell = strRight;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("talk_no_dir = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 14);
			TempPlayers.talk_no_dir = strRight;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("boss_soul_item = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 17);
			TempPlayers.boss_soul_item = strRight;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("call_sol5 = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 12);
			TempPlayers.call_sol5 = strRight;
			continue;
		}
	
	}
 
	LPlayers.AddTail(TempPlayers);  // 最后一个player

	//关闭文件
	StdFile.Close();
	//StdAlldef.Close();
}

void Common::GetDrops()
{
	int index;
	CString strGap = ",";

	CString StrValue;
	CString strPathName="";
	::GetCurrentDirectory(1024,strPathName.GetBuffer(1024));
	strPathName.ReleaseBuffer();
	strPathName += "\\DROPITEM-NEW.TXT";

	CString szLine = "";
	CString strResult;

	//检查文件是否存在
	DWORD dwRe = GetFileAttributes(strPathName);
	if ( dwRe != (DWORD)-1 )
	{
		//ShellExecute(NULL, NULL, strFilePath, NULL, NULL, SW_RESTORE); 
	}
	else 
	{
		CString errormessage;
		errormessage.Format("%s 文件不存在！", strPathName);
		AfxMessageBox(errormessage);
		return;
	}

	LDropsRange.RemoveAll();

	//打开文件
	CStdioFile StdFile;
	StdFile.Open(strPathName,CFile::modeRead | CFile::shareDenyNone);

	//逐行读取字符串
	while( StdFile.ReadString( szLine ) )
	{
		szLine.Replace('\t', ' ');
		szLine.Replace(_T(" "), _T(""));
		index = szLine.Find(';');
		if(index >= 0)
			szLine.Delete(szLine.Find(';'), szLine.GetLength() - szLine.Find(';'));
		index = szLine.Find("//");
		if(index >= 0)
			szLine.Delete(szLine.Find(';'), szLine.GetLength() - szLine.Find("//"));

		if(szLine.Find("drop=") == 0)  // get item
		{
			DropsRange TempDropsRange;
			CStringArray strDest;
			szLine.Replace(_T("drop="), _T(""));

			CString temp11 = szLine;
			int nPos = temp11.Find(strGap);
			CString strLeft = _T("");
			temp11 = temp11.Right(temp11.GetLength() - nPos - 1);
			temp11.Replace("Item", "item");
			temp11.Replace("ITEM", "item");
			TempDropsRange.DropRange = temp11;

			nPos = szLine.Find(strGap);
			strLeft = _T("");
			while(0 <= nPos)
			{
				strLeft = szLine.Left(nPos);
				strDest.Add(strLeft);
				int  len = szLine.GetLength();
				szLine = szLine.Right(szLine.GetLength() - nPos - 1);
				nPos = szLine.Find(strGap);
			}

			if (!szLine.IsEmpty()) {
				strDest.Add(szLine);
			}
			TempDropsRange.DropId = strDest[0];
// 			for(int i = 1; i < strDest.GetCount();)
// 			{
// 				TempDropsRange.ItemName.Add(strDest[i++]);
// 				TempDropsRange.Range.Add(strDest[i++]);
// 			}

			if(LDropsRange.GetCount() == 0)
				LDropsRange.AddTail(TempDropsRange);
			else
			{
				int i;
				POSITION pos = LDropsRange.GetHeadPosition();
				for (i=0;i < LDropsRange.GetCount();i++)
				{
					POSITION curPos = pos;
					DropsRange temp = LDropsRange.GetNext(pos);
					if(_ttoi(TempDropsRange.DropId) < _ttoi(temp.DropId))
					{
						LDropsRange.InsertBefore(curPos, TempDropsRange);
						break;
					}
				}
				if(i == LDropsRange.GetCount())
					LDropsRange.AddTail(TempDropsRange);
			}
		}
	}
	//关闭文件
	StdFile.Close();
}

void Common::GetBagsDrop()
{
	int index;
	int GetValueStep = 0;
	CString strGap = ",";

	CString StrValue;
	CString strPathName="";
	::GetCurrentDirectory(1024,strPathName.GetBuffer(1024));
	strPathName.ReleaseBuffer();
	strPathName += "\\ITEM.TXT";

	CString szLine = "";
	CString strName, strDropId;


	//检查文件是否存在
	DWORD dwRe = GetFileAttributes(strPathName);
	if ( dwRe != (DWORD)-1 )
	{
		//ShellExecute(NULL, NULL, strFilePath, NULL, NULL, SW_RESTORE); 
	}
	else 
	{
		CString errormessage;
		errormessage.Format("%s 文件不存在！", strPathName);
		AfxMessageBox(errormessage);
		return;
	}

	LBagsDrop.RemoveAll();

	//打开文件
	CStdioFile StdFile;
	StdFile.Open(strPathName,CFile::modeRead | CFile::shareDenyNone);

	//逐行读取字符串
	while( StdFile.ReadString( szLine ) )
	{
		//szLine.Replace('\t', ' ');
		//szLine.Replace(_T(" "), _T(""));
		index = szLine.Find(';');
		if(index >= 0)
			szLine.Delete(szLine.Find(';'), szLine.GetLength() - szLine.Find(';'));
		index = szLine.Find("//");
		if(index >= 0)
			szLine.Delete(szLine.Find(';'), szLine.GetLength() - szLine.Find("//"));

		if(0 == GetValueStep && szLine.Compare("[item]") == 0) {  //初始化了
			GetValueStep++;
			continue;
		}

		if(0 != GetValueStep && szLine.Compare("[item]") == 0) {
			if(GetValueStep == 2)
			{
				BagsDrop TempBagsDrop;
				TempBagsDrop.ItemName = strName;
				TempBagsDrop.DropId = strDropId;
				LBagsDrop.AddTail(TempBagsDrop);
			}
			strName = "";
			strDropId = "" ;
			GetValueStep = 1;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("code = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 7);
			strName = strRight;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("type = ") == 0)
		{
			if(szLine.Find("itemTypeLetto") > 0)
				GetValueStep++;
			continue;
		}
		if(2 == GetValueStep && szLine.Find("use_magic_id = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 15);
			if(IsDigital(strRight))
				strDropId = strRight;
			continue;
		}

	}

	if(GetValueStep == 2)  //最后一个项目
	{
		BagsDrop TempBagsDrop;
		TempBagsDrop.ItemName = strName;
		TempBagsDrop.DropId = strDropId;
		LBagsDrop.AddTail(TempBagsDrop);
	}


	//关闭文件
	StdFile.Close();
}

void Common::GetServerMapList()
{
	int index;
	int GetValueStep = 0;
	CString strPathName;
	struct ArmyDef TmpArmyDef;
	int ret = 0;

	strPathName.Format("%sserver.ini", CONFIG_FILE_PATH);
	CString szLine = "";

	//检查文件是否存在
	DWORD dwRe = GetFileAttributes(strPathName);
	if ( dwRe != (DWORD)-1 )
	{
		//ShellExecute(NULL, NULL, strFilePath, NULL, NULL, SW_RESTORE); 
	}
	else 
	{
		CString errormessage;
		errormessage.Format(strPathName + " 文件不存在！");
		Log(Error, errormessage);
		return;
	}

	strServerMapList = ",";

	//打开文件
	CStdioFile StdFile;
	StdFile.Open(strPathName,CFile::modeRead | CFile::shareDenyNone);

	//逐行读取字符串
	while( StdFile.ReadString( szLine ) )
	{
		index = szLine.Find(';');
		if(index >= 0)
			szLine.Delete(szLine.Find(';'), szLine.GetLength() - szLine.Find(';'));
		index = szLine.Find("//");
		if(index >= 0)
			szLine.Delete(szLine.Find(';'), szLine.GetLength() - szLine.Find("//"));

		if(0 == GetValueStep && szLine.Find("[MapServer]") == 0) {
			GetValueStep++;
			continue;
		}

		if(1 == GetValueStep && szLine.Find("set_map = ") == 0)
		{
			CString strRight = szLine.Right(szLine.GetLength() - 10);
			strServerMapList += strRight + ",";
			continue;
		}
	}
	strServerMapList.Replace(",0", ",");  // 去掉数字前的0
	//关闭文件
	StdFile.Close();
}

void Common::GetServerConfig()
{
	CString strPathName;
	ServerConfigTime *CurTimeForCB = &Common::TimeForCB;
	int ret = 0;
	int GetValueStep = 0;
	int index;

	//读取赤壁战场配置
	strPathName = Common::ServerPath + "login\\LoginHistory.ini";
	CString szLine = "";
	CString strResult;

	//检查文件是否存在
	DWORD dwRe = GetFileAttributes(strPathName);
	if ( dwRe != (DWORD)-1 )
	{
		//ShellExecute(NULL, NULL, strFilePath, NULL, NULL, SW_RESTORE); 
	}
	else 
	{
 		CString errormessage;
 		errormessage.Format("%s 配置文件不存在！", strPathName);
		Log(Error, errormessage);
		return;
	}

	//打开文件
	CStdioFile StdFile;
	StdFile.Open(strPathName,CFile::modeRead | CFile::shareDenyNone);

	//逐行读取字符串
	while( StdFile.ReadString( szLine ) )
	{
		szLine.Replace('\t', ' ');
		szLine.Replace(_T(" "), _T(""));
		index = szLine.Find(';');
		if(index >= 0)
			szLine.Delete(szLine.Find(';'), szLine.GetLength() - szLine.Find(';'));
		if(0 != GetValueStep && szLine.Compare("[history]") == 0) {
			GetValueStep = 0;
			continue;
		}
		if(0 == GetValueStep && szLine.Compare("[history]") == 0) {
			GetValueStep++;
			continue;
		}
		if(1 == GetValueStep && szLine.Compare("type=1") == 0)
		{
			GetValueStep++;
			continue;
		}

		if(2 == GetValueStep)
		{
			index = szLine.Find(',');
			for(int i = 0;index > 0; i++)
			{
				if(0 != i%2) szLine.SetAt(index, ':');
				index = szLine.Find(',', index+1);
			}
		}

		if(2 == GetValueStep && szLine.Find("period") == 0)
		{
			szLine.Replace("period=", "");
			CurTimeForCB->Period = szLine;
			continue;
		}
		if(2 == GetValueStep && szLine.Find("time=1") == 0)
		{
			CStringGap(szLine, &(CurTimeForCB->ModStartTimes), "time=1", ",", 1);
			continue;
		}
		if(2 == GetValueStep && szLine.Find("time=2") == 0)
		{
			CStringGap(szLine, &(CurTimeForCB->TuseStartTimes), "time=2", ",", 1);
			continue;
		}
		if(2 == GetValueStep && szLine.Find("time=3") == 0)
		{
			CStringGap(szLine, &(CurTimeForCB->WedStartTimes), "time=3", ",", 1);
			continue;
		}
		if(2 == GetValueStep && szLine.Find("time=4") == 0)
		{
			CStringGap(szLine, &(CurTimeForCB->ThursStartTimes), "time=4", ",", 1);
			continue;
		}
		if(2 == GetValueStep && szLine.Find("time=5") == 0)
		{
			CStringGap(szLine, &(CurTimeForCB->FriStartTimes), "time=5", ",", 1);
			continue;
		}
		if(2 == GetValueStep && szLine.Find("time=6") == 0)
		{
			CStringGap(szLine, &(CurTimeForCB->SatStartTimes), "time=6", ",", 1);
			continue;
		}
		if(2 == GetValueStep && szLine.Find("time=7") == 0)
		{
			CStringGap(szLine, &(CurTimeForCB->SunStartTimes), "time=7", ",", 1);
			continue;
		}
	}
	//关闭文件
	StdFile.Close();
/************************************************************************************************/

	//读取国战配置
	CString StrValue;
	CString strStartTime;
	CStringArray strStartDate;
	ServerConfigTime *CurTimeForCwar = &Common::TimeForCwar;
	strPathName = Common::ServerPath + "login\\LoginServer.ini";

	//检查文件是否存在
	dwRe = GetFileAttributes(strPathName);
	if ( dwRe != (DWORD)-1 )
	{		
	}
	else 
	{
		return;
	}

	GetPrivateProfileString("System","country_war_period","",StrValue.GetBuffer(128),128,strPathName);
	CurTimeForCwar->Period = StrValue;
	StrValue.ReleaseBuffer();

	GetPrivateProfileString("System","country_war_time","",StrValue.GetBuffer(128),128,strPathName);
	strStartTime = StrValue;
	StrValue.ReleaseBuffer();
	strStartTime.Replace(',', ':');

	GetPrivateProfileString("System","country_war_date","",StrValue.GetBuffer(128),128,strPathName);
	CString strTemp = StrValue; // 使用StrValue有问题，需要先ReleaseBuffer
	StrValue.ReleaseBuffer();
	CStringGap(strTemp, &strStartDate, "Cwar", ",", 0);
	for(int i = 0; i < strStartDate.GetCount(); i++)
	{
		switch (_ttoi(strStartDate[i]))
		{
		case 1:
			{
				CurTimeForCwar->ModStartTimes.Add(strStartTime);
				break;
			}
		case 2:
			{
				CurTimeForCwar->TuseStartTimes.Add(strStartTime);
				break;
			}
		case 3:
			{
				CurTimeForCwar->WedStartTimes.Add(strStartTime);
				break;
			}
		case 4:
			{
				CurTimeForCwar->ThursStartTimes.Add(strStartTime);
				break;
			}
		case 5:
			{
				CurTimeForCwar->FriStartTimes.Add(strStartTime);
				break;
			}
		case 6:
			{
				CurTimeForCwar->SatStartTimes.Add(strStartTime);
				break;
			}
		case 7:
			{
				CurTimeForCwar->SunStartTimes.Add(strStartTime);
				break;
			}

		default:
			break;
		}
	}
}

void Common::Log(int Level, CString Msg)
{
	if(Level <= LogLevel)
		::SendMessage(Common::DlgLog, WM_LOGSERVER, 0, (LPARAM)(&Msg));
}