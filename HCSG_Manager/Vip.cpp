// Vip.cpp : 实现文件
//

#include "stdafx.h"
#include "HCSG_Manager.h"
#include "HCSG_ManagerDlg.h"
#include "Vip.h"
#include "afxdialogex.h"


// CVip 对话框

IMPLEMENT_DYNAMIC(CVip, CDialogEx)

	CVip::CVip(CWnd* pParent /*=NULL*/)
	: CDialogEx(CVip::IDD, pParent)
{

}

CVip::~CVip()
{
}

void CVip::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_ACCOUNT, m_CListCtrlAccount);
	DDX_Control(pDX, IDC_LIST_VIP_ACC, m_CListCtrlVipAcc);
	DDX_Control(pDX, IDC_EDIT_ACC, m_CEditAcc);
	DDX_Control(pDX, IDC_COMBO_MODE, m_CComboBoxMode);
	DDX_Control(pDX, IDC_EDIT_POINT, m_CEditPoint);
	DDX_Control(pDX, IDC_EDIT_NOTE, m_CEditNote);
	DDX_Control(pDX, IDC_EDIT_POINT_1, m_CEditPoint1);
	DDX_Control(pDX, IDC_EDIT_NOTE_1, m_CEditNote1);
	DDX_Control(pDX, IDC_COMBO_VIP_CONFIG, m_CComboBoxVipConfig);
	DDX_Control(pDX, IDC_EDIT_VIP_POINT, m_CEditVipPoint);
	DDX_Control(pDX, IDC_EDIT_VIP_ACC, m_CEditVipAcc);
	DDX_Control(pDX, IDC_COMBO_VIP, m_CComboBoxVip);
	DDX_Control(pDX, IDC_STATIC_ACC_TOTAL, m_CStaticAccTotal);
	DDX_Control(pDX, IDC_EDIT_POINTS, m_CEditPoints);
	DDX_Control(pDX, IDC_EDIT_VIP_DATE, m_CEditVipDate);
	DDX_Control(pDX, IDC_LIST_ITEM, m_CListCtrlItem);
	DDX_Control(pDX, IDC_EDIT_VIP_ITEM_ID, m_CEditVipItemId[0]);
	DDX_Control(pDX, IDC_EDIT_VIP_ITEM_ID2, m_CEditVipItemId[1]);
	DDX_Control(pDX, IDC_EDIT_VIP_ITEM_ID3, m_CEditVipItemId[2]);
	DDX_Control(pDX, IDC_EDIT_VIP_ITEM_ID4, m_CEditVipItemId[3]);
	DDX_Control(pDX, IDC_EDIT_VIP_ITEM_ID5, m_CEditVipItemId[4]);
	DDX_Control(pDX, IDC_EDIT_VIP_ITEM_ID6, m_CEditVipItemId[5]);
	DDX_Control(pDX, IDC_EDIT_VIP_ITEM_ID7, m_CEditVipItemId[6]);
	DDX_Control(pDX, IDC_EDIT_VIP_ITEM_ID8, m_CEditVipItemId[7]);
	DDX_Control(pDX, IDC_EDIT_VIP_ITEM_ID9, m_CEditVipItemId[8]);
	DDX_Control(pDX, IDC_EDIT_VIP_ITEM_ID10, m_CEditVipItemId[9]);
	DDX_Control(pDX, IDC_EDIT_VIP_ITEM_NAME, m_CEditVipItemName[0]);
	DDX_Control(pDX, IDC_EDIT_VIP_ITEM_NAME2, m_CEditVipItemName[1]);
	DDX_Control(pDX, IDC_EDIT_VIP_ITEM_NAME3, m_CEditVipItemName[2]);
	DDX_Control(pDX, IDC_EDIT_VIP_ITEM_NAME4, m_CEditVipItemName[3]);
	DDX_Control(pDX, IDC_EDIT_VIP_ITEM_NAME5, m_CEditVipItemName[4]);
	DDX_Control(pDX, IDC_EDIT_VIP_ITEM_NAME6, m_CEditVipItemName[5]);
	DDX_Control(pDX, IDC_EDIT_VIP_ITEM_NAME7, m_CEditVipItemName[6]);
	DDX_Control(pDX, IDC_EDIT_VIP_ITEM_NAME8, m_CEditVipItemName[7]);
	DDX_Control(pDX, IDC_EDIT_VIP_ITEM_NAME9, m_CEditVipItemName[8]);
	DDX_Control(pDX, IDC_EDIT_VIP_ITEM_NAME10, m_CEditVipItemName[9]);
	DDX_Control(pDX, IDC_EDIT_VIP_ITEM_NUM, m_CEditVipItemNum[0]);
	DDX_Control(pDX, IDC_EDIT_VIP_ITEM_NUM2, m_CEditVipItemNum[1]);
	DDX_Control(pDX, IDC_EDIT_VIP_ITEM_NUM3, m_CEditVipItemNum[2]);
	DDX_Control(pDX, IDC_EDIT_VIP_ITEM_NUM4, m_CEditVipItemNum[3]);
	DDX_Control(pDX, IDC_EDIT_VIP_ITEM_NUM5, m_CEditVipItemNum[4]);
	DDX_Control(pDX, IDC_EDIT_VIP_ITEM_NUM6, m_CEditVipItemNum[5]);
	DDX_Control(pDX, IDC_EDIT_VIP_ITEM_NUM7, m_CEditVipItemNum[6]);
	DDX_Control(pDX, IDC_EDIT_VIP_ITEM_NUM8, m_CEditVipItemNum[7]);
	DDX_Control(pDX, IDC_EDIT_VIP_ITEM_NUM9, m_CEditVipItemNum[8]);
	DDX_Control(pDX, IDC_EDIT_VIP_ITEM_NUM10, m_CEditVipItemNum[9]);
	DDX_Control(pDX, IDC_EDIT_FIND_ITEM, m_CEditFindItem);
	DDX_Control(pDX, IDC_EDIT_FIND_ACC, m_CEditFindAcc);
	DDX_Control(pDX, IDC_STATIC_TIME, m_CStaticCopyRight);
}


