// ArmyDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "HC_SG_Editer.h"
#include "ArmyDlg.h"
#include "afxdialogex.h"


// CArmyDlg 对话框

IMPLEMENT_DYNAMIC(CArmyDlg, CDialogEx)

	CArmyDlg::CArmyDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CArmyDlg::IDD, pParent)
{

}

CArmyDlg::~CArmyDlg()
{
}

void CArmyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_PLAYERS, m_CListCtrlPlayers);
	DDX_Control(pDX, IDC_LIST_DROPS, m_CListCtrlDrops);
	DDX_Control(pDX, IDC_EDIT_NAME, m_CEditName);
	DDX_Control(pDX, IDC_EDIT_COUNTER, m_CEditCounter);
	DDX_Control(pDX, IDC_EDIT_FIND, m_CEditFind);
	DDX_Control(pDX, IDC_EDIT_DROP_ID, m_CEditDropId);
	DDX_Control(pDX, IDC_ARMY_LIST, m_CListCtrlArmys);
	DDX_Control(pDX, IDC_EDIT_STAGE_FIND, m_CEditStageFind);
	DDX_Control(pDX, IDC_LIST_STAGEDEF, m_CListCtrlStageDef);
	DDX_Control(pDX, IDC_EDIT_CODE, m_CEditCode);
	DDX_Control(pDX, IDC_EDIT_ARMY_NAME_ID, m_CEditArmyNameId);
	DDX_Control(pDX, IDC_EDIT_ARMY_NAME, m_CEditArmyName);
	DDX_Control(pDX, IDC_EDIT_REBORN_DELAY, m_CEditRebornDelay);
	DDX_Control(pDX, IDC_EDIT_REBORN_RANGE, m_CEditRebornRange);
	DDX_Control(pDX, IDC_EDIT_DISAPPEAR_TIME, m_CEditDisappearTime);
	DDX_Control(pDX, IDC_EDIT_MAP_NAME, m_CEditMapName);
	DDX_Control(pDX, IDC_EDIT_MAP_ID, m_CEditMapId);
	DDX_Control(pDX, IDC_EDIT_MAP_X, m_CEditMapX);
	DDX_Control(pDX, IDC_EDIT_MAP_Y, m_CEditMapY);
	DDX_Control(pDX, IDC_EDIT_BOSS_NAME, m_CEditBossName);
	DDX_Control(pDX, IDC_LIST_MAP_LIST, m_CListCtrlMapList);
	DDX_Control(pDX, IDC_LIST_BOSS_LIST, m_CListCtrlBossList);
	DDX_Control(pDX, IDC_EDIT_CODE2, m_CEditCode2);
	DDX_Control(pDX, IDC_EDIT_ARMY_NAME_ID2, m_CEditArmyNameId2);
	DDX_Control(pDX, IDC_EDIT_ARMY_NAME2, m_CEditArmyName2);
	DDX_Control(pDX, IDC_EDIT_REBORN_DELAY2, m_CEditRebornDelay2);
	DDX_Control(pDX, IDC_EDIT_REBORN_RANGE2, m_CEditRebornRange2);
	DDX_Control(pDX, IDC_EDIT_DISAPPEAR_TIME2, m_CEditDisappearTime2);
	DDX_Control(pDX, IDC_EDIT_ORG_FIND, m_CEditOrgFind);
}


BEGIN_MESSAGE_MAP(CArmyDlg, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT_FIND, &CArmyDlg::OnEnChangeEditFind)
	ON_BN_CLICKED(IDC_BUTTON_PLAYER_NEXT, &CArmyDlg::OnBnClickedButtonPlayerNext)
	ON_NOTIFY(NM_CLICK, IDC_LIST_PLAYERS, &CArmyDlg::OnNMClickListPlayers)
	ON_BN_CLICKED(IDC_BUTTON_OUTPUT, &CArmyDlg::OnBnClickedButtonOutput)
	ON_BN_CLICKED(IDC_BUTTON_ADD_ORG, &CArmyDlg::OnBnClickedButtonAddOrg)
	ON_BN_CLICKED(IDC_BUTTON_ARMY_SAVE, &CArmyDlg::OnBnClickedButtonArmySave)
	ON_BN_CLICKED(IDC_BUTTON_AUTO, &CArmyDlg::OnBnClickedButtonAuto)
	ON_EN_CHANGE(IDC_EDIT_ARMY_NAME_ID2, &CArmyDlg::OnEnChangeEditArmyNameId2)
	ON_NOTIFY(NM_CLICK, IDC_ARMY_LIST, &CArmyDlg::OnNMClickArmyList)
	ON_EN_CHANGE(IDC_EDIT_ARMY_NAME_ID, &CArmyDlg::OnEnChangeEditArmyNameId)
	ON_BN_CLICKED(IDC_BUTTON_DEL_ORG, &CArmyDlg::OnBnClickedButtonDelOrg)
	ON_EN_CHANGE(IDC_EDIT_ORG_FIND, &CArmyDlg::OnEnChangeEditOrgFind)
	ON_BN_CLICKED(IDC_BUTTON_ORG_NEXT, &CArmyDlg::OnBnClickedButtonOrgNext)
	ON_BN_CLICKED(IDC_BUTTON_REFLASH, &CArmyDlg::OnBnClickedButtonReflash)
	ON_EN_CHANGE(IDC_EDIT_STAGE_FIND, &CArmyDlg::OnEnChangeEditStageFind)
	ON_BN_CLICKED(IDC_BUTTON_STAGE_NEXT, &CArmyDlg::OnBnClickedButtonStageNext)
	ON_NOTIFY(NM_CLICK, IDC_LIST_STAGEDEF, &CArmyDlg::OnNMClickListStagedef)
	ON_EN_CHANGE(IDC_EDIT_MAP_ID, &CArmyDlg::OnEnChangeEditMapId)
	ON_BN_CLICKED(IDC_BUTTON_ADD_MAP, &CArmyDlg::OnBnClickedButtonAddMap)
	ON_BN_CLICKED(IDC_BUTTON_DEL_MAP2, &CArmyDlg::OnBnClickedButtonDelMap2)
	ON_BN_CLICKED(IDC_BUTTON_ADD_BOSS, &CArmyDlg::OnBnClickedButtonAddBoss)
	ON_BN_CLICKED(IDC_BUTTON_DEL_BOSS, &CArmyDlg::OnBnClickedButtonDelBoss)
	ON_BN_CLICKED(IDC_BUTTON_SYNC, &CArmyDlg::OnBnClickedButtonSync)
END_MESSAGE_MAP()


// CArmyDlg 消息处理程序


