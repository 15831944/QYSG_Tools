// DlgSendAwards.cpp : 实现文件
//

#include "stdafx.h"
#include "afxdb.h"
#include "HCSG_Manager.h"
#include "DlgSendAwards.h"
#include "afxdialogex.h"


// CDlgSendAwards 对话框

IMPLEMENT_DYNAMIC(CDlgSendAwards, CDialogEx)

CDlgSendAwards::CDlgSendAwards(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgSendAwards::IDD, pParent)
{
	bIsInit = FALSE;
}

CDlgSendAwards::~CDlgSendAwards()
{
}

void CDlgSendAwards::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_ACC, m_CListCtrlAcc);
	DDX_Control(pDX, IDC_LIST_ITEM, m_CListCtrlItem);
	DDX_Control(pDX, IDC_LIST_CONFIG, m_CListCtrlConfig);
	DDX_Control(pDX, IDC_EDIT_FIND_ITEM, m_CEditFindItem);
	DDX_Control(pDX, IDC_EDIT_ITEM_ID, m_CEditItemId[0]);
	DDX_Control(pDX, IDC_EDIT_ITEM_ID2, m_CEditItemId[1]);
	DDX_Control(pDX, IDC_EDIT_ITEM_ID3, m_CEditItemId[2]);
	DDX_Control(pDX, IDC_EDIT_ITEM_ID4, m_CEditItemId[3]);
	DDX_Control(pDX, IDC_EDIT_ITEM_ID5, m_CEditItemId[4]);
	DDX_Control(pDX, IDC_EDIT_ITEM_NAME, m_CEditItemName[0]);
	DDX_Control(pDX, IDC_EDIT_ITEM_NAME2, m_CEditItemName[1]);
	DDX_Control(pDX, IDC_EDIT_ITEM_NAME3, m_CEditItemName[2]);
	DDX_Control(pDX, IDC_EDIT_ITEM_NAME4, m_CEditItemName[3]);
	DDX_Control(pDX, IDC_EDIT_ITEM_NAME5, m_CEditItemName[4]);
	DDX_Control(pDX, IDC_EDIT_NUM, m_CEditItemNum[0]);
	DDX_Control(pDX, IDC_EDIT_NUM2, m_CEditItemNum[1]);
	DDX_Control(pDX, IDC_EDIT_NUM3, m_CEditItemNum[2]);
	DDX_Control(pDX, IDC_EDIT_NUM4, m_CEditItemNum[3]);
	DDX_Control(pDX, IDC_EDIT_NUM5, m_CEditItemNum[4]);
	DDX_Control(pDX, IDC_COMBO_CONFIG_ID, m_CComboBoxCfgID);
	DDX_Control(pDX, IDC_EDIT_POINTS, m_CEditPoints);
}


BEGIN_MESSAGE_MAP(CDlgSendAwards, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT_ITEM_ID, &CDlgSendAwards::OnEnChangeEditItemId)
	ON_EN_CHANGE(IDC_EDIT_ITEM_ID2, &CDlgSendAwards::OnEnChangeEditItemId2)
	ON_EN_CHANGE(IDC_EDIT_ITEM_ID3, &CDlgSendAwards::OnEnChangeEditItemId3)
	ON_EN_CHANGE(IDC_EDIT_ITEM_ID4, &CDlgSendAwards::OnEnChangeEditItemId4)
	ON_EN_CHANGE(IDC_EDIT_ITEM_ID5, &CDlgSendAwards::OnEnChangeEditItemId5)
	ON_BN_CLICKED(IDC_BUTTON_ADD_CONFIG, &CDlgSendAwards::OnBnClickedButtonAddConfig)
	ON_BN_CLICKED(IDC_BUTTON_DEL_CONFIG, &CDlgSendAwards::OnBnClickedButtonDelConfig)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_CONFIG, &CDlgSendAwards::OnBnClickedButtonSaveConfig)
	ON_BN_CLICKED(IDC_BUTTON_READ_ACCLIST, &CDlgSendAwards::OnBnClickedButtonReadAcclist)
	ON_BN_CLICKED(IDC_BUTTON_SEND_AWARDS, &CDlgSendAwards::OnBnClickedButtonSendAwards)
//	ON_WM_ACTIVATE()
END_MESSAGE_MAP()

