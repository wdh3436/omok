
// MFCApplication3View.cpp : CMFCApplication3View Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "MFCApplication3.h"
#endif

#include "MFCApplication3Doc.h"
#include "MFCApplication3View.h"
#include "afxwin.h"
#include "mmsystem.h"
#include "windows.h"
#include "time.h"
#include "string.h"


#ifdef _DEBUG
#define  new DEBUG_NEW
#endif

#pragma comment(lib,"winmm.lib")




IMPLEMENT_DYNCREATE(CMFCApplication3View, CFormView)

BEGIN_MESSAGE_MAP(CMFCApplication3View, CFormView)
	
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(btn1, &CMFCApplication3View::OnClickedStart) // ���۹�ư �޽��� ó��
	
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEMOVE()
	
	ON_WM_TIMER()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEHOVER()
END_MESSAGE_MAP()

// CMFCApplication3View ����/�Ҹ�



CMFCApplication3View::CMFCApplication3View()
	: CFormView(IDD_MFCAPPLICATION3_FORM)
	, player_black(false)
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	m_start = false;
	m_row = -1;
	m_col = -1;
	c_row = -1;
	c_col = -1;
	b_win = 0;
	w_win = 0;
	winCount = 3;
	timeSelect = 2;
	TimeSet = 60;
	m_computerStart = false;
	player_black = true;
	mouseCount = 0;
	trace = 0;
	for (int row = 0; row < 19; row++)
		for (int col = 0; col < 19; col++)
			ibaduk[row][col] = 0;
}

CMFCApplication3View::~CMFCApplication3View()
{
	
}

void CMFCApplication3View::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BOOL CMFCApplication3View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CFormView::PreCreateWindow(cs);
}

void CMFCApplication3View::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

	
}


// CMFCApplication3View ����

#ifdef _DEBUG
void CMFCApplication3View::AssertValid() const
{
	CFormView::AssertValid();
}

void CMFCApplication3View::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CMFCApplication3Doc* CMFCApplication3View::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCApplication3Doc)));
	return (CMFCApplication3Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFCApplication3View �޽��� ó����

	

void CMFCApplication3View::OnClickedStart()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	
	m_start = true;
	
	subDlg.DoModal();
	
}

void CMFCApplication3View::OnClickedConfig()
{
	subDlg2.DoModal();

}

void CMFCApplication3View::BackGround2(CDC *pDC) {    // 2��° ���
	if (m_start) {
		//�������1,backgroundmusic���ȵ� ������ �񵿱�ļҸ��� ��� �۵�����
		/* CString szSoundPath = _T("res\\Sound\\BackGroundMusic1.wav");
		PlaySound(szSoundPath, AfxGetInstanceHandle(), SND_ASYNC | SND_LOOP); */  // ����

		CDC memDC;
		CBitmap bitmap, *poldbitmap;;
		

		bitmap.LoadBitmapW(IDB_BACKGROUND2);
		memDC.CreateCompatibleDC(pDC);

		poldbitmap = memDC.SelectObject(&bitmap);

		pDC->StretchBlt(0, 0, 1057, 793, &memDC, 0, 0, 1057, 793, SRCCOPY);
		memDC.SelectObject(poldbitmap);
	}

}
void CMFCApplication3View::OnDraw(CDC *pDC) {

	/*
	CString szSoundPath = _T("res\\Sound\\�޴�Ŭ���Ҹ�1.wav");
	PlaySound(szSoundPath, AfxGetInstanceHandle(), SND_ASYNC | SND_LOOP); // ����
	*/

	/*
	CString szSoundPath = _T("res\\Sound\\�������1.wav");
	PlaySound(szSoundPath, AfxGetInstanceHandle(), SND_ASYNC | SND_LOOP);

	PlaySound((LPCSTR)MAKEINTRESOURCE(IDR_WAVE1), NULL, SND_ASYNC | SND_RESOURCE);



	BOOL PlaySound(
	LPCSTR pszSound,
	HMODULE hmod,
	DWORD fdwSound
	);
	*/
	
	
	
CMFCApplication3Doc *pDoc = GetDocument();
	CBrush blackbrush, whitebrush, yellowbrush, *pold;
	int row, col;
	int x, y, px, py, ex, ey;
	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	CBitmap bitmap, *poldbitmap;
	CBitmap startBmp, configBmp;
	//TimeSet = 10; // Ÿ�̸� �ʱⰪ
	pDC->SetBkMode(TRANSPARENT);

	bool change;

	if (m_start) {
		

		CMFCApplication3View::BackGround2(pDC);

	


		CString buf1, buf2;
		if (m_computerStart) {
			if (player_black) {
				buf1.Format(_T("�÷��̾� %d�� %d��"), b_win + w_win, b_win);
			}
			else {
				buf1.Format(_T("��ǻ�� %d�� %d��"), b_win + w_win, w_win);
			}
		}
		else {
			buf1.Format(_T("���� %d�� %d��"), b_win + w_win, b_win);
		}
		pDC->TextOutW(50,350 , buf1);

		if (m_computerStart) {
			if (player_black) {
				buf2.Format(_T("��ǻ�� %d�� %d��"), b_win + w_win, w_win);
			}
			else {
				buf2.Format(_T("�÷��̾� %d�� %d��"), b_win + w_win, b_win);
			}
		}
		else {
			buf2.Format(_T("���� %d�� %d��"), b_win + w_win, w_win);
		}
		pDC->TextOutW(850, 350, buf2);
		CBitmap player1, player2, com, BAEK, BAEK_RED, HYUK, HYUK_RED, RESET;
		

		RESET.LoadBitmap(IDB_RESET);
		CBitmap BACK;
		BACK.LoadBitmap(IDB_BACK);
		player1.LoadBitmap(IDB_PLAYER1);
		player2.LoadBitmap(IDB_PLAYER2);
		com.LoadBitmap(IDB_COM);
		
		HYUK.LoadBitmap(IDB_HYUK);
		HYUK_RED.LoadBitmap(IDB_HYUK_RED);
		BAEK.LoadBitmap(IDB_BAEK);
		BAEK_RED.LoadBitmap(IDB_BAEK_RED);


		switch (timeSelect) {
		case 1:
			TimeSet = 30;
			break;
		case 2:
			TimeSet = 60;
			break;
		case 3:
			TimeSet = 90;
			break;
		}
		
		
		if (m_sunseo) { // Ÿ�̸� ���
			SetTimer(1, 1000, NULL);
			

		}
		//else {
			//SetTimer(1, 100, NULL);
			//m_set = true;

		//}
		poldbitmap = memDC.SelectObject(&BACK);
		pDC->StretchBlt(70, 500, 148, 101, &memDC, 0, 0, 148, 101, SRCCOPY);
		


		poldbitmap = memDC.SelectObject(&RESET);
		pDC->StretchBlt(850, 500, 148, 101, &memDC, 0, 0, 148, 101, SRCCOPY);


		if (player_black) {
			if (m_computerStart) {
				poldbitmap = memDC.SelectObject(&player1);  // �÷��̾�1 ������
				pDC->BitBlt(50, 200, 128, 128, &memDC, 0, 0, SRCCOPY);
				poldbitmap = memDC.SelectObject(&com);   // ��ǻ�� ������
				pDC->BitBlt(850, 200, 128, 128, &memDC, 0, 0, SRCCOPY);
			}
			else {
				poldbitmap = memDC.SelectObject(&player1);  // �÷��̾�1 ������
				pDC->BitBlt(50, 200, 128, 128, &memDC, 0, 0, SRCCOPY);
				poldbitmap = memDC.SelectObject(&player2);   // �÷��̾�2 ������
				pDC->BitBlt(850, 200, 128, 128, &memDC, 0, 0, SRCCOPY);
			}
		}
		else {
			if (m_computerStart) {
				poldbitmap = memDC.SelectObject(&com);  //��ǻ�� ������
				pDC->BitBlt(50, 200, 128, 128, &memDC, 0, 0, SRCCOPY);
				poldbitmap = memDC.SelectObject(&player1);   // �÷��̾�2 ������
				pDC->BitBlt(850, 200, 128, 128, &memDC, 0, 0, SRCCOPY);
			}
			else {
				poldbitmap = memDC.SelectObject(&player1);  //�÷��̾�2 ������
				pDC->BitBlt(50, 200, 128, 128, &memDC, 0, 0, SRCCOPY);
				poldbitmap = memDC.SelectObject(&player2);   //�÷��̾�1 ������
				pDC->BitBlt(850, 200, 128, 128, &memDC, 0, 0, SRCCOPY);
			}	
			
		}
		
		if (m_sunseo) {// ��� ����ǥ��
			if (player_black) {
				poldbitmap = memDC.SelectObject(&HYUK_RED);   // �� ����
				pDC->TransparentBlt(50, 100, 100, 100, &memDC, 0, 0, 100, 100, RGB(255, 255, 255));
				poldbitmap = memDC.SelectObject(&BAEK);   // ��
														  //pDC->BitBlt(850, 100, 100, 100, &memDC, 0, 0, SRCCOPY);
				pDC->TransparentBlt(850, 100, 100, 100, &memDC, 0, 0, 100, 100, RGB(255, 255, 255));
			}
			else {
				poldbitmap = memDC.SelectObject(&HYUK);   // ��
				pDC->TransparentBlt(50, 100, 100, 100, &memDC, 0, 0, 100, 100, RGB(255, 255, 255));
				poldbitmap = memDC.SelectObject(&BAEK_RED);   // �� ����
				pDC->TransparentBlt(850, 100, 100, 100, &memDC, 0, 0, 100, 100, RGB(255, 255, 255));
			}
		}
		else {
			if (player_black) {
				poldbitmap = memDC.SelectObject(&HYUK);   // ��
				pDC->TransparentBlt(50, 100, 100, 100, &memDC, 0, 0, 100, 100, RGB(255, 255, 255));
				poldbitmap = memDC.SelectObject(&BAEK_RED);   // �� ����
				pDC->TransparentBlt(850, 100, 100, 100, &memDC, 0, 0, 100, 100, RGB(255, 255, 255));
			}
			else {
				poldbitmap = memDC.SelectObject(&HYUK_RED);   // �� ����
				pDC->TransparentBlt(50, 100, 100, 100, &memDC, 0, 0, 100, 100, RGB(255, 255, 255));
				poldbitmap = memDC.SelectObject(&BAEK);   // ��
				pDC->TransparentBlt(850, 100, 100, 100, &memDC, 0, 0, 100, 100, RGB(255, 255, 255));
			}
		}
		memDC.SelectObject(poldbitmap);

		// delete[] startBtn; �� �ȵǴ��� ��
		CBitmap murgi;
		murgi.LoadBitmapW(IDB_CONFIG);
		poldbitmap = memDC.SelectObject(&murgi);   // �� ����
		pDC->BitBlt(70, 500, 128, 101, &memDC, 0, 0,SRCCOPY);

		memDC.SelectObject(poldbitmap);

		const int width = 30;

		int start_x = 250;    //�ٵ����� ���۵Ǵ� ȭ�� ��ǥ
		int start_y = 100;

		 //��� ���� ��� �귯�� ����


		px = start_x;               //50�ȼ� // �ٵ��� ù��ǥ
		py = start_y;	            //50�ȼ�

		ex = start_x + width * 18;  //590�ȼ� // �ٵ��� ����ǥ
		ey = start_y + width * 18;  //590�ȼ�

		yellowbrush.CreateSolidBrush(RGB(255, 255, 0));  
		blackbrush.CreateSolidBrush(RGB(0, 0, 0));
		whitebrush.CreateSolidBrush(RGB(255, 255, 255));
				
		CMFCApplication3View::OmokGround(pDC);
		

		for (x = 0; x < 19; x++)
		{
			px = start_x + x*width;
			py = start_y;
			ex = start_x + x*width;
			ey = start_y + width * 18;  // ���μ� �߱�

			pDC->MoveTo(px, py);
			pDC->LineTo(ex, ey);
		}

		for (y = 0; y < 19; y++)
		{
			px = start_x;
			py = start_y + y * width;
			ex = start_x + width * 18;
			ey = start_y + y * width;      // ���μ� �߱�

			pDC->MoveTo(px, py);
			pDC->LineTo(ex, ey);
		}
		CBrush brush, *poldbrush; // ȭ�� �׸���
		brush.CreateSolidBrush(RGB(0, 0, 0));
		poldbrush = pDC->SelectObject(&brush);
		pDC->Ellipse(336, 186, 344, 194);
		pDC->Ellipse(516, 186, 524, 194);
		pDC->Ellipse(696, 186, 704, 194);
		pDC->Ellipse(336, 366, 344, 374);
		pDC->Ellipse(516, 366, 524, 374);
		pDC->Ellipse(696, 366, 704, 374);
		pDC->Ellipse(336, 546, 344, 554);
		pDC->Ellipse(516, 546, 524, 554);
		pDC->Ellipse(696, 546, 704, 554);

		if (!player_black && m_computerStart) pDoc->baduk[9][9] = 2;

		if (player_black == true) {
			for (row = 0; row < 19; row++) {             //�ٵϵ� ��� 1�̸� �浹 , 2�̸� �鵹�� ���� �׸�
				for (col = 0; col < 19; col++) {
					if (pDoc->baduk[row][col] == 1) {
						px = start_x + width * col - width / 2;
						py = start_y + width * row - width / 2;
						ex = px + width;
						ey = py + width;
						pold = pDC->SelectObject(&blackbrush);
						pDC->Ellipse(px, py, ex, ey);
						pDC->SelectObject(pold);
					}

					if (pDoc->baduk[row][col] == 2) {
						px = start_x + width * col - width / 2;
						py = start_y + width * row - width / 2;
						ex = px + width;
						ey = py + width;
						pold = pDC->SelectObject(&whitebrush);
						pDC->Ellipse(px, py, ex, ey);
						pDC->SelectObject(pold);

						
					}
				}
			}
		}

		else {
			for (row = 0; row < 19; row++) {             //�ٵϵ� ��� 2�̸� �浹 , 1�̸� �鵹�� ���� �׸�
				for (col = 0; col < 19; col++) {
					if (pDoc->baduk[row][col] == 2) {
						px = start_x + width * col - width / 2;
						py = start_y + width * row - width / 2;
						ex = px + width;
						ey = py + width;
						pold = pDC->SelectObject(&blackbrush);
						pDC->Ellipse(px, py, ex, ey);
						pDC->SelectObject(pold);
					}

					if (pDoc->baduk[row][col] == 1) {
						px = start_x + width * col - width / 2;
						py = start_y + width * row - width / 2;
						ex = px + width;
						ey = py + width;
						pold = pDC->SelectObject(&whitebrush);
						pDC->Ellipse(px, py, ex, ey);
						pDC->SelectObject(pold);

						
					}
				}

			}

		}
		/*
		CBrush redBrush;
		redBrush.CreateSolidBrush(RGB(255, 0, 0));
		pold = pDC->SelectObject(&redBrush);
		pDC->Ellipse(start_x + c_row*width, start_y + c_col*width, start_x + c_row*width + 10, start_y + c_col*width + 10);
		pDC->Ellipse(start_x + m_row*width, start_y + m_col*width, start_x + m_row*width + 10, start_y + m_col*width + 10);
		pDC->SelectObject(pold);
		*/
		yellowbrush.DeleteObject();
		blackbrush.DeleteObject();
		whitebrush.DeleteObject();

		
	}
	else {
		CMFCApplication3View::BackGround(pDC);
		

		// TransparentBlt( HDC hdcDest, int xDest, int yDest, int wDest, int hDest, HDC hdcSrc, int xSrc, int ySrc, int wSrc, int hSrc, UINT crTransparent ) ;
		// TransparentBlt( hdc,            x,          y,        32,         32,      MemDC,       0,        0,        32,      32,       RGB(0, 255, 0));
		startBmp.LoadBitmap(IDB_START); // ���� ��ư 
		poldbitmap = memDC.SelectObject(&startBmp);
		pDC->StretchBlt(750, 400, 156, 105, &memDC, 0, 0, 156, 105, SRCCOPY);

		configBmp.LoadBitmap(IDB_CONFIG);
		poldbitmap = memDC.SelectObject(&configBmp);  // ���� ��ư
		pDC->StretchBlt(750, 530, 156, 105, &memDC, 0, 0, 156, 105, SRCCOPY);
	}
	
}