BOOL CArmyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_CListCtrlPlayers.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP);
	m_CListCtrlPlayers.InsertColumn(0, _T("怪物名称"), LVCFMT_LEFT, 100);//插入列
	m_CListCtrlPlayers.InsertColumn(1, _T("爆率ID"), LVCFMT_LEFT, 60);//插入列
	m_CListCtrlPlayers.InsertColumn(2, _T("繁体"), LVCFMT_LEFT, 0);//插入列


	m_CListCtrlDrops.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP);
	m_CListCtrlDrops.InsertColumn(0, _T("掉落物品"), LVCFMT_LEFT, 95);//插入列
	m_CListCtrlDrops.InsertColumn(1, _T("掉落几率"), LVCFMT_LEFT, 80);
	m_CListCtrlDrops.InsertColumn(2, _T("繁体"), LVCFMT_LEFT, 0);

	m_CListCtrlArmys.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP);
	m_CListCtrlArmys.InsertColumn(0, _T("Code"), LVCFMT_LEFT, 40);//插入列
	m_CListCtrlArmys.InsertColumn(1, _T("NameID"), LVCFMT_LEFT, 50);
	m_CListCtrlArmys.InsertColumn(2, _T("Name"), LVCFMT_LEFT, 60);
	m_CListCtrlArmys.InsertColumn(3, _T("Delay"), LVCFMT_LEFT, 40);
	m_CListCtrlArmys.InsertColumn(4, _T("Army List"), LVCFMT_LEFT, 300);//插入列
	m_CListCtrlArmys.InsertColumn(5, _T("Map List"), LVCFMT_LEFT, 300);
	m_CListCtrlArmys.InsertColumn(6, _T("繁体"), LVCFMT_LEFT, 0);//插入列
	m_CListCtrlArmys.InsertColumn(7, _T("数字型地图列表"), LVCFMT_LEFT, 0);//插入列

	m_CListCtrlStageDef.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP);
	m_CListCtrlStageDef.InsertColumn(0, _T("ID"), LVCFMT_LEFT, 35);//插入列
	m_CListCtrlStageDef.InsertColumn(1, _T("Name"), LVCFMT_LEFT, 100);//插入列

	m_CListCtrlBossList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP);
	m_CListCtrlBossList.InsertColumn(0, _T("Boss名称"), LVCFMT_LEFT, 150);//插入列
	m_CListCtrlBossList.InsertColumn(1, _T("繁体"), LVCFMT_LEFT, 0);//插入列

	m_CListCtrlMapList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP);
	m_CListCtrlMapList.InsertColumn(0, _T("MapID"), LVCFMT_LEFT, 45);//插入列	
	m_CListCtrlMapList.InsertColumn(1, _T("X坐标"), LVCFMT_LEFT, 45);//插入列
	m_CListCtrlMapList.InsertColumn(2, _T("Y坐标"), LVCFMT_LEFT, 45);//插入列
	m_CListCtrlMapList.InsertColumn(3, _T("Name"), LVCFMT_LEFT, 80);//插入列

	InitPlayers();
	InitArmyLists();
	InitStageList();

	m_CEditCode2.SetWindowTextA("");
	m_CEditArmyNameId2.SetWindowTextA("");
	m_CEditRebornDelay2.SetWindowTextA("2");
	m_CEditRebornRange2.SetWindowTextA("300");
	m_CEditDisappearTime2.SetWindowTextA("240");

	m_CEditMapX.SetWindowTextA("32000");
	m_CEditMapY.SetWindowTextA("1600");

	strCurSelBoss = "";

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CArmyDlg::InitPlayers()
{
	// TODO: 在此添加控件通知处理程序代码
	struct Players TmpPlayers;
	CList <Players, Players&> *LCurPlayers = &Common::LPlayers;
	int ret = 0;
	POSITION pos;

	m_CListCtrlPlayers.DeleteAllItems();

	//将获得的物品显示到ClistCtrl里去
	pos = LCurPlayers->GetHeadPosition();
	for (int i=0;i < LCurPlayers->GetCount();i++)
	{
		TmpPlayers = LCurPlayers->GetNext(pos);

		int nrow = m_CListCtrlPlayers.GetItemCount();//取行数
		int nItem = m_CListCtrlPlayers.InsertItem(nrow+1, _T(""));
		CString tempName = TmpPlayers.code;
		tempName.Replace("role_", "");
		m_CListCtrlPlayers.SetItemText(nItem, 0, _T(Common::Big2GB((LPSTR)(LPCTSTR)tempName)));
		m_CListCtrlPlayers.SetItemText(nItem, 1, TmpPlayers.drop);
		m_CListCtrlPlayers.SetItemText(nItem, 2, TmpPlayers.code);
	}
}

void CArmyDlg::InitArmyLists()
{
	// TODO: 在此添加控件通知处理程序代码
	struct ArmyDef TmpArmyDef;
	struct ArmyNameDef TmpArmyNameDef;
	CList <ArmyDef, ArmyDef&> *LCurArmyDef = &Common::LArmyDef;
	CList <ArmyNameDef, ArmyNameDef&> *LCurArmyNameDef = &Common::LArmyNameDef;
	int ret = 0;
	POSITION pos, pos2;

	m_CListCtrlArmys.DeleteAllItems();

	pos = LCurArmyDef->GetHeadPosition();
	for (int i=0;i < LCurArmyDef->GetCount();i++)
	{
		TmpArmyDef = LCurArmyDef->GetNext(pos);

		int nrow = m_CListCtrlArmys.GetItemCount();//取行数
		int nItem = m_CListCtrlArmys.InsertItem(nrow+1, _T(""));
		m_CListCtrlArmys.SetItemText(nItem, 0, TmpArmyDef.Code);
		m_CListCtrlArmys.SetItemText(nItem, 1, TmpArmyDef.Name);  // Name id

		pos2 = LCurArmyNameDef->GetHeadPosition();
		for (int j=0;j < LCurArmyNameDef->GetCount();j++)
		{
			TmpArmyNameDef = LCurArmyNameDef->GetNext(pos2);

			if(TmpArmyNameDef.ID == TmpArmyDef.Name)  // ID相同，除非设置出错，否则一定找得到
			{
				CString tempName = TmpArmyNameDef.Name;
				m_CListCtrlArmys.SetItemText(nItem, 2, _T(Common::Big2GB((LPSTR)(LPCTSTR)tempName)));
				break;
			}
		}


		m_CListCtrlArmys.SetItemText(nItem, 3, TmpArmyDef.reborn_delay);
		CString tempList = TmpArmyDef.list;
		tempList.Replace("role_", "");
		m_CListCtrlArmys.SetItemText(nItem, 4, _T(Common::Big2GB((LPSTR)(LPCTSTR)tempList)));
		m_CListCtrlArmys.SetItemText(nItem, 5, ConvertMapList(TmpArmyDef.map_list));
		m_CListCtrlArmys.SetItemText(nItem, 6, TmpArmyDef.list);
		m_CListCtrlArmys.SetItemText(nItem, 7, TmpArmyDef.map_list);
	}
}


void CArmyDlg::InitStageList()
{
	struct StageDef TmpStageDef;
	CList <StageDef, StageDef&> *LCurStageDef = &Common::LStageDef;
	int ret = 0;
	POSITION pos;

	m_CListCtrlStageDef.DeleteAllItems();

	//将获得的物品显示到ClistCtrl里去
	pos = LCurStageDef->GetHeadPosition();
	for (int i=0;i < LCurStageDef->GetCount();i++)
	{
		TmpStageDef = LCurStageDef->GetNext(pos);

		int nrow = m_CListCtrlStageDef.GetItemCount();//取行数
		int nItem = m_CListCtrlStageDef.InsertItem(nrow+1, _T(""));
		m_CListCtrlStageDef.SetItemText(nItem, 0, TmpStageDef.ID);
		CString tempName = TmpStageDef.Name;
		tempName.Replace("city_", "");
		m_CListCtrlStageDef.SetItemText(nItem, 1, _T(Common::Big2GB((LPSTR)(LPCTSTR)tempName)));
	}
}