BOOL CDlgSendAwards::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_CListCtrlAcc.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_HEADERDRAGDROP);
/*	m_CListCtrlAcc.InsertColumn(0, _T("排名"), LVCFMT_LEFT, 40);*/
	m_CListCtrlAcc.InsertColumn(0, _T("注册帐号"), LVCFMT_LEFT, 70);
	m_CListCtrlAcc.InsertColumn(1, _T("角色名称"), LVCFMT_LEFT, 70);//插入列

	m_CListCtrlItem.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_HEADERDRAGDROP);
	m_CListCtrlItem.InsertColumn(0, _T("ID"), LVCFMT_LEFT, 40);//插入列
	m_CListCtrlItem.InsertColumn(1, _T("物品名称"), LVCFMT_LEFT, 190);

	m_CListCtrlConfig.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_HEADERDRAGDROP);

	for (int i = 0; i < GOODS_NUM; i++)
	{
		m_CListCtrlConfig.InsertColumn(3*i, _T("物品ID" ), LVCFMT_LEFT, 55);
		m_CListCtrlConfig.InsertColumn(3*i+1, _T("物品名"), LVCFMT_LEFT, 100);  // 发放物品1
		m_CListCtrlConfig.InsertColumn(3*i+2, _T("数量"), LVCFMT_LEFT, 45);
	}

	for (int i = 0; i < GOODS_NUM; i++)
	{
		m_CEditItemNum[i].SetWindowText("1");
	}

	m_CEditPoints.SetWindowText("0");


	m_CComboBoxCfgID.SetCurSel(0);


	Init();

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CDlgSendAwards::Init()
{
	// TODO: 在此添加控件通知处理程序代码
	struct ItemDef TmpItemDef;
	CList <ItemDef, ItemDef&> *LCurItemDef = &Common::LItemDef;
	int ret = 0;
	POSITION pos;

	m_CListCtrlItem.DeleteAllItems();

	//将获得的物品显示到ClistCtrl里去
	pos = LCurItemDef->GetHeadPosition();
	for (int i = 0; i < LCurItemDef->GetCount(); i++)
	{
		TmpItemDef = LCurItemDef->GetNext(pos);

		int nrow = m_CListCtrlItem.GetItemCount();//取行数
		int nItem = m_CListCtrlItem.InsertItem(nrow + 1, _T(""));
		m_CListCtrlItem.SetItemText(nItem, 0, _T(TmpItemDef.ID));
		CString tempName = TmpItemDef.Name;
		tempName.Replace("item_", "");
		m_CListCtrlItem.SetItemText(nItem, 1, _T(Common::Big2GB((LPSTR)(LPCTSTR)tempName)));
	}
}

void CDlgSendAwards::DoOnEnChangeEditItemId(int nIndex)
{
	struct ItemDef TmpItemDef;
	CList <ItemDef, ItemDef&> *LCurItemDef = &Common::LItemDef;
	POSITION pos;
	int i;

	CString strItemId;
	m_CEditItemId[nIndex].GetWindowText(strItemId);

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

				m_CEditItemName[nIndex].SetWindowText(Common::Big2GB((LPSTR)(LPCTSTR)tempName));
				break;
			}
		}

		if (i >= LCurItemDef->GetCount())
		{
			m_CEditItemName[nIndex].SetWindowText("");
		}
	}
	else
	{
		m_CEditItemName[nIndex].SetWindowText("");
	}
}

void CDlgSendAwards::OnEnChangeEditItemId()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	DoOnEnChangeEditItemId(0);
}


void CDlgSendAwards::OnEnChangeEditItemId2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	DoOnEnChangeEditItemId(1);
}


void CDlgSendAwards::OnEnChangeEditItemId3()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	DoOnEnChangeEditItemId(2);
}


void CDlgSendAwards::OnEnChangeEditItemId4()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	DoOnEnChangeEditItemId(3);
}


void CDlgSendAwards::OnEnChangeEditItemId5()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	DoOnEnChangeEditItemId(4);
}


