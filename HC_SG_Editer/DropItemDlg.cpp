// Dropitem.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "HC_SG_Editer.h"
#include "DropItemDlg.h"
#include "afxdialogex.h"


// CDropItemDlg �Ի���

IMPLEMENT_DYNAMIC(CDropItemDlg, CDialogEx)

CDropItemDlg::CDropItemDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDropItemDlg::IDD, pParent)
{

}

CDropItemDlg::~CDropItemDlg()
{
}

void CDropItemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_PATH, m_CEditPath);
	DDX_Control(pDX, IDC_LIST_COUNT, m_CListCtrlCount);
	DDX_Control(pDX, IDC_LIST_ITEM, m_CListCtrlItem);
	DDX_Control(pDX, IDC_LIST_PLAYERS, m_CListCtrlPlayers);
	DDX_Control(pDX, IDC_LIST_DROPS, m_CListCtrlDrops);
	DDX_Control(pDX, IDC_EDIT_NAME, m_CEditName);
	DDX_Control(pDX, IDC_EDIT_COUNTER, m_CEditCounter);
	DDX_Control(pDX, IDC_EDIT_FIND, m_CEditFind);
	DDX_Control(pDX, IDC_EDIT_FIND_ITEM, m_CEditFindItem);
	DDX_Control(pDX, IDC_EDIT_ITEM_NAME, m_CEditItemName);
	DDX_Control(pDX, IDC_EDIT_DROP_RANGE, m_CEditDropRange);
	DDX_Control(pDX, IDC_EDIT_ITEM_NAME2, m_CEditItemName2);
	DDX_Control(pDX, IDC_EDIT_DROP_RANGE2, m_CEditDropRange2);
	DDX_Control(pDX, IDC_EDIT_DROP_ID, m_CEditDropId);
	DDX_Control(pDX, IDC_EDIT_ITEM_NAME_TEMP, m_CEditItemNameTemp);
	DDX_Control(pDX, IDC_EDIT_ITEM_NAME_TEMP2, m_CEditItemNameTemp2);
	DDX_Control(pDX, IDC_LIST_DROPS_TEMP, m_CListCtrlDropsTemp);
	DDX_Control(pDX, IDC_EDIT_GREATER, m_CEditGreater);
	DDX_Control(pDX, IDC_EDIT_LESS, m_CEditLess);
	DDX_Control(pDX, IDC_EDIT_INC, m_CEditInc);
	DDX_Control(pDX, IDC_EDIT_DEC, m_CEditDec);
	DDX_Control(pDX, IDC_EDIT_MUL, m_CEditMul);
	DDX_Control(pDX, IDC_EDIT_EQUER, m_CEditFixed);
	DDX_Control(pDX, IDC_EDIT_FIX_ITEM, m_CEditFixItem);
	DDX_Control(pDX, IDC_STATIC_COUNTER, m_CStaticCounter);
}


BEGIN_MESSAGE_MAP(CDropItemDlg, CDialogEx)
	ON_BN_CLICKED(ID_SCAN, &CDropItemDlg::OnBnClickedScan)
	ON_BN_CLICKED(ID_RUN, &CDropItemDlg::OnBnClickedRun)
	ON_NOTIFY(NM_CLICK, IDC_LIST_PLAYERS, &CDropItemDlg::OnNMClickListPlayers)
	ON_EN_CHANGE(IDC_EDIT_FIND, &CDropItemDlg::OnEnChangeEditFind)
	ON_BN_CLICKED(IDC_BUTTON_PLAYER_NEXT, &CDropItemDlg::OnBnClickedButtonPlayerNext)
	ON_EN_CHANGE(IDC_EDIT_FIND_ITEM, &CDropItemDlg::OnEnChangeEditFindItem)
	ON_BN_CLICKED(IDC_BUTTON_ITEM_NEXT, &CDropItemDlg::OnBnClickedButtonItemNext)
	ON_NOTIFY(NM_CLICK, IDC_LIST_ITEM, &CDropItemDlg::OnNMClickListItem)
	ON_NOTIFY(NM_CLICK, IDC_LIST_DROPS, &CDropItemDlg::OnNMClickListDrops)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CDropItemDlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_DEL, &CDropItemDlg::OnBnClickedButtonDel)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CDropItemDlg::OnBnClickedButtonSaveDrop)
	ON_BN_CLICKED(IDC_BUTTON6, &CDropItemDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY, &CDropItemDlg::OnBnClickedButtonModify)
	ON_BN_CLICKED(IDC_BUTTON_DROP_TXT, &CDropItemDlg::OnBnClickedButtonDropTxt)
	ON_BN_CLICKED(IDC_BUTTON_EXE, &CDropItemDlg::OnBnClickedButtonExe)
	ON_BN_CLICKED(ID_FIX, &CDropItemDlg::OnBnClickedFix)
END_MESSAGE_MAP()


// CDropItemDlg ��Ϣ�������

int CALLBACK DroplistCompare(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)  
{  
	DATA * MyData=(DATA*)lParamSort;  
	int col=MyData->col;//���������ݸ�col,�����жϵ���˵ڼ���  
	//ȡ����ַ���  
	CString strItem1, strItem2;  
	strItem1=MyData->plist->GetItemText(lParam1,col);  
	strItem2=MyData->plist->GetItemText(lParam2,col);
	int   n1=_ttoi(strItem1);
	int   n2=_ttoi(strItem2);
	if   (n1>=n2)
		return   -1;
	else    
		return   1;
}


