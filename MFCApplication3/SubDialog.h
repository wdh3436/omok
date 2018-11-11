#pragma once


// CSubDialog 대화 상자입니다.

class CSubDialog : public CDialog
{
	DECLARE_DYNAMIC(CSubDialog)

public:
	CSubDialog(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CSubDialog();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBlack(); 
	afx_msg void OnBnClickedWhite();
	afx_msg void OnBnClickedHuman();
	afx_msg void OnBnClickedInit();
};
