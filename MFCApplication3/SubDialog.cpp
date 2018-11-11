// SubDialog.cpp : ���� �����Դϴ�.
// ��鼱��â�� ǥ���ϴ� ���̾Ʒα�.

#include "stdafx.h"
#include "MFCApplication3.h"
#include "SubDialog.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "MFCApplication3View.h"
// CSubDialog ��ȭ �����Դϴ�.

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


// CSubDialog �޽��� ó�����Դϴ�.


void CSubDialog::OnBnClickedBlack()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CMainFrame *p = (CMainFrame*)AfxGetMainWnd();
	CMFCApplication3View *pView = (CMFCApplication3View*)p->GetActiveView();
	
	pView->m_sunseo = true; // ���� ������ ���´�
	
	pView->m_computerStart = true;
	pView->m_start = true;
	pView->player_black = true;

	pView->Invalidate(false);
	OnDestroy();
	OnOK();
}


void CSubDialog::OnBnClickedWhite()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CMainFrame *p = (CMainFrame*)AfxGetMainWnd();
	CMFCApplication3View *pView = (CMFCApplication3View*)p->GetActiveView();

	pView->m_sunseo = true;  // ���� ������ ���´�

	pView->m_computerStart = true;
	pView->m_start = true;
	pView->player_black = false;

	pView->Invalidate(false);
	OnDestroy();
	OnOK();
}


void CSubDialog::OnBnClickedHuman()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CMainFrame *p = (CMainFrame*)AfxGetMainWnd();
	CMFCApplication3View *pView = (CMFCApplication3View*)p->GetActiveView();
	CMFCApplication3Doc *pDoc = (CMFCApplication3Doc*)pView->GetDocument();

	for (int row = 0; row < 19; row++)
		for (int col = 0; col < 19; col++)
			pDoc->baduk[row][col] = 0;

	pView->Invalidate(false);
}
