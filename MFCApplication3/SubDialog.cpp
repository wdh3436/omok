// SubDialog.cpp : 구현 파일입니다.
// 흑백선택창을 표시하는 다이아로그.

#include "stdafx.h"
#include "MFCApplication3.h"
#include "SubDialog.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "MFCApplication3View.h"
// CSubDialog 대화 상자입니다.

IMPLEMENT_DYNAMIC(CSubDialog, CDialog)

CSubDialog::CSubDialog(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DIALOG1, pParent)
{

}

CSubDialog::~CSubDialog()
{
}

void CSubDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSubDialog, CDialog)
	ON_BN_CLICKED(IDC_BLACK, &CSubDialog::OnBnClickedBlack)
	ON_BN_CLICKED(IDC_WHITE, &CSubDialog::OnBnClickedWhite)
	ON_BN_CLICKED(IDC_HUMAN, &CSubDialog::OnBnClickedHuman)
	ON_BN_CLICKED(IDC_INIT, &CSubDialog::OnBnClickedInit)
END_MESSAGE_MAP()


// CSubDialog 메시지 처리기입니다.


void CSubDialog::OnBnClickedBlack()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMainFrame *p = (CMainFrame*)AfxGetMainWnd();
	CMFCApplication3View *pView = (CMFCApplication3View*)p->GetActiveView();
	
	pView->m_sunseo = true; // 흑이 선수를 놓는다
	
	pView->m_computerStart = true;
	pView->m_start = true;
	pView->player_black = true;

	pView->Invalidate(false);
	OnDestroy();
	OnOK();
}


void CSubDialog::OnBnClickedWhite()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMainFrame *p = (CMainFrame*)AfxGetMainWnd();
	CMFCApplication3View *pView = (CMFCApplication3View*)p->GetActiveView();

	pView->m_sunseo = true;  // 흑이 선수를 놓는다

	pView->m_computerStart = true;
	pView->m_start = true;
	pView->player_black = false;

	pView->Invalidate(false);
	OnDestroy();
	OnOK();
}


void CSubDialog::OnBnClickedHuman()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMainFrame *p = (CMainFrame*)AfxGetMainWnd();
	CMFCApplication3View *pView = (CMFCApplication3View*)p->GetActiveView();

	pView->m_computerStart = false;
	pView->m_start = true;
	pView->Invalidate(false);
	pView->player_black = true;
	pView->m_sunseo = true;
	OnDestroy();
	OnOK();
}


void CSubDialog::OnBnClickedInit()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMainFrame *p = (CMainFrame*)AfxGetMainWnd();
	CMFCApplication3View *pView = (CMFCApplication3View*)p->GetActiveView();
	CMFCApplication3Doc *pDoc = (CMFCApplication3Doc*)pView->GetDocument();

	for (int row = 0; row < 19; row++)
		for (int col = 0; col < 19; col++)
			pDoc->baduk[row][col] = 0;

	pView->Invalidate(false);
}