BEGIN_MESSAGE_MAP(CVip, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE, &CVip::OnBnClickedButtonUpdate)
	ON_CBN_SELCHANGE(IDC_COMBO_VIP_CONFIG, &CVip::OnCbnSelchangeComboVipConfig)
	ON_BN_CLICKED(ID_SAVE, &CVip::OnBnClickedSave)
	ON_NOTIFY(NM_CLICK, IDC_LIST_ACCOUNT, &CVip::OnNMClickListAccount)
	ON_CBN_SELCHANGE(IDC_COMBO_MODE, &CVip::OnCbnSelchangeComboMode)
	ON_BN_CLICKED(ID_SEND, &CVip::OnBnClickedSend)
	ON_BN_CLICKED(ID_ADD_VIP, &CVip::OnBnClickedAddVip)
	ON_BN_CLICKED(ID_DELETE_VIP, &CVip::OnBnClickedDeleteVip)
	ON_WM_TIMER()
	ON_EN_CHANGE(IDC_EDIT_ACC, &CVip::OnEnChangeEditAcc)
	ON_EN_CHANGE(IDC_EDIT_VIP_ITEM_ID, &CVip::OnEnChangeEditVipItemId)
	ON_EN_CHANGE(IDC_EDIT_VIP_ITEM_ID2, &CVip::OnEnChangeEditVipItemId2)
	ON_EN_CHANGE(IDC_EDIT_VIP_ITEM_ID3, &CVip::OnEnChangeEditVipItemId3)
	ON_EN_CHANGE(IDC_EDIT_VIP_ITEM_ID4, &CVip::OnEnChangeEditVipItemId4)
	ON_EN_CHANGE(IDC_EDIT_VIP_ITEM_ID5, &CVip::OnEnChangeEditVipItemId5)
	ON_EN_CHANGE(IDC_EDIT_VIP_ITEM_ID6, &CVip::OnEnChangeEditVipItemId6)
	ON_EN_CHANGE(IDC_EDIT_VIP_ITEM_ID7, &CVip::OnEnChangeEditVipItemId7)
	ON_EN_CHANGE(IDC_EDIT_VIP_ITEM_ID8, &CVip::OnEnChangeEditVipItemId8)
	ON_EN_CHANGE(IDC_EDIT_VIP_ITEM_ID9, &CVip::OnEnChangeEditVipItemId9)
	ON_EN_CHANGE(IDC_EDIT_VIP_ITEM_ID10, &CVip::OnEnChangeEditVipItemId10)
	ON_NOTIFY(NM_CLICK, IDC_LIST_ITEM, &CVip::OnNMClickListItem)
	ON_BN_CLICKED(IDC_BUTTON_FIND_ITEM, &CVip::OnBnClickedButtonFindItem)
	ON_BN_CLICKED(IDC_BUTTON_FIND_NEXT_ITEM, &CVip::OnBnClickedButtonFindNextItem)
	ON_EN_CHANGE(IDC_EDIT_FIND_ACC, &CVip::OnEnChangeEditFindAcc)
	ON_BN_CLICKED(IDC_BUTTON_FIND_NEXT_ACC, &CVip::OnBnClickedButtonFindNextAcc)
	ON_EN_CHANGE(IDC_EDIT_FIND_ITEM, &CVip::OnEnChangeEditFindItem)
END_MESSAGE_MAP()


// CVip 消息处理程序


BOOL CVip::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	m_CListCtrlVipAcc.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP);
	m_CListCtrlVipAcc.InsertColumn(0, _T("帐号"), LVCFMT_LEFT, 60);
	m_CListCtrlVipAcc.InsertColumn(1, _T("级别"), LVCFMT_LEFT, 60);//插入列
	m_CListCtrlVipAcc.InsertColumn(2, _T("天数"), LVCFMT_LEFT, 60);//插入列
	m_CListCtrlVipAcc.InsertColumn(3, _T("代币"), LVCFMT_LEFT, 60);//插入列
	for(int i=4; i<4+10; i++)
	{
		CString strKey = "";
		strKey.Format("物品%d", i-3);
		m_CListCtrlVipAcc.InsertColumn(i, strKey, LVCFMT_LEFT, 80);//插入列
	}

// 	m_CListCtrlVipAcc.InsertColumn(4, _T("物品一"), LVCFMT_LEFT, 80);//插入列
// 	m_CListCtrlVipAcc.InsertColumn(5, _T("物品二"), LVCFMT_LEFT, 80);//插入列
// 	m_CListCtrlVipAcc.InsertColumn(6, _T("物品三"), LVCFMT_LEFT, 80);//插入列
// 	m_CListCtrlVipAcc.InsertColumn(7, _T("物品四"), LVCFMT_LEFT, 80);//插入列
// 	m_CListCtrlVipAcc.InsertColumn(8, _T("物品五"), LVCFMT_LEFT, 80);//插入列

	m_CListCtrlAccount.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP);
	m_CListCtrlAccount.InsertColumn(0, _T("注册帐号"), LVCFMT_LEFT, 95);
	m_CListCtrlAccount.InsertColumn(1, _T("角色名称"), LVCFMT_LEFT, 95);
	m_CListCtrlAccount.InsertColumn(2, _T("封号"), LVCFMT_LEFT, 50);//插入列
	m_CListCtrlAccount.InsertColumn(3, _T("权限"), LVCFMT_LEFT, 50);//插入列
	m_CListCtrlAccount.InsertColumn(4, _T("代币点"), LVCFMT_LEFT, 70);
	m_CListCtrlAccount.InsertColumn(5, _T("登录IP"), LVCFMT_LEFT, 80);

	m_CListCtrlItem.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP);
	m_CListCtrlItem.InsertColumn(0, _T("ID"), LVCFMT_LEFT, 50);//插入列
	m_CListCtrlItem.InsertColumn(1, _T("物品名称"), LVCFMT_LEFT, 100);

	m_CComboBoxMode.SetCurSel(0);
	nMode = 0;

	m_CEditPoint.SetWindowText("1000");
	m_CEditPoint1.SetWindowText("0");

	m_CEditNote.SetWindowText("1");
	m_CEditNote1.SetWindowText("0");

	for(int i=1; i<=VIP_LEVEL; i++)
	{
		CString strKey = "";
		strKey.Format("VIP-%d", i);
		m_CComboBoxVip.AddString(strKey);
		m_CComboBoxVipConfig.AddString(strKey);
	}

	m_CComboBoxVip.SetCurSel(0);
	m_CComboBoxVipConfig.SetCurSel(0);

	ReadVipList();

	OnCbnSelchangeComboVipConfig();

	UpdataAcc();

	OnCbnSelchangeComboMode();
	
	InitItemDef();

	CTime CurTime = CTime::GetCurrentTime();
	int y=CurTime.GetYear(); //获取年份
	int m=CurTime.GetMonth(); //获取当前月份
	int d=CurTime.GetDay(); //获得几号
	int h=CurTime.GetHour(); //获取当前为几时
	int mm=CurTime.GetMinute(); //获取分钟

	CString strCurSystemTime;
	strCurSystemTime.Format("%02d:%02d", h, mm);

	Common::Log(Info, "设定VIP发放时间为00:05");
	int  tmp_h = h, tmp_mm = 5;
	if(mm >= 5) 
		tmp_h += 1;

	CTime WarStartTime(y, m, d, tmp_h, tmp_mm, 0);
	CTimeSpan DelayTime = WarStartTime - CurTime;
	SetTimer(TIMER1, (UINT)DelayTime.GetTotalSeconds() * 1000, 0);

	m_CEditVipDate.SetWindowText("7");

	m_CStaticCopyRight.SetTextColor(RGB(255,0,0));

	return TRUE;  // return TRUE unless you set the focus to a control
}


