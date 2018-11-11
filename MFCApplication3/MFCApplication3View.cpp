
// MFCApplication3View.cpp : CMFCApplication3View 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
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
	ON_BN_CLICKED(btn1, &CMFCApplication3View::OnClickedStart) // 시작버튼 메시지 처리
	
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEMOVE()
	
	ON_WM_TIMER()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEHOVER()
END_MESSAGE_MAP()

// CMFCApplication3View 생성/소멸



CMFCApplication3View::CMFCApplication3View()
	: CFormView(IDD_MFCAPPLICATION3_FORM)
	, player_black(false)
{
	// TODO: 여기에 생성 코드를 추가합니다.
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
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CFormView::PreCreateWindow(cs);
}

void CMFCApplication3View::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

	
}


// CMFCApplication3View 진단

#ifdef _DEBUG
void CMFCApplication3View::AssertValid() const
{
	CFormView::AssertValid();
}

void CMFCApplication3View::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CMFCApplication3Doc* CMFCApplication3View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCApplication3Doc)));
	return (CMFCApplication3Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFCApplication3View 메시지 처리기

	

void CMFCApplication3View::OnClickedStart()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	m_start = true;
	
	subDlg.DoModal();
	
}

void CMFCApplication3View::OnClickedConfig()
{
	subDlg2.DoModal();

}

