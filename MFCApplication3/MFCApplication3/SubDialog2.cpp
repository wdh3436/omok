// SubDialog2.cpp : 구현 파일입니다.
// 설정 구현 다이얼로그

#include "stdafx.h"
#include "MFCApplication3.h"
#include "SubDialog2.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "MFCApplication3View.h"


// CSubDialog2 대화 상자입니다.

IMPLEMENT_DYNAMIC(CSubDialog2, CDialog)

CSubDialog2::CSubDialog2(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DIALOG2, pParent)
{

}

CSubDialog2::~CSubDialog2()
{
}

void CSubDialog2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSubDialog2, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CSubDialog2::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CSubDialog2::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CSubDialog2::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CSubDialog2::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CSubDialog2::OnBnClickedButton5)
END_MESSAGE_MAP()


// CSubDialog2 메시지 처리기입니다.


void CSubDialog2::OnBnClickedButton1()
{
	// 30초 설정
	CMainFrame *p = (CMainFrame*)AfxGetMainWnd();
	CMFCApplication3View *pView = (CMFCApplication3View*)p->GetActiveView();

	pView->timeSelect = 1;
}


void CSubDialog2::OnBnClickedButton2()
{
	// 60초 설정
	CMainFrame *p = (CMainFrame*)AfxGetMainWnd();
	CMFCApplication3View *pView = (CMFCApplication3View*)p->GetActiveView();

	pView->timeSelect = 2;
}


void CSubDialog2::OnBnClickedButton3()
{
	// 90초 설정
	CMainFrame *p = (CMainFrame*)AfxGetMainWnd();
	CMFCApplication3View *pView = (CMFCApplication3View*)p->GetActiveView();

	pView->timeSelect = 3;
}


void CSubDialog2::OnBnClickedButton4()
{
	// 3승 먼저
	CMainFrame *p = (CMainFrame*)AfxGetMainWnd();
	CMFCApplication3View *pView = (CMFCApplication3View*)p->GetActiveView();

	pView->winCount = 3;
}


void CSubDialog2::OnBnClickedButton5()
{
	// 5승 먼저
	CMainFrame *p = (CMainFrame*)AfxGetMainWnd();
	CMFCApplication3View *pView = (CMFCApplication3View*)p->GetActiveView();

	pView->winCount = 5;
}