void CVip::ReadVipList()
{
	CString des="";
	CString StrValue;
	int nVipNum = 0;
	CString strAccount, strVipType, strDate, strPoints;
	CString Key;
	CString temp;
	CString strItemTemp;
	CStringArray strItems;
	int nItem = 0;

	m_CListCtrlVipAcc.DeleteAllItems();
	::GetCurrentDirectory(1024,des.GetBuffer(1024));
	des.ReleaseBuffer();
	des += CONFIG_FILE_PATH;
	des += VIP_CONFIG_FILE;

	WaitForSingleObject(Common::hMutex,INFINITE);  // 互斥量
	GetPrivateProfileString("VIPLIST","NUM","",StrValue.GetBuffer(128),128,des);
	nVipNum = _ttoi(StrValue);
	StrValue.ReleaseBuffer();

	for(int i=1; i<=VIP_LEVEL; i++)
	{
		CString strKey = "";
		strKey.Format("VIP%d", i);
		GetPrivateProfileString("VIPAWARDE", strKey, Common::convert(i * 100), StrValue.GetBuffer(512), 512, des);
		Common::VipAwardsPoints.Add(StrValue);
		StrValue.ReleaseBuffer();
	}
	ReleaseMutex(Common::hMutex);

	for(int i=0;i < nVipNum;i++)
	{
		CStringArray tempArray;
		Key.Format("VIP-%d", i);
		WaitForSingleObject(Common::hMutex,INFINITE);  // 互斥量
		GetPrivateProfileString("VIPLIST",Key,"",StrValue.GetBuffer(128),128,des);
		ReleaseMutex(Common::hMutex);
		temp = StrValue;
		StrValue.ReleaseBuffer();

		if(temp.IsEmpty()) 
			continue;

		Common::CStringGap(temp, &tempArray,"","#");
		strAccount = tempArray[0];
		strVipType = tempArray[1];
		strDate = tempArray[2];

		//确定VIP配置
		//char num = strVipType.GetAt(4);
		CString num = strVipType.Right(strVipType.GetLength() - strlen("VIP-"));
		int index = _ttoi(num) - 1;
		CStringArray strTemp; 
		Common::CStringGap(Common::VipAwardsPoints[index],&strTemp,"","#");
		strPoints = strTemp[0];
		strItems.RemoveAll();
		if(strTemp.GetCount() >= 4)
		{
			strItemTemp = strTemp[2] + "x" + strTemp[3];
			strItems.Add(strItemTemp);
		}
		if(strTemp.GetCount() >= 7)
		{
			strItemTemp = strTemp[5] + "x" + strTemp[6];
			strItems.Add(strItemTemp);
		}
		if(strTemp.GetCount() >= 10)
		{
			strItemTemp = strTemp[8] + "x" + strTemp[9];
			strItems.Add(strItemTemp);
		}
		if(strTemp.GetCount() >= 13)
		{
			strItemTemp = strTemp[11] + "x" + strTemp[12];
			strItems.Add(strItemTemp);
		}
		if(strTemp.GetCount() >= 16)
		{
			strItemTemp = strTemp[14] + "x" + strTemp[15];
			strItems.Add(strItemTemp);
		}
		if(strTemp.GetCount() >= 19)
		{
			strItemTemp = strTemp[17] + "x" + strTemp[18];
			strItems.Add(strItemTemp);
		}
		if(strTemp.GetCount() >= 22)
		{
			strItemTemp = strTemp[20] + "x" + strTemp[21];
			strItems.Add(strItemTemp);
		}
		if(strTemp.GetCount() >= 25)
		{
			strItemTemp = strTemp[23] + "x" + strTemp[24];
			strItems.Add(strItemTemp);
		}
		if(strTemp.GetCount() >= 28)
		{
			strItemTemp = strTemp[26] + "x" + strTemp[27];
			strItems.Add(strItemTemp);
		}
		if(strTemp.GetCount() >= 31)
		{
			strItemTemp = strTemp[29] + "x" + strTemp[30];
			strItems.Add(strItemTemp);
		}

		m_CListCtrlVipAcc.InsertItem(nItem, _T(""));
		m_CListCtrlVipAcc.SetItemText(nItem, 0, strAccount);
		m_CListCtrlVipAcc.SetItemText(nItem, 1, strVipType);
		m_CListCtrlVipAcc.SetItemText(nItem, 2, strDate);
		m_CListCtrlVipAcc.SetItemText(nItem, 3, strPoints);
		for(int j=0; j < strItems.GetCount(); j++)
			m_CListCtrlVipAcc.SetItemText(nItem, 4+j, strItems[j]);

		nItem++;
	}
}


void CVip::InitItemDef()
{
	// TODO: 在此添加控件通知处理程序代码
	struct ItemDef TmpItemDef;
	CList <ItemDef, ItemDef&> *LCurItemDef = &Common::LItemDef;
	int ret = 0;
	POSITION pos;

	m_CListCtrlItem.DeleteAllItems();

	//将获得的物品显示到ClistCtrl里去
	pos = LCurItemDef->GetHeadPosition();
	for (int i=0;i < LCurItemDef->GetCount();i++)
	{
		TmpItemDef = LCurItemDef->GetNext(pos);

		int nrow = m_CListCtrlItem.GetItemCount();//取行数
		int nItem = m_CListCtrlItem.InsertItem(nrow+1, _T(""));
		m_CListCtrlItem.SetItemText(nItem, 0, _T(TmpItemDef.ID));
		CString tempName = TmpItemDef.Name;
		tempName.Replace("item_", "");
		m_CListCtrlItem.SetItemText(nItem, 1, _T(Common::Big2GB((LPSTR)(LPCTSTR)tempName)));
	}
}


void CVip::UpdataAcc()
{
	POSITION pos, pos2;
	struct AccAttr TmpAccAttr;
	CList <AccAttr, AccAttr&> *LCurAccAttr = &Common::LAccAttr;
	CList <GameAcc, GameAcc&> *LCurGameAcc = &Common::LGameAcc;
	m_CListCtrlAccount.DeleteAllItems();

	pos = LCurGameAcc->GetHeadPosition();
	for(int i=0;i < LCurGameAcc->GetCount();i++)
	{
		GameAcc TmpGameAcc = LCurGameAcc->GetNext(pos);
		CString AccountID = TmpGameAcc.account;

		int nrow = m_CListCtrlAccount.GetItemCount();//取行数
		int nItem = m_CListCtrlAccount.InsertItem(nrow+1, _T(""));
		m_CListCtrlAccount.SetItemText(nItem, 0, AccountID);

		pos2 = LCurAccAttr->GetHeadPosition();
		for (int j=0;j < LCurAccAttr->GetCount();j++)
		{
			TmpAccAttr = LCurAccAttr->GetNext(pos2);
			if(0 == strcmp(TmpAccAttr.Account, AccountID))
				m_CListCtrlAccount.SetItemText(nItem, 1, _T(Common::Big2GB(TmpAccAttr.Name)));
		}

		m_CListCtrlAccount.SetItemText(nItem, 2, TmpGameAcc.enable);
		m_CListCtrlAccount.SetItemText(nItem, 3, TmpGameAcc.privilege);
		m_CListCtrlAccount.SetItemText(nItem, 4, TmpGameAcc.point);
		m_CListCtrlAccount.SetItemText(nItem, 5, TmpGameAcc.ip);
	}

	m_CStaticAccTotal.SetWindowText(Common::convert(m_CListCtrlAccount.GetItemCount()));
}


