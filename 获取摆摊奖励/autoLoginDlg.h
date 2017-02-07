
// autoLoginDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


#define GAME_WINDOW_CLASS  TEXT("UJGAME_SANOL")		// 窗口类名
#define GAME_WINDOW_TITLE  TEXT("三国群英传OnLine")					// 窗口标题

#define BASE_ADDR    0x005C6BE0

#define FIRST_DATA_ADDR    0x005C6BE0   // 0x005C6BE0 + 0x6F  第0个角色为空，所以从第一个角色开始读内存


#pragma pack(1)
struct sAccData
{
	unsigned __int16 nStatus;		// 任务状态，等于1024表示在摆摊
	unsigned __int16 A1;
	unsigned __int16 A2;
	char cFlags[2];		// 如果这里有值则说明读取的到的内存中包含有人物属性
	char A3[30];			// 一些数值暂时不处理，其中包含角色坐标
	char cName[16];		// 角色名字，15个字节，末尾一个应该始终为0x00
	char cUnknowData[57];		// 111 - 54 = 57,不是到是什么，暂时不管
};
#pragma pack() 

// CautoLoginDlg 对话框
class CautoLoginDlg : public CDialogEx
{
// 构造
public:
	CautoLoginDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_AUTOLOGIN_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

public:

	// 生成的消息映射函数
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
