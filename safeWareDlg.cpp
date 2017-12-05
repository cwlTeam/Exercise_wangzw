
// safeWareDlg.cpp : ʵ���ļ�
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


// safeWareDlg �Ի���



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


// CsafeWareDlg ��Ϣ�������

BOOL CsafeWareDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CsafeWareDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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


//����
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


//����
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