void CMFCApplication3View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	int sx, sy, ex, ey, col, row;
	double fx, fy;

	int check_vertical = 0; // 3x3 ���ι��� üũ ����
	int check_beside_vertical = 0; // 3x3 ���ι��� üũ ����
	int check_horizontal = 0; //3x3 ���ι��� üũ ����
	int check_beside_horizontal = 0; //3x3 ���ι��� üũ ����
	int check_diagonal = 0;  // �Ϲݴ밢���� ���
	int check_beside_diagonal = 0; // �Ϲݴ밢���� ���
	int check_reverse_diagonal = 0; //�Ϲݴ밢���� �ݴ� ���
	int check_reverse_beside_diagonal = 0; // �Ϲ� �밢���� �ݴ� ���

	int three_by_three = 0; // 3x3 üũ -> 4�̻��� �Ǿ����� 33 �޽��� ���
	int i = 0;
	CString s;
	s.Format(_T("3x3�Դϴ�")); // 3x3 �޽���

	int three_by_three_flag = 0;
	
	CMFCApplication3Doc* pDoc = GetDocument();



	if (m_start == false) {			//���� ��ư? 
		if (point.x < 906 && point.x > 750 && point.y < 505 && point.y >400) {
			CSubDialog subDlg;
			subDlg.DoModal();
		}
		if (point.x < 906 && point.x > 750 && point.y < 635 && point.y >530) {
			CSubDialog2 subDlg2;		// ���� ��ư
			subDlg2.DoModal();
		}
	}

	
	if (point.x < 198 && point.x > 70 && point.y < 601 && point.y >500) {
		//murgi();
		
		CSubDialog dialog;
		dialog.DoModal();
		
	
	}
	
	
	
	
	
	
	
	
	
	
	if (point.x < 998 && point.x > 850 && point.y < 601 && point.y >500) {		//ó������ ��ư
																				
																				m_start = false;
																				Invalidate(false);

																				for (int row = 0; row < 19; row++)
																				for (int col = 0; col < 19; col++)
																				pDoc->baduk[row][col] = 0;

																				w_win=0;
																				b_win=0;

																				KillTimer(1);
																				KillTimer(2);

																				m_sunseo = true;
																				
		/*CSubDialog subdialog;        //�̰� ���߿� ������
		subdialog.DoModal();*/
	}

	sx = 250, sy = 100;  // ������

	ex = sx + 30 * 18;  // ����
	ey = sy + 30 * 18;

	if (point.x < sx || point.x > ex || point.y <sy || point.y >ey) return;

	col = (point.x - sx) / 30;     //ȭ����ǥ�� ������ ��ġ ���
	row = (point.y - sy) / 30;

	fx = double((point.x - sx)) / 30.0;  // ���콺 ��ġ�� �ٵ����� ��Ȯ�� row,col ��ġ�� �ƴҰ��
	
	fy = double((point.y - sy)) / 30.0; // ����� ��ġ�� ����

	if (fx - col > 0.5) col++;
	if (fy - row > 0.5) row++;

	 check_vertical = 0; // 3x3 ���ι��� üũ ����
	 check_beside_vertical = 0; // 3x3 ���ι��� üũ ����
	 check_horizontal = 0; //3x3 ���ι��� üũ ����
	 check_beside_horizontal = 0; //3x3 ���ι��� üũ ����
	 check_diagonal = 0;  // �Ϲݴ밢���� ���
	 check_beside_diagonal = 0; // �Ϲݴ밢���� ���
	 check_reverse_diagonal = 0; //�Ϲݴ밢���� �ݴ� ���
	 check_reverse_beside_diagonal = 0; // �Ϲ� �밢���� �ݴ� ���

	if(m_start){
		//PlaySound(_T("res\\Sound\\BackGroundMusic1.wav"), NULL , SND_ASYNC | SND_LOOP);
		PlaySound(_T("res\\Sound\\�ٵϵ�Ŭ���Ҹ�1.wav"), NULL, SND_ASYNC);

		if (pDoc->baduk[row][col] == 0) //����� ��ġ�� �ٵϵ��� ������ ����ġ�� �ٵϵ� ���� ����
		{
			if (m_sunseo) {




				// 33 ����

				//==============�� ��ġ�� �߽����� 33 ���� �� üũ===============//
				
				if (pDoc->baduk[row + 1][col] == 2);			//�� ��ġ���� ������ üũ x?
				else if (pDoc->baduk[row + 1][col] == 1) {			//�� ��ġ ���� ������ üũ x*?
					if (pDoc->baduk[row + 2][col] == 2);			
					else if (pDoc->baduk[row + 2][col] == 1) {			//x** ����
						if (pDoc->baduk[row + 3][col] == 2);
						else if (pDoc->baduk[row + 3][col] == 1);
						else if (pDoc->baduk[row + 3][col] == 0){
							if (pDoc->baduk[row + 4][col] == 2 || pDoc->baduk[row + 4][col] == 0) {
								if (pDoc->baduk[row - 1][col] == 2);
								else if (pDoc->baduk[row - 1][col] == 1);
								else if (pDoc->baduk[row - 1][col] == 0) {
									if (pDoc->baduk[row - 2][col] == 2) {
										if (pDoc->baduk[row + 4][col] == 0) three_by_three_flag++; // �� ������ ���� ���ɼ� üũ
									}
									else if (pDoc->baduk[row - 2][col] == 1);
									else if (pDoc->baduk[row - 2][col] == 0)three_by_three_flag++; // x**���� �Ϸ�
								}
							}
							else if (pDoc->baduk[row + 4][col] == 1);
						}
					}
					else if(pDoc->baduk[row + 2][col] == 0){		//�� ��ġ���� ������ x* ?
						if (pDoc->baduk[row + 3][col] == 2 || pDoc->baduk[row + 3][col] == 0) {		//x*   ����
							if (pDoc->baduk[row - 1][col] == 2);
							else if (pDoc->baduk[row - 1][col] == 1) {		// *x*
								if (pDoc->baduk[row - 2][col] == 2);
								else if (pDoc->baduk[row - 2][col] == 1);
								else if (pDoc->baduk[row - 2][col] == 0) {
									if (pDoc->baduk[row - 3][col] == 2) {
										if (pDoc->baduk[row + 3][col] == 0)	three_by_three_flag++;
									}
									else if (pDoc->baduk[row - 3][col] == 1);
									else if (pDoc->baduk[row - 3][col] == 0) three_by_three_flag++;
								}
							}
							else if (pDoc->baduk[row - 1][col] == 0) {		// ? x*
								if (pDoc->baduk[row - 2][col] == 2);
								else if (pDoc->baduk[row - 2][col] == 1) {		// * x*
									if (pDoc->baduk[row - 3][col] == 2);
									else if (pDoc->baduk[row - 3][col] == 1);
									else if (pDoc->baduk[row - 3][col] == 0) {
										if (pDoc->baduk[row - 4][col] == 2) three_by_three_flag++;
										else if (pDoc->baduk[row - 4][col] == 1);
										else if (pDoc->baduk[row - 4][col] == 0) three_by_three_flag++;
									}
								}
								else if (pDoc->baduk[row - 2][col] == 0);
							}
						}
						else if (pDoc->baduk[row + 3][col] == 1) {		//x* *
							if (pDoc->baduk[row + 4][col] == 2);
							else if (pDoc->baduk[row + 4][col] == 1) three_by_three_flag - 3;
							else if (pDoc->baduk[row + 4][col] == 0) {
								if (pDoc->baduk[row - 1][col] == 2);
								else if (pDoc->baduk[row - 1][col] == 1);
								else if (pDoc->baduk[row - 1][col] == 0) {
									if (pDoc->baduk[row - 2][col] == 2) three_by_three_flag++;
									else if (pDoc->baduk[row - 2][col] == 1);
									else if (pDoc->baduk[row - 2][col] == 0) three_by_three_flag++;
								}
							}
						}
					}
				}
				else if (pDoc->baduk[row + 1][col] == 0) {			//x ? ����.
					if (pDoc->baduk[row + 2][col] == 2 || pDoc->baduk[row + 2][col] == 0) {		//   x ���� �˻� ����.
						if (pDoc->baduk[row - 1][col] == 2);
						else if (pDoc->baduk[row - 1][col] == 1) {				//   *x ����.
							if (pDoc->baduk[row - 2][col] == 2);
							else if (pDoc->baduk[row - 2][col] == 1) {				//   **x
								if (pDoc->baduk[row - 3][col] == 2);
								else if (pDoc->baduk[row - 3][col] == 1) three_by_three_flag - 3;
								else if (pDoc->baduk[row - 3][col] == 0) {
									if (pDoc->baduk[row - 4][col] == 2) {
										if (pDoc->baduk[row + 2][col] == 0) three_by_three_flag++;
									}
									else if (pDoc->baduk[row - 4][col] == 1);
									else if (pDoc->baduk[row - 4][col] == 0) three_by_three_flag++;
								}
							}
							else if (pDoc->baduk[row - 2][col] == 0) {			// ? *x
								if (pDoc->baduk[row - 3][col] == 2);
								else if (pDoc->baduk[row - 3][col] == 1) {			// * *x
									if (pDoc->baduk[row - 4][col] == 2);
									else if (pDoc->baduk[row - 4][col] == 1) three_by_three_flag - 3;
									else if (pDoc->baduk[row - 4][col] == 0) three_by_three_flag++;
								}
								else if (pDoc->baduk[row - 3][col] == 0);
							}
						}
						else if (pDoc->baduk[row - 1][col] == 0) {		// ? x ����
							if (pDoc->baduk[row - 2][col] == 2);
							else if (pDoc->baduk[row - 2][col] == 1) {		// * x
								if (pDoc->baduk[row - 3][col] == 2);
								else if (pDoc->baduk[row - 3][col] == 1) {		// ** x
									if (pDoc->baduk[row - 4][col] == 2);
									else if (pDoc->baduk[row - 4][col] == 1);
									else if (pDoc->baduk[row - 4][col] == 0) {
										if (pDoc->baduk[row - 5][col] == 2) three_by_three_flag++;
										else if (pDoc->baduk[row - 5][col] == 1);
										else if (pDoc->baduk[row - 5][col] == 0) three_by_three_flag++;
									}
								}
								else if (pDoc->baduk[row - 3][col] == 0);
							}
						}
					}
					else if (pDoc->baduk[row + 2][col] == 1) {		// x *
						if (pDoc->baduk[row + 3][col] == 2);
						else if (pDoc->baduk[row + 3][col] == 1) {		// x **
							if (pDoc->baduk[row + 4][col] == 2);
							else if (pDoc->baduk[row + 4][col] == 1);
							else if (pDoc->baduk[row + 4][col] == 0) {
								if (pDoc->baduk[row + 5][col] == 2 || pDoc->baduk[row + 5][col] == 0) {
									if (pDoc->baduk[row - 1][col] == 2);
									else if (pDoc->baduk[row - 1][col] == 1);
									else if (pDoc->baduk[row - 1][col] == 0) {
										if (pDoc->baduk[row - 2][col] == 2);
										else if (pDoc->baduk[row - 2][col] == 1);
										else if (pDoc->baduk[row - 2][col] == 0) three_by_three_flag++;
									}
								}
								else if (pDoc->baduk[row + 5][col] == 1);
							}
						}
						else if (pDoc->baduk[row + 3][col] == 0) {		// x *  ����
							if (pDoc->baduk[row + 4][col] == 2 || pDoc->baduk[row + 4][col] == 0) {
								if (pDoc->baduk[row - 1][col] == 2);
								else if (pDoc->baduk[row - 1][col] == 1) {		// *x * ����
									if (pDoc->baduk[row - 2][col] == 2);
									else if (pDoc->baduk[row - 2][col] == 1);
									else if (pDoc->baduk[row - 2][col] == 0) three_by_three_flag++;
								}
								else if (pDoc->baduk[row - 1][col] == 0);
							}
							else if (pDoc->baduk[row + 4][col] == 1);
						}
					}
				}

				// ====================== ������ üũ �� ====================== //



				//==============�� ��ġ�� �߽����� 33 ���� �� üũ===============//

				if (pDoc->baduk[row][col + 1] == 2);			//�� ��ġ���� ������ üũ x?
				else if (pDoc->baduk[row][col + 1] == 1) {			//�� ��ġ ���� ������ üũ x*?
					if (pDoc->baduk[row][col + 2] == 2);
					else if (pDoc->baduk[row][col + 2] == 1) {			//x** ����
						if (pDoc->baduk[row][col + 3] == 2);
						else if (pDoc->baduk[row][col + 3] == 1);
						else if (pDoc->baduk[row][col + 3] == 0) {
							if (pDoc->baduk[row][col + 4] == 2 || pDoc->baduk[row][col + 4] == 0) {
								if (pDoc->baduk[row][col - 1] == 2);
								else if (pDoc->baduk[row][col - 1] == 1);
								else if (pDoc->baduk[row][col - 1] == 0) {
									if (pDoc->baduk[row][col - 2] == 2) {
										if (pDoc->baduk[row][col + 4] == 0) three_by_three_flag++; // �� ������ ���� ���ɼ� üũ
									}
									else if (pDoc->baduk[row][col - 2] == 1);
									else if (pDoc->baduk[row][col - 2] == 0)three_by_three_flag++; // x**���� �Ϸ�
								}
							}
							else if (pDoc->baduk[row][col + 4] == 1);
						}
					}
					else if (pDoc->baduk[row][col + 2] == 0) {		//�� ��ġ���� ������ x* ?
						if (pDoc->baduk[row][col + 3] == 2 || pDoc->baduk[row][col + 3] == 0) {		//x*   ����
							if (pDoc->baduk[row][col - 1] == 2);
							else if (pDoc->baduk[row][col - 1] == 1) {		// *x*
								if (pDoc->baduk[row][col - 2] == 2);
								else if (pDoc->baduk[row][col - 2] == 1);
								else if (pDoc->baduk[row][col - 2] == 0) {
									if (pDoc->baduk[row][col - 3] == 2) {
										if (pDoc->baduk[row][col + 3] == 0)	three_by_three_flag++;
									}
									else if (pDoc->baduk[row][col - 3] == 1);
									else if (pDoc->baduk[row][col - 3] == 0) three_by_three_flag++;
								}
							}
							else if (pDoc->baduk[row][col - 1] == 0) {		// ? x*
								if (pDoc->baduk[row][col - 2] == 2);
								else if (pDoc->baduk[row][col - 2] == 1) {		// * x*
									if (pDoc->baduk[row][col - 3] == 2);
									else if (pDoc->baduk[row][col - 3] == 1);
									else if (pDoc->baduk[row][col - 3] == 0) {
										if (pDoc->baduk[row][col - 4] == 2) three_by_three_flag++;
										else if (pDoc->baduk[row][col - 4] == 1);
										else if (pDoc->baduk[row][col - 4] == 0) three_by_three_flag++;
									}
								}
								else if (pDoc->baduk[row][col - 2] == 0);
							}
						}
						else if (pDoc->baduk[row][col + 3] == 1) {		//x* *
							if (pDoc->baduk[row][col + 4] == 2);
							else if (pDoc->baduk[row][col + 4] == 1);
							else if (pDoc->baduk[row][col + 4] == 0) {
								if (pDoc->baduk[row][col - 1] == 2);
								else if (pDoc->baduk[row][col - 1] == 1);
								else if (pDoc->baduk[row][col - 1] == 0) {
									if (pDoc->baduk[row][col - 2] == 2) three_by_three_flag++;
									else if (pDoc->baduk[row][col - 2] == 1);
									else if (pDoc->baduk[row][col - 2] == 0) three_by_three_flag++;
								}
							}
						}
					}
				}
				else if (pDoc->baduk[row][col + 1] == 0) {			//x ? ����.
					if (pDoc->baduk[row][col + 2] == 2 || pDoc->baduk[row][col + 2] == 0) {		//   x ���� �˻� ����.
						if (pDoc->baduk[row][col - 1] == 2);
						else if (pDoc->baduk[row][col - 1] == 1) {				//   *x ����.
							if (pDoc->baduk[row][col - 2] == 2);
							else if (pDoc->baduk[row][col - 2] == 1) {				//   **x
								if (pDoc->baduk[row][col - 3] == 2);
								else if (pDoc->baduk[row][col - 3] == 1);
								else if (pDoc->baduk[row][col - 3] == 0) {
									if (pDoc->baduk[row][col - 4] == 2) {
										if (pDoc->baduk[row][col + 2] == 0) three_by_three_flag++;
									}
									else if (pDoc->baduk[row][col - 4] == 1);
									else if (pDoc->baduk[row][col - 4] == 0) three_by_three_flag++;
								}
							}
							else if (pDoc->baduk[row][col - 2] == 0) {			// ? *x
								if (pDoc->baduk[row][col - 3] == 2);
								else if (pDoc->baduk[row][col - 3] == 1) {			// * *x
									if (pDoc->baduk[row][col - 4] == 2);
									else if (pDoc->baduk[row][col - 4] == 1);
									else if (pDoc->baduk[row][col - 4] == 0) three_by_three_flag++;
								}
								else if (pDoc->baduk[row][col - 3] == 0);
							}
						}
						else if (pDoc->baduk[row][col - 1] == 0) {		// ? x ����
							if (pDoc->baduk[row][col - 2] == 2);
							else if (pDoc->baduk[row][col - 2] == 1) {		// * x
								if (pDoc->baduk[row][col - 3] == 2);
								else if (pDoc->baduk[row][col - 3] == 1) {		// ** x
									if (pDoc->baduk[row][col - 4] == 2);
									else if (pDoc->baduk[row][col - 4] == 1);
									else if (pDoc->baduk[row][col - 4] == 0) {
										if (pDoc->baduk[row][col - 5] == 2) three_by_three_flag++;
										else if (pDoc->baduk[row][col - 5] == 1);
										else if (pDoc->baduk[row][col - 5] == 0) three_by_three_flag++;
									}
								}
								else if (pDoc->baduk[row][col - 3] == 0);
							}
						}
					}
					else if (pDoc->baduk[row][col + 2] == 1) {		// x *
						if (pDoc->baduk[row][col + 3] == 2);
						else if (pDoc->baduk[row][col + 3] == 1) {		// x **
							if (pDoc->baduk[row][col + 4] == 2);
							else if (pDoc->baduk[row][col + 4] == 1);
							else if (pDoc->baduk[row][col + 4] == 0) {
								if (pDoc->baduk[row][col + 5] == 2 || pDoc->baduk[row][col + 5] == 0) {
									if (pDoc->baduk[row][col - 1] == 2);
									else if (pDoc->baduk[row][col - 1] == 1);
									else if (pDoc->baduk[row][col - 1] == 0) {
										if (pDoc->baduk[row][col - 2] == 2);
										else if (pDoc->baduk[row][col - 2] == 1);
										else if (pDoc->baduk[row][col - 2] == 0) three_by_three_flag++;
									}
								}
								else if (pDoc->baduk[row][col + 5] == 1);
							}
						}
						else if (pDoc->baduk[row][col + 3] == 0) {		// x *  ����
							if (pDoc->baduk[row][col + 4] == 2 || pDoc->baduk[row][col + 4] == 0) {
								if (pDoc->baduk[row][col - 1] == 2);
								else if (pDoc->baduk[row][col - 1] == 1) {		// *x * ����
									if (pDoc->baduk[row][col - 2] == 2);
									else if (pDoc->baduk[row][col - 2] == 1);
									else if (pDoc->baduk[row][col - 2] == 0) three_by_three_flag++;
								}
								else if (pDoc->baduk[row][col - 1] == 0);
							}
							else if (pDoc->baduk[row][col + 4] == 1);
						}
					}
				}

				// ====================== ������ üũ �� ====================== //




				//==============�� ��ġ�� �߽����� �»� --> ���� �밢�� �� üũ===============//

				if (pDoc->baduk[row + 1][col + 1] == 2);			//�� ��ġ���� ������ üũ x?
				else if (pDoc->baduk[row + 1][col + 1] == 1) {			//�� ��ġ ���� ������ üũ x*?
					if (pDoc->baduk[row + 2][col + 2] == 2);
					else if (pDoc->baduk[row + 2][col + 2] == 1) {			//x** ����
						if (pDoc->baduk[row + 3][col + 3] == 2);
						else if (pDoc->baduk[row + 3][col + 3] == 1);
						else if (pDoc->baduk[row + 3][col + 3] == 0) {
							if (pDoc->baduk[row + 4][col + 4] == 2 || pDoc->baduk[row + 4][col + 4] == 0) {
								if (pDoc->baduk[row - 1][col - 1] == 2);
								else if (pDoc->baduk[row - 1][col - 1] == 1);
								else if (pDoc->baduk[row - 1][col - 1] == 0) {
									if (pDoc->baduk[row - 2][col - 2] == 2) {
										if (pDoc->baduk[row + 4][col + 4] == 0) three_by_three_flag++; // �� ������ ���� ���ɼ� üũ
									}
									else if (pDoc->baduk[row - 2][col - 2] == 1);
									else if (pDoc->baduk[row - 2][col - 2] == 0)three_by_three_flag++; // x**���� �Ϸ�
								}
							}
							else if (pDoc->baduk[row + 4][col + 4] == 1);
						}
					}
					else if (pDoc->baduk[row + 2][col + 2] == 0) {		//�� ��ġ���� ������ x* ?
						if (pDoc->baduk[row + 3][col + 3] == 2 || pDoc->baduk[row + 3][col + 3] == 0) {		//x*   ����
							if (pDoc->baduk[row - 1][col - 1] == 2);
							else if (pDoc->baduk[row - 1][col - 1] == 1) {		// *x*
								if (pDoc->baduk[row - 2][col - 2] == 2);
								else if (pDoc->baduk[row - 2][col - 2] == 1);
								else if (pDoc->baduk[row - 2][col - 2] == 0) {
									if (pDoc->baduk[row - 3][col - 3] == 2) {
										if (pDoc->baduk[row + 3][col + 3] == 0)	three_by_three_flag++;
									}
									else if (pDoc->baduk[row - 3][col - 3] == 1);
									else if (pDoc->baduk[row - 3][col - 3] == 0) three_by_three_flag++;
								}
							}
							else if (pDoc->baduk[row - 1][col - 1] == 0) {		// ? x*
								if (pDoc->baduk[row - 2][col - 2] == 2);
								else if (pDoc->baduk[row - 2][col - 2] == 1) {		// * x*
									if (pDoc->baduk[row - 3][col - 3] == 2);
									else if (pDoc->baduk[row - 3][col - 3] == 1);
									else if (pDoc->baduk[row - 3][col - 3] == 0) {
										if (pDoc->baduk[row - 4][col - 4] == 2) three_by_three_flag++;
										else if (pDoc->baduk[row - 4][col - 4] == 1);
										else if (pDoc->baduk[row - 4][col - 4] == 0) three_by_three_flag++;
									}
								}
								else if (pDoc->baduk[row - 2][col - 2] == 0);
							}
						}
						else if (pDoc->baduk[row + 3][col + 3] == 1) {		//x* *
							if (pDoc->baduk[row + 4][col + 4] == 2);
							else if (pDoc->baduk[row + 4][col + 4] == 1);
							else if (pDoc->baduk[row + 4][col + 4] == 0) {
								if (pDoc->baduk[row - 1][col - 1] == 2);
								else if (pDoc->baduk[row - 1][col - 1] == 1);
								else if (pDoc->baduk[row - 1][col - 1] == 0) {
									if (pDoc->baduk[row - 2][col - 2] == 2) three_by_three_flag++;
									else if (pDoc->baduk[row - 2][col - 2] == 1);
									else if (pDoc->baduk[row - 2][col - 2] == 0) three_by_three_flag++;
								}
							}
						}
					}
				}
				else if (pDoc->baduk[row + 1][col + 1] == 0) {			//x ? ����.
					if (pDoc->baduk[row + 2][col + 2] == 2 || pDoc->baduk[row + 2][col + 2] == 0) {		//   x ���� �˻� ����.
						if (pDoc->baduk[row - 1][col - 1] == 2);
						else if (pDoc->baduk[row - 1][col - 1] == 1) {				//   *x ����.
							if (pDoc->baduk[row - 2][col - 2] == 2);
							else if (pDoc->baduk[row - 2][col - 2] == 1) {				//   **x
								if (pDoc->baduk[row - 3][col - 3] == 2);
								else if (pDoc->baduk[row - 3][col - 3] == 1);
								else if (pDoc->baduk[row - 3][col - 3] == 0) {
									if (pDoc->baduk[row - 4][col - 4] == 2) {
										if (pDoc->baduk[row + 2][col + 2] == 0) three_by_three_flag++;
									}
									else if (pDoc->baduk[row - 4][col - 4] == 1);
									else if (pDoc->baduk[row - 4][col - 4] == 0) three_by_three_flag++;
								}
							}
							else if (pDoc->baduk[row - 2][col - 2] == 0) {			// ? *x
								if (pDoc->baduk[row - 3][col - 3] == 2);
								else if (pDoc->baduk[row - 3][col - 3] == 1) {			// * *x
									if (pDoc->baduk[row - 4][col - 4] == 2);
									else if (pDoc->baduk[row - 4][col - 4] == 1);
									else if (pDoc->baduk[row - 4][col - 4] == 0) three_by_three_flag++;
								}
								else if (pDoc->baduk[row - 3][col - 3] == 0);
							}
						}
						else if (pDoc->baduk[row - 1][col - 1] == 0) {		// ? x ����
							if (pDoc->baduk[row - 2][col - 2] == 2);
							else if (pDoc->baduk[row - 2][col - 2] == 1) {		// * x
								if (pDoc->baduk[row - 3][col - 3] == 2);
								else if (pDoc->baduk[row - 3][col - 3] == 1) {		// ** x
									if (pDoc->baduk[row - 4][col - 4] == 2);
									else if (pDoc->baduk[row - 4][col - 4] == 1);
									else if (pDoc->baduk[row - 4][col - 4] == 0) {
										if (pDoc->baduk[row - 5][col - 5] == 2) three_by_three_flag++;
										else if (pDoc->baduk[row - 5][col - 5] == 1);
										else if (pDoc->baduk[row - 5][col - 5] == 0) three_by_three_flag++;
									}
								}
								else if (pDoc->baduk[row - 3][col - 3] == 0);
							}
						}
					}
					else if (pDoc->baduk[row + 2][col + 2] == 1) {		// x *
						if (pDoc->baduk[row + 3][col + 3] == 2);
						else if (pDoc->baduk[row + 3][col + 3] == 1) {		// x **
							if (pDoc->baduk[row + 4][col + 4] == 2);
							else if (pDoc->baduk[row + 4][col + 4] == 1);
							else if (pDoc->baduk[row + 4][col + 4] == 0) {
								if (pDoc->baduk[row + 5][col + 5] == 2 || pDoc->baduk[row + 5][col + 5] == 0) {
									if (pDoc->baduk[row - 1][col - 1] == 2);
									else if (pDoc->baduk[row - 1][col - 1] == 1);
									else if (pDoc->baduk[row - 1][col - 1] == 0) {
										if (pDoc->baduk[row - 2][col - 2] == 2);
										else if (pDoc->baduk[row - 2][col - 2] == 1);
										else if (pDoc->baduk[row - 2][col - 2] == 0) three_by_three_flag++;
									}
								}
								else if (pDoc->baduk[row + 5][col + 5] == 1);
							}
						}
						else if (pDoc->baduk[row + 3][col + 3] == 0) {		// x *  ����
							if (pDoc->baduk[row + 4][col + 4] == 2 || pDoc->baduk[row + 4][col + 4] == 0) {
								if (pDoc->baduk[row - 1][col - 1] == 2);
								else if (pDoc->baduk[row - 1][col - 1] == 1) {		// *x * ����
									if (pDoc->baduk[row - 2][col - 2] == 2);
									else if (pDoc->baduk[row - 2][col - 2] == 1);
									else if (pDoc->baduk[row - 2][col - 2] == 0) three_by_three_flag++;
								}
								else if (pDoc->baduk[row - 1][col - 1] == 0);
							}
							else if (pDoc->baduk[row + 4][col + 4] == 1);
						}
					}
				}

				// ====================== �»� ���� �밢�� üũ �� ====================== //




				//==============�� ��ġ�� �߽����� ��� --> ���� �밢�� �� üũ===============//

				if (pDoc->baduk[row + 1][col - 1] == 2);			//�� ��ġ���� ������ üũ x?
				else if (pDoc->baduk[row + 1][col - 1] == 1) {			//�� ��ġ ���� ������ üũ x*?
					if (pDoc->baduk[row + 2][col - 2] == 2);
					else if (pDoc->baduk[row + 2][col - 2] == 1) {			//x** ����
						if (pDoc->baduk[row + 3][col - 3] == 2);
						else if (pDoc->baduk[row + 3][col - 3] == 1);
						else if (pDoc->baduk[row + 3][col - 3] == 0) {
							if (pDoc->baduk[row + 4][col - 4] == 2 || pDoc->baduk[row + 4][col - 4] == 0) {
								if (pDoc->baduk[row - 1][col + 1] == 2);
								else if (pDoc->baduk[row - 1][col + 1] == 1);
								else if (pDoc->baduk[row - 1][col + 1] == 0) {
									if (pDoc->baduk[row - 2][col + 2] == 2) {
										if (pDoc->baduk[row + 4][col - 4] == 0) three_by_three_flag++; // �� ������ ���� ���ɼ� üũ
									}
									else if (pDoc->baduk[row - 2][col + 2] == 1);
									else if (pDoc->baduk[row - 2][col + 2] == 0)three_by_three_flag++; // x**���� �Ϸ�
								}
							}
							else if (pDoc->baduk[row + 4][col - 4] == 1);
						}
					}
					else if (pDoc->baduk[row + 2][col - 2] == 0) {		//�� ��ġ���� ������ x* ?
						if (pDoc->baduk[row + 3][col - 3] == 2 || pDoc->baduk[row + 3][col - 3] == 0) {		//x*   ����
							if (pDoc->baduk[row - 1][col + 1] == 2);
							else if (pDoc->baduk[row - 1][col + 1] == 1) {		// *x*
								if (pDoc->baduk[row - 2][col + 2] == 2);
								else if (pDoc->baduk[row - 2][col + 2] == 1);
								else if (pDoc->baduk[row - 2][col + 2] == 0) {
									if (pDoc->baduk[row - 3][col + 3] == 2) {
										if (pDoc->baduk[row + 3][col - 3] == 0)	three_by_three_flag++;
									}
									else if (pDoc->baduk[row - 3][col + 3] == 1);
									else if (pDoc->baduk[row - 3][col + 3] == 0) three_by_three_flag++;
								}
							}
							else if (pDoc->baduk[row - 1][col + 1] == 0) {		// ? x*
								if (pDoc->baduk[row - 2][col + 2] == 2);
								else if (pDoc->baduk[row - 2][col + 2] == 1) {		// * x*
									if (pDoc->baduk[row - 3][col + 3] == 2);
									else if (pDoc->baduk[row - 3][col + 3] == 1);
									else if (pDoc->baduk[row - 3][col + 3] == 0) {
										if (pDoc->baduk[row - 4][col + 4] == 2) three_by_three_flag++;
										else if (pDoc->baduk[row - 4][col + 4] == 1);
										else if (pDoc->baduk[row - 4][col + 4] == 0) three_by_three_flag++;
									}
								}
								else if (pDoc->baduk[row - 2][col + 2] == 0);
							}
						}
						else if (pDoc->baduk[row + 3][col - 3] == 1) {		//x* *
							if (pDoc->baduk[row + 4][col - 4] == 2);
							else if (pDoc->baduk[row + 4][col - 4] == 1);
							else if (pDoc->baduk[row + 4][col - 4] == 0) {
								if (pDoc->baduk[row - 1][col + 1] == 2);
								else if (pDoc->baduk[row - 1][col + 1] == 1);
								else if (pDoc->baduk[row - 1][col + 1] == 0) {
									if (pDoc->baduk[row - 2][col + 2] == 2) three_by_three_flag++;
									else if (pDoc->baduk[row - 2][col + 2] == 1);
									else if (pDoc->baduk[row - 2][col + 2] == 0) three_by_three_flag++;
								}
							}
						}
					}
				}
				else if (pDoc->baduk[row + 1][col - 1] == 0) {			//x ? ����.
					if (pDoc->baduk[row + 2][col - 2] == 2 || pDoc->baduk[row + 2][col - 2] == 0) {		//   x ���� �˻� ����.
						if (pDoc->baduk[row - 1][col + 1] == 2);
						else if (pDoc->baduk[row - 1][col + 1] == 1) {				//   *x ����.
							if (pDoc->baduk[row - 2][col + 2] == 2);
							else if (pDoc->baduk[row - 2][col + 2] == 1) {				//   **x
								if (pDoc->baduk[row - 3][col + 3] == 2);
								else if (pDoc->baduk[row - 3][col + 3] == 1);
								else if (pDoc->baduk[row - 3][col + 3] == 0) {
									if (pDoc->baduk[row - 4][col + 4] == 2) {
										if (pDoc->baduk[row + 2][col - 2] == 0) three_by_three_flag++;
									}
									else if (pDoc->baduk[row - 4][col + 4] == 1);
									else if (pDoc->baduk[row - 4][col + 4] == 0) three_by_three_flag++;
								}
							}
							else if (pDoc->baduk[row - 2][col + 2] == 0) {			// ? *x
								if (pDoc->baduk[row - 3][col + 3] == 2);
								else if (pDoc->baduk[row - 3][col + 3] == 1) {			// * *x
									if (pDoc->baduk[row - 4][col + 4] == 2);
									else if (pDoc->baduk[row - 4][col + 4] == 1);
									else if (pDoc->baduk[row - 4][col + 4] == 0) three_by_three_flag++;
								}
								else if (pDoc->baduk[row - 3][col + 3] == 0);
							}
						}
						else if (pDoc->baduk[row - 1][col + 1] == 0) {		// ? x ����
							if (pDoc->baduk[row - 2][col + 2] == 2);
							else if (pDoc->baduk[row - 2][col + 2] == 1) {		// * x
								if (pDoc->baduk[row - 3][col + 3] == 2);
								else if (pDoc->baduk[row - 3][col + 3] == 1) {		// ** x
									if (pDoc->baduk[row - 4][col + 4] == 2);
									else if (pDoc->baduk[row - 4][col + 4] == 1);
									else if (pDoc->baduk[row - 4][col + 4] == 0) {
										if (pDoc->baduk[row - 5][col + 5] == 2) three_by_three_flag++;
										else if (pDoc->baduk[row - 5][col + 5] == 1);
										else if (pDoc->baduk[row - 5][col + 5] == 0) three_by_three_flag++;
									}
								}
								else if (pDoc->baduk[row - 3][col + 3] == 0);
							}
						}
					}
					else if (pDoc->baduk[row + 2][col - 2] == 1) {		// x *
						if (pDoc->baduk[row + 3][col - 3] == 2);
						else if (pDoc->baduk[row + 3][col - 3] == 1) {		// x **
							if (pDoc->baduk[row + 4][col - 4] == 2);
							else if (pDoc->baduk[row + 4][col - 4] == 1);
							else if (pDoc->baduk[row + 4][col - 4] == 0) {
								if (pDoc->baduk[row + 5][col - 5] == 2 || pDoc->baduk[row + 5][col - 5] == 0) {
									if (pDoc->baduk[row - 1][col + 1] == 2);
									else if (pDoc->baduk[row - 1][col + 1] == 1);
									else if (pDoc->baduk[row - 1][col + 1] == 0) {
										if (pDoc->baduk[row - 2][col + 2] == 2);
										else if (pDoc->baduk[row - 2][col + 2] == 1);
										else if (pDoc->baduk[row - 2][col + 2] == 0) three_by_three_flag++;
									}
								}
								else if (pDoc->baduk[row + 5][col - 5] == 1);
							}
						}
						else if (pDoc->baduk[row + 3][col - 3] == 0) {		// x *  ����
							if (pDoc->baduk[row + 4][col - 4] == 2 || pDoc->baduk[row + 4][col - 4] == 0) {
								if (pDoc->baduk[row - 1][col + 1] == 2);
								else if (pDoc->baduk[row - 1][col + 1] == 1) {		// *x * ����
									if (pDoc->baduk[row - 2][col + 2] == 2);
									else if (pDoc->baduk[row - 2][col + 2] == 1);
									else if (pDoc->baduk[row - 2][col + 2] == 0) three_by_three_flag++;
								}
								else if (pDoc->baduk[row - 1][col + 1] == 0);
							}
							else if (pDoc->baduk[row + 4][col - 4] == 1);
						}
					}
				}

				// ====================== ��� ���� �밢�� üũ �� ====================== //


				// 33 ��



				pDoc->baduk[row][col] = 1;
				m_sunseo = false;
				if (three_by_three_flag >= 2) {
					pDoc->baduk[row][col] = 0;
					m_sunseo = true;
					AfxMessageBox(s);
				}
			}
			else {
				for (i = 1; i < 5; i++) {
					if (pDoc->baduk[row - i][col - i] == 2) check_beside_diagonal++;             //�Ϲ� �밢���� ��� (��������)
					else if (pDoc->baduk[row - 4][col - 4] == 1) {
						if (pDoc->baduk[row - 3][col - 3] == 0);
						else check_beside_diagonal = -1;
					}
					else if (pDoc->baduk[row - i][col - i] == 1)	check_beside_diagonal = -1;

					if (pDoc->baduk[row + i][col + i] == 2) check_diagonal++;            //�Ϲ� �밢���� ��� (������ �Ʒ���)
					else if (pDoc->baduk[row + 4][col + 4] == 1) {
						if (pDoc->baduk[row + 3][col + 3] == 0);
						else check_diagonal = -1;
					}
					else if (pDoc->baduk[row + i][col + i] == 1) check_diagonal = -1;

					if (pDoc->baduk[row - i][col + i] == 2) check_reverse_diagonal++;             //�밢���� �ݴ� ��� (������ ����)
					else if (pDoc->baduk[row - 4][col + 4] == 1) {
						if (pDoc->baduk[row - 3][col + 3] == 0);
						else check_reverse_diagonal = -1;
					}
					else if (pDoc->baduk[row - i][col + i] == 1) check_reverse_diagonal = -1;

					if (pDoc->baduk[row + i][col - i] == 2) check_reverse_beside_diagonal++;           //�밢���� �ݴ� ��� (���� �Ʒ���)
					else if (pDoc->baduk[row + 4][col - 4] == 1) {
						if (pDoc->baduk[row + 3][col - 3] == 0);
						else check_reverse_beside_diagonal = -1;
					}
					else if (pDoc->baduk[row + i][col - i] == 1) check_reverse_beside_diagonal = -1;

					if (pDoc->baduk[row][col + i] == 2) check_horizontal++;             //���ι��� (����������)
					else if (pDoc->baduk[row][col + 4] == 1) {
						if (pDoc->baduk[row][col + 3] == 0); // �ǳ��� �鵹�� ������� �˻�
						else check_horizontal = -1;
					}
					else if (pDoc->baduk[row][col + i] == 1) check_horizontal = -1;  // �׿� �鵹�� ������ ��� 3x3���� ����


					if (pDoc->baduk[row][col - i] == 2) check_beside_horizontal++;            //���ι��� (��������)
					else if (pDoc->baduk[row][col - 4] == 1) {
						if (pDoc->baduk[row][col - 3] == 0); //�ǳ��� �鵹�� ������� �˻�
						else check_beside_horizontal = -1;
					}
					else if (pDoc->baduk[row][col - i] == 1) check_beside_horizontal = -1; // �׿� �鵹�� ������ ��� 3x3���� ����

					if (pDoc->baduk[row + i][col] == 2) check_vertical++;            // ���ι��� (������)
					else if (pDoc->baduk[row + 4][col] == 1) {
						if (pDoc->baduk[row + 3][col] == 0);
						else check_vertical = -1;
					}
					else if (pDoc->baduk[row + i][col] == 1) check_vertical = -1;

					if (pDoc->baduk[row - i][col] == 2) check_beside_vertical++;            // ���ι��� (����)
					else if (pDoc->baduk[row - 4][col] == 1) {
						if (pDoc->baduk[row - 3][col] == 0); //�ǳ��� �鵹�� ���� ��� �˻�
						else check_beside_vertical = -1;
					}
					else if (pDoc->baduk[row - i][col] == 1) check_beside_vertical = -1; // �׿� �鵹�� ������ ��� 3x3����

				}
				// ���⼭ ���� �ٽ� �˻� ���ι��� �˻�
				if (check_vertical == 2) three_by_three += 2; if (check_beside_vertical == 2) three_by_three += 2; //���ι��� 
				if (check_vertical == 2 && (check_beside_vertical >= 1)) three_by_three -= 4;  // ������ ����. ������ ���� �ִ��� �˻�
				if (check_beside_vertical == 2 && (check_vertical >= 1)) three_by_three -= 4;// ������ ����. ������ ���� �ִ��� �˻�
																							 // ���ι��� �˻� ��

																							 // ���ι��� �˻� ����
				if (check_horizontal == 2) three_by_three += 2; if (check_beside_horizontal == 2) three_by_three += 2; //���ι���
				if (check_horizontal == 2 && (check_beside_horizontal >= 1)) three_by_three -= 4;  // ������ ����. ������ ���� �ִ��� �˻�
				if (check_beside_horizontal == 2 && (check_horizontal >= 1)) three_by_three -= 4;// ������ ����. ������ ���� �ִ��� �˻�
																								 //���ι��� �˻� ��

																								 //�밢�� �˻� ����
				if (check_diagonal == 2) three_by_three += 2; if (check_beside_diagonal == 2) three_by_three += 2; //�ݴ� �밢������
				if (check_diagonal == 2 && (check_beside_diagonal >= 1)) three_by_three -= 4;  // ������ ����. ������ ���� �ִ��� �˻�
				if (check_beside_diagonal == 2 && (check_diagonal >= 1)) three_by_three -= 4;// ������ ����. ������ ���� �ִ��� �˻�
																							 //�밢�� �˻� ��

																							 //�ݴ� �밢�� �˻� ����
				if (check_reverse_diagonal == 2) three_by_three += 2; if (check_reverse_beside_diagonal == 2) three_by_three += 2; //�ݴ� �밢������
				if (check_reverse_diagonal == 2 && (check_reverse_beside_diagonal >= 1)) three_by_three -= 4;  // ���� �밢�� ���� ���� �ִ��� �˻�
				if (check_reverse_beside_diagonal == 2 && (check_reverse_diagonal >= 1)) three_by_three -= 4;// ������ �밢�� �Ʒ��� �ִ��� �˻�
																											 //�ݴ� �밢�� �˻� ��

																											 // 3x3 üũ ��!
				pDoc->baduk[row][col] = 2;
				m_sunseo = true;

				if (three_by_three >= 4) { pDoc->baduk[row][col] = 0; m_sunseo = false; AfxMessageBox(s); } // three_by_three�� 4�̻��Ͻ� 3x3 �޽��� ���
			}
			RECT rect, rect2, rect3;
			
			rect.left = 250 + col * 30 - 15;
			rect.top = 100 + row * 30  - 15;
			rect.right = rect.left + 30;
			rect.bottom = rect.top + 30;

			rect2.left = 50;
			rect2.top = 100;
			rect2.right = 150;
			rect2.bottom = 200;
		
			rect3.left = 850;
			rect3.top = 100;
			rect3.right = 950;
			rect3.bottom = 200;



			InvalidateRect(&rect,false);
			InvalidateRect(&rect2, false);
			InvalidateRect(&rect3, false);

			m_row = row;		//�����⸦ ���� ����
			m_col = col;

			


			if (m_sunseo) {
				if (Checkvictory(2, row, col) == 1) {
					PlaySound(_T("res\\Sound\\�¸�����1.wav"), NULL, SND_ASYNC);
					w_win++; // �� 1�� �߰�

					if (m_computerStart) {
						AfxMessageBox(_T("�÷��̾ �¸��߽��ϴ�."), MB_OK);
					}
					else {
						AfxMessageBox(_T("���� �¸��߽��ϴ�."), MB_OK);
					}
					for (int row = 0; row < 19; row++)
						for (int col = 0; col < 19; col++)
							pDoc->baduk[row][col] = 0;

					if (m_computerStart) {
						if (player_black) player_black = false;
						else player_black = true;
					}

					
					if (w_win==winCount) {		// �� �����¸� ���
						if (m_computerStart) {
							AfxMessageBox(_T("�÷��̾ ���� �¸��߽��ϴ�. �ʱ�ȭ������"), MB_OK);
						}
						else {
							AfxMessageBox(_T("���� ���� �¸��߽��ϴ�. �ʱ�ȭ������"), MB_OK);
						}
						m_start = false;
						Invalidate(false);

						for (int row = 0; row < 19; row++)
							for (int col = 0; col < 19; col++)
								pDoc->baduk[row][col] = 0;

						w_win = 0;
						b_win = 0;

						KillTimer(1);
						KillTimer(2);

						m_sunseo = true;
					}

					
					m_sunseo = true;
					Invalidate(false);
				}
			}
			else {
				if (Checkvictory(1, row, col) == 1) {
					PlaySound(_T("res\\Sound\\�¸�����1.wav"), NULL, SND_ASYNC);
					b_win++; // �� 1�� �߰�

					if (m_computerStart) {
						AfxMessageBox(_T("�÷��̾ �¸��߽��ϴ�."), MB_OK);
					}else {
						AfxMessageBox(_T("���� �¸��߽��ϴ�."), MB_OK);
					}
					for (int row = 0; row < 19; row++)
						for (int col = 0; col < 19; col++)
							pDoc->baduk[row][col] = 0;

					if (m_computerStart) {
						if (player_black) player_black = false;
						else player_black = true;
					}

					if (b_win == winCount) {		// �� �����¸� ���
						if (m_computerStart) {
							AfxMessageBox(_T("�÷��̾ ���� �¸��߽��ϴ�. �ʱ�ȭ������"), MB_OK);
						}else {
							AfxMessageBox(_T("���� ���� �¸��߽��ϴ�. �ʱ�ȭ������"), MB_OK);
						}
						m_start = false;
						Invalidate(false);

						for (int row = 0; row < 19; row++)
							for (int col = 0; col < 19; col++)
								pDoc->baduk[row][col] = 0;

						w_win = 0;
						b_win = 0;

						KillTimer(1);
						KillTimer(2);

						m_sunseo = true;
					}

					m_sunseo = true;
					Invalidate(false);
				}
				if (m_sunseo == false)
				{
					if (m_computerStart == true) {        //�ΰ�����
						hansu_ap(2, 1, row, col);
						//AI_White_Do(row, col);
					}
					for (int r = 0; r<19; r++)
					{
						for (int c = 0; c<19; c++)
						{
							if (Checkvictory(2, r, c) == 1)
							{
								PlaySound(_T("res\\Sound\\�¸�����1.wav"), NULL, SND_ASYNC);
								w_win++;

								
								AfxMessageBox(_T("��ǻ�Ͱ� �¸��߽��ϴ�."), MB_OK);
								
								for (int row = 0; row<19; row++)
									for (int col = 0; col<19; col++)
										pDoc->baduk[row][col] = 0;

								if (player_black) player_black = false;
								else player_black = true;

								if (w_win == winCount) {		// ��ǻ�� �����¸� ���
									
									AfxMessageBox(_T("��ǻ�Ͱ� ���� �¸��߽��ϴ�. �ʱ�ȭ������"), MB_OK);

									m_start = false;
									Invalidate(false);

									for (int row = 0; row < 19; row++)
										for (int col = 0; col < 19; col++)
											pDoc->baduk[row][col] = 0;

									w_win = 0;
									b_win = 0;

									KillTimer(1);
									KillTimer(2);

									m_sunseo = true;
								}
								
								m_sunseo = true;
								Invalidate(true);
							}
						}trace = 0;
					}trace = 0;
				}trace = 0;

			}trace = 0;

		}

		if (point.x < 250 && point.x > 50 && point.y < 200 && point.y >50) { //�� �� ������
			
			pDoc->baduk[m_row][m_col] = 0;

			if(m_sunseo) m_sunseo = false;
			else m_sunseo = true;

			Invalidate(true);
			
		}

		
		
	}
	CFormView::OnLButtonDown(nFlags, point);
}




int CMFCApplication3View::Checkvictory(int a, int r, int c)
{
	//a=1 �̸� �浹 ���� üũ, a=2 �� �鵹 ���� üũ
	CMFCApplication3Doc* pDoc = GetDocument();

	int i;
	int count = 0;

	int victory_count = 0;  //�¸� ������ �����Ǹ� 5�� �ȴ�

	for (i = 0; i < 19; i++) {		//���ʿ��� ���������� üũ
		if (pDoc->baduk[r][i] == a) {
			count++;
			if (pDoc->baduk[r][i + 1] == a);
			else if (count == 5) victory_count = count;
		}

		else count = 0;
	}

	if (victory_count == 5) return 1; 	//�����̸� 1 ����


	count = 0;
	victory_count = 0;

	for (i = 0; i < 19; i++) {		//������ �Ʒ��� üũ
		if (pDoc->baduk[i][c] == a) {
			count++;
			if (pDoc->baduk[i + 1][c] == a);
			else if (count == 5) victory_count = count;
		}

		else count = 0;

	}
	if (victory_count == 5) return 1; 	//�����̸� 1 ����


										//���� ������ ������ �Ʒ��밢�� ����
	int srow, scol;
	int erow, ecol;
	int tr, tc;
	tr = r;	tc = c;

	while (tr != 0 && tc != 0) {	//���� ���� ���� ���ޱ��� ����
		tr--;
		tc--;
	}

	srow = tr; scol = tc;		//���� �� �� ���� ����.

	tr = r; tc = c;

	while (tr != 18 && tc != 18) {
		tr++;
		tc++;
	}

	erow = tr; ecol = tc;		//������ �Ʒ� �� ����.

	count = 0;
	victory_count = 0;

	while (scol <= ecol && srow <= erow) {	//üũ ����
		if (pDoc->baduk[srow][scol] == a) {
			count++;
			if (pDoc->baduk[srow + 1][scol + 1] == a);
			else if (count == 5) victory_count = count;
		}
		else count = 0;
		srow++;
		scol++;
	}
	if (victory_count == 5) return 1; 	//�����̸� 1 ����



	tr = r;
	tc = c;

	while (tr != 0 && tc != 18) {	//������ ���� ���� ���ޱ��� ����
		tr--;
		tc++;
	}

	srow = tr; scol = tc;		// ������ �� �� ���� ����.

	tr = r; tc = c;
	while (tr != 18 && tc != 0) {
		tr++;
		tc--;
	}

	erow = tr; ecol = tc;		//������ �Ʒ� �� ����.

	count = 0;
	victory_count = 0;

	while (scol >= ecol&&srow <= erow) {	//üũ ����
		if (pDoc->baduk[srow][scol] == a) {
			count++;
			if (pDoc->baduk[srow + 1][scol - 1] == a);
			else if (count == 5) victory_count = count;
		}
		else count = 0;
		srow++;
		scol--;
	}
	if (victory_count == 5) return 1; 	//�����̸� 1 ����



	return 0;			//������ �ƴϸ� 0 ����
}






void CMFCApplication3View::OnTimer(UINT_PTR nIDEvent) // ���� Ÿ�̸� ���
{
	CDC *pDC = GetDC(); 
	CMFCApplication3Doc *pDoc = GetDocument();
	CString buf;
	CClientDC dc(this);
	
	if (nIDEvent == 1)
	{
		TimeSet--;
		if (TimeSet < 10) {
			buf.Format(_T("�����ð� : 0%d��"), TimeSet);
		}
		else {
			buf.Format(_T("�����ð� : %d��"), TimeSet);
		}
			dc.TextOut(250, 50, buf);
		
		if (TimeSet == 0)
		{
			KillTimer(1);
			if (m_sunseo == true) { //�� �ð��ʰ�
				w_win++;
				
				if (m_computerStart){ // ��ǻ�Ͷ� �� ��
					AfxMessageBox(_T("��ǻ�Ͱ� �¸��߽��ϴ�. �� ���� �����մϴ�."), MB_OK);
				} //����̶� �� ��
				else { AfxMessageBox(_T("���� �¸��߽��ϴ�. �� ���� �����մϴ�."), MB_OK); }
				
				
				Invalidate(false);

				for (int row = 0; row < 19; row++)
					for (int col = 0; col < 19; col++)
						pDoc->baduk[row][col] = 0;

			

				KillTimer(1);
				KillTimer(2);

				m_sunseo = true;
			}
			else {
				b_win++;
				if (m_computerStart) { // ��ǻ�Ͷ� �� ��
					AfxMessageBox(_T("��ǻ�Ͱ� �¸��߽��ϴ�. �� ���� �����մϴ�."), MB_OK);
				} //����̶� �� ��
				else { AfxMessageBox(_T("���� �¸��߽��ϴ�. �� ���� �����մϴ�."), MB_OK); }
				
				
				Invalidate(false);

				for (int row = 0; row < 19; row++)
					for (int col = 0; col < 19; col++)
						pDoc->baduk[row][col] = 0;

				

				KillTimer(1);
				KillTimer(2);

				m_sunseo = true;
			}
			
		}
	}


	CFormView::OnTimer(nIDEvent);
}

/*
int CMFCApplication3View::AI(int r, int c) {

	CMFCApplication3Doc* pDoc = GetDocument();
	CDC *pDC = GetDC();
	
	int tr, tc;

	int connt = 0;

	int row, col;

	if (pDoc->baduk[m_row][m_col - 1] == 0) {
		pDoc -> baduk[m_row][m_col + 1] = 2;
		
	}
	

	m_sunseo = true;
	
	Invalidate(false);
	return 0;
}
*/