CString CArmyDlg::ConvertMapList(CString MapList)
{
	CString strResult = "";

	struct StageDef TmpStageDef;
	CList <StageDef, StageDef&> *LCurStageDef = &Common::LStageDef;

	CString szLine = MapList;
	CStringArray strDest;
	CString strGap = ",";
	int nPos = szLine.Find(strGap);
	CString strLeft = _T("");
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

	for(int i = 0; i < strDest.GetCount();)
	{
		POSITION pos = LCurStageDef->GetHeadPosition();
		for (int j=0;j < LCurStageDef->GetCount();j++)
		{
			TmpStageDef = LCurStageDef->GetNext(pos);

			if(_ttoi(TmpStageDef.ID) == _ttoi(strDest[i]))  // ID相同，除非设置出错，否则一定找得到
			{
				CString tempName = TmpStageDef.Name;
				tempName.Replace("city_", "");
				tempName.Format("%s(%s,%d,%d) , ", Common::Big2GB((LPSTR)(LPCTSTR)tempName), strDest[i], _ttoi(strDest[i+1])/64, _ttoi(strDest[i+2])/64);

				strResult += tempName;
				break;
			}
		}
		i += 3;
	}

	return strResult;
}


void CArmyDlg::OnEnChangeEditFind()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	CString strKey;
	int iColumnNum,iRowCount;
	char chTemp[32];
	int ListIndex = 0;

	m_CEditFind.GetWindowText(strKey);
	if(strKey.IsEmpty()) return;

	iColumnNum = m_CListCtrlPlayers.GetHeaderCtrl()->GetItemCount();
	iRowCount = m_CListCtrlPlayers.GetItemCount();

	for (int j=0 ; j<iRowCount ; j++ )
	{
		memset(chTemp, 0 ,32);
		for ( int i=0 ; i<iColumnNum ; i++ )
		{
			m_CListCtrlPlayers.GetItemText(j,i,chTemp, 32);
			if(strstr(chTemp,strKey))
			{
				ListIndex = j;
				goto BreakLoop;
			}
		}
	}
BreakLoop:
	m_CListCtrlPlayers.SetFocus();  
	m_CListCtrlPlayers.SetItemState(ListIndex, LVIS_SELECTED, LVIS_SELECTED);
	m_CListCtrlPlayers.SetSelectionMark(ListIndex);
	m_CListCtrlPlayers.EnsureVisible(ListIndex, FALSE);
	::SendMessage(m_CListCtrlPlayers.m_hWnd,  LVM_SETEXTENDEDLISTVIEWSTYLE,  
		LVS_EX_FULLROWSELECT,  LVS_EX_FULLROWSELECT); 


	int i;
	struct DropsRange TmpDropsRange;
	CList <DropsRange, DropsRange&> *LCurDropsRange = &Common::LDropsRange;

	m_CListCtrlDrops.DeleteAllItems();

	ListIndex = m_CListCtrlPlayers.GetSelectionMark();
	if(ListIndex == -1) return;
	CString DropId = m_CListCtrlPlayers.GetItemText(ListIndex, 1);
	m_CEditName.SetWindowTextA( m_CListCtrlPlayers.GetItemText(ListIndex, 0));
	m_CEditDropId.SetWindowTextA(DropId);
	POSITION pos = LCurDropsRange->GetHeadPosition();
	for (i=0;i < LCurDropsRange->GetCount();i++)
	{
		TmpDropsRange = LCurDropsRange->GetNext(pos);
		if(TmpDropsRange.DropId == DropId)
			break;
	}

	if(i >= LCurDropsRange->GetCount())
	{
		AfxMessageBox("没有找到设定的爆率");
		return;
	}

	CString szLine = TmpDropsRange.DropRange;
	CStringArray strDest;
	CString strGap = ",";
	int nPos = szLine.Find(strGap);
	CString strLeft = _T("");
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

	int count = 0;
	for(int i = 0; i < strDest.GetCount();)
	{
		int nrow = m_CListCtrlDrops.GetItemCount();//取行数
		int nItem = m_CListCtrlDrops.InsertItem(nrow+1, _T(""));
		CString tempName = strDest[i++];
		tempName.Replace("item_", "");
		m_CListCtrlDrops.SetItemText(nItem, 0, _T(Common::Big2GB((LPSTR)(LPCTSTR)tempName)));
		CString temp12 = strDest[i++];
		count += _ttoi(temp12);
		m_CListCtrlDrops.SetItemText(nItem, 1, temp12);
		m_CListCtrlDrops.SetItemText(nItem, 2, tempName);
	}

	CString strTemp;
	strTemp.Format("%d", count);
	m_CEditCounter.SetWindowTextA(strTemp);

	m_CEditFind.SetFocus();
}


void CArmyDlg::OnBnClickedButtonPlayerNext()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strKey;
	int iColumnNum,iRowCount;
	char chTemp[32];
	int ListIndex = 0;
	int iCurListIndex  = m_CListCtrlPlayers.GetSelectionMark();

	m_CEditFind.GetWindowText(strKey);
	if(strKey.IsEmpty()) return;

	iColumnNum = m_CListCtrlPlayers.GetHeaderCtrl()->GetItemCount();
	iRowCount = m_CListCtrlPlayers.GetItemCount();

	int j = iCurListIndex + 1;
	do
	{
		memset(chTemp, 0 ,32);
		for ( int i=0 ; i<iColumnNum ; i++ )
		{
			m_CListCtrlPlayers.GetItemText(j,i,chTemp, 32);
			if(strstr(chTemp,strKey))
			{
				ListIndex = j;
				goto BreakLoop;
			}
		}
		if(j == iRowCount) 
			j = -1;
	}while(j != iCurListIndex && (j++ || j!=0));
BreakLoop:
	m_CListCtrlPlayers.SetFocus();  
	m_CListCtrlPlayers.SetItemState(ListIndex, LVIS_SELECTED, LVIS_SELECTED);
	m_CListCtrlPlayers.SetSelectionMark(ListIndex);
	m_CListCtrlPlayers.EnsureVisible(ListIndex, FALSE);
	::SendMessage(m_CListCtrlPlayers.m_hWnd,  LVM_SETEXTENDEDLISTVIEWSTYLE,  
		LVS_EX_FULLROWSELECT,  LVS_EX_FULLROWSELECT); 

	int i;
	struct DropsRange TmpDropsRange;
	CList <DropsRange, DropsRange&> *LCurDropsRange = &Common::LDropsRange;

	m_CListCtrlDrops.DeleteAllItems();

	ListIndex = m_CListCtrlPlayers.GetSelectionMark();
	if(ListIndex == -1) return;
	CString DropId = m_CListCtrlPlayers.GetItemText(ListIndex, 1);
	m_CEditName.SetWindowTextA( m_CListCtrlPlayers.GetItemText(ListIndex, 0));
	m_CEditDropId.SetWindowTextA(DropId);
	POSITION pos = LCurDropsRange->GetHeadPosition();
	for (i=0;i < LCurDropsRange->GetCount();i++)
	{
		TmpDropsRange = LCurDropsRange->GetNext(pos);
		if(TmpDropsRange.DropId == DropId)
			break;
	}

	if(i >= LCurDropsRange->GetCount())
	{
		AfxMessageBox("没有找到设定的爆率");
		return;
	}

	CString szLine = TmpDropsRange.DropRange;
	CStringArray strDest;
	CString strGap = ",";
	int nPos = szLine.Find(strGap);
	CString strLeft = _T("");
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

	int count = 0;
	for(int i = 0; i < strDest.GetCount();)
	{
		int nrow = m_CListCtrlDrops.GetItemCount();//取行数
		int nItem = m_CListCtrlDrops.InsertItem(nrow+1, _T(""));
		CString tempName = strDest[i++];
		tempName.Replace("item_", "");
		m_CListCtrlDrops.SetItemText(nItem, 0, _T(Common::Big2GB((LPSTR)(LPCTSTR)tempName)));
		CString temp12 = strDest[i++];
		count += _ttoi(temp12);
		m_CListCtrlDrops.SetItemText(nItem, 1, temp12);
		m_CListCtrlDrops.SetItemText(nItem, 2, tempName);
	}

	CString strTemp;
	strTemp.Format("%d", count);
	m_CEditCounter.SetWindowTextA(strTemp);
}