BOOL CDropItemDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	m_CListCtrlPlayers.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP);
	m_CListCtrlPlayers.InsertColumn(0, _T("��������"), LVCFMT_LEFT, 100);//������
	m_CListCtrlPlayers.InsertColumn(1, _T("����ID"), LVCFMT_LEFT, 60);//������


	m_CListCtrlDrops.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP);
	m_CListCtrlDrops.InsertColumn(0, _T("������Ʒ"), LVCFMT_LEFT, 95);//������
	m_CListCtrlDrops.InsertColumn(1, _T("���伸��"), LVCFMT_LEFT, 80);
	m_CListCtrlDrops.InsertColumn(2, _T("����"), LVCFMT_LEFT, 0);

	m_CListCtrlItem.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP);
	m_CListCtrlItem.InsertColumn(0, _T("��ƷID"), LVCFMT_LEFT, 60);//������
	m_CListCtrlItem.InsertColumn(1, _T("��Ʒ����"), LVCFMT_LEFT, 160);
	m_CListCtrlItem.InsertColumn(2, _T("����"), LVCFMT_LEFT, 0);

	m_CListCtrlCount.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP);
	m_CListCtrlCount.InsertColumn(0, _T("Drop_ID"), LVCFMT_LEFT, 60);//������
	m_CListCtrlCount.InsertColumn(1, _T("�ܺ�"), LVCFMT_LEFT, 70);
	m_CListCtrlCount.InsertColumn(2, _T("״̬"), LVCFMT_LEFT, 60);

	m_CListCtrlDropsTemp.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP);
	m_CListCtrlDropsTemp.InsertColumn(0, _T("������Ʒ"), LVCFMT_LEFT, 95);//������
	m_CListCtrlDropsTemp.InsertColumn(1, _T("���伸��"), LVCFMT_LEFT, 80);
	m_CListCtrlDropsTemp.InsertColumn(2, _T("����"), LVCFMT_LEFT, 0);

	InitItemDef();
	InitPlayers();

	return TRUE;  // return TRUE unless you set the focus to a control
}


void CDropItemDlg::OnBnClickedScan()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,_T("All Files(*.txt)|*.txt||"));
	if(dlg.DoModal()==IDOK){
		CString PathName=dlg.GetPathName();
		if(PathName.IsEmpty()==0){
			m_CEditPath.SetWindowText(PathName);
		}
	}
}


void CDropItemDlg::OnBnClickedRun()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strPathName;
	int ret = 0;
	int GetValueStep = 0;
	int index;
	CString strGap = ",";

	m_CListCtrlCount.DeleteAllItems();

	m_CEditPath.GetWindowText(strPathName);
	CString szLine = "";
	CString strResult;

	//����ļ��Ƿ����
	DWORD dwRe = GetFileAttributes(strPathName);
	if ( dwRe != (DWORD)-1 )
	{
		//ShellExecute(NULL, NULL, strFilePath, NULL, NULL, SW_RESTORE); 
	}
	else 
	{
		CString errormessage;
		errormessage.Format("%s �����ļ������ڣ�", strPathName);
		AfxMessageBox(errormessage);
		return;
	}

	//���ļ�
	CStdioFile StdFile;
	StdFile.Open(strPathName,CFile::modeRead | CFile::shareDenyNone);

	//���ж�ȡ�ַ���
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
			CStringArray strDest;
			szLine.Replace(_T("drop="), _T(""));
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
			for(int i = 2; i < strDest.GetCount();)
			{
				count += _ttoi(strDest[i]);
				i +=2;
			}

			CString strMsg;
			if(count != 100000000)
			{
				int nrow = m_CListCtrlCount.GetItemCount();//ȡ����
				int nItem = m_CListCtrlCount.InsertItem(nrow+1, _T(""));
				m_CListCtrlCount.SetItemText(nItem, 0, strDest[0]);
				CString strTemp;
				strTemp.Format("%d", count);
				m_CListCtrlCount.SetItemText(nItem, 1, strTemp);
				m_CListCtrlCount.SetItemText(nItem, 2, _T("�쳣"));
			}
			else
			{
				// 				int nrow = m_CListCtrlCount.GetItemCount();//ȡ����
				// 				int nItem = m_CListCtrlCount.InsertItem(nrow+1, _T(""));
				// 				m_CListCtrlCount.SetItemText(nItem, 0, strDest[0]);
				// 				CString strTemp;
				// 				strTemp.Format("%d", count);
				// 				m_CListCtrlCount.SetItemText(nItem, 1, strTemp);
				// 				m_CListCtrlCount.SetItemText(nItem, 2, _T(""));
			}
		}
	}
	//�ر��ļ�
	StdFile.Close();
}


void CDropItemDlg::InitItemDef()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	struct ItemDef TmpItemDef;
	CList <ItemDef, ItemDef&> *LCurItemDef = &Common::LItemDef;
	int ret = 0;
	POSITION pos;

	m_CListCtrlItem.DeleteAllItems();

	//����õ���Ʒ��ʾ��ClistCtrl��ȥ
	pos = LCurItemDef->GetHeadPosition();
	for (int i=0;i < LCurItemDef->GetCount();i++)
	{
		TmpItemDef = LCurItemDef->GetNext(pos);

		int nrow = m_CListCtrlItem.GetItemCount();//ȡ����
		int nItem = m_CListCtrlItem.InsertItem(nrow+1, _T(""));
		m_CListCtrlItem.SetItemText(nItem, 0, _T(TmpItemDef.ID));
		CString tempName = TmpItemDef.Name;
		tempName.Replace("item_", "");
		tempName.Replace("Item_", "");
		m_CListCtrlItem.SetItemText(nItem, 1, _T(Common::Big2GB((LPSTR)(LPCTSTR)tempName)));
		m_CListCtrlItem.SetItemText(nItem, 2, tempName);
	}
}


void CDropItemDlg::InitPlayers()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	struct Players TmpPlayers;
	CList <Players, Players&> *LCurPlayers = &Common::LPlayers;
	int ret = 0;
	POSITION pos;

	m_CListCtrlPlayers.DeleteAllItems();

	//����õ���Ʒ��ʾ��ClistCtrl��ȥ
	pos = LCurPlayers->GetHeadPosition();
	for (int i=0;i < LCurPlayers->GetCount();i++)
	{
		TmpPlayers = LCurPlayers->GetNext(pos);

		int nrow = m_CListCtrlPlayers.GetItemCount();//ȡ����
		int nItem = m_CListCtrlPlayers.InsertItem(nrow+1, _T(""));
		CString tempName = TmpPlayers.code;
		tempName.Replace("role_", "");
		m_CListCtrlPlayers.SetItemText(nItem, 0, _T(Common::Big2GB((LPSTR)(LPCTSTR)tempName)));
		m_CListCtrlPlayers.SetItemText(nItem, 1, TmpPlayers.drop);
	}

	InitBagsDrop();  //˳���Ѹ����Ŀ������ݼ��ؽ���
}