int CMFCApplication3View::hansu_ap(int o, int d, int r, int c)
{
	CMFCApplication3Doc* pDoc = GetDocument();
	int prow = 0;
	int pcol = 0; //���� row �� col
	int count = 0;
	int max;
	int mrow = 0;
	int mcol = 0;;          //���� �� ��
	int nrow = 0;
	int ncol = 0;;          //���� ��뵹

	int superrow = 0;        //5���̻��Ͻ� row
	int supercol = 0;        //5���̻��Ͻ� col

	int ultrarow = 0;        //4_3���̻��Ͻ� 
	int ultracol = 0;		 //4_3���̻��Ͻ� 

	int change = 0;            //4_3���̻��Ͻ�
	int change2 = 0;           //5���̻��Ͻ�

	int row, col;

	int chrow, chcol;

	/* ù�� ���� ���� ù���� ���������� �����ƾ��ϰų� �����ؾ��Ѵٸ� */
	{   //�� ��ȣ�� ���п��̴�.
		for (chrow = 0; chrow < 19; chrow++)
			for (chcol = 0; chcol < 19; chcol++) {
				ibaduk[chrow][chcol] = 0;
			}
		for (chrow = 0; chrow < 19; chrow++)
			for (chcol = 0; chcol < 19; chcol++) {
				obaduk[chrow][chcol] = 0;
			}
		for (chrow = 0; chrow < 19; chrow++)
			for (chcol = 0; chcol < 19; chcol++) {
				dbaduk[chcol][chcol] = 0;
			}
		offendWeight_three_by_three(2, 1);      // 33���� �ڵ�, 43 üũ �ڵ�
		dffendWeight_three_by_three(1, 2);


		OffendWeight5(2, 1);                   // 4�� �ɶ� ���ݰ� ���
		OffendWeight5_2(2, 1);	               // 2�� 2�� ���� ������ ������ ��� ����
		OffendWeight5_3(2, 1);		           // 3�� 1�� ������ ������ ��� ����

		OffendWeight6(2, 1);				   // 6�� �����ڵ� 
		OffendWeight6_2(2, 1);
		OffendWeight6_3(2, 1);

		OffendWeight4(2, 1);                   // 3���� ���ӵɰ�� ���ݰ� ���
		OffendWeight4_2(2, 1);                 // 2�� 1�� ������ ������ ��� ����

		OffendWeight(2, 1);                    // ���� �Ű������� ���ǵ� , ���� �Ű������� ����� ��
		defendWeight(2, 1);
		max = 0;

		mrow = 0; mcol = 0;



		for (chrow = 0; chrow < 19; chrow++)                                    //����ġ�� �ִ밪�� ã����
			for (chcol = 0; chcol < 19; chcol++) {
				if (max < ibaduk[chrow][chcol]) {
					max = ibaduk[chrow][chcol];
					mrow = chrow;
					mcol = chcol;
				}
			}


		if (max >= 20000)
		{
			change2 = 1;
			superrow = mrow;
			supercol = mcol;
			
			
			CString s;                                         // ��� ������ ǥ�����ִ°ǵ� test����
			s.Format(_T("max = %d ,m_row= %d m_col= %d "), max, mrow, mcol);
			AfxMessageBox(s);
			
			
			
		}
		else if (max >= 600)
		{
			change2 = 1;
			superrow = mrow;
			supercol = mcol;
			
			CString s;                                         // ��� ������ ǥ�����ִ°ǵ� test����
			s.Format(_T("max = %d ,m_row= %d m_col= %d "), max, mrow, mcol);
			AfxMessageBox(s);
			
			
		}


		if (change2) {
			pDoc->baduk[superrow][supercol] = 2;
			m_sunseo = true;
			Invalidate(false);
			
			return 0;
		}
		else if (change) {
			pDoc->baduk[ultrarow][ultracol] = 2;
			m_sunseo = true;
			Invalidate(false);
			
			return 0;
		}

	}
	/* ù�� ���� ���� ù���� ���������� 43 �� 5���� ������ �׳� �� �Լ��� �������´� */

	/* ���ʷ� ���� ����*/
	for (row = 0; row < 19; row++)
		for (col = 0; col < 19; col++) {

			if (pDoc->baduk[row][col] == 0) {

				pDoc->baduk[row][col] = 2;

				/* ���ʷ� ���� ����*/


				prow = row;       //previousrow ������
				pcol = col;       //previouscol ������



								  /* �ʱ�ȭ ibaduk, obaduk , dbaduk */
				for (chrow = 0; chrow < 19; chrow++)
					for (chcol = 0; chcol < 19; chcol++) {
						ibaduk[chrow][chcol] = 0;
					}
				for (chrow = 0; chrow < 19; chrow++)
					for (chcol = 0; chcol < 19; chcol++) {
						obaduk[chrow][chcol] = 0;
					}
				for (chrow = 0; chrow < 19; chrow++)
					for (chcol = 0; chcol < 19; chcol++) {
						dbaduk[chcol][chcol] = 0;
					}
				/* �ʱ�ȭ ibaduk, obaduk , dbaduk */

				/*���� ���*/
				{
					offendWeight_three_by_three(1, 2);      // 33���� �ڵ�, 43 üũ �ڵ�
					dffendWeight_three_by_three(2, 1);


					OffendWeight5(1, 2);                   // 4�� �ɶ� ���ݰ� ���
					OffendWeight5_2(1, 2);	               // 2�� 2�� ���� ������ ������ ��� ����
					OffendWeight5_3(1, 2);		           // 3�� 1�� ������ ������ ��� ����

					OffendWeight6(1, 2);				   // 6�� �����ڵ� 
					OffendWeight6_2(1, 2);
					OffendWeight6_3(1, 2);

					OffendWeight4(1, 2);                   // 3���� ���ӵɰ�� ���ݰ� ���
					OffendWeight4_2(1, 2);                 // 2�� 1�� ������ ������ ��� ����

					OffendWeight(1, 2);                    // ���� �Ű������� ���ǵ� , ���� �Ű������� ����� ��


					max = 0;

					nrow = 0; ncol = 0;
					for (int drow = 0; drow < 19; drow++)                                    //����ġ�� �ִ밪�� ã����
						for (int dcol = 0; dcol < 19; dcol++) {
							if (max < dbaduk[drow][dcol]) {
								max = dbaduk[drow][dcol];
								nrow = drow;
								ncol = dcol;
							}
						}


					pDoc->baduk[nrow][ncol] = 1;

				}
				/*���� ���*/



				/*���� �� ���*/
				{
					for (chrow = 0; chrow < 19; chrow++)
						for (chcol = 0; chcol < 19; chcol++) {
							ibaduk[chrow][chcol] = 0;
						}
					for (chrow = 0; chrow < 19; chrow++)
						for (chcol = 0; chcol < 19; chcol++) {
							obaduk[chrow][chcol] = 0;
						}
					for (chrow = 0; chrow < 19; chrow++)
						for (chcol = 0; chcol < 19; chcol++) {
							dbaduk[chcol][chcol] = 0;
						}

					offendWeight_three_by_three(2, 1);      // 33���� �ڵ�, 43 üũ �ڵ�
					dffendWeight_three_by_three(1, 2);


					OffendWeight5(2, 1);                   // 4�� �ɶ� ���ݰ� ���
					OffendWeight5_2(2, 1);	               // 2�� 2�� ���� ������ ������ ��� ����
					OffendWeight5_3(2, 1);		           // 3�� 1�� ������ ������ ��� ����

					OffendWeight6(2, 1);				   // 6�� �����ڵ� 
					OffendWeight6_2(2, 1);
					OffendWeight6_3(2, 1);

					OffendWeight4(2, 1);                   // 3���� ���ӵɰ�� ���ݰ� ���
					OffendWeight4_2(2, 1);                 // 2�� 1�� ������ ������ ��� ����

					OffendWeight(2, 1);                    // ���� �Ű������� ���ǵ� , ���� �Ű������� ����� ��


					max = 0;

					mrow = 0; mcol = 0;


					for (int orow = 0; orow < 19; orow++)                                    //����ġ�� �ִ밪�� ã����
						for (int ocol = 0; ocol < 19; ocol++) {
							if (obaduk[orow][col] >0) {
								if (max < obaduk[orow][ocol]) {
									max = obaduk[orow][ocol];
									mrow = row;
									mcol = col;
								}
							}
						}
				}

				/*���� �� ���*/




				/* 43���̰ų� 5���̻��Ͻ� ���� ����*/
				if (max >= 900)
				{

					ultrarow = mrow;
					ultracol = mcol;
				}
				if (max >= 20000)
				{

					superrow = mrow;
					supercol = mcol;
				}
				/* 43���̰ų� 5���̻��Ͻ� ���� ����*/

				/*
				Invalidate(false);
				CString s;                                         // ��� ������ ǥ�����ִ°ǵ� test����
				s.Format(_T("max = %d ,ultrarow= %d ultracol= %d "), max, ultrarow, ultracol);
				AfxMessageBox(s);
				*/

				/* �ݺ����� 1���̻� �������� ������ �� ��뵹 ����*/
				count++;

				if (count > 0)
				{
					pDoc->baduk[prow][pcol] = 0;
					pDoc->baduk[nrow][ncol] = 0;
				}
				/* �ݺ����� 1���̻� �������� ������ �� ��뵹 ����*/
			}


		}  // �ݺ��� ��

	pDoc->baduk[row][col] = 0; // �������� ����


	change = 0;
	change2 = 0;

	/* ultra �� super�� ���� �������� change���� ����*/
	if (ultrarow > 0)
		if (ultracol > 0)
		{
			change = 1;
		}
	if (superrow > 0)
		if (supercol > 0)
		{
			change = 1;
		}
	/* ultra �� super�� ���� �������� change���� ����*/

	/* change���� �������� �����ϰ� �ƴϸ� �׳� AI_WHITE_DO ����*/
	if (change2) {
		/*
		CString s;                                         // ��� ������ ǥ�����ִ°ǵ� test����
		s.Format(_T("max = %d ,m_row= %d m_col= %d "), max, superrow, supercol);
		AfxMessageBox(s);
		*/
		pDoc->baduk[superrow][supercol] = 2;
		m_sunseo = true;
		Invalidate(false);
		
		return 0;
	}
	else if (change) {
		/*
		CString s;                                         // ��� ������ ǥ�����ִ°ǵ� test����
		s.Format(_T("max = %d ,m_row= %d m_col= %d "), max, ultrarow, ultracol);
		AfxMessageBox(s);
		*/
		pDoc->baduk[ultrarow][ultracol] = 2;
		m_sunseo = true;
		Invalidate(false);
		
		return 0;
	}

	else AI_White_Do(r, c);
	/* change���� �������� �����ϰ� �ƴϸ� �׳� AI_WHITE_DO ����*/

}


int CMFCApplication3View::AI_White_Do(int r, int c)
{

	{
		CMFCApplication3Doc* pDoc = GetDocument();




		//===============================================================
		// ����, ��� �˰���
		//===============================================================

		int count = 0;
		int row, col;
		int tr, tc;
		int max, mrow, mcol;

		for (row = 0; row < 19; row++)
			for (col = 0; col < 19; col++) {
				ibaduk[row][col] = 0;
			}

		offendWeight_three_by_three(2, 1);      // 33���� �ڵ�, 43 üũ �ڵ�
		dffendWeight_three_by_three(1, 2);


		OffendWeight5(2, 1);                   // 4�� �ɶ� ���ݰ� ���
		OffendWeight5_2(2, 1);	               // 2�� 2�� ���� ������ ������ ��� ����
		OffendWeight5_3(2, 1);		           // 3�� 1�� ������ ������ ��� ����

		OffendWeight6(2, 1);				   // 6�� �����ڵ� 
		OffendWeight6_2(2, 1);
		OffendWeight6_3(2, 1);

		OffendWeight4(2, 1);                   // 3���� ���ӵɰ�� ���ݰ� ���
		OffendWeight4_2(2, 1);                 // 2�� 1�� ������ ������ ��� ����
											   /*
											   OffendWeight4_3_1(2, 1);
											   OffendWeight4_3(2, 1);                 // 43�ڵ�
											   OffendWeight4_3_2(2, 1);
											   OffendWeight4_3_3(2, 1);
											   */
		OffendWeight3(2, 1);
		OffendWeight(2, 1);                    // ���� �Ű������� ���ǵ� , ���� �Ű������� ����� ��
		defendWeight(2, 1);
		max = 0;

		mrow = 0; mcol = 0;
		for (row = 0; row < 19; row++)                                    //����ġ�� �ִ밪�� ã����
			for (col = 0; col < 19; col++) {
				if (max < ibaduk[row][col]) {
					max = ibaduk[row][col];
					mrow = row;
					mcol = col;
				}
				else if (max == ibaduk[row][col]) {
					if (pDoc->baduk[row + 1][col] == 2) { mrow = row; mcol = col; }    //�ִ밪�� ���̰� ���� �� �ִ��� ������ ���� ���� ���� �ִ°��� ������
					else if (pDoc->baduk[row - 1][col + 1] == 2) { mrow = row; mcol = col; }
					else if (pDoc->baduk[row][col + 1] == 2) { mrow = row; mcol = col; }
					else if (pDoc->baduk[row][col - 1] == 2) { mrow = row; mcol = col; }
					else if (pDoc->baduk[row - 1][col - 1] == 2) { mrow = row; mcol = col; }
					else if (pDoc->baduk[row + 1][col - 1] == 2) { mrow = row; mcol = col; }
					else if (pDoc->baduk[row + 1][col - 1] == 2) { mrow = row; mcol = col; }
					else if (pDoc->baduk[row - 1][col + 1] == 2) { mrow = row; mcol = col; }
				}

			}

		
		CString s;                                         // ��� ������ ǥ�����ִ°ǵ� test����
		s.Format(_T("max = %d ,m_row= %d m_col= %d "), max, mrow, mcol);
		AfxMessageBox(s);
		
		

		if (max <= 0) {                     // ù���� �׳� ����� ���콺 Ŭ���� ���� �д�
			tr = r + 1; tc = c + 1;
			if (tr <= 18 || tc <= 18)          //�⺻�밢��
			{
				if (pDoc->baduk[tr][tc] == 0) {
					pDoc->baduk[tr][tc] = 2;
					m_sunseo = true;
					m_row = tr; m_col = tc;
					c_row = m_row;
					c_col = m_col;
					Invalidate(false);
					return 1;
				}
			}
			tr = r; tc = c + 1;
			if (tr <= 18)                   //�װžȵǸ� ������
			{
				if (pDoc->baduk[tr][tc] == 0) {
					pDoc->baduk[tr][tc] = 2;
					m_sunseo = true;
					m_row = tr; m_col = tc;
					c_row = m_row;
					c_col = m_col;
					Invalidate(false);
					return 1;
				}
			}
			tr = r + 1; tc = c;
			if (tr <= 18)                    //�װžȵǸ� ��
			{
				if (pDoc->baduk[tr][tc] == 0) {
					pDoc->baduk[tr][tc] = 2;
					m_sunseo = true;
					m_row = tr; m_col = tc;
					c_row = m_row;
					c_col = m_col;
					Invalidate(false);
					return 1;
				}
			}

		}
		else                                  //�׻�Ȳ�ܿ��� ����ġ�� ���� �д�.
			pDoc->baduk[mrow][mcol] = 2;
		
		m_sunseo = true;
		c_row = mrow;
		c_col = mcol;
		Invalidate(false);
		return 1;

	}
	
}








void CMFCApplication3View::OffendWeight6(int o, int d) { //5�� �̻��϶� ������ �������� ��� ���°� ����
	CMFCApplication3Doc* pDoc = GetDocument();
	int i;
	int check_vertical = 0; // ���ι��� üũ ����
	int check_beside_vertical = 0; //  ���ι��� üũ ����
	int check_horizontal = 0; // ���ι��� üũ ����
	int check_beside_horizontal = 0; // ���ι��� üũ ����
	int check_diagonal = 0;  // �Ϲݴ밢���� ���
	int check_beside_diagonal = 0; // �Ϲݴ밢���� ���
	int check_reverse_diagonal = 0; //�Ϲݴ밢���� �ݴ� ���
	int check_reverse_beside_diagonal = 0; // �Ϲ� �밢���� �ݴ� ���

	int row, col;

	for (row = 0; row < 19; row++)
		for (col = 0; col < 19; col++) {
			check_vertical = 0; //  ���ι��� üũ ����
			check_beside_vertical = 0; //  ���ι��� üũ ����
			check_horizontal = 0; // ���ι��� üũ ����
			check_beside_horizontal = 0; // ���ι��� üũ ����
			check_diagonal = 0;  // �Ϲݴ밢���� ���
			check_beside_diagonal = 0; // �Ϲݴ밢���� ���
			check_reverse_diagonal = 0; //�Ϲݴ밢���� �ݴ� ���
			check_reverse_beside_diagonal = 0; // �Ϲ� �밢���� �ݴ� ���

			if (pDoc->baduk[row][col] == 0) {
				for (i = 1; i < 6; i++) {

					if (col - i < 0) break;
					if (pDoc->baduk[row][col - i] == o) { check_beside_horizontal++; }
				}


				for (i = 1; i < 6; i++) {
					if (col + i > 19) break;
					if (pDoc->baduk[row][col + i] == o) { check_horizontal++; };
				}


				for (i = 1; i < 6; i++) {
					if (row - i < 0) break;
					if (pDoc->baduk[row - i][col] == o) { check_beside_vertical++; }
				}


				for (i = 1; i < 6; i++) {
					if (row + i > 19) break;
					if (pDoc->baduk[row + i][col] == o) { check_vertical++; }
				}

				for (i = 1; i < 6; i++) {
					if (row + i > 19 || col + i > 19) break;
					if (pDoc->baduk[row + i][col + i] == o) { check_diagonal++; }
				}

				for (i = 1; i < 6; i++) {
					if (row - i < 0 || col - i <  0) break;
					if (pDoc->baduk[row - i][col - i] == o) { check_beside_diagonal++; }
				}

				for (i = 1; i < 6; i++) {
					if (row - i < 0 || col + i > 19) break;
					if (pDoc->baduk[row - i][col + i] == o) { check_reverse_diagonal++; }
				}

				for (i = 1; i < 6; i++) {
					if (row + i > 19 || col - i < 0) break;
					if (pDoc->baduk[row + i][col - i] == o) { check_reverse_beside_diagonal++; }
				}
				if (check_horizontal == 5)
				{
					ibaduk[row][col] -= six;
					obaduk[row][col] -= six;
				}
				else if (check_beside_horizontal == 5)
				{
					ibaduk[row][col] -= six;
					obaduk[row][col] -= six;
				}
				else if (check_vertical == 5)
				{
					ibaduk[row][col] -= six;
					obaduk[row][col] -= six;
				}
				else if (check_beside_vertical == 5)
				{
					ibaduk[row][col] -= six;
					obaduk[row][col] -= six;
				}
				else if (check_diagonal == 5)
				{
					ibaduk[row][col] -= six;
					obaduk[row][col] -= six;
				}
				else if (check_beside_diagonal == 5)
				{
					ibaduk[row][col] -= six;
					obaduk[row][col] -= six;
				}
				else if (check_reverse_diagonal == 5)
				{
					ibaduk[row][col] -= six;
					obaduk[row][col] -= six;
				}
				else if (check_reverse_beside_diagonal == 5)
				{
					ibaduk[row][col] -= six;
					obaduk[row][col] -= six;
				}
			}
			else
			{
				ibaduk[row][col] = 0;
				obaduk[row][col] = 0;
			}
		}

	for (row = 0; row < 19; row++)
		for (col = 0; col < 19; col++) {
			check_vertical = 0; //  ���ι��� üũ ����
			check_beside_vertical = 0; //  ���ι��� üũ ����
			check_horizontal = 0; // ���ι��� üũ ����
			check_beside_horizontal = 0; // ���ι��� üũ ����
			check_diagonal = 0;  // �Ϲݴ밢���� ���
			check_beside_diagonal = 0; // �Ϲݴ밢���� ���
			check_reverse_diagonal = 0; //�Ϲݴ밢���� �ݴ� ���
			check_reverse_beside_diagonal = 0; // �Ϲ� �밢���� �ݴ� ���

			if (pDoc->baduk[row][col] == 0) {
				for (i = 1; i < 6; i++) {
					if (col - i < 0) break; // ���ΰ� 0 �̸� �ݺ�Ż��
					if (pDoc->baduk[row][col - i] == d) { check_beside_horizontal++; }
				}

				for (i = 1; i < 6; i++) {
					if (col + i > 19) break;
					if (pDoc->baduk[row][col + i] == d) { check_horizontal++; };
				}

				for (i = 1; i < 6; i++) {
					if (row - i < 0) break;
					if (pDoc->baduk[row - i][col] == d) { check_beside_vertical++; }
				}

				for (i = 1; i < 6; i++) {
					if (row + i > 19) break;
					if (pDoc->baduk[row + i][col] == d) { check_vertical++; }
				}

				for (i = 1; i < 6; i++) {
					if (row + i > 19 || col + i > 19) break;
					if (pDoc->baduk[row + i][col + i] == d) { check_diagonal++; }

				}

				for (i = 1; i < 6; i++) {
					if (row - i < 0 || col - i <  0) break;
					if (pDoc->baduk[row - i][col - i] == d) { check_beside_diagonal++; }
				}

				for (i = 1; i < 6; i++) {
					if (row - i < 0 || col + i > 19) break;
					if (pDoc->baduk[row - i][col + i] == d) { check_reverse_diagonal++; }
				}

				for (i = 1; i < 6; i++) {
					if (row + i > 19 || col - i < 0) break;
					if (pDoc->baduk[row + i][col - i] == d) { check_reverse_beside_diagonal++; }
				}
				if (check_horizontal == 5)
				{
					ibaduk[row][col] -= six;
					dbaduk[row][col] -= six;
				}
				if (check_beside_horizontal == 5)
				{
					ibaduk[row][col] -= six;
					dbaduk[row][col] -= six;
				}
				if (check_vertical == 5)
				{
					ibaduk[row][col] -= six;
					dbaduk[row][col] -= six;
				}
				if (check_beside_vertical == 5)
				{
					ibaduk[row][col] -= six;
					dbaduk[row][col] -= six;
				}
				if (check_diagonal == 5)
				{
					ibaduk[row][col] -= six;
					dbaduk[row][col] -= six;
				}
				if (check_beside_diagonal == 5)
				{
					ibaduk[row][col] -= six;
					dbaduk[row][col] -= six;
				}
				if (check_reverse_diagonal == 5)
				{
					ibaduk[row][col] -= six;
					dbaduk[row][col] -= six;
				}
				if (check_reverse_beside_diagonal == 5)
				{
					ibaduk[row][col] -= six;
					dbaduk[row][col] -= six;
				}

			}
			else {
				ibaduk[row][col] = 0;
				dbaduk[row][col] = 0;
			}
		}
}

void CMFCApplication3View::OffendWeight6_2(int o, int d) { //6�� �����ڵ�
	CMFCApplication3Doc* pDoc = GetDocument();
	int i;
	int check_vertical = 0; // ���ι��� üũ ����
	int check_beside_vertical = 0; //  ���ι��� üũ ����
	int check_horizontal = 0; // ���ι��� üũ ����
	int check_beside_horizontal = 0; // ���ι��� üũ ����
	int check_diagonal = 0;  // �Ϲݴ밢���� ���
	int check_beside_diagonal = 0; // �Ϲݴ밢���� ���
	int check_reverse_diagonal = 0; //�Ϲݴ밢���� �ݴ� ���
	int check_reverse_beside_diagonal = 0; // �Ϲ� �밢���� �ݴ� ���

	int check_vertical2 = 0; // ���ι��� üũ ����
	int check_beside_vertical2 = 0; //  ���ι��� üũ ����
	int check_horizontal2 = 0; // ���ι��� üũ ����
	int check_beside_horizontal2 = 0; // ���ι��� üũ ����
	int check_diagonal2 = 0;  // �Ϲݴ밢���� ���
	int check_beside_diagonal2 = 0; // �Ϲݴ밢���� ���
	int check_reverse_diagonal2 = 0; //�Ϲݴ밢���� �ݴ� ���
	int check_reverse_beside_diagonal2 = 0; // �Ϲ� �밢���� �ݴ� ���
	int row, col;

	/* ***��** �ΰ�쿡 �� �� ���� �����ʰ���. �����ǰ��*/
	for (row = 0; row < 19; row++)
		for (col = 0; col < 19; col++) {
			check_vertical = 0; //  ���ι��� üũ ����
			check_beside_vertical = 0; //  ���ι��� üũ ����
			check_horizontal = 0; // ���ι��� üũ ����
			check_beside_horizontal = 0; // ���ι��� üũ ����
			check_diagonal = 0;  // �Ϲݴ밢���� ���
			check_beside_diagonal = 0; // �Ϲݴ밢���� ���
			check_reverse_diagonal = 0; //�Ϲݴ밢���� �ݴ� ���
			check_reverse_beside_diagonal = 0; // �Ϲ� �밢���� �ݴ� ���


			check_vertical2 = 0; //  ���ι��� üũ ����   	   2 ���˻�
			check_beside_vertical2 = 0; //  ���ι��� üũ ����
			check_horizontal2 = 0; // ���ι��� üũ ����
			check_beside_horizontal2 = 0; // ���ι��� üũ ����
			check_diagonal2 = 0;  // �Ϲݴ밢���� ���
			check_beside_diagonal2 = 0; // �Ϲݴ밢���� ���
			check_reverse_diagonal2 = 0; //�Ϲݴ밢���� �ݴ� ���
			check_reverse_beside_diagonal2 = 0; // �Ϲ� �밢���� �ݴ� ���

			if (pDoc->baduk[row][col] == 0) {
				for (i = 1; i < 4; i++) {

					if (col - i < 0) break;
					if (pDoc->baduk[row][col - i] == o) { check_beside_horizontal++; }   // 3��üũ
				}

				for (i = 1; i < 3; i++) {

					if (col - i < 0) break;
					if (pDoc->baduk[row][col - i] == o) { check_beside_horizontal2++; }  // 2��üũ
				}

				for (i = 1; i < 4; i++) {
					if (col + i > 19) break;
					if (pDoc->baduk[row][col + i] == o) { check_horizontal++; };
				}

				for (i = 1; i < 3; i++) {
					if (col + i > 19) break;
					if (pDoc->baduk[row][col + i] == o) { check_horizontal2++; };
				}

				for (i = 1; i < 4; i++) {
					if (row - i < 0) break;
					if (pDoc->baduk[row - i][col] == o) { check_beside_vertical++; }
				}


				for (i = 1; i < 3; i++) {
					if (row - i < 0) break;
					if (pDoc->baduk[row - i][col] == o) { check_beside_vertical2++; }
				}

				for (i = 1; i < 4; i++) {
					if (row + i > 19) break;
					if (pDoc->baduk[row + i][col] == o) { check_vertical++; }
				}

				for (i = 1; i < 3; i++) {
					if (row + i > 19) break;
					if (pDoc->baduk[row + i][col] == o) { check_vertical2++; }
				}

				for (i = 1; i < 4; i++) {
					if (row + i > 19 || col + i > 19) break;
					if (pDoc->baduk[row + i][col + i] == o) { check_diagonal++; }
				}

				for (i = 1; i < 3; i++) {
					if (row + i > 19 || col + i > 19) break;
					if (pDoc->baduk[row + i][col + i] == o) { check_diagonal2++; }
				}

				for (i = 1; i < 4; i++) {
					if (row - i < 0 || col - i <  0) break;
					if (pDoc->baduk[row - i][col - i] == o) { check_beside_diagonal++; }
				}

				for (i = 1; i < 3; i++) {
					if (row - i < 0 || col - i <  0) break;
					if (pDoc->baduk[row - i][col - i] == o) { check_beside_diagonal2++; }
				}

				for (i = 1; i < 4; i++) {
					if (row - i < 0 || col + i > 19) break;
					if (pDoc->baduk[row - i][col + i] == o) { check_reverse_diagonal++; }
				}

				for (i = 1; i < 3; i++) {
					if (row - i < 0 || col + i > 19) break;
					if (pDoc->baduk[row - i][col + i] == o) { check_reverse_diagonal2++; }
				}

				for (i = 1; i < 4; i++) {
					if (row + i > 19 || col - i < 0) break;
					if (pDoc->baduk[row + i][col - i] == o) { check_reverse_beside_diagonal++; }
				}

				for (i = 1; i < 3; i++) {
					if (row + i > 19 || col - i < 0) break;
					if (pDoc->baduk[row + i][col - i] == o) { check_reverse_beside_diagonal2++; }
				}

				if (check_horizontal == 3 && check_beside_horizontal2 == 2)
				{
					ibaduk[row][col] -= six;
					obaduk[row][col] -= six;
				}
				if (check_horizontal2 == 2 && check_beside_horizontal == 3)
				{
					ibaduk[row][col] -= six;
					obaduk[row][col] -= six;
				}

				if (check_vertical == 3 && check_beside_vertical2 == 2)
				{
					ibaduk[row][col] -= six;
					obaduk[row][col] -= six;
				}
				if (check_vertical2 == 2 && check_beside_vertical == 3)
				{
					ibaduk[row][col] -= six;
					obaduk[row][col] -= six;
				}

				if (check_diagonal == 3 && check_beside_diagonal2 == 2)
				{
					ibaduk[row][col] -= six;
					obaduk[row][col] -= six;
				}
				if (check_diagonal2 == 2 && check_beside_diagonal == 3)
				{
					ibaduk[row][col] -= six;
					obaduk[row][col] -= six;
				}

				if (check_reverse_diagonal == 3 && check_reverse_beside_diagonal2 == 2)
				{
					ibaduk[row][col] -= six;
					obaduk[row][col] -= six;
				}
				if (check_reverse_diagonal2 == 2 && check_reverse_beside_diagonal == 3)
				{
					ibaduk[row][col] -= six;
					obaduk[row][col] -= six;
				}
			}
			else
			{
				ibaduk[row][col] = 0;
				obaduk[row][col] = 0;
			}
		}
	/* ***��** �ΰ�쿡 �� �� ���� �����ʰ���. �����ǰ��*/

	/* ***��** �ΰ�쿡 �� �� ���� �����ʰ���. �����ǰ��*/
	for (row = 0; row < 19; row++)
		for (col = 0; col < 19; col++) {
			check_vertical = 0; //  ���ι��� üũ ����        3 �� �˻�
			check_beside_vertical = 0; //  ���ι��� üũ ����
			check_horizontal = 0; // ���ι��� üũ ����
			check_beside_horizontal = 0; // ���ι��� üũ ����
			check_diagonal = 0;  // �Ϲݴ밢���� ���
			check_beside_diagonal = 0; // �Ϲݴ밢���� ���
			check_reverse_diagonal = 0; //�Ϲݴ밢���� �ݴ� ���
			check_reverse_beside_diagonal = 0; // �Ϲ� �밢���� �ݴ� ���

			check_vertical2 = 0; //  ���ι��� üũ ����   	   2 ���˻�
			check_beside_vertical2 = 0; //  ���ι��� üũ ����
			check_horizontal2 = 0; // ���ι��� üũ ����
			check_beside_horizontal2 = 0; // ���ι��� üũ ����
			check_diagonal2 = 0;  // �Ϲݴ밢���� ���
			check_beside_diagonal2 = 0; // �Ϲݴ밢���� ���
			check_reverse_diagonal2 = 0; //�Ϲݴ밢���� �ݴ� ���
			check_reverse_beside_diagonal2 = 0; // �Ϲ� �밢���� �ݴ� ���

			if (pDoc->baduk[row][col] == 0) {
				for (i = 1; i < 4; i++) {

					if (col - i < 0) break;
					if (pDoc->baduk[row][col - i] == d) { check_beside_horizontal++; }   // 3��üũ
				}

				for (i = 1; i < 3; i++) {

					if (col - i < 0) break;
					if (pDoc->baduk[row][col - i] == d) { check_beside_horizontal2++; }  // 2��üũ
				}

				for (i = 1; i < 4; i++) {
					if (col + i > 19) break;
					if (pDoc->baduk[row][col + i] == d) { check_horizontal++; };
				}

				for (i = 1; i < 3; i++) {
					if (col + i > 19) break;
					if (pDoc->baduk[row][col + i] == d) { check_horizontal2++; };
				}

				for (i = 1; i < 4; i++) {
					if (row - i < 0) break;
					if (pDoc->baduk[row - i][col] == d) { check_beside_vertical++; }
				}


				for (i = 1; i < 3; i++) {
					if (row - i < 0) break;
					if (pDoc->baduk[row - i][col] == d) { check_beside_vertical2++; }
				}

				for (i = 1; i < 4; i++) {
					if (row + i > 19) break;
					if (pDoc->baduk[row + i][col] == d) { check_vertical++; }
				}

				for (i = 1; i < 3; i++) {
					if (row + i > 19) break;
					if (pDoc->baduk[row + i][col] == d) { check_vertical2++; }
				}

				for (i = 1; i < 4; i++) {
					if (row + i > 19 || col + i > 19) break;
					if (pDoc->baduk[row + i][col + i] == d) { check_diagonal++; }
				}

				for (i = 1; i < 3; i++) {
					if (row + i > 19 || col + i > 19) break;
					if (pDoc->baduk[row + i][col + i] == d) { check_diagonal2++; }
				}

				for (i = 1; i < 4; i++) {
					if (row - i < 0 || col - i <  0) break;
					if (pDoc->baduk[row - i][col - i] == d) { check_beside_diagonal++; }
				}

				for (i = 1; i < 3; i++) {
					if (row - i < 0 || col - i <  0) break;
					if (pDoc->baduk[row - i][col - i] == d) { check_beside_diagonal2++; }
				}

				for (i = 1; i < 4; i++) {
					if (row - i < 0 || col + i > 19) break;
					if (pDoc->baduk[row - i][col + i] == d) { check_reverse_diagonal++; }
				}

				for (i = 1; i < 3; i++) {
					if (row - i < 0 || col + i > 19) break;
					if (pDoc->baduk[row - i][col + i] == d) { check_reverse_diagonal2++; }
				}

				for (i = 1; i < 4; i++) {
					if (row + i > 19 || col - i < 0) break;
					if (pDoc->baduk[row + i][col - i] == d) { check_reverse_beside_diagonal++; }
				}

				for (i = 1; i < 3; i++) {
					if (row + i > 19 || col - i < 0) break;
					if (pDoc->baduk[row + i][col - i] == d) { check_reverse_beside_diagonal2++; }
				}

				if (check_horizontal == 3 && check_beside_horizontal2 == 2)
				{
					ibaduk[row][col] -= six;
					dbaduk[row][col] -= six;
				}
				if (check_horizontal2 == 2 && check_beside_horizontal == 3)
				{
					ibaduk[row][col] -= six;
					dbaduk[row][col] -= six;
				}

				if (check_vertical == 3 && check_beside_vertical2 == 2)
				{
					ibaduk[row][col] -= six;
					dbaduk[row][col] -= six;
				}
				if (check_vertical2 == 2 && check_beside_vertical == 3)
				{
					ibaduk[row][col] -= six;
					dbaduk[row][col] -= six;
				}

				if (check_diagonal == 3 && check_beside_diagonal2 == 2)
				{
					ibaduk[row][col] -= six;
					dbaduk[row][col] -= six;
				}
				if (check_diagonal2 == 2 && check_beside_diagonal == 3)
				{
					ibaduk[row][col] -= six;
					dbaduk[row][col] -= six;
				}

				if (check_reverse_diagonal == 3 && check_reverse_beside_diagonal2 == 2)
				{
					ibaduk[row][col] -= six;
					dbaduk[row][col] -= six;
				}
				if (check_reverse_diagonal2 == 2 && check_reverse_beside_diagonal == 3)
				{
					ibaduk[row][col] -= six;
					dbaduk[row][col] -= six;
				}
			}
			else
			{
				ibaduk[row][col] = 0;
				dbaduk[row][col] = 0;
			}
		}
}