void CArmyDlg::OnNMClickListPlayers(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	int i;
	struct DropsRange TmpDropsRange;
	CList <DropsRange, DropsRange&> *LCurDropsRange = &Common::LDropsRange;

	m_CListCtrlDrops.DeleteAllItems();

	int ListIndex = m_CListCtrlPlayers.GetSelectionMark();
	if(ListIndex == -1) return;
	CString DropId = m_CListCtrlPlayers.GetItemText(ListIndex, 1);
	m_CEditName.SetWindowTextA(m_CListCtrlPlayers.GetItemText(ListIndex, 0));
	m_CEditBossName.SetWindowTextA(m_CListCtrlPlayers.GetItemText(ListIndex, 0));
	strCurSelBoss = m_CListCtrlPlayers.GetItemText(ListIndex, 2);  // 繁体
	m_CEditDropId.SetWindowTextA(DropId);
	POSITION pos = LCurDropsRange->GetHeadPosition();
	for (i=0;i < LCurDropsRange->GetCount();i++)
	{
		TmpDropsRange = LCurDropsRange->GetNext(pos);
		if(TmpDropsRange.DropId == DropId)
			break;
	}

	if(i >= LCurDropsRange->GetCount())
	{
		AfxMessageBox("没有找到设定的爆率");
		return;
	}

	CString szLine = TmpDropsRange.DropRange;
	CStringArray strDest;
	CString strGap = ",";
	int nPos = szLine.Find(strGap);
	CString strLeft = _T("");
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

	int count = 0;
	for(int i = 0; i < strDest.GetCount();)
	{
		int nrow = m_CListCtrlDrops.GetItemCount();//取行数
		int nItem = m_CListCtrlDrops.InsertItem(nrow+1, _T(""));
		CString tempName = strDest[i++];
		tempName.Replace("item_", "");
		m_CListCtrlDrops.SetItemText(nItem, 0, _T(Common::Big2GB((LPSTR)(LPCTSTR)tempName)));
		CString temp12 = strDest[i++];
		count += _ttoi(temp12);
		m_CListCtrlDrops.SetItemText(nItem, 1, temp12);
		m_CListCtrlDrops.SetItemText(nItem, 2, tempName);
	}

	CString strTemp;
	strTemp.Format("%d", count);
	m_CEditCounter.SetWindowTextA(strTemp);
}


void CArmyDlg::OnBnClickedButtonOutput()
{
	// TODO: 在此添加控件通知处理程序代码
	BOOL bMode = FALSE;  // TURE表示输出所以城市掉宝， FALSE 表示只输出开放地图掉宝
	int i, j;
	struct DropsRange TmpDropsRange;
	CList <DropsRange, DropsRange&> *LCurDropsRange = &Common::LDropsRange;
	struct StageDef TmpStageDef;
	CList <StageDef, StageDef&> *LCurStageDef = &Common::LStageDef;
	struct Players TmpPlayers;
	CList <Players, Players&> *LCurPlayers = &Common::LPlayers;

	POSITION pos, pos2;

	CStringArray strDest;
	CString szLine;
	CString strGap = ",";
	int nPos, len;
	CString strLeft = _T("");

	if (IDYES == AfxMessageBox("点击‘是’输出全部地图掉宝，点击‘否’输出开放地图掉宝" , MB_YESNO))
		bMode = TRUE;

	CString StrValue;
	CString strPathName="";
	::GetCurrentDirectory(1024,strPathName.GetBuffer(1024));
	strPathName.ReleaseBuffer();
	if(bMode)
		strPathName += "\\皇朝三国-Boss刷新、地图分布、掉宝（内部机密，严禁外传）-全.TXT";
	else
		strPathName += "\\皇朝三国-Boss刷新、地图分布、掉宝（内部机密，严禁外传）-开放.TXT";

	DWORD dwRe = GetFileAttributes(strPathName);
	if ( dwRe != (DWORD)-1 )
	{
		DeleteFile(strPathName);
	}

	//打开文件
	CStdioFile StdFile;
	StdFile.Open(strPathName,CFile::modeCreate | CFile::modeWrite | CFile::shareDenyNone);

	StdFile.WriteString("// 皇朝三国-Boss刷新、地图分布、掉宝（内部机密，严禁外传）\n");

	CString strStageName, strBossList, strDropItemList;
	CString strName, strDropId, strDropList;
	CString tempStageName, tempStageName2;
	CString strTemp;

	pos = LCurStageDef->GetHeadPosition();
	for (i=0;i < LCurStageDef->GetCount();i++)
	{
		strDest.RemoveAll();
		strStageName = "";
		strBossList = "";
		strDropItemList = "";

		TmpStageDef = LCurStageDef->GetNext(pos);

		strTemp.Format(",%d,", _ttoi(TmpStageDef.ID));
		if(!bMode && Common::strServerMapList.Find(strTemp) == -1)
			continue;

		tempStageName = TmpStageDef.Name;
		tempStageName.Replace("city_", "");
		tempStageName = Common::Big2GB((LPSTR)(LPCTSTR)tempStageName);
		strTemp.Format("%s(%d,", tempStageName, _ttoi(TmpStageDef.ID));

		int nrow = m_CListCtrlArmys.GetItemCount();//取行数
		for(j = 0; j < nrow; j++)
		{
			tempStageName2 = m_CListCtrlArmys.GetItemText(j, 5);

			if(tempStageName2.Find(strTemp) != -1)  // 找到了
			{
				strStageName = tempStageName;

				szLine = m_CListCtrlArmys.GetItemText(j, 4);
				nPos = szLine.Find(strGap);
				strLeft = _T("");
				while(0 <= nPos)
				{
					strLeft = szLine.Left(nPos);
					if(strBossList.Find(strLeft) == -1)
					{
						strBossList += strLeft + ",";
						strDest.Add(strLeft);
					}
					len = szLine.GetLength();
					szLine = szLine.Right(szLine.GetLength() - nPos - 1);
					nPos = szLine.Find(strGap);
				}

				if (!szLine.IsEmpty()) {
					if(strBossList.Find(szLine) == -1)
					{
						strBossList += szLine + ",";
						strDest.Add(szLine);
					}
				}				
			}
		}

		if(strStageName.IsEmpty())
			continue;

		StdFile.WriteString("【" + strStageName + "】\n\n");
		StdFile.WriteString(strBossList + "\n\n");

		// 根据boss列表输出本地图的掉落物品
		for(j = 0; j < strDest.GetCount();j++)
		{
			strDropId = "";
			pos2 = LCurPlayers->GetHeadPosition();
			for (int k=0;k < LCurPlayers->GetCount();k++)
			{
				TmpPlayers = LCurPlayers->GetNext(pos2);

				CString tempName = TmpPlayers.code;
				tempName.Replace("role_", "");
				tempName = Common::Big2GB((LPSTR)(LPCTSTR)tempName);
				if(tempName == strDest[j]) // 寻找对应boss的drop id
				{
					strDropId = TmpPlayers.drop;
					break;
				}
			}

			if(strDropId.IsEmpty())
				continue;

			// 获取掉落物品列表
			strDropList = "";
			pos2 = LCurDropsRange->GetHeadPosition();
			for (int k=0;k < LCurDropsRange->GetCount();k++)
			{
				TmpDropsRange = LCurDropsRange->GetNext(pos2);
				if(strDropId == TmpDropsRange.DropId)
				{
					if(TmpDropsRange.DropRange.IsEmpty())
						break;
					CString szLine = TmpDropsRange.DropRange;
					CStringArray strDest;
					CString strGap = ",";
					int nPos = szLine.Find(strGap);
					CString strLeft = _T("");
					BOOL bSkip = FALSE;
					int  len;
					while(0 <= nPos)
					{
						strLeft = szLine.Left(nPos);
						if(strLeft == "item_Nothing")  // 跳过 Nothing
						{
							bSkip = TRUE;
							len = szLine.GetLength();
							szLine = szLine.Right(szLine.GetLength() - nPos - 1);
							nPos = szLine.Find(strGap);
							continue;
						}
						if(bSkip)   // 跳过Nothing的爆率数
						{
							bSkip = FALSE;
							len = szLine.GetLength();
							szLine = szLine.Right(szLine.GetLength() - nPos - 1);
							nPos = szLine.Find(strGap);
							continue;
						}

						strDest.Add(strLeft);

						len = szLine.GetLength();
						szLine = szLine.Right(szLine.GetLength() - nPos - 1);
						nPos = szLine.Find(strGap);
					}

					if (!szLine.IsEmpty() && !bSkip) {
						strDest.Add(szLine);
					}

					if(strDest.GetCount() < 2)
						continue;

					CString Temp22 = "";
					int nCount = strDest.GetCount();
					CString strTemp = "";
					for(int l = nCount-1; l >=0;)
					{
						strTemp = strDest[l-1];					
						strTemp.Replace("item_", "");
						strTemp.Replace("Item_", "");
						if(strTemp == "Nothing")
						{
							l -= 2;
							continue;
						}

						if(l > 1)
						{
							if(strDropItemList.Find(Common::Big2GB((LPSTR)(LPCTSTR)strTemp)) == -1)
								Temp22 += Common::Big2GB((LPSTR)(LPCTSTR)strTemp) + "，";
						}
						else
						{
							if(strDropItemList.Find(Common::Big2GB((LPSTR)(LPCTSTR)strTemp)) == -1)
								Temp22 += Common::Big2GB((LPSTR)(LPCTSTR)strTemp);
						}
						l -= 2; 
					}
					strDropList = Temp22;
				}
			}

			if(strDropList.IsEmpty())
				continue;

			strDropItemList += strDropList + "，";
		}

		if(strDropItemList.IsEmpty())
			continue;

		StdFile.WriteString(strDropItemList + "\n\n");

	}

	StdFile.Close();
}


