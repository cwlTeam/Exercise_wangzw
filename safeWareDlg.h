
// safeWareDlg : ͷ�ļ�
//

#pragma once


// safeWareDlg �Ի���
class CsafeWareDlg : public CDialogEx
{
// ����
public:
	CsafeWareDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CNMD_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedSecret();
	CString Encrypt(CString S);
	CString Decrypt(CString S);
	CString GetMD(BYTE* pBuf, UINT nLength);
	afx_msg void OnBnClickedResult();
};

