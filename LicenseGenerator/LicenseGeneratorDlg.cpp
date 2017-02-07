
// LicenseGeneratorDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "LicenseGenerator.h"
#include "LicenseGeneratorDlg.h"
#include "afxdialogex.h"
#include <math.h>
#include   <stdio.h>   
#include   <stdlib.h>   
#include   <httpext.h>   
#include   <windef.h>   
#include   <Nb30.h>
#pragma comment(lib, "Netapi32.lib")
#pragma warning(disable:4996)

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLicenseGeneratorDlg 对话框
const unsigned char cArray[1024] = {
	52,   13,   45,   11,   32,   46,   77,    6,   57,   51,   50,  127,   45,  108,  120,  122, 
	23,   30,  127,   40,   91,  111,  102,  109,   58,   87,   46,   61,  126,   83,   85,   93, 
	34,  113,   70,  103,   45,   15,  124,  126,   69,   60,   37,   40,   62,   17,   45,   95, 
	99,  105,   92,   61,   25,   52,  114,   13,   58,  116,  110,  114,    2,   87,   76,   52, 
	50,   13,   31,  102,    6,   11,  115,   98,   75,   66,   73,   76,   89,   59,    1,   10, 
	77,   25,   76,   31,   29,   26,    8,   18,   47,   32,   67,  103,   32,   79,   27,  118, 
	48,   66,   89,   52,  101,  113,   46,    6,   96,   18,   69,  116,  114,   76,   37,   18, 
	95,    6,  123,   79,    8,   38,   39,   87,   28,  101,   27,  113,   72,   92,   17,   81, 
	95,   82,   77,   28,  108,   11,   19,  117,  105,   38,   25,   50,    8,  124,    8,    6, 
	46,   88,    2,  108,   41,   77,  113,    8,   48,   90,   57,    5,   16,    5,   36,   54, 
	58,   88,   56,   17,   23,   58,  125,   45,   58,   97,   35,   86,   77,   26,   23,   98, 
	120,  19,   88,   95,   34,   97,   38,   65,   51,   18,   86,  111,   59,   72,   66,  109, 
	2,    51,   67,   35,   16,  126,   48,  110,   51,   65,   80,   69,   43,  117,   16,   79, 
	47,  112,  118,   17,  126,   91,   83,   71,   87,   17,   25,   67,   23,   36,   16,   83, 
	109,   6,   34,   10,  103,  117,   32,    3,   57,   12,   66,   83,   59,   37,   36,  124, 
	39,   50,   49,   81,   32,   60,    5,   84,   40,  120,   43,   42,   78,   58,   27,   81, 
	12,   49,   77,   51,   63,   44,  110,   75,   16,   40,   23,   85,   49,  127,   78,   69, 
	80,  111,   49,   42,   16,    2,   81,   73,  127,   60,   70,   16,  118,   65,   69,   52, 
	6,    37,   51,   51,   96,   17,   36,   86,  122,   36,   54,   18,   24,   12,  102,   12, 
	82,   56,    3,   73,   80,   64,   89,   62,   92,   21,   13,   97,   13,   59,   91,  124, 
	44,  109,   73,   62,  100,   72,   65,   73,  119,   49,   24,   13,   64,   54,  113,   75, 
	80,   20,  105,   48,  109,  124,   52,   55,   92,   43,  119,   65,   13,   46,   33,   49, 
	47,   42,  118,   53,  103,   73,   45,   51,   73,   94,  110,   32,   66,   32,  103,  122, 
	78,  113,  117,   79,   68,   81,   48,   40,   19,  111,  102,  112,   15,   24,   62,  120, 
	47,   50,  116,    7,    4,   23,    1,   94,   17,  115,  126,  114,  116,  116,  107,  115, 
	16,   36,   32,   36,    3,  114,   20,   58,  121,   22,   89,   16,   77,    4,   59,   69, 
	94,    1,  115,   85,  104,  104,   36,  104,   23,   62,   12,   48,  114,   40,   79,  115, 
	123,  82,   56,  105,  112,   52,   97,   98,   76,   78,   31,  122,   75,   38,  111,   10, 
	45,   17,   32,  120,    2,  100,   42,  100,   62,   59,   46,   97,    4,   86,   15,   24, 
	79,  106,   19,   23,  127,  126,   49,  123,  119,   21,   88,  125,  106,   21,   55,  101, 
	35,   79,  126,  123,   32,   98,   84,    1,   16,   18,  119,   46,   25,   90,   47,   31, 
	21,   65,  120,   33,    8,  103,   60,   14,  105,   57,  106,   29,   62,   49,   12,   84, 
	82,   88,    4,   77,    4,   73,  117,   87,   12,   65,   97,   19,   33,   55,  109,   53, 
	13,   27,   31,   49,   18,    7,  116,   23,   42,   83,   13,  108,   61,  118,   53,   21, 
	52,   51,    8,   36,   12,  104,   82,   76,   94,   23,   45,    9,   77,   96,   32,  112, 
	123,  92,   25,   72,   65,   91,   93,   10,   25,    9,   40,  117,   93,    2,  115,   63, 
	6,    92,  119,  124,  108,   19,   36,   34,   81,   70,   96,   24,   62,   79,   88,   18, 
	85,  114,   98,   39,   27,   30,   80,   99,  114,  118,    1,    4,  100,    3,   66,   57, 
	21,   91,   18,   80,  102,  111,   80,   41,   55,   88,    8,   48,  114,  102,   44,    9, 
	8,    32,  102,   70,  116,  108,  122,   15,   21,  111,  121,   61,   94,   60,   65,  110, 
	34,   43,   67,   69,   32,   28,   25,   50,   93,   53,   78,   62,  110,   33,   32,   17, 
	56,   36,  122,   55,  112,   92,  101,   80,   86,   56,   36,   16,   70,   65,   96,   77, 
	80,   56,   47,   25,   42,   43,   10,  110,  109,   98,   71,   80,   40,   39,   39,   42, 
	13,   79,   96,   21,    2,  120,   72,   93,   54,   52,   78,  122,   73,   10,   86,   72, 
	50,   55,    5,    3,   60,  127,   38,   16,   31,   54,   99,   35,   15,   96,   38,   91, 
	68,    6,   59,   81,  102,   74,  119,   79,   39,   68,   48,   57,   36,   16,   80,   85, 
	119, 119,   71,   20,   84,   13,   56,   31,   52,   12,   78,   38,  105,   29,  126,   69, 
	120, 102,   67,   21,  116,   71,   68,   60,   36,   50,   18,  124,   31,   74,   49,   17, 
	89,   80,   95,    9,   67,   42,   59,   90,  102,   78,   90,  118,   88,  116,   43,  120, 
	66,  114,   96,   23,   71,   80,  110,    7,   74,   83,  103,  124,   39,  125,   22,  105, 
	102,   9,    6,   62,   32,   55,   83,   55,  121,   95,   21,   67,  120,   60,   79,    2, 
	71,   37,   14,   70,    9,  108,   16,  103,  116,  121,   47,   35,   84,   51,   12,   52, 
	49,    8,   37,   67,   82,   55,   46,   29,   51,   46,   46,   10,  110,    2,   93,  109, 
	23,   88,   87,   52,   34,   48,   12,   48,  126,   49,   23,   24,   74,   17,  112,  104, 
	9,   101,  119,  112,   10,   45,   54,   61,   15,   82,    8,   39,  102,   40,  100,  109, 
	112,  54,    4,   92,   97,   35,   75,   88,  127,   44,   38,   59,  109,  103,   42,  125, 
	62,  110,   24,  106,   60,   56,   40,  114,   50,  127,   24,  115,   63,   45,   41,   65, 
	20,    2,   66,    1,   18,   18,  116,   82,   54,   95,  100,   85,  102,   24,   34,   99, 
	115,  32,  106,   13,   76,   34,    6,  112,   79,   28,  102,   38,   14,   84,  115,   68, 
	126,  88,  114,   89,   60,   94,   27,   43,   98,   96,   41,   66,   38,   91,    7,  121, 
	2,    44,  123,   13,   74,   42,   78,   63,  127,   97,  110,   88,  104,   38,   66,  116, 
	33,   19,  124,  104,   61,   15,   22,   15,   44,   23,   97,   21,   46,   61,   82,   84, 
	74,   61,  108,  112,  101,   94,  123,   45,  106,   77,   75,    9,   92,   13,   95,   87, 
	64,   11,    1,   96,  117,  107,  106,   82,  109,   79,   52,   10,   29,   62,   65,   0
};

