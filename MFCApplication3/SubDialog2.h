#pragma once


// CSubDialog2 대화 상자입니다.

class CSubDialog2 : public CDialog
{
	DECLARE_DYNAMIC(CSubDialog2)

public:
	CSubDialog2(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CSubDialog2();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
};
