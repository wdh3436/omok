#pragma once


// CSubDialog ��ȭ �����Դϴ�.

class CSubDialog : public CDialog
{
	DECLARE_DYNAMIC(CSubDialog)

public:
	CSubDialog(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CSubDialog();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBlack(); 
	afx_msg void OnBnClickedWhite();
	afx_msg void OnBnClickedHuman();
	afx_msg void OnBnClickedInit();
};