void CDropItemDlg::InitBagsDrop()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	struct BagsDrop TmpBagsDrop;
	CList <BagsDrop, BagsDrop&> *LCurBagsDrop = &Common::LBagsDrop;
	int ret = 0;
	POSITION pos;

	//����õ���Ʒ��ʾ��ClistCtrl��ȥ
	pos = LCurBagsDrop->GetHeadPosition();
	for (int i=0;i < LCurBagsDrop->GetCount();i++)
	{
		TmpBagsDrop = LCurBagsDrop->GetNext(pos);

		int nrow = m_CListCtrlPlayers.GetItemCount();//ȡ����
		int nItem = m_CListCtrlPlayers.InsertItem(nrow+1, _T(""));
		CString tempName = TmpBagsDrop.ItemName;
		tempName.Replace("item_", "");
		m_CListCtrlPlayers.SetItemText(nItem, 0, _T(Common::Big2GB((LPSTR)(LPCTSTR)tempName)));
		m_CListCtrlPlayers.SetItemText(nItem, 1, TmpBagsDrop.DropId);
	}
}


void CDropItemDlg::DoDropListSort()
{
	int i;
	struct DropsRange TmpDropsRange;
	CList <DropsRange, DropsRange&> *LCurDropsRange = &Common::LDropsRange;
	CString strItemName, strDropRange;
	CString TempItemDrop = "";
	int len=m_CListCtrlDrops.GetItemCount();
	for(int i=0;i<len;i++)
	{
		m_CListCtrlDrops.SetItemData(i,i);
	}

	DATA data;
	data.col=1;//ȡ��
	data.plist=&m_CListCtrlDrops;//ȡ�б�ָ��
	m_CListCtrlDrops.SortItems(DroplistCompare, (LPARAM)&data);

	int count = 0;
	int nrow = m_CListCtrlDrops.GetItemCount();//ȡ����
	for(i=0; i< nrow; i++)
	{
		strItemName = m_CListCtrlDrops.GetItemText(i, 2);
		strDropRange = m_CListCtrlDrops.GetItemText(i, 1);
		count += _ttoi(strDropRange);
		if(i<nrow-1)
			TempItemDrop += "item_" + strItemName + "," + strDropRange + ",";
		else
			TempItemDrop += "item_" + strItemName + "," + strDropRange;
	}

	CString strTemp;
	strTemp.Format("%d", count);
	m_CEditCounter.SetWindowTextA(strTemp);

	CString DropId;
	m_CEditDropId.GetWindowTextA(DropId);
	POSITION pos = LCurDropsRange->GetHeadPosition();
	for (i=0;i < LCurDropsRange->GetCount();i++)
	{
		POSITION tmpPos = pos;
		TmpDropsRange = LCurDropsRange->GetNext(pos);
		if(TmpDropsRange.DropId == DropId)
		{
			TmpDropsRange.DropRange = TempItemDrop;
			LCurDropsRange->SetAt(tmpPos, TmpDropsRange);
			break;
		}
	}
	m_CStaticCounter.SetWindowText(Common::convert(m_CListCtrlDrops.GetItemCount()));
}


void CDropItemDlg::DoDropListSortTemp(CString strDropId)
{
	int i;
	struct DropsRange TmpDropsRange;
	CList <DropsRange, DropsRange&> *LCurDropsRange = &Common::LDropsRange;
	CString strItemName, strDropRange;
	CString TempItemDrop = "";
	int len=m_CListCtrlDropsTemp.GetItemCount();
	for(int i=0;i<len;i++)
	{
		m_CListCtrlDropsTemp.SetItemData(i,i);
	}

	DATA data;
	data.col=1;//ȡ��
	data.plist=&m_CListCtrlDropsTemp;//ȡ�б�ָ��
	m_CListCtrlDropsTemp.SortItems(DroplistCompare, (LPARAM)&data);

	int nrow = m_CListCtrlDropsTemp.GetItemCount();//ȡ����
	for(i=0; i< nrow; i++)
	{
		strItemName = m_CListCtrlDropsTemp.GetItemText(i, 2);
		strDropRange = m_CListCtrlDropsTemp.GetItemText(i, 1);

		if(i<nrow-1)
			TempItemDrop += strItemName + "," + strDropRange + ",";
		else
			TempItemDrop += strItemName + "," + strDropRange;
	}


	POSITION pos = LCurDropsRange->GetHeadPosition();
	for (i=0;i < LCurDropsRange->GetCount();i++)
	{
		POSITION tmpPos = pos;
		TmpDropsRange = LCurDropsRange->GetNext(pos);
		if(TmpDropsRange.DropId == strDropId)
		{
			TmpDropsRange.DropRange = TempItemDrop;
			LCurDropsRange->SetAt(tmpPos, TmpDropsRange);
			break;
		}
	}
}


void CDropItemDlg::OnNMClickListPlayers(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	int i;
	struct DropsRange TmpDropsRange;
	CList <DropsRange, DropsRange&> *LCurDropsRange = &Common::LDropsRange;

	m_CListCtrlDrops.DeleteAllItems();

	int ListIndex = m_CListCtrlPlayers.GetSelectionMark();
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
		AfxMessageBox("û���ҵ��趨�ı���");
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
		int nrow = m_CListCtrlDrops.GetItemCount();//ȡ����
		int nItem = m_CListCtrlDrops.InsertItem(nrow+1, _T(""));
		CString tempName = strDest[i++];
		tempName.Replace("item_", "");
		tempName.Replace("Item_", "");
		m_CListCtrlDrops.SetItemText(nItem, 0, _T(Common::Big2GB((LPSTR)(LPCTSTR)tempName)));
		CString temp12 = strDest[i++];
		count += _ttoi(temp12);
		m_CListCtrlDrops.SetItemText(nItem, 1, temp12);
		m_CListCtrlDrops.SetItemText(nItem, 2, tempName);
	}

	CString strTemp;
	strTemp.Format("%d", count);
	m_CEditCounter.SetWindowTextA(strTemp);

	DoDropListSort();
}