void CDlgSendAwards::OnBnClickedButtonAddConfig()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strItem[GOODS_NUM], strNum[GOODS_NUM], strItemName[GOODS_NUM];

	for (int i = 0; i < GOODS_NUM; i++)
	{
		//物品 i
		m_CEditItemId[i].GetWindowTextA(strItem[i]);
		m_CEditItemName[i].GetWindowTextA(strItemName[i]);
		m_CEditItemNum[i].GetWindowTextA(strNum[i]);

		if (strItem[i].IsEmpty()){ strItemName[i] = ""; strNum[i] = ""; }
	}

	if (strItem[0].IsEmpty() && strItem[1].IsEmpty() && strItem[2].IsEmpty()
		&& strItem[3].IsEmpty() && strItem[4].IsEmpty())
		return;

	int nrow = m_CListCtrlConfig.GetItemCount();//取行数
	int nItem = m_CListCtrlConfig.InsertItem(nrow + 1, _T(""));
	int nColumn = 0;

	for (int i = 0; i < GOODS_NUM; i++)
	{
		m_CListCtrlConfig.SetItemText(nItem, nColumn++, strItem[i]);
		m_CListCtrlConfig.SetItemText(nItem, nColumn++, strItemName[i]);
		m_CListCtrlConfig.SetItemText(nItem, nColumn++, strNum[i]);
	}
}


void CDlgSendAwards::OnBnClickedButtonDelConfig()
{
	// TODO: 在此添加控件通知处理程序代码
	int ListIndex = m_CListCtrlConfig.GetSelectionMark();
	if (ListIndex == -1) return;
	m_CListCtrlConfig.DeleteItem(ListIndex);//删除选中行
}


void CDlgSendAwards::OnBnClickedButtonSaveConfig()
{
	// TODO: 在此添加控件通知处理程序代码

	// 暂时不作处理


	if (m_CListCtrlConfig.GetItemCount() <= 0)
	{
		Common::Log(Error, "列表中没有记录需要保存！");
		return;
	}
}

CString CDlgSendAwards::GetPathName()
{
	BOOL isOpen = TRUE;        //是否打开(否则为保存)  
	CString defaultDir = ".\\";   //默认打开的文件路径  
// 	CTime m_time;
// 	m_time = CTime::GetCurrentTime();
// 	CString strBatch = m_time.Format(_T("%Y%m%d-%H%M%S"));

	CString fileName = _T("奖励名单.txt");         //默认打开的文件名  
	CString filter = "文件 (*.txt)||";   //文件过虑的类型  
	CFileDialog openFileDlg(isOpen, defaultDir, fileName, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, filter, NULL);
	openFileDlg.GetOFN().lpstrInitialDir = "";
	if (openFileDlg.DoModal())
	{
		CString PathName = openFileDlg.GetPathName();
		if (PathName.IsEmpty() == 0){
			return PathName;
		}
	}
	return "";
}

void CDlgSendAwards::OnBnClickedButtonReadAcclist()
{
	// TODO:  在此添加控件通知处理程序代码
	CString strPathName;
	CString szLine = "";
	CString strResult;
	int index;

	strPathName = GetPathName();

	//检查文件是否存在
	DWORD dwRe = GetFileAttributes(strPathName);
	if (dwRe != (DWORD)-1)
	{
		//ShellExecute(NULL, NULL, strFilePath, NULL, NULL, SW_RESTORE); 
	}
	else
	{
		CString errormessage;
		errormessage.Format("%s 奖励名单文件不存在！", strPathName);
		Common::Log(Error, errormessage);
		return;
	}

	POSITION pos;
	struct AccAttr TmpAccAttr;
	CList <AccAttr, AccAttr&> *LCurAccAttr = &Common::LAccAttr;

	//打开文件
	CStdioFile StdFile;
	StdFile.Open(strPathName, CFile::modeRead | CFile::shareDenyNone);

	m_CListCtrlAcc.DeleteAllItems();

	//逐行读取字符串
	while (StdFile.ReadString(szLine))
	{
		szLine.Replace('\t', ' ');
		szLine.Replace(_T(" "), _T(""));
		index = szLine.Find(';');
		if (index >= 0)
			szLine.Delete(szLine.Find(';'), szLine.GetLength() - szLine.Find(';'));

		index = szLine.Find("//");
		if (index >= 0)
			szLine.Delete(szLine.Find("//"), szLine.GetLength() - szLine.Find("//"));

		int nrow = m_CListCtrlAcc.GetItemCount();//取行数
		int nItem = m_CListCtrlAcc.InsertItem(nrow + 1, _T(""));
		pos = LCurAccAttr->GetHeadPosition();
		for (int j = 0; j < LCurAccAttr->GetCount(); j++)
		{
			TmpAccAttr = LCurAccAttr->GetNext(pos);
			if (0 == strcmp(Common::Big2GB(TmpAccAttr.Name), szLine))
				m_CListCtrlAcc.SetItemText(nItem, 0, _T(TmpAccAttr.Account));
		}
		m_CListCtrlAcc.SetItemText(nItem, 1, szLine);
	}

}