void CMFCApplication3View::OffendWeight6_3(int o, int d) { //6�� �����ڵ�
	CMFCApplication3Doc* pDoc = GetDocument();
	int i;
	int check_vertical = 0; // ���ι��� üũ ����             4���˻�
	int check_beside_vertical = 0; //  ���ι��� üũ ����
	int check_horizontal = 0; // ���ι��� üũ ����
	int check_beside_horizontal = 0; // ���ι��� üũ ����
	int check_diagonal = 0;  // �Ϲݴ밢���� ���
	int check_beside_diagonal = 0; // �Ϲݴ밢���� ���
	int check_reverse_diagonal = 0; //�Ϲݴ밢���� �ݴ� ���
	int check_reverse_beside_diagonal = 0; // �Ϲ� �밢���� �ݴ� ���

	int check_vertical2 = 0; // ���ι��� üũ ����            1 ���˻�
	int check_beside_vertical2 = 0; //  ���ι��� üũ ����
	int check_horizontal2 = 0; // ���ι��� üũ ����
	int check_beside_horizontal2 = 0; // ���ι��� üũ ����
	int check_diagonal2 = 0;  // �Ϲݴ밢���� ���
	int check_beside_diagonal2 = 0; // �Ϲݴ밢���� ���
	int check_reverse_diagonal2 = 0; //�Ϲݴ밢���� �ݴ� ���
	int check_reverse_beside_diagonal2 = 0; // �Ϲ� �밢���� �ݴ� ���
	int row, col;

	/* ****��* �ΰ�쿡 �� �� ���� �����ʰ���. �����ǰ��*/
	for (row = 0; row < 19; row++)
		for (col = 0; col < 19; col++) {
			check_vertical = 0; //  ���ι��� üũ ����
			check_beside_vertical = 0; //  ���ι��� üũ ����
			check_horizontal = 0; // ���ι��� üũ ����
			check_beside_horizontal = 0; // ���ι��� üũ ����
			check_diagonal = 0;  // �Ϲݴ밢���� ���
			check_beside_diagonal = 0; // �Ϲݴ밢���� ���
			check_reverse_diagonal = 0; //�Ϲݴ밢���� �ݴ� ���
			check_reverse_beside_diagonal = 0; // �Ϲ� �밢���� �ݴ� ���


			check_vertical2 = 0; //  ���ι��� üũ ����   	   2 ���˻�
			check_beside_vertical2 = 0; //  ���ι��� üũ ����
			check_horizontal2 = 0; // ���ι��� üũ ����
			check_beside_horizontal2 = 0; // ���ι��� üũ ����
			check_diagonal2 = 0;  // �Ϲݴ밢���� ���
			check_beside_diagonal2 = 0; // �Ϲݴ밢���� ���
			check_reverse_diagonal2 = 0; //�Ϲݴ밢���� �ݴ� ���
			check_reverse_beside_diagonal2 = 0; // �Ϲ� �밢���� �ݴ� ���

			if (pDoc->baduk[row][col] == 0) {
				for (i = 1; i < 5; i++) {

					if (col - i < 0) break;
					if (pDoc->baduk[row][col - i] == o) { check_beside_horizontal++; }   // 3��üũ
				}

				for (i = 1; i < 2; i++) {

					if (col - i < 0) break;
					if (pDoc->baduk[row][col - i] == o) { check_beside_horizontal2++; }  // 2��üũ
				}

				for (i = 1; i < 5; i++) {
					if (col + i > 19) break;
					if (pDoc->baduk[row][col + i] == o) { check_horizontal++; };
				}

				for (i = 1; i < 2; i++) {
					if (col + i > 19) break;
					if (pDoc->baduk[row][col + i] == o) { check_horizontal2++; };
				}

				for (i = 1; i < 5; i++) {
					if (row - i < 0) break;
					if (pDoc->baduk[row - i][col] == o) { check_beside_vertical++; }
				}


				for (i = 1; i < 2; i++) {
					if (row - i < 0) break;
					if (pDoc->baduk[row - i][col] == o) { check_beside_vertical2++; }
				}

				for (i = 1; i < 5; i++) {
					if (row + i > 19) break;
					if (pDoc->baduk[row + i][col] == o) { check_vertical++; }
				}

				for (i = 1; i < 2; i++) {
					if (row + i > 19) break;
					if (pDoc->baduk[row + i][col] == o) { check_vertical2++; }
				}

				for (i = 1; i < 5; i++) {
					if (row + i > 19 || col + i > 19) break;
					if (pDoc->baduk[row + i][col + i] == o) { check_diagonal++; }
				}

				for (i = 1; i < 2; i++) {
					if (row + i > 19 || col + i > 19) break;
					if (pDoc->baduk[row + i][col + i] == o) { check_diagonal2++; }
				}

				for (i = 1; i < 5; i++) {
					if (row - i < 0 || col - i <  0) break;
					if (pDoc->baduk[row - i][col - i] == o) { check_beside_diagonal++; }
				}

				for (i = 1; i < 2; i++) {
					if (row - i < 0 || col - i <  0) break;
					if (pDoc->baduk[row - i][col - i] == o) { check_beside_diagonal2++; }
				}

				for (i = 1; i < 5; i++) {
					if (row - i < 0 || col + i > 19) break;
					if (pDoc->baduk[row - i][col + i] == o) { check_reverse_diagonal++; }
				}

				for (i = 1; i < 2; i++) {
					if (row - i < 0 || col + i > 19) break;
					if (pDoc->baduk[row - i][col + i] == o) { check_reverse_diagonal2++; }
				}

				for (i = 1; i < 5; i++) {
					if (row + i > 19 || col - i < 0) break;
					if (pDoc->baduk[row + i][col - i] == o) { check_reverse_beside_diagonal++; }
				}

				for (i = 1; i < 2; i++) {
					if (row + i > 19 || col - i < 0) break;
					if (pDoc->baduk[row + i][col - i] == o) { check_reverse_beside_diagonal2++; }
				}

				if (check_horizontal == 4 && check_beside_horizontal2 == 1)
				{
					ibaduk[row][col] -= six;
					obaduk[row][col] -= six;
				}
				if (check_horizontal2 == 1 && check_beside_horizontal == 4)
				{
					ibaduk[row][col] -= six;
					obaduk[row][col] -= six;
				}

				if (check_vertical == 4 && check_beside_vertical2 == 1)
				{
					ibaduk[row][col] -= six;
					obaduk[row][col] -= six;
				}
				if (check_vertical2 == 1 && check_beside_vertical == 4)
				{
					ibaduk[row][col] -= six;
					obaduk[row][col] -= six;
				}

				if (check_diagonal == 4 && check_beside_diagonal2 == 1)
				{
					ibaduk[row][col] -= six;
					obaduk[row][col] -= six;
				}
				if (check_diagonal2 == 1 && check_beside_diagonal == 4)
				{
					ibaduk[row][col] -= six;
					obaduk[row][col] -= six;
				}

				if (check_reverse_diagonal == 4 && check_reverse_beside_diagonal2 == 1)
				{
					ibaduk[row][col] -= six;
					obaduk[row][col] -= six;
				}
				if (check_reverse_diagonal2 == 1 && check_reverse_beside_diagonal == 4)
				{
					ibaduk[row][col] -= six;
					obaduk[row][col] -= six;
				}
			}
			else
			{
				ibaduk[row][col] = 0;
				obaduk[row][col] = 0;
			}
		}
	/* ****��* �ΰ�쿡 �� �� ���� �����ʰ���. �����ǰ��*/

	/* ****��* �ΰ�쿡 �� �� ���� �����ʰ���. �����ǰ��*/
	for (row = 0; row < 19; row++)
		for (col = 0; col < 19; col++) {
			check_vertical = 0; //  ���ι��� üũ ����        3 �� �˻�
			check_beside_vertical = 0; //  ���ι��� üũ ����
			check_horizontal = 0; // ���ι��� üũ ����
			check_beside_horizontal = 0; // ���ι��� üũ ����
			check_diagonal = 0;  // �Ϲݴ밢���� ���
			check_beside_diagonal = 0; // �Ϲݴ밢���� ���
			check_reverse_diagonal = 0; //�Ϲݴ밢���� �ݴ� ���
			check_reverse_beside_diagonal = 0; // �Ϲ� �밢���� �ݴ� ���

			check_vertical2 = 0; //  ���ι��� üũ ����   	   2 ���˻�
			check_beside_vertical2 = 0; //  ���ι��� üũ ����
			check_horizontal2 = 0; // ���ι��� üũ ����
			check_beside_horizontal2 = 0; // ���ι��� üũ ����
			check_diagonal2 = 0;  // �Ϲݴ밢���� ���
			check_beside_diagonal2 = 0; // �Ϲݴ밢���� ���
			check_reverse_diagonal2 = 0; //�Ϲݴ밢���� �ݴ� ���
			check_reverse_beside_diagonal2 = 0; // �Ϲ� �밢���� �ݴ� ���

			if (pDoc->baduk[row][col] == 0) {
				for (i = 1; i < 5; i++) {

					if (col - i < 0) break;
					if (pDoc->baduk[row][col - i] == d) { check_beside_horizontal++; }   // 3��üũ
				}

				for (i = 1; i < 2; i++) {

					if (col - i < 0) break;
					if (pDoc->baduk[row][col - i] == d) { check_beside_horizontal2++; }  // 2��üũ
				}

				for (i = 1; i < 5; i++) {
					if (col + i > 19) break;
					if (pDoc->baduk[row][col + i] == d) { check_horizontal++; };
				}

				for (i = 1; i < 2; i++) {
					if (col + i > 19) break;
					if (pDoc->baduk[row][col + i] == d) { check_horizontal2++; };
				}

				for (i = 1; i < 5; i++) {
					if (row - i < 0) break;
					if (pDoc->baduk[row - i][col] == d) { check_beside_vertical++; }
				}


				for (i = 1; i < 2; i++) {
					if (row - i < 0) break;
					if (pDoc->baduk[row - i][col] == d) { check_beside_vertical2++; }
				}

				for (i = 1; i < 5; i++) {
					if (row + i > 19) break;
					if (pDoc->baduk[row + i][col] == d) { check_vertical++; }
				}

				for (i = 1; i < 2; i++) {
					if (row + i > 19) break;
					if (pDoc->baduk[row + i][col] == d) { check_vertical2++; }
				}

				for (i = 1; i < 5; i++) {
					if (row + i > 19 || col + i > 19) break;
					if (pDoc->baduk[row + i][col + i] == d) { check_diagonal++; }
				}

				for (i = 1; i < 2; i++) {
					if (row + i > 19 || col + i > 19) break;
					if (pDoc->baduk[row + i][col + i] == d) { check_diagonal2++; }
				}

				for (i = 1; i < 5; i++) {
					if (row - i < 0 || col - i <  0) break;
					if (pDoc->baduk[row - i][col - i] == d) { check_beside_diagonal++; }
				}

				for (i = 1; i < 2; i++) {
					if (row - i < 0 || col - i <  0) break;
					if (pDoc->baduk[row - i][col - i] == d) { check_beside_diagonal2++; }
				}

				for (i = 1; i < 5; i++) {
					if (row - i < 0 || col + i > 19) break;
					if (pDoc->baduk[row - i][col + i] == d) { check_reverse_diagonal++; }
				}

				for (i = 1; i < 2; i++) {
					if (row - i < 0 || col + i > 19) break;
					if (pDoc->baduk[row - i][col + i] == d) { check_reverse_diagonal2++; }
				}

				for (i = 1; i < 5; i++) {
					if (row + i > 19 || col - i < 0) break;
					if (pDoc->baduk[row + i][col - i] == d) { check_reverse_beside_diagonal++; }
				}

				for (i = 1; i < 2; i++) {
					if (row + i > 19 || col - i < 0) break;
					if (pDoc->baduk[row + i][col - i] == d) { check_reverse_beside_diagonal2++; }
				}

				if (check_horizontal == 4 && check_beside_horizontal2 == 1)
				{
					ibaduk[row][col] -= six;
					dbaduk[row][col] -= six;
				}
				if (check_horizontal2 == 1 && check_beside_horizontal == 4)
				{
					ibaduk[row][col] -= six;
					dbaduk[row][col] -= six;
				}


				if (check_vertical == 4 && check_beside_vertical2 == 1)
				{
					ibaduk[row][col] -= six;
					dbaduk[row][col] -= six;
				}
				if (check_vertical2 == 1 && check_beside_vertical == 4)
				{
					ibaduk[row][col] -= six;
					dbaduk[row][col] -= six;
				}

				if (check_diagonal == 4 && check_beside_diagonal2 == 1)
				{
					ibaduk[row][col] -= six;
					dbaduk[row][col] -= six;
				}
				if (check_diagonal2 == 1 && check_beside_diagonal == 4)
				{
					ibaduk[row][col] -= six;
					dbaduk[row][col] -= six;
				}

				if (check_reverse_diagonal == 4 && check_reverse_beside_diagonal2 == 1)
				{
					ibaduk[row][col] -= six;
					dbaduk[row][col] -= six;
				}
				if (check_reverse_diagonal2 == 1 && check_reverse_beside_diagonal == 4)
				{
					ibaduk[row][col] -= six;
					dbaduk[row][col] -= six;
				}
			}
			else {
				ibaduk[row][col] = 0;
				dbaduk[row][col] -= six;
			}
		}
	/* ****��* �ΰ�쿡 �� �� ���� �����ʰ���. �����ǰ��*/
}


void CMFCApplication3View::OffendWeight5(int o, int d) { // �װ��� ���� ���ӵɶ�
	CMFCApplication3Doc* pDoc = GetDocument();
	int i;
	int check_vertical = 0; // ���ι��� üũ ����
	int check_beside_vertical = 0; //  ���ι��� üũ ����
	int check_horizontal = 0; // ���ι��� üũ ����
	int check_beside_horizontal = 0; // ���ι��� üũ ����
	int check_diagonal = 0;  // �Ϲݴ밢���� ���
	int check_beside_diagonal = 0; // �Ϲݴ밢���� ���
	int check_reverse_diagonal = 0; //�Ϲݴ밢���� �ݴ� ���
	int check_reverse_beside_diagonal = 0; // �Ϲ� �밢���� �ݴ� ���

	int row, col;
	/* ====================================================================================

	�����ҵ��� 4�� ���ӵɶ� 5���� �ǵ��� ��

	=====================================================================================*/
	for (row = 0; row < 19; row++)
		for (col = 0; col < 19; col++) {
			check_vertical = 0; //  ���ι��� üũ ����
			check_beside_vertical = 0; //  ���ι��� üũ ����
			check_horizontal = 0; // ���ι��� üũ ����
			check_beside_horizontal = 0; // ���ι��� üũ ����
			check_diagonal = 0;  // �Ϲݴ밢���� ���
			check_beside_diagonal = 0; // �Ϲݴ밢���� ���
			check_reverse_diagonal = 0; //�Ϲݴ밢���� �ݴ� ���
			check_reverse_beside_diagonal = 0; // �Ϲ� �밢���� �ݴ� ���

			if (pDoc->baduk[row][col] == 0) {
				for (i = 1; i < 5; i++) {

					if (col - i < 0) break;
					if (pDoc->baduk[row][col - i] == o) { check_beside_horizontal++; }
				}


				for (i = 1; i < 5; i++) {
					if (col + i > 19) break;
					if (pDoc->baduk[row][col + i] == o) { check_horizontal++; };
				}


				for (i = 1; i < 5; i++) {
					if (row - i < 0) break;
					if (pDoc->baduk[row - i][col] == o) { check_beside_vertical++; }
				}


				for (i = 1; i < 5; i++) {
					if (row + i > 19) break;
					if (pDoc->baduk[row + i][col] == o) { check_vertical++; }
				}

				for (i = 1; i < 5; i++) {
					if (row + i > 19 || col + i > 19) break;
					if (pDoc->baduk[row + i][col + i] == o) { check_diagonal++; }
				}

				for (i = 1; i < 5; i++) {
					if (row - i < 0 || col - i <  0) break;
					if (pDoc->baduk[row - i][col - i] == o) { check_beside_diagonal++; }
				}

				for (i = 1; i < 5; i++) {
					if (row - i < 0 || col + i > 19) break;
					if (pDoc->baduk[row - i][col + i] == o) { check_reverse_diagonal++; }
				}

				for (i = 1; i < 5; i++) {
					if (row + i > 19 || col - i < 0) break;
					if (pDoc->baduk[row + i][col - i] == o) { check_reverse_beside_diagonal++; }
				}
				if (check_horizontal == 4)
				{
					ibaduk[row][col] += o_five;
					obaduk[row][col] += o_five;
				}

				else if (check_beside_horizontal == 4)
				{
					ibaduk[row][col] += o_five;
					obaduk[row][col] += o_five;
				}
				else if (check_vertical == 4)
				{
					ibaduk[row][col] += o_five;
					obaduk[row][col] += o_five;
				}
				else if (check_beside_vertical == 4)
				{
					ibaduk[row][col] += o_five;
					obaduk[row][col] += o_five;
				}
				else if (check_diagonal == 4)
				{
					ibaduk[row][col] += o_five;
					obaduk[row][col] += o_five;
				}
				else if (check_beside_diagonal == 4)
				{
					ibaduk[row][col] += o_five;
					obaduk[row][col] += o_five;
				}
				else if (check_reverse_diagonal == 4)
				{
					ibaduk[row][col] += o_five;
					obaduk[row][col] += o_five;
				}
				else if (check_reverse_beside_diagonal == 4)
				{
					ibaduk[row][col] += o_five;
					obaduk[row][col] += o_five;
				}
			}
			else
			{
				ibaduk[row][col] = 0;
				obaduk[row][col] = 0;
			}
		}
	/* ====================================================================================

	�����ҵ��� 4�� ���ӵɶ� 5���� �ǵ��� �� ������� //

	=====================================================================================*/


	/* ====================================================================================

	�����ҵ��� 4�� ���ӵɶ� ����ϵ��� ��

	=====================================================================================*/
	for (row = 0; row < 19; row++)
		for (col = 0; col < 19; col++) {
			check_vertical = 0; //  ���ι��� üũ ����
			check_beside_vertical = 0; //  ���ι��� üũ ����
			check_horizontal = 0; // ���ι��� üũ ����
			check_beside_horizontal = 0; // ���ι��� üũ ����
			check_diagonal = 0;  // �Ϲݴ밢���� ���
			check_beside_diagonal = 0; // �Ϲݴ밢���� ���
			check_reverse_diagonal = 0; //�Ϲݴ밢���� �ݴ� ���
			check_reverse_beside_diagonal = 0; // �Ϲ� �밢���� �ݴ� ���

			if (pDoc->baduk[row][col] == 0) {
				for (i = 1; i < 5; i++) {
					if (col - i < 0) break; // ���ΰ� 0 �̸� �ݺ�Ż��
					if (pDoc->baduk[row][col - i] == d) { check_beside_horizontal++; }
				}

				for (i = 1; i < 5; i++) {
					if (col + i > 19) break;
					if (pDoc->baduk[row][col + i] == d) { check_horizontal++; };
				}

				for (i = 1; i < 5; i++) {
					if (row - i < 0) break;
					if (pDoc->baduk[row - i][col] == d) { check_beside_vertical++; }
				}

				for (i = 1; i < 5; i++) {
					if (row + i > 19) break;
					if (pDoc->baduk[row + i][col] == d) { check_vertical++; }
				}

				for (i = 1; i < 5; i++) {
					if (row + i > 19 || col + i > 19) break;
					if (pDoc->baduk[row + i][col + i] == d) { check_diagonal++; }

				}

				for (i = 1; i < 5; i++) {
					if (row - i < 0 || col - i <  0) break;
					if (pDoc->baduk[row - i][col - i] == d) { check_beside_diagonal++; }
				}

				for (i = 1; i < 5; i++) {
					if (row - i < 0 || col + i > 19) break;
					if (pDoc->baduk[row - i][col + i] == d) { check_reverse_diagonal++; }
				}

				for (i = 1; i < 5; i++) {
					if (row + i > 19 || col - i < 0) break;
					if (pDoc->baduk[row + i][col - i] == d) { check_reverse_beside_diagonal++; }
				}
				if (check_horizontal == 4)
				{
					ibaduk[row][col] += d_five;
					dbaduk[row][col] += d_five;
				}
				if (check_beside_horizontal == 4) {
					ibaduk[row][col] += d_five;
					dbaduk[row][col] += d_five;
				}
				if (check_vertical == 4) {
					ibaduk[row][col] += d_five;
					dbaduk[row][col] += d_five;
				}
				if (check_beside_vertical == 4) {
					ibaduk[row][col] += d_five;
					dbaduk[row][col] += d_five;
				}
				if (check_diagonal == 4) {
					ibaduk[row][col] += d_five;
					dbaduk[row][col] += d_five;
				}
				if (check_beside_diagonal == 4) {
					ibaduk[row][col] += d_five;
					dbaduk[row][col] += d_five;
				}
				if (check_reverse_diagonal == 4) {
					ibaduk[row][col] += d_five;
					dbaduk[row][col] += d_five;
				}
				if (check_reverse_beside_diagonal == 4) {
					ibaduk[row][col] += d_five;
					dbaduk[row][col] += d_five;
				}

			}
			else {
				ibaduk[row][col] = 0;
				dbaduk[row][col] = 0;
			}
		}
	/* ====================================================================================

	�����ҵ��� 4�� ���ӵɶ� ����ϵ��� �� �������

	=====================================================================================*/
}

void CMFCApplication3View::OffendWeight5_2(int o, int d) { // 2�� 2�� ������ ������
	CMFCApplication3Doc* pDoc = GetDocument();
	int i;
	int check_vertical = 0; // ���ι��� üũ ����
	int check_beside_vertical = 0; //  ���ι��� üũ ����
	int check_horizontal = 0; // ���ι��� üũ ����
	int check_beside_horizontal = 0; // ���ι��� üũ ����
	int check_diagonal = 0;  // �Ϲݴ밢���� ���
	int check_beside_diagonal = 0; // �Ϲݴ밢���� ���
	int check_reverse_diagonal = 0; //�Ϲݴ밢���� �ݴ� ���
	int check_reverse_beside_diagonal = 0; // �Ϲ� �밢���� �ݴ� ���
	int check_point1 = 0; // ����Ʈ
	int check_point2 = 0;
	int row, col;

	/* ====================================================================================

	�����ҵ��� ����*����  �϶� *�� ���� ������

	=====================================================================================*/
	for (row = 0; row < 19; row++)
		for (col = 0; col < 19; col++) {
			check_vertical = 0; //  ���ι��� üũ ����
			check_beside_vertical = 0; //  ���ι��� üũ ����
			check_horizontal = 0; // ���ι��� üũ ����
			check_beside_horizontal = 0; // ���ι��� üũ ����
			check_diagonal = 0;  // �Ϲݴ밢���� ���
			check_beside_diagonal = 0; // �Ϲݴ밢���� ���
			check_reverse_diagonal = 0; //�Ϲݴ밢���� �ݴ� ���
			check_reverse_beside_diagonal = 0; // �Ϲ� �밢���� �ݴ� ���

			if (pDoc->baduk[row][col] == 0) {
				for (i = 1; i < 3; i++) {
					if (col - i < 0) break; // ���ΰ� 0 �̸� �ݺ�Ż��
					if (pDoc->baduk[row][col - i] == o) { check_beside_horizontal++; }
				}


				for (i = 1; i < 3; i++) {
					if (col + i > 19) break;
					if (pDoc->baduk[row][col + i] == o) { check_horizontal++; };
				}


				for (i = 1; i < 3; i++) {
					if (row - i < 0) break;
					if (pDoc->baduk[row - i][col] == o) { check_beside_vertical++; }
				}

				check_point1, check_point2 = 0;
				for (i = 1; i < 3; i++) {
					if (row + i > 19) break;
					if (pDoc->baduk[row + i][col] == o) { check_vertical++; }
				}

				for (i = 1; i < 3; i++) {
					if (row + i > 19 || col + i > 19) break;
					if (pDoc->baduk[row + i][col + i] == o) { check_diagonal++; }
				}

				for (i = 1; i < 3; i++) {
					if (row - i < 0 || col - i <  0) break;
					if (pDoc->baduk[row - i][col - i] == o) { check_beside_diagonal++; }
				}

				for (i = 1; i < 3; i++) {
					if (row - i < 0 || col + i > 19) break;
					if (pDoc->baduk[row - i][col + i] == o) { check_reverse_diagonal++; }
				}

				for (i = 1; i < 3; i++) {
					if (row + i > 19 || col - i < 0) break;
					if (pDoc->baduk[row + i][col - i] == o) { check_reverse_beside_diagonal++; }
				}
				if (check_horizontal == 2 && check_beside_horizontal == 2)
				{
					ibaduk[row][col] += o_five;
					obaduk[row][col] += o_five;
				}
				else if (check_vertical == 2 && check_beside_vertical == 2) {
					ibaduk[row][col] += o_five;
					obaduk[row][col] += o_five;
				}
				else if (check_diagonal == 2 && check_beside_diagonal == 2) {
					ibaduk[row][col] += o_five;
					obaduk[row][col] += o_five;
				}
				else if (check_reverse_diagonal == 2 && check_reverse_beside_diagonal == 2) {
					ibaduk[row][col] += o_five;
					obaduk[row][col] += o_five;
				}
			}
			else {
				ibaduk[row][col] = 0;
				obaduk[row][col] = 0;
			}
		}

	/* ====================================================================================

	�����ҵ��� ����*����  �϶� *�� ���� ������ �������

	=====================================================================================*/

	/* ====================================================================================

	�����ҵ��� **��**  �϶� ���� ���� ������

	=====================================================================================*/
	for (row = 0; row < 19; row++)
		for (col = 0; col < 19; col++) {
			check_vertical = 0; //  ���ι��� üũ ����
			check_beside_vertical = 0; //  ���ι��� üũ ����
			check_horizontal = 0; // ���ι��� üũ ����
			check_beside_horizontal = 0; // ���ι��� üũ ����
			check_diagonal = 0;  // �Ϲݴ밢���� ���
			check_beside_diagonal = 0; // �Ϲݴ밢���� ���
			check_reverse_diagonal = 0; //�Ϲݴ밢���� �ݴ� ���
			check_reverse_beside_diagonal = 0; // �Ϲ� �밢���� �ݴ� ���

			if (pDoc->baduk[row][col] == 0) {
				for (i = 1; i < 3; i++) {
					if (col - i < 0) break; // ���ΰ� 0 �̸� �ݺ�Ż��
					if (pDoc->baduk[row][col - i] == d) { check_beside_horizontal++; }
				}

				for (i = 1; i < 3; i++) {
					if (col + i > 19) break;
					if (pDoc->baduk[row][col + i] == d) { check_horizontal++; };
				}

				for (i = 1; i < 3; i++) {
					if (row - i < 0) break;
					if (pDoc->baduk[row - i][col] == d) { check_beside_vertical++; }
				}

				for (i = 1; i < 3; i++) {
					if (row + i > 19) break;
					if (pDoc->baduk[row + i][col] == d) { check_vertical++; }
				}

				for (i = 1; i < 3; i++) {
					if (row + i > 19 || col + i > 19) break;
					if (pDoc->baduk[row + i][col + i] == d) { check_diagonal++; }

				}

				for (i = 1; i < 3; i++) {
					if (row - i < 0 || col - i <  0) break;
					if (pDoc->baduk[row - i][col - i] == d) { check_beside_diagonal++; }
				}

				for (i = 1; i < 3; i++) {
					if (row - i < 0 || col + i > 19) break;
					if (pDoc->baduk[row - i][col + i] == d) { check_reverse_diagonal++; }
				}

				for (i = 1; i < 3; i++) {
					if (row + i > 19 || col - i < 0) break;
					if (pDoc->baduk[row + i][col - i] == d) { check_reverse_beside_diagonal++; }
				}
				if (check_horizontal == 2 && check_beside_horizontal == 2) {
					ibaduk[row][col] += d_five;
					dbaduk[row][col] += d_five;
				}
				else if (check_vertical == 2 && check_beside_vertical == 2) {
					ibaduk[row][col] += d_five;
					dbaduk[row][col] += d_five;
				}
				else if (check_diagonal == 2 && check_beside_diagonal == 2) {
					ibaduk[row][col] += d_five;
					dbaduk[row][col] += d_five;
				}
				else if (check_reverse_diagonal == 2 && check_reverse_beside_diagonal == 2) {
					ibaduk[row][col] += d_five;
					dbaduk[row][col] += d_five;
				}
			}
			else {
				ibaduk[row][col] = 0;
				dbaduk[row][col] = 0;
			}
		}
	/* ====================================================================================

	�����ҵ��� **��**  �϶� ���� ���� ������ �������

	=====================================================================================*/
}

void CMFCApplication3View::OffendWeight5_3(int o, int d) { // 3�� 1�� ������ ������
	CMFCApplication3Doc* pDoc = GetDocument();
	int i;
	int check_vertical = 0; // ���ι��� üũ ����
	int check_beside_vertical = 0; //  ���ι��� üũ ����
	int check_horizontal = 0; // ���ι��� üũ ����
	int check_beside_horizontal = 0; // ���ι��� üũ ����
	int check_diagonal = 0;  // �Ϲݴ밢���� ���
	int check_beside_diagonal = 0; // �Ϲݴ밢���� ���
	int check_reverse_diagonal = 0; //�Ϲݴ밢���� �ݴ� ���
	int check_reverse_beside_diagonal = 0; // �Ϲ� �밢���� �ݴ� ���
	int check_vertical_point = 0; // ����Ʈ
	int check_beside_vertical_point = 0;
	int check_horizontal_point = 0;
	int check_beside_horizontal_point = 0;
	int check_diagonal_point = 0;
	int check_beside_diagonal_point = 0;
	int check_reverse_diagonal_point = 0;
	int check_reverse_beside_diagonal_point = 0;

	int row, col;

	/* ====================================================================================

	�����ҵ��� ������*�� �϶� *�� ���� ������

	=====================================================================================*/
	for (row = 0; row < 19; row++)
		for (col = 0; col < 19; col++) {
			check_vertical = 0; //  ���ι��� üũ ����
			check_beside_vertical = 0; //  ���ι��� üũ ����
			check_horizontal = 0; // ���ι��� üũ ����
			check_beside_horizontal = 0; // ���ι��� üũ ����
			check_diagonal = 0;  // �Ϲݴ밢���� ���
			check_beside_diagonal = 0; // �Ϲݴ밢���� ���
			check_reverse_diagonal = 0; //�Ϲݴ밢���� �ݴ� ���
			check_reverse_beside_diagonal = 0; // �Ϲ� �밢���� �ݴ� ���

			int check_vertical_point = 0; // ����Ʈ
			int check_beside_vertical_point = 0;
			int check_horizontal_point = 0;
			int check_beside_horizontal_point = 0;
			int check_diagonal_point = 0;
			int check_beside_diagonal_point = 0;
			int check_reverse_diagonal_point = 0;
			int check_reverse_beside_diagonal_point = 0;

			if (pDoc->baduk[row][col] == 0) {
				for (i = 1; i < 4; i++) {
					if (col - i < 0) break;  // ���ΰ� 0 �̸� �ݺ�Ż��
					if (pDoc->baduk[row][col - i] == o) { check_beside_horizontal++; }
					if (pDoc->baduk[row][col - 1] == o) { check_beside_horizontal_point = 1; }
				}


				for (i = 1; i < 4; i++) {
					if (col + i > 19) break;
					if (pDoc->baduk[row][col + i] == o) { check_horizontal++; };
					if (pDoc->baduk[row][col + 1] == o) { check_horizontal_point = 1; }
				}


				for (i = 1; i < 4; i++) {
					if (row - i < 0) break;
					if (pDoc->baduk[row - i][col] == o) { check_beside_vertical++; }
					if (pDoc->baduk[row - 1][col] == o) { check_beside_vertical_point = 1; }
				}


				for (i = 1; i < 4; i++) {

					if (row + i > 19) break;
					if (pDoc->baduk[row + i][col] == o) { check_vertical++; }
					if (pDoc->baduk[row + 1][col] == o) { check_vertical_point = 1; }
				}

				for (i = 1; i < 4; i++) {
					if (row + i > 19 || col + i > 19) break;
					if (pDoc->baduk[row + i][col + i] == o) { check_diagonal++; }
					if (pDoc->baduk[row + 1][col + 1] == o) { check_diagonal_point = 1; }
				}

				for (i = 1; i < 4; i++) {
					if (row - i < 0 || col - i <  0) break;
					if (pDoc->baduk[row - i][col - i] == o) { check_beside_diagonal++; }
					if (pDoc->baduk[row - 1][col - 1] == o) { check_beside_diagonal_point = 1; }
				}

				for (i = 1; i < 4; i++) {
					if (row - i < 0 || col + i > 19) break;
					if (pDoc->baduk[row - i][col + i] == o) { check_reverse_diagonal++; }
					if (pDoc->baduk[row - 1][col + 1] == o) { check_reverse_diagonal_point = 1; }
				}

				for (i = 1; i < 4; i++) {
					if (row + i > 19 || col - i < 0) break;
					if (pDoc->baduk[row + i][col - i] == o) { check_reverse_beside_diagonal++; }
					if (pDoc->baduk[row + 1][col - 1] == o) { check_reverse_beside_diagonal_point = 1; }
				}
				if (check_horizontal == 3 && check_beside_horizontal_point == 1) {
					ibaduk[row][col] += o_five;
					obaduk[row][col] += o_five;
				}
				if (check_beside_horizontal == 3 && check_horizontal_point == 1) {
					ibaduk[row][col] += o_five;
					obaduk[row][col] += o_five;
				}
				if (check_vertical == 3 && check_beside_vertical_point == 1) {
					ibaduk[row][col] += o_five;
					obaduk[row][col] += o_five;
				}
				if (check_beside_vertical == 3 && check_vertical_point == 1) {
					ibaduk[row][col] += o_five;
					obaduk[row][col] += o_five;
				}
				if (check_diagonal == 3 && check_beside_diagonal_point == 1) {
					ibaduk[row][col] += o_five;
					obaduk[row][col] += o_five;
				}
				if (check_beside_diagonal == 3 && check_diagonal_point == 1) {
					ibaduk[row][col] += o_five;
					obaduk[row][col] += o_five;
				}
				if (check_reverse_diagonal == 3 && check_reverse_beside_diagonal_point == 1) {
					ibaduk[row][col] += o_five;
					obaduk[row][col] += o_five;
				}
				if (check_reverse_beside_diagonal == 3 && check_reverse_diagonal_point == 1) {
					ibaduk[row][col] += o_five;
					obaduk[row][col] += o_five;
				}
			}
			else {
				ibaduk[row][col] = 0;
				obaduk[row][col] = 0;
			}
		}
	/* ====================================================================================

	�����ҵ��� ������*�� �϶� *�� ���� ������ �������

	=====================================================================================*/



	/* ====================================================================================

	�����ҵ��� ***��* �϶� ���� ���� ������

	=====================================================================================*/
	for (row = 0; row < 19; row++)
		for (col = 0; col < 19; col++) {
			check_vertical = 0; //  ���ι��� üũ ����
			check_beside_vertical = 0; //  ���ι��� üũ ����
			check_horizontal = 0; // ���ι��� üũ ����
			check_beside_horizontal = 0; // ���ι��� üũ ����
			check_diagonal = 0;  // �Ϲݴ밢���� ���
			check_beside_diagonal = 0; // �Ϲݴ밢���� ���
			check_reverse_diagonal = 0; //�Ϲݴ밢���� �ݴ� ���
			check_reverse_beside_diagonal = 0; // �Ϲ� �밢���� �ݴ� ���

			check_vertical_point = 0; // ����Ʈ
			check_beside_vertical_point = 0;
			check_horizontal_point = 0;
			check_beside_horizontal_point = 0;
			check_diagonal_point = 0;
			check_beside_diagonal_point = 0;
			check_reverse_diagonal_point = 0;
			check_reverse_beside_diagonal_point = 0;

			if (pDoc->baduk[row][col] == 0) {
				for (i = 1; i < 4; i++) {

					if (col - i < 0) break; // ���ΰ� 0 �̸� �ݺ�Ż��
					if (pDoc->baduk[row][col - i] == d) { check_beside_horizontal++; }
					if (pDoc->baduk[row][col - 1] == d) { check_beside_horizontal_point = 1; }
				}

				for (i = 1; i < 4; i++) {
					if (col + i > 19) break;
					if (pDoc->baduk[row][col + i] == d) { check_horizontal++; };
					if (pDoc->baduk[row][col + 1] == d) { check_horizontal_point = 1; }
				}

				for (i = 1; i < 4; i++) {
					if (row - i < 0) break;
					if (pDoc->baduk[row - i][col] == d) { check_beside_vertical++; }
					if (pDoc->baduk[row - 1][col] == d) { check_beside_vertical_point = 1; }
				}

				for (i = 1; i < 4; i++) {
					if (row + i > 19) break;
					if (pDoc->baduk[row + i][col] == d) { check_vertical++; }
					if (pDoc->baduk[row + 1][col] == d) { check_vertical_point = 1; }
				}

				for (i = 1; i < 4; i++) {
					if (row + i > 19 || col + i > 19) break;
					if (pDoc->baduk[row + i][col + i] == d) { check_diagonal++; }
					if (pDoc->baduk[row + 1][col + 1] == d) { check_diagonal_point = 1; }

				}

				for (i = 1; i < 4; i++) {
					if (row - i < 0 || col - i <  0) break;
					if (pDoc->baduk[row - i][col - i] == d) { check_beside_diagonal++; }
					if (pDoc->baduk[row - 1][col - 1] == d) { check_beside_diagonal_point = 1; }
				}

				for (i = 1; i < 4; i++) {
					if (row - i < 0 || col + i > 19) break;
					if (pDoc->baduk[row - i][col + i] == d) { check_reverse_diagonal++; }
					if (pDoc->baduk[row - 1][col + 1] == d) { check_reverse_diagonal_point = 1; }
				}

				for (i = 1; i < 4; i++) {
					if (row + i > 19 || col - i < 0) break;
					if (pDoc->baduk[row + i][col - i] == d) { check_reverse_beside_diagonal++; }
					if (pDoc->baduk[row + 1][col - 1] == d) { check_reverse_beside_diagonal_point = 1; }
				}
				if (check_horizontal == 3 && check_beside_horizontal_point == 1) {
					ibaduk[row][col] += d_five;
					dbaduk[row][col] += d_five;
				}
				if (check_beside_horizontal == 3 && check_horizontal_point == 1) {
					ibaduk[row][col] += d_five;
					dbaduk[row][col] += d_five;
				}
				if (check_vertical == 3 && check_beside_vertical_point == 1) {
					ibaduk[row][col] += d_five;
					dbaduk[row][col] += d_five;
				}
				if (check_beside_vertical == 3 && check_vertical_point == 1) {
					ibaduk[row][col] += d_five;
					dbaduk[row][col] += d_five;
				}
				if (check_diagonal == 3 && check_beside_diagonal_point == 1) {
					ibaduk[row][col] += d_five;
					dbaduk[row][col] += d_five;
				}
				if (check_beside_diagonal == 3 && check_diagonal_point == 1) {
					ibaduk[row][col] += d_five;
					dbaduk[row][col] += d_five;
				}
				if (check_reverse_diagonal == 3 && check_reverse_beside_diagonal_point == 1) {
					ibaduk[row][col] += d_five;
					dbaduk[row][col] += d_five;
				}
				if (check_reverse_beside_diagonal == 3 && check_reverse_diagonal_point == 1) {
					ibaduk[row][col] += d_five;
					dbaduk[row][col] += d_five;
				}
			}
			else {
				ibaduk[row][col] = 0;
				dbaduk[row][col] = 0;
			}
		}
	/* ====================================================================================

	�����ҵ��� ***��* �϶� ���� ���� ������ �������

	=====================================================================================*/
}