void CDropItemDlg::OnEnChangeEditFind()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
		AfxMessageBox("û���ҵ��趨�ı���");
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
		int nrow = m_CListCtrlDrops.GetItemCount();//ȡ����
		int nItem = m_CListCtrlDrops.InsertItem(nrow+1, _T(""));
		CString tempName = strDest[i++];
		tempName.Replace("item_", "");
		tempName.Replace("Item_", "");
		m_CListCtrlDrops.SetItemText(nItem, 0, _T(Common::Big2GB((LPSTR)(LPCTSTR)tempName)));
		CString temp12 = strDest[i++];
		count += _ttoi(temp12);
		m_CListCtrlDrops.SetItemText(nItem, 1, temp12);
		m_CListCtrlDrops.SetItemText(nItem, 2, tempName);
	}

	CString strTemp;
	strTemp.Format("%d", count);
	m_CEditCounter.SetWindowTextA(strTemp);

	DoDropListSort();

	m_CEditFind.SetFocus();
}


void CDropItemDlg::OnBnClickedButtonPlayerNext()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
		AfxMessageBox("û���ҵ��趨�ı���");
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
		int nrow = m_CListCtrlDrops.GetItemCount();//ȡ����
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

	DoDropListSort();
}


void CDropItemDlg::OnEnChangeEditFindItem()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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


	ListIndex = m_CListCtrlItem.GetSelectionMark();
	if(ListIndex == -1) return;
	m_CEditItemName.SetWindowText(m_CListCtrlItem.GetItemText(ListIndex, 1));
	m_CEditItemNameTemp.SetWindowText(m_CListCtrlItem.GetItemText(ListIndex, 2));

	m_CEditFindItem.SetFocus();
}


void CDropItemDlg::OnBnClickedButtonItemNext()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
		for ( int i=0 ; i<2 ; i++ )  // ֻ�����˻����ͽ�ɫ��
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


	ListIndex = m_CListCtrlItem.GetSelectionMark();
	if(ListIndex == -1) return;
	m_CEditItemName.SetWindowText(m_CListCtrlItem.GetItemText(ListIndex, 1));
	m_CEditItemNameTemp.SetWindowText(m_CListCtrlItem.GetItemText(ListIndex, 2));
}


void CDropItemDlg::OnNMClickListItem(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int ListIndex = m_CListCtrlItem.GetSelectionMark();
	if(ListIndex == -1) return;
	m_CEditItemName.SetWindowText(m_CListCtrlItem.GetItemText(ListIndex, 1));
	m_CEditItemNameTemp.SetWindowText(m_CListCtrlItem.GetItemText(ListIndex, 2));
	*pResult = 0;
}


void CDropItemDlg::OnNMClickListDrops(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int ListIndex = m_CListCtrlDrops.GetSelectionMark();
	if(ListIndex == -1) return;
	m_CEditItemName2.SetWindowText(m_CListCtrlDrops.GetItemText(ListIndex, 0));
	m_CEditDropRange2.SetWindowText(m_CListCtrlDrops.GetItemText(ListIndex, 1));
	m_CEditItemNameTemp2.SetWindowText(m_CListCtrlItem.GetItemText(ListIndex, 2));
	*pResult = 0;
}


void CDropItemDlg::OnBnClickedButtonAdd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strItemName, strItemNameTemp, strDropRange;
	BOOL bFound = FALSE;
	int i;
	m_CEditItemName.GetWindowTextA(strItemName);
	m_CEditItemNameTemp.GetWindowTextA(strItemNameTemp);
	m_CEditDropRange.GetWindowText(strDropRange);
	CString DropId;
	m_CEditDropId.GetWindowTextA(DropId);

	if(strItemName.IsEmpty() || DropId.IsEmpty())
		return;

	int nrow = m_CListCtrlDrops.GetItemCount();//ȡ����
	for(i=0; i< nrow; i++)
	{
		CString temp;
		temp = m_CListCtrlDrops.GetItemText(i, 0);
		if(strItemName.Compare(temp) == 0)
		{
			//bFound = TRUE;   // Ϊ��������ͬ��Ʒ���趨
			break;
		}
	}

	struct DropsRange TmpDropsRange;
	CList <DropsRange, DropsRange&> *LCurDropsRange = &Common::LDropsRange;

	if(bFound)
	{
		m_CListCtrlDrops.SetItemText(i, 1, strDropRange);  // �滻ԭ�еı���

		//��Ҫ�޸�ԭ�������еı���
		//�ҵ�������
		POSITION pos = LCurDropsRange->GetHeadPosition();
		for (i=0;i < LCurDropsRange->GetCount();i++)
		{
			TmpDropsRange = LCurDropsRange->GetNext(pos);
			if(TmpDropsRange.DropId == DropId)
				break;
		}

		DoDropListSort();
	}
	else
	{
		int nItem = m_CListCtrlDrops.InsertItem(nrow+1, _T(""));

		m_CListCtrlDrops.SetItemText(nItem, 0, strItemName);
		m_CListCtrlDrops.SetItemText(nItem, 1, strDropRange);
		m_CListCtrlDrops.SetItemText(nItem, 2, strItemNameTemp);

		DoDropListSort();
	}
}


void CDropItemDlg::OnBnClickedButtonDel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int ListIndex  = m_CListCtrlDrops.GetSelectionMark();
	if(ListIndex == -1) return;
	m_CListCtrlDrops.DeleteItem(ListIndex);//ɾ��ѡ����

	DoDropListSort();
}


