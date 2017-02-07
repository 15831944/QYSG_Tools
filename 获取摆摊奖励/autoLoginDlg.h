
// autoLoginDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


#define GAME_WINDOW_CLASS  TEXT("UJGAME_SANOL")		// ��������
#define GAME_WINDOW_TITLE  TEXT("����ȺӢ��OnLine")					// ���ڱ���

#define BASE_ADDR    0x005C6BE0

#define FIRST_DATA_ADDR    0x005C6BE0   // 0x005C6BE0 + 0x6F  ��0����ɫΪ�գ����Դӵ�һ����ɫ��ʼ���ڴ�


#pragma pack(1)
struct sAccData
{
	unsigned __int16 nStatus;		// ����״̬������1024��ʾ�ڰ�̯
	unsigned __int16 A1;
	unsigned __int16 A2;
	char cFlags[2];		// ���������ֵ��˵����ȡ�ĵ����ڴ��а�������������
	char A3[30];			// һЩ��ֵ��ʱ���������а�����ɫ����
	char cName[16];		// ��ɫ���֣�15���ֽڣ�ĩβһ��Ӧ��ʼ��Ϊ0x00
	char cUnknowData[57];		// 111 - 54 = 57,���ǵ���ʲô����ʱ����
};
#pragma pack() 

// CautoLoginDlg �Ի���
class CautoLoginDlg : public CDialogEx
{
// ����
public:
	CautoLoginDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_AUTOLOGIN_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

public:

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	void CautoLoginDlg::StartGame();
	afx_msg void OnBnClickedStart();
	HANDLE CautoLoginDlg::GetMineProc();
	afx_msg void OnBnClickedButtonGetAccList();
	afx_msg void OnBnClickedButtonStop();
	CString CautoLoginDlg::setEditVlaue();
	afx_msg void OnBnClickedButtonScanGameClient();
	CEdit m_CEditGameClient;
	CComboBox m_CComboBoxProcess;
	afx_msg void OnCbnSelchangeComboProcess();
	afx_msg void OnBnClickedButtonOpen();
	afx_msg void OnBnClickedButtonGetAccList2();
	afx_msg void OnBnClickedButtonStop2();
	LRESULT CautoLoginDlg::OnUpdateCount(WPARAM wParam, LPARAM lParam);
	LRESULT CautoLoginDlg::OnUpdateName(WPARAM wParam, LPARAM lParam);
	CStatic m_CStaticCount;
	CStatic m_CStaticName;
};