void CMFCApplication3View::OffendWeight4(int o, int d) { //3���� ���� ����������
	CMFCApplication3Doc* pDoc = GetDocument();
	int i;
	int check_vertical = 0; // ���ι��� üũ ����
	int check_beside_vertical = 0; //  ���ι��� üũ ����
	int check_horizontal = 0; // ���ι��� üũ ����
	int check_beside_horizontal = 0; // ���ι��� üũ ����
	int check_diagonal = 0;  // �Ϲݴ밢���� ���
	int check_beside_diagonal = 0; // �Ϲݴ밢���� ���
	int check_reverse_diagonal = 0; //�Ϲݴ밢���� �ݴ� ���
	int check_reverse_beside_diagonal = 0; // �Ϲ� �밢���� �ݴ� ���
	int row, col;

	int defend_four_point[8]; //4����ĭ�� �������� ���� 

	int defend_one_point[8];  //1���� ĭ�� �������� ����

	int defend_five_point[8]; // 5��° ĭ�� �������� ����
							  /* �迭�����Ͽ�
							  0 : beside_horizontal
							  1 : horizontal
							  2 : beside_vertical
							  3 : vertical
							  4 : diagonal
							  5 : beside_diagonal
							  6 : reverse_diagonal
							  7 : reverse_beside_diagonal
							  */
							  /* ====================================================================================

							  �����ҵ��� *������* �϶� *�� ����ġ

							  =====================================================================================*/
	for (row = 0; row < 19; row++)
		for (col = 0; col < 19; col++) {
			check_vertical = 0; //  ���ι��� üũ ����
			check_beside_vertical = 0; //  ���ι��� üũ ����
			check_horizontal = 0; // ���ι��� üũ ����
			check_beside_horizontal = 0; // ���ι��� üũ ����
			check_diagonal = 0;  // �Ϲݴ밢���� ���
			check_beside_diagonal = 0; // �Ϲݴ밢���� ���
			check_reverse_diagonal = 0; //�Ϲݴ밢���� �ݴ� ���
			check_reverse_beside_diagonal = 0; // �Ϲ� �밢���� �ݴ� ���

			for (i = 0; i < 9; i++) {
				defend_four_point[i] = 0;
			}

			for (i = 0; i < 9; i++) {
				defend_one_point[i] = 0;
			}

			for (i = 0; i < 9; i++) {
				defend_five_point[i] = 0;
			}
			if (pDoc->baduk[row][col] == 0) {
				for (i = 1; i < 4; i++) {
					if (col - i < 0) break; // ���ΰ� 0 �̸� �ݺ�Ż��
					if (pDoc->baduk[row][col - i] == o) { check_beside_horizontal++; }
				}

				for (i = 1; i < 4; i++) {
					if (col + i > 19) break;
					if (pDoc->baduk[row][col + i] == o) { check_horizontal++; }
				}

				for (i = 1; i < 4; i++) {
					if (row - i < 0) break;
					if (pDoc->baduk[row - i][col] == o) { check_beside_vertical++; }
				}

				for (i = 1; i < 4; i++) {
					if (row + i > 19) break;
					if (pDoc->baduk[row + i][col] == o) { check_vertical++; }
				}

				for (i = 1; i < 4; i++) {
					if (row + i > 19 || col + i > 19) break;
					if (pDoc->baduk[row + i][col + i] == o) { check_diagonal++; }
				}

				for (i = 1; i < 4; i++) {
					if (row - i < 0 || col - i <  0) break;
					if (pDoc->baduk[row - i][col - i] == o) { check_beside_diagonal++; }
				}

				for (i = 1; i < 4; i++) {
					if (row - i < 0 || col + i > 19) break;
					if (pDoc->baduk[row - i][col + i] == o) { check_reverse_diagonal++; }
				}

				for (i = 1; i < 4; i++) {
					if (row + i > 19 || col - i < 0) break;
					if (pDoc->baduk[row + i][col - i] == o) { check_reverse_beside_diagonal++; }
				}

				if (pDoc->baduk[row][col - 4] == d) { defend_four_point[0] = 1; }          //beside_horziontal
				if (pDoc->baduk[row][col + 4] == d) { defend_four_point[1] = 1; }          //horizontal
				if (pDoc->baduk[row - 4][col] == d) { defend_four_point[2] = 1; }          //beside_vertical
				if (pDoc->baduk[row + 4][col] == d) { defend_four_point[3] = 1; }          //vertical
				if (pDoc->baduk[row + 4][col + 4] == d) { defend_four_point[4] = 1; }      //diagonal
				if (pDoc->baduk[row - 4][col - 4] == d) { defend_four_point[5] = 1; }      //beside_diagonal
				if (pDoc->baduk[row - 4][col + 4] == d) { defend_four_point[6] = 1; }      //reverse_diagonazl
				if (pDoc->baduk[row + 4][col - 4] == d) { defend_four_point[7] = 1; }      //reverse_besisde_diagonal

				if (pDoc->baduk[row][col - 5] == d) { defend_five_point[0] = 1; }
				if (pDoc->baduk[row][col + 5] == d) { defend_five_point[1] = 1; }
				if (pDoc->baduk[row - 5][col] == d) { defend_five_point[2] = 1; }
				if (pDoc->baduk[row + 5][col] == d) { defend_five_point[3] = 1; }
				if (pDoc->baduk[row + 5][col + 5] == d) { defend_five_point[4] = 1; }
				if (pDoc->baduk[row - 5][col - 5] == d) { defend_five_point[5] = 1; }
				if (pDoc->baduk[row - 5][col + 5] == d) { defend_five_point[6] = 1; }
				if (pDoc->baduk[row + 5][col - 5] == d) { defend_five_point[7] = 1; }

				if (pDoc->baduk[row][col - 1] == d) { defend_one_point[0] = 1; }         //beside_horziontal
				if (pDoc->baduk[row][col + 1] == d) { defend_one_point[1] = 1; }          //horizontal
				if (pDoc->baduk[row - 1][col] == d) { defend_one_point[2] = 1; }          //beside_vertical
				if (pDoc->baduk[row + 1][col] == d) { defend_one_point[3] = 1; }          //vertical
				if (pDoc->baduk[row + 1][col + 1] == d) { defend_one_point[4] = 1; }     //diagonal
				if (pDoc->baduk[row - 1][col - 1] == d) { defend_one_point[5] = 1; }      //beside_diagonal
				if (pDoc->baduk[row - 1][col + 1] == d) { defend_one_point[6] = 1; }      //reverse_diagonazl
				if (pDoc->baduk[row + 1][col - 1] == d) { defend_one_point[7] = 1; }      //reverse_besisde_diagonal

				if (check_horizontal == 3) {
					if (defend_four_point[1] == 1 && defend_one_point[0] == 1);
					else if ((defend_four_point[1] == 0 || defend_five_point[1] == 0) && defend_one_point[0] == 1);              // ��***����  �϶� ���� ��������
					else {
						ibaduk[row][col] += o_four;
						obaduk[row][col] += o_four;
					}
				}
				if (check_beside_horizontal == 3) {
					if (defend_four_point[0] == 1 && defend_one_point[1] == 1);
					else if ((defend_four_point[0] == 0 || defend_five_point[0] == 0) && defend_one_point[1] == 1);
					else {
						ibaduk[row][col] += o_four;
						obaduk[row][col] += o_four;
					}
				}
				if (check_vertical == 3) {
					if (defend_four_point[3] == 1 && defend_one_point[2] == 1);
					else if ((defend_four_point[3] == 0 || defend_five_point[3] == 0) && defend_one_point[2] == 1);
					else {
						ibaduk[row][col] += o_four;
						obaduk[row][col] += o_four;
					}
				}
				if (check_beside_vertical == 3) {
					if (defend_four_point[2] == 1 && defend_one_point[3] == 1);
					else if ((defend_four_point[2] == 0 || defend_five_point[2] == 0) && defend_one_point[3] == 1);
					else {
						ibaduk[row][col] += o_four;
						obaduk[row][col] += o_four;
					}
				}
				if (check_diagonal == 3) {
					if (defend_four_point[4] == 1 && defend_one_point[5] == 1);
					else if ((defend_four_point[4] == 0 || defend_five_point[4] == 0) && defend_one_point[5] == 1);
					else {
						ibaduk[row][col] += o_four;
						obaduk[row][col] += o_four;
					}
				}
				if (check_beside_diagonal == 3) {
					if (defend_four_point[5] == 1 && defend_one_point[4] == 1);
					else if ((defend_four_point[5] == 0 || defend_five_point[5] == 0) && defend_one_point[4] == 1);
					else {
						ibaduk[row][col] += o_four;
						obaduk[row][col] += o_four;
					}
				}
				if (check_reverse_diagonal == 3) {
					if (defend_four_point[6] == 1 && defend_one_point[7] == 1);
					else if ((defend_four_point[6] == 0 || defend_five_point[6] == 0) && defend_one_point[7] == 1);
					else {
						ibaduk[row][col] += o_four;
						obaduk[row][col] += o_four;
					}
				}
				if (check_reverse_beside_diagonal == 3) {
					if (defend_four_point[7] == 1 && defend_one_point[6] == 1);
					else if ((defend_four_point[7] == 0 || defend_five_point[7] == 0) && defend_one_point[6] == 1);
					else {
						ibaduk[row][col] += o_four;
						obaduk[row][col] += o_four;
					}
				}
			}
			else {
				ibaduk[row][col] = 0;
				obaduk[row][col] = 0;
			}
		}

	/* ====================================================================================

	�����ҵ��� *������* �϶� *�� ����ġ �������

	=====================================================================================*/

	/* ====================================================================================

	�����ҵ��� ��***�� �϶� ���� ����ġ

	=====================================================================================*/
	for (row = 0; row < 19; row++)
		for (col = 0; col < 19; col++) {
			check_vertical = 0; //  ���ι��� üũ ����
			check_beside_vertical = 0; //  ���ι��� üũ ����
			check_horizontal = 0; // ���ι��� üũ ����
			check_beside_horizontal = 0; // ���ι��� üũ ����
			check_diagonal = 0;  // �Ϲݴ밢���� ���
			check_beside_diagonal = 0; // �Ϲݴ밢���� ���
			check_reverse_diagonal = 0; //�Ϲݴ밢���� �ݴ� ���
			check_reverse_beside_diagonal = 0; // �Ϲ� �밢���� �ݴ� ���

			if (pDoc->baduk[row][col] == 0) {
				for (i = 1; i < 4; i++) {
					if (col - i < 0) break;
					if (pDoc->baduk[row][col - i] == d) { check_beside_horizontal++; }

				}

				for (i = 1; i < 4; i++) {
					if (col + i > 19) break;
					if (pDoc->baduk[row][col + i] == d) { check_horizontal++; }

				}

				for (i = 1; i < 4; i++) {

					if (row - i < 0) break;
					if (pDoc->baduk[row - i][col] == d) { check_beside_vertical++; }

				}

				for (i = 1; i < 4; i++) {
					if (row + i > 19) break;
					if (pDoc->baduk[row + i][col] == d) { check_vertical++; }

				}

				for (i = 1; i < 4; i++) {
					if (row + i > 19 || col + i > 19) break;
					if (pDoc->baduk[row + i][col + i] == d) { check_diagonal++; }


				}

				for (i = 1; i < 4; i++) {
					if (row - i < 0 || col - i <  0) break;
					if (pDoc->baduk[row - i][col - i] == d) { check_beside_diagonal++; }

				}

				for (i = 1; i < 4; i++) {

					if (row - i < 0 || col + i > 19) break;
					if (pDoc->baduk[row - i][col + i] == d) { check_reverse_diagonal++; }

				}

				for (i = 1; i < 4; i++) {
					if (row + i > 19 || col - i < 0) break;
					if (pDoc->baduk[row + i][col - i] == d) { check_reverse_beside_diagonal++; }


				}

				if (check_horizontal == 3)
				{
					if ((pDoc->baduk[row][col + 4] == o | pDoc->baduk[row][col - 1] == o) == false) {
						ibaduk[row][col] += d_four;
						dbaduk[row][col] += d_four;
					}
				}
				if (check_beside_horizontal == 3)
				{
					if ((pDoc->baduk[row][col - 4] == o | pDoc->baduk[row][col + 1] == o) == false) {
						ibaduk[row][col] += d_four;
						dbaduk[row][col] += d_four;
					}
				}
				if (check_vertical == 3)
				{
					if ((pDoc->baduk[row + 4][col] == o | pDoc->baduk[row - 1][col] == o) == false) {
						ibaduk[row][col] += d_four;
						dbaduk[row][col] += d_four;
					}
				}
				if (check_beside_vertical == 3)
				{
					if ((pDoc->baduk[row - 4][col] == o | pDoc->baduk[row + 1][col] == o) == false) {
						ibaduk[row][col] += d_four;
						dbaduk[row][col] += d_four;
					}
				}
				if (check_diagonal == 3)
				{
					if ((pDoc->baduk[row + 4][col + 4] == o | pDoc->baduk[row - 1][col - 1] == o) == false) {
						ibaduk[row][col] += d_four;
						dbaduk[row][col] += d_four;
					}
				}
				if (check_beside_diagonal == 3)
				{
					if ((pDoc->baduk[row - 4][col - 4] == o | pDoc->baduk[row + 1][col + 1] == o) == false) {
						ibaduk[row][col] += d_four;
						dbaduk[row][col] += d_four;
					}
				}
				if (check_reverse_diagonal == 3)
				{
					if ((pDoc->baduk[row - 4][col + 4] == o | pDoc->baduk[row + 1][col - 1] == o) == false) {
						ibaduk[row][col] += d_four;
						dbaduk[row][col] += d_four;
					}
				}
				if (check_reverse_beside_diagonal == 3)
				{
					if ((pDoc->baduk[row + 4][col - 4] == o | pDoc->baduk[row - 1][col + 1] == o) == false) {
						ibaduk[row][col] += d_four;
						dbaduk[row][col] += d_four;
					}
				}

			}
			else {
				ibaduk[row][col] = 0;
				dbaduk[row][col] = 0;
			}
		}
	/* ====================================================================================

	�����ҵ��� ��***�� �϶� ���� ����ġ �������

	=====================================================================================*/
}

void CMFCApplication3View::OffendWeight4_2(int o, int d) { // 2�� 1�� ������ ������
	CMFCApplication3Doc* pDoc = GetDocument();
	int i;
	int check_vertical = 0; // ���ι��� üũ ����
	int check_beside_vertical = 0; //  ���ι��� üũ ����
	int check_horizontal = 0; // ���ι��� üũ ����
	int check_beside_horizontal = 0; // ���ι��� üũ ����
	int check_diagonal = 0;  // �Ϲݴ밢���� ���
	int check_beside_diagonal = 0; // �Ϲݴ밢���� ���
	int check_reverse_diagonal = 0; //�Ϲݴ밢���� �ݴ� ���
	int check_reverse_beside_diagonal = 0; // �Ϲ� �밢���� �ݴ� ���

	int check_vertical_point = 0; // ����Ʈ
	int check_beside_vertical_point = 0;
	int check_horizontal_point = 0;
	int check_beside_horizontal_point = 0;
	int check_diagonal_point = 0;
	int check_beside_diagonal_point = 0;
	int check_reverse_diagonal_point = 0;
	int check_reverse_beside_diagonal_point = 0;

	int check_vertical_opposite_point3 = 0; // �ݴ��� ����Ʈ
	int check_beside_vertical_opposite_point3 = 0;
	int check_horizontal_opposite_point3 = 0;
	int check_beside_horizontal_opposite_point3 = 0;
	int check_diagonal_opposite_point3 = 0;
	int check_beside_diagonal_opposite_point3 = 0;
	int check_reverse_diagonal_opposite_point3 = 0;
	int check_reverse_beside_diagonal_opposite_point3 = 0;

	int check_vertical_opposite_point2 = 0; // �ݴ��� ����Ʈ2
	int check_beside_vertical_opposite_point2 = 0;
	int check_horizontal_opposite_point2 = 0;
	int check_beside_horizontal_opposite_point2 = 0;
	int check_diagonal_opposite_point2 = 0;
	int check_beside_diagonal_opposite_point2 = 0;
	int check_reverse_diagonal_opposite_point2 = 0;
	int check_reverse_beside_diagonal_opposite_point2 = 0;

	int row, col;

	/* ====================================================================================

	�����ҵ��� **��* �϶� ���� ����ġ

	=====================================================================================*/
	for (row = 0; row < 19; row++)
		for (col = 0; col < 19; col++) {
			check_vertical = 0; //  ���ι��� üũ ����
			check_beside_vertical = 0; //  ���ι��� üũ ����
			check_horizontal = 0; // ���ι��� üũ ����
			check_beside_horizontal = 0; // ���ι��� üũ ����
			check_diagonal = 0;  // �Ϲݴ밢���� ���
			check_beside_diagonal = 0; // �Ϲݴ밢���� ���
			check_reverse_diagonal = 0; //�Ϲݴ밢���� �ݴ� ���
			check_reverse_beside_diagonal = 0; // �Ϲ� �밢���� �ݴ� ���

			check_vertical_point = 0; // 3��°�� ��뵹�� �ִ°��
			check_beside_vertical_point = 0;
			check_horizontal_point = 0;
			check_beside_horizontal_point = 0;
			check_diagonal_point = 0;
			check_beside_diagonal_point = 0;
			check_reverse_diagonal_point = 0;
			check_reverse_beside_diagonal_point = 0;

			check_vertical_opposite_point2 = 0; // 2��°�� ��뵹�� �ִ°��
			check_beside_vertical_opposite_point2 = 0;
			check_horizontal_opposite_point2 = 0;
			check_beside_horizontal_opposite_point2 = 0;
			check_diagonal_opposite_point2 = 0;
			check_beside_diagonal_opposite_point2 = 0;
			check_reverse_diagonal_opposite_point2 = 0;
			check_reverse_beside_diagonal_opposite_point2 = 0;

			check_vertical_opposite_point3 = 0; // 3��°�� ��뵹�� �ִ°��
			check_beside_vertical_opposite_point3 = 0;
			check_horizontal_opposite_point3 = 0;
			check_beside_horizontal_opposite_point3 = 0;
			check_diagonal_opposite_point3 = 0;
			check_beside_diagonal_opposite_point3 = 0;
			check_reverse_diagonal_opposite_point3 = 0;
			check_reverse_beside_diagonal_opposite_point3 = 0;

			if (pDoc->baduk[row][col] == 0) {
				for (i = 1; i < 3; i++) {
					if (col - i < 0) break;  // ���ΰ� 0 �̸� �ݺ�Ż��
					if (pDoc->baduk[row][col - i] == o) { check_beside_horizontal++; }
					if (pDoc->baduk[row][col - 1] == o) { check_beside_horizontal_point = 1; }
					if (pDoc->baduk[row][col - 2] == d) { check_beside_horizontal_opposite_point2 = 1; }
					if (pDoc->baduk[row][col - 3] == d) { check_beside_horizontal_opposite_point3 = 1; }

				}


				for (i = 1; i < 3; i++) {
					if (col + i > 19) break;
					if (pDoc->baduk[row][col + i] == o) { check_horizontal++; };
					if (pDoc->baduk[row][col + 1] == o) { check_horizontal_point = 1; }
					if (pDoc->baduk[row][col + 1] == o) { check_horizontal_point = 1; }
					if (pDoc->baduk[row][col + 2] == d) { check_horizontal_opposite_point2 = 1; }
					if (pDoc->baduk[row][col + 3] == d) { check_horizontal_opposite_point3 = 1; }
				}


				for (i = 1; i < 3; i++) {
					if (row - i < 0) break;
					if (pDoc->baduk[row - i][col] == o) { check_beside_vertical++; }
					if (pDoc->baduk[row - 1][col] == o) { check_beside_vertical_point = 1; }
					if (pDoc->baduk[row - 2][col] == d) { check_beside_vertical_opposite_point2 = 1; }
					if (pDoc->baduk[row - 3][col] == d) { check_beside_vertical_opposite_point3 = 1; }
				}


				for (i = 1; i < 3; i++) {
					if (row + i > 19) break;
					if (pDoc->baduk[row + i][col] == o) { check_vertical++; }
					if (pDoc->baduk[row + 1][col] == o) { check_vertical_point = 1; }
					if (pDoc->baduk[row + 3][col] == d) { check_vertical_opposite_point2 = 1; }
					if (pDoc->baduk[row + 3][col] == d) { check_vertical_opposite_point3 = 1; }
				}

				for (i = 1; i < 3; i++) {
					if (row + i > 19 || col + i > 19) break;
					if (pDoc->baduk[row + i][col + i] == o) { check_diagonal++; }
					if (pDoc->baduk[row + 1][col + 1] == o) { check_diagonal_point = 1; }
					if (pDoc->baduk[row + 2][col + 2] == d) { check_diagonal_opposite_point2 = 1; }
					if (pDoc->baduk[row + 3][col + 3] == d) { check_diagonal_opposite_point3 = 1; }
				}

				for (i = 1; i < 3; i++) {
					if (row - i < 0 || col - i < 0) break;
					if (pDoc->baduk[row - i][col - i] == o) { check_beside_diagonal++; }
					if (pDoc->baduk[row - 1][col - 1] == o) { check_beside_diagonal_point = 1; }
					if (pDoc->baduk[row - 2][col - 2] == d) { check_beside_diagonal_opposite_point2 = 1; }
					if (pDoc->baduk[row - 3][col - 3] == d) { check_beside_diagonal_opposite_point3 = 1; }
				}

				for (i = 1; i < 3; i++) {
					if (row - i < 0 || col - i > 19) break;
					if (pDoc->baduk[row - i][col + i] == o) { check_reverse_diagonal++; }
					if (pDoc->baduk[row - 1][col + 1] == o) { check_reverse_diagonal_point = 1; }
					if (pDoc->baduk[row - 2][col + 2] == d) { check_reverse_diagonal_opposite_point2 = 1; }
					if (pDoc->baduk[row - 3][col + 3] == d) { check_reverse_diagonal_opposite_point3 = 1; }
				}

				for (i = 1; i < 3; i++) {
					if (row + i> 19 || col - i < 0) break;
					if (pDoc->baduk[row + i][col - i] == o) { check_reverse_beside_diagonal++; }
					if (pDoc->baduk[row + 1][col - 1] == o) { check_reverse_beside_diagonal_point = 1; }
					if (pDoc->baduk[row + 2][col - 2] == d) { check_reverse_beside_diagonal_opposite_point2 = 1; }
					if (pDoc->baduk[row + 3][col - 3] == d) { check_reverse_beside_diagonal_opposite_point3 = 1; }
				}

				if (check_horizontal == 2 && check_beside_horizontal_point == 1 &&
					check_horizontal_opposite_point3 == 0 && check_beside_horizontal_opposite_point2 == 0) {
					ibaduk[row][col] += o_four;
					obaduk[row][col] += o_four;
				}
				if (check_beside_horizontal == 2 && check_horizontal_point == 1 &&
					check_beside_horizontal_opposite_point3 == 0 && check_horizontal_opposite_point2 == 0) {
					ibaduk[row][col] += o_four;
					obaduk[row][col] += o_four;
				}
				if (check_vertical == 2 && check_beside_vertical_point == 1 &&
					check_vertical_opposite_point3 == 0 && check_beside_vertical_opposite_point2 == 0) {
					ibaduk[row][col] += o_four;
					obaduk[row][col] += o_four;
				}
				if (check_beside_vertical == 2 && check_vertical_point == 1 &&
					check_beside_vertical_opposite_point3 == 0 && check_vertical_opposite_point2 == 0) {
					ibaduk[row][col] += o_four;
					obaduk[row][col] += o_four;
				}
				if (check_diagonal == 2 && check_beside_diagonal_point == 1 &&
					check_diagonal_opposite_point3 == 0 && check_beside_diagonal_opposite_point2 == 0) {
					ibaduk[row][col] += o_four;
					obaduk[row][col] += o_four;
				}
				if (check_beside_diagonal == 2 && check_diagonal_point == 1 &&
					check_beside_diagonal_opposite_point3 == 0 && check_diagonal_opposite_point2 == 0) {
					ibaduk[row][col] += o_four;
					obaduk[row][col] += o_four;
				}
				if (check_reverse_diagonal == 2 && check_reverse_beside_diagonal_point == 1 &&
					check_reverse_diagonal_opposite_point3 == 0 && check_reverse_beside_diagonal_opposite_point2 == 0) {
					ibaduk[row][col] += o_four;
					obaduk[row][col] += o_four;
				}
				if (check_reverse_beside_diagonal == 2 && check_reverse_diagonal_point == 1 &&
					check_reverse_beside_diagonal_opposite_point3 == 0 && check_reverse_diagonal_opposite_point2 == 0) {
					ibaduk[row][col] += o_four;
					obaduk[row][col] += o_four;
				}

			}
			else {
				ibaduk[row][col] = 0;
				obaduk[row][col] = 0;
			}
		}

	for (row = 0; row < 19; row++)
		for (col = 0; col < 19; col++) {
			check_vertical = 0; //  ���ι��� üũ ����
			check_beside_vertical = 0; //  ���ι��� üũ ����
			check_horizontal = 0; // ���ι��� üũ ����
			check_beside_horizontal = 0; // ���ι��� üũ ����
			check_diagonal = 0;  // �Ϲݴ밢���� ���
			check_beside_diagonal = 0; // �Ϲݴ밢���� ���
			check_reverse_diagonal = 0; //�Ϲݴ밢���� �ݴ� ���
			check_reverse_beside_diagonal = 0; // �Ϲ� �밢���� �ݴ� ���

			check_vertical_point = 0; // ����Ʈ
			check_beside_vertical_point = 0;
			check_horizontal_point = 0;
			check_beside_horizontal_point = 0;
			check_diagonal_point = 0;
			check_beside_diagonal_point = 0;
			check_reverse_diagonal_point = 0;
			check_reverse_beside_diagonal_point = 0;

			check_vertical_opposite_point2 = 0; // 2��°�� ��뵹�� �ִ°��
			check_beside_vertical_opposite_point2 = 0;
			check_horizontal_opposite_point2 = 0;
			check_beside_horizontal_opposite_point2 = 0;
			check_diagonal_opposite_point2 = 0;
			check_beside_diagonal_opposite_point2 = 0;
			check_reverse_diagonal_opposite_point2 = 0;
			check_reverse_beside_diagonal_opposite_point2 = 0;

			check_vertical_opposite_point3 = 0; // 3��°�� ��뵹�� �ִ°��
			check_beside_vertical_opposite_point3 = 0;
			check_horizontal_opposite_point3 = 0;
			check_beside_horizontal_opposite_point3 = 0;
			check_diagonal_opposite_point3 = 0;
			check_beside_diagonal_opposite_point3 = 0;
			check_reverse_diagonal_opposite_point3 = 0;
			check_reverse_beside_diagonal_opposite_point3 = 0;

			if (pDoc->baduk[row][col] == 0) {
				for (i = 1; i < 3; i++) {
					if (col - i < 0) break;  // ���ΰ� 0 �̸� �ݺ�Ż��
					if (pDoc->baduk[row][col - i] == d) { check_beside_horizontal++; }
					if (pDoc->baduk[row][col - 1] == d) { check_beside_horizontal_point = 1; }
					if (pDoc->baduk[row][col - 2] == o) { check_beside_horizontal_opposite_point2 = 1; }
					if (pDoc->baduk[row][col - 3] == o) { check_beside_horizontal_opposite_point3 = 1; }
				}

				for (i = 1; i < 3; i++) {
					if (col + i > 19) break;
					if (pDoc->baduk[row][col + i] == d) { check_horizontal++; };
					if (pDoc->baduk[row][col + 1] == d) { check_horizontal_point = 1; }
					if (pDoc->baduk[row][col + 2] == o) { check_horizontal_opposite_point2 = 1; }
					if (pDoc->baduk[row][col + 3] == o) { check_horizontal_opposite_point3 = 1; }
				}

				for (i = 1; i < 3; i++) {
					if (row - i< 0) break;
					if (pDoc->baduk[row - i][col] == d) { check_beside_vertical++; }
					if (pDoc->baduk[row - 1][col] == d) { check_beside_vertical_point = 1; }
					if (pDoc->baduk[row - 2][col] == o) { check_beside_vertical_opposite_point2 = 1; }
					if (pDoc->baduk[row - 3][col] == o) { check_beside_vertical_opposite_point3 = 1; }
				}

				for (i = 1; i < 3; i++) {
					if (row + i> 19) break;
					if (pDoc->baduk[row + i][col] == d) { check_vertical++; }
					if (pDoc->baduk[row + 1][col] == d) { check_vertical_point = 1; }
					if (pDoc->baduk[row + 2][col] == o) { check_vertical_opposite_point2 = 1; }
					if (pDoc->baduk[row + 3][col] == o) { check_vertical_opposite_point3 = 1; }
				}

				for (i = 1; i < 3; i++) {
					if (row + i> 19 || col + i > 19) break;
					if (pDoc->baduk[row + i][col + i] == d) { check_diagonal++; }
					if (pDoc->baduk[row + 1][col + 1] == d) { check_diagonal_point = 1; }
					if (pDoc->baduk[row + 2][col + 2] == o) { check_diagonal_opposite_point2 = 1; }
					if (pDoc->baduk[row + 3][col + 3] == o) { check_diagonal_opposite_point3 = 1; }

				}

				for (i = 1; i < 3; i++) {
					if (row - i< 0 || col - i < 0) break;
					if (pDoc->baduk[row - i][col - i] == d) { check_beside_diagonal++; }
					if (pDoc->baduk[row - 1][col - 1] == d) { check_beside_diagonal_point = 1; }
					if (pDoc->baduk[row - 2][col - 2] == o) { check_beside_diagonal_opposite_point2 = 1; }
					if (pDoc->baduk[row - 3][col - 3] == o) { check_beside_diagonal_opposite_point3 = 1; }
				}

				for (i = 1; i < 3; i++) {
					if (row - i < 0 || col + i > 19) break;
					if (pDoc->baduk[row - i][col + i] == d) { check_reverse_diagonal++; }
					if (pDoc->baduk[row - 1][col + 1] == d) { check_reverse_diagonal_point = 1; }
					if (pDoc->baduk[row - 2][col + 2] == o) { check_reverse_diagonal_opposite_point2 = 1; }
					if (pDoc->baduk[row - 3][col + 3] == o) { check_reverse_diagonal_opposite_point3 = 1; }
				}

				for (i = 1; i < 3; i++) {
					if (row + i > 19 || col - i < 0) break;
					if (pDoc->baduk[row + i][col - i] == d) { check_reverse_beside_diagonal++; }
					if (pDoc->baduk[row + 1][col - 1] == d) { check_reverse_beside_diagonal_point = 1; }
					if (pDoc->baduk[row + 2][col - 2] == o) { check_reverse_beside_diagonal_opposite_point2 = 1; }
					if (pDoc->baduk[row + 3][col - 3] == o) { check_reverse_beside_diagonal_opposite_point3 = 1; }

				}
				if (check_horizontal == 2 && check_beside_horizontal_point == 1 &&
					check_horizontal_opposite_point3 == 0 && check_beside_horizontal_opposite_point2 == 0)
				{
					ibaduk[row][col] += d_four;
					dbaduk[row][col] += d_four;
				}
				if (check_beside_horizontal == 2 && check_horizontal_point == 1 &&
					check_beside_horizontal_opposite_point3 == 0 && check_horizontal_opposite_point2 == 0) {
					ibaduk[row][col] += d_four;
					dbaduk[row][col] += d_four;
				}
				if (check_vertical == 2 && check_beside_vertical_point == 1 &&
					check_vertical_opposite_point3 == 0 && check_beside_vertical_opposite_point2 == 0) {
					ibaduk[row][col] += d_four;
					dbaduk[row][col] += d_four;
				}
				if (check_beside_vertical == 2 && check_vertical_point == 1 &&
					check_beside_vertical_opposite_point3 == 0 && check_vertical_opposite_point2 == 0) {
					ibaduk[row][col] += d_four;
					dbaduk[row][col] += d_four;
				}
				if (check_diagonal == 2 && check_beside_diagonal_point == 1 &&
					check_diagonal_opposite_point3 == 0 && check_beside_diagonal_opposite_point2 == 0) {
					ibaduk[row][col] += d_four;
					dbaduk[row][col] += d_four;
				}
				if (check_beside_diagonal == 2 && check_diagonal_point == 1 &&
					check_beside_diagonal_opposite_point3 == 0 && check_diagonal_opposite_point2 == 0) {
					ibaduk[row][col] += d_four;
					dbaduk[row][col] += d_four;
				}
				if (check_reverse_diagonal == 2 && check_reverse_beside_diagonal_point == 1 &&
					check_reverse_diagonal_opposite_point3 == 0 && check_reverse_beside_diagonal_opposite_point2 == 0) {
					ibaduk[row][col] += d_four;
					dbaduk[row][col] += d_four;
				}
				if (check_reverse_beside_diagonal == 2 && check_reverse_diagonal_point == 1 &&
					check_reverse_beside_diagonal_opposite_point3 == 0 && check_reverse_diagonal_opposite_point2 == 0) {
					ibaduk[row][col] += d_four;
					dbaduk[row][col] += d_four;
				}
			}
			else {
				ibaduk[row][col] = 0;
				dbaduk[row][col] = 0;
			}
		}
	/* ====================================================================================

	�����ҵ��� **��* �϶� ���� ����ġ �������

	=====================================================================================*/
}






