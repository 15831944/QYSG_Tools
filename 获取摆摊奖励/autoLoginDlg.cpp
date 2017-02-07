
// autoLoginDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "autoLogin.h"
#include "autoLoginDlg.h"
#include "afxdialogex.h"
#include "CommDef.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#define WM_UPDATE_COUNT				(WM_USER+100)
#define WM_UPDATE_NAME				(WM_USER+101)

DWORD dwMineProcId;
HANDLE hMineProc;
HWND hMineWnd;
BOOL bStop;
int m_num;
struct sWindowInfo
{
	HWND hHwnd;
	HANDLE hProc;
	DWORD dwProcId;
	CString csWindowName;
	CString csClassName;
};
struct sWindowInfo m_WindowInfo[512];


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CautoLoginDlg 对话框



CautoLoginDlg::CautoLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CautoLoginDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CautoLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_GAME_CLIENT, m_CEditGameClient);
	DDX_Control(pDX, IDC_COMBO_PROCESS, m_CComboBoxProcess);
	DDX_Control(pDX, IDC_STATIC_COUNT, m_CStaticCount);
	DDX_Control(pDX, IDC_STATIC_NAME, m_CStaticName);
}

BEGIN_MESSAGE_MAP(CautoLoginDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_START, &CautoLoginDlg::OnBnClickedStart)
	ON_BN_CLICKED(IDC_BUTTON_GET_ACC_LIST, &CautoLoginDlg::OnBnClickedButtonGetAccList)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CautoLoginDlg::OnBnClickedButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_SCAN_GAME_CLIENT, &CautoLoginDlg::OnBnClickedButtonScanGameClient)
	ON_CBN_SELCHANGE(IDC_COMBO_PROCESS, &CautoLoginDlg::OnCbnSelchangeComboProcess)
	ON_BN_CLICKED(ID_BUTTON_OPEN, &CautoLoginDlg::OnBnClickedButtonOpen)
	ON_BN_CLICKED(IDC_BUTTON_GET_ACC_LIST2, &CautoLoginDlg::OnBnClickedButtonGetAccList2)
	ON_BN_CLICKED(IDC_BUTTON_STOP2, &CautoLoginDlg::OnBnClickedButtonStop2)
	ON_MESSAGE(WM_UPDATE_COUNT, OnUpdateCount)
	ON_MESSAGE(WM_UPDATE_NAME, OnUpdateName)
END_MESSAGE_MAP()


// CautoLoginDlg 消息处理程序

BOOL CALLBACK MyEnumWindowsProc(HWND hwnd, LPARAM lParam)
{
// 	if (::GetWindowLong(hwnd, GWL_STYLE)& WS_VISIBLE)
// 	{
// 		m_WindowInfo[m_num].hHwnd = hwnd;//record the HWND handle into array
// 		::GetWindowThreadProcessId(hwnd, &m_WindowInfo[m_num].dwProcId); //获取窗口进程ID
// 		CWnd* pWnd = CWnd::FromHandle(hwnd);
// 		pWnd->GetWindowText(m_WindowInfo[m_num].csWindowName);// 获取窗口名称
// 		//m_CComboBoxProcess.AddString(m_WindowInfo[m_num].csWindowName);
// 		m_num++;//count start
// 	}

	CautoLoginDlg* pView = (CautoLoginDlg*)lParam;
/*	CListCtrl& lc = pView->GetListCtrl();*/

	if (hwnd != pView->GetParentFrame()->GetSafeHwnd()) //不是本程序
	{
		DWORD dwStyle = GetWindowLong(hwnd, GWL_STYLE);
		if ((dwStyle & WS_OVERLAPPEDWINDOW) && (dwStyle & WS_VISIBLE))
		{
			CString csWinName;
			CWnd* pWnd = CWnd::FromHandle(hwnd);
			// 窗口标题
			pWnd->GetWindowText(csWinName);
			if (csWinName.Find("三国") >= 0 || csWinName.Find("online") >= 0 || csWinName.Find("loader") >= 0)
			{
				m_WindowInfo[m_num].hHwnd = hwnd;//record the HWND handle into array

				//保存窗口名
				m_WindowInfo[m_num].csWindowName = csWinName;
				//获取窗口进程ID
				::GetWindowThreadProcessId(hwnd, &m_WindowInfo[m_num].dwProcId);
				// 窗口类名
				::GetClassName(hwnd, m_WindowInfo[m_num].csClassName.GetBuffer(256), 256);
				m_num++;
			}
			
		}
	}

	return TRUE;
}