void CVip::OnBnClickedButtonUpdate()
{
	// TODO: 在此添加控件通知处理程序代码
	Common::GetGameAccFormDB();
	Common::GetAccAttr();
	UpdataAcc();
}


void CVip::OnCbnSelchangeComboVipConfig()
{
	// TODO: 在此添加控件通知处理程序代码
	int nIndex = m_CComboBoxVipConfig.GetCurSel();

	//确定VIP配置
	CStringArray strTemp; 
	Common::CStringGap(Common::VipAwardsPoints[nIndex],&strTemp,"","#");
	m_CEditVipPoint.SetWindowText(strTemp[0]);

	for (int i = 0; i < VIP_ITEM_NUM; i++)
	{
		m_CEditVipItemId[i].SetWindowText("");
		m_CEditVipItemName[i].SetWindowText("");
		m_CEditVipItemNum[i].SetWindowText("");
	}

	for (int i = 1; i < strTemp.GetCount(); i += 3)
	{
		int n = (int)((i-1) / 3);
		if (strTemp.GetCount() >= (n * 3 + 4))
		{
			m_CEditVipItemId[n].SetWindowText(strTemp[i]);
			m_CEditVipItemName[n].SetWindowText(strTemp[i+1]);
			m_CEditVipItemNum[n].SetWindowText(strTemp[i+2]);
		}
	}
}


void CVip::OnBnClickedSave()
{
	// TODO: 在此添加控件通知处理程序代码
	struct ItemDef TmpItemDef;
	CList <ItemDef, ItemDef&> *LCurItemDef = &Common::LItemDef;
	POSITION pos;
	int j;

	int nIndex = m_CComboBoxVipConfig.GetCurSel();
	CString VipAwardsTemp;
	CString strPoint;
	CString strItemId[10], strItemName[10], strItemNum[10];
	m_CEditVipPoint.GetWindowText(strPoint);
	if (strPoint.IsEmpty())  strPoint = "0";

	for (int i = 0; i < VIP_ITEM_NUM; i++)
	{
		m_CEditVipItemId[i].GetWindowText(strItemId[i]);
		m_CEditVipItemName[i].GetWindowText(strItemName[i]);
		m_CEditVipItemNum[i].GetWindowText(strItemNum[i]);
		if (strItemId[i].IsEmpty()) { strItemName[i] = ""; strItemNum[i] = ""; }
	}

	VipAwardsTemp = strPoint;

	//确认物品是否存在
	for (int i = 0; i < VIP_ITEM_NUM; i++)
	{
		if (!strItemId[i].IsEmpty())
		{
			CString strItemIdTemp = strItemId[i];
			CString strItemNameTemp = strItemName[i];
			CString strItemNumTemp = strItemNum[i];

			pos = LCurItemDef->GetHeadPosition();
			for (j = 0; j < LCurItemDef->GetCount(); j++)
			{
				TmpItemDef = LCurItemDef->GetNext(pos);

				CString tempName = TmpItemDef.Name;
				tempName.Replace("item_", "");

				if (strItemIdTemp == TmpItemDef.ID && strItemNameTemp == Common::Big2GB((LPSTR)(LPCTSTR)tempName))
					break;
			}

			if (j >= LCurItemDef->GetCount())
			{
				AfxMessageBox("设定的物品不存在，无法保存配置");
				return;
			}

			if (!strItemNumTemp.IsEmpty() && _ttoi(strItemNumTemp) > 0)
			{
				VipAwardsTemp += "#" + strItemIdTemp + "#" + strItemNameTemp + "#" + strItemNumTemp;
			}
		}

	}

	Common::VipAwardsPoints[nIndex] = VipAwardsTemp;
	//Common::SaveConfig();

	CString des = "";
	::GetCurrentDirectory(1024, des.GetBuffer(1024));
	des.ReleaseBuffer();
	des += CONFIG_FILE_PATH;
	des += VIP_CONFIG_FILE;

	for (int i = 1; i <= VIP_LEVEL; i++)
	{
		CString strKey = "";
		strKey.Format("VIP%d", i);
		WritePrivateProfileString("VIPAWARDE", strKey, Common::VipAwardsPoints[i - 1], des);
	}

	// 刷新VIP列表配置
	ReadVipList();
}


void CVip::OnNMClickListAccount(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	int ListIndex = m_CListCtrlAccount.GetSelectionMark();
	if(ListIndex == -1) return;
	m_CEditAcc.SetWindowText(m_CListCtrlAccount.GetItemText(ListIndex, 0));
	m_CEditPoints.SetWindowText(m_CListCtrlAccount.GetItemText(ListIndex, 4));
	m_CEditVipAcc.SetWindowText(m_CListCtrlAccount.GetItemText(ListIndex, 0));
}


void CVip::OnCbnSelchangeComboMode()
{
	// TODO: 在此添加控件通知处理程序代码
	int nIndex = m_CComboBoxMode.GetCurSel();
	if(0 == nIndex)
	{
		m_CEditPoint.SetReadOnly(FALSE);
		m_CEditPoint1.SetReadOnly(FALSE);
		m_CEditNote.SetReadOnly(TRUE);
		m_CEditNote1.SetReadOnly(TRUE);
		nMode = 0;
	}
	else if (1 == nIndex)
	{
		m_CEditNote.SetReadOnly(FALSE);
		m_CEditNote1.SetReadOnly(FALSE);
		m_CEditPoint.SetReadOnly(TRUE);
		m_CEditPoint1.SetReadOnly(TRUE);
		nMode = 1;
	}
}