void CMFCApplication3View::OffendWeight(int o, int d) { // �⺻���� ����ġ�� �д�. ���� ���ӵɰ�� �� ū ����ġ�� �д�.
	CMFCApplication3Doc* pDoc = GetDocument();
	int i;
	int check_vertical = 0; // ���ι��� üũ ����
	int check_beside_vertical = 0; // ���ι��� üũ ����
	int check_horizontal= 0; //���ι��� üũ ����
	int check_beside_horizontal = 0; // ���ι��� üũ ����
	int check_diagonal = 0;  // �Ϲݴ밢���� ���
	int check_beside_diagonal = 0; // �Ϲݴ밢���� ���
	int check_reverse_diagonal = 0; //�Ϲݴ밢���� �ݴ� ���
	int check_reverse_beside_diagonal = 0; // �Ϲ� �밢���� �ݴ� ���
	int row, col;

	for (row = 0; row < 19; row++)
		for (col = 0; col < 19; col++) {
			check_vertical = 0; // 3x3 ���ι��� üũ ����
			check_beside_vertical = 0; // 3x3 ���ι��� üũ ����
			check_horizontal = 0; //3x3 ���ι��� üũ ����
			check_beside_horizontal = 0; //3x3 ���ι��� üũ ����
			check_diagonal = 0;  // �Ϲݴ밢���� ���
			check_beside_diagonal = 0; // �Ϲݴ밢���� ���
			check_reverse_diagonal = 0; //�Ϲݴ밢���� �ݴ� ���
			check_reverse_beside_diagonal = 0; // �Ϲ� �밢���� �ݴ� ���

			if (pDoc->baduk[row][col] == 0) {
				for (i = 1; i < 5; i++) {
					if (col - i < 0) break; // ���ΰ� 0 �̸� �ݺ�Ż��
					if (pDoc->baduk[row][col - i] == o && pDoc->baduk[row][col - i - 1] == 0) { check_beside_horizontal++; }
					else if (pDoc->baduk[row][col - i] == o && pDoc->baduk[row][col - i - 1] == o) { check_beside_horizontal++; }

				}

				for (i = 1; i < 5; i++) {
					if (col + i > 19) break;
					if (pDoc->baduk[row][col + i] == o && pDoc->baduk[row][col + i + 1] == 0) { check_horizontal++; }
					else if (pDoc->baduk[row][col + i] == o && pDoc->baduk[row][col + i + 1] == o) { check_horizontal++; }

				}

				for (i = 1; i < 5; i++) {
					if (row - i < 0) break;
					if (pDoc->baduk[row - i][col] == o && pDoc->baduk[row - i - 1][col] == 0) { check_beside_vertical++; }
					else if (pDoc->baduk[row - i][col] == o && pDoc->baduk[row - i - 1][col] == o) { check_beside_vertical++; }

				}

				for (i = 1; i < 5; i++) {
					if (row + i > 19) break;
					if (pDoc->baduk[row + i][col] == o && pDoc->baduk[row + i + 1][col] == 0) { check_vertical++; }
					else if (pDoc->baduk[row + i][col] == o && pDoc->baduk[row + i + 1][col] == o) { check_vertical++; }

				}

				for (i = 1; i < 5; i++) {
					if (row + i > 19 || col + i > 19) break;
					if (pDoc->baduk[row + i][col + i] == o && pDoc->baduk[row + i + 1][col + i + 1] == 0) { check_diagonal++; }
					else if (pDoc->baduk[row + i][col + i] == o && pDoc->baduk[row + i + 1][col + i] == o) { check_diagonal++; }

				}

				for (i = 1; i < 5; i++) {
					if (row - i < 0 || col - i <  0) break;
					if (pDoc->baduk[row - i][col - i] == o && pDoc->baduk[row - i - 1][col - i - 1] == 0) { check_beside_diagonal++; }
					else if (pDoc->baduk[row - i][col - i - 1] == o && pDoc->baduk[row - i - 1][col - i - 1] == o) { check_beside_diagonal++; }

				}

				for (i = 1; i < 5; i++) {
					if (row - i < 0 || col + i > 19) break;
					if (pDoc->baduk[row - i][col + i] == o && pDoc->baduk[row - i - 1][col + i + 1] == 0) { check_reverse_diagonal++; }
					else if (pDoc->baduk[row - i][col + i] == o && pDoc->baduk[row - i - 1][col + i + 1] == o) { check_reverse_diagonal++; }

				}

				for (i = 1; i < 5; i++) {
					if (row + i > 19 || col - i < 0) break;
					if (pDoc->baduk[row + i][col - i] == o && pDoc->baduk[row + i - 1][col + i - 1] == 0) { check_reverse_beside_diagonal++; }
					else if (pDoc->baduk[row + i][col - i] == o && pDoc->baduk[row + i - 1][col + i - 1] == o) { check_reverse_beside_diagonal++; }


				}




				ibaduk[row][col] += (check_vertical + check_beside_vertical + check_horizontal + check_beside_horizontal + check_diagonal + check_beside_diagonal + check_reverse_diagonal + check_reverse_beside_diagonal);
			}
			else ibaduk[row][col] = 0;
		}
}


void CMFCApplication3View::defendWeight(int o, int d) { // ��븦 ����� �⺻���� ����ġ�� �д�.
	CMFCApplication3Doc* pDoc = GetDocument();
	int i;
	int check_vertical = 0; // ���ι��� üũ ����
	int check_beside_vertical = 0; // ���ι��� üũ ����
	int check_horizontal = 0; //���ι��� üũ ����
	int check_beside_horizontal = 0; // ���ι��� üũ ����
	int check_diagonal = 0;  // �Ϲݴ밢���� ���
	int check_beside_diagonal = 0; // �Ϲݴ밢���� ���
	int check_reverse_diagonal = 0; //�Ϲݴ밢���� �ݴ� ���
	int check_reverse_beside_diagonal = 0; // �Ϲ� �밢���� �ݴ� ���
	int row, col;

	for (row = 0; row < 19; row++)
		for (col = 0; col < 19; col++) {
			check_vertical = 0; // 3x3 ���ι��� üũ ����
			check_beside_vertical = 0; // 3x3 ���ι��� üũ ����
			check_horizontal = 0; //3x3 ���ι��� üũ ����
			check_beside_horizontal = 0; //3x3 ���ι��� üũ ����
			check_diagonal = 0;  // �Ϲݴ밢���� ���
			check_beside_diagonal = 0; // �Ϲݴ밢���� ���
			check_reverse_diagonal = 0; //�Ϲݴ밢���� �ݴ� ���
			check_reverse_beside_diagonal = 0; // �Ϲ� �밢���� �ݴ� ���

			if (pDoc->baduk[row][col] == 0) {
				for (i = 1; i < 3; i++) {
					if (col - i < 0) break; // ���ΰ� 0 �̸� �ݺ�Ż��
					if (pDoc->baduk[row][col - i] == d) { check_beside_horizontal++; }

				}

				for (i = 1; i < 3; i++) {
					if (col + i > 19) break;
					if (pDoc->baduk[row][col + i] == d) { check_horizontal++; }


				}

				for (i = 1; i < 3; i++) {
					if (row - i < 0) break;
					if (pDoc->baduk[row - i][col] == d) { check_beside_vertical++; }

				}

				for (i = 1; i < 3; i++) {
					if (row + i > 19) break;
					if (pDoc->baduk[row + i][col] == d) { check_vertical++; }

				}

				for (i = 1; i < 3; i++) {
					if (row + i > 19 || col + i > 19) break;
					if (pDoc->baduk[row + i][col + i] == d) { check_diagonal++; }


				}

				for (i = 1; i < 3; i++) {
					if (row - i < 0 || col - i <  0) break;
					if (pDoc->baduk[row - i][col - i] == d) { check_beside_diagonal++; }


				}

				for (i = 1; i < 3; i++) {
					if (row - i < 0 || col + i > 19) break;
					if (pDoc->baduk[row - i][col + i] == d) { check_reverse_diagonal++; }


				}

				for (i = 1; i < 3; i++) {
					if (row + i > 19 || col - i < 0) break;
					if (pDoc->baduk[row + i][col - i] == d) { check_reverse_beside_diagonal++; }



				}


				ibaduk[row][col] -= (check_vertical + check_beside_vertical + check_horizontal + check_beside_horizontal + check_diagonal + check_beside_diagonal + check_reverse_diagonal + check_reverse_beside_diagonal) / 10;
			}
			else ibaduk[row][col] = 0;
		}
}





void CMFCApplication3View::Delay(long d)
{
	while (d--);

}

void CMFCApplication3View::offendWeight_three_by_three(int o, int d)
{

	int three_by_three_flag;
	int four_by_three_flag;
	CMFCApplication3Doc* pDoc = GetDocument();
	int row, col;


	three_by_three_flag = 0;
	four_by_three_flag = 0;

	for (row = 0; row < 19; row++) {
		for (col = 0; col < 19; col++) {


			// 33 ����

			//==============�� ��ġ�� �߽����� 33 ���� �� üũ===============//

			if (pDoc->baduk[row + 1][col] == d) {			//�� ��ġ���� ������ üũ x?
				if (pDoc->baduk[row - 1][col] == d);			//4�� �ִ��� üũ ����.
				else if (pDoc->baduk[row - 1][col] == o) {			//  *x-   ����
					if (pDoc->baduk[row - 2][col] == d);
					else if (pDoc->baduk[row - 2][col] == o) {			//   **x- ����
						if (pDoc->baduk[row - 3][col] == d);
						else if (pDoc->baduk[row - 3][col] == o) {			// ***x- �ϼ�
							if (pDoc->baduk[row - 4][col] == d);
							else if (pDoc->baduk[row - 4][col] == o);
							else if (pDoc->baduk[row - 4][col] == 0) {
								if (pDoc->baduk[row - 5][col] != o) four_by_three_flag++;
							}
						}
						else if (pDoc->baduk[row - 3][col] == 0) {			// ? **x-
							if (pDoc->baduk[row - 4][col] == d);
							else if (pDoc->baduk[row - 4][col] == o) four_by_three_flag++;
							else if (pDoc->baduk[row - 4][col] == 0);
						}
					}
					else if (pDoc->baduk[row - 2][col] == 0) {		//  ? *x-
						if (pDoc->baduk[row - 3][col] == d);
						else if (pDoc->baduk[row - 3][col] == o) {		//   * *x-
							if (pDoc->baduk[row - 4][col] == d);
							else if (pDoc->baduk[row - 4][col] == o) {
								if (pDoc->baduk[row - 5][col] != o) four_by_three_flag++;
							}
							else if (pDoc->baduk[row - 4][col] == 0);
						}
						else if (pDoc->baduk[row - 3][col] == 0);
					}					
				}
				else if (pDoc->baduk[row - 1][col] == 0) {		//	? x-
					if (pDoc->baduk[row - 2][col] == o) {
						if (pDoc->baduk[row - 3][col] == o) {		// ** x-
							if (pDoc->baduk[row - 4][col] == o) {
								if (pDoc->baduk[row - 5][col] != o) four_by_three_flag++;
							}
						}
					}
				}
			}
			else if (pDoc->baduk[row + 1][col] == o) {			//�� ��ġ ���� ������ üũ x*?
				if (pDoc->baduk[row + 2][col] == d) {		//	  x*-
					if (pDoc->baduk[row - 1][col] == d);
					else if (pDoc->baduk[row - 1][col] == o) {	// *x*-
						if (pDoc->baduk[row - 2][col] == d);
						else if (pDoc->baduk[row - 2][col] == o) {	// **x*-
							if (pDoc->baduk[row - 3][col] == d);
							else if (pDoc->baduk[row - 3][col] == o);
							else if (pDoc->baduk[row - 3][col] == 0) {
								if (pDoc->baduk[row - 4][col] != o) four_by_three_flag++;
							}
						}
						else if (pDoc->baduk[row - 2][col] == 0) {		// ? *x*-
							if (pDoc->baduk[row - 3][col] == d);
							else if (pDoc->baduk[row - 3][col] == o) {
								if (pDoc->baduk[row - 4][col] != o) four_by_three_flag++;
							}
							else if (pDoc->baduk[row - 3][col] == 0);
						}
					}
					else if (pDoc->baduk[row - 1][col] == 0) {	// ? x*-
						if (pDoc->baduk[row - 2][col] == o) {
							if (pDoc->baduk[row - 3][col] == o) {
								if (pDoc->baduk[row - 4][col] != o) four_by_three_flag++;
							}
						}
					}
				}
				else if (pDoc->baduk[row + 2][col] == o) {			//x** ����
					if (pDoc->baduk[row + 3][col] == d) {			//x**-
						if (pDoc->baduk[row - 1][col] == d);
						else if (pDoc->baduk[row - 1][col] == o) {
							if (pDoc->baduk[row - 2][col] == d);
							else if (pDoc->baduk[row - 2][col] == o);
							else if (pDoc->baduk[row - 2][col] == 0) {
								if (pDoc->baduk[row - 3][col] != o) four_by_three_flag++;
							}
						}
						else if (pDoc->baduk[row - 1][col] == 0) {
							if (pDoc->baduk[row - 2][col] == o) {
								if (pDoc->baduk[row - 3][col] != o) four_by_three_flag++;
							}
						}
					}
					else if (pDoc->baduk[row + 3][col] == o) {			// x***
						if (pDoc->baduk[row + 4][col] == d) {
							if (pDoc->baduk[row - 1][col] == d);
							else if (pDoc->baduk[row - 1][col] == o);
							else if (pDoc->baduk[row - 1][col] == 0) {
								if (pDoc->baduk[row - 1][col] != o) four_by_three_flag++;
							}
						}
						else if (pDoc->baduk[row + 4][col] == o);
						else if (pDoc->baduk[row + 4][col] == 0) four_by_three_flag++;
					}
					else if (pDoc->baduk[row + 3][col] == 0) {
						if (pDoc->baduk[row + 4][col] == d || pDoc->baduk[row + 4][col] == 0) {
							if (pDoc->baduk[row - 1][col] == d);
							else if (pDoc->baduk[row - 1][col] == o)four_by_three_flag++;
							else if (pDoc->baduk[row - 1][col] == 0) {
								if (pDoc->baduk[row - 2][col] == d) {
									if (pDoc->baduk[row + 4][col] == 0) three_by_three_flag++; // �� ������ ���� ���ɼ� üũ
								}
								else if (pDoc->baduk[row - 2][col] == o)four_by_three_flag++;
								else if (pDoc->baduk[row - 2][col] == 0)three_by_three_flag++; // x**���� �Ϸ�
							}
						}
						else if (pDoc->baduk[row + 4][col] == o)four_by_three_flag++;
					}
				}
				else if (pDoc->baduk[row + 2][col] == 0) {		//�� ��ġ���� ������ x* ?
					if (pDoc->baduk[row + 3][col] == d || pDoc->baduk[row + 3][col] == 0) {		//x*   ����
						if (pDoc->baduk[row - 1][col] == d);
						else if (pDoc->baduk[row - 1][col] == o) {		// *x*
							if (pDoc->baduk[row - 2][col] == d);
							else if (pDoc->baduk[row - 2][col] == o) four_by_three_flag++;
							else if (pDoc->baduk[row - 2][col] == 0) {
								if (pDoc->baduk[row - 3][col] == d) {
									if (pDoc->baduk[row + 3][col] == 0)	three_by_three_flag++;
								}
								else if (pDoc->baduk[row - 3][col] == o) four_by_three_flag++;
								else if (pDoc->baduk[row - 3][col] == 0) three_by_three_flag++;
							}
						}
						else if (pDoc->baduk[row - 1][col] == 0) {		// ? x*
							if (pDoc->baduk[row - 2][col] == d);
							else if (pDoc->baduk[row - 2][col] == o) {		// * x*
								if (pDoc->baduk[row - 3][col] == d);
								else if (pDoc->baduk[row - 3][col] == o) four_by_three_flag++;
								else if (pDoc->baduk[row - 3][col] == 0) {
									if (pDoc->baduk[row - 4][col] == d) three_by_three_flag++;
									else if (pDoc->baduk[row - 4][col] == o);
									else if (pDoc->baduk[row - 4][col] == 0) three_by_three_flag++;
								}
							}
							else if (pDoc->baduk[row - 2][col] == 0);
						}
					}
					else if (pDoc->baduk[row + 3][col] == o) {		//x* *
						if (pDoc->baduk[row + 4][col] == d) {
							if (pDoc->baduk[row - 1][col] == o) {
								if (pDoc->baduk[row - 2][col] != o) four_by_three_flag++;
							}
						}
						else if (pDoc->baduk[row + 4][col] == o) four_by_three_flag++;
						else if (pDoc->baduk[row + 4][col] == 0) {
							if (pDoc->baduk[row - 1][col] == d);
							else if (pDoc->baduk[row - 1][col] == o) {
								if (pDoc->baduk[row - 1][col] != o) four_by_three_flag++;
							}
							else if (pDoc->baduk[row - 1][col] == 0) {
								if (pDoc->baduk[row - 2][col] == d) three_by_three_flag++;
								else if (pDoc->baduk[row - 2][col] == o);
								else if (pDoc->baduk[row - 2][col] == 0) three_by_three_flag++;
							}
						}
					}
				}
			}
			else if (pDoc->baduk[row + 1][col] == 0) {			//x ? ����.
				if (pDoc->baduk[row + 2][col] == d || pDoc->baduk[row + 2][col] == 0) {		//   x ���� �˻� ����.
					if (pDoc->baduk[row - 1][col] == d);
					else if (pDoc->baduk[row - 1][col] == o) {				//   *x ����.
						if (pDoc->baduk[row - 2][col] == d);
						else if (pDoc->baduk[row - 2][col] == o) {				//   **x
							if (pDoc->baduk[row - 3][col] == d);
							else if (pDoc->baduk[row - 3][col] == o) four_by_three_flag++;
							else if (pDoc->baduk[row - 3][col] == 0) {
								if (pDoc->baduk[row - 4][col] == d) {
									if (pDoc->baduk[row + 2][col] == 0) three_by_three_flag++;
								}
								else if (pDoc->baduk[row - 4][col] == o) four_by_three_flag++;
								else if (pDoc->baduk[row - 4][col] == 0) three_by_three_flag++;
							}
						}
						else if (pDoc->baduk[row - 2][col] == 0) {			// ? *x
							if (pDoc->baduk[row - 3][col] == d);
							else if (pDoc->baduk[row - 3][col] == o) {			// * *x
								if (pDoc->baduk[row - 4][col] == d);
								else if (pDoc->baduk[row - 4][col] == o) four_by_three_flag++;
								else if (pDoc->baduk[row - 4][col] == 0) three_by_three_flag++;
							}
							else if (pDoc->baduk[row - 3][col] == 0);
						}
					}
					else if (pDoc->baduk[row - 1][col] == 0) {		// ? x ����
						if (pDoc->baduk[row - 2][col] == d);
						else if (pDoc->baduk[row - 2][col] == o) {		// * x
							if (pDoc->baduk[row - 3][col] == d);
							else if (pDoc->baduk[row - 3][col] == o) {		// ** x
								if (pDoc->baduk[row - 4][col] == d);
								else if (pDoc->baduk[row - 4][col] == o) four_by_three_flag++;
								else if (pDoc->baduk[row - 4][col] == 0) {
									if (pDoc->baduk[row - 5][col] == d) three_by_three_flag++;
									else if (pDoc->baduk[row - 5][col] == o);
									else if (pDoc->baduk[row - 5][col] == 0) three_by_three_flag++;
								}
							}
							else if (pDoc->baduk[row - 3][col] == 0);
						}
					}
				}
				else if (pDoc->baduk[row + 2][col] == o) {		// x *
					if (pDoc->baduk[row + 3][col] == d);
					else if (pDoc->baduk[row + 3][col] == o) {		// x **
						if (pDoc->baduk[row + 4][col] == d);
						else if (pDoc->baduk[row + 4][col] == o) four_by_three_flag++;
						else if (pDoc->baduk[row + 4][col] == 0) {
							if (pDoc->baduk[row + 5][col] == d || pDoc->baduk[row + 5][col] == 0) {
								if (pDoc->baduk[row - 1][col] == d);
								else if (pDoc->baduk[row - 1][col] == o) four_by_three_flag++;
								else if (pDoc->baduk[row - 1][col] == 0) {
									if (pDoc->baduk[row - 2][col] == d);
									else if (pDoc->baduk[row - 2][col] == o);
									else if (pDoc->baduk[row - 2][col] == 0) three_by_three_flag++;
								}
							}
							else if (pDoc->baduk[row + 5][col] == o);
						}
					}
					else if (pDoc->baduk[row + 3][col] == 0) {		// x *  ����
						if (pDoc->baduk[row + 4][col] == d || pDoc->baduk[row + 4][col] == 0) {
							if (pDoc->baduk[row - 1][col] == d);
							else if (pDoc->baduk[row - 1][col] == o) {		// *x * ����
								if (pDoc->baduk[row - 2][col] == d);
								else if (pDoc->baduk[row - 2][col] == o) four_by_three_flag++;
								else if (pDoc->baduk[row - 2][col] == 0) three_by_three_flag++;
							}
							else if (pDoc->baduk[row - 1][col] == 0);
						}
						else if (pDoc->baduk[row + 4][col] == o);
					}
				}
			}

			// ====================== ������ üũ �� ====================== //



			//==============�� ��ġ�� �߽����� 33 ���� �� üũ===============//

			if (pDoc->baduk[row][col + 1] == d) {			//�� ��ġ���� ������ üũ x?
				if (pDoc->baduk[row][col - 1] == d);			//4�� �ִ��� üũ ����.
				else if (pDoc->baduk[row][col - 1] == o) {			//  *x-   ����
					if (pDoc->baduk[row][col - 2] == d);
					else if (pDoc->baduk[row][col - 2] == o) {			//   **x- ����
						if (pDoc->baduk[row][col - 3] == d);
						else if (pDoc->baduk[row][col - 3] == o) {			// ***x- �ϼ�
							if (pDoc->baduk[row][col - 4] == d);
							else if (pDoc->baduk[row][col - 4] == o);
							else if (pDoc->baduk[row][col - 4] == 0) {
								if (pDoc->baduk[row][col - 5] != o) four_by_three_flag++;
							}
						}
						else if (pDoc->baduk[row][col - 3] == 0) {			// ? **x-
							if (pDoc->baduk[row][col - 4] == d);
							else if (pDoc->baduk[row][col - 4] == o) four_by_three_flag++;
							else if (pDoc->baduk[row][col - 4] == 0);
						}
					}
					else if (pDoc->baduk[row][col - 2] == 0) {		//  ? *x-
						if (pDoc->baduk[row][col - 3] == d);
						else if (pDoc->baduk[row][col - 3] == o) {		//   * *x-
							if (pDoc->baduk[row][col - 4] == d);
							else if (pDoc->baduk[row][col - 4] == o) {
								if (pDoc->baduk[row][col - 5] != o) four_by_three_flag++;
							}
							else if (pDoc->baduk[row][col - 4] == 0);
						}
						else if (pDoc->baduk[row][col - 3] == 0);
					}
				}
				else if (pDoc->baduk[row][col - 1] == 0) {		//	? x-
					if (pDoc->baduk[row][col - 2] == o) {
						if (pDoc->baduk[row][col - 3] == o) {		// ** x-
							if (pDoc->baduk[row][col - 4] == o) {
								if (pDoc->baduk[row][col - 5] != o) four_by_three_flag++;
							}
						}
					}
				}
			}
			else if (pDoc->baduk[row][col + 1] == o) {			//�� ��ġ ���� ������ üũ x*?
				if (pDoc->baduk[row][col + 2] == d) {		//	  x*-
					if (pDoc->baduk[row][col - 1] == d);
					else if (pDoc->baduk[row][col - 1] == o) {	// *x*-
						if (pDoc->baduk[row][col - 2] == d);
						else if (pDoc->baduk[row][col - 2] == o) {	// **x*-
							if (pDoc->baduk[row][col - 3] == d);
							else if (pDoc->baduk[row][col - 3] == o);
							else if (pDoc->baduk[row][col - 3] == 0) {
								if (pDoc->baduk[row][col - 4] != o) four_by_three_flag++;
							}
						}
						else if (pDoc->baduk[row][col - 2] == 0) {		// ? *x*-
							if (pDoc->baduk[row][col - 3] == d);
							else if (pDoc->baduk[row][col - 3] == o) {
								if (pDoc->baduk[row][col - 4] != o) four_by_three_flag++;
							}
							else if (pDoc->baduk[row][col - 3] == 0);
						}
					}
					else if (pDoc->baduk[row][col - 1] == 0) {	// ? x*-
						if (pDoc->baduk[row][col - 2] == o) {
							if (pDoc->baduk[row][col - 3] == o) {
								if (pDoc->baduk[row][col - 4] != o) four_by_three_flag++;
							}
						}
					}
				}
				else if (pDoc->baduk[row][col + 2] == o) {			//x** ����
					if (pDoc->baduk[row][col + 3] == d) {			//x**-
						if (pDoc->baduk[row][col - 1] == d);
						else if (pDoc->baduk[row][col - 1] == o) {
							if (pDoc->baduk[row][col - 2] == d);
							else if (pDoc->baduk[row][col - 2] == o);
							else if (pDoc->baduk[row][col - 2] == 0) {
								if (pDoc->baduk[row][col - 3] != o) four_by_three_flag++;
							}
						}
						else if (pDoc->baduk[row][col - 1] == 0) {
							if (pDoc->baduk[row][col - 2] == o) {
								if (pDoc->baduk[row][col - 3] != o) four_by_three_flag++;
							}
						}
					}
					else if (pDoc->baduk[row][col + 3] == o) {			// x***
						if (pDoc->baduk[row][col + 4] == d) {
							if (pDoc->baduk[row][col - 1] == d);
							else if (pDoc->baduk[row][col - 1] == o);
							else if (pDoc->baduk[row][col - 1] == 0) {
								if (pDoc->baduk[row][col - 1] != o) four_by_three_flag++;
							}
						}
						else if (pDoc->baduk[row][col + 4] == o);
						else if (pDoc->baduk[row][col + 4] == 0) four_by_three_flag++;
					}
					else if (pDoc->baduk[row][col + 3] == 0) {
						if (pDoc->baduk[row][col + 4] == d || pDoc->baduk[row + 4][col] == 0) {
							if (pDoc->baduk[row][col - 1] == d);
							else if (pDoc->baduk[row][col - 1] == o)four_by_three_flag++;
							else if (pDoc->baduk[row][col - 1] == 0) {
								if (pDoc->baduk[row][col - 2] == d) {
									if (pDoc->baduk[row][col + 4] == 0) three_by_three_flag++; // �� ������ ���� ���ɼ� üũ
								}
								else if (pDoc->baduk[row][col - 2] == o)four_by_three_flag++;
								else if (pDoc->baduk[row][col - 2] == 0)three_by_three_flag++; // x**���� �Ϸ�
							}
						}
						else if (pDoc->baduk[row][col + 4] == o)four_by_three_flag++;
					}
				}
				else if (pDoc->baduk[row][col + 2] == 0) {		//�� ��ġ���� ������ x* ?
					if (pDoc->baduk[row][col + 3] == d || pDoc->baduk[row][col + 3] == 0) {		//x*   ����
						if (pDoc->baduk[row][col - 1] == d);
						else if (pDoc->baduk[row][col - 1] == o) {		// *x*
							if (pDoc->baduk[row][col - 2] == d);
							else if (pDoc->baduk[row][col - 2] == o) four_by_three_flag++;
							else if (pDoc->baduk[row][col - 2] == 0) {
								if (pDoc->baduk[row][col - 3] == d) {
									if (pDoc->baduk[row][col + 3] == 0)	three_by_three_flag++;
								}
								else if (pDoc->baduk[row][col - 3] == o) four_by_three_flag++;
								else if (pDoc->baduk[row][col - 3] == 0) three_by_three_flag++;
							}
						}
						else if (pDoc->baduk[row][col - 1] == 0) {		// ? x*
							if (pDoc->baduk[row][col - 2] == d);
							else if (pDoc->baduk[row][col - 2] == o) {		// * x*
								if (pDoc->baduk[row][col - 3] == d);
								else if (pDoc->baduk[row][col - 3] == o) four_by_three_flag++;
								else if (pDoc->baduk[row][col - 3] == 0) {
									if (pDoc->baduk[row][col - 4] == d) three_by_three_flag++;
									else if (pDoc->baduk[row][col - 4] == o);
									else if (pDoc->baduk[row][col - 4] == 0) three_by_three_flag++;
								}
							}
							else if (pDoc->baduk[row][col - 2] == 0);
						}
					}
					else if (pDoc->baduk[row][col + 3] == o) {		//x* *
						if (pDoc->baduk[row][col + 4] == d) {
							if (pDoc->baduk[row][col - 1] == o) {
								if (pDoc->baduk[row][col - 2] != o) four_by_three_flag++;
							}
						}
						else if (pDoc->baduk[row][col + 4] == o) four_by_three_flag++;
						else if (pDoc->baduk[row][col + 4] == 0) {
							if (pDoc->baduk[row][col - 1] == d);
							else if (pDoc->baduk[row][col - 1] == o) {
								if (pDoc->baduk[row][col - 2] != o) four_by_three_flag++;
							}
							else if (pDoc->baduk[row][col - 1] == 0) {
								if (pDoc->baduk[row][col - 2] == d) three_by_three_flag++;
								else if (pDoc->baduk[row][col - 2] == o);
								else if (pDoc->baduk[row][col - 2] == 0) three_by_three_flag++;
							}
						}
					}
				}
			}
			else if (pDoc->baduk[row][col + 1] == 0) {			//x ? ����.
				if (pDoc->baduk[row][col + 2] == d || pDoc->baduk[row][col + 2] == 0) {		//   x ���� �˻� ����.
					if (pDoc->baduk[row][col - 1] == d);
					else if (pDoc->baduk[row][col - 1] == o) {				//   *x ����.
						if (pDoc->baduk[row][col - 2] == d);
						else if (pDoc->baduk[row][col - 2] == o) {				//   **x
							if (pDoc->baduk[row][col - 3] == d);
							else if (pDoc->baduk[row][col - 3] == o) four_by_three_flag++;
							else if (pDoc->baduk[row][col - 3] == 0) {
								if (pDoc->baduk[row][col - 4] == d) {
									if (pDoc->baduk[row][col + 2] == 0) three_by_three_flag++;
								}
								else if (pDoc->baduk[row][col - 4] == o) four_by_three_flag++;
								else if (pDoc->baduk[row][col - 4] == 0) three_by_three_flag++;
							}
						}
						else if (pDoc->baduk[row][col - 2] == 0) {			// ? *x
							if (pDoc->baduk[row][col - 3] == d);
							else if (pDoc->baduk[row][col - 3] == o) {			// * *x
								if (pDoc->baduk[row][col - 4] == d);
								else if (pDoc->baduk[row][col - 4] == o) four_by_three_flag++;
								else if (pDoc->baduk[row][col - 4] == 0) three_by_three_flag++;
							}
							else if (pDoc->baduk[row][col - 3] == 0);
						}
					}
					else if (pDoc->baduk[row][col - 1] == 0) {		// ? x ����
						if (pDoc->baduk[row][col - 2] == d);
						else if (pDoc->baduk[row][col - 2] == o) {		// * x
							if (pDoc->baduk[row][col - 3] == d);
							else if (pDoc->baduk[row][col - 3] == o) {		// ** x
								if (pDoc->baduk[row][col - 4] == d);
								else if (pDoc->baduk[row][col - 4] == o) four_by_three_flag++;
								else if (pDoc->baduk[row][col - 4] == 0) {
									if (pDoc->baduk[row][col - 5] == d) three_by_three_flag++;
									else if (pDoc->baduk[row][col - 5] == o);
									else if (pDoc->baduk[row][col - 5] == 0) three_by_three_flag++;
								}
							}
							else if (pDoc->baduk[row][col - 3] == 0);
						}
					}
				}
				else if (pDoc->baduk[row][col + 2] == o) {		// x *
					if (pDoc->baduk[row][col + 3] == d);
					else if (pDoc->baduk[row][col + 3] == o) {		// x **
						if (pDoc->baduk[row][col + 4] == d);
						else if (pDoc->baduk[row][col + 4] == o) four_by_three_flag++;
						else if (pDoc->baduk[row][col + 4] == 0) {
							if (pDoc->baduk[row][col + 5] == d || pDoc->baduk[row][col + 5] == 0) {
								if (pDoc->baduk[row][col - 1] == d);
								else if (pDoc->baduk[row][col - 1] == o) four_by_three_flag++;
								else if (pDoc->baduk[row][col - 1] == 0) {
									if (pDoc->baduk[row][col - 2] == d);
									else if (pDoc->baduk[row][col - 2] == o);
									else if (pDoc->baduk[row][col - 2] == 0) three_by_three_flag++;
								}
							}
							else if (pDoc->baduk[row][col + 5] == o);
						}
					}
					else if (pDoc->baduk[row][col + 3] == 0) {		// x *  ����
						if (pDoc->baduk[row][col + 4] == d || pDoc->baduk[row][col + 4] == 0) {
							if (pDoc->baduk[row][col - 1] == d);
							else if (pDoc->baduk[row][col - 1] == o) {		// *x * ����
								if (pDoc->baduk[row][col - 2] == d);
								else if (pDoc->baduk[row][col - 2] == o) four_by_three_flag++;
								else if (pDoc->baduk[row][col - 2] == 0) three_by_three_flag++;
							}
							else if (pDoc->baduk[row][col - 1] == 0);
						}
						else if (pDoc->baduk[row][col + 4] == o);
					}
				}
			}

			// ====================== ������ üũ �� ====================== //




			//==============�� ��ġ�� �߽����� �»� --> ���� �밢�� �� üũ===============//

			if (pDoc->baduk[row + 1][col + 1] == d);			//�� ��ġ���� ������ üũ x?
			else if (pDoc->baduk[row + 1][col + 1] == o) {			//�� ��ġ ���� ������ üũ x*?
				if (pDoc->baduk[row + 2][col + 2] == d);
				else if (pDoc->baduk[row + 2][col + 2] == o) {			//x** ����
					if (pDoc->baduk[row + 3][col + 3] == d);
					else if (pDoc->baduk[row + 3][col + 3] == o) four_by_three_flag++;
					else if (pDoc->baduk[row + 3][col + 3] == 0) {
						if (pDoc->baduk[row + 4][col + 4] == d || pDoc->baduk[row + 4][col + 4] == 0) {
							if (pDoc->baduk[row - 1][col - 1] == d);
							else if (pDoc->baduk[row - 1][col - 1] == o) four_by_three_flag++;
							else if (pDoc->baduk[row - 1][col - 1] == 0) {
								if (pDoc->baduk[row - 2][col - 2] == d) {
									if (pDoc->baduk[row + 4][col + 4] == 0) three_by_three_flag++; // �� ������ ���� ���ɼ� üũ
								}
								else if (pDoc->baduk[row - 2][col - 2] == o) four_by_three_flag++;
								else if (pDoc->baduk[row - 2][col - 2] == 0) three_by_three_flag++; // x**���� �Ϸ�
							}
						}
						else if (pDoc->baduk[row + 4][col + 4] == o) four_by_three_flag++;
					}
				}
				else if (pDoc->baduk[row + 2][col + 2] == 0) {		//�� ��ġ���� ������ x* ?
					if (pDoc->baduk[row + 3][col + 3] == d || pDoc->baduk[row + 3][col + 3] == 0) {		//x*   ����
						if (pDoc->baduk[row - 1][col - 1] == d);
						else if (pDoc->baduk[row - 1][col - 1] == o) {		// *x*
							if (pDoc->baduk[row - 2][col - 2] == d);
							else if (pDoc->baduk[row - 2][col - 2] == o) four_by_three_flag++;
							else if (pDoc->baduk[row - 2][col - 2] == 0) {
								if (pDoc->baduk[row - 3][col - 3] == d) {
									if (pDoc->baduk[row + 3][col + 3] == 0)	three_by_three_flag++;
								}
								else if (pDoc->baduk[row - 3][col - 3] == o) four_by_three_flag++;
								else if (pDoc->baduk[row - 3][col - 3] == 0) three_by_three_flag++;
							}
						}
						else if (pDoc->baduk[row - 1][col - 1] == 0) {		// ? x*
							if (pDoc->baduk[row - 2][col - 2] == d);
							else if (pDoc->baduk[row - 2][col - 2] == o) {		// * x*
								if (pDoc->baduk[row - 3][col - 3] == d);
								else if (pDoc->baduk[row - 3][col - 3] == o) four_by_three_flag++;
								else if (pDoc->baduk[row - 3][col - 3] == 0) {
									if (pDoc->baduk[row - 4][col - 4] == d) three_by_three_flag++;
									else if (pDoc->baduk[row - 4][col - 4] == o);
									else if (pDoc->baduk[row - 4][col - 4] == 0) three_by_three_flag++;
								}
							}
							else if (pDoc->baduk[row - 2][col - 2] == 0);
						}
					}
					else if (pDoc->baduk[row + 3][col + 3] == o) {		//x* *
						if (pDoc->baduk[row + 4][col + 4] == d);
						else if (pDoc->baduk[row + 4][col + 4] == o) four_by_three_flag++;
						else if (pDoc->baduk[row + 4][col + 4] == 0) {
							if (pDoc->baduk[row - 1][col - 1] == d);
							else if (pDoc->baduk[row - 1][col - 1] == o) four_by_three_flag++;
							else if (pDoc->baduk[row - 1][col - 1] == 0) {
								if (pDoc->baduk[row - 2][col - 2] == d) three_by_three_flag++;
								else if (pDoc->baduk[row - 2][col - 2] == o);
								else if (pDoc->baduk[row - 2][col - 2] == 0) three_by_three_flag++;
							}
						}
					}
				}
			}
			else if (pDoc->baduk[row + 1][col + 1] == 0) {			//x ? ����.
				if (pDoc->baduk[row + 2][col + 2] == d || pDoc->baduk[row + 2][col + 2] == 0) {		//   x ���� �˻� ����.
					if (pDoc->baduk[row - 1][col - 1] == d);
					else if (pDoc->baduk[row - 1][col - 1] == o) {				//   *x ����.
						if (pDoc->baduk[row - 2][col - 2] == d);
						else if (pDoc->baduk[row - 2][col - 2] == o) {				//   **x
							if (pDoc->baduk[row - 3][col - 3] == d);
							else if (pDoc->baduk[row - 3][col - 3] == o) four_by_three_flag++;
							else if (pDoc->baduk[row - 3][col - 3] == 0) {
								if (pDoc->baduk[row - 4][col - 4] == d) {
									if (pDoc->baduk[row + 2][col + 2] == 0) three_by_three_flag++;
								}
								else if (pDoc->baduk[row - 4][col - 4] == o) four_by_three_flag++;
								else if (pDoc->baduk[row - 4][col - 4] == 0) three_by_three_flag++;
							}
						}
						else if (pDoc->baduk[row - 2][col - 2] == 0) {			// ? *x
							if (pDoc->baduk[row - 3][col - 3] == d);
							else if (pDoc->baduk[row - 3][col - 3] == o) {			// * *x
								if (pDoc->baduk[row - 4][col - 4] == d);
								else if (pDoc->baduk[row - 4][col - 4] == o) four_by_three_flag++;
								else if (pDoc->baduk[row - 4][col - 4] == 0) three_by_three_flag++;
							}
							else if (pDoc->baduk[row - 3][col - 3] == 0);
						}
					}
					else if (pDoc->baduk[row - 1][col - 1] == 0) {		// ? x ����
						if (pDoc->baduk[row - 2][col - 2] == d);
						else if (pDoc->baduk[row - 2][col - 2] == o) {		// * x
							if (pDoc->baduk[row - 3][col - 3] == d);
							else if (pDoc->baduk[row - 3][col - 3] == o) {		// ** x
								if (pDoc->baduk[row - 4][col - 4] == d);
								else if (pDoc->baduk[row - 4][col - 4] == o) four_by_three_flag++;
								else if (pDoc->baduk[row - 4][col - 4] == 0) {
									if (pDoc->baduk[row - 5][col - 5] == d) three_by_three_flag++;
									else if (pDoc->baduk[row - 5][col - 5] == o);
									else if (pDoc->baduk[row - 5][col - 5] == 0) three_by_three_flag++;
								}
							}
							else if (pDoc->baduk[row - 3][col - 3] == 0);
						}
					}
				}
				else if (pDoc->baduk[row + 2][col + 2] == o) {		// x *
					if (pDoc->baduk[row + 3][col + 3] == d);
					else if (pDoc->baduk[row + 3][col + 3] == o) {		// x **
						if (pDoc->baduk[row + 4][col + 4] == d);
						else if (pDoc->baduk[row + 4][col + 4] == o) four_by_three_flag++;
						else if (pDoc->baduk[row + 4][col + 4] == 0) {
							if (pDoc->baduk[row + 5][col + 5] == d || pDoc->baduk[row + 5][col + 5] == 0) {
								if (pDoc->baduk[row - 1][col - 1] == d);
								else if (pDoc->baduk[row - 1][col - 1] == o) four_by_three_flag++;
								else if (pDoc->baduk[row - 1][col - 1] == 0) {
									if (pDoc->baduk[row - 2][col - 2] == d);
									else if (pDoc->baduk[row - 2][col - 2] == o);
									else if (pDoc->baduk[row - 2][col - 2] == 0) three_by_three_flag++;
								}
							}
							else if (pDoc->baduk[row + 5][col + 5] == o);
						}
					}
					else if (pDoc->baduk[row + 3][col + 3] == 0) {		// x *  ����
						if (pDoc->baduk[row + 4][col + 4] == d || pDoc->baduk[row + 4][col + 4] == 0) {
							if (pDoc->baduk[row - 1][col - 1] == d);
							else if (pDoc->baduk[row - 1][col - 1] == o) {		// *x * ����
								if (pDoc->baduk[row - 2][col - 2] == d);
								else if (pDoc->baduk[row - 2][col - 2] == o) four_by_three_flag++;
								else if (pDoc->baduk[row - 2][col - 2] == 0) three_by_three_flag++;
							}
							else if (pDoc->baduk[row - 1][col - 1] == 0);
						}
						else if (pDoc->baduk[row + 4][col + 4] == o);
					}
				}
			}

			// ====================== �»� ���� �밢�� üũ �� ====================== //




			//==============�� ��ġ�� �߽����� ��� --> ���� �밢�� �� üũ===============//

			if (pDoc->baduk[row + 1][col - 1] == d);			//�� ��ġ���� ������ üũ x?
			else if (pDoc->baduk[row + 1][col - 1] == o) {			//�� ��ġ ���� ������ üũ x*?
				if (pDoc->baduk[row + 2][col - 2] == d);
				else if (pDoc->baduk[row + 2][col - 2] == o) {			//x** ����
					if (pDoc->baduk[row + 3][col - 3] == d);
					else if (pDoc->baduk[row + 3][col - 3] == o) four_by_three_flag++;
					else if (pDoc->baduk[row + 3][col - 3] == 0) {
						if (pDoc->baduk[row + 4][col - 4] == d || pDoc->baduk[row + 4][col - 4] == 0) {
							if (pDoc->baduk[row - 1][col + 1] == d);
							else if (pDoc->baduk[row - 1][col + 1] == o) four_by_three_flag++;
							else if (pDoc->baduk[row - 1][col + 1] == 0) {
								if (pDoc->baduk[row - 2][col + 2] == d) {
									if (pDoc->baduk[row + 4][col - 4] == 0) three_by_three_flag++; // �� ������ ���� ���ɼ� üũ
								}
								else if (pDoc->baduk[row - 2][col + 2] == o) four_by_three_flag++;
								else if (pDoc->baduk[row - 2][col + 2] == 0) three_by_three_flag++; // x**���� �Ϸ�
							}
						}
						else if (pDoc->baduk[row + 4][col - 4] == o) four_by_three_flag++;
					}
				}
				else if (pDoc->baduk[row + 2][col - 2] == 0) {		//�� ��ġ���� ������ x* ?
					if (pDoc->baduk[row + 3][col - 3] == d || pDoc->baduk[row + 3][col - 3] == 0) {		//x*   ����
						if (pDoc->baduk[row - 1][col + 1] == d);
						else if (pDoc->baduk[row - 1][col + 1] == o) {		// *x*
							if (pDoc->baduk[row - 2][col + 2] == d);
							else if (pDoc->baduk[row - 2][col + 2] == o) four_by_three_flag++;
							else if (pDoc->baduk[row - 2][col + 2] == 0) {
								if (pDoc->baduk[row - 3][col + 3] == d) {
									if (pDoc->baduk[row + 3][col - 3] == 0)	three_by_three_flag++;
								}
								else if (pDoc->baduk[row - 3][col + 3] == o) four_by_three_flag++;
								else if (pDoc->baduk[row - 3][col + 3] == 0) three_by_three_flag++;
							}
						}
						else if (pDoc->baduk[row - 1][col + 1] == 0) {		// ? x*
							if (pDoc->baduk[row - 2][col + 2] == d);
							else if (pDoc->baduk[row - 2][col + 2] == o) {		// * x*
								if (pDoc->baduk[row - 3][col + 3] == d);
								else if (pDoc->baduk[row - 3][col + 3] == o) four_by_three_flag++;
								else if (pDoc->baduk[row - 3][col + 3] == 0) {
									if (pDoc->baduk[row - 4][col + 4] == d) three_by_three_flag++;
									else if (pDoc->baduk[row - 4][col + 4] == o);
									else if (pDoc->baduk[row - 4][col + 4] == 0) three_by_three_flag++;
								}
							}
							else if (pDoc->baduk[row - 2][col + 2] == 0);
						}
					}
					else if (pDoc->baduk[row + 3][col - 3] == o) {		//x* *
						if (pDoc->baduk[row + 4][col - 4] == d);
						else if (pDoc->baduk[row + 4][col - 4] == o) four_by_three_flag++;
						else if (pDoc->baduk[row + 4][col - 4] == 0) {
							if (pDoc->baduk[row - 1][col + 1] == d);
							else if (pDoc->baduk[row - 1][col + 1] == o) four_by_three_flag++;
							else if (pDoc->baduk[row - 1][col + 1] == 0) {
								if (pDoc->baduk[row - 2][col + 2] == d) three_by_three_flag++;
								else if (pDoc->baduk[row - 2][col + 2] == o);
								else if (pDoc->baduk[row - 2][col + 2] == 0) three_by_three_flag++;
							}
						}
					}
				}
			}
			else if (pDoc->baduk[row + 1][col - 1] == 0) {			//x ? ����.
				if (pDoc->baduk[row + 2][col - 2] == d || pDoc->baduk[row + 2][col - 2] == 0) {		//   x ���� �˻� ����.
					if (pDoc->baduk[row - 1][col + 1] == d);
					else if (pDoc->baduk[row - 1][col + 1] == o) {				//   *x ����.
						if (pDoc->baduk[row - 2][col + 2] == d);
						else if (pDoc->baduk[row - 2][col + 2] == o) {				//   **x
							if (pDoc->baduk[row - 3][col + 3] == d);
							else if (pDoc->baduk[row - 3][col + 3] == o) four_by_three_flag++;
							else if (pDoc->baduk[row - 3][col + 3] == 0) {
								if (pDoc->baduk[row - 4][col + 4] == d) {
									if (pDoc->baduk[row + 2][col - 2] == 0) three_by_three_flag++;
								}
								else if (pDoc->baduk[row - 4][col + 4] == o) four_by_three_flag++;
								else if (pDoc->baduk[row - 4][col + 4] == 0) three_by_three_flag++;
							}
						}
						else if (pDoc->baduk[row - 2][col + 2] == 0) {			// ? *x
							if (pDoc->baduk[row - 3][col + 3] == d);
							else if (pDoc->baduk[row - 3][col + 3] == o) {			// * *x
								if (pDoc->baduk[row - 4][col + 4] == d);
								else if (pDoc->baduk[row - 4][col + 4] == o) four_by_three_flag++;
								else if (pDoc->baduk[row - 4][col + 4] == 0) three_by_three_flag++;
							}
							else if (pDoc->baduk[row - 3][col + 3] == 0);
						}
					}
					else if (pDoc->baduk[row - 1][col + 1] == 0) {		// ? x ����
						if (pDoc->baduk[row - 2][col + 2] == d);
						else if (pDoc->baduk[row - 2][col + 2] == o) {		// * x
							if (pDoc->baduk[row - 3][col + 3] == d);
							else if (pDoc->baduk[row - 3][col + 3] == o) {		// ** x
								if (pDoc->baduk[row - 4][col + 4] == d);
								else if (pDoc->baduk[row - 4][col + 4] == o) four_by_three_flag++;
								else if (pDoc->baduk[row - 4][col + 4] == 0) {
									if (pDoc->baduk[row - 5][col + 5] == d) three_by_three_flag++;
									else if (pDoc->baduk[row - 5][col + 5] == o);
									else if (pDoc->baduk[row - 5][col + 5] == 0) three_by_three_flag++;
								}
							}
							else if (pDoc->baduk[row - 3][col + 3] == 0);
						}
					}
				}
				else if (pDoc->baduk[row + 2][col - 2] == o) {		// x *
					if (pDoc->baduk[row + 3][col - 3] == d);
					else if (pDoc->baduk[row + 3][col - 3] == o) {		// x **
						if (pDoc->baduk[row + 4][col - 4] == d);
						else if (pDoc->baduk[row + 4][col - 4] == o) four_by_three_flag++;
						else if (pDoc->baduk[row + 4][col - 4] == 0) {
							if (pDoc->baduk[row + 5][col - 5] == d || pDoc->baduk[row + 5][col - 5] == 0) {
								if (pDoc->baduk[row - 1][col + 1] == d);
								else if (pDoc->baduk[row - 1][col + 1] == o) four_by_three_flag++;
								else if (pDoc->baduk[row - 1][col + 1] == 0) {
									if (pDoc->baduk[row - 2][col + 2] == d);
									else if (pDoc->baduk[row - 2][col + 2] == o);
									else if (pDoc->baduk[row - 2][col + 2] == 0) three_by_three_flag++;
								}
							}
							else if (pDoc->baduk[row + 5][col - 5] == o);
						}
					}
					else if (pDoc->baduk[row + 3][col - 3] == 0) {		// x *  ����
						if (pDoc->baduk[row + 4][col - 4] == d || pDoc->baduk[row + 4][col - 4] == 0) {
							if (pDoc->baduk[row - 1][col + 1] == d);
							else if (pDoc->baduk[row - 1][col + 1] == o) {		// *x * ����
								if (pDoc->baduk[row - 2][col + 2] == d);
								else if (pDoc->baduk[row - 2][col + 2] == o) four_by_three_flag++;
								else if (pDoc->baduk[row - 2][col + 2] == 0) three_by_three_flag++;
							}
							else if (pDoc->baduk[row - 1][col + 1] == 0);
						}
						else if (pDoc->baduk[row + 4][col - 4] == o);
					}
				}
			}

			// ====================== ��� ���� �밢�� üũ �� ====================== //



			// 33 ��

			if (four_by_three_flag >= 1 && three_by_three_flag == 1) {
				ibaduk[row][col] += o_four_three;		
				obaduk[row][col] += o_four_three;
			}

			if (three_by_three_flag >= 2) {
				ibaduk[row][col] += -200000;
			}

			three_by_three_flag = 0;
			four_by_three_flag = 0;


		}
	}
	
}