BOOL CautoLoginDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	CString strPathName = "";
	::GetCurrentDirectory(1024, strPathName.GetBuffer(1024));
	strPathName.ReleaseBuffer();
	strPathName += "\\online.dat";

	m_CEditGameClient.SetWindowText(strPathName);

	m_num = 0;
	EnumWindows(MyEnumWindowsProc, (LPARAM)this);//遍历窗口程序

	for (int i = 0; i < m_num; i++)
	{
		m_CComboBoxProcess.AddString(m_WindowInfo[i].csWindowName);
	}

	m_CComboBoxProcess.SetCurSel(0);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CautoLoginDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CautoLoginDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CautoLoginDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//获得游戏进程句柄（注意用完后要关闭）
HANDLE CautoLoginDlg::GetMineProc()
{
	hMineWnd = ::FindWindow(GAME_WINDOW_CLASS, GAME_WINDOW_TITLE); //查找窗口
	if (hMineWnd <= 0)
		return FALSE;

	::GetWindowThreadProcessId(hMineWnd, &dwMineProcId); //获取窗口进程ID
	if (!dwMineProcId)
		return FALSE;

	return ::OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwMineProcId); //打开进程句柄
}

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM param)
{

	DWORD id = GetWindowThreadProcessId(hwnd, NULL);
		if (id == (DWORD)param)
		{
			//do whatever we want to do
			hMineWnd = hwnd;
			return false;
		}
	return true;
}

void CautoLoginDlg::StartGame()
{
	CString StartFile = _T(GAME_START_FILE);
	CString g_CmdLine = _T(GAME_START_LINE);
	STARTUPINFO si = { sizeof(si) };
	PROCESS_INFORMATION pi;
	// TODO:  在此添加控件通知处理程序代码
	if (!CreateProcess(StartFile.GetBuffer(), g_CmdLine.GetBuffer(), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
	{
		AfxMessageBox(_T("启动失败,代码"));
		StartFile.ReleaseBuffer();
		g_CmdLine.ReleaseBuffer();
		return;
	}
	StartFile.ReleaseBuffer();
	g_CmdLine.ReleaseBuffer();

	if (WaitForInputIdle(pi.hProcess, INFINITE) == 0)
	{
		dwMineProcId = ::GetProcessId(pi.hProcess);	// ID任务管理器相同
		::EnumWindows(&EnumWindowsProc, pi.dwThreadId);
	}

	hMineProc = ::OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwMineProcId); //打开进程句柄
}

void CautoLoginDlg::OnBnClickedStart()
{
	// TODO:  在此添加控件通知处理程序代码
	StartGame();
	//GetMineProc();
	// 置前
	//::SetWindowPos(hMineWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

	/* 鼠标点击没有效果，应该还是要找关键call才行 */

// 	Sleep(1000);
// 	// 开启画面，随便一个鼠标点击
// 	::SendMessage(hMineWnd, WM_LBUTTONDOWN, 0, MAKELONG(160 - 4 + 8, 16 + 39 + 8));
// 	::SendMessage(hMineWnd, WM_LBUTTONUP, 1, MAKELONG(160 - 4 + 8, 16 + 39 + 8));
// 
// 	Sleep(1000);
// 	// 点击我同意
// 	::SendMessage(hMineWnd, WM_LBUTTONDOWN, 2, MAKELONG(570, 550));
// 	::SendMessage(hMineWnd, WM_LBUTTONDOWN, 2, MAKELONG(570, 550));
// 	Sleep(100);
// 	::SendMessage(hMineWnd, WM_LBUTTONUP, 3, MAKELONG(570, 550));
}

CString GB2Big(char*  sGb)
{
	char*  pszGbt = NULL;
	char*  pszGbs = NULL;
	wchar_t*  wszUnicode = NULL;
	char*  pszBig5 = NULL;
	CString  sBig5;
	int  iLen = 0;

	pszGbs = sGb;
	iLen = MultiByteToWideChar(936, 0, pszGbs, -1, NULL, 0);
	pszGbt = new  char[iLen * 2 + 1];
	LCMapString(0x0804, LCMAP_TRADITIONAL_CHINESE, pszGbs, -1, pszGbt, iLen * 2);
	wszUnicode = new  wchar_t[iLen + 1];
	MultiByteToWideChar(936, 0, pszGbt, -1, wszUnicode, iLen);
	iLen = WideCharToMultiByte(950, 0, (PWSTR)wszUnicode, -1, NULL, 0, NULL, NULL);
	pszBig5 = new  char[iLen + 1];
	WideCharToMultiByte(950, 0, (PWSTR)wszUnicode, -1, pszBig5, iLen, NULL, NULL);
	sBig5 = pszBig5;
	delete[]  wszUnicode;
	wszUnicode = NULL;
	delete[]  pszGbt;
	pszGbt = NULL;
	delete[]  pszBig5;
	pszBig5 = NULL;

	return  sBig5;
}

CString Big2GB(char*  sBig5)
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
	WideCharToMultiByte(936, 0, wbuf, -1, buf, sizeof(buf), NULL, NULL);

	//转换Gb码繁体到Gb码简体，使用API函数LCMapString
	LCMapString(0x0804, LCMAP_SIMPLIFIED_CHINESE, buf, -1, GbBuf, 2048);

	sRetBig5 = GbBuf;
	return  sRetBig5;
}