void CArmyDlg::OnBnClickedButtonAddOrg()
{
	// TODO: 在此添加控件通知处理程序代码
	int i;
	struct ArmyDef TmpArmyDef;
	CList <ArmyDef, ArmyDef&> *LCurArmyDef = &Common::LArmyDef;
	POSITION pos, tmpPos = NULL;
	CString strCode, strBossList, strMapList;

	m_CEditCode2.GetWindowTextA(strCode);
	pos = LCurArmyDef->GetHeadPosition();
	for (i=0;i < LCurArmyDef->GetCount();i++)
	{
		tmpPos = pos;
		TmpArmyDef = LCurArmyDef->GetNext(pos);

		if(_ttoi(strCode) < _ttoi(TmpArmyDef.Code))
		{
			TmpArmyDef.Code = strCode;
			m_CEditArmyNameId2.GetWindowTextA(TmpArmyDef.Name);
			m_CEditRebornDelay2.GetWindowTextA(TmpArmyDef.reborn_delay);
			m_CEditRebornRange2.GetWindowTextA(TmpArmyDef.reborn_range);
			m_CEditDisappearTime2.GetWindowTextA(TmpArmyDef.disappear_time);

			int nrow = m_CListCtrlBossList.GetItemCount();//取行数
			for(int j = 0; j < nrow; j++)
			{
				if(j == nrow -1)
					strBossList += m_CListCtrlBossList.GetItemText(j, 1);
				else
					strBossList += m_CListCtrlBossList.GetItemText(j, 1) + ",";
			}

			TmpArmyDef.list = strBossList;

			nrow = m_CListCtrlMapList.GetItemCount();//取行数
			for(int j = 0; j < nrow; j++)
			{
				if(j == nrow -1)
					strMapList += m_CListCtrlMapList.GetItemText(j, 0) + ","+ m_CListCtrlMapList.GetItemText(j, 1) +  "," + m_CListCtrlMapList.GetItemText(j, 2);
				else
					strMapList += m_CListCtrlMapList.GetItemText(j, 0) + ","+ m_CListCtrlMapList.GetItemText(j, 1) +  "," + m_CListCtrlMapList.GetItemText(j, 2) + ",";
			}
			TmpArmyDef.map_list = strMapList;

			LCurArmyDef->InsertBefore(tmpPos, TmpArmyDef);
			break;
		}		
	}
}