void CMFCApplication3View::dffendWeight_three_by_three(int o, int d)
{

	int three_by_three_flag;
	int four_by_three_flag;
	CMFCApplication3Doc* pDoc = GetDocument();
	int row, col;


	three_by_three_flag = 0;
	four_by_three_flag = 0;

	/*

	for (row = 0; row < 19; row++) {
	for (col = 0; col < 19; col++) {
	if (pDoc->baduk[row][col] == 2) pDoc->baduk[row][col] = 1;
	else if (pDoc->baduk[row][col] == 1) pDoc->baduk[row][col] = 2;
	}
	}
	*/

	for (row = 0; row < 19; row++) {
		for (col = 0; col < 19; col++) {


			// 33 ����

			//==============�� ��ġ�� �߽����� 33 ���� �� üũ===============//

			if (pDoc->baduk[row + 1][col] == d) {			//�� ��ġ���� ������ üũ x?
				if (pDoc->baduk[row - 1][col] == d);			//4�� �ִ��� üũ ����.
				else if (pDoc->baduk[row - 1][col] == o) {			//  *x-   ����
					if (pDoc->baduk[row - 2][col] == d);
					else if (pDoc->baduk[row - 2][col] == o) {			//   **x- ����
						if (pDoc->baduk[row - 3][col] == d);
						else if (pDoc->baduk[row - 3][col] == o) {			// ***x- �ϼ�
							if (pDoc->baduk[row - 4][col] == d);
							else if (pDoc->baduk[row - 4][col] == o);
							else if (pDoc->baduk[row - 4][col] == 0) {
								if (pDoc->baduk[row - 5][col] != o) four_by_three_flag++;
							}
						}
						else if (pDoc->baduk[row - 3][col] == 0) {			// ? **x-
							if (pDoc->baduk[row - 4][col] == d);
							else if (pDoc->baduk[row - 4][col] == o) {
								if (pDoc->baduk[row - 5][col] != o) four_by_three_flag++;
							}
							else if (pDoc->baduk[row - 4][col] == 0);
						}
					}
					else if (pDoc->baduk[row - 2][col] == 0) {		//  ? *x-
						if (pDoc->baduk[row - 3][col] == d);
						else if (pDoc->baduk[row - 3][col] == o) {		//   * *x-
							if (pDoc->baduk[row - 4][col] == d);
							else if (pDoc->baduk[row - 4][col] == o) {
								if (pDoc->baduk[row - 5][col] != o) four_by_three_flag++;
							}
							else if (pDoc->baduk[row - 4][col] == 0);
						}
						else if (pDoc->baduk[row - 3][col] == 0);
					}
				}
				else if (pDoc->baduk[row - 1][col] == 0) {		//	? x-
					if (pDoc->baduk[row - 2][col] == o) {
						if (pDoc->baduk[row - 3][col] == o) {		// ** x-
							if (pDoc->baduk[row - 4][col] == o) {
								if (pDoc->baduk[row - 5][col] != o) four_by_three_flag++;
							}
						}
					}
				}
			}
			else if (pDoc->baduk[row + 1][col] == o) {			//�� ��ġ ���� ������ üũ x*?
				if (pDoc->baduk[row + 2][col] == d) {		//	  x*-
					if (pDoc->baduk[row - 1][col] == d);
					else if (pDoc->baduk[row - 1][col] == o) {	// *x*-
						if (pDoc->baduk[row - 2][col] == d);
						else if (pDoc->baduk[row - 2][col] == o) {	// **x*-
							if (pDoc->baduk[row - 3][col] == d);
							else if (pDoc->baduk[row - 3][col] == o);
							else if (pDoc->baduk[row - 3][col] == 0) {
								if (pDoc->baduk[row - 4][col] != o) four_by_three_flag++;
							}
						}
						else if (pDoc->baduk[row - 2][col] == 0) {		// ? *x*-
							if (pDoc->baduk[row - 3][col] == d);
							else if (pDoc->baduk[row - 3][col] == o) {
								if (pDoc->baduk[row - 4][col] != o) four_by_three_flag++;
							}
							else if (pDoc->baduk[row - 3][col] == 0);
						}
					}
					else if (pDoc->baduk[row - 1][col] == 0) {	// ? x*-
						if (pDoc->baduk[row - 2][col] == o) {
							if (pDoc->baduk[row - 3][col] == o) {
								if (pDoc->baduk[row - 4][col] != o) four_by_three_flag++;
							}
						}
					}
				}
				else if (pDoc->baduk[row + 2][col] == o) {			//x** ����
					if (pDoc->baduk[row + 3][col] == d) {			//x**-
						if (pDoc->baduk[row - 1][col] == d);
						else if (pDoc->baduk[row - 1][col] == o) {
							if (pDoc->baduk[row - 2][col] == d);
							else if (pDoc->baduk[row - 2][col] == o);
							else if (pDoc->baduk[row - 2][col] == 0) {
								if (pDoc->baduk[row - 3][col] != o) four_by_three_flag++;
							}
						}
						else if (pDoc->baduk[row - 1][col] == 0) {
							if (pDoc->baduk[row - 2][col] == o) {
								if (pDoc->baduk[row - 3][col] != o) four_by_three_flag++;
							}
						}
					}
					else if (pDoc->baduk[row + 3][col] == o) {			// x***
						if (pDoc->baduk[row + 4][col] == d) {
							if (pDoc->baduk[row - 1][col] == d);
							else if (pDoc->baduk[row - 1][col] == o);
							else if (pDoc->baduk[row - 1][col] == 0) {
								if (pDoc->baduk[row - 1][col] != o) four_by_three_flag++;
							}
						}
						else if (pDoc->baduk[row + 4][col] == o);
						else if (pDoc->baduk[row + 4][col] == 0) four_by_three_flag++;
					}
					else if (pDoc->baduk[row + 3][col] == 0) {
						if (pDoc->baduk[row + 4][col] == d || pDoc->baduk[row + 4][col] == 0) {
							if (pDoc->baduk[row - 1][col] == d);
							else if (pDoc->baduk[row - 1][col] == o)four_by_three_flag++;
							else if (pDoc->baduk[row - 1][col] == 0) {
								if (pDoc->baduk[row - 2][col] == d) {
									if (pDoc->baduk[row + 4][col] == 0) three_by_three_flag++; // �� ������ ���� ���ɼ� üũ
								}
								else if (pDoc->baduk[row - 2][col] == o)four_by_three_flag++;
								else if (pDoc->baduk[row - 2][col] == 0)three_by_three_flag++; // x**���� �Ϸ�
							}
						}
						else if (pDoc->baduk[row + 4][col] == o)four_by_three_flag++;
					}
				}
				else if (pDoc->baduk[row + 2][col] == 0) {		//�� ��ġ���� ������ x* ?
					if (pDoc->baduk[row + 3][col] == d || pDoc->baduk[row + 3][col] == 0) {		//x*   ����
						if (pDoc->baduk[row - 1][col] == d);
						else if (pDoc->baduk[row - 1][col] == o) {		// *x*
							if (pDoc->baduk[row - 2][col] == d);
							else if (pDoc->baduk[row - 2][col] == o) four_by_three_flag++;
							else if (pDoc->baduk[row - 2][col] == 0) {
								if (pDoc->baduk[row - 3][col] == d) {
									if (pDoc->baduk[row + 3][col] == 0)	three_by_three_flag++;
								}
								else if (pDoc->baduk[row - 3][col] == o) four_by_three_flag++;
								else if (pDoc->baduk[row - 3][col] == 0) three_by_three_flag++;
							}
						}
						else if (pDoc->baduk[row - 1][col] == 0) {		// ? x*
							if (pDoc->baduk[row - 2][col] == d);
							else if (pDoc->baduk[row - 2][col] == o) {		// * x*
								if (pDoc->baduk[row - 3][col] == d);
								else if (pDoc->baduk[row - 3][col] == o) four_by_three_flag++;
								else if (pDoc->baduk[row - 3][col] == 0) {
									if (pDoc->baduk[row - 4][col] == d) three_by_three_flag++;
									else if (pDoc->baduk[row - 4][col] == o);
									else if (pDoc->baduk[row - 4][col] == 0) three_by_three_flag++;
								}
							}
							else if (pDoc->baduk[row - 2][col] == 0);
						}
					}
					else if (pDoc->baduk[row + 3][col] == o) {		//x* *
						if (pDoc->baduk[row + 4][col] == d) {
							if (pDoc->baduk[row - 1][col] == o) {
								if (pDoc->baduk[row - 2][col] != o) four_by_three_flag++;
							}
						}
						else if (pDoc->baduk[row + 4][col] == o) four_by_three_flag++;
						else if (pDoc->baduk[row + 4][col] == 0) {
							if (pDoc->baduk[row - 1][col] == d);
							else if (pDoc->baduk[row - 1][col] == o) {
								if (pDoc->baduk[row - 1][col] != o) four_by_three_flag++;
							}
							else if (pDoc->baduk[row - 1][col] == 0) {
								if (pDoc->baduk[row - 2][col] == d) three_by_three_flag++;
								else if (pDoc->baduk[row - 2][col] == o);
								else if (pDoc->baduk[row - 2][col] == 0) three_by_three_flag++;
							}
						}
					}
				}
			}
			else if (pDoc->baduk[row + 1][col] == 0) {			//x ? ����.
				if (pDoc->baduk[row + 2][col] == d || pDoc->baduk[row + 2][col] == 0) {		//   x ���� �˻� ����.
					if (pDoc->baduk[row - 1][col] == d);
					else if (pDoc->baduk[row - 1][col] == o) {				//   *x ����.
						if (pDoc->baduk[row - 2][col] == d);
						else if (pDoc->baduk[row - 2][col] == o) {				//   **x
							if (pDoc->baduk[row - 3][col] == d);
							else if (pDoc->baduk[row - 3][col] == o) four_by_three_flag++;
							else if (pDoc->baduk[row - 3][col] == 0) {
								if (pDoc->baduk[row - 4][col] == d) {
									if (pDoc->baduk[row + 2][col] == 0) three_by_three_flag++;
								}
								else if (pDoc->baduk[row - 4][col] == o) four_by_three_flag++;
								else if (pDoc->baduk[row - 4][col] == 0) three_by_three_flag++;
							}
						}
						else if (pDoc->baduk[row - 2][col] == 0) {			// ? *x
							if (pDoc->baduk[row - 3][col] == d);
							else if (pDoc->baduk[row - 3][col] == o) {			// * *x
								if (pDoc->baduk[row - 4][col] == d);
								else if (pDoc->baduk[row - 4][col] == o) four_by_three_flag++;
								else if (pDoc->baduk[row - 4][col] == 0) three_by_three_flag++;
							}
							else if (pDoc->baduk[row - 3][col] == 0);
						}
					}
					else if (pDoc->baduk[row - 1][col] == 0) {		// ? x ����
						if (pDoc->baduk[row - 2][col] == d);
						else if (pDoc->baduk[row - 2][col] == o) {		// * x
							if (pDoc->baduk[row - 3][col] == d);
							else if (pDoc->baduk[row - 3][col] == o) {		// ** x
								if (pDoc->baduk[row - 4][col] == d);
								else if (pDoc->baduk[row - 4][col] == o) four_by_three_flag++;
								else if (pDoc->baduk[row - 4][col] == 0) {
									if (pDoc->baduk[row - 5][col] == d) three_by_three_flag++;
									else if (pDoc->baduk[row - 5][col] == o);
									else if (pDoc->baduk[row - 5][col] == 0) three_by_three_flag++;
								}
							}
							else if (pDoc->baduk[row - 3][col] == 0);
						}
					}
				}
				else if (pDoc->baduk[row + 2][col] == o) {		// x *
					if (pDoc->baduk[row + 3][col] == d);
					else if (pDoc->baduk[row + 3][col] == o) {		// x **
						if (pDoc->baduk[row + 4][col] == d);
						else if (pDoc->baduk[row + 4][col] == o) four_by_three_flag++;
						else if (pDoc->baduk[row + 4][col] == 0) {
							if (pDoc->baduk[row + 5][col] == d || pDoc->baduk[row + 5][col] == 0) {
								if (pDoc->baduk[row - 1][col] == d);
								else if (pDoc->baduk[row - 1][col] == o) four_by_three_flag++;
								else if (pDoc->baduk[row - 1][col] == 0) {
									if (pDoc->baduk[row - 2][col] == d);
									else if (pDoc->baduk[row - 2][col] == o);
									else if (pDoc->baduk[row - 2][col] == 0) three_by_three_flag++;
								}
							}
							else if (pDoc->baduk[row + 5][col] == o);
						}
					}
					else if (pDoc->baduk[row + 3][col] == 0) {		// x *  ����
						if (pDoc->baduk[row + 4][col] == d || pDoc->baduk[row + 4][col] == 0) {
							if (pDoc->baduk[row - 1][col] == d);
							else if (pDoc->baduk[row - 1][col] == o) {		// *x * ����
								if (pDoc->baduk[row - 2][col] == d);
								else if (pDoc->baduk[row - 2][col] == o) four_by_three_flag++;
								else if (pDoc->baduk[row - 2][col] == 0) three_by_three_flag++;
							}
							else if (pDoc->baduk[row - 1][col] == 0);
						}
						else if (pDoc->baduk[row + 4][col] == o);
					}
				}
			}

			// ====================== ������ üũ �� ====================== //



			//==============�� ��ġ�� �߽����� 33 ���� �� üũ===============//

			if (pDoc->baduk[row][col + 1] == d);			//�� ��ġ���� ������ üũ x?
			else if (pDoc->baduk[row][col + 1] == o) {			//�� ��ġ ���� ������ üũ x*?
				if (pDoc->baduk[row][col + 2] == d);
				else if (pDoc->baduk[row][col + 2] == o) {			//x** ����
					if (pDoc->baduk[row][col + 3] == d);
					else if (pDoc->baduk[row][col + 3] == o) four_by_three_flag++;
					else if (pDoc->baduk[row][col + 3] == 0) {
						if (pDoc->baduk[row][col + 4] == d || pDoc->baduk[row][col + 4] == 0) {
							if (pDoc->baduk[row][col - 1] == d);
							else if (pDoc->baduk[row][col - 1] == o) four_by_three_flag++;
							else if (pDoc->baduk[row][col - 1] == 0) {
								if (pDoc->baduk[row][col - 2] == d) {
									if (pDoc->baduk[row][col + 4] == 0) three_by_three_flag++; // �� ������ ���� ���ɼ� üũ
								}
								else if (pDoc->baduk[row][col - 2] == o) four_by_three_flag++;
								else if (pDoc->baduk[row][col - 2] == 0)three_by_three_flag++; // x**���� �Ϸ�
							}
						}
						else if (pDoc->baduk[row][col + 4] == o) four_by_three_flag++;
					}
				}
				else if (pDoc->baduk[row][col + 2] == 0) {		//�� ��ġ���� ������ x* ?
					if (pDoc->baduk[row][col + 3] == d || pDoc->baduk[row][col + 3] == 0) {		//x*   ����
						if (pDoc->baduk[row][col - 1] == d);
						else if (pDoc->baduk[row][col - 1] == o) {		// *x*
							if (pDoc->baduk[row][col - 2] == d);
							else if (pDoc->baduk[row][col - 2] == o) four_by_three_flag++;
							else if (pDoc->baduk[row][col - 2] == 0) {
								if (pDoc->baduk[row][col - 3] == d) {
									if (pDoc->baduk[row][col + 3] == 0)	three_by_three_flag++;
								}
								else if (pDoc->baduk[row][col - 3] == o) four_by_three_flag++;
								else if (pDoc->baduk[row][col - 3] == 0) three_by_three_flag++;
							}
						}
						else if (pDoc->baduk[row][col - 1] == 0) {		// ? x*
							if (pDoc->baduk[row][col - 2] == d);
							else if (pDoc->baduk[row][col - 2] == o) {		// * x*
								if (pDoc->baduk[row][col - 3] == d);
								else if (pDoc->baduk[row][col - 3] == o) four_by_three_flag++;
								else if (pDoc->baduk[row][col - 3] == 0) {
									if (pDoc->baduk[row][col - 4] == d) three_by_three_flag++;
									else if (pDoc->baduk[row][col - 4] == o);
									else if (pDoc->baduk[row][col - 4] == 0) three_by_three_flag++;
								}
							}
							else if (pDoc->baduk[row][col - 2] == 0);
						}
					}
					else if (pDoc->baduk[row][col + 3] == o) {		//x* *
						if (pDoc->baduk[row][col + 4] == d);
						else if (pDoc->baduk[row][col + 4] == o) four_by_three_flag++;
						else if (pDoc->baduk[row][col + 4] == 0) {
							if (pDoc->baduk[row][col - 1] == d);
							else if (pDoc->baduk[row][col - 1] == o) four_by_three_flag++;
							else if (pDoc->baduk[row][col - 1] == 0) {
								if (pDoc->baduk[row][col - 2] == d) three_by_three_flag++;
								else if (pDoc->baduk[row][col - 2] == o);
								else if (pDoc->baduk[row][col - 2] == 0) three_by_three_flag++;
							}
						}
					}
				}
			}
			else if (pDoc->baduk[row][col + 1] == 0) {			//x ? ����.
				if (pDoc->baduk[row][col + 2] == d || pDoc->baduk[row][col + 2] == 0) {		//   x ���� �˻� ����.
					if (pDoc->baduk[row][col - 1] == d);
					else if (pDoc->baduk[row][col - 1] == o) {				//   *x ����.
						if (pDoc->baduk[row][col - 2] == d);
						else if (pDoc->baduk[row][col - 2] == o) {				//   **x
							if (pDoc->baduk[row][col - 3] == d);
							else if (pDoc->baduk[row][col - 3] == o) four_by_three_flag++;
							else if (pDoc->baduk[row][col - 3] == 0) {
								if (pDoc->baduk[row][col - 4] == d) {
									if (pDoc->baduk[row][col + 2] == 0) three_by_three_flag++;
								}
								else if (pDoc->baduk[row][col - 4] == o) four_by_three_flag++;
								else if (pDoc->baduk[row][col - 4] == 0) three_by_three_flag++;
							}
						}
						else if (pDoc->baduk[row][col - 2] == 0) {			// ? *x
							if (pDoc->baduk[row][col - 3] == d);
							else if (pDoc->baduk[row][col - 3] == o) {			// * *x
								if (pDoc->baduk[row][col - 4] == d);
								else if (pDoc->baduk[row][col - 4] == o) four_by_three_flag++;
								else if (pDoc->baduk[row][col - 4] == 0) three_by_three_flag++;
							}
							else if (pDoc->baduk[row][col - 3] == 0);
						}
					}
					else if (pDoc->baduk[row][col - 1] == 0) {		// ? x ����
						if (pDoc->baduk[row][col - 2] == d);
						else if (pDoc->baduk[row][col - 2] == o) {		// * x
							if (pDoc->baduk[row][col - 3] == d);
							else if (pDoc->baduk[row][col - 3] == o) {		// ** x
								if (pDoc->baduk[row][col - 4] == d);
								else if (pDoc->baduk[row][col - 4] == o) four_by_three_flag++;
								else if (pDoc->baduk[row][col - 4] == 0) {
									if (pDoc->baduk[row][col - 5] == d) three_by_three_flag++;
									else if (pDoc->baduk[row][col - 5] == o);
									else if (pDoc->baduk[row][col - 5] == 0) three_by_three_flag++;
								}
							}
							else if (pDoc->baduk[row][col - 3] == 0);
						}
					}
				}
				else if (pDoc->baduk[row][col + 2] == o) {		// x *
					if (pDoc->baduk[row][col + 3] == d);
					else if (pDoc->baduk[row][col + 3] == o) {		// x **
						if (pDoc->baduk[row][col + 4] == d);
						else if (pDoc->baduk[row][col + 4] == o) four_by_three_flag++;
						else if (pDoc->baduk[row][col + 4] == 0) {
							if (pDoc->baduk[row][col + 5] == d || pDoc->baduk[row][col + 5] == 0) {
								if (pDoc->baduk[row][col - 1] == d);
								else if (pDoc->baduk[row][col - 1] == o) four_by_three_flag++;
								else if (pDoc->baduk[row][col - 1] == 0) {
									if (pDoc->baduk[row][col - 2] == d);
									else if (pDoc->baduk[row][col - 2] == o);
									else if (pDoc->baduk[row][col - 2] == 0) three_by_three_flag++;
								}
							}
							else if (pDoc->baduk[row][col + 5] == o);
						}
					}
					else if (pDoc->baduk[row][col + 3] == 0) {		// x *  ����
						if (pDoc->baduk[row][col + 4] == d || pDoc->baduk[row][col + 4] == 0) {
							if (pDoc->baduk[row][col - 1] == d);
							else if (pDoc->baduk[row][col - 1] == o) {		// *x * ����
								if (pDoc->baduk[row][col - 2] == d);
								else if (pDoc->baduk[row][col - 2] == o) four_by_three_flag++;
								else if (pDoc->baduk[row][col - 2] == 0) three_by_three_flag++;
							}
							else if (pDoc->baduk[row][col - 1] == 0);
						}
						else if (pDoc->baduk[row][col + 4] == o);
					}
				}
			}

			// ====================== ������ üũ �� ====================== //




			//==============�� ��ġ�� �߽����� �»� --> ���� �밢�� �� üũ===============//

			if (pDoc->baduk[row + 1][col + 1] == d);			//�� ��ġ���� ������ üũ x?
			else if (pDoc->baduk[row + 1][col + 1] == o) {			//�� ��ġ ���� ������ üũ x*?
				if (pDoc->baduk[row + 2][col + 2] == d);
				else if (pDoc->baduk[row + 2][col + 2] == o) {			//x** ����
					if (pDoc->baduk[row + 3][col + 3] == d);
					else if (pDoc->baduk[row + 3][col + 3] == o) four_by_three_flag++;
					else if (pDoc->baduk[row + 3][col + 3] == 0) {
						if (pDoc->baduk[row + 4][col + 4] == d || pDoc->baduk[row + 4][col + 4] == 0) {
							if (pDoc->baduk[row - 1][col - 1] == d);
							else if (pDoc->baduk[row - 1][col - 1] == o) four_by_three_flag++;
							else if (pDoc->baduk[row - 1][col - 1] == 0) {
								if (pDoc->baduk[row - 2][col - 2] == d) {
									if (pDoc->baduk[row + 4][col + 4] == 0) three_by_three_flag++; // �� ������ ���� ���ɼ� üũ
								}
								else if (pDoc->baduk[row - 2][col - 2] == o) four_by_three_flag++;
								else if (pDoc->baduk[row - 2][col - 2] == 0) three_by_three_flag++; // x**���� �Ϸ�
							}
						}
						else if (pDoc->baduk[row + 4][col + 4] == o) four_by_three_flag++;
					}
				}
				else if (pDoc->baduk[row + 2][col + 2] == 0) {		//�� ��ġ���� ������ x* ?
					if (pDoc->baduk[row + 3][col + 3] == d || pDoc->baduk[row + 3][col + 3] == 0) {		//x*   ����
						if (pDoc->baduk[row - 1][col - 1] == d);
						else if (pDoc->baduk[row - 1][col - 1] == o) {		// *x*
							if (pDoc->baduk[row - 2][col - 2] == d);
							else if (pDoc->baduk[row - 2][col - 2] == o) four_by_three_flag++;
							else if (pDoc->baduk[row - 2][col - 2] == 0) {
								if (pDoc->baduk[row - 3][col - 3] == d) {
									if (pDoc->baduk[row + 3][col + 3] == 0)	three_by_three_flag++;
								}
								else if (pDoc->baduk[row - 3][col - 3] == o) four_by_three_flag++;
								else if (pDoc->baduk[row - 3][col - 3] == 0) three_by_three_flag++;
							}
						}
						else if (pDoc->baduk[row - 1][col - 1] == 0) {		// ? x*
							if (pDoc->baduk[row - 2][col - 2] == d);
							else if (pDoc->baduk[row - 2][col - 2] == o) {		// * x*
								if (pDoc->baduk[row - 3][col - 3] == d);
								else if (pDoc->baduk[row - 3][col - 3] == o) four_by_three_flag++;
								else if (pDoc->baduk[row - 3][col - 3] == 0) {
									if (pDoc->baduk[row - 4][col - 4] == d) three_by_three_flag++;
									else if (pDoc->baduk[row - 4][col - 4] == o);
									else if (pDoc->baduk[row - 4][col - 4] == 0) three_by_three_flag++;
								}
							}
							else if (pDoc->baduk[row - 2][col - 2] == 0);
						}
					}
					else if (pDoc->baduk[row + 3][col + 3] == o) {		//x* *
						if (pDoc->baduk[row + 4][col + 4] == d);
						else if (pDoc->baduk[row + 4][col + 4] == o) four_by_three_flag++;
						else if (pDoc->baduk[row + 4][col + 4] == 0) {
							if (pDoc->baduk[row - 1][col - 1] == d);
							else if (pDoc->baduk[row - 1][col - 1] == o) four_by_three_flag++;
							else if (pDoc->baduk[row - 1][col - 1] == 0) {
								if (pDoc->baduk[row - 2][col - 2] == d) three_by_three_flag++;
								else if (pDoc->baduk[row - 2][col - 2] == o);
								else if (pDoc->baduk[row - 2][col - 2] == 0) three_by_three_flag++;
							}
						}
					}
				}
			}
			else if (pDoc->baduk[row + 1][col + 1] == 0) {			//x ? ����.
				if (pDoc->baduk[row + 2][col + 2] == d || pDoc->baduk[row + 2][col + 2] == 0) {		//   x ���� �˻� ����.
					if (pDoc->baduk[row - 1][col - 1] == d);
					else if (pDoc->baduk[row - 1][col - 1] == o) {				//   *x ����.
						if (pDoc->baduk[row - 2][col - 2] == d);
						else if (pDoc->baduk[row - 2][col - 2] == o) {				//   **x
							if (pDoc->baduk[row - 3][col - 3] == d);
							else if (pDoc->baduk[row - 3][col - 3] == o) four_by_three_flag++;
							else if (pDoc->baduk[row - 3][col - 3] == 0) {
								if (pDoc->baduk[row - 4][col - 4] == d) {
									if (pDoc->baduk[row + 2][col + 2] == 0) three_by_three_flag++;
								}
								else if (pDoc->baduk[row - 4][col - 4] == o) four_by_three_flag++;
								else if (pDoc->baduk[row - 4][col - 4] == 0) three_by_three_flag++;
							}
						}
						else if (pDoc->baduk[row - 2][col - 2] == 0) {			// ? *x
							if (pDoc->baduk[row - 3][col - 3] == d);
							else if (pDoc->baduk[row - 3][col - 3] == o) {			// * *x
								if (pDoc->baduk[row - 4][col - 4] == d);
								else if (pDoc->baduk[row - 4][col - 4] == o) four_by_three_flag++;
								else if (pDoc->baduk[row - 4][col - 4] == 0) three_by_three_flag++;
							}
							else if (pDoc->baduk[row - 3][col - 3] == 0);
						}
					}
					else if (pDoc->baduk[row - 1][col - 1] == 0) {		// ? x ����
						if (pDoc->baduk[row - 2][col - 2] == d);
						else if (pDoc->baduk[row - 2][col - 2] == o) {		// * x
							if (pDoc->baduk[row - 3][col - 3] == d);
							else if (pDoc->baduk[row - 3][col - 3] == o) {		// ** x
								if (pDoc->baduk[row - 4][col - 4] == d);
								else if (pDoc->baduk[row - 4][col - 4] == o) four_by_three_flag++;
								else if (pDoc->baduk[row - 4][col - 4] == 0) {
									if (pDoc->baduk[row - 5][col - 5] == d) three_by_three_flag++;
									else if (pDoc->baduk[row - 5][col - 5] == o);
									else if (pDoc->baduk[row - 5][col - 5] == 0) three_by_three_flag++;
								}
							}
							else if (pDoc->baduk[row - 3][col - 3] == 0);
						}
					}
				}
				else if (pDoc->baduk[row + 2][col + 2] == o) {		// x *
					if (pDoc->baduk[row + 3][col + 3] == d);
					else if (pDoc->baduk[row + 3][col + 3] == o) {		// x **
						if (pDoc->baduk[row + 4][col + 4] == d);
						else if (pDoc->baduk[row + 4][col + 4] == o) four_by_three_flag++;
						else if (pDoc->baduk[row + 4][col + 4] == 0) {
							if (pDoc->baduk[row + 5][col + 5] == d || pDoc->baduk[row + 5][col + 5] == 0) {
								if (pDoc->baduk[row - 1][col - 1] == d);
								else if (pDoc->baduk[row - 1][col - 1] == o) four_by_three_flag++;
								else if (pDoc->baduk[row - 1][col - 1] == 0) {
									if (pDoc->baduk[row - 2][col - 2] == d);
									else if (pDoc->baduk[row - 2][col - 2] == o);
									else if (pDoc->baduk[row - 2][col - 2] == 0) three_by_three_flag++;
								}
							}
							else if (pDoc->baduk[row + 5][col + 5] == o);
						}
					}
					else if (pDoc->baduk[row + 3][col + 3] == 0) {		// x *  ����
						if (pDoc->baduk[row + 4][col + 4] == d || pDoc->baduk[row + 4][col + 4] == 0) {
							if (pDoc->baduk[row - 1][col - 1] == d);
							else if (pDoc->baduk[row - 1][col - 1] == o) {		// *x * ����
								if (pDoc->baduk[row - 2][col - 2] == d);
								else if (pDoc->baduk[row - 2][col - 2] == o) four_by_three_flag++;
								else if (pDoc->baduk[row - 2][col - 2] == 0) three_by_three_flag++;
							}
							else if (pDoc->baduk[row - 1][col - 1] == 0);
						}
						else if (pDoc->baduk[row + 4][col + 4] == o);
					}
				}
			}

			// ====================== �»� ���� �밢�� üũ �� ====================== //




			//==============�� ��ġ�� �߽����� ��� --> ���� �밢�� �� üũ===============//

			if (pDoc->baduk[row + 1][col - 1] == d);			//�� ��ġ���� ������ üũ x?
			else if (pDoc->baduk[row + 1][col - 1] == o) {			//�� ��ġ ���� ������ üũ x*?
				if (pDoc->baduk[row + 2][col - 2] == d);
				else if (pDoc->baduk[row + 2][col - 2] == o) {			//x** ����
					if (pDoc->baduk[row + 3][col - 3] == d);
					else if (pDoc->baduk[row + 3][col - 3] == o) four_by_three_flag++;
					else if (pDoc->baduk[row + 3][col - 3] == 0) {
						if (pDoc->baduk[row + 4][col - 4] == d || pDoc->baduk[row + 4][col - 4] == 0) {
							if (pDoc->baduk[row - 1][col + 1] == d);
							else if (pDoc->baduk[row - 1][col + 1] == o) four_by_three_flag++;
							else if (pDoc->baduk[row - 1][col + 1] == 0) {
								if (pDoc->baduk[row - 2][col + 2] == d) {
									if (pDoc->baduk[row + 4][col - 4] == 0) three_by_three_flag++; // �� ������ ���� ���ɼ� üũ
								}
								else if (pDoc->baduk[row - 2][col + 2] == o) four_by_three_flag++;
								else if (pDoc->baduk[row - 2][col + 2] == 0) three_by_three_flag++; // x**���� �Ϸ�
							}
						}
						else if (pDoc->baduk[row + 4][col - 4] == o) four_by_three_flag++;
					}
				}
				else if (pDoc->baduk[row + 2][col - 2] == 0) {		//�� ��ġ���� ������ x* ?
					if (pDoc->baduk[row + 3][col - 3] == d || pDoc->baduk[row + 3][col - 3] == 0) {		//x*   ����
						if (pDoc->baduk[row - 1][col + 1] == d);
						else if (pDoc->baduk[row - 1][col + 1] == o) {		// *x*
							if (pDoc->baduk[row - 2][col + 2] == d);
							else if (pDoc->baduk[row - 2][col + 2] == o) four_by_three_flag++;
							else if (pDoc->baduk[row - 2][col + 2] == 0) {
								if (pDoc->baduk[row - 3][col + 3] == d) {
									if (pDoc->baduk[row + 3][col - 3] == 0)	three_by_three_flag++;
								}
								else if (pDoc->baduk[row - 3][col + 3] == o) four_by_three_flag++;
								else if (pDoc->baduk[row - 3][col + 3] == 0) three_by_three_flag++;
							}
						}
						else if (pDoc->baduk[row - 1][col + 1] == 0) {		// ? x*
							if (pDoc->baduk[row - 2][col + 2] == d);
							else if (pDoc->baduk[row - 2][col + 2] == o) {		// * x*
								if (pDoc->baduk[row - 3][col + 3] == d);
								else if (pDoc->baduk[row - 3][col + 3] == o) four_by_three_flag++;
								else if (pDoc->baduk[row - 3][col + 3] == 0) {
									if (pDoc->baduk[row - 4][col + 4] == d) three_by_three_flag++;
									else if (pDoc->baduk[row - 4][col + 4] == o);
									else if (pDoc->baduk[row - 4][col + 4] == 0) three_by_three_flag++;
								}
							}
							else if (pDoc->baduk[row - 2][col + 2] == 0);
						}
					}
					else if (pDoc->baduk[row + 3][col - 3] == o) {		//x* *
						if (pDoc->baduk[row + 4][col - 4] == d);
						else if (pDoc->baduk[row + 4][col - 4] == o) four_by_three_flag++;
						else if (pDoc->baduk[row + 4][col - 4] == 0) {
							if (pDoc->baduk[row - 1][col + 1] == d);
							else if (pDoc->baduk[row - 1][col + 1] == o) four_by_three_flag++;
							else if (pDoc->baduk[row - 1][col + 1] == 0) {
								if (pDoc->baduk[row - 2][col + 2] == d) three_by_three_flag++;
								else if (pDoc->baduk[row - 2][col + 2] == o);
								else if (pDoc->baduk[row - 2][col + 2] == 0) three_by_three_flag++;
							}
						}
					}
				}
			}
			else if (pDoc->baduk[row + 1][col - 1] == 0) {			//x ? ����.
				if (pDoc->baduk[row + 2][col - 2] == d || pDoc->baduk[row + 2][col - 2] == 0) {		//   x ���� �˻� ����.
					if (pDoc->baduk[row - 1][col + 1] == d);
					else if (pDoc->baduk[row - 1][col + 1] == o) {				//   *x ����.
						if (pDoc->baduk[row - 2][col + 2] == d);
						else if (pDoc->baduk[row - 2][col + 2] == o) {				//   **x
							if (pDoc->baduk[row - 3][col + 3] == d);
							else if (pDoc->baduk[row - 3][col + 3] == o) four_by_three_flag++;
							else if (pDoc->baduk[row - 3][col + 3] == 0) {
								if (pDoc->baduk[row - 4][col + 4] == d) {
									if (pDoc->baduk[row + 2][col - 2] == 0) three_by_three_flag++;
								}
								else if (pDoc->baduk[row - 4][col + 4] == o) four_by_three_flag++;
								else if (pDoc->baduk[row - 4][col + 4] == 0) three_by_three_flag++;
							}
						}
						else if (pDoc->baduk[row - 2][col + 2] == 0) {			// ? *x
							if (pDoc->baduk[row - 3][col + 3] == d);
							else if (pDoc->baduk[row - 3][col + 3] == o) {			// * *x
								if (pDoc->baduk[row - 4][col + 4] == d);
								else if (pDoc->baduk[row - 4][col + 4] == o) four_by_three_flag++;
								else if (pDoc->baduk[row - 4][col + 4] == 0) three_by_three_flag++;
							}
							else if (pDoc->baduk[row - 3][col + 3] == 0);
						}
					}
					else if (pDoc->baduk[row - 1][col + 1] == 0) {		// ? x ����
						if (pDoc->baduk[row - 2][col + 2] == d);
						else if (pDoc->baduk[row - 2][col + 2] == o) {		// * x
							if (pDoc->baduk[row - 3][col + 3] == d);
							else if (pDoc->baduk[row - 3][col + 3] == o) {		// ** x
								if (pDoc->baduk[row - 4][col + 4] == d);
								else if (pDoc->baduk[row - 4][col + 4] == o) four_by_three_flag++;
								else if (pDoc->baduk[row - 4][col + 4] == 0) {
									if (pDoc->baduk[row - 5][col + 5] == d) three_by_three_flag++;
									else if (pDoc->baduk[row - 5][col + 5] == o);
									else if (pDoc->baduk[row - 5][col + 5] == 0) three_by_three_flag++;
								}
							}
							else if (pDoc->baduk[row - 3][col + 3] == 0);
						}
					}
				}
				else if (pDoc->baduk[row + 2][col - 2] == o) {		// x *
					if (pDoc->baduk[row + 3][col - 3] == d);
					else if (pDoc->baduk[row + 3][col - 3] == o) {		// x **
						if (pDoc->baduk[row + 4][col - 4] == d);
						else if (pDoc->baduk[row + 4][col - 4] == o) four_by_three_flag++;
						else if (pDoc->baduk[row + 4][col - 4] == 0) {
							if (pDoc->baduk[row + 5][col - 5] == d || pDoc->baduk[row + 5][col - 5] == 0) {
								if (pDoc->baduk[row - 1][col + 1] == d);
								else if (pDoc->baduk[row - 1][col + 1] == o) four_by_three_flag++;
								else if (pDoc->baduk[row - 1][col + 1] == 0) {
									if (pDoc->baduk[row - 2][col + 2] == d);
									else if (pDoc->baduk[row - 2][col + 2] == o);
									else if (pDoc->baduk[row - 2][col + 2] == 0) three_by_three_flag++;
								}
							}
							else if (pDoc->baduk[row + 5][col - 5] == o);
						}
					}
					else if (pDoc->baduk[row + 3][col - 3] == 0) {		// x *  ����
						if (pDoc->baduk[row + 4][col - 4] == d || pDoc->baduk[row + 4][col - 4] == 0) {
							if (pDoc->baduk[row - 1][col + 1] == d);
							else if (pDoc->baduk[row - 1][col + 1] == o) {		// *x * ����
								if (pDoc->baduk[row - 2][col + 2] == d);
								else if (pDoc->baduk[row - 2][col + 2] == o) four_by_three_flag++;
								else if (pDoc->baduk[row - 2][col + 2] == 0) three_by_three_flag++;
							}
							else if (pDoc->baduk[row - 1][col + 1] == 0);
						}
						else if (pDoc->baduk[row + 4][col - 4] == o);
					}
				}
			}

			// ====================== ��� ���� �밢�� üũ �� ====================== //



			// 33 ��

			if (four_by_three_flag >= 1 && three_by_three_flag == 1) {
				ibaduk[row][col] += d_four_three;
				dbaduk[row][col] += d_four_three;
			}

			/*
			if (three_by_three_flag >= 2) {
				ibaduk[row][col] += -10000;
			}
			*/
			three_by_three_flag = 0;
			four_by_three_flag = 0;


		}
	}

}