void CVip::OnBnClickedSend()
{
	// TODO: 在此添加控件通知处理程序代码
	int i;
	POSITION pos;
	CList <GameAcc, GameAcc&> *LCurGameAcc = &Common::LGameAcc;
	CString strAccount;
	m_CEditAcc.GetWindowText(strAccount);
	// 确认帐号是否存在
	pos = LCurGameAcc->GetHeadPosition();
	for(i=0;i < LCurGameAcc->GetCount();i++)
	{
		GameAcc TmpGameAcc = LCurGameAcc->GetNext(pos);
		CString AccountID = TmpGameAcc.account;

		if(AccountID == strAccount)
		{
			break;
		}
	}
	if(i >= LCurGameAcc->GetCount())
	{
		AfxMessageBox("帐号不存在，无法充值！");
		return;
	}

	if(0 == nMode)
	{
		if(Common::m_pConnection == NULL)
		{
			Common::Log(Info, "数据库未连接");
			return;
		}

		CString strPoint, strPoint1, AccCurPoints;
		int nTotalPoints = 0, nAddPoints = 0;
		m_CEditPoint.GetWindowText(strPoint);
		m_CEditPoint1.GetWindowText(strPoint1);
		nTotalPoints = _ttoi(strPoint) + _ttoi(strPoint1);
		nAddPoints = nTotalPoints;

		if(nTotalPoints <= 0)
			return;

		CString tmp22;
		tmp22.Format("是否向%s发放%d三国代币？", strAccount, nAddPoints);
		if (IDYES != AfxMessageBox(tmp22 , MB_YESNO))
			return;

		m_CEditPoints.GetWindowText(AccCurPoints);
		nTotalPoints += _ttoi(AccCurPoints);

		if(Common::AddPoints(nAddPoints, strAccount, "手动发放") == "转商城代币成功")
		{
			tmp22.Format("向%s发放%d三国代币成功，请注意查收！", strAccount, nTotalPoints);
			Common::Log(Info, tmp22);
			AfxMessageBox(tmp22);			
		}
		else
		{
			Common::Log(Error, "代币发放失败");
			AfxMessageBox("代币发放失败");
			return;
		}

		m_CEditPoints.SetWindowText(Common::convert(nTotalPoints));
		Common::GetGameAccFormDB();
		// UpdataAcc();  // 账户多了之后刷新很慢，所以不每次刷新了
	}
	else if(1 == nMode)
	{
		if(Common::m_pConnXb == NULL)
		{
			Common::Log(Info, "数据库未连接");
			return;
		}

		CString strNote, strNote1;
		int nTotalNote = 0;
		m_CEditNote.GetWindowText(strNote);
		m_CEditNote1.GetWindowText(strNote1);
		nTotalNote = _ttoi(strNote) + _ttoi(strNote1);

		if(nTotalNote <= 0)
			return;

		CString tmp22;
		tmp22.Format("是否向%s发放%d张银票？", strAccount, nTotalNote);
		if (IDYES != AfxMessageBox(tmp22, MB_YESNO) )
			return;
		CStringArray ItemList;
		ItemList.Add("5090");
		ItemList.Add(Common::convert(nTotalNote));
		if(!Common::SendXubao(strAccount, &ItemList))
		{
			Common::Log(Error, "发放银票失败");
			AfxMessageBox("发放银票失败");
			return;
		}
		else
		{
			tmp22.Format("向%s发放%d张银票成功，请通知去大鸿胪处领取！", strAccount, nTotalNote);
			Common::Log(Info, tmp22);
			AfxMessageBox(tmp22);
		}
	}
}


void CVip::OnBnClickedAddVip()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strAccount, strVipType, strDate, strPoints;
	CString strItemTemp;
	CStringArray strItems;
	BOOL bFound = FALSE;
	int i,j;
	m_CComboBoxVip.GetWindowText(strVipType);
	m_CEditVipAcc.GetWindowTextA(strAccount);
	m_CEditVipDate.GetWindowText(strDate);

	if(strAccount.IsEmpty())
		return;

	//确定VIP配置
	//char num = strVipType.GetAt(4);
	CString num = strVipType.Right(strVipType.GetLength() - strlen("VIP-"));
	int index = _ttoi(num) - 1;
	CStringArray strTemp; 
	Common::CStringGap(Common::VipAwardsPoints[index],&strTemp,"","#");
	strPoints = strTemp[0];
	strItems.RemoveAll();
	if(strTemp.GetCount() >= 4)
	{
		strItemTemp = strTemp[2] + "x" + strTemp[3];
		strItems.Add(strItemTemp);
	}
	if(strTemp.GetCount() >= 7)
	{
		strItemTemp = strTemp[5] + "x" + strTemp[6];
		strItems.Add(strItemTemp);
	}
	if(strTemp.GetCount() >= 10)
	{
		strItemTemp = strTemp[8] + "x" + strTemp[9];
		strItems.Add(strItemTemp);
	}
	if(strTemp.GetCount() >= 13)
	{
		strItemTemp = strTemp[11] + "x" + strTemp[12];
		strItems.Add(strItemTemp);
	}
	if(strTemp.GetCount() >= 16)
	{
		strItemTemp = strTemp[14] + "x" + strTemp[15];
		strItems.Add(strItemTemp);
	}
	if(strTemp.GetCount() >= 19)
	{
		strItemTemp = strTemp[17] + "x" + strTemp[18];
		strItems.Add(strItemTemp);
	}
	if(strTemp.GetCount() >= 22)
	{
		strItemTemp = strTemp[20] + "x" + strTemp[21];
		strItems.Add(strItemTemp);
	}
	if(strTemp.GetCount() >= 25)
	{
		strItemTemp = strTemp[23] + "x" + strTemp[24];
		strItems.Add(strItemTemp);
	}
	if(strTemp.GetCount() >= 28)
	{
		strItemTemp = strTemp[26] + "x" + strTemp[27];
		strItems.Add(strItemTemp);
	}
	if(strTemp.GetCount() >= 31)
	{
		strItemTemp = strTemp[29] + "x" + strTemp[30];
		strItems.Add(strItemTemp);
	}

	int nrow = m_CListCtrlVipAcc.GetItemCount();//取行数
	for(i=0; i< nrow; i++)
	{
		CString temp;
		temp = m_CListCtrlVipAcc.GetItemText(i, 0);
		if(strAccount.Compare(temp) == 0)
		{
			bFound = TRUE;
			break;
		}
	}
	if(bFound)
	{
		m_CListCtrlVipAcc.SetItemText(i, 1, strVipType);
		m_CListCtrlVipAcc.SetItemText(i, 2, strDate);
		m_CListCtrlVipAcc.SetItemText(i, 3, strPoints);
		for(j=0; j < strItems.GetCount(); j++)
			m_CListCtrlVipAcc.SetItemText(i, 4+j, strItems[j]);
	}
	else
	{
		int nItem = m_CListCtrlVipAcc.InsertItem(nrow+1, _T(""));

		m_CListCtrlVipAcc.SetItemText(nItem, 0, strAccount);
		m_CListCtrlVipAcc.SetItemText(nItem, 1, strVipType);
		m_CListCtrlVipAcc.SetItemText(nItem, 2, strDate);
		m_CListCtrlVipAcc.SetItemText(nItem, 3, strPoints);
		for(j=0; j < strItems.GetCount(); j++)
			m_CListCtrlVipAcc.SetItemText(nItem, 4+j, strItems[j]);
	}

	CString Key;
	CString StrValue;
	CString des="";
	::GetCurrentDirectory(1024,des.GetBuffer(1024));
	des.ReleaseBuffer();
	des += CONFIG_FILE_PATH;
	des += CONFIG_FILE;
	nrow = m_CListCtrlVipAcc.GetItemCount();//取行数
	WaitForSingleObject(Common::hMutex,INFINITE);  // 互斥量
	WritePrivateProfileString("VIPLIST","NUM",Common::convert(nrow),des);
	ReleaseMutex(Common::hMutex);
	for(i=0; i< nrow; i++)
	{
		strAccount = m_CListCtrlVipAcc.GetItemText(i, 0);
		strVipType = m_CListCtrlVipAcc.GetItemText(i, 1);
		strDate = m_CListCtrlVipAcc.GetItemText(i, 2);
		Key.Format("VIP-%d", i);
		StrValue = strAccount + "#" + strVipType + "#" + strDate;
		WaitForSingleObject(Common::hMutex,INFINITE);  // 互斥量
		WritePrivateProfileString("VIPLIST",Key,StrValue,des);
		ReleaseMutex(Common::hMutex);
	}

	// 刷新VIP列表配置
	ReadVipList();
}


