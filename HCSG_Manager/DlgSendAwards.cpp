// DlgSendAwards.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "afxdb.h"
#include "HCSG_Manager.h"
#include "DlgSendAwards.h"
#include "afxdialogex.h"


// CDlgSendAwards �Ի���

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

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_CListCtrlAcc.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_HEADERDRAGDROP);
/*	m_CListCtrlAcc.InsertColumn(0, _T("����"), LVCFMT_LEFT, 40);*/
	m_CListCtrlAcc.InsertColumn(0, _T("ע���ʺ�"), LVCFMT_LEFT, 70);
	m_CListCtrlAcc.InsertColumn(1, _T("��ɫ����"), LVCFMT_LEFT, 70);//������

	m_CListCtrlItem.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_HEADERDRAGDROP);
	m_CListCtrlItem.InsertColumn(0, _T("ID"), LVCFMT_LEFT, 40);//������
	m_CListCtrlItem.InsertColumn(1, _T("��Ʒ����"), LVCFMT_LEFT, 190);

	m_CListCtrlConfig.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_HEADERDRAGDROP);

	for (int i = 0; i < GOODS_NUM; i++)
	{
		m_CListCtrlConfig.InsertColumn(3*i, _T("��ƷID" ), LVCFMT_LEFT, 55);
		m_CListCtrlConfig.InsertColumn(3*i+1, _T("��Ʒ��"), LVCFMT_LEFT, 100);  // ������Ʒ1
		m_CListCtrlConfig.InsertColumn(3*i+2, _T("����"), LVCFMT_LEFT, 45);
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	struct ItemDef TmpItemDef;
	CList <ItemDef, ItemDef&> *LCurItemDef = &Common::LItemDef;
	int ret = 0;
	POSITION pos;

	m_CListCtrlItem.DeleteAllItems();

	//����õ���Ʒ��ʾ��ClistCtrl��ȥ
	pos = LCurItemDef->GetHeadPosition();
	for (int i = 0; i < LCurItemDef->GetCount(); i++)
	{
		TmpItemDef = LCurItemDef->GetNext(pos);

		int nrow = m_CListCtrlItem.GetItemCount();//ȡ����
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

	//ȷ����Ʒ�Ƿ����
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
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	DoOnEnChangeEditItemId(0);
}


void CDlgSendAwards::OnEnChangeEditItemId2()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	DoOnEnChangeEditItemId(1);
}


void CDlgSendAwards::OnEnChangeEditItemId3()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	DoOnEnChangeEditItemId(2);
}


void CDlgSendAwards::OnEnChangeEditItemId4()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	DoOnEnChangeEditItemId(3);
}


void CDlgSendAwards::OnEnChangeEditItemId5()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	DoOnEnChangeEditItemId(4);
}


void CDlgSendAwards::OnBnClickedButtonAddConfig()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strItem[GOODS_NUM], strNum[GOODS_NUM], strItemName[GOODS_NUM];

	for (int i = 0; i < GOODS_NUM; i++)
	{
		//��Ʒ i
		m_CEditItemId[i].GetWindowTextA(strItem[i]);
		m_CEditItemName[i].GetWindowTextA(strItemName[i]);
		m_CEditItemNum[i].GetWindowTextA(strNum[i]);

		if (strItem[i].IsEmpty()){ strItemName[i] = ""; strNum[i] = ""; }
	}

	if (strItem[0].IsEmpty() && strItem[1].IsEmpty() && strItem[2].IsEmpty()
		&& strItem[3].IsEmpty() && strItem[4].IsEmpty())
		return;

	int nrow = m_CListCtrlConfig.GetItemCount();//ȡ����
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int ListIndex = m_CListCtrlConfig.GetSelectionMark();
	if (ListIndex == -1) return;
	m_CListCtrlConfig.DeleteItem(ListIndex);//ɾ��ѡ����
}


void CDlgSendAwards::OnBnClickedButtonSaveConfig()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	// ��ʱ��������


	if (m_CListCtrlConfig.GetItemCount() <= 0)
	{
		Common::Log(Error, "�б���û�м�¼��Ҫ���棡");
		return;
	}
}