void CArmyDlg::OnBnClickedButtonArmySave()
{
	// TODO: 在此添加控件通知处理程序代码

	struct ArmyDef TmpArmyDef;
	CList <ArmyDef, ArmyDef&> *LCurArmyDef = &Common::LArmyDef;

	CString strPathName="", strDistPathName="";
	::GetCurrentDirectory(1024,strPathName.GetBuffer(1024));
	strPathName.ReleaseBuffer();
	strDistPathName = strPathName + CONFIG_FILE_PATH +"ARMY-BAK.TXT";
	strPathName += CONFIG_FILE_PATH;
	strPathName += "ARMY.TXT";

	if(!CopyFile(strPathName, strDistPathName, TRUE))
	{
		if (IDYES != AfxMessageBox("备份文件已经存在，是否继续？" , MB_YESNO))
		{
			return;
		}
		else
		{
			CopyFile(strPathName, strDistPathName, FALSE);
		}
	}

	//打开文件
	CStdioFile StdFile;
	StdFile.Open(strPathName,CFile::modeCreate | CFile::modeWrite | CFile::shareDenyNone);

	StdFile.WriteString(Common::GB2Big("// 敌人势力表"));
	StdFile.WriteString("\n");
	StdFile.WriteString("#include PLAYERS.H\n");
	StdFile.WriteString("\n\n");

	int i;
	CString strTemp;
	POSITION pos = LCurArmyDef->GetHeadPosition();
	for (i=0;i < LCurArmyDef->GetCount();i++)
	{
		TmpArmyDef = LCurArmyDef->GetNext(pos);
		StdFile.WriteString("[army]\n");
		strTemp = "code = " + TmpArmyDef.Code + "\n";
		StdFile.WriteString(strTemp);
		strTemp = "name = " + TmpArmyDef.Name + "\n";
		StdFile.WriteString(strTemp);
		strTemp = "reborn_delay = " + TmpArmyDef.reborn_delay + "\n";
		StdFile.WriteString(strTemp);
		strTemp = "reborn_range = " + TmpArmyDef.reborn_range + "\n";
		StdFile.WriteString(strTemp);
		strTemp = "disappear_time = " + TmpArmyDef.disappear_time + "\n";		
		StdFile.WriteString(strTemp);
		if(!TmpArmyDef.mission_boss.IsEmpty())
		{
			strTemp = "mission_boss = " + TmpArmyDef.mission_boss + "\n";
			StdFile.WriteString(strTemp);
		}
		strTemp = "list = " + TmpArmyDef.list + "\n";
		StdFile.WriteString(strTemp);

		CString szLine = TmpArmyDef.map_list;
		CStringArray strDest;
		CString strGap = ",";
		int nPos = szLine.Find(strGap);
		CString strLeft = _T("");
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

		for(int j = 0; j < strDest.GetCount();)
		{
			strTemp.Format("map = %s,%s,%s\n", strDest[j], strDest[j+1], strDest[j+2]);
			StdFile.WriteString(strTemp);
			j += 3;
		}

		strTemp = "map = " + TmpArmyDef.Code + "\n";
		StdFile.WriteString("\n");
	}
	StdFile.Close();
	AfxMessageBox("保存完成！");
}


void CArmyDlg::OnBnClickedButtonAuto()
{
	// TODO: 在此添加控件通知处理程序代码
	int i;
	struct ArmyDef TmpArmyDef;
	CList <ArmyDef, ArmyDef&> *LCurArmyDef = &Common::LArmyDef;
	POSITION pos, tmpPos = NULL;
	pos = LCurArmyDef->GetHeadPosition();
	for (i=0;i < LCurArmyDef->GetCount();i++)
	{
		tmpPos = pos;
		TmpArmyDef = LCurArmyDef->GetNext(pos);
		TmpArmyDef.Code.Format("%d", i+1);

		LCurArmyDef->SetAt(tmpPos, TmpArmyDef);
	}

	InitArmyLists();
}


void CArmyDlg::OnEnChangeEditArmyNameId2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	int i;
	struct ArmyNameDef TmpArmyNameDef;
	CList <ArmyNameDef, ArmyNameDef&> *LCurArmyNameDef = &Common::LArmyNameDef;

	CString strNameId;
	m_CEditArmyName2.SetWindowTextA("");
	m_CEditArmyNameId2.GetWindowTextA(strNameId);
	POSITION pos2 = LCurArmyNameDef->GetHeadPosition();
	for (i=0;i < LCurArmyNameDef->GetCount();i++)
	{
		TmpArmyNameDef = LCurArmyNameDef->GetNext(pos2);

		if(TmpArmyNameDef.ID == strNameId)  // ID相同，除非设置出错，否则一定找得到
		{
			CString tempName = TmpArmyNameDef.Name;
			m_CEditArmyName2.SetWindowTextA(_T(Common::Big2GB((LPSTR)(LPCTSTR)tempName)));
			break;
		}
	}
}


void CArmyDlg::OnNMClickArmyList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	int i, j, k;
	struct ArmyDef TmpArmyDef;
	CList <ArmyDef, ArmyDef&> *LCurArmyDef = &Common::LArmyDef;
	struct StageDef TmpStageDef;
	CList <StageDef, StageDef&> *LCurStageDef = &Common::LStageDef;

	POSITION pos, tmpPos = NULL;
	CString strCode;

	int ListIndex = m_CListCtrlArmys.GetSelectionMark();
	if(ListIndex == -1) return;

	CString szLine;
	CStringArray strDest;
	CString strGap = ",";
	int nPos, len;
	CString strLeft = _T("");

	strCode = m_CListCtrlArmys.GetItemText(ListIndex, 0);

	pos = LCurArmyDef->GetHeadPosition();
	for (i=0;i < LCurArmyDef->GetCount();i++)
	{
		TmpArmyDef = LCurArmyDef->GetNext(pos);
		
		if(TmpArmyDef.Code == strCode)
		{
			m_CEditCode.SetWindowTextA(TmpArmyDef.Code);
			m_CEditArmyNameId.SetWindowTextA(TmpArmyDef.Name);
			m_CEditRebornDelay.SetWindowTextA(TmpArmyDef.reborn_delay);
			m_CEditRebornRange.SetWindowTextA(TmpArmyDef.reborn_range);
			m_CEditDisappearTime.SetWindowTextA(TmpArmyDef.disappear_time);

			m_CEditCode2.SetWindowTextA(TmpArmyDef.Code);
			m_CEditArmyNameId2.SetWindowTextA(TmpArmyDef.Name);
			m_CEditRebornDelay2.SetWindowTextA(TmpArmyDef.reborn_delay);
			m_CEditRebornRange2.SetWindowTextA(TmpArmyDef.reborn_range);
			m_CEditDisappearTime2.SetWindowTextA(TmpArmyDef.disappear_time);

			// 设置地图列表
			m_CListCtrlMapList.DeleteAllItems();
			strDest.RemoveAll();
			szLine = TmpArmyDef.map_list;
			nPos = szLine.Find(strGap);
			while(0 <= nPos)
			{
				strLeft = szLine.Left(nPos);
				strDest.Add(strLeft);
				len = szLine.GetLength();
				szLine = szLine.Right(szLine.GetLength() - nPos - 1);
				nPos = szLine.Find(strGap);
			}

			if (!szLine.IsEmpty()) {
				strDest.Add(szLine);
			}
			
			for(k = 0; k < strDest.GetCount();)
			{
				POSITION pos = LCurStageDef->GetHeadPosition();
				for (j=0;j < LCurStageDef->GetCount();j++)
				{
					TmpStageDef = LCurStageDef->GetNext(pos);

					if(_ttoi(TmpStageDef.ID) == _ttoi(strDest[k]))  // ID相同，除非设置出错，否则一定找得到
					{
						int nrow = m_CListCtrlMapList.GetItemCount();//取行数
						int nItem = m_CListCtrlMapList.InsertItem(nrow+1, _T(""));
						m_CListCtrlMapList.SetItemText(nItem, 0, strDest[k]);
						m_CListCtrlMapList.SetItemText(nItem, 1, strDest[k+1]);
						m_CListCtrlMapList.SetItemText(nItem, 2, strDest[k+2]);
						CString tempName = TmpStageDef.Name;
						tempName.Replace("city_", "");
						m_CListCtrlMapList.SetItemText(nItem, 3, _T(Common::Big2GB((LPSTR)(LPCTSTR)tempName)));
						break;
					}
				}
				k += 3;
			}

			// 设置Boss列表
			m_CListCtrlBossList.DeleteAllItems();
			strDest.RemoveAll();
			szLine = TmpArmyDef.list;
			nPos = szLine.Find(strGap);
			while(0 <= nPos)
			{
				strLeft = szLine.Left(nPos);
				strDest.Add(strLeft);
				len = szLine.GetLength();
				szLine = szLine.Right(szLine.GetLength() - nPos - 1);
				nPos = szLine.Find(strGap);
			}

			if (!szLine.IsEmpty()) {
				strDest.Add(szLine);
			}

			for(k = 0; k < strDest.GetCount(); k++)
			{				
				int nrow = m_CListCtrlBossList.GetItemCount();//取行数
				int nItem = m_CListCtrlBossList.InsertItem(nrow+1, _T(""));
				CString tempName = strDest[k];
				tempName.Replace("role_", "");
				m_CListCtrlBossList.SetItemText(nItem, 0, _T(Common::Big2GB((LPSTR)(LPCTSTR)tempName)));
				m_CListCtrlBossList.SetItemText(nItem, 1, strDest[k]);
			}

			break;  // 跳出查找循环
		}
	}
}


