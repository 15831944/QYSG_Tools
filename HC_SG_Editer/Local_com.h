#pragma once
#include "StructDef.h"

#define TIMER1 1
#define TIMER2 2
#define TIMER3 3
#define TIMER4 4
#define TIMER5 5
#define TIMER_UPDATE 10

#define CONFIG_FILE_PATH ".\\Profile\\"
#define CONFIG_FILE "配置.ini"
#define ITEM_H "item.h"
#define STAGE_H "stage.h"
#define ARMY_TXT "ARMY.TXT"
#define ARMY_NAME_TXT "ARMY_NAME.TXT"

#define TEMP_FILE_PATH ".\\Temp\\"
#define ITEM_DAT "item.dat"
#define STORE_DAT "store.dat"


//定义日志等级
#define Fatal	1
#define Error	2
#define Warn	3
#define Info	4
#define Debug	5

#define WM_SHOWTASK				(WM_USER+100)
#define WM_SQLCONCT				(WM_USER+101)
#define WM_SAVECWARORGAWARDS	(WM_USER+102)
#define WM_SAVECWARPLAYERAWARDS (WM_USER+103)
#define WM_SAVECBAWARDS			(WM_USER+104)
#define WM_SAVEXUBAOCONFIG		(WM_USER+105)
#define WM_LOGSERVER			(WM_USER+106)

class Common
{
public:
	Common(void);
	~Common(void);

	static BOOL SanGuoServerIsRuning;

	static HWND DlgCwarOrg;
	static HWND DlgCwarPlayer;
	static HWND DlgAttr;
	static HWND DlgCB;
	static HWND DlgServer;
	static HWND DlgXubao;
	static HWND DlgLog;
	static HWND DlgDrop;
	static HWND DlgArmy;
	static HWND DlgPlayer;

	static int LogLevel;

	static BOOL IsEnConn;
	static BOOL IsDbConct;

	static CString ServerPath;
	static CString SQLServer;
	static CString SQLAccount;
	static CString SQLPassWord;
	
	static CString mEditAcc;
	static CString mEditDB;
	static CString mEditLogin;
	static CString mEditVT;
	static CString mEditMap1;
	static CString mEditMap2;
	static CString mEditMap3;
	static CString mEditMap4;
	static CString mEditBackup1;
	static CString mEditBackup2;
	static CString mEditGate;

	static CString m_CbMinKills;
	static CString m_CbChkMinKills;
	static CString m_CbMinHonors;
	static CString m_CbChkMinHonors;

	static CString m_CWarMinKills;
	static CString m_CWarChkMinKills;
	static CString m_CWarMinHonors;
	static CString m_CWarChkMinHonors;

	static CString m_CWarAwardsChkTime;

	static CStringArray VipAwardsPoints;

	static _ConnectionPtr m_pConnection;
	static _RecordsetPtr m_pRecordset;

	static _ConnectionPtr m_pConnXb;
	static _RecordsetPtr m_pRecordsetXb;

	static CString GB2Big(char*  sGb);
	static CString Big2GB(char*  sBig5);
	static CString convert(int n);
	static void CStringGap(CString strSrc, CStringArray *strDest, CString Key, CString strGap, int Skip = 0);
	static BOOL IsDigital(LPCTSTR lpszSrc);
	static void ReadConfig();
	static void SaveConfig();
	static BOOL SaveAwardsConfig();

	static CList <GameAcc, GameAcc&> LGameAcc;
	static CList <AccAttr, AccAttr&> LAccAttr;
	static CList <AccSkills, AccSkills&> LAccSkills;
	static CList <ItemDef, ItemDef&> LItemDef;
	static CList <Players, Players&> LPlayers;
	static CList <BagsDrop, BagsDrop&> LBagsDrop;
	static CList <DropsRange, DropsRange&> LDropsRange;
	static CList <StageDef, StageDef&> LStageDef;
	static CList <ArmyNameDef, ArmyNameDef&> LArmyNameDef;
	static CList <ArmyDef, ArmyDef&> LArmyDef;
	static CList <OrganizeAttr, OrganizeAttr&> LOrganizeAttr;

	static CString strServerMapList;

	static ServerConfigTime TimeForCB;
	static ServerConfigTime TimeForCwar;

	static void SystemInit();
	static void GetUpdateCLists();

	static void ConnToSQLServer();
	static BOOL SendPoint(int nTotalPoints, CString strAccount);
	static BOOL SendXubao(CString strAccount, CStringArray *ItemList);

	static void GetGameAccFormDB();
	static void GetAccAttr();
	static void GetAccSkills();
	static void GetOrganizeAttr();
	static void GetItemDef();
	static void GetStageDef();
	static void GetArmyNameDef();
	static void GetArmyDef();
	static void GetPlayers();
	static void GetDrops();
	static void GetBagsDrop();
	static void GetServerMapList();

	static void GetServerConfig();

	static void Log(int Level, CString Msg);
};