void CVip::OnBnClickedDeleteVip()
{
	// TODO: 在此添加控件通知处理程序代码
	int ListIndex  = m_CListCtrlVipAcc.GetSelectionMark();
	if(ListIndex == -1) return;
	m_CListCtrlVipAcc.DeleteItem(ListIndex);//删除选中行

	CString strAccount, strVipType, strDate, strPoints;
	CString Key;
	CString StrValue;
	int i;
	CString des="";
	::GetCurrentDirectory(1024,des.GetBuffer(1024));
	des.ReleaseBuffer();
	des += CONFIG_FILE_PATH;
	des += CONFIG_FILE;
	int nrow = m_CListCtrlVipAcc.GetItemCount();//取行数
	WaitForSingleObject(Common::hMutex,INFINITE);  // 互斥量
	WritePrivateProfileString("VIPLIST","NUM",Common::convert(nrow),des);
	ReleaseMutex(Common::hMutex);
	for(i=0; i< nrow; i++)
	{
		strAccount = m_CListCtrlVipAcc.GetItemText(i, 0);
		strVipType = m_CListCtrlVipAcc.GetItemText(i, 1);
		strDate = m_CListCtrlVipAcc.GetItemText(i, 2);
		Key.Format("VIP-%d", i);
		StrValue = strAccount + "#" + strVipType + "#" + strDate;
		WaitForSingleObject(Common::hMutex,INFINITE);  // 互斥量
		WritePrivateProfileString("VIPLIST",Key,StrValue,des);
		ReleaseMutex(Common::hMutex);
	}

	Key.Format("VIP-%d", i);  //delete VIP
	StrValue = "";
	WaitForSingleObject(Common::hMutex,INFINITE);  // 互斥量
	WritePrivateProfileString("VIPLIST",Key,StrValue,des);
	ReleaseMutex(Common::hMutex);
}


void CVip::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch(nIDEvent){
	case TIMER1:
		{
			KillTimer(TIMER1);
			SetTimer(TIMER1, 60*60*1000, 0); // 每1个小时检测是否需要发放奖励
			//SetTimer(TIMER1, 30*1000, 0); // for test
			CTime CurTime = CTime::GetCurrentTime();
			int h=CurTime.GetHour(); //获取当前为几时

			if(0 == h)  // 零点发放VIP代币
				SendPointToVip();
			break;
		}
	default:
		break;
	}

	CDialogEx::OnTimer(nIDEvent);
}


void CVip::SendPointToVip()
{
	int i, j;
	CString strInsert;
	CString SQLInSertCmd;
	_variant_t strValue;
	CString strAccount, strVipType, strDate, strPoints, AccCurPoints, strItemName;
	int nTotalPoints = 0, nSendPoint = 0;
	_variant_t RecordsAffected;
	POSITION pos;
	CList <GameAcc, GameAcc&> *LCurGameAcc = &Common::LGameAcc;
	CStringArray strItems;

	if(!Common::LicenseDecodeAndCheck())
	{
		exit(-1);
	}

	Common::Log(Info, "开始发放VIP代币和物品！");

	CString Key;
	CString StrValue;
	CString des="";
	::GetCurrentDirectory(1024,des.GetBuffer(1024));
	des.ReleaseBuffer();
	des += CONFIG_FILE_PATH;
	des += CONFIG_FILE;

	int nrow = m_CListCtrlVipAcc.GetItemCount();//取行数
	for(i=0; i< nrow; i++)
	{
		strAccount = m_CListCtrlVipAcc.GetItemText(i, 0);
		// 确认帐号是否存在
		pos = LCurGameAcc->GetHeadPosition();
		for(j=0;j < LCurGameAcc->GetCount();j++)
		{
			GameAcc TmpGameAcc = LCurGameAcc->GetNext(pos);
			CString AccountID = TmpGameAcc.account;
			if(AccountID == strAccount)
			{
				break;
			}
		}
		if(j >= LCurGameAcc->GetCount())
		{
			Common::Log(Error, "帐号不存在，无法发放！ID: " + strAccount);
			continue;
		}

		strVipType = m_CListCtrlVipAcc.GetItemText(i, 1);
		strDate = m_CListCtrlVipAcc.GetItemText(i, 2);
		strPoints = m_CListCtrlVipAcc.GetItemText(i, 3);
		strItemName = m_CListCtrlVipAcc.GetItemText(i, 4);

		if(_ttoi(strDate) <= 0) continue;

		//确定VIP配置
		//char num = strVipType.GetAt(4);
		CString num = strVipType.Right(strVipType.GetLength() - strlen("VIP-"));
		int index = _ttoi(num) - 1;
		CStringArray strTemp; 
		Common::CStringGap(Common::VipAwardsPoints[index],&strTemp,"","#");
		nSendPoint = _ttoi(strTemp[0]);  //获得需要发放的点数
		strItems.RemoveAll();
		if(strTemp.GetCount() >= 4)
		{
			strItems.Add(strTemp[1]);
			strItems.Add(strTemp[3]);
		}
		if(strTemp.GetCount() >= 7)
		{
			strItems.Add(strTemp[4]);
			strItems.Add(strTemp[6]);
		}
		if(strTemp.GetCount() >= 10)
		{
			strItems.Add(strTemp[7]);
			strItems.Add(strTemp[9]);
		}
		if(strTemp.GetCount() >= 13)
		{
			strItems.Add(strTemp[10]);
			strItems.Add(strTemp[12]);
		}
		if(strTemp.GetCount() >= 16)
		{
			strItems.Add(strTemp[13]);
			strItems.Add(strTemp[15]);
		}
		if(strTemp.GetCount() >= 19)
		{
			strItems.Add(strTemp[16]);
			strItems.Add(strTemp[18]);
		}
		if(strTemp.GetCount() >= 22)
		{
			strItems.Add(strTemp[19]);
			strItems.Add(strTemp[21]);
		}
		if(strTemp.GetCount() >= 25)
		{
			strItems.Add(strTemp[22]);
			strItems.Add(strTemp[24]);
		}
		if(strTemp.GetCount() >= 28)
		{
			strItems.Add(strTemp[25]);
			strItems.Add(strTemp[27]);
		}
		if(strTemp.GetCount() >= 31)
		{
			strItems.Add(strTemp[28]);
			strItems.Add(strTemp[30]);
		}
		if(nSendPoint > 0)
		{
			if(Common::m_pConnection == NULL)
			{
				Common::Log(Info, "数据库未连接");
				return;
			}

			if(Common::AddPoints(nSendPoint, strAccount, "VIP用户发放") == "转商城代币成功")
			{
				CString tmp22;
				tmp22.Format("向%s发放%d代币成功！", strAccount, nSendPoint);
				Common::Log(Info, tmp22);
			}
			else
			{				
				Common::Log(Error, "VIP代币发放失败");
				continue;
			}
		}
		if(strItems.GetCount() > 0)
		{
			if(Common::m_pConnXb == NULL)
			{
				Common::Log(Info, "数据库未连接");
				return;
			}

			CStringArray ItemList;
			for(j=0; j < strItems.GetCount();)
			{
				ItemList.Add(strItems[j++]);   // 添加ID号
				ItemList.Add(strItems[j++]);   // 添加数量
			}			
			if(!Common::SendXubao(strAccount, &ItemList))
			{
				Common::Log(Error, "发放VIP物品失败");
				continue;
			}
			else
			{
				CString tmp22;
				tmp22.Format("向%s发放VIP物品成功，请通知去大鸿胪处领取！", strAccount);
				Common::Log(Info, tmp22);
			}
		}
		
		CString tt;
		tt.Format("%d", _ttoi(strDate) - 1);
		m_CListCtrlVipAcc.SetItemText(i, 2, tt);

		Key.Format("VIP-%d", i);
		StrValue = strAccount + "#" + strVipType + "#" + tt;
		WaitForSingleObject(Common::hMutex,INFINITE);  // 互斥量
		WritePrivateProfileString("VIPLIST",Key,StrValue,des);
		ReleaseMutex(Common::hMutex);
	}

	nrow = m_CListCtrlVipAcc.GetItemCount();//取行数
	for(i=nrow-1; i>=0; i--)
	{
		strDate = m_CListCtrlVipAcc.GetItemText(i, 2);
		if(strDate == "0")
		{
			m_CListCtrlVipAcc.DeleteItem(i);
			Key.Format("VIP-%d", i);
			StrValue = "";
			WaitForSingleObject(Common::hMutex,INFINITE);  // 互斥量
			WritePrivateProfileString("VIPLIST",Key,StrValue,des);	
			ReleaseMutex(Common::hMutex);
			m_CListCtrlVipAcc.DeleteItem(i);
		}
	}

	ReadVipList();

	nrow = m_CListCtrlVipAcc.GetItemCount();//取行数
	WaitForSingleObject(Common::hMutex,INFINITE);  // 互斥量
	WritePrivateProfileString("VIPLIST","NUM",Common::convert(nrow),des);
	ReleaseMutex(Common::hMutex);
	m_CListCtrlVipAcc.DeleteItem(i);
	for(i=0; i< nrow; i++)
	{
		strAccount = m_CListCtrlVipAcc.GetItemText(i, 0);
		strVipType = m_CListCtrlVipAcc.GetItemText(i, 1);
		strDate = m_CListCtrlVipAcc.GetItemText(i, 2);
		strPoints = m_CListCtrlVipAcc.GetItemText(i, 3);
		strItemName = m_CListCtrlVipAcc.GetItemText(i, 4);
		Key.Format("VIP-%d", i);
		StrValue = strAccount + "#" + strVipType + "#" + strDate;
		WaitForSingleObject(Common::hMutex,INFINITE);  // 互斥量
		WritePrivateProfileString("VIPLIST",Key,StrValue,des);
		ReleaseMutex(Common::hMutex);
	}
	OnBnClickedButtonUpdate();
	OnEnChangeEditAcc();

	Common::Log(Info, "发放VIP代币和物品结束！");
}