void CArmyDlg::OnEnChangeEditArmyNameId()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	int i;
	struct ArmyNameDef TmpArmyNameDef;
	CList <ArmyNameDef, ArmyNameDef&> *LCurArmyNameDef = &Common::LArmyNameDef;

	CString strNameId;
	m_CEditArmyName.SetWindowTextA("");
	m_CEditArmyNameId.GetWindowTextA(strNameId);
	POSITION pos2 = LCurArmyNameDef->GetHeadPosition();
	for (i=0;i < LCurArmyNameDef->GetCount();i++)
	{
		TmpArmyNameDef = LCurArmyNameDef->GetNext(pos2);

		if(TmpArmyNameDef.ID == strNameId)  // ID相同，除非设置出错，否则一定找得到
		{
			CString tempName = TmpArmyNameDef.Name;
			m_CEditArmyName.SetWindowTextA(_T(Common::Big2GB((LPSTR)(LPCTSTR)tempName)));
			break;
		}
	}
}


void CArmyDlg::OnBnClickedButtonDelOrg()
{
	// TODO: 在此添加控件通知处理程序代码
	struct ArmyDef TmpArmyDef;
	CList <ArmyDef, ArmyDef&> *LCurArmyDef = &Common::LArmyDef;
	POSITION pos, tmpPos = NULL;
	CString strCode;

	int ListIndex  = m_CListCtrlDrops.GetSelectionMark();
	if(ListIndex == -1) return;

	strCode = m_CListCtrlArmys.GetItemText(ListIndex, 0);

	pos = LCurArmyDef->GetHeadPosition();
	for (int i=0;i < LCurArmyDef->GetCount();i++)
	{
		tmpPos = pos;
		TmpArmyDef = LCurArmyDef->GetNext(pos);

		if(TmpArmyDef.Code == strCode)
		{
			LCurArmyDef->RemoveAt(tmpPos);
			break;
		}
	}

	m_CListCtrlDrops.DeleteItem(ListIndex);//删除选中行

	OnBnClickedButtonAuto();
}


void CArmyDlg::OnEnChangeEditOrgFind()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码

	CString strKey;
	int iColumnNum;
	char chTemp[32];
	int ListIndex = 0;

	m_CEditOrgFind.GetWindowText(strKey);
	if(strKey.IsEmpty()) return;

	iColumnNum = m_CListCtrlArmys.GetHeaderCtrl()->GetItemCount();
	//iRowCount = m_CListCtrlArmys.GetItemCount();

	for (int j=0 ; j<5 ; j++ )
	{
		memset(chTemp, 0 ,32);
		for ( int i=0 ; i<iColumnNum ; i++ )
		{
			m_CListCtrlArmys.GetItemText(j,i,chTemp, 32);
			if(strstr(chTemp,strKey))
			{
				ListIndex = j;
				goto BreakLoop;
			}
		}
	}
BreakLoop:
	m_CListCtrlArmys.SetFocus();  
	m_CListCtrlArmys.SetItemState(ListIndex, LVIS_SELECTED, LVIS_SELECTED);
	m_CListCtrlArmys.SetSelectionMark(ListIndex);
	m_CListCtrlArmys.EnsureVisible(ListIndex, FALSE);
	::SendMessage(m_CListCtrlArmys.m_hWnd,  LVM_SETEXTENDEDLISTVIEWSTYLE,  
		LVS_EX_FULLROWSELECT,  LVS_EX_FULLROWSELECT); 

	m_CEditOrgFind.SetFocus();
}


void CArmyDlg::OnBnClickedButtonOrgNext()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strKey;
	int iColumnNum;
	char chTemp[32];
	int ListIndex = 0;
	int iCurListIndex  = m_CListCtrlArmys.GetSelectionMark();

	m_CEditOrgFind.GetWindowText(strKey);
	if(strKey.IsEmpty()) return;

	iColumnNum = m_CListCtrlArmys.GetHeaderCtrl()->GetItemCount();
	//iRowCount = m_CListCtrlArmys.GetItemCount();

	int j = iCurListIndex + 1;
	do
	{
		memset(chTemp, 0 ,32);
		for ( int i=0 ; i<iColumnNum ; i++ )
		{
			m_CListCtrlArmys.GetItemText(j,i,chTemp, 32);
			if(strstr(chTemp,strKey))
			{
				ListIndex = j;
				goto BreakLoop;
			}
		}
		if(j == 5) 
			j = -1;
	}while(j != iCurListIndex && (j++ || j!=0));
BreakLoop:
	m_CListCtrlArmys.SetFocus();  
	m_CListCtrlArmys.SetItemState(ListIndex, LVIS_SELECTED, LVIS_SELECTED);
	m_CListCtrlArmys.SetSelectionMark(ListIndex);
	m_CListCtrlArmys.EnsureVisible(ListIndex, FALSE);
	::SendMessage(m_CListCtrlArmys.m_hWnd,  LVM_SETEXTENDEDLISTVIEWSTYLE,  
		LVS_EX_FULLROWSELECT,  LVS_EX_FULLROWSELECT); 
}


void CArmyDlg::OnBnClickedButtonReflash()
{
	// TODO: 在此添加控件通知处理程序代码
	OnBnClickedButtonAuto();
}


void CArmyDlg::OnEnChangeEditStageFind()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码

	CString strKey;
	int iColumnNum,iRowCount;
	char chTemp[32];
	int ListIndex = 0;

	m_CEditStageFind.GetWindowText(strKey);
	if(strKey.IsEmpty()) return;

	iColumnNum = m_CListCtrlStageDef.GetHeaderCtrl()->GetItemCount();
	iRowCount = m_CListCtrlStageDef.GetItemCount();

	for (int j=0 ; j<iRowCount ; j++ )
	{
		memset(chTemp, 0 ,32);
		for ( int i=0 ; i<iColumnNum ; i++ )
		{
			m_CListCtrlStageDef.GetItemText(j,i,chTemp, 32);
			if(strstr(chTemp,strKey))
			{
				ListIndex = j;
				goto BreakLoop;
			}
		}
	}
BreakLoop:
	m_CListCtrlStageDef.SetFocus();  
	m_CListCtrlStageDef.SetItemState(ListIndex, LVIS_SELECTED, LVIS_SELECTED);
	m_CListCtrlStageDef.SetSelectionMark(ListIndex);
	m_CListCtrlStageDef.EnsureVisible(ListIndex, FALSE);
	::SendMessage(m_CListCtrlStageDef.m_hWnd,  LVM_SETEXTENDEDLISTVIEWSTYLE,  
		LVS_EX_FULLROWSELECT,  LVS_EX_FULLROWSELECT); 

	m_CEditStageFind.SetFocus();
}