void CDropItemDlg::OnBnClickedButtonSaveDrop()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString StrValue;
	CString strPathName="";
	::GetCurrentDirectory(1024,strPathName.GetBuffer(1024));
	strPathName.ReleaseBuffer();
	strPathName += "\\DROPITEM-New.TXT";

	DWORD dwRe = GetFileAttributes(strPathName);
	if ( dwRe != (DWORD)-1 )
	{
		DeleteFile(strPathName);
	}

	//���ļ�
	CStdioFile StdFile;
	StdFile.Open(strPathName,CFile::modeCreate | CFile::modeWrite | CFile::shareDenyNone);

	StdFile.WriteString(Common::GB2Big("// ������Ʒ�趨��"));
	StdFile.WriteString("\n");
	StdFile.WriteString("#include TYPE.H\n");
	StdFile.WriteString("#include ITEM.H\n\n\n");
	StdFile.WriteString("[ini]\n");
	StdFile.WriteString("max = 10000\n\n");
	StdFile.WriteString("[drop]\n");

	int i;
	struct DropsRange TmpDropsRange;
	CList <DropsRange, DropsRange&> *LCurDropsRange = &Common::LDropsRange;
	CString DropId;
	m_CEditDropId.GetWindowTextA(DropId);
	POSITION pos = LCurDropsRange->GetHeadPosition();
	for (i=0;i < LCurDropsRange->GetCount();i++)
	{
		TmpDropsRange = LCurDropsRange->GetNext(pos);
		CString Temp22 = "drop = " + TmpDropsRange.DropId + "," + TmpDropsRange.DropRange + "\n";
		StdFile.WriteString(Temp22);
	}

	AfxMessageBox("�����趨��ɣ�");
}


void CDropItemDlg::OnBnClickedButton6()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	AfxMessageBox("û������Ӵ��");
	// 	Common::SystemInit();
	// 	InitPlayers();
	// 	InitItemDef();
}


void CDropItemDlg::OnBnClickedButtonModify()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strItemName, strItemNameTemp, strDropRange;
	BOOL bFound = FALSE;
	int i;
	m_CEditItemName2.GetWindowTextA(strItemName);
	m_CEditDropRange2.GetWindowText(strDropRange);
	m_CEditItemNameTemp2.GetWindowTextA(strItemNameTemp);
	CString DropId;
	m_CEditDropId.GetWindowTextA(DropId);

	if(strItemName.IsEmpty() || DropId.IsEmpty())
		return;

	int nrow = m_CListCtrlDrops.GetItemCount();//ȡ����
	for(i=0; i< nrow; i++)
	{
		CString temp;
		temp = m_CListCtrlDrops.GetItemText(i, 0);
		if(strItemName.Compare(temp) == 0)
		{
			bFound = TRUE;   // Ϊ��������ͬ��Ʒ���趨
			break;
		}
	}

	struct DropsRange TmpDropsRange;
	CList <DropsRange, DropsRange&> *LCurDropsRange = &Common::LDropsRange;

	if(bFound)
	{
		m_CListCtrlDrops.SetItemText(i, 1, strDropRange);  // �滻��ԭ�еı���

		//��Ҫ�޸�ԭ�������еı���
		//�ҵ�������
		POSITION pos = LCurDropsRange->GetHeadPosition();
		for (i=0;i < LCurDropsRange->GetCount();i++)
		{
			TmpDropsRange = LCurDropsRange->GetNext(pos);
			if(TmpDropsRange.DropId == DropId)
				break;
		}

		DoDropListSort();
	}
	else
	{
		int nItem = m_CListCtrlDrops.InsertItem(nrow+1, _T(""));

		m_CListCtrlDrops.SetItemText(nItem, 0, strItemName);
		m_CListCtrlDrops.SetItemText(nItem, 1, strDropRange);
		m_CListCtrlDrops.SetItemText(nItem, 2, strItemNameTemp);

		DoDropListSort();
	}
}


void CDropItemDlg::OnBnClickedButtonDropTxt()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int i, j;
	CString strName, strDropId, strDropList;
	struct DropsRange TmpDropsRange;
	CList <DropsRange, DropsRange&> *LCurDropsRange = &Common::LDropsRange;

	CString StrValue;
	CString strPathName = "";
	::GetCurrentDirectory(1024, strPathName.GetBuffer(1024));
	strPathName.ReleaseBuffer();
	strPathName += "\\�ʳ�90��-С�� boss ��ǩ ����˵��.TXT";

	DWORD dwRe = GetFileAttributes(strPathName);
	if ( dwRe != (DWORD)-1 )
	{
		DeleteFile(strPathName);
	}

	//���ļ�
	CStdioFile StdFile;
	StdFile.Open(strPathName,CFile::modeCreate | CFile::modeWrite | CFile::shareDenyNone);

	StdFile.WriteString("// �ʳ�90��-С�� boss ��ǩ ����˵��\n");

	int nrow = m_CListCtrlPlayers.GetItemCount();//ȡ����
	for(i = 0; i < nrow; i++)
	{
		strName = m_CListCtrlPlayers.GetItemText(i, 0);
		strDropId = m_CListCtrlPlayers.GetItemText(i, 1);

		POSITION pos = LCurDropsRange->GetHeadPosition();
		for (j=0;j < LCurDropsRange->GetCount();j++)
		{
			TmpDropsRange = LCurDropsRange->GetNext(pos);
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
					if(strLeft == "item_Nothing")  // ���� Nothing
					{
						bSkip = TRUE;
						len = szLine.GetLength();
						szLine = szLine.Right(szLine.GetLength() - nPos - 1);
						nPos = szLine.Find(strGap);
						continue;
					}
					if(bSkip)   // ����Nothing�ı�����
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

				CString Temp22 = "��" + strName + "��\n";
				StdFile.WriteString(Temp22);
				Temp22 = "";
				int nCount = strDest.GetCount();
				CString strTemp = "";
				for(int k = nCount-1; k >=0;)
				{
					strTemp = strDest[k-1];					
					strTemp.Replace("item_", "");
					strTemp.Replace("Item_", "");
					if(strTemp == "Nothing")
					{
						k -= 2;
						continue;
					}

					if(k > 1)
						Temp22 += Common::Big2GB((LPSTR)(LPCTSTR)strTemp) + "��";
					else
						Temp22 += Common::Big2GB((LPSTR)(LPCTSTR)strTemp);
					k -= 2; 
				}
				Temp22 += "\n\n";
				StdFile.WriteString(Temp22);
			}
		}
	}

	StdFile.Close();
}


