// PlayersDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "HC_SG_Editer.h"
#include "PlayersDlg.h"
#include "afxdialogex.h"
#include <stdio.h>
#include <stdlib.h>
#include <share.h>


// CPlayersDlg �Ի���

IMPLEMENT_DYNAMIC(CPlayersDlg, CDialogEx)

CPlayersDlg::CPlayersDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPlayersDlg::IDD, pParent)
{

}

CPlayersDlg::~CPlayersDlg()
{
}

void CPlayersDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_EXP_MUL, m_CEditExpMul);
	DDX_Control(pDX, IDC_EDIT_SKIP_EXP, m_CEditSkipExp);
	DDX_Control(pDX, IDC_LIST_ACCOUNT, m_CListCtrlAcc);
	DDX_Control(pDX, IDC_LIST_SKILLS, m_CListCtrlSkills);
	DDX_Control(pDX, IDC_EDIT_FIND, m_CEditFind);
	DDX_Control(pDX, IDC_EDIT_FIND_SKILL, m_CEditFindSkill);
	DDX_Control(pDX, IDC_EDIT_ACCOUNTS, m_CEditAccounts);
	DDX_Control(pDX, IDC_EDIT_SKILL_ID, m_CEditSkillID);
}


BEGIN_MESSAGE_MAP(CPlayersDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_EXE, &CPlayersDlg::OnBnClickedButtonExe)
	ON_BN_CLICKED(IDC_BUTTON_EXE2, &CPlayersDlg::OnBnClickedButtonExe2)
	ON_BN_CLICKED(IDC_BUTTON_DEL_SKILL, &CPlayersDlg::OnBnClickedButtonDelSkill)
	ON_NOTIFY(NM_CLICK, IDC_LIST_ACCOUNT, &CPlayersDlg::OnNMClickListAccount)
	ON_BN_CLICKED(IDC_BUTTON_ACC_NEXT, &CPlayersDlg::OnBnClickedButtonAccNext)
	ON_EN_CHANGE(IDC_EDIT_FIND, &CPlayersDlg::OnEnChangeEditFind)
	ON_EN_CHANGE(IDC_EDIT_FIND_SKILL, &CPlayersDlg::OnEnChangeEditFindSkill)
	ON_BN_CLICKED(IDC_BUTTON_SKILL_NEXT, &CPlayersDlg::OnBnClickedButtonSkillNext)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CPlayersDlg::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_DEL_ALL, &CPlayersDlg::OnBnClickedButtonDelAll)
END_MESSAGE_MAP()


// CPlayersDlg ��Ϣ�������


BOOL CPlayersDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	m_CListCtrlAcc.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_HEADERDRAGDROP);
	m_CListCtrlAcc.InsertColumn(0, _T("���"), LVCFMT_LEFT, 40);
	m_CListCtrlAcc.InsertColumn(1, _T("��ɫ����"), LVCFMT_LEFT, 80);
	m_CListCtrlAcc.InsertColumn(2, _T("ע���ʺ�"), LVCFMT_LEFT, 90);//������

	m_CListCtrlSkills.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_HEADERDRAGDROP);
	m_CListCtrlSkills.InsertColumn(0, _T("���"), LVCFMT_LEFT, 40);
	m_CListCtrlSkills.InsertColumn(1, _T("����ID"), LVCFMT_LEFT, 50);//��Ӧskills.dat�е�����
	m_CListCtrlSkills.InsertColumn(2, _T("������"), LVCFMT_LEFT, 0);//������
	m_CListCtrlSkills.InsertColumn(3, _T("ʹ�õȼ�"), LVCFMT_LEFT, 60);//������
	m_CListCtrlSkills.InsertColumn(4, _T("�ȼ�����"), LVCFMT_LEFT, 60);//������

	m_CEditExpMul.SetWindowTextA("3");
	m_CEditSkipExp.SetWindowTextA("2");

	Common::ServerPath = "D:\\sgserver\\";

	LoadAccSkills();
	LoadAccAttr();
	DisPlayAccSkills(1);

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CPlayersDlg::LoadAccAttr()
{
	CString strPathName;
	struct AccAttr TmpAccAtrr;
	CList <AccAttr, AccAttr&> *LCurAccAttr = &Common::LAccAttr;
	int ret = 0;

	Common::GetAccAttr();
	//GetSoldierAttr();

	m_CListCtrlAcc.DeleteAllItems();

	POSITION pos = LCurAccAttr->GetHeadPosition();
	for (int i = 0; i < LCurAccAttr->GetCount(); i++)
	{
		TmpAccAtrr = LCurAccAttr->GetNext(pos);

		int nrow = m_CListCtrlAcc.GetItemCount();//ȡ����
		int nItem = m_CListCtrlAcc.InsertItem(nrow + 1, _T(""));
		m_CListCtrlAcc.SetItemText(nItem, 0, Common::convert(TmpAccAtrr.nIndex));
		m_CListCtrlAcc.SetItemText(nItem, 1, _T(Common::Big2GB(TmpAccAtrr.Name)));
		m_CListCtrlAcc.SetItemText(nItem, 2, _T(TmpAccAtrr.Account));

	}

//	m_CButtonLoad.SetWindowText("�ض�����");
// 	pos = Common::LAccAttr.GetHeadPosition();
// 	if (pos != NULL)
// 		DisplayAttr(pos);
}

