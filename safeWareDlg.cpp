
// safeWareDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "safeWare.h"
#include "safeWareDlg.h"
#include "afxdialogex.h"
#include "symmetry.h"
#include "MD5.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// safeWareDlg 对话框



CsafeWareDlg::CsafeWareDlg(CWnd* pParent /*=NULL*/)
: CDialogEx(CsafeWareDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CsafeWareDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CsafeWareDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SECRET, &CsafeWareDlg::OnBnClickedSecret)
	ON_BN_CLICKED(IDC_RESULT, &CsafeWareDlg::OnBnClickedResult)
END_MESSAGE_MAP()


// CsafeWareDlg 消息处理程序

BOOL CsafeWareDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CsafeWareDlg::OnPaint()
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
HCURSOR CsafeWareDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CsafeWareDlg::OnBnClickedSecret()
{
	CString str,result,m_password;
	GetDlgItemText(IDC_PASSWORD,str);
	result=Encrypt(str);
	SetDlgItemText(IDC_SCREAT1,result);
	UpdateData();
	GetDlgItemText(IDC_PASSWORD,m_password);
	str = GetMD((BYTE *)m_password.GetBuffer(0),m_password.GetLength());
	SetDlgItemText(IDC_SCREAT2,str);
	UpdateData(false);
}
CString CsafeWareDlg::GetMD(BYTE* pBuf, UINT nLength)
{
	CString str;
	str=MD5::GetMD5(pBuf,nLength);
	return str;
}


//加密
CString CsafeWareDlg::Encrypt(CString S)
{
	CString Str,Str1,Result;
	WORD K=123456789;
	int i,j;
	Str=S;
	for(i=0;i<S.GetLength();i++)
	{
		Str.SetAt(i,S.GetAt(i)+K);
	}
	S=Str;
	for(i=0;i<S.GetLength();i++)
	{
		j=(BYTE)S.GetAt(i);
		Str1="01";
		Str1.SetAt(0,65+j/26);
		Str1.SetAt(1,65+j%26);
		Result+=Str1;
	}
	return Result;
}


//解密
CString CsafeWareDlg::Decrypt(CString S)
{
	CString Str,Str1,Result;
	WORD K=123456789;
	int i,j;
	for(i=0;i<S.GetLength()/2;i++)
	{
		j=((BYTE)S.GetAt(2*i)-65)*26;
		j+=(BYTE)S.GetAt(2*i+1)-65;
		Str='0';
		Str.SetAt(0,j);
		Result+=Str;
	}
	S=Result;
	for(i=0;i<S.GetLength();i++)
	{
		Result.SetAt(i,(BYTE)S.GetAt(i)-K);
	}
	return Result;
}

void CsafeWareDlg::OnBnClickedResult()
{
	CString str,result;
	GetDlgItemText(IDC_SCREAT1,str);
	result=Decrypt(str);
	SetDlgItemText(IDC_RESULT1,result);
	GetDlgItemText(IDC_PASSWORD,str);
	SetDlgItemText(IDC_RESULT2,str);
}