void CDropItemDlg::OnBnClickedButtonExe()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int i, j;
	struct DropsRange TmpDropsRange;
	CList <DropsRange, DropsRange&> *LCurDropsRange = &Common::LDropsRange;
	CString szLine;
	CStringArray strDest;
	CString strGap = ",";
	CString strLeft = _T("");
	CString strDropId;

	// ��ȡ��������
	// �����������֣�����ֵ����С��С��ֵ������ֵ������ֵ�ͱ���ֵֻ����һ��������
	CString strFixed, strGreater, strLess, strFixItem, strInc, strDec, strMul;
	int nFixed=-1, nGreater=-1, nLess=-1;
	int nInc=-1, nDec=-1, nMul=-1;
	m_CEditFixed.GetWindowTextA(strFixed);
	m_CEditGreater.GetWindowTextA(strGreater);
	m_CEditLess.GetWindowTextA(strLess);
	m_CEditFixItem.GetWindowTextA(strFixItem);
	m_CEditInc.GetWindowTextA(strInc);
	m_CEditDec.GetWindowTextA(strDec);
	m_CEditMul.GetWindowTextA(strMul);

	if(strFixItem.IsEmpty())
	{
		if((strFixed.IsEmpty() && (strGreater.IsEmpty() || strLess.IsEmpty()))
			|| (!strFixed.IsEmpty() && (!strGreater.IsEmpty() || !strLess.IsEmpty())))
		{
			AfxMessageBox("û����ȷ��д��ֵ,����ֵ��С��ֵ");
			return;
		}

		if(!strFixed.IsEmpty() && (!strGreater.IsEmpty() || !strLess.IsEmpty()))
		{
			AfxMessageBox("���ƺʹ���ֵ��С��ֵ����ͬʱ����");
			return;
		}
	}

	if(strInc.IsEmpty() && strDec.IsEmpty() && strMul.IsEmpty())
	{
		AfxMessageBox("δ�������ӡ����١����ʲ���");
		return;
	}

	if(!strFixed.IsEmpty())
		nFixed = _ttoi(strFixed);
	if(!strGreater.IsEmpty())
		nGreater = _ttoi(strGreater);
	if(!strLess.IsEmpty())
		nLess = _ttoi(strLess);

	if(!strInc.IsEmpty())
		nInc = _ttoi(strInc);
	else if(!strDec.IsEmpty())
		nDec = _ttoi(strDec);
	else
		nMul = _ttoi(strMul);

	if(nGreater > nLess)
	{
		CString temp11;
		temp11.Format("С��ֵ������С�ڴ���ֵ %d, %d", nGreater, nLess);
		AfxMessageBox(temp11);
		return;
	}

	CString strPathName="", strDistPathName="";
	::GetCurrentDirectory(1024,strPathName.GetBuffer(1024));
	strPathName.ReleaseBuffer();
	strDistPathName = strPathName + "\\DROPITEM-NEW-BAK.TXT";
	strPathName += "\\DROPITEM-NEW.TXT";

	if(!CopyFile(strPathName, strDistPathName, TRUE))
	{
		if (IDYES != AfxMessageBox("�����ļ��Ѿ����ڣ��Ƿ������" , MB_YESNO))
		{
			return;
		}
		else
		{
			CopyFile(strPathName, strDistPathName, FALSE);
		}
	}

	// ���λ�ȡ�����ҽ�����ֵ����ص���ʱListCtrl�У���������
	m_CListCtrlDropsTemp.DeleteAllItems();
	POSITION pos = LCurDropsRange->GetHeadPosition();
	for (i=0;i < LCurDropsRange->GetCount();i++)
	{
		strDest.RemoveAll();
		m_CListCtrlDropsTemp.DeleteAllItems();
		TmpDropsRange = LCurDropsRange->GetNext(pos);
		strDropId = TmpDropsRange.DropId;
		CString szLine = TmpDropsRange.DropRange;
		int nPos = szLine.Find(strGap);
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

		for(j = 0; j < strDest.GetCount();)
		{
			int nrow = m_CListCtrlDropsTemp.GetItemCount();//ȡ����
			int nItem = m_CListCtrlDropsTemp.InsertItem(nrow+1, _T(""));
			CString tempName = strDest[j++];
			CString tempName2 = tempName;
			tempName.Replace("item_", "");
			m_CListCtrlDropsTemp.SetItemText(nItem, 0, _T(Common::Big2GB((LPSTR)(LPCTSTR)tempName)));
			CString temp12 = strDest[j++];
			m_CListCtrlDropsTemp.SetItemText(nItem, 1, temp12);
			m_CListCtrlDropsTemp.SetItemText(nItem, 2, tempName2);
		}

		DoDropListSortTemp(strDropId);

		int nIncrementTable[100];

		if(!strFixItem.IsEmpty())  // �����趨ָ����Ʒ
		{
			if(nInc >= 0)
			{
				// �����������
				int nCounter = 0;
				int nCurDropRang, nDropRang;
				CString strItemTemp = "";
				int nrow = m_CListCtrlDropsTemp.GetItemCount();//ȡ����
				for(j=nrow-1;j>=0;j--)
				{
					nCurDropRang = _ttoi(m_CListCtrlDropsTemp.GetItemText(j,1));
					strItemTemp = m_CListCtrlDropsTemp.GetItemText(j,0);
					if(strFixItem == strItemTemp)  // ������ͬ�����޸�
					{
						nDropRang = nCurDropRang + nInc;

						// ���ӱ���
						m_CListCtrlDropsTemp.SetItemText(j, 1, Common::convert(nDropRang));
						nIncrementTable[nCounter++] = nDropRang - nCurDropRang;
					}
				}

				DoDropListSortTemp(strDropId);  // �������򣬲��Ҹ�������

				// �����������������ֵ
				for(j = 0; j < nCounter; j++)
				{
					nCurDropRang = _ttoi(m_CListCtrlDropsTemp.GetItemText(0,1));  // ȡ������ߵĽ��е���
					nDropRang = nCurDropRang - nIncrementTable[j];
					if(nDropRang < 0)
					{
						// ������뵽�������ô˵������Ҫ���¿������õ�������
						nDropRang = 0;
					}
					// ��������
					m_CListCtrlDropsTemp.SetItemText(0, 1, Common::convert(nDropRang));

					DoDropListSortTemp(strDropId);  // �������򣬲��Ҹ�������
				}

			}
			else if(nDec >= 0)
			{
				// �����������
				int nCounter = 0;
				int nCurDropRang, nDropRang;
				CString strItemTemp = "";
				int nrow = m_CListCtrlDropsTemp.GetItemCount();//ȡ����
				for(j=nrow-1;j>=0;j--)
				{
					nCurDropRang = _ttoi(m_CListCtrlDropsTemp.GetItemText(j,1));
					strItemTemp = m_CListCtrlDropsTemp.GetItemText(j,0);
					if(strFixItem == strItemTemp)  // ������ͬ�����޸�
					{
						nDropRang = nCurDropRang - nDec;

						// ���ӱ���
						m_CListCtrlDropsTemp.SetItemText(j, 1, Common::convert(nDropRang));
						nIncrementTable[nCounter++] = nDropRang - nCurDropRang;
					}
				}

				DoDropListSortTemp(strDropId);  // �������򣬲��Ҹ�������

				// �����������������ֵ
				for(j = 0; j < nCounter; j++)
				{
					nCurDropRang = _ttoi(m_CListCtrlDropsTemp.GetItemText(0,1));  // ȡ������ߵĽ��е���
					nDropRang = nCurDropRang - nIncrementTable[j];
					if(nDropRang < 0)
					{
						// ������뵽�������ô˵������Ҫ���¿������õ�������
						nDropRang = 0;
					}
					// ��������
					m_CListCtrlDropsTemp.SetItemText(0, 1, Common::convert(nDropRang));

					DoDropListSortTemp(strDropId);  // �������򣬲��Ҹ�������
				}

			}
			else  // nMul >= 0
			{
				// ÿ����һ��ֵ��Ҫ��Ӧ�ļ���һ��ֵ
				// �����������
				int nCounter = 0;
				int nCurDropRang, nDropRang;
				CString strItemTemp = "";
				int nrow = m_CListCtrlDropsTemp.GetItemCount();//ȡ����
				for(j=nrow-1;j>=0;j--)
				{
					nCurDropRang = _ttoi(m_CListCtrlDropsTemp.GetItemText(j,1));
					strItemTemp = m_CListCtrlDropsTemp.GetItemText(j,0);
					if(strFixItem == strItemTemp)  // ������ͬ�����޸�
					{
						nDropRang = nCurDropRang * nMul;

						// ���ӱ���
						m_CListCtrlDropsTemp.SetItemText(j, 1, Common::convert(nDropRang));
						nIncrementTable[nCounter++] = nDropRang - nCurDropRang;
					}
				}

				DoDropListSortTemp(strDropId);  // �������򣬲��Ҹ�������

				// �����������������ֵ
				for(j = 0; j < nCounter; j++)
				{
					nCurDropRang = _ttoi(m_CListCtrlDropsTemp.GetItemText(0,1));  // ȡ������ߵĽ��е���
					nDropRang = nCurDropRang - nIncrementTable[j];
					if(nDropRang < 0)
					{
						// ������뵽�������ô˵������Ҫ���¿������õ�������
						nDropRang = 0;
					}
					// ��������
					m_CListCtrlDropsTemp.SetItemText(0, 1, Common::convert(nDropRang));

					DoDropListSortTemp(strDropId);  // �������򣬲��Ҹ�������
				}
			}
		}
		else if(nFixed >= 0)
		{
			if(nInc >= 0)
			{
				// �����������
				int nCounter = 0;
				int nCurDropRang, nDropRang;
				int nrow = m_CListCtrlDropsTemp.GetItemCount();//ȡ����
				for(j=nrow-1;j>=0;j--)
				{
					nCurDropRang = _ttoi(m_CListCtrlDropsTemp.GetItemText(j,1));
					if(nCurDropRang == nFixed)
					{
						nDropRang = nCurDropRang + nInc;

						// ���ӱ���
						m_CListCtrlDropsTemp.SetItemText(j, 1, Common::convert(nDropRang));
						nIncrementTable[nCounter++] = nDropRang - nCurDropRang;
					}
				}

				DoDropListSortTemp(strDropId);  // �������򣬲��Ҹ�������

				// �����������������ֵ
				for(j = 0; j < nCounter; j++)
				{
					nCurDropRang = _ttoi(m_CListCtrlDropsTemp.GetItemText(0,1));  // ȡ������ߵĽ��е���
					nDropRang = nCurDropRang - nIncrementTable[j];
					if(nDropRang < 0)
					{
						// ������뵽�������ô˵������Ҫ���¿������õ�������
						nDropRang = 0;
					}
					// ��������
					m_CListCtrlDropsTemp.SetItemText(0, 1, Common::convert(nDropRang));

					DoDropListSortTemp(strDropId);  // �������򣬲��Ҹ�������
				}

			}
			else if(nDec >= 0)
			{
				AfxMessageBox("��ʱûʵ�֣�������������������");
				return;
			}
			else  // nMul >= 0
			{
				// ÿ����һ��ֵ��Ҫ��Ӧ�ļ���һ��ֵ
				// �����������
				int nCounter = 0;
				int nCurDropRang, nDropRang;
				int nrow = m_CListCtrlDropsTemp.GetItemCount();//ȡ����
				for(j=nrow-1;j>=0;j--)
				{
					nCurDropRang = _ttoi(m_CListCtrlDropsTemp.GetItemText(j,1));
					if(nCurDropRang == nFixed)
					{
						nDropRang = nCurDropRang * nMul;

						// ���ӱ���
						m_CListCtrlDropsTemp.SetItemText(j, 1, Common::convert(nDropRang));
						nIncrementTable[nCounter++] = nDropRang - nCurDropRang;
					}
				}

				DoDropListSortTemp(strDropId);  // �������򣬲��Ҹ�������

				// �����������������ֵ
				for(j = 0; j < nCounter; j++)
				{
					nCurDropRang = _ttoi(m_CListCtrlDropsTemp.GetItemText(0,1));  // ȡ������ߵĽ��е���
					nDropRang = nCurDropRang - nIncrementTable[j];
					if(nDropRang < 0)
					{
						// ������뵽�������ô˵������Ҫ���¿������õ�������
						nDropRang = 0;
					}
					// ��������
					m_CListCtrlDropsTemp.SetItemText(0, 1, Common::convert(nDropRang));

					DoDropListSortTemp(strDropId);  // �������򣬲��Ҹ�������
				}
			}
		}
		else
		{
			if(nInc >= 0)
			{
				// �����������
				int nCounter = 0;
				int nCurDropRang, nDropRang;
				int nrow = m_CListCtrlDropsTemp.GetItemCount();//ȡ����
				for(j=nrow-1;j>=0;j--)
				{
					nCurDropRang = _ttoi(m_CListCtrlDropsTemp.GetItemText(j,1));
					if(nCurDropRang > nGreater && nCurDropRang < nLess)
					{
						nDropRang = nCurDropRang + nInc;
						if(nDropRang > nLess)
							nDropRang = nLess;    // �������أ�������Ҫ����һ��������

						// ���ӱ���
						m_CListCtrlDropsTemp.SetItemText(j, 1, Common::convert(nDropRang));
						nIncrementTable[nCounter++] = nDropRang - nCurDropRang;
					}
				}

				DoDropListSortTemp(strDropId);  // �������򣬲��Ҹ�������

				// �����������������ֵ
				for(j = 0; j < nCounter; j++)
				{
					nCurDropRang = _ttoi(m_CListCtrlDropsTemp.GetItemText(0,1));  // ȡ������ߵĽ��е���
					nDropRang = nCurDropRang - nIncrementTable[j];
					if(nDropRang < 0)
					{
						// ������뵽�������ô˵������Ҫ���¿������õ�������
						nDropRang = 0;
					}
					// ��������
					m_CListCtrlDropsTemp.SetItemText(0, 1, Common::convert(nDropRang));

					DoDropListSortTemp(strDropId);  // �������򣬲��Ҹ�������
				}

			}
			else if(nDec >= 0)
			{
				AfxMessageBox("��ʱûʵ�֣�������������������");
				return;
			}
			else  // nMul >= 0
			{
				// ÿ����һ��ֵ��Ҫ��Ӧ�ļ���һ��ֵ
				// �����������
				int nCounter = 0;
				int nCurDropRang, nDropRang;
				int nrow = m_CListCtrlDropsTemp.GetItemCount();//ȡ����
				for(j=nrow-1;j>=0;j--)
				{
					nCurDropRang = _ttoi(m_CListCtrlDropsTemp.GetItemText(j,1));
					if(nCurDropRang > nGreater && nCurDropRang < nLess)
					{
						nDropRang = nCurDropRang * nMul;
						if(nDropRang > nLess)
							nDropRang = nLess;    // �������أ�������Ҫ����һ��������

						// ���ӱ���
						m_CListCtrlDropsTemp.SetItemText(j, 1, Common::convert(nDropRang));
						nIncrementTable[nCounter++] = nDropRang - nCurDropRang;
					}
				}

				DoDropListSortTemp(strDropId);  // �������򣬲��Ҹ�������

				// �����������������ֵ
				for(j = 0; j < nCounter; j++)
				{
					nCurDropRang = _ttoi(m_CListCtrlDropsTemp.GetItemText(0,1));  // ȡ������ߵĽ��е���
					nDropRang = nCurDropRang - nIncrementTable[j];
					if(nDropRang < 0)
					{
						// ������뵽�������ô˵������Ҫ���¿������õ�������
						nDropRang = 0;
					}
					// ��������
					m_CListCtrlDropsTemp.SetItemText(0, 1, Common::convert(nDropRang));

					DoDropListSortTemp(strDropId);  // �������򣬲��Ҹ�������
				}
			}
		}
	}

	OnBnClickedButtonSaveDrop();
}