void CPlayersDlg::LoadAccSkills()
{
	Common::GetAccSkills();
}

void CPlayersDlg::DisPlayAccSkills(int nIndex)
{
	m_CListCtrlSkills.DeleteAllItems();
	struct AccSkills TmpAccSkills;
	POSITION pos = Common::LAccSkills.FindIndex(nIndex);
	TmpAccSkills = Common::LAccSkills.GetNext(pos);

	for (int i = 0; i < 551; i++)
	{
		int nrow = m_CListCtrlSkills.GetItemCount();//ȡ����
		int nItem = m_CListCtrlSkills.InsertItem(nrow + 1, _T(""));
		m_CListCtrlSkills.SetItemText(nItem, 0, Common::convert(i));
		m_CListCtrlSkills.SetItemText(nItem, 1, Common::convert(i));
		m_CListCtrlSkills.SetItemText(nItem, 2, "");
		m_CListCtrlSkills.SetItemText(nItem, 3, Common::convert(TmpAccSkills.SkillsUsing[i]));
		m_CListCtrlSkills.SetItemText(nItem, 4, Common::convert(TmpAccSkills.SkillsHad[i]));
	}
}


void CPlayersDlg::OnBnClickedButtonExe()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CStringArray strResult;

	CString strPathName="", strNewFile;
	::GetCurrentDirectory(1024,strPathName.GetBuffer(1024));
	strPathName.ReleaseBuffer();
	strPathName += "\\PLAYERS.TXT";

	CString szLine = "";
	CString strTemp = "";

	//����ļ��Ƿ����
	DWORD dwRe = GetFileAttributes(strPathName);
	if ( dwRe != (DWORD)-1 )
	{
		//ShellExecute(NULL, NULL, strFilePath, NULL, NULL, SW_RESTORE); 
	}
	else 
	{
		CString errormessage;
		errormessage.Format("%s �ļ������ڣ�", strPathName);
		AfxMessageBox(errormessage);
		return;
	}

	CString strMul;
	int nMul = 1;

	m_CEditExpMul.GetWindowTextA(strMul);

	if(!strMul.IsEmpty() && Common::IsDigital((LPCTSTR)strMul))
		nMul = _ttoi(strMul);

	//���ļ�
	CStdioFile StdFile;
	StdFile.Open(strPathName,CFile::modeRead | CFile::shareDenyNone);

	//���ж�ȡ�ַ���
	while( StdFile.ReadString( szLine ) )
	{
		if(szLine.Find("exp = ") == 0)  // get it
		{
			CString strRight = szLine.Right(szLine.GetLength() - 6);
			if(_ttoi(strRight) < 1000000)
			{
				strTemp.Format("exp = %d\n", _ttoi(strRight) * nMul);
				strResult.Add(strTemp);
				continue;
			}
			else
			{
				strResult.Add(szLine + "\n");
				continue;
			}

			
		}

		strResult.Add(szLine + "\n");
	}
	//�ر��ļ�
	StdFile.Close();

	DeleteFile(strPathName);

	StdFile.Open(strPathName,CFile::modeCreate | CFile::modeWrite | CFile::shareDenyNone);

	for(int i=0; i< strResult.GetCount(); i++)
	{
		StdFile.WriteString(strResult[i]);
	}
	StdFile.Close();
	AfxMessageBox("�޸����");
}