static DWORD WINAPI  DoGetAccList(void *pArg)
{
	//这里写上创建线程做什么的函数
	LPCVOID pBase = (LPCVOID)0x005C6BE0;
	__int32 pSaveFirstAccAdds, pFirstAccAdds;
	struct sAccData strAccData;

	CStringArray strNames;
	CList <CString, CString&> LAccNames;
	CString strTmp;
	BOOL bFound = FALSE;
	int nCount = 0;

	if (hMineProc <= 0)
	{
		return -1;
	}

	// 获取基址偏移后的地址值
	ReadProcessMemory(hMineProc, pBase, &pSaveFirstAccAdds, 4, NULL);
	pSaveFirstAccAdds = pSaveFirstAccAdds + 0x6F;		// 直接跳过第0个角色
	pFirstAccAdds = pSaveFirstAccAdds;

	bStop = FALSE;
	//读取角色信息
	while (!bStop)
	{
		pFirstAccAdds = pSaveFirstAccAdds;
		do{
			ReadProcessMemory(hMineProc, (void *)pFirstAccAdds, &strAccData, sizeof(struct sAccData), NULL);
			if (strAccData.cFlags[0] != 0 && strAccData.nStatus == 1024)   // 0x0400
			{
				// 插入的是不存在的
				strTmp = Big2GB(strAccData.cName);
				if (strNames.GetCount() == 0)
				{
					strNames.Add(strTmp);
					nCount = strNames.GetCount();
					AfxGetApp()->m_pMainWnd->SendMessage(WM_UPDATE_COUNT, 0, (LPARAM)(&nCount));
					continue;
				}

				bFound = FALSE;
				for (int i = 0; i < strNames.GetCount(); i++)
				{
					if (strTmp == strNames.GetAt(i))
					{
						bFound = TRUE;
					}
				}
				if (bFound == FALSE)
				{
					strNames.Add(strTmp);
					nCount = strNames.GetCount();
					AfxGetApp()->m_pMainWnd->SendMessage(WM_UPDATE_COUNT, 0, (LPARAM)(&nCount));
					AfxGetApp()->m_pMainWnd->SendMessage(WM_UPDATE_NAME, 0, (LPARAM)(&strTmp));
				}
				
// 				POSITION aaa = LAccNames.Find(Big2GB(strAccData.cName), 0);
// 				if (LAccNames.Find(Big2GB(strAccData.cName), 0) < 0)
// 				{
// 					LAccNames.AddHead(Big2GB(strAccData.cName));
// 				}
// 				LAccNames.AddHead(Big2GB(strAccData.cName));
			}
			pFirstAccAdds += 0x6F;

			// 垃圾判断语句
			if (strAccData.nStatus == 0 && strAccData.A1 == 0 && strAccData.A2 == 0
				&& strAccData.cFlags[0] == '\0' && strAccData.cFlags[1] == '\0')
				break;
		} while (TRUE);

		Sleep(10);
	}

	// 输出名单
	CString StrValue;
	CString strPathName = "";
	::GetCurrentDirectory(1024, strPathName.GetBuffer(1024));
	strPathName.ReleaseBuffer();
	strPathName += "\\奖励名单.txt";

	DWORD dwRe = GetFileAttributes(strPathName);
	if (dwRe != (DWORD)-1)
	{
		DeleteFile(strPathName);
	}
	//打开文件
	CStdioFile StdFile;
	StdFile.Open(strPathName, CFile::modeCreate | CFile::modeWrite | CFile::shareDenyNone);

	for (int i = 0; i < strNames.GetCount(); i++)
	{
		StdFile.WriteString(strNames.GetAt(i) + "\n");
	}

	StdFile.Close();

	//使用记事本打开 奖励名单.txt
	CString strCmdLine = "notepad.exe " + strPathName;
	::WinExec(strCmdLine.GetBuffer(), SW_SHOW);

	return 0;
}