#pragma pack(1)
struct sLicense
{
	unsigned __int8 A1;
	unsigned __int16 nMachineCodeLen;
	unsigned __int8 A2;
	unsigned __int16 nStartDateLen;
	unsigned __int8 A3;
	unsigned __int16 nEndDateLen;
	unsigned __int8 A4;
	unsigned __int16 nNameLen;
	unsigned __int8 A5;
	unsigned __int16 nBakLen;
	unsigned char A6[9];
	unsigned char Data[1000];
};
#pragma pack() 


CLicenseGeneratorDlg::CLicenseGeneratorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLicenseGeneratorDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLicenseGeneratorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_MACHINE_CODE, mCEditMachineCode);
	DDX_Control(pDX, IDC_EDIT_START_DATE, mCEditStartDate);
	DDX_Control(pDX, IDC_EDIT_END_DATE, mCEditEndDate);
	DDX_Control(pDX, IDC_EDIT_NAME, mCEditName);
}

BEGIN_MESSAGE_MAP(CLicenseGeneratorDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_Generator, &CLicenseGeneratorDlg::OnBnClickedGenerator)
	ON_BN_CLICKED(ID_Decode, &CLicenseGeneratorDlg::OnBnClickedDecode)
END_MESSAGE_MAP()


// CLicenseGeneratorDlg 消息处理程序