void CPlayersDlg::OnBnClickedButtonExe2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CStringArray strResult;

	CString strPathName="", strNewFile;
	::GetCurrentDirectory(1024,strPathName.GetBuffer(1024));
	strPathName.ReleaseBuffer();
	strNewFile = strPathName + "\\PLAYERS-new.TXT";
	strPathName += "\\PLAYERS.TXT";

	CString szLine = "";
	CString strTemp = "";

	//����ļ��Ƿ����
	DWORD dwRe = GetFileAttributes(strPathName);
	if ( dwRe != (DWORD)-1 )
	{
		//ShellExecute(NULL, NULL, strFilePath, NULL, NULL, SW_RESTORE); 
	}
	else 
	{
		CString errormessage;
		errormessage.Format("%s �ļ������ڣ�", strPathName);
		AfxMessageBox(errormessage);
		return;
	}

	CString strMul;
	int nMul = 1;

	m_CEditSkipExp.GetWindowTextA(strMul);

	if(!strMul.IsEmpty() && Common::IsDigital((LPCTSTR)strMul))
		nMul = _ttoi(strMul);

	//���ļ�
	CStdioFile StdFile;
	StdFile.Open(strPathName,CFile::modeRead | CFile::shareDenyNone);

	//���ж�ȡ�ַ���
	while( StdFile.ReadString( szLine ) )
	{
		if(szLine.Find("skill_exp = ") == 0)  // get it
		{
			CString strRight = szLine.Right(szLine.GetLength() - 12);
			if(_ttoi(strRight) < 100000)
			{
				strTemp.Format("skill_exp = %d\n", _ttoi(strRight) * nMul);
				strResult.Add(strTemp);
				continue;
			}
			else
			{
				strResult.Add(szLine + "\n");
				continue;
			}			
		}

		strResult.Add(szLine + "\n");
	}
	//�ر��ļ�
	StdFile.Close();

	DeleteFile(strPathName);

	StdFile.Open(strPathName,CFile::modeCreate | CFile::modeWrite | CFile::shareDenyNone);

	for(int i=0; i< strResult.GetCount(); i++)
	{
		StdFile.WriteString(strResult[i]);
	}
	StdFile.Close();

	AfxMessageBox("�޸����");
}


void CPlayersDlg::OnBnClickedButtonDelSkill()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	// �õ�ѡ�еĽ�ɫ���
	int AccListIndex = m_CListCtrlAcc.GetSelectionMark();
	if (AccListIndex == -1) return;

	// �õ�ѡ�е�Skill ID
	int SkillListIndex = m_CListCtrlSkills.GetSelectionMark();
	if (SkillListIndex == -1) return;

	struct AccSkills TmpAccSkills;
	POSITION pos = Common::LAccSkills.FindIndex(AccListIndex);
	POSITION tmpPos = pos;
	TmpAccSkills = Common::LAccSkills.GetNext(pos);

	TmpAccSkills.SkillsUsing[SkillListIndex] = 1;
	TmpAccSkills.SkillsHad[SkillListIndex] = 0;

	Common::LAccSkills.SetAt(tmpPos, TmpAccSkills);

	DisPlayAccSkills(AccListIndex);
}


void CPlayersDlg::OnNMClickListAccount(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int ListIndex = m_CListCtrlAcc.GetSelectionMark();
	CList <AccAttr, AccAttr&> *LCurAccAttr = &Common::LAccAttr;
	if (ListIndex == -1) return;
	POSITION pos = LCurAccAttr->FindIndex(ListIndex);
	if (pos != NULL)
		DisPlayAccSkills(ListIndex);
	*pResult = 0;
}


void CPlayersDlg::OnBnClickedButtonAccNext()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString strKey;
	int iColumnNum, iRowCount;
	char chTemp[32];
	int ListIndex = 0;
	int iCurListIndex = m_CListCtrlAcc.GetSelectionMark();

	m_CEditFind.GetWindowText(strKey);
	if (strKey.IsEmpty()) return;

	iColumnNum = m_CListCtrlAcc.GetHeaderCtrl()->GetItemCount();
	iRowCount = m_CListCtrlAcc.GetItemCount();

	int j = iCurListIndex + 1;
	do
	{
		memset(chTemp, 0, 32);
		for (int i = 0; i < iColumnNum; i++)
		{
			m_CListCtrlAcc.GetItemText(j, i, chTemp, 32);
			if (strstr(chTemp, strKey))
			{
				ListIndex = j;
				goto BreakLoop;
			}
		}
		if (j == iRowCount)
			j = -1;
	} while (j != iCurListIndex && (j++ || j != 0));
