#pragma once


// CSubDialog2 ��ȭ �����Դϴ�.

class CSubDialog2 : public CDialog
{
	DECLARE_DYNAMIC(CSubDialog2)

public:
	CSubDialog2(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CSubDialog2();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
};