BOOL CLicenseGeneratorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	ShowWindow(SW_MINIMIZE);

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CLicenseGeneratorDlg::OnPaint()
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
HCURSOR CLicenseGeneratorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CLicenseGeneratorDlg::OnBnClickedGenerator()
{
	// TODO: 在此添加控件通知处理程序代码
	CString csMachineCode, csStartDate, csEndDate, csName;
	mCEditMachineCode.GetWindowTextA(csMachineCode);
	mCEditStartDate.GetWindowTextA(csStartDate);
	mCEditEndDate.GetWindowTextA(csEndDate);
	mCEditName.GetWindowTextA(csName);

	struct sLicense srcLicense;

	memset(&srcLicense, '\0', sizeof(srcLicense));
	memcpy(&srcLicense, cArray, sizeof(cArray));

	srcLicense.nMachineCodeLen = csMachineCode.GetLength();
	srcLicense.nStartDateLen = csStartDate.GetLength();
	srcLicense.nEndDateLen = csEndDate.GetLength();
	srcLicense.nNameLen = csName.GetLength();
	srcLicense.nBakLen = 1;

	int nIndex = srcLicense.A1;

	for(int i=0; i < srcLicense.nMachineCodeLen; i++)
	{
		srcLicense.Data[nIndex] = csMachineCode.GetAt(i);
		nIndex += 2;
	}
	nIndex += srcLicense.A2;

	for(int i=0; i < srcLicense.nStartDateLen; i++)
	{
		srcLicense.Data[nIndex] = csStartDate.GetAt(i);
		nIndex += 2;
	}
	nIndex += srcLicense.A3;

	for(int i=0; i < srcLicense.nEndDateLen; i++)
	{
		srcLicense.Data[nIndex] = csEndDate.GetAt(i);
		nIndex += 2;
	}
	nIndex += srcLicense.A4;

	for(int i=0; i < srcLicense.nNameLen; i++)
	{
		srcLicense.Data[nIndex] = csName.GetAt(i);
		nIndex += 2;
	}
	nIndex += srcLicense.A5;

	memset(cKey, '\0', sizeof(cKey));
	memcpy(cKey, &srcLicense, sizeof(srcLicense));

	Encrypt();

	CString StrValue;
	CString strPathName="";
	CString strPath="";
	::GetCurrentDirectory(1024,strPathName.GetBuffer(1024));
	strPathName.ReleaseBuffer();
	strPathName += "\\License.exe";

	DWORD dwRe = GetFileAttributes(strPathName);
	if ( dwRe != (DWORD)-1 )
	{
		DeleteFile(strPathName);
	}

	//打开文件
	FILE   *pOutFile   =   fopen( strPathName, "w+b ");
	fwrite((void*)cKey,   1,   1024,   pOutFile);
	fclose(pOutFile);

}

void CLicenseGeneratorDlg::OnBnClickedDecode()
{
	// TODO: 在此添加控件通知处理程序代码
	CString PathName;

	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,_T("All Files(*.exe)|*.exe||"));
	if(dlg.DoModal()==IDOK){
		PathName=dlg.GetPathName();
		if(PathName.IsEmpty()){
			return ;
		}
	}
	struct sLicense	TmpLicense;

	CFile iFile(PathName, CFile::modeRead | CFile::modeNoTruncate | CFile::shareDenyNone);  
	CArchive iar(&iFile, CArchive::load); 

	iar.Read(&TmpLicense,sizeof(TmpLicense));

	iar.Close();
	iFile.Close();

	Decode(&TmpLicense);
}

void CLicenseGeneratorDlg::Encrypt()
{

}

void CLicenseGeneratorDlg::Decode(struct sLicense *TmpLicense)
{
	CString csMachineCode = "", csStartDate = "", csEndDate = "", csName = "";

	int nIndex = TmpLicense->A1;

	for(int i=0; i < TmpLicense->nMachineCodeLen; i++)
	{
		csMachineCode += TmpLicense->Data[nIndex];
		nIndex += 2;
	}
	nIndex += TmpLicense->A2;

	for(int i=0; i < TmpLicense->nStartDateLen; i++)
	{
		csStartDate += TmpLicense->Data[nIndex];
		nIndex += 2;
	}
	nIndex += TmpLicense->A3;

	for(int i=0; i < TmpLicense->nEndDateLen; i++)
	{
		csEndDate += TmpLicense->Data[nIndex];
		nIndex += 2;
	}
	nIndex += TmpLicense->A4;

	for(int i=0; i < TmpLicense->nNameLen; i++)
	{
		csName += TmpLicense->Data[nIndex];
		nIndex += 2;
	}

	mCEditMachineCode.SetWindowTextA(csMachineCode);
	mCEditStartDate.SetWindowTextA(csStartDate);
	mCEditEndDate.SetWindowTextA(csEndDate);
	mCEditName.SetWindowTextA(csName);
}