BreakLoop:
	m_CListCtrlAcc.SetFocus();
	m_CListCtrlAcc.SetItemState(ListIndex, LVIS_SELECTED, LVIS_SELECTED);
	m_CListCtrlAcc.SetSelectionMark(ListIndex);
	m_CListCtrlAcc.EnsureVisible(ListIndex, FALSE);
	::SendMessage(m_CListCtrlAcc.m_hWnd, LVM_SETEXTENDEDLISTVIEWSTYLE,
		LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
}


void CPlayersDlg::OnEnChangeEditFind()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString strKey;
	int iColumnNum, iRowCount;
	char chTemp[32];
	int ListIndex = 0;

	m_CEditFind.GetWindowText(strKey);
	if (strKey.IsEmpty()) return;

	iColumnNum = m_CListCtrlAcc.GetHeaderCtrl()->GetItemCount();
	iRowCount = m_CListCtrlAcc.GetItemCount();

	for (int j = 0; j < iRowCount; j++)
	{
		memset(chTemp, 0, 32);
		for (int i = 0; i < iColumnNum; i++)
		{
			m_CListCtrlAcc.GetItemText(j, i, chTemp, 32);
			if (strstr(chTemp, strKey))
			{
				ListIndex = j;
				goto BreakLoop;
			}
		}
	}
BreakLoop:
	m_CListCtrlAcc.SetFocus();
	m_CListCtrlAcc.SetItemState(ListIndex, LVIS_SELECTED, LVIS_SELECTED);
	m_CListCtrlAcc.SetSelectionMark(ListIndex);
	m_CListCtrlAcc.EnsureVisible(ListIndex, FALSE);
	::SendMessage(m_CListCtrlAcc.m_hWnd, LVM_SETEXTENDEDLISTVIEWSTYLE,
		LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);

	m_CEditFind.SetFocus();
}


void CPlayersDlg::OnEnChangeEditFindSkill()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString strKey;
	int iColumnNum, iRowCount;
	char chTemp[32];
	int ListIndex = 0;

	m_CEditFindSkill.GetWindowText(strKey);
	if (strKey.IsEmpty()) return;

	iColumnNum = m_CListCtrlSkills.GetHeaderCtrl()->GetItemCount();
	iRowCount = m_CListCtrlSkills.GetItemCount();

	for (int j = 0; j < iRowCount; j++)
	{
		memset(chTemp, 0, 32);
		for (int i = 0; i < iColumnNum; i++)
		{
			m_CListCtrlSkills.GetItemText(j, i, chTemp, 32);
			if (strstr(chTemp, strKey))
			{
				ListIndex = j;
				goto BreakLoop;
			}
		}
	}
BreakLoop:
	m_CListCtrlSkills.SetFocus();
	m_CListCtrlSkills.SetItemState(ListIndex, LVIS_SELECTED, LVIS_SELECTED);
	m_CListCtrlSkills.SetSelectionMark(ListIndex);
	m_CListCtrlSkills.EnsureVisible(ListIndex, FALSE);
	::SendMessage(m_CListCtrlSkills.m_hWnd, LVM_SETEXTENDEDLISTVIEWSTYLE,
		LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);

	m_CEditFindSkill.SetFocus();
}


void CPlayersDlg::OnBnClickedButtonSkillNext()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString strKey;
	int iColumnNum, iRowCount;
	char chTemp[32];
	int ListIndex = 0;
	int iCurListIndex = m_CListCtrlSkills.GetSelectionMark();

	m_CEditFindSkill.GetWindowText(strKey);
	if (strKey.IsEmpty()) return;

	iColumnNum = m_CListCtrlSkills.GetHeaderCtrl()->GetItemCount();
	iRowCount = m_CListCtrlSkills.GetItemCount();

	int j = iCurListIndex + 1;
	do
	{
		memset(chTemp, 0, 32);
		for (int i = 0; i < iColumnNum; i++)
		{
			m_CListCtrlSkills.GetItemText(j, i, chTemp, 32);
			if (strstr(chTemp, strKey))
			{
				ListIndex = j;
				goto BreakLoop;
			}
		}
		if (j == iRowCount)
			j = -1;
	} while (j != iCurListIndex && (j++ || j != 0));
BreakLoop:
	m_CListCtrlSkills.SetFocus();
	m_CListCtrlSkills.SetItemState(ListIndex, LVIS_SELECTED, LVIS_SELECTED);
	m_CListCtrlSkills.SetSelectionMark(ListIndex);
	m_CListCtrlSkills.EnsureVisible(ListIndex, FALSE);
	::SendMessage(m_CListCtrlSkills.m_hWnd, LVM_SETEXTENDEDLISTVIEWSTYLE,
		LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
}