void CDlgSendAwards::OnBnClickedButtonSendAwards()
{
	// TODO:  在此添加控件通知处理程序代码
	if (IDYES != AfxMessageBox(_T("是否发放奖励？"), MB_YESNO))
		return;

	if (!Common::SanGuoServerIsRuning)
		return;

	int iColumnNumAcc, iRowCountAcc;
	int iColumnNumConfig, iRowCountConfig;
	CString strAccount, strItem[5], strNum[5], strAccountName;

	CStringArray AwardsArray;     // 0:id,1:num  2:id,3:num ......
	CString m_Points = "0";

	// 读取代币奖励配置
	m_CEditPoints.GetWindowText(m_Points);

	// 读取虚宝奖励配置
	iRowCountConfig = m_CListCtrlConfig.GetItemCount();   // 获得行数
	iColumnNumConfig = m_CListCtrlConfig.GetHeaderCtrl()->GetItemCount();  // 获得列数

	for (int i = 0; i < iRowCountConfig; i++)
	{
		for (int j = 0; j < GOODS_NUM; j++)
		{
			strItem[j] = m_CListCtrlConfig.GetItemText(i, 3*j);
			strNum[j] = m_CListCtrlConfig.GetItemText(i, 3*j+2);

			if (strItem[j].IsEmpty())	strNum[j] = "";
			if (!strItem[j].IsEmpty())
			{
				AwardsArray.Add(strItem[j]);
				AwardsArray.Add(strNum[j]);
			}
		}
		
	}

	Common::Log(Info, "奖励发放开始");

	iColumnNumAcc = m_CListCtrlAcc.GetHeaderCtrl()->GetItemCount();  // 获取奖励表的列数
	iRowCountAcc = m_CListCtrlAcc.GetItemCount();	// 获取奖励表的行数

	for (int i = 0; i < iRowCountAcc; i++)
	{
		strAccount = m_CListCtrlAcc.GetItemText(i, 0); // 获得角色账户
		strAccountName = m_CListCtrlAcc.GetItemText(i, 1); // 获得角色名称
		if (strAccount.IsEmpty() && !strAccountName.IsEmpty())
		{
			CString strMsg;
			strMsg.Format("### 奖励发放不成功 ###：  <  %s  > ， 请手动补发", strAccountName);
			Common::Log(Error, strMsg);
			continue;
		}

		// 发送代币奖励
		int nSendPoint = _ttoi(m_Points);
		if (!m_Points.IsEmpty() && nSendPoint > 0)
		{
			if (Common::AddPoints(nSendPoint, strAccount, "VIP用户发放") == "转商城代币成功")
			{
				CString tmp22;
				tmp22.Format("### 奖励发放 ###：向%s发放%d代币成功！", strAccount, nSendPoint);
				Common::Log(Info, tmp22);
			}
			else
			{
				CString tmp22;
				tmp22.Format("### 奖励发放 ###：代币奖励发放失败 -- %s 代币数：%d", strAccount, nSendPoint);
				Common::Log(Error, tmp22);
				continue;
			}
		}

		// 发送虚宝奖励
		CStringArray ItemList;
		ItemList.RemoveAll();
		for (int i = 0; i < AwardsArray.GetCount(); i++)
		{
			ItemList.Add(AwardsArray.GetAt(i));
			if ((i+1) % 10 == 0)
			{
				if (!Common::SendXubao(strAccount, &ItemList))
				{
					Common::Log(Error, "奖励发放失败");
				}
				ItemList.RemoveAll();
			}
			
		}

		// 把剩下的不足五个的虚宝发出去且多余一个虚宝的奖励发出去
		if (ItemList.GetCount() > 0)
		{
			if (!Common::SendXubao(strAccount, &ItemList))
			{
				Common::Log(Error, "奖励发放失败");
			}
		}
		
	}
	Common::Log(Info, "奖励发放结束");
}


//void CDlgSendAwards::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
//{
//	CDialogEx::OnActivate(nState, pWndOther, bMinimized);
//
//	// TODO:  在此处添加消息处理程序代码
//	if (bIsInit == FALSE) {
//		AfxMessageBox("窗口激活了");
//		bIsInit = TRUE;
//	}
//}