void CMFCApplication3View::OffendWeight3(int o, int d) { //2���� ���� ����������
	CMFCApplication3Doc* pDoc = GetDocument();
	int i;
	int check_vertical = 0; // ���ι��� üũ ����
	int check_beside_vertical = 0; //  ���ι��� üũ ����
	int check_horizontal = 0; // ���ι��� üũ ����
	int check_beside_horizontal = 0; // ���ι��� üũ ����
	int check_diagonal = 0;  // �Ϲݴ밢���� ���
	int check_beside_diagonal = 0; // �Ϲݴ밢���� ���
	int check_reverse_diagonal = 0; //�Ϲݴ밢���� �ݴ� ���
	int check_reverse_beside_diagonal = 0; // �Ϲ� �밢���� �ݴ� ���
	int row, col;

	int defend_three_point[8]; //4���� ĭ�� �������� ���� 

	int defend_one_point[8];  //1���� ĭ�� �������� ����

							  /* �迭�����Ͽ�
							  0 : beside_horizontal
							  1 : horizontal
							  2 : beside_vertical
							  3 : vertical
							  4 : diagonal
							  5 : beside_diagonal
							  6 : reverse_diagonal
							  7 : reverse_beside_diagonal
							  */
							  /* ====================================================================================

							  �����ҵ��� *������* �϶� *�� ����ġ

							  =====================================================================================*/
	for (row = 0; row < 19; row++)
		for (col = 0; col < 19; col++) {
			check_vertical = 0; //  ���ι��� üũ ����
			check_beside_vertical = 0; //  ���ι��� üũ ����
			check_horizontal = 0; // ���ι��� üũ ����
			check_beside_horizontal = 0; // ���ι��� üũ ����
			check_diagonal = 0;  // �Ϲݴ밢���� ���
			check_beside_diagonal = 0; // �Ϲݴ밢���� ���
			check_reverse_diagonal = 0; //�Ϲݴ밢���� �ݴ� ���
			check_reverse_beside_diagonal = 0; // �Ϲ� �밢���� �ݴ� ���

			for (i = 0; i < 9; i++) {
				defend_three_point[i] = 0;
			}

			for (i = 0; i < 9; i++) {
				defend_one_point[i] = 0;
			}

			if (pDoc->baduk[row][col] == 0) {
				for (i = 1; i < 3; i++) {
					if (col - i < 0) break; // ���ΰ� 0 �̸� �ݺ�Ż��
					if (pDoc->baduk[row][col - i] == o) { check_beside_horizontal++; }

				}

				for (i = 1; i < 3; i++) {
					if (col + i > 19) break;
					if (pDoc->baduk[row][col + i] == o) { check_horizontal++; }
				}

				for (i = 1; i < 3; i++) {
					if (row - i < 0) break;
					if (pDoc->baduk[row - i][col] == o) { check_beside_vertical++; }
				}

				for (i = 1; i < 3; i++) {
					if (row + i > 19) break;
					if (pDoc->baduk[row + i][col] == o) { check_vertical++; }
				}

				for (i = 1; i < 3; i++) {
					if (row + i > 19 || col + i > 19) break;
					if (pDoc->baduk[row + i][col + i] == o) { check_diagonal++; }
				}

				for (i = 1; i < 3; i++) {
					if (row - i < 0 || col - i <  0) break;
					if (pDoc->baduk[row - i][col - i] == o) { check_beside_diagonal++; }
				}

				for (i = 1; i < 3; i++) {
					if (row - i < 0 || col + i > 19) break;
					if (pDoc->baduk[row - i][col + i] == o) { check_reverse_diagonal++; }
				}

				for (i = 1; i < 3; i++) {
					if (row + i > 19 || col - i < 0) break;
					if (pDoc->baduk[row + i][col - i] == o) { check_reverse_beside_diagonal++; }
				}

				if (pDoc->baduk[row][col - 3] == d) { defend_three_point[0] = 1; }          //beside_horziontal
				if (pDoc->baduk[row][col + 3] == d) { defend_three_point[1] = 1; }          //horizontal
				if (pDoc->baduk[row - 3][col] == d) { defend_three_point[2] = 1; }          //beside_vertical
				if (pDoc->baduk[row + 3][col] == d) { defend_three_point[3] = 1; }          //vertical
				if (pDoc->baduk[row + 3][col + 3] == d) { defend_three_point[4] = 1; }      //diagonal
				if (pDoc->baduk[row - 3][col - 3] == d) { defend_three_point[5] = 1; }      //beside_diagonal
				if (pDoc->baduk[row - 3][col + 34] == d) { defend_three_point[6] = 1; }      //reverse_diagonazl
				if (pDoc->baduk[row + 3][col - 3] == d) { defend_three_point[7] = 1; }      //reverse_besisde_diagonal


				if (pDoc->baduk[row][col - 1] == d) { defend_one_point[0] = 1; }         //beside_horziontal
				if (pDoc->baduk[row][col + 1] == d) { defend_one_point[1] = 1; }          //horizontal
				if (pDoc->baduk[row - 1][col] == d) { defend_one_point[2] = 1; }          //beside_vertical
				if (pDoc->baduk[row + 1][col] == d) { defend_one_point[3] = 1; }          //vertical
				if (pDoc->baduk[row + 1][col + 1] == d) { defend_one_point[4] = 1; }     //diagonal
				if (pDoc->baduk[row - 1][col - 1] == d) { defend_one_point[5] = 1; }      //beside_diagonal
				if (pDoc->baduk[row - 1][col + 1] == d) { defend_one_point[6] = 1; }      //reverse_diagonazl
				if (pDoc->baduk[row + 1][col - 1] == d) { defend_one_point[7] = 1; }      //reverse_besisde_diagonal

				if (check_horizontal == 2) {
					if (defend_three_point[1] == 1 | defend_one_point[0] == 1);
					else ibaduk[row][col] += 30;
				}
				if (check_beside_horizontal == 2) {
					if (defend_three_point[0] == 1 || defend_one_point[1] == 1);
					else ibaduk[row][col] += 30;
				}
				if (check_vertical == 2) {
					if (defend_three_point[3] == 1 || defend_one_point[2] == 1);
					else ibaduk[row][col] += 30;
				}
				if (check_beside_vertical == 2) {
					if (defend_three_point[2] == 1 || defend_one_point[3] == 1);
					else ibaduk[row][col] += 30;
				}
				if (check_diagonal == 2) {
					if (defend_three_point[4] == 1 || defend_one_point[5] == 1);
					else ibaduk[row][col] += 30;
				}
				if (check_beside_diagonal == 2) {
					if (defend_three_point[5] == 1 || defend_one_point[4] == 1);
					else ibaduk[row][col] += 30;
				}
				if (check_reverse_diagonal == 2) {
					if (defend_three_point[6] == 1 || defend_one_point[7] == 1);
					else ibaduk[row][col] += 30;
				}
				if (check_reverse_beside_diagonal == 2) {
					if (defend_three_point[7] == 1 || defend_one_point[6] == 1);
					else ibaduk[row][col] += 30;
				}
			}
			else ibaduk[row][col] = 0;
		}

}

void CMFCApplication3View::OnMouseMove(UINT nFlags, CPoint point) // �ٵ��ǿ� ���� ǥ��
{
	/*
	int sx, sy, ex, ey, col, row, px, py, ex2, ey2;
	double fx, fy;
	int width = 30;
	static int prow, pcol;
	
	CClientDC *pDC, dc(this);
	pDC = &dc;




	CBrush blackbrush, whitebrush, *pold;
	blackbrush.CreateSolidBrush(RGB(0, 0, 0));
	whitebrush.CreateSolidBrush(RGB(255, 255, 255));


	RECT rect;

	//	rect.left = 250 + col * 30 - 15;
	//	rect.top = 100 + row * 30 - 15;
	//	rect.right = rect.left + 30;
	//	rect.bottom = rect.top + 30;

	

	sx = 250, sy = 100;  // ������
	ex = sx + 30 * 18;  // ����
	ey = sy + 30 * 18;

	if (m_start) {

		CMFCApplication3Doc* pDoc = GetDocument();
		if (point.x <sx || point.x>ex || point.y<sy || point.y>ey) {
			mouseCount = 0;
			return;
		}
		// ���콺 ��ǥ���� �̿��Ͽ� �ٵ����� row, col�� �����
		col = (point.x - sx) / 30;
		row = (point.y - sy) / 30;

		// ���콺 ��ġ�� �ٵ����� ��Ȯ�� row, col�� �ƴ� ��� �ݿø��Ͽ� ����� ��ġ�� ����
		fx = double((point.x - sx)) / 30.0;
		fy = double((point.y - sy)) / 30.0;
		if (fx - col > 0.5) col++;
		if (fy - row > 0.5) row++;
		if (prow == row && pcol == col)
			return;


		px = sx + 30 * col - width / 2; //�浹�� ���� ������ǥ(px,py)�� ����ǥ(ex2,ey2)
		py = sy + 30 * row - width / 2;
		ex2 = px + width;
		ey2 = py + width;


		dc.SetROP2(R2_XORPEN);

		if (pDoc->baduk[row][col] == 0) {
		if (m_sunseo) {
			if (trace)
			{
				px = sx + 30 * pcol - width / 2; //�浹�� ���� ������ǥ(px,py)�� ����ǥ(ex2,ey2)
				py = sy + 30 * prow - width / 2;
				ex2 = px + width;
				ey2 = py + width;
				pold = pDC->SelectObject(&whitebrush);
				pDC->Ellipse(px, py, ex2, ey2);
				pDC->SelectObject(pold);

			}
			px = sx + 30 * col - width / 2; //�浹�� ���� ������ǥ(px,py)�� ����ǥ(ex2,ey2)
			py = sy + 30 * row - width / 2;
			ex2 = px + width;
			ey2 = py + width;
			pold = pDC->SelectObject(&whitebrush);
			pDC->Ellipse(px, py, ex2, ey2);
			pDC->SelectObject(pold);
			prow = row;
			pcol = col;
			trace = 1;

		}
		else {
			if (trace)
			{
				px = sx + 30 * pcol - width / 2; //�浹�� ���� ������ǥ(px,py)�� ����ǥ(ex2,ey2)
				py = sy + 30 * prow - width / 2;
				ex2 = px + width;
				ey2 = py + width;
				pold = pDC->SelectObject(&whitebrush);
				pDC->Ellipse(px, py, ex2, ey2);
				pDC->SelectObject(pold);

			}
			px = sx + 30 * col - width / 2; //�浹�� ���� ������ǥ(px,py)�� ����ǥ(ex2,ey2)
			py = sy + 30 * row - width / 2;
			ex2 = px + width;
			ey2 = py + width;
			pold = pDC->SelectObject(&whitebrush);
			pDC->Ellipse(px, py, ex2, ey2);
			pDC->SelectObject(pold);
			prow = row;
			pcol = col;
			trace = 1;

		}
	}
		
		
	}


	*/
	CFormView::OnMouseMove(nFlags, point);
}


void CMFCApplication3View::OnMouseHover(UINT nFlags, CPoint point)
{
	
	
	
	CFormView::OnMouseHover(nFlags, point);
}


int CMFCApplication3View::murgi()
{
	CMFCApplication3Doc* pDoc = GetDocument();
	pDoc->baduk[m_row][m_col] = 0;
	pDoc->baduk[c_row][c_col] = 0;
	Invalidate(true);

	if(m_computerStart==false){
		if (m_sunseo) m_sunseo = false;
		else m_sunseo = true;
	
	}
	return 0;
}