void CMFCApplication3View::BackGround2(CDC *pDC) {    // 2번째 배경
	if (m_start) {
		//배경음악1,backgroundmusic은안됨 나머지 비동기식소리는 모두 작동가능
		/* CString szSoundPath = _T("res\\Sound\\BackGroundMusic1.wav");
		PlaySound(szSoundPath, AfxGetInstanceHandle(), SND_ASYNC | SND_LOOP); */  // 무한

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
	CString szSoundPath = _T("res\\Sound\\메뉴클릭소리1.wav");
	PlaySound(szSoundPath, AfxGetInstanceHandle(), SND_ASYNC | SND_LOOP); // 무한
	*/

	/*
	CString szSoundPath = _T("res\\Sound\\배경음악1.wav");
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
	//TimeSet = 10; // 타이머 초기값
	pDC->SetBkMode(TRANSPARENT);

	bool change;

	if (m_start) {
		

		CMFCApplication3View::BackGround2(pDC);

	


		CString buf1, buf2;
		if (m_computerStart) {
			if (player_black) {
				buf1.Format(_T("플레이어 %d전 %d승"), b_win + w_win, b_win);
			}
			else {
				buf1.Format(_T("컴퓨터 %d전 %d승"), b_win + w_win, w_win);
			}
		}
		else {
			buf1.Format(_T("흑이 %d전 %d승"), b_win + w_win, b_win);
		}
		pDC->TextOutW(50,350 , buf1);

		if (m_computerStart) {
			if (player_black) {
				buf2.Format(_T("컴퓨터 %d전 %d승"), b_win + w_win, w_win);
			}
			else {
				buf2.Format(_T("플레이어 %d전 %d승"), b_win + w_win, b_win);
			}
		}
		else {
			buf2.Format(_T("백이 %d전 %d승"), b_win + w_win, w_win);
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
		
		
		if (m_sunseo) { // 타이머 출력
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
				poldbitmap = memDC.SelectObject(&player1);  // 플레이어1 프로필
				pDC->BitBlt(50, 200, 128, 128, &memDC, 0, 0, SRCCOPY);
				poldbitmap = memDC.SelectObject(&com);   // 컴퓨터 프로필
				pDC->BitBlt(850, 200, 128, 128, &memDC, 0, 0, SRCCOPY);
			}
			else {
				poldbitmap = memDC.SelectObject(&player1);  // 플레이어1 프로필
				pDC->BitBlt(50, 200, 128, 128, &memDC, 0, 0, SRCCOPY);
				poldbitmap = memDC.SelectObject(&player2);   // 플레이어2 프로필
				pDC->BitBlt(850, 200, 128, 128, &memDC, 0, 0, SRCCOPY);
			}
		}
		else {
			if (m_computerStart) {
				poldbitmap = memDC.SelectObject(&com);  //컴퓨터 프로필
				pDC->BitBlt(50, 200, 128, 128, &memDC, 0, 0, SRCCOPY);
				poldbitmap = memDC.SelectObject(&player1);   // 플레이어2 프로필
				pDC->BitBlt(850, 200, 128, 128, &memDC, 0, 0, SRCCOPY);
			}
			else {
				poldbitmap = memDC.SelectObject(&player1);  //플레이어2 프로필
				pDC->BitBlt(50, 200, 128, 128, &memDC, 0, 0, SRCCOPY);
				poldbitmap = memDC.SelectObject(&player2);   //플레이어1 프로필
				pDC->BitBlt(850, 200, 128, 128, &memDC, 0, 0, SRCCOPY);
			}	
			
		}
		
		if (m_sunseo) {// 흑백 차례표시
			if (player_black) {
				poldbitmap = memDC.SelectObject(&HYUK_RED);   // 흑 빨강
				pDC->TransparentBlt(50, 100, 100, 100, &memDC, 0, 0, 100, 100, RGB(255, 255, 255));
				poldbitmap = memDC.SelectObject(&BAEK);   // 백
														  //pDC->BitBlt(850, 100, 100, 100, &memDC, 0, 0, SRCCOPY);
				pDC->TransparentBlt(850, 100, 100, 100, &memDC, 0, 0, 100, 100, RGB(255, 255, 255));
			}
			else {
				poldbitmap = memDC.SelectObject(&HYUK);   // 흑
				pDC->TransparentBlt(50, 100, 100, 100, &memDC, 0, 0, 100, 100, RGB(255, 255, 255));
				poldbitmap = memDC.SelectObject(&BAEK_RED);   // 백 빨강
				pDC->TransparentBlt(850, 100, 100, 100, &memDC, 0, 0, 100, 100, RGB(255, 255, 255));
			}
		}
		else {
			if (player_black) {
				poldbitmap = memDC.SelectObject(&HYUK);   // 흑
				pDC->TransparentBlt(50, 100, 100, 100, &memDC, 0, 0, 100, 100, RGB(255, 255, 255));
				poldbitmap = memDC.SelectObject(&BAEK_RED);   // 백 빨강
				pDC->TransparentBlt(850, 100, 100, 100, &memDC, 0, 0, 100, 100, RGB(255, 255, 255));
			}
			else {
				poldbitmap = memDC.SelectObject(&HYUK_RED);   // 흑 빨강
				pDC->TransparentBlt(50, 100, 100, 100, &memDC, 0, 0, 100, 100, RGB(255, 255, 255));
				poldbitmap = memDC.SelectObject(&BAEK);   // 백
				pDC->TransparentBlt(850, 100, 100, 100, &memDC, 0, 0, 100, 100, RGB(255, 255, 255));
			}
		}
		memDC.SelectObject(poldbitmap);

		// delete[] startBtn; 왜 안되는지 모름
		CBitmap murgi;
		murgi.LoadBitmapW(IDB_CONFIG);
		poldbitmap = memDC.SelectObject(&murgi);   // 흑 빨강
		pDC->BitBlt(70, 500, 128, 101, &memDC, 0, 0,SRCCOPY);

		memDC.SelectObject(poldbitmap);

		const int width = 30;

		int start_x = 250;    //바둑판이 시작되는 화면 좌표
		int start_y = 100;

		 //노랑 검정 흰색 브러시 생성


		px = start_x;               //50픽셀 // 바둑판 첫좌표
		py = start_y;	            //50픽셀

		ex = start_x + width * 18;  //590픽셀 // 바둑판 끝과표
		ey = start_y + width * 18;  //590픽셀

		yellowbrush.CreateSolidBrush(RGB(255, 255, 0));  
		blackbrush.CreateSolidBrush(RGB(0, 0, 0));
		whitebrush.CreateSolidBrush(RGB(255, 255, 255));
				
		CMFCApplication3View::OmokGround(pDC);
		

		for (x = 0; x < 19; x++)
		{
			px = start_x + x*width;
			py = start_y;
			ex = start_x + x*width;
			ey = start_y + width * 18;  // 세로선 긋기

			pDC->MoveTo(px, py);
			pDC->LineTo(ex, ey);
		}

		for (y = 0; y < 19; y++)
		{
			px = start_x;
			py = start_y + y * width;
			ex = start_x + width * 18;
			ey = start_y + y * width;      // 가로선 긋기

			pDC->MoveTo(px, py);
			pDC->LineTo(ex, ey);
		}
		CBrush brush, *poldbrush; // 화점 그리기
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
			for (row = 0; row < 19; row++) {             //바둑돌 출력 1이면 흑돌 , 2이면 백돌로 원을 그림
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
			for (row = 0; row < 19; row++) {             //바둑돌 출력 2이면 흑돌 , 1이면 백돌로 원을 그림
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
		startBmp.LoadBitmap(IDB_START); // 시작 버튼 
		poldbitmap = memDC.SelectObject(&startBmp);
		pDC->StretchBlt(750, 400, 156, 105, &memDC, 0, 0, 156, 105, SRCCOPY);

		configBmp.LoadBitmap(IDB_CONFIG);
		poldbitmap = memDC.SelectObject(&configBmp);  // 설정 버튼
		pDC->StretchBlt(750, 530, 156, 105, &memDC, 0, 0, 156, 105, SRCCOPY);
	}
	
}




void CMFCApplication3View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	int sx, sy, ex, ey, col, row;
	double fx, fy;

	int check_vertical = 0; // 3x3 세로방향 체크 변수
	int check_beside_vertical = 0; // 3x3 세로방향 체크 변수
	int check_horizontal = 0; //3x3 가로방향 체크 변수
	int check_beside_horizontal = 0; //3x3 가로방향 체크 변수
	int check_diagonal = 0;  // 일반대각선의 경우
	int check_beside_diagonal = 0; // 일반대각선의 경우
	int check_reverse_diagonal = 0; //일반대각선의 반대 경우
	int check_reverse_beside_diagonal = 0; // 일반 대각선의 반대 경우

	int three_by_three = 0; // 3x3 체크 -> 4이상이 되었을때 33 메시지 출력
	int i = 0;
	CString s;
	s.Format(_T("3x3입니다")); // 3x3 메시지

	int three_by_three_flag = 0;
	
	CMFCApplication3Doc* pDoc = GetDocument();



	if (m_start == false) {			//시작 버튼? 
		if (point.x < 906 && point.x > 750 && point.y < 505 && point.y >400) {
			CSubDialog subDlg;
			subDlg.DoModal();
		}
		if (point.x < 906 && point.x > 750 && point.y < 635 && point.y >530) {
			CSubDialog2 subDlg2;		// 설정 버튼
			subDlg2.DoModal();
		}
	}

	
	if (point.x < 198 && point.x > 70 && point.y < 601 && point.y >500) {
		//murgi();
		
		CSubDialog dialog;
		dialog.DoModal();
		
	
	}
	
	
	
	
	
	
	
	
	
	
	if (point.x < 998 && point.x > 850 && point.y < 601 && point.y >500) {		//처음으로 버튼
																				
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
																				
		/*CSubDialog subdialog;        //이거 나중에 지우면됨
		subdialog.DoModal();*/
	}

	sx = 250, sy = 100;  // 시작점

	ex = sx + 30 * 18;  // 끝점
	ey = sy + 30 * 18;

	if (point.x < sx || point.x > ex || point.y <sy || point.y >ey) return;

	col = (point.x - sx) / 30;     //화면좌표로 데이터 위치 계산
	row = (point.y - sy) / 30;

	fx = double((point.x - sx)) / 30.0;  // 마우스 위치가 바둑판의 정확한 row,col 위치가 아닐경우
	
	fy = double((point.y - sy)) / 30.0; // 가까운 위치로 지정

	if (fx - col > 0.5) col++;
	if (fy - row > 0.5) row++;

	 check_vertical = 0; // 3x3 세로방향 체크 변수
	 check_beside_vertical = 0; // 3x3 세로방향 체크 변수
	 check_horizontal = 0; //3x3 가로방향 체크 변수
	 check_beside_horizontal = 0; //3x3 가로방향 체크 변수
	 check_diagonal = 0;  // 일반대각선의 경우
	 check_beside_diagonal = 0; // 일반대각선의 경우
	 check_reverse_diagonal = 0; //일반대각선의 반대 경우
	 check_reverse_beside_diagonal = 0; // 일반 대각선의 반대 경우

	if(m_start){
		//PlaySound(_T("res\\Sound\\BackGroundMusic1.wav"), NULL , SND_ASYNC | SND_LOOP);
		PlaySound(_T("res\\Sound\\바둑돌클릭소리1.wav"), NULL, SND_ASYNC);

		if (pDoc->baduk[row][col] == 0) //계산한 위치에 바둑돌이 없으면 그위치에 바둑돌 값을 저장
		{
			if (m_sunseo) {




				// 33 시작

				//==============둔 위치를 중심으로 33 가로 줄 체크===============//
				
				if (pDoc->baduk[row + 1][col] == 2);			//둔 위치부터 오른쪽 체크 x?
				else if (pDoc->baduk[row + 1][col] == 1) {			//둔 위치 부터 오른쪽 체크 x*?
					if (pDoc->baduk[row + 2][col] == 2);			
					else if (pDoc->baduk[row + 2][col] == 1) {			//x** 상태
						if (pDoc->baduk[row + 3][col] == 2);
						else if (pDoc->baduk[row + 3][col] == 1);
						else if (pDoc->baduk[row + 3][col] == 0){
							if (pDoc->baduk[row + 4][col] == 2 || pDoc->baduk[row + 4][col] == 0) {
								if (pDoc->baduk[row - 1][col] == 2);
								else if (pDoc->baduk[row - 1][col] == 1);
								else if (pDoc->baduk[row - 1][col] == 0) {
									if (pDoc->baduk[row - 2][col] == 2) {
										if (pDoc->baduk[row + 4][col] == 0) three_by_three_flag++; // 흰돌 양쪽을 막을 가능성 체크
									}
									else if (pDoc->baduk[row - 2][col] == 1);
									else if (pDoc->baduk[row - 2][col] == 0)three_by_three_flag++; // x**검증 완료
								}
							}
							else if (pDoc->baduk[row + 4][col] == 1);
						}
					}
					else if(pDoc->baduk[row + 2][col] == 0){		//둔 위치부터 오른쪽 x* ?
						if (pDoc->baduk[row + 3][col] == 2 || pDoc->baduk[row + 3][col] == 0) {		//x*   상태
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
				else if (pDoc->baduk[row + 1][col] == 0) {			//x ? 상태.
					if (pDoc->baduk[row + 2][col] == 2 || pDoc->baduk[row + 2][col] == 0) {		//   x 좌측 검사 시작.
						if (pDoc->baduk[row - 1][col] == 2);
						else if (pDoc->baduk[row - 1][col] == 1) {				//   *x 상태.
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
						else if (pDoc->baduk[row - 1][col] == 0) {		// ? x 상태
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
						else if (pDoc->baduk[row + 3][col] == 0) {		// x *  상태
							if (pDoc->baduk[row + 4][col] == 2 || pDoc->baduk[row + 4][col] == 0) {
								if (pDoc->baduk[row - 1][col] == 2);
								else if (pDoc->baduk[row - 1][col] == 1) {		// *x * 상태
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

				// ====================== 가로줄 체크 끝 ====================== //



				//==============둔 위치를 중심으로 33 세로 줄 체크===============//

				if (pDoc->baduk[row][col + 1] == 2);			//둔 위치부터 오른쪽 체크 x?
				else if (pDoc->baduk[row][col + 1] == 1) {			//둔 위치 부터 오른쪽 체크 x*?
					if (pDoc->baduk[row][col + 2] == 2);
					else if (pDoc->baduk[row][col + 2] == 1) {			//x** 상태
						if (pDoc->baduk[row][col + 3] == 2);
						else if (pDoc->baduk[row][col + 3] == 1);
						else if (pDoc->baduk[row][col + 3] == 0) {
							if (pDoc->baduk[row][col + 4] == 2 || pDoc->baduk[row][col + 4] == 0) {
								if (pDoc->baduk[row][col - 1] == 2);
								else if (pDoc->baduk[row][col - 1] == 1);
								else if (pDoc->baduk[row][col - 1] == 0) {
									if (pDoc->baduk[row][col - 2] == 2) {
										if (pDoc->baduk[row][col + 4] == 0) three_by_three_flag++; // 흰돌 양쪽을 막을 가능성 체크
									}
									else if (pDoc->baduk[row][col - 2] == 1);
									else if (pDoc->baduk[row][col - 2] == 0)three_by_three_flag++; // x**검증 완료
								}
							}
							else if (pDoc->baduk[row][col + 4] == 1);
						}
					}
					else if (pDoc->baduk[row][col + 2] == 0) {		//둔 위치부터 오른쪽 x* ?
						if (pDoc->baduk[row][col + 3] == 2 || pDoc->baduk[row][col + 3] == 0) {		//x*   상태
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
				else if (pDoc->baduk[row][col + 1] == 0) {			//x ? 상태.
					if (pDoc->baduk[row][col + 2] == 2 || pDoc->baduk[row][col + 2] == 0) {		//   x 좌측 검사 시작.
						if (pDoc->baduk[row][col - 1] == 2);
						else if (pDoc->baduk[row][col - 1] == 1) {				//   *x 상태.
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
						else if (pDoc->baduk[row][col - 1] == 0) {		// ? x 상태
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
						else if (pDoc->baduk[row][col + 3] == 0) {		// x *  상태
							if (pDoc->baduk[row][col + 4] == 2 || pDoc->baduk[row][col + 4] == 0) {
								if (pDoc->baduk[row][col - 1] == 2);
								else if (pDoc->baduk[row][col - 1] == 1) {		// *x * 상태
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

				// ====================== 세로줄 체크 끝 ====================== //




				//==============둔 위치를 중심으로 좌상 --> 우하 대각선 줄 체크===============//

				if (pDoc->baduk[row + 1][col + 1] == 2);			//둔 위치부터 오른쪽 체크 x?
				else if (pDoc->baduk[row + 1][col + 1] == 1) {			//둔 위치 부터 오른쪽 체크 x*?
					if (pDoc->baduk[row + 2][col + 2] == 2);
					else if (pDoc->baduk[row + 2][col + 2] == 1) {			//x** 상태
						if (pDoc->baduk[row + 3][col + 3] == 2);
						else if (pDoc->baduk[row + 3][col + 3] == 1);
						else if (pDoc->baduk[row + 3][col + 3] == 0) {
							if (pDoc->baduk[row + 4][col + 4] == 2 || pDoc->baduk[row + 4][col + 4] == 0) {
								if (pDoc->baduk[row - 1][col - 1] == 2);
								else if (pDoc->baduk[row - 1][col - 1] == 1);
								else if (pDoc->baduk[row - 1][col - 1] == 0) {
									if (pDoc->baduk[row - 2][col - 2] == 2) {
										if (pDoc->baduk[row + 4][col + 4] == 0) three_by_three_flag++; // 흰돌 양쪽을 막을 가능성 체크
									}
									else if (pDoc->baduk[row - 2][col - 2] == 1);
									else if (pDoc->baduk[row - 2][col - 2] == 0)three_by_three_flag++; // x**검증 완료
								}
							}
							else if (pDoc->baduk[row + 4][col + 4] == 1);
						}
					}
					else if (pDoc->baduk[row + 2][col + 2] == 0) {		//둔 위치부터 오른쪽 x* ?
						if (pDoc->baduk[row + 3][col + 3] == 2 || pDoc->baduk[row + 3][col + 3] == 0) {		//x*   상태
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
				else if (pDoc->baduk[row + 1][col + 1] == 0) {			//x ? 상태.
					if (pDoc->baduk[row + 2][col + 2] == 2 || pDoc->baduk[row + 2][col + 2] == 0) {		//   x 좌측 검사 시작.
						if (pDoc->baduk[row - 1][col - 1] == 2);
						else if (pDoc->baduk[row - 1][col - 1] == 1) {				//   *x 상태.
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
						else if (pDoc->baduk[row - 1][col - 1] == 0) {		// ? x 상태
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
						else if (pDoc->baduk[row + 3][col + 3] == 0) {		// x *  상태
							if (pDoc->baduk[row + 4][col + 4] == 2 || pDoc->baduk[row + 4][col + 4] == 0) {
								if (pDoc->baduk[row - 1][col - 1] == 2);
								else if (pDoc->baduk[row - 1][col - 1] == 1) {		// *x * 상태
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

				// ====================== 좌상 우하 대각선 체크 끝 ====================== //




				//==============둔 위치를 중심으로 우상 --> 좌하 대각선 줄 체크===============//

				if (pDoc->baduk[row + 1][col - 1] == 2);			//둔 위치부터 오른쪽 체크 x?
				else if (pDoc->baduk[row + 1][col - 1] == 1) {			//둔 위치 부터 오른쪽 체크 x*?
					if (pDoc->baduk[row + 2][col - 2] == 2);
					else if (pDoc->baduk[row + 2][col - 2] == 1) {			//x** 상태
						if (pDoc->baduk[row + 3][col - 3] == 2);
						else if (pDoc->baduk[row + 3][col - 3] == 1);
						else if (pDoc->baduk[row + 3][col - 3] == 0) {
							if (pDoc->baduk[row + 4][col - 4] == 2 || pDoc->baduk[row + 4][col - 4] == 0) {
								if (pDoc->baduk[row - 1][col + 1] == 2);
								else if (pDoc->baduk[row - 1][col + 1] == 1);
								else if (pDoc->baduk[row - 1][col + 1] == 0) {
									if (pDoc->baduk[row - 2][col + 2] == 2) {
										if (pDoc->baduk[row + 4][col - 4] == 0) three_by_three_flag++; // 흰돌 양쪽을 막을 가능성 체크
									}
									else if (pDoc->baduk[row - 2][col + 2] == 1);
									else if (pDoc->baduk[row - 2][col + 2] == 0)three_by_three_flag++; // x**검증 완료
								}
							}
							else if (pDoc->baduk[row + 4][col - 4] == 1);
						}
					}
					else if (pDoc->baduk[row + 2][col - 2] == 0) {		//둔 위치부터 오른쪽 x* ?
						if (pDoc->baduk[row + 3][col - 3] == 2 || pDoc->baduk[row + 3][col - 3] == 0) {		//x*   상태
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
				else if (pDoc->baduk[row + 1][col - 1] == 0) {			//x ? 상태.
					if (pDoc->baduk[row + 2][col - 2] == 2 || pDoc->baduk[row + 2][col - 2] == 0) {		//   x 좌측 검사 시작.
						if (pDoc->baduk[row - 1][col + 1] == 2);
						else if (pDoc->baduk[row - 1][col + 1] == 1) {				//   *x 상태.
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
						else if (pDoc->baduk[row - 1][col + 1] == 0) {		// ? x 상태
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
						else if (pDoc->baduk[row + 3][col - 3] == 0) {		// x *  상태
							if (pDoc->baduk[row + 4][col - 4] == 2 || pDoc->baduk[row + 4][col - 4] == 0) {
								if (pDoc->baduk[row - 1][col + 1] == 2);
								else if (pDoc->baduk[row - 1][col + 1] == 1) {		// *x * 상태
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

				// ====================== 우상 좌하 대각선 체크 끝 ====================== //


				// 33 끝



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
					if (pDoc->baduk[row - i][col - i] == 2) check_beside_diagonal++;             //일반 대각선의 경우 (왼쪽위로)
					else if (pDoc->baduk[row - 4][col - 4] == 1) {
						if (pDoc->baduk[row - 3][col - 3] == 0);
						else check_beside_diagonal = -1;
					}
					else if (pDoc->baduk[row - i][col - i] == 1)	check_beside_diagonal = -1;

					if (pDoc->baduk[row + i][col + i] == 2) check_diagonal++;            //일반 대각선의 경우 (오른쪽 아래로)
					else if (pDoc->baduk[row + 4][col + 4] == 1) {
						if (pDoc->baduk[row + 3][col + 3] == 0);
						else check_diagonal = -1;
					}
					else if (pDoc->baduk[row + i][col + i] == 1) check_diagonal = -1;

					if (pDoc->baduk[row - i][col + i] == 2) check_reverse_diagonal++;             //대각선의 반대 경우 (오른쪽 위로)
					else if (pDoc->baduk[row - 4][col + 4] == 1) {
						if (pDoc->baduk[row - 3][col + 3] == 0);
						else check_reverse_diagonal = -1;
					}
					else if (pDoc->baduk[row - i][col + i] == 1) check_reverse_diagonal = -1;

					if (pDoc->baduk[row + i][col - i] == 2) check_reverse_beside_diagonal++;           //대각선의 반대 경우 (왼쪽 아래로)
					else if (pDoc->baduk[row + 4][col - 4] == 1) {
						if (pDoc->baduk[row + 3][col - 3] == 0);
						else check_reverse_beside_diagonal = -1;
					}
					else if (pDoc->baduk[row + i][col - i] == 1) check_reverse_beside_diagonal = -1;

					if (pDoc->baduk[row][col + i] == 2) check_horizontal++;             //가로방향 (오른쪽으로)
					else if (pDoc->baduk[row][col + 4] == 1) {
						if (pDoc->baduk[row][col + 3] == 0); // 맨끝에 백돌이 있을경우 검사
						else check_horizontal = -1;
					}
					else if (pDoc->baduk[row][col + i] == 1) check_horizontal = -1;  // 그외 백돌이 있으면 모두 3x3에서 제외


					if (pDoc->baduk[row][col - i] == 2) check_beside_horizontal++;            //가로방향 (왼쪽으로)
					else if (pDoc->baduk[row][col - 4] == 1) {
						if (pDoc->baduk[row][col - 3] == 0); //맨끝에 백돌이 있을경우 검사
						else check_beside_horizontal = -1;
					}
					else if (pDoc->baduk[row][col - i] == 1) check_beside_horizontal = -1; // 그외 백돌이 있으면 모두 3x3에서 제외

					if (pDoc->baduk[row + i][col] == 2) check_vertical++;            // 세로방향 (밑으로)
					else if (pDoc->baduk[row + 4][col] == 1) {
						if (pDoc->baduk[row + 3][col] == 0);
						else check_vertical = -1;
					}
					else if (pDoc->baduk[row + i][col] == 1) check_vertical = -1;

					if (pDoc->baduk[row - i][col] == 2) check_beside_vertical++;            // 세로방향 (위로)
					else if (pDoc->baduk[row - 4][col] == 1) {
						if (pDoc->baduk[row - 3][col] == 0); //맨끝에 백돌이 있을 경우 검사
						else check_beside_vertical = -1;
					}
					else if (pDoc->baduk[row - i][col] == 1) check_beside_vertical = -1; // 그외 백돌이 있으면 모두 3x3제외

				}
				// 여기서 부터 다시 검사 세로방향 검사
				if (check_vertical == 2) three_by_three += 2; if (check_beside_vertical == 2) three_by_three += 2; //세로방향 
				if (check_vertical == 2 && (check_beside_vertical >= 1)) three_by_three -= 4;  // 문제점 보완. 주위에 돌이 있는지 검사
				if (check_beside_vertical == 2 && (check_vertical >= 1)) three_by_three -= 4;// 문제점 보완. 주위에 돌이 있는지 검사
																							 // 세로방향 검사 끝

																							 // 가로방향 검사 시작
				if (check_horizontal == 2) three_by_three += 2; if (check_beside_horizontal == 2) three_by_three += 2; //가로방향
				if (check_horizontal == 2 && (check_beside_horizontal >= 1)) three_by_three -= 4;  // 문제점 보완. 주위에 돌이 있는지 검사
				if (check_beside_horizontal == 2 && (check_horizontal >= 1)) three_by_three -= 4;// 문제점 보완. 주위에 돌이 있는지 검사
																								 //가로방향 검사 끝

																								 //대각선 검사 시작
				if (check_diagonal == 2) three_by_three += 2; if (check_beside_diagonal == 2) three_by_three += 2; //반대 대각선방향
				if (check_diagonal == 2 && (check_beside_diagonal >= 1)) three_by_three -= 4;  // 문제점 보완. 주위에 돌이 있는지 검사
				if (check_beside_diagonal == 2 && (check_diagonal >= 1)) three_by_three -= 4;// 문제점 보완. 주위에 돌이 있는지 검사
																							 //대각선 검사 끝

																							 //반대 대각선 검사 시작
				if (check_reverse_diagonal == 2) three_by_three += 2; if (check_reverse_beside_diagonal == 2) three_by_three += 2; //반대 대각선방향
				if (check_reverse_diagonal == 2 && (check_reverse_beside_diagonal >= 1)) three_by_three -= 4;  // 왼쪽 대각선 위에 돌이 있는지 검사
				if (check_reverse_beside_diagonal == 2 && (check_reverse_diagonal >= 1)) three_by_three -= 4;// 오른쪽 대각선 아래에 있는지 검사
																											 //반대 대각선 검사 끝

																											 // 3x3 체크 끝!
				pDoc->baduk[row][col] = 2;
				m_sunseo = true;

				if (three_by_three >= 4) { pDoc->baduk[row][col] = 0; m_sunseo = false; AfxMessageBox(s); } // three_by_three가 4이상일시 3x3 메시지 출력
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

			m_row = row;		//무르기를 위한 저장
			m_col = col;

			


			if (m_sunseo) {
				if (Checkvictory(2, row, col) == 1) {
					PlaySound(_T("res\\Sound\\승리사운드1.wav"), NULL, SND_ASYNC);
					w_win++; // 백 1승 추가

					if (m_computerStart) {
						AfxMessageBox(_T("플레이어가 승리했습니다."), MB_OK);
					}
					else {
						AfxMessageBox(_T("백이 승리했습니다."), MB_OK);
					}
					for (int row = 0; row < 19; row++)
						for (int col = 0; col < 19; col++)
							pDoc->baduk[row][col] = 0;

					if (m_computerStart) {
						if (player_black) player_black = false;
						else player_black = true;
					}

					
					if (w_win==winCount) {		// 백 최종승리 계산
						if (m_computerStart) {
							AfxMessageBox(_T("플레이어가 최종 승리했습니다. 초기화면으로"), MB_OK);
						}
						else {
							AfxMessageBox(_T("백이 최종 승리했습니다. 초기화면으로"), MB_OK);
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
					PlaySound(_T("res\\Sound\\승리사운드1.wav"), NULL, SND_ASYNC);
					b_win++; // 흑 1승 추가

					if (m_computerStart) {
						AfxMessageBox(_T("플레이어가 승리했습니다."), MB_OK);
					}else {
						AfxMessageBox(_T("흑이 승리했습니다."), MB_OK);
					}
					for (int row = 0; row < 19; row++)
						for (int col = 0; col < 19; col++)
							pDoc->baduk[row][col] = 0;

					if (m_computerStart) {
						if (player_black) player_black = false;
						else player_black = true;
					}

					if (b_win == winCount) {		// 흑 최종승리 계산
						if (m_computerStart) {
							AfxMessageBox(_T("플레이어가 최종 승리했습니다. 초기화면으로"), MB_OK);
						}else {
							AfxMessageBox(_T("흑이 최종 승리했습니다. 초기화면으로"), MB_OK);
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
					if (m_computerStart == true) {        //인공지능
						hansu_ap(2, 1, row, col);
						//AI_White_Do(row, col);
					}
					for (int r = 0; r<19; r++)
					{
						for (int c = 0; c<19; c++)
						{
							if (Checkvictory(2, r, c) == 1)
							{
								PlaySound(_T("res\\Sound\\승리사운드1.wav"), NULL, SND_ASYNC);
								w_win++;

								
								AfxMessageBox(_T("컴퓨터가 승리했습니다."), MB_OK);
								
								for (int row = 0; row<19; row++)
									for (int col = 0; col<19; col++)
										pDoc->baduk[row][col] = 0;

								if (player_black) player_black = false;
								else player_black = true;

								if (w_win == winCount) {		// 컴퓨터 최종승리 계산
									
									AfxMessageBox(_T("컴퓨터가 최종 승리했습니다. 초기화면으로"), MB_OK);

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

		if (point.x < 250 && point.x > 50 && point.y < 200 && point.y >50) { //한 수 무르기
			
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
	//a=1 이면 흑돌 오목 체크, a=2 면 백돌 오목 체크
	CMFCApplication3Doc* pDoc = GetDocument();

	int i;
	int count = 0;

	int victory_count = 0;  //승리 조건이 만족되면 5가 된다

	for (i = 0; i < 19; i++) {		//왼쪽에서 오른쪽으로 체크
		if (pDoc->baduk[r][i] == a) {
			count++;
			if (pDoc->baduk[r][i + 1] == a);
			else if (count == 5) victory_count = count;
		}

		else count = 0;
	}

	if (victory_count == 5) return 1; 	//오목이면 1 리턴


	count = 0;
	victory_count = 0;

	for (i = 0; i < 19; i++) {		//위에서 아래로 체크
		if (pDoc->baduk[i][c] == a) {
			count++;
			if (pDoc->baduk[i + 1][c] == a);
			else if (count == 5) victory_count = count;
		}

		else count = 0;

	}
	if (victory_count == 5) return 1; 	//오목이면 1 리턴


										//왼쪽 위부터 오른쪽 아래대각선 까지
	int srow, scol;
	int erow, ecol;
	int tr, tc;
	tr = r;	tc = c;

	while (tr != 0 && tc != 0) {	//왼쪽 위의 끝에 도달까지 진행
		tr--;
		tc--;
	}

	srow = tr; scol = tc;		//왼쪽 위 끝 시작 지점.

	tr = r; tc = c;

	while (tr != 18 && tc != 18) {
		tr++;
		tc++;
	}

	erow = tr; ecol = tc;		//오른쪽 아래 끝 지점.

	count = 0;
	victory_count = 0;

	while (scol <= ecol && srow <= erow) {	//체크 시작
		if (pDoc->baduk[srow][scol] == a) {
			count++;
			if (pDoc->baduk[srow + 1][scol + 1] == a);
			else if (count == 5) victory_count = count;
		}
		else count = 0;
		srow++;
		scol++;
	}
	if (victory_count == 5) return 1; 	//오목이면 1 리턴



	tr = r;
	tc = c;

	while (tr != 0 && tc != 18) {	//오른쪽 위의 끝에 도달까지 진행
		tr--;
		tc++;
	}

	srow = tr; scol = tc;		// 오른쪽 위 끝 시작 지점.

	tr = r; tc = c;
	while (tr != 18 && tc != 0) {
		tr++;
		tc--;
	}

	erow = tr; ecol = tc;		//오른쪽 아래 끝 지점.

	count = 0;
	victory_count = 0;

	while (scol >= ecol&&srow <= erow) {	//체크 시작
		if (pDoc->baduk[srow][scol] == a) {
			count++;
			if (pDoc->baduk[srow + 1][scol - 1] == a);
			else if (count == 5) victory_count = count;
		}
		else count = 0;
		srow++;
		scol--;
	}
	if (victory_count == 5) return 1; 	//오목이면 1 리턴



	return 0;			//오목이 아니면 0 리턴
}






void CMFCApplication3View::OnTimer(UINT_PTR nIDEvent) // 오목 타이머 기능
{
	CDC *pDC = GetDC(); 
	CMFCApplication3Doc *pDoc = GetDocument();
	CString buf;
	CClientDC dc(this);
	
	if (nIDEvent == 1)
	{
		TimeSet--;
		if (TimeSet < 10) {
			buf.Format(_T("남은시간 : 0%d초"), TimeSet);
		}
		else {
			buf.Format(_T("남은시간 : %d초"), TimeSet);
		}
			dc.TextOut(250, 50, buf);
		
		if (TimeSet == 0)
		{
			KillTimer(1);
			if (m_sunseo == true) { //흑 시간초과
				w_win++;
				
				if (m_computerStart){ // 컴퓨터랑 할 때
					AfxMessageBox(_T("컴퓨터가 승리했습니다. 새 게임 시작합니다."), MB_OK);
				} //사람이랑 할 때
				else { AfxMessageBox(_T("백이 승리했습니다. 새 게임 시작합니다."), MB_OK); }
				
				
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
				if (m_computerStart) { // 컴퓨터랑 할 때
					AfxMessageBox(_T("컴퓨터가 승리했습니다. 새 게임 시작합니다."), MB_OK);
				} //사람이랑 할 때
				else { AfxMessageBox(_T("흑이 승리했습니다. 새 게임 시작합니다."), MB_OK); }
				
				
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
	int pcol = 0; //이전 row 와 col
	int count = 0;
	int max;
	int mrow = 0;
	int mcol = 0;;          //예상 내 돌
	int nrow = 0;
	int ncol = 0;;          //예상 상대돌

	int superrow = 0;        //5목이상일시 row
	int supercol = 0;        //5목이상일시 col

	int ultrarow = 0;        //4_3목이상일시 
	int ultracol = 0;		 //4_3목이상일시 

	int change = 0;            //4_3목이상일시
	int change2 = 0;           //5목이상일시

	int row, col;

	int chrow, chcol;

	/* 첫수 조사 만약 첫수를 조사했을때 꼭막아야하거나 공격해야한다면 */
	{   //이 괄호는 구분용이다.
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
		offendWeight_three_by_three(2, 1);      // 33방지 코드, 43 체크 코드
		dffendWeight_three_by_three(1, 2);


		OffendWeight5(2, 1);                   // 4개 될때 공격과 방어
		OffendWeight5_2(2, 1);	               // 2개 2개 돌이 나눠져 있을때 가운데 놓음
		OffendWeight5_3(2, 1);		           // 3개 1개 나눠져 있을때 가운데 놓음

		OffendWeight6(2, 1);				   // 6목 방지코드 
		OffendWeight6_2(2, 1);
		OffendWeight6_3(2, 1);

		OffendWeight4(2, 1);                   // 3돌이 연속될경우 공격과 방어
		OffendWeight4_2(2, 1);                 // 2개 1개 나눠져 있을때 가운데 놓음

		OffendWeight(2, 1);                    // 앞의 매개변수는 나의돌 , 뒤의 매개변수는 상대의 돌
		defendWeight(2, 1);
		max = 0;

		mrow = 0; mcol = 0;



		for (chrow = 0; chrow < 19; chrow++)                                    //가중치의 최대값을 찾아줌
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
			
			
			CString s;                                         // 어디에 놨는지 표시해주는건데 test용임
			s.Format(_T("max = %d ,m_row= %d m_col= %d "), max, mrow, mcol);
			AfxMessageBox(s);
			
			
			
		}
		else if (max >= 600)
		{
			change2 = 1;
			superrow = mrow;
			supercol = mcol;
			
			CString s;                                         // 어디에 놨는지 표시해주는건데 test용임
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
	/* 첫수 조사 만약 첫수를 조사했을때 43 및 5목이 나오면 그냥 이 함수를 빠져나온다 */

	/* 차례로 내돌 놓기*/
	for (row = 0; row < 19; row++)
		for (col = 0; col < 19; col++) {

			if (pDoc->baduk[row][col] == 0) {

				pDoc->baduk[row][col] = 2;

				/* 차례로 내돌 놓기*/


				prow = row;       //previousrow 이전돌
				pcol = col;       //previouscol 이전돌



								  /* 초기화 ibaduk, obaduk , dbaduk */
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
				/* 초기화 ibaduk, obaduk , dbaduk */

				/*상대수 계산*/
				{
					offendWeight_three_by_three(1, 2);      // 33방지 코드, 43 체크 코드
					dffendWeight_three_by_three(2, 1);


					OffendWeight5(1, 2);                   // 4개 될때 공격과 방어
					OffendWeight5_2(1, 2);	               // 2개 2개 돌이 나눠져 있을때 가운데 놓음
					OffendWeight5_3(1, 2);		           // 3개 1개 나눠져 있을때 가운데 놓음

					OffendWeight6(1, 2);				   // 6목 방지코드 
					OffendWeight6_2(1, 2);
					OffendWeight6_3(1, 2);

					OffendWeight4(1, 2);                   // 3돌이 연속될경우 공격과 방어
					OffendWeight4_2(1, 2);                 // 2개 1개 나눠져 있을때 가운데 놓음

					OffendWeight(1, 2);                    // 앞의 매개변수는 나의돌 , 뒤의 매개변수는 상대의 돌


					max = 0;

					nrow = 0; ncol = 0;
					for (int drow = 0; drow < 19; drow++)                                    //가중치의 최대값을 찾아줌
						for (int dcol = 0; dcol < 19; dcol++) {
							if (max < dbaduk[drow][dcol]) {
								max = dbaduk[drow][dcol];
								nrow = drow;
								ncol = dcol;
							}
						}


					pDoc->baduk[nrow][ncol] = 1;

				}
				/*상대수 계산*/



				/*나의 수 계산*/
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

					offendWeight_three_by_three(2, 1);      // 33방지 코드, 43 체크 코드
					dffendWeight_three_by_three(1, 2);


					OffendWeight5(2, 1);                   // 4개 될때 공격과 방어
					OffendWeight5_2(2, 1);	               // 2개 2개 돌이 나눠져 있을때 가운데 놓음
					OffendWeight5_3(2, 1);		           // 3개 1개 나눠져 있을때 가운데 놓음

					OffendWeight6(2, 1);				   // 6목 방지코드 
					OffendWeight6_2(2, 1);
					OffendWeight6_3(2, 1);

					OffendWeight4(2, 1);                   // 3돌이 연속될경우 공격과 방어
					OffendWeight4_2(2, 1);                 // 2개 1개 나눠져 있을때 가운데 놓음

					OffendWeight(2, 1);                    // 앞의 매개변수는 나의돌 , 뒤의 매개변수는 상대의 돌


					max = 0;

					mrow = 0; mcol = 0;


					for (int orow = 0; orow < 19; orow++)                                    //가중치의 최대값을 찾아줌
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

				/*나의 수 계산*/




				/* 43목이거나 5목이상일시 값이 변함*/
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
				/* 43목이거나 5목이상일시 값이 변함*/

				/*
				Invalidate(false);
				CString s;                                         // 어디에 놨는지 표시해주는건데 test용임
				s.Format(_T("max = %d ,ultrarow= %d ultracol= %d "), max, ultrarow, ultracol);
				AfxMessageBox(s);
				*/

				/* 반복문이 1번이상 돌았을때 이전돌 및 상대돌 제거*/
				count++;

				if (count > 0)
				{
					pDoc->baduk[prow][pcol] = 0;
					pDoc->baduk[nrow][ncol] = 0;
				}
				/* 반복문이 1번이상 돌았을때 이전돌 및 상대돌 제거*/
			}


		}  // 반복문 끝

	pDoc->baduk[row][col] = 0; // 마지막돌 제거


	change = 0;
	change2 = 0;

	/* ultra 나 super의 값이 변했을시 change값이 변함*/
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
	/* ultra 나 super의 값이 변했을시 change값이 변함*/

	/* change값이 변했을시 동작하고 아니면 그냥 AI_WHITE_DO 실행*/
	if (change2) {
		/*
		CString s;                                         // 어디에 놨는지 표시해주는건데 test용임
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
		CString s;                                         // 어디에 놨는지 표시해주는건데 test용임
		s.Format(_T("max = %d ,m_row= %d m_col= %d "), max, ultrarow, ultracol);
		AfxMessageBox(s);
		*/
		pDoc->baduk[ultrarow][ultracol] = 2;
		m_sunseo = true;
		Invalidate(false);
		
		return 0;
	}

	else AI_White_Do(r, c);
	/* change값이 변했을시 동작하고 아니면 그냥 AI_WHITE_DO 실행*/

}


int CMFCApplication3View::AI_White_Do(int r, int c)
{

	{
		CMFCApplication3Doc* pDoc = GetDocument();




		//===============================================================
		// 공격, 방어 알고리즘
		//===============================================================

		int count = 0;
		int row, col;
		int tr, tc;
		int max, mrow, mcol;

		for (row = 0; row < 19; row++)
			for (col = 0; col < 19; col++) {
				ibaduk[row][col] = 0;
			}

		offendWeight_three_by_three(2, 1);      // 33방지 코드, 43 체크 코드
		dffendWeight_three_by_three(1, 2);


		OffendWeight5(2, 1);                   // 4개 될때 공격과 방어
		OffendWeight5_2(2, 1);	               // 2개 2개 돌이 나눠져 있을때 가운데 놓음
		OffendWeight5_3(2, 1);		           // 3개 1개 나눠져 있을때 가운데 놓음

		OffendWeight6(2, 1);				   // 6목 방지코드 
		OffendWeight6_2(2, 1);
		OffendWeight6_3(2, 1);

		OffendWeight4(2, 1);                   // 3돌이 연속될경우 공격과 방어
		OffendWeight4_2(2, 1);                 // 2개 1개 나눠져 있을때 가운데 놓음
											   /*
											   OffendWeight4_3_1(2, 1);
											   OffendWeight4_3(2, 1);                 // 43코드
											   OffendWeight4_3_2(2, 1);
											   OffendWeight4_3_3(2, 1);
											   */
		OffendWeight3(2, 1);
		OffendWeight(2, 1);                    // 앞의 매개변수는 나의돌 , 뒤의 매개변수는 상대의 돌
		defendWeight(2, 1);
		max = 0;

		mrow = 0; mcol = 0;
		for (row = 0; row < 19; row++)                                    //가중치의 최대값을 찾아줌
			for (col = 0; col < 19; col++) {
				if (max < ibaduk[row][col]) {
					max = ibaduk[row][col];
					mrow = row;
					mcol = col;
				}
				else if (max == ibaduk[row][col]) {
					if (pDoc->baduk[row + 1][col] == 2) { mrow = row; mcol = col; }    //최대값이 차이가 없을 때 최대한 주위를 살펴 나의 돌이 있는곳에 수를둠
					else if (pDoc->baduk[row - 1][col + 1] == 2) { mrow = row; mcol = col; }
					else if (pDoc->baduk[row][col + 1] == 2) { mrow = row; mcol = col; }
					else if (pDoc->baduk[row][col - 1] == 2) { mrow = row; mcol = col; }
					else if (pDoc->baduk[row - 1][col - 1] == 2) { mrow = row; mcol = col; }
					else if (pDoc->baduk[row + 1][col - 1] == 2) { mrow = row; mcol = col; }
					else if (pDoc->baduk[row + 1][col - 1] == 2) { mrow = row; mcol = col; }
					else if (pDoc->baduk[row - 1][col + 1] == 2) { mrow = row; mcol = col; }
				}

			}

		
		CString s;                                         // 어디에 놨는지 표시해주는건데 test용임
		s.Format(_T("max = %d ,m_row= %d m_col= %d "), max, mrow, mcol);
		AfxMessageBox(s);
		
		

		if (max <= 0) {                     // 첫수는 그냥 사용자 마우스 클릭에 따라 둔다
			tr = r + 1; tc = c + 1;
			if (tr <= 18 || tc <= 18)          //기본대각선
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
			if (tr <= 18)                   //그거안되면 오른쪽
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
			if (tr <= 18)                    //그거안되면 밑
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
		else                                  //그상황외에는 가중치에 따라 둔다.
			pDoc->baduk[mrow][mcol] = 2;
		
		m_sunseo = true;
		c_row = mrow;
		c_col = mcol;
		Invalidate(false);
		return 1;

	}
	
}








void CMFCApplication3View::OffendWeight6(int o, int d) { //5개 이상일때 줄줄이 사탕으로 계속 놓는걸 방지
	CMFCApplication3Doc* pDoc = GetDocument();
	int i;
	int check_vertical = 0; // 세로방향 체크 변수
	int check_beside_vertical = 0; //  세로방향 체크 변수
	int check_horizontal = 0; // 가로방향 체크 변수
	int check_beside_horizontal = 0; // 가로방향 체크 변수
	int check_diagonal = 0;  // 일반대각선의 경우
	int check_beside_diagonal = 0; // 일반대각선의 경우
	int check_reverse_diagonal = 0; //일반대각선의 반대 경우
	int check_reverse_beside_diagonal = 0; // 일반 대각선의 반대 경우

	int row, col;

	for (row = 0; row < 19; row++)
		for (col = 0; col < 19; col++) {
			check_vertical = 0; //  세로방향 체크 변수
			check_beside_vertical = 0; //  세로방향 체크 변수
			check_horizontal = 0; // 가로방향 체크 변수
			check_beside_horizontal = 0; // 가로방향 체크 변수
			check_diagonal = 0;  // 일반대각선의 경우
			check_beside_diagonal = 0; // 일반대각선의 경우
			check_reverse_diagonal = 0; //일반대각선의 반대 경우
			check_reverse_beside_diagonal = 0; // 일반 대각선의 반대 경우

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
			check_vertical = 0; //  세로방향 체크 변수
			check_beside_vertical = 0; //  세로방향 체크 변수
			check_horizontal = 0; // 가로방향 체크 변수
			check_beside_horizontal = 0; // 가로방향 체크 변수
			check_diagonal = 0;  // 일반대각선의 경우
			check_beside_diagonal = 0; // 일반대각선의 경우
			check_reverse_diagonal = 0; //일반대각선의 반대 경우
			check_reverse_beside_diagonal = 0; // 일반 대각선의 반대 경우

			if (pDoc->baduk[row][col] == 0) {
				for (i = 1; i < 6; i++) {
					if (col - i < 0) break; // 가로가 0 이면 반복탈출
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

void CMFCApplication3View::OffendWeight6_2(int o, int d) { //6목 방지코드
	CMFCApplication3Doc* pDoc = GetDocument();
	int i;
	int check_vertical = 0; // 세로방향 체크 변수
	int check_beside_vertical = 0; //  세로방향 체크 변수
	int check_horizontal = 0; // 가로방향 체크 변수
	int check_beside_horizontal = 0; // 가로방향 체크 변수
	int check_diagonal = 0;  // 일반대각선의 경우
	int check_beside_diagonal = 0; // 일반대각선의 경우
	int check_reverse_diagonal = 0; //일반대각선의 반대 경우
	int check_reverse_beside_diagonal = 0; // 일반 대각선의 반대 경우

	int check_vertical2 = 0; // 세로방향 체크 변수
	int check_beside_vertical2 = 0; //  세로방향 체크 변수
	int check_horizontal2 = 0; // 가로방향 체크 변수
	int check_beside_horizontal2 = 0; // 가로방향 체크 변수
	int check_diagonal2 = 0;  // 일반대각선의 경우
	int check_beside_diagonal2 = 0; // 일반대각선의 경우
	int check_reverse_diagonal2 = 0; //일반대각선의 반대 경우
	int check_reverse_beside_diagonal2 = 0; // 일반 대각선의 반대 경우
	int row, col;

	/* ***ㅇ** 인경우에 ㅇ 에 돌을 놓지않게함. 공격의경우*/
	for (row = 0; row < 19; row++)
		for (col = 0; col < 19; col++) {
			check_vertical = 0; //  세로방향 체크 변수
			check_beside_vertical = 0; //  세로방향 체크 변수
			check_horizontal = 0; // 가로방향 체크 변수
			check_beside_horizontal = 0; // 가로방향 체크 변수
			check_diagonal = 0;  // 일반대각선의 경우
			check_beside_diagonal = 0; // 일반대각선의 경우
			check_reverse_diagonal = 0; //일반대각선의 반대 경우
			check_reverse_beside_diagonal = 0; // 일반 대각선의 반대 경우


			check_vertical2 = 0; //  세로방향 체크 변수   	   2 개검사
			check_beside_vertical2 = 0; //  세로방향 체크 변수
			check_horizontal2 = 0; // 가로방향 체크 변수
			check_beside_horizontal2 = 0; // 가로방향 체크 변수
			check_diagonal2 = 0;  // 일반대각선의 경우
			check_beside_diagonal2 = 0; // 일반대각선의 경우
			check_reverse_diagonal2 = 0; //일반대각선의 반대 경우
			check_reverse_beside_diagonal2 = 0; // 일반 대각선의 반대 경우

			if (pDoc->baduk[row][col] == 0) {
				for (i = 1; i < 4; i++) {

					if (col - i < 0) break;
					if (pDoc->baduk[row][col - i] == o) { check_beside_horizontal++; }   // 3개체크
				}

				for (i = 1; i < 3; i++) {

					if (col - i < 0) break;
					if (pDoc->baduk[row][col - i] == o) { check_beside_horizontal2++; }  // 2개체크
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
	/* ***ㅇ** 인경우에 ㅇ 에 돌을 놓지않게함. 공격의경우*/

	/* ***ㅇ** 인경우에 ㅇ 에 돌을 놓지않게함. 수비의경우*/
	for (row = 0; row < 19; row++)
		for (col = 0; col < 19; col++) {
			check_vertical = 0; //  세로방향 체크 변수        3 개 검사
			check_beside_vertical = 0; //  세로방향 체크 변수
			check_horizontal = 0; // 가로방향 체크 변수
			check_beside_horizontal = 0; // 가로방향 체크 변수
			check_diagonal = 0;  // 일반대각선의 경우
			check_beside_diagonal = 0; // 일반대각선의 경우
			check_reverse_diagonal = 0; //일반대각선의 반대 경우
			check_reverse_beside_diagonal = 0; // 일반 대각선의 반대 경우

			check_vertical2 = 0; //  세로방향 체크 변수   	   2 개검사
			check_beside_vertical2 = 0; //  세로방향 체크 변수
			check_horizontal2 = 0; // 가로방향 체크 변수
			check_beside_horizontal2 = 0; // 가로방향 체크 변수
			check_diagonal2 = 0;  // 일반대각선의 경우
			check_beside_diagonal2 = 0; // 일반대각선의 경우
			check_reverse_diagonal2 = 0; //일반대각선의 반대 경우
			check_reverse_beside_diagonal2 = 0; // 일반 대각선의 반대 경우

			if (pDoc->baduk[row][col] == 0) {
				for (i = 1; i < 4; i++) {

					if (col - i < 0) break;
					if (pDoc->baduk[row][col - i] == d) { check_beside_horizontal++; }   // 3개체크
				}

				for (i = 1; i < 3; i++) {

					if (col - i < 0) break;
					if (pDoc->baduk[row][col - i] == d) { check_beside_horizontal2++; }  // 2개체크
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

void CMFCApplication3View::OffendWeight6_3(int o, int d) { //6목 방지코드
	CMFCApplication3Doc* pDoc = GetDocument();
	int i;
	int check_vertical = 0; // 세로방향 체크 변수             4개검사
	int check_beside_vertical = 0; //  세로방향 체크 변수
	int check_horizontal = 0; // 가로방향 체크 변수
	int check_beside_horizontal = 0; // 가로방향 체크 변수
	int check_diagonal = 0;  // 일반대각선의 경우
	int check_beside_diagonal = 0; // 일반대각선의 경우
	int check_reverse_diagonal = 0; //일반대각선의 반대 경우
	int check_reverse_beside_diagonal = 0; // 일반 대각선의 반대 경우

	int check_vertical2 = 0; // 세로방향 체크 변수            1 개검사
	int check_beside_vertical2 = 0; //  세로방향 체크 변수
	int check_horizontal2 = 0; // 가로방향 체크 변수
	int check_beside_horizontal2 = 0; // 가로방향 체크 변수
	int check_diagonal2 = 0;  // 일반대각선의 경우
	int check_beside_diagonal2 = 0; // 일반대각선의 경우
	int check_reverse_diagonal2 = 0; //일반대각선의 반대 경우
	int check_reverse_beside_diagonal2 = 0; // 일반 대각선의 반대 경우
	int row, col;

	/* ****ㅇ* 인경우에 ㅇ 에 돌을 놓지않게함. 공격의경우*/
	for (row = 0; row < 19; row++)
		for (col = 0; col < 19; col++) {
			check_vertical = 0; //  세로방향 체크 변수
			check_beside_vertical = 0; //  세로방향 체크 변수
			check_horizontal = 0; // 가로방향 체크 변수
			check_beside_horizontal = 0; // 가로방향 체크 변수
			check_diagonal = 0;  // 일반대각선의 경우
			check_beside_diagonal = 0; // 일반대각선의 경우
			check_reverse_diagonal = 0; //일반대각선의 반대 경우
			check_reverse_beside_diagonal = 0; // 일반 대각선의 반대 경우


			check_vertical2 = 0; //  세로방향 체크 변수   	   2 개검사
			check_beside_vertical2 = 0; //  세로방향 체크 변수
			check_horizontal2 = 0; // 가로방향 체크 변수
			check_beside_horizontal2 = 0; // 가로방향 체크 변수
			check_diagonal2 = 0;  // 일반대각선의 경우
			check_beside_diagonal2 = 0; // 일반대각선의 경우
			check_reverse_diagonal2 = 0; //일반대각선의 반대 경우
			check_reverse_beside_diagonal2 = 0; // 일반 대각선의 반대 경우

			if (pDoc->baduk[row][col] == 0) {
				for (i = 1; i < 5; i++) {

					if (col - i < 0) break;
					if (pDoc->baduk[row][col - i] == o) { check_beside_horizontal++; }   // 3개체크
				}

				for (i = 1; i < 2; i++) {

					if (col - i < 0) break;
					if (pDoc->baduk[row][col - i] == o) { check_beside_horizontal2++; }  // 2개체크
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
	/* ****ㅇ* 인경우에 ㅇ 에 돌을 놓지않게함. 공격의경우*/

	/* ****ㅇ* 인경우에 ㅇ 에 돌을 놓지않게함. 수비의경우*/
	for (row = 0; row < 19; row++)
		for (col = 0; col < 19; col++) {
			check_vertical = 0; //  세로방향 체크 변수        3 개 검사
			check_beside_vertical = 0; //  세로방향 체크 변수
			check_horizontal = 0; // 가로방향 체크 변수
			check_beside_horizontal = 0; // 가로방향 체크 변수
			check_diagonal = 0;  // 일반대각선의 경우
			check_beside_diagonal = 0; // 일반대각선의 경우
			check_reverse_diagonal = 0; //일반대각선의 반대 경우
			check_reverse_beside_diagonal = 0; // 일반 대각선의 반대 경우

			check_vertical2 = 0; //  세로방향 체크 변수   	   2 개검사
			check_beside_vertical2 = 0; //  세로방향 체크 변수
			check_horizontal2 = 0; // 가로방향 체크 변수
			check_beside_horizontal2 = 0; // 가로방향 체크 변수
			check_diagonal2 = 0;  // 일반대각선의 경우
			check_beside_diagonal2 = 0; // 일반대각선의 경우
			check_reverse_diagonal2 = 0; //일반대각선의 반대 경우
			check_reverse_beside_diagonal2 = 0; // 일반 대각선의 반대 경우

			if (pDoc->baduk[row][col] == 0) {
				for (i = 1; i < 5; i++) {

					if (col - i < 0) break;
					if (pDoc->baduk[row][col - i] == d) { check_beside_horizontal++; }   // 3개체크
				}

				for (i = 1; i < 2; i++) {

					if (col - i < 0) break;
					if (pDoc->baduk[row][col - i] == d) { check_beside_horizontal2++; }  // 2개체크
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
	/* ****ㅇ* 인경우에 ㅇ 에 돌을 놓지않게함. 수비의경우*/
}


void CMFCApplication3View::OffendWeight5(int o, int d) { // 네개의 돌이 연속될때
	CMFCApplication3Doc* pDoc = GetDocument();
	int i;
	int check_vertical = 0; // 세로방향 체크 변수
	int check_beside_vertical = 0; //  세로방향 체크 변수
	int check_horizontal = 0; // 가로방향 체크 변수
	int check_beside_horizontal = 0; // 가로방향 체크 변수
	int check_diagonal = 0;  // 일반대각선의 경우
	int check_beside_diagonal = 0; // 일반대각선의 경우
	int check_reverse_diagonal = 0; //일반대각선의 반대 경우
	int check_reverse_beside_diagonal = 0; // 일반 대각선의 반대 경우

	int row, col;
	/* ====================================================================================

	공격할돌이 4개 연속될때 5개가 되도록 함

	=====================================================================================*/
	for (row = 0; row < 19; row++)
		for (col = 0; col < 19; col++) {
			check_vertical = 0; //  세로방향 체크 변수
			check_beside_vertical = 0; //  세로방향 체크 변수
			check_horizontal = 0; // 가로방향 체크 변수
			check_beside_horizontal = 0; // 가로방향 체크 변수
			check_diagonal = 0;  // 일반대각선의 경우
			check_beside_diagonal = 0; // 일반대각선의 경우
			check_reverse_diagonal = 0; //일반대각선의 반대 경우
			check_reverse_beside_diagonal = 0; // 일반 대각선의 반대 경우

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

	공격할돌이 4개 연속될때 5개가 되도록 함 여기까지 //

	=====================================================================================*/


	/* ====================================================================================

	수비할돌이 4개 연속될때 방어하도록 함

	=====================================================================================*/
	for (row = 0; row < 19; row++)
		for (col = 0; col < 19; col++) {
			check_vertical = 0; //  세로방향 체크 변수
			check_beside_vertical = 0; //  세로방향 체크 변수
			check_horizontal = 0; // 가로방향 체크 변수
			check_beside_horizontal = 0; // 가로방향 체크 변수
			check_diagonal = 0;  // 일반대각선의 경우
			check_beside_diagonal = 0; // 일반대각선의 경우
			check_reverse_diagonal = 0; //일반대각선의 반대 경우
			check_reverse_beside_diagonal = 0; // 일반 대각선의 반대 경우

			if (pDoc->baduk[row][col] == 0) {
				for (i = 1; i < 5; i++) {
					if (col - i < 0) break; // 가로가 0 이면 반복탈출
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

	수비할돌이 4개 연속될때 방어하도록 함 여기까지

	=====================================================================================*/
}

void CMFCApplication3View::OffendWeight5_2(int o, int d) { // 2개 2개 나눠져 있을때
	CMFCApplication3Doc* pDoc = GetDocument();
	int i;
	int check_vertical = 0; // 세로방향 체크 변수
	int check_beside_vertical = 0; //  세로방향 체크 변수
	int check_horizontal = 0; // 가로방향 체크 변수
	int check_beside_horizontal = 0; // 가로방향 체크 변수
	int check_diagonal = 0;  // 일반대각선의 경우
	int check_beside_diagonal = 0; // 일반대각선의 경우
	int check_reverse_diagonal = 0; //일반대각선의 반대 경우
	int check_reverse_beside_diagonal = 0; // 일반 대각선의 반대 경우
	int check_point1 = 0; // 포인트
	int check_point2 = 0;
	int row, col;

	/* ====================================================================================

	공격할돌이 ㅇㅇ*ㅇㅇ  일때 *에 돌을 놓게함

	=====================================================================================*/
	for (row = 0; row < 19; row++)
		for (col = 0; col < 19; col++) {
			check_vertical = 0; //  세로방향 체크 변수
			check_beside_vertical = 0; //  세로방향 체크 변수
			check_horizontal = 0; // 가로방향 체크 변수
			check_beside_horizontal = 0; // 가로방향 체크 변수
			check_diagonal = 0;  // 일반대각선의 경우
			check_beside_diagonal = 0; // 일반대각선의 경우
			check_reverse_diagonal = 0; //일반대각선의 반대 경우
			check_reverse_beside_diagonal = 0; // 일반 대각선의 반대 경우

			if (pDoc->baduk[row][col] == 0) {
				for (i = 1; i < 3; i++) {
					if (col - i < 0) break; // 가로가 0 이면 반복탈출
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

	공격할돌이 ㅇㅇ*ㅇㅇ  일때 *에 돌을 놓게함 여기까지

	=====================================================================================*/

	/* ====================================================================================

	수비할돌이 **ㅇ**  일때 ㅇ에 돌을 놓게함

	=====================================================================================*/
	for (row = 0; row < 19; row++)
		for (col = 0; col < 19; col++) {
			check_vertical = 0; //  세로방향 체크 변수
			check_beside_vertical = 0; //  세로방향 체크 변수
			check_horizontal = 0; // 가로방향 체크 변수
			check_beside_horizontal = 0; // 가로방향 체크 변수
			check_diagonal = 0;  // 일반대각선의 경우
			check_beside_diagonal = 0; // 일반대각선의 경우
			check_reverse_diagonal = 0; //일반대각선의 반대 경우
			check_reverse_beside_diagonal = 0; // 일반 대각선의 반대 경우

			if (pDoc->baduk[row][col] == 0) {
				for (i = 1; i < 3; i++) {
					if (col - i < 0) break; // 가로가 0 이면 반복탈출
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

	수비할돌이 **ㅇ**  일때 ㅇ에 돌을 놓게함 여기까지

	=====================================================================================*/
}

void CMFCApplication3View::OffendWeight5_3(int o, int d) { // 3개 1개 나눠져 있을때
	CMFCApplication3Doc* pDoc = GetDocument();
	int i;
	int check_vertical = 0; // 세로방향 체크 변수
	int check_beside_vertical = 0; //  세로방향 체크 변수
	int check_horizontal = 0; // 가로방향 체크 변수
	int check_beside_horizontal = 0; // 가로방향 체크 변수
	int check_diagonal = 0;  // 일반대각선의 경우
	int check_beside_diagonal = 0; // 일반대각선의 경우
	int check_reverse_diagonal = 0; //일반대각선의 반대 경우
	int check_reverse_beside_diagonal = 0; // 일반 대각선의 반대 경우
	int check_vertical_point = 0; // 포인트
	int check_beside_vertical_point = 0;
	int check_horizontal_point = 0;
	int check_beside_horizontal_point = 0;
	int check_diagonal_point = 0;
	int check_beside_diagonal_point = 0;
	int check_reverse_diagonal_point = 0;
	int check_reverse_beside_diagonal_point = 0;

	int row, col;

	/* ====================================================================================

	공격할돌이 ㅇㅇㅇ*ㅇ 일때 *에 돌을 놓게함

	=====================================================================================*/
	for (row = 0; row < 19; row++)
		for (col = 0; col < 19; col++) {
			check_vertical = 0; //  세로방향 체크 변수
			check_beside_vertical = 0; //  세로방향 체크 변수
			check_horizontal = 0; // 가로방향 체크 변수
			check_beside_horizontal = 0; // 가로방향 체크 변수
			check_diagonal = 0;  // 일반대각선의 경우
			check_beside_diagonal = 0; // 일반대각선의 경우
			check_reverse_diagonal = 0; //일반대각선의 반대 경우
			check_reverse_beside_diagonal = 0; // 일반 대각선의 반대 경우

			int check_vertical_point = 0; // 포인트
			int check_beside_vertical_point = 0;
			int check_horizontal_point = 0;
			int check_beside_horizontal_point = 0;
			int check_diagonal_point = 0;
			int check_beside_diagonal_point = 0;
			int check_reverse_diagonal_point = 0;
			int check_reverse_beside_diagonal_point = 0;

			if (pDoc->baduk[row][col] == 0) {
				for (i = 1; i < 4; i++) {
					if (col - i < 0) break;  // 가로가 0 이면 반복탈출
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

	공격할돌이 ㅇㅇㅇ*ㅇ 일때 *에 돌을 놓게함 여기까지

	=====================================================================================*/



	/* ====================================================================================

	수비할돌이 ***ㅇ* 일때 ㅇ에 돌을 놓게함

	=====================================================================================*/
	for (row = 0; row < 19; row++)
		for (col = 0; col < 19; col++) {
			check_vertical = 0; //  세로방향 체크 변수
			check_beside_vertical = 0; //  세로방향 체크 변수
			check_horizontal = 0; // 가로방향 체크 변수
			check_beside_horizontal = 0; // 가로방향 체크 변수
			check_diagonal = 0;  // 일반대각선의 경우
			check_beside_diagonal = 0; // 일반대각선의 경우
			check_reverse_diagonal = 0; //일반대각선의 반대 경우
			check_reverse_beside_diagonal = 0; // 일반 대각선의 반대 경우

			check_vertical_point = 0; // 포인트
			check_beside_vertical_point = 0;
			check_horizontal_point = 0;
			check_beside_horizontal_point = 0;
			check_diagonal_point = 0;
			check_beside_diagonal_point = 0;
			check_reverse_diagonal_point = 0;
			check_reverse_beside_diagonal_point = 0;

			if (pDoc->baduk[row][col] == 0) {
				for (i = 1; i < 4; i++) {

					if (col - i < 0) break; // 가로가 0 이면 반복탈출
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

	수비할돌이 ***ㅇ* 일때 ㅇ에 돌을 놓게함 여기까지

	=====================================================================================*/
}


void CMFCApplication3View::OffendWeight4(int o, int d) { //3개가 같이 놓여있을때
	CMFCApplication3Doc* pDoc = GetDocument();
	int i;
	int check_vertical = 0; // 세로방향 체크 변수
	int check_beside_vertical = 0; //  세로방향 체크 변수
	int check_horizontal = 0; // 가로방향 체크 변수
	int check_beside_horizontal = 0; // 가로방향 체크 변수
	int check_diagonal = 0;  // 일반대각선의 경우
	int check_beside_diagonal = 0; // 일반대각선의 경우
	int check_reverse_diagonal = 0; //일반대각선의 반대 경우
	int check_reverse_beside_diagonal = 0; // 일반 대각선의 반대 경우
	int row, col;

	int defend_four_point[8]; //4번쨰칸이 막혔는지 조사 

	int defend_one_point[8];  //1번쨰 칸이 막혔는지 조사

	int defend_five_point[8]; // 5번째 칸이 막혔는지 조사
							  /* 배열에대하여
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

							  공격할돌이 *ㅇㅇㅇ* 일때 *의 가중치

							  =====================================================================================*/
	for (row = 0; row < 19; row++)
		for (col = 0; col < 19; col++) {
			check_vertical = 0; //  세로방향 체크 변수
			check_beside_vertical = 0; //  세로방향 체크 변수
			check_horizontal = 0; // 가로방향 체크 변수
			check_beside_horizontal = 0; // 가로방향 체크 변수
			check_diagonal = 0;  // 일반대각선의 경우
			check_beside_diagonal = 0; // 일반대각선의 경우
			check_reverse_diagonal = 0; //일반대각선의 반대 경우
			check_reverse_beside_diagonal = 0; // 일반 대각선의 반대 경우

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
					if (col - i < 0) break; // 가로가 0 이면 반복탈출
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
					else if ((defend_four_point[1] == 0 || defend_five_point[1] == 0) && defend_one_point[0] == 1);              // ㅁ***ㅇㅁ  일때 ㅇ에 못놓게함
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

	공격할돌이 *ㅇㅇㅇ* 일때 *의 가중치 여기까지

	=====================================================================================*/

	/* ====================================================================================

	수비할돌이 ㅇ***ㅇ 일때 ㅇ의 가중치

	=====================================================================================*/
	for (row = 0; row < 19; row++)
		for (col = 0; col < 19; col++) {
			check_vertical = 0; //  세로방향 체크 변수
			check_beside_vertical = 0; //  세로방향 체크 변수
			check_horizontal = 0; // 가로방향 체크 변수
			check_beside_horizontal = 0; // 가로방향 체크 변수
			check_diagonal = 0;  // 일반대각선의 경우
			check_beside_diagonal = 0; // 일반대각선의 경우
			check_reverse_diagonal = 0; //일반대각선의 반대 경우
			check_reverse_beside_diagonal = 0; // 일반 대각선의 반대 경우

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

	수비할돌이 ㅇ***ㅇ 일때 ㅇ의 가중치 여기까지

	=====================================================================================*/
}

void CMFCApplication3View::OffendWeight4_2(int o, int d) { // 2개 1개 나눠져 있을때
	CMFCApplication3Doc* pDoc = GetDocument();
	int i;
	int check_vertical = 0; // 세로방향 체크 변수
	int check_beside_vertical = 0; //  세로방향 체크 변수
	int check_horizontal = 0; // 가로방향 체크 변수
	int check_beside_horizontal = 0; // 가로방향 체크 변수
	int check_diagonal = 0;  // 일반대각선의 경우
	int check_beside_diagonal = 0; // 일반대각선의 경우
	int check_reverse_diagonal = 0; //일반대각선의 반대 경우
	int check_reverse_beside_diagonal = 0; // 일반 대각선의 반대 경우

	int check_vertical_point = 0; // 포인트
	int check_beside_vertical_point = 0;
	int check_horizontal_point = 0;
	int check_beside_horizontal_point = 0;
	int check_diagonal_point = 0;
	int check_beside_diagonal_point = 0;
	int check_reverse_diagonal_point = 0;
	int check_reverse_beside_diagonal_point = 0;

	int check_vertical_opposite_point3 = 0; // 반대편 포인트
	int check_beside_vertical_opposite_point3 = 0;
	int check_horizontal_opposite_point3 = 0;
	int check_beside_horizontal_opposite_point3 = 0;
	int check_diagonal_opposite_point3 = 0;
	int check_beside_diagonal_opposite_point3 = 0;
	int check_reverse_diagonal_opposite_point3 = 0;
	int check_reverse_beside_diagonal_opposite_point3 = 0;

	int check_vertical_opposite_point2 = 0; // 반대편 포인트2
	int check_beside_vertical_opposite_point2 = 0;
	int check_horizontal_opposite_point2 = 0;
	int check_beside_horizontal_opposite_point2 = 0;
	int check_diagonal_opposite_point2 = 0;
	int check_beside_diagonal_opposite_point2 = 0;
	int check_reverse_diagonal_opposite_point2 = 0;
	int check_reverse_beside_diagonal_opposite_point2 = 0;

	int row, col;

	/* ====================================================================================

	공격할돌이 **ㅇ* 일때 ㅇ의 가중치

	=====================================================================================*/
	for (row = 0; row < 19; row++)
		for (col = 0; col < 19; col++) {
			check_vertical = 0; //  세로방향 체크 변수
			check_beside_vertical = 0; //  세로방향 체크 변수
			check_horizontal = 0; // 가로방향 체크 변수
			check_beside_horizontal = 0; // 가로방향 체크 변수
			check_diagonal = 0;  // 일반대각선의 경우
			check_beside_diagonal = 0; // 일반대각선의 경우
			check_reverse_diagonal = 0; //일반대각선의 반대 경우
			check_reverse_beside_diagonal = 0; // 일반 대각선의 반대 경우

			check_vertical_point = 0; // 3번째에 상대돌이 있는경우
			check_beside_vertical_point = 0;
			check_horizontal_point = 0;
			check_beside_horizontal_point = 0;
			check_diagonal_point = 0;
			check_beside_diagonal_point = 0;
			check_reverse_diagonal_point = 0;
			check_reverse_beside_diagonal_point = 0;

			check_vertical_opposite_point2 = 0; // 2번째에 상대돌이 있는경우
			check_beside_vertical_opposite_point2 = 0;
			check_horizontal_opposite_point2 = 0;
			check_beside_horizontal_opposite_point2 = 0;
			check_diagonal_opposite_point2 = 0;
			check_beside_diagonal_opposite_point2 = 0;
			check_reverse_diagonal_opposite_point2 = 0;
			check_reverse_beside_diagonal_opposite_point2 = 0;

			check_vertical_opposite_point3 = 0; // 3번째에 상대돌이 있는경우
			check_beside_vertical_opposite_point3 = 0;
			check_horizontal_opposite_point3 = 0;
			check_beside_horizontal_opposite_point3 = 0;
			check_diagonal_opposite_point3 = 0;
			check_beside_diagonal_opposite_point3 = 0;
			check_reverse_diagonal_opposite_point3 = 0;
			check_reverse_beside_diagonal_opposite_point3 = 0;

			if (pDoc->baduk[row][col] == 0) {
				for (i = 1; i < 3; i++) {
					if (col - i < 0) break;  // 가로가 0 이면 반복탈출
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
			check_vertical = 0; //  세로방향 체크 변수
			check_beside_vertical = 0; //  세로방향 체크 변수
			check_horizontal = 0; // 가로방향 체크 변수
			check_beside_horizontal = 0; // 가로방향 체크 변수
			check_diagonal = 0;  // 일반대각선의 경우
			check_beside_diagonal = 0; // 일반대각선의 경우
			check_reverse_diagonal = 0; //일반대각선의 반대 경우
			check_reverse_beside_diagonal = 0; // 일반 대각선의 반대 경우

			check_vertical_point = 0; // 포인트
			check_beside_vertical_point = 0;
			check_horizontal_point = 0;
			check_beside_horizontal_point = 0;
			check_diagonal_point = 0;
			check_beside_diagonal_point = 0;
			check_reverse_diagonal_point = 0;
			check_reverse_beside_diagonal_point = 0;

			check_vertical_opposite_point2 = 0; // 2번째에 상대돌이 있는경우
			check_beside_vertical_opposite_point2 = 0;
			check_horizontal_opposite_point2 = 0;
			check_beside_horizontal_opposite_point2 = 0;
			check_diagonal_opposite_point2 = 0;
			check_beside_diagonal_opposite_point2 = 0;
			check_reverse_diagonal_opposite_point2 = 0;
			check_reverse_beside_diagonal_opposite_point2 = 0;

			check_vertical_opposite_point3 = 0; // 3번째에 상대돌이 있는경우
			check_beside_vertical_opposite_point3 = 0;
			check_horizontal_opposite_point3 = 0;
			check_beside_horizontal_opposite_point3 = 0;
			check_diagonal_opposite_point3 = 0;
			check_beside_diagonal_opposite_point3 = 0;
			check_reverse_diagonal_opposite_point3 = 0;
			check_reverse_beside_diagonal_opposite_point3 = 0;

			if (pDoc->baduk[row][col] == 0) {
				for (i = 1; i < 3; i++) {
					if (col - i < 0) break;  // 가로가 0 이면 반복탈출
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

	공격할돌이 **ㅇ* 일때 ㅇ의 가중치 여기까지

	=====================================================================================*/
}






void CMFCApplication3View::OffendWeight(int o, int d) { // 기본적인 가중치를 둔다. 돌이 연속될경우 더 큰 가중치를 둔다.
	CMFCApplication3Doc* pDoc = GetDocument();
	int i;
	int check_vertical = 0; // 세로방향 체크 변수
	int check_beside_vertical = 0; // 세로방향 체크 변수
	int check_horizontal= 0; //가로방향 체크 변수
	int check_beside_horizontal = 0; // 가로방향 체크 변수
	int check_diagonal = 0;  // 일반대각선의 경우
	int check_beside_diagonal = 0; // 일반대각선의 경우
	int check_reverse_diagonal = 0; //일반대각선의 반대 경우
	int check_reverse_beside_diagonal = 0; // 일반 대각선의 반대 경우
	int row, col;

	for (row = 0; row < 19; row++)
		for (col = 0; col < 19; col++) {
			check_vertical = 0; // 3x3 세로방향 체크 변수
			check_beside_vertical = 0; // 3x3 세로방향 체크 변수
			check_horizontal = 0; //3x3 가로방향 체크 변수
			check_beside_horizontal = 0; //3x3 가로방향 체크 변수
			check_diagonal = 0;  // 일반대각선의 경우
			check_beside_diagonal = 0; // 일반대각선의 경우
			check_reverse_diagonal = 0; //일반대각선의 반대 경우
			check_reverse_beside_diagonal = 0; // 일반 대각선의 반대 경우

			if (pDoc->baduk[row][col] == 0) {
				for (i = 1; i < 5; i++) {
					if (col - i < 0) break; // 가로가 0 이면 반복탈출
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


void CMFCApplication3View::defendWeight(int o, int d) { // 상대를 고려한 기본적인 가중치를 둔다.
	CMFCApplication3Doc* pDoc = GetDocument();
	int i;
	int check_vertical = 0; // 세로방향 체크 변수
	int check_beside_vertical = 0; // 세로방향 체크 변수
	int check_horizontal = 0; //가로방향 체크 변수
	int check_beside_horizontal = 0; // 가로방향 체크 변수
	int check_diagonal = 0;  // 일반대각선의 경우
	int check_beside_diagonal = 0; // 일반대각선의 경우
	int check_reverse_diagonal = 0; //일반대각선의 반대 경우
	int check_reverse_beside_diagonal = 0; // 일반 대각선의 반대 경우
	int row, col;

	for (row = 0; row < 19; row++)
		for (col = 0; col < 19; col++) {
			check_vertical = 0; // 3x3 세로방향 체크 변수
			check_beside_vertical = 0; // 3x3 세로방향 체크 변수
			check_horizontal = 0; //3x3 가로방향 체크 변수
			check_beside_horizontal = 0; //3x3 가로방향 체크 변수
			check_diagonal = 0;  // 일반대각선의 경우
			check_beside_diagonal = 0; // 일반대각선의 경우
			check_reverse_diagonal = 0; //일반대각선의 반대 경우
			check_reverse_beside_diagonal = 0; // 일반 대각선의 반대 경우

			if (pDoc->baduk[row][col] == 0) {
				for (i = 1; i < 3; i++) {
					if (col - i < 0) break; // 가로가 0 이면 반복탈출
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


			// 33 시작

			//==============둔 위치를 중심으로 33 가로 줄 체크===============//

			if (pDoc->baduk[row + 1][col] == d) {			//둔 위치부터 오른쪽 체크 x?
				if (pDoc->baduk[row - 1][col] == d);			//4가 있는지 체크 시작.
				else if (pDoc->baduk[row - 1][col] == o) {			//  *x-   상태
					if (pDoc->baduk[row - 2][col] == d);
					else if (pDoc->baduk[row - 2][col] == o) {			//   **x- 상태
						if (pDoc->baduk[row - 3][col] == d);
						else if (pDoc->baduk[row - 3][col] == o) {			// ***x- 완성
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
			else if (pDoc->baduk[row + 1][col] == o) {			//둔 위치 부터 오른쪽 체크 x*?
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
				else if (pDoc->baduk[row + 2][col] == o) {			//x** 상태
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
									if (pDoc->baduk[row + 4][col] == 0) three_by_three_flag++; // 흰돌 양쪽을 막을 가능성 체크
								}
								else if (pDoc->baduk[row - 2][col] == o)four_by_three_flag++;
								else if (pDoc->baduk[row - 2][col] == 0)three_by_three_flag++; // x**검증 완료
							}
						}
						else if (pDoc->baduk[row + 4][col] == o)four_by_three_flag++;
					}
				}
				else if (pDoc->baduk[row + 2][col] == 0) {		//둔 위치부터 오른쪽 x* ?
					if (pDoc->baduk[row + 3][col] == d || pDoc->baduk[row + 3][col] == 0) {		//x*   상태
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
			else if (pDoc->baduk[row + 1][col] == 0) {			//x ? 상태.
				if (pDoc->baduk[row + 2][col] == d || pDoc->baduk[row + 2][col] == 0) {		//   x 좌측 검사 시작.
					if (pDoc->baduk[row - 1][col] == d);
					else if (pDoc->baduk[row - 1][col] == o) {				//   *x 상태.
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
					else if (pDoc->baduk[row - 1][col] == 0) {		// ? x 상태
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
					else if (pDoc->baduk[row + 3][col] == 0) {		// x *  상태
						if (pDoc->baduk[row + 4][col] == d || pDoc->baduk[row + 4][col] == 0) {
							if (pDoc->baduk[row - 1][col] == d);
							else if (pDoc->baduk[row - 1][col] == o) {		// *x * 상태
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

			// ====================== 가로줄 체크 끝 ====================== //



			//==============둔 위치를 중심으로 33 세로 줄 체크===============//

			if (pDoc->baduk[row][col + 1] == d) {			//둔 위치부터 오른쪽 체크 x?
				if (pDoc->baduk[row][col - 1] == d);			//4가 있는지 체크 시작.
				else if (pDoc->baduk[row][col - 1] == o) {			//  *x-   상태
					if (pDoc->baduk[row][col - 2] == d);
					else if (pDoc->baduk[row][col - 2] == o) {			//   **x- 상태
						if (pDoc->baduk[row][col - 3] == d);
						else if (pDoc->baduk[row][col - 3] == o) {			// ***x- 완성
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
			else if (pDoc->baduk[row][col + 1] == o) {			//둔 위치 부터 오른쪽 체크 x*?
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
				else if (pDoc->baduk[row][col + 2] == o) {			//x** 상태
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
									if (pDoc->baduk[row][col + 4] == 0) three_by_three_flag++; // 흰돌 양쪽을 막을 가능성 체크
								}
								else if (pDoc->baduk[row][col - 2] == o)four_by_three_flag++;
								else if (pDoc->baduk[row][col - 2] == 0)three_by_three_flag++; // x**검증 완료
							}
						}
						else if (pDoc->baduk[row][col + 4] == o)four_by_three_flag++;
					}
				}
				else if (pDoc->baduk[row][col + 2] == 0) {		//둔 위치부터 오른쪽 x* ?
					if (pDoc->baduk[row][col + 3] == d || pDoc->baduk[row][col + 3] == 0) {		//x*   상태
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
			else if (pDoc->baduk[row][col + 1] == 0) {			//x ? 상태.
				if (pDoc->baduk[row][col + 2] == d || pDoc->baduk[row][col + 2] == 0) {		//   x 좌측 검사 시작.
					if (pDoc->baduk[row][col - 1] == d);
					else if (pDoc->baduk[row][col - 1] == o) {				//   *x 상태.
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
					else if (pDoc->baduk[row][col - 1] == 0) {		// ? x 상태
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
					else if (pDoc->baduk[row][col + 3] == 0) {		// x *  상태
						if (pDoc->baduk[row][col + 4] == d || pDoc->baduk[row][col + 4] == 0) {
							if (pDoc->baduk[row][col - 1] == d);
							else if (pDoc->baduk[row][col - 1] == o) {		// *x * 상태
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

			// ====================== 세로줄 체크 끝 ====================== //




			//==============둔 위치를 중심으로 좌상 --> 우하 대각선 줄 체크===============//

			if (pDoc->baduk[row + 1][col + 1] == d);			//둔 위치부터 오른쪽 체크 x?
			else if (pDoc->baduk[row + 1][col + 1] == o) {			//둔 위치 부터 오른쪽 체크 x*?
				if (pDoc->baduk[row + 2][col + 2] == d);
				else if (pDoc->baduk[row + 2][col + 2] == o) {			//x** 상태
					if (pDoc->baduk[row + 3][col + 3] == d);
					else if (pDoc->baduk[row + 3][col + 3] == o) four_by_three_flag++;
					else if (pDoc->baduk[row + 3][col + 3] == 0) {
						if (pDoc->baduk[row + 4][col + 4] == d || pDoc->baduk[row + 4][col + 4] == 0) {
							if (pDoc->baduk[row - 1][col - 1] == d);
							else if (pDoc->baduk[row - 1][col - 1] == o) four_by_three_flag++;
							else if (pDoc->baduk[row - 1][col - 1] == 0) {
								if (pDoc->baduk[row - 2][col - 2] == d) {
									if (pDoc->baduk[row + 4][col + 4] == 0) three_by_three_flag++; // 흰돌 양쪽을 막을 가능성 체크
								}
								else if (pDoc->baduk[row - 2][col - 2] == o) four_by_three_flag++;
								else if (pDoc->baduk[row - 2][col - 2] == 0) three_by_three_flag++; // x**검증 완료
							}
						}
						else if (pDoc->baduk[row + 4][col + 4] == o) four_by_three_flag++;
					}
				}
				else if (pDoc->baduk[row + 2][col + 2] == 0) {		//둔 위치부터 오른쪽 x* ?
					if (pDoc->baduk[row + 3][col + 3] == d || pDoc->baduk[row + 3][col + 3] == 0) {		//x*   상태
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
			else if (pDoc->baduk[row + 1][col + 1] == 0) {			//x ? 상태.
				if (pDoc->baduk[row + 2][col + 2] == d || pDoc->baduk[row + 2][col + 2] == 0) {		//   x 좌측 검사 시작.
					if (pDoc->baduk[row - 1][col - 1] == d);
					else if (pDoc->baduk[row - 1][col - 1] == o) {				//   *x 상태.
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
					else if (pDoc->baduk[row - 1][col - 1] == 0) {		// ? x 상태
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
					else if (pDoc->baduk[row + 3][col + 3] == 0) {		// x *  상태
						if (pDoc->baduk[row + 4][col + 4] == d || pDoc->baduk[row + 4][col + 4] == 0) {
							if (pDoc->baduk[row - 1][col - 1] == d);
							else if (pDoc->baduk[row - 1][col - 1] == o) {		// *x * 상태
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

			// ====================== 좌상 우하 대각선 체크 끝 ====================== //




			//==============둔 위치를 중심으로 우상 --> 좌하 대각선 줄 체크===============//

			if (pDoc->baduk[row + 1][col - 1] == d);			//둔 위치부터 오른쪽 체크 x?
			else if (pDoc->baduk[row + 1][col - 1] == o) {			//둔 위치 부터 오른쪽 체크 x*?
				if (pDoc->baduk[row + 2][col - 2] == d);
				else if (pDoc->baduk[row + 2][col - 2] == o) {			//x** 상태
					if (pDoc->baduk[row + 3][col - 3] == d);
					else if (pDoc->baduk[row + 3][col - 3] == o) four_by_three_flag++;
					else if (pDoc->baduk[row + 3][col - 3] == 0) {
						if (pDoc->baduk[row + 4][col - 4] == d || pDoc->baduk[row + 4][col - 4] == 0) {
							if (pDoc->baduk[row - 1][col + 1] == d);
							else if (pDoc->baduk[row - 1][col + 1] == o) four_by_three_flag++;
							else if (pDoc->baduk[row - 1][col + 1] == 0) {
								if (pDoc->baduk[row - 2][col + 2] == d) {
									if (pDoc->baduk[row + 4][col - 4] == 0) three_by_three_flag++; // 흰돌 양쪽을 막을 가능성 체크
								}
								else if (pDoc->baduk[row - 2][col + 2] == o) four_by_three_flag++;
								else if (pDoc->baduk[row - 2][col + 2] == 0) three_by_three_flag++; // x**검증 완료
							}
						}
						else if (pDoc->baduk[row + 4][col - 4] == o) four_by_three_flag++;
					}
				}
				else if (pDoc->baduk[row + 2][col - 2] == 0) {		//둔 위치부터 오른쪽 x* ?
					if (pDoc->baduk[row + 3][col - 3] == d || pDoc->baduk[row + 3][col - 3] == 0) {		//x*   상태
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
			else if (pDoc->baduk[row + 1][col - 1] == 0) {			//x ? 상태.
				if (pDoc->baduk[row + 2][col - 2] == d || pDoc->baduk[row + 2][col - 2] == 0) {		//   x 좌측 검사 시작.
					if (pDoc->baduk[row - 1][col + 1] == d);
					else if (pDoc->baduk[row - 1][col + 1] == o) {				//   *x 상태.
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
					else if (pDoc->baduk[row - 1][col + 1] == 0) {		// ? x 상태
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
					else if (pDoc->baduk[row + 3][col - 3] == 0) {		// x *  상태
						if (pDoc->baduk[row + 4][col - 4] == d || pDoc->baduk[row + 4][col - 4] == 0) {
							if (pDoc->baduk[row - 1][col + 1] == d);
							else if (pDoc->baduk[row - 1][col + 1] == o) {		// *x * 상태
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

			// ====================== 우상 좌하 대각선 체크 끝 ====================== //



			// 33 끝

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


			// 33 시작

			//==============둔 위치를 중심으로 33 가로 줄 체크===============//

			if (pDoc->baduk[row + 1][col] == d) {			//둔 위치부터 오른쪽 체크 x?
				if (pDoc->baduk[row - 1][col] == d);			//4가 있는지 체크 시작.
				else if (pDoc->baduk[row - 1][col] == o) {			//  *x-   상태
					if (pDoc->baduk[row - 2][col] == d);
					else if (pDoc->baduk[row - 2][col] == o) {			//   **x- 상태
						if (pDoc->baduk[row - 3][col] == d);
						else if (pDoc->baduk[row - 3][col] == o) {			// ***x- 완성
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
			else if (pDoc->baduk[row + 1][col] == o) {			//둔 위치 부터 오른쪽 체크 x*?
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
				else if (pDoc->baduk[row + 2][col] == o) {			//x** 상태
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
									if (pDoc->baduk[row + 4][col] == 0) three_by_three_flag++; // 흰돌 양쪽을 막을 가능성 체크
								}
								else if (pDoc->baduk[row - 2][col] == o)four_by_three_flag++;
								else if (pDoc->baduk[row - 2][col] == 0)three_by_three_flag++; // x**검증 완료
							}
						}
						else if (pDoc->baduk[row + 4][col] == o)four_by_three_flag++;
					}
				}
				else if (pDoc->baduk[row + 2][col] == 0) {		//둔 위치부터 오른쪽 x* ?
					if (pDoc->baduk[row + 3][col] == d || pDoc->baduk[row + 3][col] == 0) {		//x*   상태
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
			else if (pDoc->baduk[row + 1][col] == 0) {			//x ? 상태.
				if (pDoc->baduk[row + 2][col] == d || pDoc->baduk[row + 2][col] == 0) {		//   x 좌측 검사 시작.
					if (pDoc->baduk[row - 1][col] == d);
					else if (pDoc->baduk[row - 1][col] == o) {				//   *x 상태.
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
					else if (pDoc->baduk[row - 1][col] == 0) {		// ? x 상태
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
					else if (pDoc->baduk[row + 3][col] == 0) {		// x *  상태
						if (pDoc->baduk[row + 4][col] == d || pDoc->baduk[row + 4][col] == 0) {
							if (pDoc->baduk[row - 1][col] == d);
							else if (pDoc->baduk[row - 1][col] == o) {		// *x * 상태
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

			// ====================== 가로줄 체크 끝 ====================== //



			//==============둔 위치를 중심으로 33 세로 줄 체크===============//

			if (pDoc->baduk[row][col + 1] == d);			//둔 위치부터 오른쪽 체크 x?
			else if (pDoc->baduk[row][col + 1] == o) {			//둔 위치 부터 오른쪽 체크 x*?
				if (pDoc->baduk[row][col + 2] == d);
				else if (pDoc->baduk[row][col + 2] == o) {			//x** 상태
					if (pDoc->baduk[row][col + 3] == d);
					else if (pDoc->baduk[row][col + 3] == o) four_by_three_flag++;
					else if (pDoc->baduk[row][col + 3] == 0) {
						if (pDoc->baduk[row][col + 4] == d || pDoc->baduk[row][col + 4] == 0) {
							if (pDoc->baduk[row][col - 1] == d);
							else if (pDoc->baduk[row][col - 1] == o) four_by_three_flag++;
							else if (pDoc->baduk[row][col - 1] == 0) {
								if (pDoc->baduk[row][col - 2] == d) {
									if (pDoc->baduk[row][col + 4] == 0) three_by_three_flag++; // 흰돌 양쪽을 막을 가능성 체크
								}
								else if (pDoc->baduk[row][col - 2] == o) four_by_three_flag++;
								else if (pDoc->baduk[row][col - 2] == 0)three_by_three_flag++; // x**검증 완료
							}
						}
						else if (pDoc->baduk[row][col + 4] == o) four_by_three_flag++;
					}
				}
				else if (pDoc->baduk[row][col + 2] == 0) {		//둔 위치부터 오른쪽 x* ?
					if (pDoc->baduk[row][col + 3] == d || pDoc->baduk[row][col + 3] == 0) {		//x*   상태
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
			else if (pDoc->baduk[row][col + 1] == 0) {			//x ? 상태.
				if (pDoc->baduk[row][col + 2] == d || pDoc->baduk[row][col + 2] == 0) {		//   x 좌측 검사 시작.
					if (pDoc->baduk[row][col - 1] == d);
					else if (pDoc->baduk[row][col - 1] == o) {				//   *x 상태.
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
					else if (pDoc->baduk[row][col - 1] == 0) {		// ? x 상태
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
					else if (pDoc->baduk[row][col + 3] == 0) {		// x *  상태
						if (pDoc->baduk[row][col + 4] == d || pDoc->baduk[row][col + 4] == 0) {
							if (pDoc->baduk[row][col - 1] == d);
							else if (pDoc->baduk[row][col - 1] == o) {		// *x * 상태
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

			// ====================== 세로줄 체크 끝 ====================== //




			//==============둔 위치를 중심으로 좌상 --> 우하 대각선 줄 체크===============//

			if (pDoc->baduk[row + 1][col + 1] == d);			//둔 위치부터 오른쪽 체크 x?
			else if (pDoc->baduk[row + 1][col + 1] == o) {			//둔 위치 부터 오른쪽 체크 x*?
				if (pDoc->baduk[row + 2][col + 2] == d);
				else if (pDoc->baduk[row + 2][col + 2] == o) {			//x** 상태
					if (pDoc->baduk[row + 3][col + 3] == d);
					else if (pDoc->baduk[row + 3][col + 3] == o) four_by_three_flag++;
					else if (pDoc->baduk[row + 3][col + 3] == 0) {
						if (pDoc->baduk[row + 4][col + 4] == d || pDoc->baduk[row + 4][col + 4] == 0) {
							if (pDoc->baduk[row - 1][col - 1] == d);
							else if (pDoc->baduk[row - 1][col - 1] == o) four_by_three_flag++;
							else if (pDoc->baduk[row - 1][col - 1] == 0) {
								if (pDoc->baduk[row - 2][col - 2] == d) {
									if (pDoc->baduk[row + 4][col + 4] == 0) three_by_three_flag++; // 흰돌 양쪽을 막을 가능성 체크
								}
								else if (pDoc->baduk[row - 2][col - 2] == o) four_by_three_flag++;
								else if (pDoc->baduk[row - 2][col - 2] == 0) three_by_three_flag++; // x**검증 완료
							}
						}
						else if (pDoc->baduk[row + 4][col + 4] == o) four_by_three_flag++;
					}
				}
				else if (pDoc->baduk[row + 2][col + 2] == 0) {		//둔 위치부터 오른쪽 x* ?
					if (pDoc->baduk[row + 3][col + 3] == d || pDoc->baduk[row + 3][col + 3] == 0) {		//x*   상태
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
			else if (pDoc->baduk[row + 1][col + 1] == 0) {			//x ? 상태.
				if (pDoc->baduk[row + 2][col + 2] == d || pDoc->baduk[row + 2][col + 2] == 0) {		//   x 좌측 검사 시작.
					if (pDoc->baduk[row - 1][col - 1] == d);
					else if (pDoc->baduk[row - 1][col - 1] == o) {				//   *x 상태.
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
					else if (pDoc->baduk[row - 1][col - 1] == 0) {		// ? x 상태
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
					else if (pDoc->baduk[row + 3][col + 3] == 0) {		// x *  상태
						if (pDoc->baduk[row + 4][col + 4] == d || pDoc->baduk[row + 4][col + 4] == 0) {
							if (pDoc->baduk[row - 1][col - 1] == d);
							else if (pDoc->baduk[row - 1][col - 1] == o) {		// *x * 상태
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

			// ====================== 좌상 우하 대각선 체크 끝 ====================== //




			//==============둔 위치를 중심으로 우상 --> 좌하 대각선 줄 체크===============//

			if (pDoc->baduk[row + 1][col - 1] == d);			//둔 위치부터 오른쪽 체크 x?
			else if (pDoc->baduk[row + 1][col - 1] == o) {			//둔 위치 부터 오른쪽 체크 x*?
				if (pDoc->baduk[row + 2][col - 2] == d);
				else if (pDoc->baduk[row + 2][col - 2] == o) {			//x** 상태
					if (pDoc->baduk[row + 3][col - 3] == d);
					else if (pDoc->baduk[row + 3][col - 3] == o) four_by_three_flag++;
					else if (pDoc->baduk[row + 3][col - 3] == 0) {
						if (pDoc->baduk[row + 4][col - 4] == d || pDoc->baduk[row + 4][col - 4] == 0) {
							if (pDoc->baduk[row - 1][col + 1] == d);
							else if (pDoc->baduk[row - 1][col + 1] == o) four_by_three_flag++;
							else if (pDoc->baduk[row - 1][col + 1] == 0) {
								if (pDoc->baduk[row - 2][col + 2] == d) {
									if (pDoc->baduk[row + 4][col - 4] == 0) three_by_three_flag++; // 흰돌 양쪽을 막을 가능성 체크
								}
								else if (pDoc->baduk[row - 2][col + 2] == o) four_by_three_flag++;
								else if (pDoc->baduk[row - 2][col + 2] == 0) three_by_three_flag++; // x**검증 완료
							}
						}
						else if (pDoc->baduk[row + 4][col - 4] == o) four_by_three_flag++;
					}
				}
				else if (pDoc->baduk[row + 2][col - 2] == 0) {		//둔 위치부터 오른쪽 x* ?
					if (pDoc->baduk[row + 3][col - 3] == d || pDoc->baduk[row + 3][col - 3] == 0) {		//x*   상태
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
			else if (pDoc->baduk[row + 1][col - 1] == 0) {			//x ? 상태.
				if (pDoc->baduk[row + 2][col - 2] == d || pDoc->baduk[row + 2][col - 2] == 0) {		//   x 좌측 검사 시작.
					if (pDoc->baduk[row - 1][col + 1] == d);
					else if (pDoc->baduk[row - 1][col + 1] == o) {				//   *x 상태.
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
					else if (pDoc->baduk[row - 1][col + 1] == 0) {		// ? x 상태
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
					else if (pDoc->baduk[row + 3][col - 3] == 0) {		// x *  상태
						if (pDoc->baduk[row + 4][col - 4] == d || pDoc->baduk[row + 4][col - 4] == 0) {
							if (pDoc->baduk[row - 1][col + 1] == d);
							else if (pDoc->baduk[row - 1][col + 1] == o) {		// *x * 상태
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

			// ====================== 우상 좌하 대각선 체크 끝 ====================== //



			// 33 끝

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

void CMFCApplication3View::OffendWeight3(int o, int d) { //2개가 같이 놓여있을때
	CMFCApplication3Doc* pDoc = GetDocument();
	int i;
	int check_vertical = 0; // 세로방향 체크 변수
	int check_beside_vertical = 0; //  세로방향 체크 변수
	int check_horizontal = 0; // 가로방향 체크 변수
	int check_beside_horizontal = 0; // 가로방향 체크 변수
	int check_diagonal = 0;  // 일반대각선의 경우
	int check_beside_diagonal = 0; // 일반대각선의 경우
	int check_reverse_diagonal = 0; //일반대각선의 반대 경우
	int check_reverse_beside_diagonal = 0; // 일반 대각선의 반대 경우
	int row, col;

	int defend_three_point[8]; //4번쨰 칸이 막혔는지 조사 

	int defend_one_point[8];  //1번쨰 칸이 막혔는지 조사

							  /* 배열에대하여
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

							  공격할돌이 *ㅇㅇㅇ* 일때 *의 가중치

							  =====================================================================================*/
	for (row = 0; row < 19; row++)
		for (col = 0; col < 19; col++) {
			check_vertical = 0; //  세로방향 체크 변수
			check_beside_vertical = 0; //  세로방향 체크 변수
			check_horizontal = 0; // 가로방향 체크 변수
			check_beside_horizontal = 0; // 가로방향 체크 변수
			check_diagonal = 0;  // 일반대각선의 경우
			check_beside_diagonal = 0; // 일반대각선의 경우
			check_reverse_diagonal = 0; //일반대각선의 반대 경우
			check_reverse_beside_diagonal = 0; // 일반 대각선의 반대 경우

			for (i = 0; i < 9; i++) {
				defend_three_point[i] = 0;
			}

			for (i = 0; i < 9; i++) {
				defend_one_point[i] = 0;
			}

			if (pDoc->baduk[row][col] == 0) {
				for (i = 1; i < 3; i++) {
					if (col - i < 0) break; // 가로가 0 이면 반복탈출
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

void CMFCApplication3View::OnMouseMove(UINT nFlags, CPoint point) // 바둑판에 투명돌 표시
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

	

	sx = 250, sy = 100;  // 시작점
	ex = sx + 30 * 18;  // 끝점
	ey = sy + 30 * 18;

	if (m_start) {

		CMFCApplication3Doc* pDoc = GetDocument();
		if (point.x <sx || point.x>ex || point.y<sy || point.y>ey) {
			mouseCount = 0;
			return;
		}
		// 마우스 좌표값을 이용하여 바둑판의 row, col을 계산함
		col = (point.x - sx) / 30;
		row = (point.y - sy) / 30;

		// 마우스 위치가 바둑판의 정확한 row, col이 아닐 경우 반올림하여 가까운 위치로 지정
		fx = double((point.x - sx)) / 30.0;
		fy = double((point.y - sy)) / 30.0;
		if (fx - col > 0.5) col++;
		if (fy - row > 0.5) row++;
		if (prow == row && pcol == col)
			return;


		px = sx + 30 * col - width / 2; //흑돌의 원의 시작좌표(px,py)와 끝좌표(ex2,ey2)
		py = sy + 30 * row - width / 2;
		ex2 = px + width;
		ey2 = py + width;


		dc.SetROP2(R2_XORPEN);

		if (pDoc->baduk[row][col] == 0) {
		if (m_sunseo) {
			if (trace)
			{
				px = sx + 30 * pcol - width / 2; //흑돌의 원의 시작좌표(px,py)와 끝좌표(ex2,ey2)
				py = sy + 30 * prow - width / 2;
				ex2 = px + width;
				ey2 = py + width;
				pold = pDC->SelectObject(&whitebrush);
				pDC->Ellipse(px, py, ex2, ey2);
				pDC->SelectObject(pold);

			}
			px = sx + 30 * col - width / 2; //흑돌의 원의 시작좌표(px,py)와 끝좌표(ex2,ey2)
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
				px = sx + 30 * pcol - width / 2; //흑돌의 원의 시작좌표(px,py)와 끝좌표(ex2,ey2)
				py = sy + 30 * prow - width / 2;
				ex2 = px + width;
				ey2 = py + width;
				pold = pDC->SelectObject(&whitebrush);
				pDC->Ellipse(px, py, ex2, ey2);
				pDC->SelectObject(pold);

			}
			px = sx + 30 * col - width / 2; //흑돌의 원의 시작좌표(px,py)와 끝좌표(ex2,ey2)
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