CString CDlgSendAwards::GetPathName()
{
	BOOL isOpen = TRUE;        //�Ƿ��(����Ϊ����)  
	CString defaultDir = ".\\";   //Ĭ�ϴ򿪵��ļ�·��  
// 	CTime m_time;
// 	m_time = CTime::GetCurrentTime();
// 	CString strBatch = m_time.Format(_T("%Y%m%d-%H%M%S"));

	CString fileName = _T("��������.txt");         //Ĭ�ϴ򿪵��ļ���  
	CString filter = "�ļ� (*.txt)||";   //�ļ����ǵ�����  
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString strPathName;
	CString szLine = "";
	CString strResult;
	int index;

	strPathName = GetPathName();

	//����ļ��Ƿ����
	DWORD dwRe = GetFileAttributes(strPathName);
	if (dwRe != (DWORD)-1)
	{
		//ShellExecute(NULL, NULL, strFilePath, NULL, NULL, SW_RESTORE); 
	}
	else
	{
		CString errormessage;
		errormessage.Format("%s ���������ļ������ڣ�", strPathName);
		Common::Log(Error, errormessage);
		return;
	}

	POSITION pos;
	struct AccAttr TmpAccAttr;
	CList <AccAttr, AccAttr&> *LCurAccAttr = &Common::LAccAttr;

	//���ļ�
	CStdioFile StdFile;
	StdFile.Open(strPathName, CFile::modeRead | CFile::shareDenyNone);

	m_CListCtrlAcc.DeleteAllItems();

	//���ж�ȡ�ַ���
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

		int nrow = m_CListCtrlAcc.GetItemCount();//ȡ����
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (IDYES != AfxMessageBox(_T("�Ƿ񷢷Ž�����"), MB_YESNO))
		return;

	if (!Common::SanGuoServerIsRuning)
		return;

	int iColumnNumAcc, iRowCountAcc;
	int iColumnNumConfig, iRowCountConfig;
	CString strAccount, strItem[5], strNum[5], strAccountName;

	CStringArray AwardsArray;     // 0:id,1:num  2:id,3:num ......
	CString m_Points = "0";

	// ��ȡ���ҽ�������
	m_CEditPoints.GetWindowText(m_Points);

	// ��ȡ�鱦��������
	iRowCountConfig = m_CListCtrlConfig.GetItemCount();   // �������
	iColumnNumConfig = m_CListCtrlConfig.GetHeaderCtrl()->GetItemCount();  // �������

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

	Common::Log(Info, "�������ſ�ʼ");

	iColumnNumAcc = m_CListCtrlAcc.GetHeaderCtrl()->GetItemCount();  // ��ȡ�����������
	iRowCountAcc = m_CListCtrlAcc.GetItemCount();	// ��ȡ�����������

	for (int i = 0; i < iRowCountAcc; i++)
	{
		strAccount = m_CListCtrlAcc.GetItemText(i, 0); // ��ý�ɫ�˻�
		strAccountName = m_CListCtrlAcc.GetItemText(i, 1); // ��ý�ɫ����
		if (strAccount.IsEmpty() && !strAccountName.IsEmpty())
		{
			CString strMsg;
			strMsg.Format("### �������Ų��ɹ� ###��  <  %s  > �� ���ֶ�����", strAccountName);
			Common::Log(Error, strMsg);
			continue;
		}

		// ���ʹ��ҽ���
		int nSendPoint = _ttoi(m_Points);
		if (!m_Points.IsEmpty() && nSendPoint > 0)
		{
			if (Common::AddPoints(nSendPoint, strAccount, "VIP�û�����") == "ת�̳Ǵ��ҳɹ�")
			{
				CString tmp22;
				tmp22.Format("### �������� ###����%s����%d���ҳɹ���", strAccount, nSendPoint);
				Common::Log(Info, tmp22);
			}
			else
			{
				CString tmp22;
				tmp22.Format("### �������� ###�����ҽ�������ʧ�� -- %s ��������%d", strAccount, nSendPoint);
				Common::Log(Error, tmp22);
				continue;
			}
		}

		// �����鱦����
		CStringArray ItemList;
		ItemList.RemoveAll();
		for (int i = 0; i < AwardsArray.GetCount(); i++)
		{
			ItemList.Add(AwardsArray.GetAt(i));
			if ((i+1) % 10 == 0)
			{
				if (!Common::SendXubao(strAccount, &ItemList))
				{
					Common::Log(Error, "��������ʧ��");
				}
				ItemList.RemoveAll();
			}
			
		}

		// ��ʣ�µĲ���������鱦����ȥ�Ҷ���һ���鱦�Ľ�������ȥ
		if (ItemList.GetCount() > 0)
		{
			if (!Common::SendXubao(strAccount, &ItemList))
			{
				Common::Log(Error, "��������ʧ��");
			}
		}
		
	}
	Common::Log(Info, "�������Ž���");
}


//void CDlgSendAwards::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
//{
//	CDialogEx::OnActivate(nState, pWndOther, bMinimized);
//
//	// TODO:  �ڴ˴������Ϣ����������
//	if (bIsInit == FALSE) {
//		AfxMessageBox("���ڼ�����");
//		bIsInit = TRUE;
//	}
//}