void CPlayersDlg::OnBnClickedButtonSave()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	if (IDYES != AfxMessageBox("��ȷ����ǰ����������崻�״̬��", MB_YESNO))
		return;

	CString strPathName = Common::ServerPath + "DataBase\\saves\\skill.dat";
	CString strBakPathName = Common::ServerPath + "DataBase\\saves\\skill_bak.dat";

	//����ļ��Ƿ����
	DWORD dwRe = GetFileAttributes(strPathName);
	if (dwRe != (DWORD)-1)
	{
		//ShellExecute(NULL, NULL, strFilePath, NULL, NULL, SW_RESTORE); 
	}
	else
	{
		CString errormessage;
		errormessage.Format(strPathName + " �ļ������ڣ�");
		Common::Log(Error, errormessage);
		return;
	}

	CopyFile(strPathName, strBakPathName, FALSE);

	unsigned __int32 nSeek = 0;
	int ret = 0, i;

	nSeek = 32;

	FILE *fp = NULL;
	//���ļ�
	fp = _fsopen((LPSTR)(LPCTSTR)strPathName, "r+b", _SH_DENYNO);

	if (!fp)
	{
		AfxMessageBox("���ļ�ʧ�ܣ�");
		return;
	}

	fseek(fp, nSeek, SEEK_SET);

	struct AccSkills TmpAccSkills;
	CList <AccSkills, AccSkills&> *LCurAccSkills = &Common::LAccSkills;

	POSITION pos = LCurAccSkills->GetHeadPosition();
	for (int i = 0; i < LCurAccSkills->GetCount(); i++)
	{
		TmpAccSkills = LCurAccSkills->GetNext(pos);

		ret = fwrite(&TmpAccSkills, sizeof(unsigned char), sizeof(TmpAccSkills), fp);

		if (ret < sizeof(TmpAccSkills))
		{
			AfxMessageBox("д��ʧ�ܣ�һ������������󣬻����б��ݣ�����");
			fclose(fp);
			return;
		}
	}

	fclose(fp);
}


void CPlayersDlg::OnBnClickedButtonDelAll()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CStringArray strAccounts;
	CString strEditAccs;
	m_CEditAccounts.GetWindowTextA(strEditAccs);
	if (strEditAccs.IsEmpty())
		strEditAccs = "lidawai;qq123456;a6961964;znxmorborl;ww123456;missing34;easy1461;jhx99140235;10xipo98;10xipo99;dsl2003;dsl2008;19890929aa;dsl2001;10xipo97;allenmou;easy14610;jhx8116;ming891;qweqweqq;gang899;yun89025;fengyun329;monkey;allenmou2;allenmou1;kingjiange;allenmou3;dsl2000";
	Common::CStringGap(strEditAccs, &strAccounts, "", ";", 0);

	CStringArray strSkills;
	CString tmpSkillIDs;
	m_CEditSkillID.GetWindowTextA(tmpSkillIDs);
	if (tmpSkillIDs.IsEmpty())
		tmpSkillIDs = "208;86;187;459;102;207;189;94;89;191;206;91;196;103;201;99;93;92;188;202;58;88;190;192;195;193;101;59;96";
	Common::CStringGap(tmpSkillIDs, &strSkills, "", ";", 0);

	struct AccAttr TmpAccAtrr;
	CList <AccAttr, AccAttr&> *LCurAccAttr = &Common::LAccAttr;
	struct AccSkills TmpAccSkills;

	for (int i = 0; i < strAccounts.GetCount(); i++)
	{
		POSITION pos = LCurAccAttr->GetHeadPosition();
		int j;
		for (j = 0; j < LCurAccAttr->GetCount(); j++)
		{
			TmpAccAtrr = LCurAccAttr->GetNext(pos);
			if (strAccounts[i] == TmpAccAtrr.Account)
				break;
		}

		if (j == LCurAccAttr->GetCount())
			continue;


		POSITION pos2 = Common::LAccSkills.FindIndex(j);
		POSITION tmpPos = pos2;
		TmpAccSkills = Common::LAccSkills.GetNext(pos2);

		int m_SkillID;
		for (int k = 0; k < strSkills.GetCount(); k++)
		{
			m_SkillID = atoi(strSkills[k]);
			TmpAccSkills.SkillsUsing[m_SkillID] = 1;
			TmpAccSkills.SkillsHad[m_SkillID] = 0;
			Common::LAccSkills.SetAt(tmpPos, TmpAccSkills);
		}
	}
}