void CVip::OnEnChangeEditAcc()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	int i;
	POSITION pos;
	CList <GameAcc, GameAcc&> *LCurGameAcc = &Common::LGameAcc;
	CString strEnter;

	m_CEditAcc.GetWindowText(strEnter);

	pos = LCurGameAcc->GetHeadPosition();
	for(i=0;i < LCurGameAcc->GetCount();i++)
	{
		GameAcc TmpGameAcc = LCurGameAcc->GetNext(pos);
		CString AccountID = TmpGameAcc.account;

		if(AccountID == strEnter)
		{
			m_CEditPoints.SetWindowText(TmpGameAcc.point);
			break;
		}
	}
	if(i >= LCurGameAcc->GetCount())
	{
		m_CEditPoints.SetWindowText("0");
	}
}

void CVip::DoOnEnChangeEditItemId(int nIndex)
{
	struct ItemDef TmpItemDef;
	CList <ItemDef, ItemDef&> *LCurItemDef = &Common::LItemDef;
	POSITION pos;
	int i;

	CString strItemId;
	m_CEditVipItemId[nIndex].GetWindowText(strItemId);

	//确认物品是否存在
	if (!strItemId.IsEmpty())
	{
		pos = LCurItemDef->GetHeadPosition();
		for (i = 0; i < LCurItemDef->GetCount(); i++)
		{
			TmpItemDef = LCurItemDef->GetNext(pos);

			if (strItemId == TmpItemDef.ID)
			{
				CString tempName = TmpItemDef.Name;
				tempName.Replace("item_", "");

				m_CEditVipItemName[nIndex].SetWindowText(Common::Big2GB((LPSTR)(LPCTSTR)tempName));
				break;
			}
		}

		if (i >= LCurItemDef->GetCount())
		{
			m_CEditVipItemName[nIndex].SetWindowText("");
		}
	}
	else
	{
		m_CEditVipItemName[nIndex].SetWindowText("");
	}
}


void CVip::OnEnChangeEditVipItemId()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	DoOnEnChangeEditItemId(0);
}


void CVip::OnEnChangeEditVipItemId2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	DoOnEnChangeEditItemId(1);
}


void CVip::OnEnChangeEditVipItemId3()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	DoOnEnChangeEditItemId(2);
}


void CVip::OnEnChangeEditVipItemId4()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	DoOnEnChangeEditItemId(3);
}


void CVip::OnEnChangeEditVipItemId5()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	DoOnEnChangeEditItemId(4);
}

void CVip::OnEnChangeEditVipItemId6()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	DoOnEnChangeEditItemId(5);
}

void CVip::OnEnChangeEditVipItemId7()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	DoOnEnChangeEditItemId(6);
}

void CVip::OnEnChangeEditVipItemId8()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	DoOnEnChangeEditItemId(7);
}

void CVip::OnEnChangeEditVipItemId9()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	DoOnEnChangeEditItemId(8);
}

void CVip::OnEnChangeEditVipItemId10()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	DoOnEnChangeEditItemId(9);
}


void CVip::OnNMClickListItem(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	CString strValue;

	int ListIndex = m_CListCtrlItem.GetSelectionMark();
	if(ListIndex == -1) return;

	for (int i = 0; i < VIP_ITEM_NUM; i++)
	{ 
		m_CEditVipItemId[i].GetWindowText(strValue);
		if (strValue.IsEmpty())
		{
			m_CEditVipItemId[i].SetWindowText(m_CListCtrlItem.GetItemText(ListIndex, 0));
			return;
		}
	}
}