void CArmyDlg::OnBnClickedButtonStageNext()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strKey;
	int iColumnNum,iRowCount;
	char chTemp[32];
	int ListIndex = 0;
	int iCurListIndex  = m_CListCtrlStageDef.GetSelectionMark();

	m_CEditStageFind.GetWindowText(strKey);
	if(strKey.IsEmpty()) return;

	iColumnNum = m_CListCtrlStageDef.GetHeaderCtrl()->GetItemCount();
	iRowCount = m_CListCtrlStageDef.GetItemCount();

	int j = iCurListIndex + 1;
	do
	{
		memset(chTemp, 0 ,32);
		for ( int i=0 ; i<iColumnNum ; i++ )
		{
			m_CListCtrlStageDef.GetItemText(j,i,chTemp, 32);
			if(strstr(chTemp,strKey))
			{
				ListIndex = j;
				goto BreakLoop;
			}
		}
		if(j == iRowCount) 
			j = -1;
	}while(j != iCurListIndex && (j++ || j!=0));
BreakLoop:
	m_CListCtrlStageDef.SetFocus();  
	m_CListCtrlStageDef.SetItemState(ListIndex, LVIS_SELECTED, LVIS_SELECTED);
	m_CListCtrlStageDef.SetSelectionMark(ListIndex);
	m_CListCtrlStageDef.EnsureVisible(ListIndex, FALSE);
	::SendMessage(m_CListCtrlStageDef.m_hWnd,  LVM_SETEXTENDEDLISTVIEWSTYLE,  
		LVS_EX_FULLROWSELECT,  LVS_EX_FULLROWSELECT); 
}


void CArmyDlg::OnNMClickListStagedef(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	int ListIndex = m_CListCtrlStageDef.GetSelectionMark();
	if(ListIndex == -1) return;

	m_CEditMapId.SetWindowTextA(m_CListCtrlStageDef.GetItemText(ListIndex, 0));
}


void CArmyDlg::OnEnChangeEditMapId()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	struct StageDef TmpStageDef;
	CList <StageDef, StageDef&> *LCurStageDef = &Common::LStageDef;

	CString strMapId;
	m_CEditMapId.GetWindowTextA(strMapId);

	POSITION pos = LCurStageDef->GetHeadPosition();
	for (int i=0;i < LCurStageDef->GetCount();i++)
	{
		TmpStageDef = LCurStageDef->GetNext(pos);

		if(strMapId == TmpStageDef.ID)
		{
			CString tempName = TmpStageDef.Name;
			tempName.Replace("city_", "");
			m_CEditMapName.SetWindowTextA(Common::Big2GB((LPSTR)(LPCTSTR)tempName));
			break;
		}
	}
}


void CArmyDlg::OnBnClickedButtonAddMap()
{
	// TODO: 在此添加控件通知处理程序代码
	int nrow = m_CListCtrlMapList.GetItemCount();//取行数
	int nItem = m_CListCtrlMapList.InsertItem(nrow+1, _T(""));
	CString strValue;
	m_CEditMapId.GetWindowTextA(strValue);
	m_CListCtrlMapList.SetItemText(nItem, 0, strValue);
	m_CEditMapX.GetWindowTextA(strValue);
	m_CListCtrlMapList.SetItemText(nItem, 1, strValue);
	m_CEditMapY.GetWindowTextA(strValue);
	m_CListCtrlMapList.SetItemText(nItem, 2, strValue);
	m_CEditMapName.GetWindowTextA(strValue);
	m_CListCtrlMapList.SetItemText(nItem, 3, strValue);
}


void CArmyDlg::OnBnClickedButtonDelMap2()
{
	// TODO: 在此添加控件通知处理程序代码
	int ListIndex  = m_CListCtrlMapList.GetSelectionMark();
	if(ListIndex == -1) return;
	m_CListCtrlMapList.DeleteItem(ListIndex);//删除选中行
}


void CArmyDlg::OnBnClickedButtonAddBoss()
{
	// TODO: 在此添加控件通知处理程序代码
	int nrow = m_CListCtrlBossList.GetItemCount();//取行数
	int nItem = m_CListCtrlBossList.InsertItem(nrow+1, _T(""));
	CString strValue;
	m_CEditBossName.GetWindowTextA(strValue);
	m_CListCtrlBossList.SetItemText(nItem, 0, strValue);
	m_CListCtrlBossList.SetItemText(nItem, 1, strCurSelBoss);
}


void CArmyDlg::OnBnClickedButtonDelBoss()
{
	// TODO: 在此添加控件通知处理程序代码
	int ListIndex  = m_CListCtrlBossList.GetSelectionMark();
	if(ListIndex == -1) return;
	m_CListCtrlBossList.DeleteItem(ListIndex);//删除选中行
}


void CArmyDlg::OnBnClickedButtonSync()
{
	// TODO: 在此添加控件通知处理程序代码

	int i;
	struct ArmyDef TmpArmyDef;
	CList <ArmyDef, ArmyDef&> *LCurArmyDef = &Common::LArmyDef;
	POSITION pos, tmpPos = NULL;
	CString strCode, strBossList, strMapList;

	m_CEditCode2.GetWindowTextA(strCode);
	pos = LCurArmyDef->GetHeadPosition();
	for (i=0;i < LCurArmyDef->GetCount();i++)
	{
		tmpPos = pos;
		TmpArmyDef = LCurArmyDef->GetNext(pos);

		if(_ttoi(strCode) == _ttoi(TmpArmyDef.Code))
		{
			TmpArmyDef.Code = strCode;
			m_CEditArmyNameId.GetWindowTextA(TmpArmyDef.Name);
			m_CEditRebornDelay.GetWindowTextA(TmpArmyDef.reborn_delay);
			m_CEditRebornRange.GetWindowTextA(TmpArmyDef.reborn_range);
			m_CEditDisappearTime.GetWindowTextA(TmpArmyDef.disappear_time);

			int nrow = m_CListCtrlBossList.GetItemCount();//取行数
			for(int j = 0; j < nrow; j++)
			{
				if(j == nrow -1)
					strBossList += m_CListCtrlBossList.GetItemText(j, 1);
				else
					strBossList += m_CListCtrlBossList.GetItemText(j, 1) + ",";
			}

			TmpArmyDef.list = strBossList;

			nrow = m_CListCtrlMapList.GetItemCount();//取行数
			for(int j = 0; j < nrow; j++)
			{
				if(j == nrow -1)
					strMapList += m_CListCtrlMapList.GetItemText(j, 0) + ","+ m_CListCtrlMapList.GetItemText(j, 1) +  "," + m_CListCtrlMapList.GetItemText(j, 2);
				else
					strMapList += m_CListCtrlMapList.GetItemText(j, 0) + ","+ m_CListCtrlMapList.GetItemText(j, 1) +  "," + m_CListCtrlMapList.GetItemText(j, 2) + ",";
			}
			TmpArmyDef.map_list = strMapList;

			LCurArmyDef->SetAt(tmpPos, TmpArmyDef);
			break;
		}		
	}

	OnBnClickedButtonAuto();
}