void CDropItemDlg::OnBnClickedFix()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int i, j;
	struct DropsRange TmpDropsRange;
	CList <DropsRange, DropsRange&> *LCurDropsRange = &Common::LDropsRange;
	CString szLine;
	CStringArray strDest;
	CString strGap = ",";
	CString strLeft = _T("");
	CString strDropId;

	m_CListCtrlDropsTemp.DeleteAllItems();
	POSITION pos = LCurDropsRange->GetHeadPosition();
	for (i=0;i < LCurDropsRange->GetCount();i++)
	{
		strDest.RemoveAll();
		m_CListCtrlDropsTemp.DeleteAllItems();
		TmpDropsRange = LCurDropsRange->GetNext(pos);
		strDropId = TmpDropsRange.DropId;
		CString szLine = TmpDropsRange.DropRange;
		int nPos = szLine.Find(strGap);
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

		int count = 0;
		for(j = 1; j < strDest.GetCount();)
		{
			count += _ttoi(strDest[j]);
			j +=2;
		}

		CString strMsg;
		int nFixed = 100000000 - count;

		if(count!= 100000000 && abs(nFixed) < 10000)   //�����ܺ�С����һ�ڵĲ�ֵС��һ��������
		{
			for(j = 0; j < strDest.GetCount();)
			{
				int nrow = m_CListCtrlDropsTemp.GetItemCount();//ȡ����
				int nItem = m_CListCtrlDropsTemp.InsertItem(nrow+1, _T(""));
				CString tempName = strDest[j++];
				CString tempName2 = tempName;
				tempName.Replace("item_", "");
				m_CListCtrlDropsTemp.SetItemText(nItem, 0, _T(Common::Big2GB((LPSTR)(LPCTSTR)tempName)));
				CString temp12 = strDest[j++];
				m_CListCtrlDropsTemp.SetItemText(nItem, 1, temp12);
				m_CListCtrlDropsTemp.SetItemText(nItem, 2, tempName2);
			}

			DoDropListSortTemp(strDropId);

			int nCurDropRang;
			nCurDropRang = _ttoi(m_CListCtrlDropsTemp.GetItemText(0,1));  // ȡ������ߵĽ��е���

			// ��������
			m_CListCtrlDropsTemp.SetItemText(0, 1, Common::convert(nCurDropRang + nFixed));

			DoDropListSortTemp(strDropId);  // �������򣬲��Ҹ�������
		}
	}

	OnBnClickedButtonSaveDrop();
}