void CVip::OnBnClickedButtonFindItem()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strKey;
	int iColumnNum,iRowCount;
	char chTemp[32];
	int ListIndex = 0;

	m_CEditFindItem.GetWindowText(strKey);
	if(strKey.IsEmpty()) return;

	iColumnNum = m_CListCtrlItem.GetHeaderCtrl()->GetItemCount();
	iRowCount = m_CListCtrlItem.GetItemCount();

	for (int j=0 ; j<iRowCount ; j++ )
	{
		memset(chTemp, 0 ,32);
		for ( int i=0 ; i<iColumnNum ; i++ )
		{
			m_CListCtrlItem.GetItemText(j,i,chTemp, 32);
			if(strstr(chTemp,strKey))
			{
				ListIndex = j;
				goto BreakLoop;
			}
		}
	}
BreakLoop:
	m_CListCtrlItem.SetFocus();  
	m_CListCtrlItem.SetItemState(ListIndex, LVIS_SELECTED, LVIS_SELECTED);
	m_CListCtrlItem.SetSelectionMark(ListIndex);
	m_CListCtrlItem.EnsureVisible(ListIndex, FALSE);
	::SendMessage(m_CListCtrlItem.m_hWnd,  LVM_SETEXTENDEDLISTVIEWSTYLE,  
		LVS_EX_FULLROWSELECT,  LVS_EX_FULLROWSELECT);  
}


void CVip::OnBnClickedButtonFindNextItem()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strKey;
	int iColumnNum,iRowCount;
	char chTemp[32];
	int ListIndex = 0;
	int iCurListIndex  = m_CListCtrlItem.GetSelectionMark();

	m_CEditFindItem.GetWindowText(strKey);
	if(strKey.IsEmpty()) return;

	iColumnNum = m_CListCtrlItem.GetHeaderCtrl()->GetItemCount();
	iRowCount = m_CListCtrlItem.GetItemCount();

	int j = iCurListIndex + 1;
	do
	{
		memset(chTemp, 0 ,32);
		for ( int i=0 ; i<iColumnNum ; i++ )
		{
			m_CListCtrlItem.GetItemText(j,i,chTemp, 32);
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
	m_CListCtrlItem.SetFocus();  
	m_CListCtrlItem.SetItemState(ListIndex, LVIS_SELECTED, LVIS_SELECTED);
	m_CListCtrlItem.SetSelectionMark(ListIndex);
	m_CListCtrlItem.EnsureVisible(ListIndex, FALSE);
	::SendMessage(m_CListCtrlItem.m_hWnd,  LVM_SETEXTENDEDLISTVIEWSTYLE,  
		LVS_EX_FULLROWSELECT,  LVS_EX_FULLROWSELECT);  
}


void CVip::OnEnChangeEditFindAcc()
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

	m_CEditFindAcc.GetWindowText(strKey);
	if(strKey.IsEmpty()) return;

	iColumnNum = m_CListCtrlAccount.GetHeaderCtrl()->GetItemCount();
	iRowCount = m_CListCtrlAccount.GetItemCount();

	for (int j=0 ; j<iRowCount ; j++ )
	{
		memset(chTemp, 0 ,32);
		for ( int i=0 ; i<iColumnNum ; i++ )
		{
			m_CListCtrlAccount.GetItemText(j,i,chTemp, 32);
			if(strstr(chTemp,strKey))
			{
				ListIndex = j;
				goto BreakLoop;
			}
		}
	}
BreakLoop:
	m_CListCtrlAccount.SetFocus();  
	m_CListCtrlAccount.SetItemState(ListIndex, LVIS_SELECTED, LVIS_SELECTED);
	m_CListCtrlAccount.SetSelectionMark(ListIndex);
	m_CListCtrlAccount.EnsureVisible(ListIndex, FALSE);
	::SendMessage(m_CListCtrlAccount.m_hWnd,  LVM_SETEXTENDEDLISTVIEWSTYLE,  
		LVS_EX_FULLROWSELECT,  LVS_EX_FULLROWSELECT); 

	m_CEditFindAcc.SetFocus();
}


void CVip::OnBnClickedButtonFindNextAcc()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strKey;
	int iColumnNum,iRowCount;
	char chTemp[32];
	int ListIndex = 0;
	int iCurListIndex  = m_CListCtrlAccount.GetSelectionMark();

	m_CEditFindAcc.GetWindowText(strKey);
	if(strKey.IsEmpty()) return;

	iColumnNum = m_CListCtrlAccount.GetHeaderCtrl()->GetItemCount();
	iRowCount = m_CListCtrlAccount.GetItemCount();

	int j = iCurListIndex + 1;
	do
	{
		memset(chTemp, 0 ,32);
		for ( int i=0 ; i<2 ; i++ )  // 只查找账户名和角色名
		{
			m_CListCtrlAccount.GetItemText(j,i,chTemp, 32);
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
	m_CListCtrlAccount.SetFocus();  
	m_CListCtrlAccount.SetItemState(ListIndex, LVIS_SELECTED, LVIS_SELECTED);
	m_CListCtrlAccount.SetSelectionMark(ListIndex);
	m_CListCtrlAccount.EnsureVisible(ListIndex, FALSE);
	::SendMessage(m_CListCtrlAccount.m_hWnd,  LVM_SETEXTENDEDLISTVIEWSTYLE,  
		LVS_EX_FULLROWSELECT,  LVS_EX_FULLROWSELECT); 
}


void CVip::OnEnChangeEditFindItem()
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

	m_CEditFindItem.GetWindowText(strKey);
	if(strKey.IsEmpty()) return;

	iColumnNum = m_CListCtrlItem.GetHeaderCtrl()->GetItemCount();
	iRowCount = m_CListCtrlItem.GetItemCount();

	for (int j=0 ; j<iRowCount ; j++ )
	{
		memset(chTemp, 0 ,32);
		for ( int i=0 ; i<iColumnNum ; i++ )
		{
			m_CListCtrlItem.GetItemText(j,i,chTemp, 32);
			if(strstr(chTemp,strKey))
			{
				ListIndex = j;
				goto BreakLoop;
			}
		}
	}
BreakLoop:
	m_CListCtrlItem.SetFocus();  
	m_CListCtrlItem.SetItemState(ListIndex, LVIS_SELECTED, LVIS_SELECTED);
	m_CListCtrlItem.SetSelectionMark(ListIndex);
	m_CListCtrlItem.EnsureVisible(ListIndex, FALSE);
	::SendMessage(m_CListCtrlItem.m_hWnd,  LVM_SETEXTENDEDLISTVIEWSTYLE,  
		LVS_EX_FULLROWSELECT,  LVS_EX_FULLROWSELECT); 

	m_CEditFindItem.SetFocus();
}