void CautoLoginDlg::OnBnClickedButtonGetAccList()
{
	// TODO:  在此添加控件通知处理程序代码
	DWORD dwThreadID = 0;
	HANDLE hThread = CreateThread(NULL, 0, DoGetAccList, 0, NULL, &dwThreadID);	
}


void CautoLoginDlg::OnBnClickedButtonStop()
{
	// TODO:  在此添加控件通知处理程序代码
	bStop = TRUE;

	//::WinExec("notepad.exe F:\\Game\\自动发摆摊奖励-准备工作\\Automation\\autoLogin\\奖励名单.txt", SW_SHOW);
}

CString CautoLoginDlg::setEditVlaue()
{
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("All Files(*.*)||"));
	if (dlg.DoModal() == IDOK){
		CString PathName = dlg.GetPathName();
		if (PathName.IsEmpty() == 0){
			return PathName;
		}
	}
	return "";
}


void CautoLoginDlg::OnBnClickedButtonScanGameClient()
{
	// TODO:  在此添加控件通知处理程序代码
	//m_CEditGameClient.SetWindowText(_T(GAME_START_FILE));
	m_CEditGameClient.SetWindowText(setEditVlaue());
}


void CautoLoginDlg::OnCbnSelchangeComboProcess()
{
	// TODO:  在此添加控件通知处理程序代码
}


void CautoLoginDlg::OnBnClickedButtonOpen()
{
	// TODO:  在此添加控件通知处理程序代码
	int nCurSel = m_CComboBoxProcess.GetCurSel();
	::ShowWindow(m_WindowInfo[nCurSel].hHwnd, SW_SHOWNORMAL);
	::SetForegroundWindow(m_WindowInfo[nCurSel].hHwnd);
	hMineProc = ::OpenProcess(PROCESS_ALL_ACCESS, FALSE, m_WindowInfo[nCurSel].dwProcId); //打开进程句柄
}


void CautoLoginDlg::OnBnClickedButtonGetAccList2()
{
	// TODO:  在此添加控件通知处理程序代码
	DWORD dwThreadID = 0;
	HANDLE hThread = CreateThread(NULL, 0, DoGetAccList, 0, NULL, &dwThreadID);
}


void CautoLoginDlg::OnBnClickedButtonStop2()
{
	// TODO:  在此添加控件通知处理程序代码
	bStop = TRUE;
}


LRESULT CautoLoginDlg::OnUpdateCount(WPARAM wParam, LPARAM lParam)
{
	int nCount = *((int*)lParam);
	CString strCount;
	strCount.Format("%d", nCount);
	m_CStaticCount.SetWindowTextA(strCount);
	return 0;
}

LRESULT CautoLoginDlg::OnUpdateName(WPARAM wParam, LPARAM lParam)
{
	CString strName = *((CString*)lParam);
	m_CStaticName.SetWindowTextA(strName);
	return 0;
}
