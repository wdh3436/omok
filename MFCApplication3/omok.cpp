// COmokView

IMPLEMENT_DYNCREATE(COmokView, CView)

BEGIN_MESSAGE_MAP(COmokView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &COmokView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_EDIT_UNDO, &COmokView::OnEditUndo)
END_MESSAGE_MAP()

// COmokView 생성/소멸

COmokView::COmokView()
	: m_sunseo(0)
	, m_row(0)
	, m_col(0)
{
	// TODO: 여기에 생성 코드를 추가합니다.
	m_sunseo = true;
	m_row = 0;
	m_col = 0;

}

COmokView::~COmokView()
{
}

BOOL COmokView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// COmokView 그리기

void COmokView::OnDraw(CDC* pDC)
{
	COmokDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	CBrush blackbrush, whitebrush, yellowbrush, *pold;
	int row, col;
	int x, y, px, py, ex, ey;

	int start_x = 50, start_y = 50;
	int width = 30;

	px = start_x;
	py = start_y;

	ex = start_x + width * 18;
	ey = start_y + width * 18;

	yellowbrush.CreateSolidBrush(RGB(255, 255, 0));
	blackbrush.CreateSolidBrush(RGB(0, 0, 0));
	whitebrush.CreateSolidBrush(RGB(255, 255, 255));

	CDC memDC;
	CBitmap bitmap, *poldbit;

	bitmap.LoadBitmapW(IDB_BITMAP1);
	memDC.CreateCompatibleDC(pDC);

	poldbit = memDC.SelectObject(&bitmap);
	pDC->StretchBlt(30,30,30*18+40, 30*18+40,&memDC,0,0,400,400,SRCCOPY);
	memDC.SelectObject(poldbit);

	

	for (x = 0; x<19; x++){
		px = start_x + x*width;
		py = start_y;
		ex = px;
		ey = py + width * 18;
		pDC->MoveTo(px, py);
		pDC->LineTo(ex, ey);
	}
	for (y = 0; y<19; y++){
		py = start_y + y*width;
		px = start_x;
		ey = py;
		ex = px + width * 18;
		pDC->MoveTo(px, py);
		pDC->LineTo(ex, ey);
	}

	for (row = 0; row<19; row++){
		for (col = 0; col<19; col++){

			if (pDoc->baduk[row][col] == 1){

				px = start_x + width*col - width / 2;
				py = start_y + width*row - width / 2;
				ex = px + width;
				ey = py + width;
				pold = pDC->SelectObject(&blackbrush);
				pDC->Ellipse(px, py, ex, ey);
				pDC->SelectObject(pold);
				
			}
			if (pDoc->baduk[row][col] == 2){

				px = start_x + width*col - width / 2;
				py = start_y + width*row - width / 2;
				ex = px + width;
				ey = py + width;
				pold = pDC->SelectObject(&whitebrush);
				pDC->Ellipse(px, py, ex, ey);
				pDC->SelectObject(pold);
				if( row == m_row && col == m_col)
				{
					CBrush brush, *oldb;
					brush.CreateSolidBrush(RGB(180,0,0));
					oldb = pDC->SelectObject(&brush);
					pDC->Ellipse(px+10,py+10, px+20, py+20);
					pDC->SelectObject(oldb);
					brush.DeleteObject();
				}
			}
		}
	}
	yellowbrush.DeleteObject();
	blackbrush.DeleteObject();
	whitebrush.DeleteObject();

}


// COmokView 인쇄


void COmokView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL COmokView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void COmokView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void COmokView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void COmokView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void COmokView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// COmokView 진단

#ifdef _DEBUG
void COmokView::AssertValid() const
{
	CView::AssertValid();
}

void COmokView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COmokDoc* COmokView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COmokDoc)));
	return (COmokDoc*)m_pDocument;
}
#endif //_DEBUG


// COmokView 메시지 처리기


void COmokView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	int sx, sy, ex, ey, col, row;
	double fx, fy;

	COmokDoc* pDoc = GetDocument();

	sx = 50, sy = 50;
	ex = sx + 30 * 18;
	ey = sy + 30 * 18;

	if(point.x< sx || point.x > ex || point.y < sy || point.y > ey)
		return;
	if( m_sunseo == false ) return;

	col = (point.x - sx) / 30;
	row = (point.y - sy) / 30;


	fx = double((point.x-sx)) / 30.0;
	fy = double((point.y-sy)) / 30.0;
	if(fx-col > 0.5) col++;
	if(fy-row > 0.5) row++;

	if(pDoc->baduk[row][col] == 0 ){
		if(m_sunseo){
			pDoc->baduk[row][col] = 1;
			m_sunseo = false;
		}
	}

	Invalidate(false);
	m_row = row;
	m_col = col;
	if(CheckVictory(1,row,col) == 1){
			AfxMessageBox(_T("흑이 승리했습니다. 새 게임 시작합니다."), MB_OK);
			for(int row=0; row<19; row++)
				for(int col=0; col<19; col++)
					pDoc->baduk[row][col] = 0;
			m_sunseo = true;
			Invalidate(true);
	
	}

					
	
	if( m_sunseo == false )
	{
		AI_White_Do(row,col);
		for(int r=0;r<19;r++)
		{
			for(int c=0; c<19; c++)
			{
				if(CheckVictory(2,r,c) == 1)
				{
					AfxMessageBox(_T("백이 승리했습니다. 새 게임 시작합니다."), MB_OK);
					for(int row=0; row<19; row++)
							for(int col=0; col<19; col++)
								pDoc->baduk[row][col] = 0;
					m_sunseo = true;
					Invalidate(true);
				}
			}
		}
	}

}


	void COmokView::OnEditUndo()
	{
		// TODO: 여기에 명령 처리기 코드를 추가합니다.
		COmokDoc* pDoc = GetDocument();
		pDoc->baduk[m_row][m_col] = 0;

		if(m_sunseo) m_sunseo = false;
		else m_sunseo = true;

		Invalidate(true);
	}


int COmokView::CheckVictory(int a, int r, int c)
{
	COmokDoc* pDoc = GetDocument();

	int i;

	int count = 0;
	for (i = 0; i<19; i++){
		if (pDoc->baduk[r][i] == a) count++;
		else
		{
			if (count == 5) return 1;
			count = 0;
		}
		//if (count == 5) return 1;
	}

	count = 0;
	for (i = 0; i<19; i++){
		if (pDoc->baduk[i][c] == a) count++;
		else count = 0;
		if (count == 5) return 1;
	}
	int srow, scol;
	int erow, ecol;
	int tr, tc;
	tr = r; tc = c;
	while (tr != 0 && tc != 0){
				tr--;
				tc--;
	}
	

	srow = tr; scol = tc;

	tr = r; tc = c;

	while (tr != 18 && tc!= 18){
		tr++;
		tc++;
	}


	erow = tr; ecol = tc;
	count = 0;

	while (scol <= ecol && srow <= erow){
		if (pDoc->baduk[srow][scol] == a) count++;
		else count = 0;
		if (count == 5) return 1;
		srow++;
		scol++;

	}


	tr = r; tc = c;

	while (tr != 0 && tc != 18){
		tr--;
		tc++;
	}

	srow = tr; scol = tc;

	tr = r; tc = c;
	while (tr != 18 && tc != 0){
		tr++;
		tc--;
	}

	erow = tr; ecol = tc;
	count = 0;

	while (scol >= ecol && srow <= erow){
		if (pDoc->baduk[srow][scol] == a) count ++;
		else count = 0;
		if (count == 5) return 1;
		srow++;
		scol--;
	}
	return 0;
}



int COmokView::AI_White_Do(int r, int c)
{
	COmokDoc* pDoc = GetDocument();

	
	int tr,tc;

	//===============================================================
	// 방어 알고리즘
	//===============================================================

	int count = 0;
	
	//===============================================================
	// 4 돌 공격 알고리즘 공백백백백공
	//===============================================================
	int row,col;
	for(row=0; row<19; row++)
		for(col=0; col<19; col++)
			if(pDoc->baduk[row][col] == 2 && Offend4(4,row,col)) return 1;

	//===============================================================
	// 3-1 돌 공격 알고리즘
	//===============================================================
	for(row=0; row<19; row++)
		for(col=0; col<19; col++)
			if(pDoc->baduk[row][col] == 2 && Offend3_1(3,row,col)) return 1;


	//===============================================================
	// 4 돌 방어 알고리즘 백흑흑흑흑공 또는  공흑흑흑흑공 
	//===============================================================
	for(row=0; row<19; row++)
		for(col=0; col<19; col++)
			if(pDoc->baduk[row][col] == 1 && Defend(4,row,col)) return 1;

	//===============================================================
	// 3-1 돌 방어 알고리즘 백흑흑흑흑공 또는  공흑흑흑흑공 
	//===============================================================
	for(row=0; row<19; row++)
		for(col=0; col<19; col++)
			if(pDoc->baduk[row][col] == 1 && Defend3_1(3,row,col)) return 1;


	//if( Defend(4,r,c) ) return 1;

	//===============================================================
	// 3 돌 공격 알고리즘 공백백백공
	//===============================================================
	for(row=0; row<19; row++)
		for(col=0; col<19; col++)
			if(pDoc->baduk[row][col] == 2 && Offend3(3,row,col)) return 1;
	
	for(row=0; row<19; row++)
		for(col=0; col<19; col++)
			if(pDoc->baduk[row][col] == 2 && Offend3_1(2,row,col)) return 1;

	//===============================================================
	// 4 돌 공격 알고리즘 공백백백흑
	//===============================================================
	for(row=0; row<19; row++)
		for(col=0; col<19; col++)
			if(pDoc->baduk[row][col] == 2 && Offend(4,row,col)) return 1;

	//===============================================================
	// 3 돌 방어 알고리즘
	//===============================================================
	//if( Defend(3,r,c) ) return 1;
	for(row=0; row<19; row++)
		for(col=0; col<19; col++)
			if(pDoc->baduk[row][col] == 1 && Defend3(3,row,col)) return 1;

	for(row=0; row<19; row++)
		for(col=0; col<19; col++)
			if(pDoc->baduk[row][col] == 1 && Defend3_1(2,row,col)) return 1;

	
	//===============================================================
	// 3 돌 공격 알고리즘 흑백백백공
	//===============================================================
	for(row=0; row<19; row++)
		for(col=0; col<19; col++)
			if(pDoc->baduk[row][col] == 2 && Offend(3,row,col)) return 1;
	
	//===============================================================
	// 2 돌 공격 알고리즘
	//===============================================================
	for(row=0; row<19; row++)
		for(col=0; col<19; col++)
			if(pDoc->baduk[row][col] == 2 && Offend2(2,row,col)) return 1;

	for(row=0; row<19; row++)
		for(col=0; col<19; col++)
			if(pDoc->baduk[row][col] == 2 && Offend2(1,row,col)) return 1;

	for(row=0; row<19; row++)
		for(col=0; col<19; col++)
			if(pDoc->baduk[row][col] == 2 && Offend(2,row,col)) return 1;

	
	//===============================================================
	// 1 돌 공격 알고리즘
	//===============================================================
	tr = r; tc = c+1;
	if( tc <= 18) 
	{
		if( pDoc->baduk[tr][tc] == 0)  pDoc->baduk[tr][tc] = 2;
		m_sunseo = true;
		m_row = tr; m_col =tc;
		Invalidate(false);
		return 1;
	}
	tr = r; tc = c-1;
	if( tc >= 0) 
	{
		if( pDoc->baduk[tr][tc] == 0)  pDoc->baduk[tr][tc] = 2;
		m_sunseo = true;
		m_row = tr; m_col =tc;
		Invalidate(false);
		return 1;
	}
	tr = r+1; tc = c;
	if( tr <= 18) 
	{
		if( pDoc->baduk[tr][tc] == 0)  pDoc->baduk[tr][tc] = 2;
		m_sunseo = true;
		m_row = tr; m_col =tc;
		Invalidate(false);
		return 1;
	}
	tr = r-1; tc = c;
	if( tr >= 0) 
	{
		if( pDoc->baduk[tr][tc] == 0)  pDoc->baduk[tr][tc] = 2;
		m_sunseo = true;
		m_row = tr; m_col =tc;
		Invalidate(false);
		return 1;
	}

	return 0;
}


int COmokView::Defend(int cnt, int r, int c)
{
	COmokDoc* pDoc = GetDocument();

	int i;

	//===============================================================
	// 방어 알고리즘
	//===============================================================

	int count = 0;
	
	for (i = 0; i<19; i++){
		if (pDoc->baduk[r][i] == 1) count++;
		else
		{
			if( count == cnt && pDoc->baduk[r][i] == 0 )
			{
				pDoc->baduk[r][i] = 2;
				m_sunseo = true;
				m_row = r; m_col =i;
				Invalidate(false);
				return 1;
			}
			if( count == cnt && i-cnt-1 >=0 && pDoc->baduk[r][i-cnt-1] == 0 )
			{
				pDoc->baduk[r][i-cnt-1] = 2;
				m_sunseo = true;
				m_row = r; m_col =i-5;
				Invalidate(false);
				return 1;
			}
			
			count = 0;
		}
		
	}

	count = 0;
	for (i = 0; i<19; i++){
		if (pDoc->baduk[i][c] == 1) count++;
		else
		{
			if( count == cnt && pDoc->baduk[i][c] == 0 )
			{
				pDoc->baduk[i][c] = 2;
				m_sunseo = true;
				m_row = i; m_col =c;
				Invalidate(false);
				return 1;
			}
			if( count == cnt && i-cnt-1 >= 0 && pDoc->baduk[i-cnt-1][c] == 0 )
			{
				pDoc->baduk[i-cnt-1][c] = 2;
				m_sunseo = true;
				m_row = i-cnt-1; m_col =c;
				Invalidate(false);
				return 1;
			}

			
			count = 0;
		}
	}

	int srow, scol;
	int erow, ecol;
	int tr, tc;
	tr = r; tc = c;
	while (tr != 0 && tc != 0){
				tr--;
				tc--;
	}
	

	srow = tr; scol = tc;

	tr = r; tc = c;

	while (tr != 18 && tc!= 18){
		tr++;
		tc++;
	}


	erow = tr; ecol = tc;
	count = 0;

	while (scol <= ecol && srow <= erow){
		if (pDoc->baduk[srow][scol] == 1) count++;
		else
		{
			if( count == cnt && pDoc->baduk[srow][scol] == 0 )
			{
				pDoc->baduk[srow][scol] = 2;
				m_sunseo = true;
				m_row = srow; m_col =scol;
				Invalidate(false);
				return 1;
			}
			if( count == cnt && srow-cnt-1 >=0 && scol-cnt-1 >= 0 && pDoc->baduk[srow-cnt-1][scol-cnt-1] == 0 )
			{
				pDoc->baduk[srow-cnt-1][scol-cnt-1] = 2;
				m_sunseo = true;
				m_row = srow-cnt-1; m_col =scol-cnt-1;
				Invalidate(false);
				return 1;
			}
			
			count = 0;
		}
		srow++;
		scol++;

	}


	tr = r; tc = c;

	while (tr != 0 && tc != 18){
		tr--;
		tc++;
	}

	srow = tr; scol = tc;

	tr = r; tc = c;
	while (tr != 18 && tc != 0){
		tr++;
		tc--;
	}

	erow = tr; ecol = tc;
	count = 0;

	while (scol >= ecol && srow <= erow){
		if (pDoc->baduk[srow][scol] == 1) count ++;
		else
		{
			if( count == cnt && pDoc->baduk[srow][scol] == 0 )
			{
				pDoc->baduk[srow][scol] = 2;
				m_sunseo = true;
				m_row = srow; m_col =scol;
				Invalidate(false);
				return 1;
			}
			if( count == cnt && srow-cnt-1 >= 0 && scol+cnt+1 <= 18 && pDoc->baduk[srow-cnt-1][scol+cnt+1] == 0 )
			{
				pDoc->baduk[srow-cnt-1][scol+cnt+1] = 2;
				m_sunseo = true;
				m_row = srow; m_col =scol;
				Invalidate(false);
				return 1;
			}
			
			count = 0;
		}
		srow++;
		scol--;
	}

	return 0;
}


int COmokView::Offend(int cnt, int r, int c)
{
	COmokDoc* pDoc = GetDocument();

	int i;

	//===============================================================
	// 공격 알고리즘
	//===============================================================

	int count = 0;
	int srow, scol;
	int erow, ecol;
	int tr, tc;

	for (i = 0; i<19; i++){
		if (pDoc->baduk[r][i] == 2) count++;
		else
		{
			if( count == cnt && pDoc->baduk[r][i] == 0 )
			{
				pDoc->baduk[r][i] = 2;
				m_sunseo = true;
				m_row = r; m_col =i;
				Invalidate(false);
				return 1;
			}
			if( count == cnt && i-cnt-1 >= 0 && pDoc->baduk[r][i-cnt-1] == 0 )
			{
				pDoc->baduk[r][i-cnt-1] = 2;
				m_sunseo = true;
				m_row = r; m_col =i-cnt-1;
				Invalidate(false);
				return 1;
			}
			
			count = 0;
		}
		
	}

	count = 0;
	for (i = 0; i<19; i++){
		if (pDoc->baduk[i][c] == 2) count++;
		else
		{
			if( count == cnt && pDoc->baduk[i][c] == 0 )
			{
				pDoc->baduk[i][c] = 2;
				m_sunseo = true;
				m_row = i; m_col =c;
				Invalidate(false);
				return 1;
			}
			if( count == cnt && i-cnt-1 >= 0 && pDoc->baduk[i-cnt-1][c] == 0 )
			{
				pDoc->baduk[i-cnt-1][c] = 2;
				m_sunseo = true;
				m_row = i-cnt-1; m_col =c;
				Invalidate(false);
				return 1;
			}
			
			count = 0;
		}
	}

	
	tr = r; tc = c;
	while (tr != 0 && tc != 0){
				tr--;
				tc--;
	}
	

	srow = tr; scol = tc;

	tr = r; tc = c;

	while (tr != 18 && tc!= 18){
		tr++;
		tc++;
	}


	erow = tr; ecol = tc;
	count = 0;

	while (scol <= ecol && srow <= erow){
		if (pDoc->baduk[srow][scol] == 2) count++;
		else
		{
			if( count == cnt && pDoc->baduk[srow][scol] == 0 )
			{
				pDoc->baduk[srow][scol] = 2;
				m_sunseo = true;
				m_row = srow; m_col =scol;
				Invalidate(false);
				return 1;
			}
			if( count == cnt && srow-cnt-1 >= 0 && scol-cnt-1 >= 0 && pDoc->baduk[srow-cnt-1][scol-cnt-1] == 0 )
			{
				pDoc->baduk[srow-cnt-1][scol-cnt-1] = 2;
				m_sunseo = true;
				m_row = srow-cnt-1; m_col =scol-cnt-1;
				Invalidate(false);
				return 1;
			}

			
			count = 0;
		}
		srow++;
		scol++;

	}


	tr = r; tc = c;

	while (tr != 0 && tc != 18){
		tr--;
		tc++;
	}

	srow = tr; scol = tc;

	tr = r; tc = c;
	while (tr != 18 && tc != 0){
		tr++;
		tc--;
	}

	erow = tr; ecol = tc;
	count = 0;

	while (scol >= ecol && srow <= erow){
		if (pDoc->baduk[srow][scol] == 2) count ++;
		else
		{
			if( count == cnt && pDoc->baduk[srow][scol] == 0 )
			{
				pDoc->baduk[srow][scol] = 2;
				m_sunseo = true;
				m_row = srow; m_col =scol;
				Invalidate(false);
				return 1;
			}
			if( count == cnt && srow-cnt-1 >= 0 && scol+cnt+1 <= 18 && pDoc->baduk[srow-cnt-1][scol+cnt+1] == 0 )
			{
				pDoc->baduk[srow-cnt-1][scol+cnt+1] = 2;
				m_sunseo = true;
				m_row = srow-cnt-1; m_col =scol+cnt+1;
				Invalidate(false);
				return 1;
			}
			
			count = 0;
		}
		srow++;
		scol--;
	}
	return 0;
}


int COmokView::Offend4(int cnt, int r, int c)
{
	
	COmokDoc* pDoc = GetDocument();

	int i;

	//===============================================================
	// 공격 알고리즘
	//===============================================================

	int count = 0;
	int srow, scol;
	int erow, ecol;
	int tr, tc;

	for (i = 0; i<19; i++){
		if (pDoc->baduk[r][i] == 2) count++;
		else
		{
			if( count == cnt && pDoc->baduk[r][i] == 0 )
			{
				pDoc->baduk[r][i] = 2;
				m_sunseo = true;
				m_row = r; m_col =i;
				Invalidate(false);
				return 1;
			}
			if( count == cnt && i-cnt-1 >= 0 && pDoc->baduk[r][i-cnt-1] == 0 )
			{
				pDoc->baduk[r][i-cnt-1] = 2;
				m_sunseo = true;
				m_row = r; m_col =i-cnt-1;
				Invalidate(false);
				return 1;
			}
			
			count = 0;
		}
		
	}

	count = 0;
	for (i = 0; i<19; i++){
		if (pDoc->baduk[i][c] == 2) count++;
		else
		{
			if( count == cnt && pDoc->baduk[i][c] == 0 )
			{
				pDoc->baduk[i][c] = 2;
				m_sunseo = true;
				m_row = i; m_col =c;
				Invalidate(false);
				return 1;
			}
			if( count == cnt && i-cnt-1 >= 0 && pDoc->baduk[i-cnt-1][c] == 0 )
			{
				pDoc->baduk[i-cnt-1][c] = 2;
				m_sunseo = true;
				m_row = i-cnt-1; m_col =c;
				Invalidate(false);
				return 1;
			}
			
			count = 0;
		}
	}

	
	tr = r; tc = c;
	while (tr != 0 && tc != 0){
				tr--;
				tc--;
	}
	

	srow = tr; scol = tc;

	tr = r; tc = c;

	while (tr != 18 && tc!= 18){
		tr++;
		tc++;
	}


	erow = tr; ecol = tc;
	count = 0;

	while (scol <= ecol && srow <= erow){
		if (pDoc->baduk[srow][scol] == 2) count++;
		else
		{
			if( count == cnt && pDoc->baduk[srow][scol] == 0 )
			{
				pDoc->baduk[srow][scol] = 2;
				m_sunseo = true;
				m_row = srow; m_col =scol;
				Invalidate(false);
				return 1;
			}
			if( count == cnt && srow-cnt-1 >= 0 && scol-cnt-1 >= 0 && pDoc->baduk[srow-cnt-1][scol-cnt-1] == 0 )
			{
				pDoc->baduk[srow-cnt-1][scol-cnt-1] = 2;
				m_sunseo = true;
				m_row = srow-cnt-1; m_col =scol-cnt-1;
				Invalidate(false);
				return 1;
			}

			
			count = 0;
		}
		srow++;
		scol++;

	}


	tr = r; tc = c;

	while (tr != 0 && tc != 18){
		tr--;
		tc++;
	}

	srow = tr; scol = tc;

	tr = r; tc = c;
	while (tr != 18 && tc != 0){
		tr++;
		tc--;
	}

	erow = tr; ecol = tc;
	count = 0;

	while (scol >= ecol && srow <= erow){
		if (pDoc->baduk[srow][scol] == 2) count ++;
		else
		{
			if( count == cnt && pDoc->baduk[srow][scol] == 0 )
			{
				pDoc->baduk[srow][scol] = 2;
				m_sunseo = true;
				m_row = srow; m_col =scol;
				Invalidate(false);
				return 1;
			}
			if( count == cnt && srow-cnt-1 >= 0 && scol+cnt+1 <= 18 && pDoc->baduk[srow-cnt-1][scol+cnt+1] == 0 )
			{
				pDoc->baduk[srow-cnt-1][scol+cnt+1] = 2;
				m_sunseo = true;
				m_row = srow-cnt-1; m_col =scol+cnt+1;
				Invalidate(false);
				return 1;
			}
			
			count = 0;
		}
		srow++;
		scol--;
	}
	return 0;
	return 0;
}


int COmokView::Offend3(int a, int r, int c)
{
	
	COmokDoc* pDoc = GetDocument();

	int i;

	//===============================================================
	// 공격 알고리즘
	//===============================================================

	int count = 0;
	int srow, scol;
	int erow, ecol;
	int tr, tc;
	int cnt;

	cnt = a;

	for (i = 0; i<19; i++){
		if (pDoc->baduk[r][i] == 2) count++;
		else
		{
			if( count == cnt && pDoc->baduk[r][i] == 0 && i-cnt-1 >= 0 && pDoc->baduk[r][i-cnt-1] == 0)
			{
				pDoc->baduk[r][i] = 2;
				m_sunseo = true;
				m_row = r; m_col =i;
				Invalidate(false);
				return 1;
			}
			
			count = 0;
		}
		
	}

	count = 0;
	for (i = 0; i<19; i++){
		if (pDoc->baduk[i][c] == 2) count++;
		else
		{
			if( count == cnt && pDoc->baduk[i][c] == 0  && i-cnt-1 >= 0 && pDoc->baduk[i-cnt-1][c] == 0)
			{
				pDoc->baduk[i][c] = 2;
				m_sunseo = true;
				m_row = i; m_col =c;
				Invalidate(false);
				return 1;
			}
			
			
			count = 0;
		}
	}

	
	tr = r; tc = c;
	while (tr != 0 && tc != 0){
				tr--;
				tc--;
	}
	

	srow = tr; scol = tc;

	tr = r; tc = c;

	while (tr != 18 && tc!= 18){
		tr++;
		tc++;
	}


	erow = tr; ecol = tc;
	count = 0;

	while (scol <= ecol && srow <= erow){
		if (pDoc->baduk[srow][scol] == 2) count++;
		else
		{
			if( count == cnt && pDoc->baduk[srow][scol] == 0  && srow-cnt-1 >= 0 && scol-cnt-1 >= 0 && pDoc->baduk[srow-cnt-1][scol-cnt-1] == 0)
			{
				pDoc->baduk[srow][scol] = 2;
				m_sunseo = true;
				m_row = srow; m_col =scol;
				Invalidate(false);
				return 1;
			}
						
			count = 0;
		}
		srow++;
		scol++;

	}


	tr = r; tc = c;

	while (tr != 0 && tc != 18){
		tr--;
		tc++;
	}

	srow = tr; scol = tc;

	tr = r; tc = c;
	while (tr != 18 && tc != 0){
		tr++;
		tc--;
	}

	erow = tr; ecol = tc;
	count = 0;

	while (scol >= ecol && srow <= erow){
		if (pDoc->baduk[srow][scol] == 2) count ++;
		else
		{
			if( count == cnt && pDoc->baduk[srow][scol] == 0 && srow-cnt-1 >= 0 && scol+cnt+1 <= 18 && pDoc->baduk[srow-cnt-1][scol+cnt+1] == 0 )
			{
				pDoc->baduk[srow][scol] = 2;
				m_sunseo = true;
				m_row = srow; m_col =scol;
				Invalidate(false);
				return 1;
			}
						
			count = 0;
		}
		srow++;
		scol--;
	}
	return 0;
	
}


int COmokView::Defend3(int cnt, int r, int c)
{
	COmokDoc* pDoc = GetDocument();

	int i;

	//===============================================================
	// 방어 알고리즘
	//===============================================================

	int count = 0;
	
	for (i = 0; i<19; i++){
		if (pDoc->baduk[r][i] == 1) count++;
		else
		{
			if( count == cnt && pDoc->baduk[r][i] == 0 && i-cnt-1 >=0 && pDoc->baduk[r][i-cnt-1] == 0 )
			{
				pDoc->baduk[r][i] = 2;
				m_sunseo = true;
				m_row = r; m_col =i;
				Invalidate(false);
				return 1;
			}
			
			
			count = 0;
		}
		
	}

	count = 0;
	for (i = 0; i<19; i++){
		if (pDoc->baduk[i][c] == 1) count++;
		else
		{
			if( count == cnt && pDoc->baduk[i][c] == 0 && i-cnt-1 >= 0 && pDoc->baduk[i-cnt-1][c] == 0)
			{
				pDoc->baduk[i][c] = 2;
				m_sunseo = true;
				m_row = i; m_col =c;
				Invalidate(false);
				return 1;
			}
			

			
			count = 0;
		}
	}

	int srow, scol;
	int erow, ecol;
	int tr, tc;
	tr = r; tc = c;
	while (tr != 0 && tc != 0){
				tr--;
				tc--;
	}
	

	srow = tr; scol = tc;

	tr = r; tc = c;

	while (tr != 18 && tc!= 18){
		tr++;
		tc++;
	}


	erow = tr; ecol = tc;
	count = 0;

	while (scol <= ecol && srow <= erow){
		if (pDoc->baduk[srow][scol] == 1) count++;
		else
		{
			if( count == cnt && pDoc->baduk[srow][scol] == 0 && srow-cnt-1 >=0 && scol-cnt-1 >= 0 && pDoc->baduk[srow-cnt-1][scol-cnt-1] == 0)
			{
				pDoc->baduk[srow][scol] = 2;
				m_sunseo = true;
				m_row = srow; m_col =scol;
				Invalidate(false);
				return 1;
			}
			
			
			count = 0;
		}
		srow++;
		scol++;

	}


	tr = r; tc = c;

	while (tr != 0 && tc != 18){
		tr--;
		tc++;
	}

	srow = tr; scol = tc;

	tr = r; tc = c;
	while (tr != 18 && tc != 0){
		tr++;
		tc--;
	}

	erow = tr; ecol = tc;
	count = 0;

	while (scol >= ecol && srow <= erow){
		if (pDoc->baduk[srow][scol] == 1) count ++;
		else
		{
			if( count == cnt && pDoc->baduk[srow][scol] == 0  && srow-cnt-1 >= 0 && scol+cnt+1 <= 18 && pDoc->baduk[srow-cnt-1][scol+cnt+1] == 0)
			{
				pDoc->baduk[srow][scol] = 2;
				m_sunseo = true;
				m_row = srow; m_col =scol;
				Invalidate(false);
				return 1;
			}
			
			
			count = 0;
		}
		srow++;
		scol--;
	}

	return 0;
}


#ifdef KKK
int COmokView::Offend(int cnt, int r, int c)
{
	COmokDoc* pDoc = GetDocument();

	int i;

	//===============================================================
	// 공격 알고리즘
	//===============================================================

	int count = 0;
	int srow, scol;
	int erow, ecol;
	int tr, tc;

	for (i = 0; i<19; i++){
		if (pDoc->baduk[r][i] == 2) count++;
		else
		{
			if( count == cnt && pDoc->baduk[r][i] == 0 )
			{
				pDoc->baduk[r][i] = 2;
				m_sunseo = true;
				m_row = r; m_col =i;
				Invalidate(false);
				return 1;
			}
			if( count == cnt && i-cnt-1 >=0 && pDoc->baduk[r][i-cnt-1] == 0 )
			{
				pDoc->baduk[r][i-cnt-1] = 2;
				m_sunseo = true;
				m_row = r; m_col =i-5;
				Invalidate(false);
				return 1;
			}
			
			count = 0;
		}
		
	}

	
	count = 0;
	for (i = 0; i<19; i++){
		if (pDoc->baduk[i][c] == 2) count++;
		else
		{
			if( count == cnt && pDoc->baduk[i][c] == 0 )
			{
				pDoc->baduk[i][c] = 2;
				m_sunseo = true;
				m_row = i; m_col =c;
				Invalidate(false);
				return 1;
			}
			if( count == cnt && i-cnt-1 >=0 && pDoc->baduk[i-cnt-1][c] == 0 )
			{
				pDoc->baduk[i-cnt-1][c] = 2;
				m_sunseo = true;
				m_row = i-cnt-1; m_col =c;
				Invalidate(false);
				return 1;
			}
			///////////////////////////////////////////
									
			count = 0;
		}
	}

	
	tr = r; tc = c;
	while (tr != 0 && tc != 0){
				tr--;
				tc--;
	}
	

	srow = tr; scol = tc;

	tr = r; tc = c;

	while (tr != 18 && tc!= 18){
		tr++;
		tc++;
	}


	erow = tr; ecol = tc;
	count = 0;

	while (scol <= ecol && srow <= erow){
		if (pDoc->baduk[srow][scol] == 2) count++;
		else
		{
			if( count == cnt && pDoc->baduk[srow][scol] == 0 )
			{
				pDoc->baduk[srow][scol] = 2;
				m_sunseo = true;
				m_row = srow; m_col =scol;
				Invalidate(false);
				return 1;
			}
			if( count == cnt && srow-cnt-1 >= 0 && scol-cnt-1 >= 0 && pDoc->baduk[srow-cnt-1][scol-cnt-1] == 0 )
			{
				pDoc->baduk[srow-cnt-1][scol-cnt-1] = 2;
				m_sunseo = true;
				m_row = srow-cnt-1; m_col =scol-cnt-1;
				Invalidate(false);
				return 1;
			}

			
			count = 0;
		}
		srow++;
		scol++;

	}


	tr = r; tc = c;

	while (tr != 0 && tc != 18){
		tr--;
		tc++;
	}

	srow = tr; scol = tc;

	tr = r; tc = c;
	while (tr != 18 && tc != 0){
		tr++;
		tc--;
	}

	erow = tr; ecol = tc;
	count = 0;

	while (scol >= ecol && srow <= erow){
		if (pDoc->baduk[srow][scol] == 2) count ++;
		else
		{
			if( count == cnt && pDoc->baduk[srow][scol] == 0 )
			{
				pDoc->baduk[srow][scol] = 2;
				m_sunseo = true;
				m_row = srow; m_col =scol;
				Invalidate(false);
				return 1;
			}
			if( count == cnt && srow-cnt-1 >= 0 && scol+cnt+1 <= 18 && pDoc->baduk[srow-cnt-1][scol+cnt+1] == 0 )
			{
				pDoc->baduk[srow-cnt-1][scol+cnt+1] = 2;
				m_sunseo = true;
				m_row = srow-cnt-1; m_col =scol+cnt+1;
				Invalidate(false);
				return 1;
			}
			
			count = 0;
		}
		srow++;
		scol--;
	}
	return 0;
}
#endif

int COmokView::Offend2(int cnt, int r, int c)
{
	COmokDoc* pDoc = GetDocument();

	int i;

	//===============================================================
	// 공격 알고리즘
	//===============================================================

	int count = 0;
	int srow, scol;
	int erow, ecol;
	int tr, tc;




	for (i = 0; i<19; i++){
		if (pDoc->baduk[r][i] == 2) count++;
		else
		{
			if( count == cnt && pDoc->baduk[r][i] == 0 && i-cnt-1 >= 0 && pDoc->baduk[r][i-cnt-1] == 0)
			{
				pDoc->baduk[r][i] = 2;
				m_sunseo = true;
				m_row = r; m_col =i;
				Invalidate(false);
				return 1;
			}
			
			count = 0;
		}
		
	}

	count = 0;
	for (i = 0; i<19; i++){
		if (pDoc->baduk[i][c] == 2) count++;
		else
		{
			if( count == cnt && pDoc->baduk[i][c] == 0  && i-cnt-1 >= 0 && pDoc->baduk[i-cnt-1][c] == 0)
			{
				pDoc->baduk[i][c] = 2;
				m_sunseo = true;
				m_row = i; m_col =c;
				Invalidate(false);
				return 1;
			}
			
			
			count = 0;
		}
	}

	
	tr = r; tc = c;
	while (tr != 0 && tc != 0){
				tr--;
				tc--;
	}
	

	srow = tr; scol = tc;

	tr = r; tc = c;

	while (tr != 18 && tc!= 18){
		tr++;
		tc++;
	}


	erow = tr; ecol = tc;
	count = 0;

	while (scol <= ecol && srow <= erow){
		if (pDoc->baduk[srow][scol] == 2) count++;
		else
		{
			if( count == cnt && pDoc->baduk[srow][scol] == 0  && srow-cnt-1 >= 0 && scol-cnt-1 >= 0 && pDoc->baduk[srow-cnt-1][scol-cnt-1] == 0)
			{
				pDoc->baduk[srow][scol] = 2;
				m_sunseo = true;
				m_row = srow; m_col =scol;
				Invalidate(false);
				return 1;
			}
						
			count = 0;
		}
		srow++;
		scol++;

	}


	tr = r; tc = c;

	while (tr != 0 && tc != 18){
		tr--;
		tc++;
	}

	srow = tr; scol = tc;

	tr = r; tc = c;
	while (tr != 18 && tc != 0){
		tr++;
		tc--;
	}

	erow = tr; ecol = tc;
	count = 0;

	while (scol >= ecol && srow <= erow){
		if (pDoc->baduk[srow][scol] == 2) count ++;
		else
		{
			if( count == cnt && pDoc->baduk[srow][scol] == 0 && srow-cnt-1 >= 0 && scol+cnt+1 <= 18 && pDoc->baduk[srow-cnt-1][scol+cnt+1] == 0 )
			{
				pDoc->baduk[srow][scol] = 2;
				m_sunseo = true;
				m_row = srow; m_col =scol;
				Invalidate(false);
				return 1;
			}
						
			count = 0;
		}
		srow++;
		scol--;
	}
	return 0;
	
}


int COmokView::Defend3_1(int cnt, int r, int c)
{
	COmokDoc* pDoc = GetDocument();

	int i;

	//===============================================================
	// 방어 알고리즘
	//===============================================================

	int count = 0;
	
	for (i = 0; i<19; i++){
		if (pDoc->baduk[r][i] == 1) count++;
		else
		{
			if( count == cnt && pDoc->baduk[r][i] == 0 && i+1<= 18 && pDoc->baduk[r][i+1] == 1)
			{
				pDoc->baduk[r][i] = 2;
				m_sunseo = true;
				m_row = r; m_col =i;
				Invalidate(false);
				return 1;
			}

			if( count == cnt && i-cnt-1 >=0 && pDoc->baduk[r][i-cnt-1] == 0 && i-cnt-2 >=0 && pDoc->baduk[r][i-cnt-2] == 1)
			{
				pDoc->baduk[r][i-cnt-1] = 2;
				m_sunseo = true;
				m_row = r; m_col =i-cnt-1;
				Invalidate(false);
				return 1;
			}
			
			count = 0;
		}
		
	}

	count = 0;
	for (i = 0; i<19; i++){
		if (pDoc->baduk[i][c] == 1) count++;
		else
		{
			if( count == cnt && pDoc->baduk[i][c] == 0 && i+1<= 18 && pDoc->baduk[i+1][c] == 1 )
			{
				pDoc->baduk[i][c] = 2;
				m_sunseo = true;
				m_row = i; m_col =c;
				Invalidate(false);
				return 1;
			}
			if( count == cnt && i-cnt-1 >= 0 && pDoc->baduk[i-cnt-1][c] == 0 && i-cnt-2 >= 0 && pDoc->baduk[i-cnt-2][c] == 1)
			{
				pDoc->baduk[i-cnt-1][c] = 2;
				m_sunseo = true;
				m_row = i-cnt-1; m_col =c;
				Invalidate(false);
				return 1;
			}

			
			count = 0;
		}
	}

	int srow, scol;
	int erow, ecol;
	int tr, tc;
	tr = r; tc = c;
	while (tr != 0 && tc != 0){
				tr--;
				tc--;
	}
	

	srow = tr; scol = tc;

	tr = r; tc = c;

	while (tr != 18 && tc!= 18){
		tr++;
		tc++;
	}


	erow = tr; ecol = tc;
	count = 0;

	while (scol <= ecol && srow <= erow){
		if (pDoc->baduk[srow][scol] == 1) count++;
		else
		{
			if( count == cnt && pDoc->baduk[srow][scol] == 0 && srow+1<=18 && scol+1<=18 && pDoc->baduk[srow+1][scol+1] == 1 )
			{
				pDoc->baduk[srow][scol] = 2;
				m_sunseo = true;
				m_row = srow; m_col =scol;
				Invalidate(false);
				return 1;
			}
			
			if( count == cnt && srow-cnt-1 >=0 && scol-cnt-1 >= 0 && pDoc->baduk[srow-cnt-1][scol-cnt-1] == 0 && srow-cnt-2 >=0 && scol-cnt-2 >= 0 && pDoc->baduk[srow-cnt-2][scol-cnt-2] == 1)
			{
				pDoc->baduk[srow-cnt-1][scol-cnt-1] = 2;
				m_sunseo = true;
				m_row = srow-cnt-1; m_col =scol-cnt-1;
				Invalidate(false);
				return 1;
			}
			
			count = 0;
		}
		srow++;
		scol++;

	}


	tr = r; tc = c;

	while (tr != 0 && tc != 18){
		tr--;
		tc++;
	}

	srow = tr; scol = tc;

	tr = r; tc = c;
	while (tr != 18 && tc != 0){
		tr++;
		tc--;
	}

	erow = tr; ecol = tc;
	count = 0;

	while (scol >= ecol && srow <= erow){
		if (pDoc->baduk[srow][scol] == 1) count ++;
		else
		{
			if( count == cnt && pDoc->baduk[srow][scol] == 0 && srow+1 <= 18 && scol-1>=0 && pDoc->baduk[srow+1][scol-1] == 1)
			{
				pDoc->baduk[srow][scol] = 2;
				m_sunseo = true;
				m_row = srow; m_col =scol;
				Invalidate(false);
				return 1;
			}
			if( count == cnt && srow-cnt-1 >= 0 && scol+cnt+1 <= 18 && pDoc->baduk[srow-cnt-1][scol+cnt+1] == 0 && srow-cnt-2 >= 0 && scol+cnt+2 <= 18 && pDoc->baduk[srow-cnt-2][scol+cnt+2] == 1)
			{
				pDoc->baduk[srow-cnt-1][scol+cnt+1] = 2;
				m_sunseo = true;
				m_row = srow; m_col =scol;
				Invalidate(false);
				return 1;
			}
			
			count = 0;
		}
		srow++;
		scol--;
	}

	return 0;
	
}


int COmokView::Offend3_1(int cnt, int r, int c)
{
	COmokDoc* pDoc = GetDocument();

	int i;

	//===============================================================
	// 방어 알고리즘
	//===============================================================

	int count = 0;
	
	for (i = 0; i<19; i++){
		if (pDoc->baduk[r][i] == 2) count++;
		else
		{
			if( count == cnt && pDoc->baduk[r][i] == 0 && i+1<= 18 && pDoc->baduk[r][i+1] == 2)
			{
				pDoc->baduk[r][i] = 2;
				m_sunseo = true;
				m_row = r; m_col =i;
				Invalidate(false);
				return 1;
			}

			if( count == cnt && i-cnt-1 >=0 && pDoc->baduk[r][i-cnt-1] == 0 && i-cnt-2 >=0 && pDoc->baduk[r][i-cnt-2] == 2)
			{
				pDoc->baduk[r][i-cnt-1] = 2;
				m_sunseo = true;
				m_row = r; m_col =i-cnt-1;
				Invalidate(false);
				return 1;
			}
			
			count = 0;
		}
		
	}

	count = 0;
	for (i = 0; i<19; i++){
		if (pDoc->baduk[i][c] == 2) count++;
		else
		{
			if( count == cnt && pDoc->baduk[i][c] == 0 && i+1<= 18 && pDoc->baduk[i+1][c] == 2 )
			{
				pDoc->baduk[i][c] = 2;
				m_sunseo = true;
				m_row = i; m_col =c;
				Invalidate(false);
				return 1;
			}
			if( count == cnt && i-cnt-1 >= 0 && pDoc->baduk[i-cnt-1][c] == 0 && i-cnt-2 >= 0 && pDoc->baduk[i-cnt-2][c] == 2)
			{
				pDoc->baduk[i-cnt-1][c] = 2;
				m_sunseo = true;
				m_row = i-cnt-1; m_col =c;
				Invalidate(false);
				return 1;
			}

			
			count = 0;
		}
	}

	int srow, scol;
	int erow, ecol;
	int tr, tc;
	tr = r; tc = c;
	while (tr != 0 && tc != 0){
				tr--;
				tc--;
	}
	

	srow = tr; scol = tc;

	tr = r; tc = c;

	while (tr != 18 && tc!= 18){
		tr++;
		tc++;
	}


	erow = tr; ecol = tc;
	count = 0;

	while (scol <= ecol && srow <= erow){
		if (pDoc->baduk[srow][scol] == 2) count++;
		else
		{
			if( count == cnt && pDoc->baduk[srow][scol] == 0 && srow+1<=18 && scol+1<=18 && pDoc->baduk[srow+1][scol+1] == 2 )
			{
				pDoc->baduk[srow][scol] = 2;
				m_sunseo = true;
				m_row = srow; m_col =scol;
				Invalidate(false);
				return 1;
			}
			
			if( count == cnt && srow-cnt-1 >=0 && scol-cnt-1 >= 0 && pDoc->baduk[srow-cnt-1][scol-cnt-1] == 0 && srow-cnt-2 >=0 && scol-cnt-2 >= 0 && pDoc->baduk[srow-cnt-2][scol-cnt-2] == 2)
			{
				pDoc->baduk[srow-cnt-1][scol-cnt-1] = 2;
				m_sunseo = true;
				m_row = srow-cnt-1; m_col =scol-cnt-1;
				Invalidate(false);
				return 1;
			}
			
			count = 0;
		}
		srow++;
		scol++;

	}


	tr = r; tc = c;

	while (tr != 0 && tc != 18){
		tr--;
		tc++;
	}

	srow = tr; scol = tc;

	tr = r; tc = c;
	while (tr != 18 && tc != 0){
		tr++;
		tc--;
	}

	erow = tr; ecol = tc;
	count = 0;

	while (scol >= ecol && srow <= erow){
		if (pDoc->baduk[srow][scol] == 2) count ++;
		else
		{
			if( count == cnt && pDoc->baduk[srow][scol] == 0 && srow+1 <= 18 && scol-1>=0 && pDoc->baduk[srow+1][scol-1] == 2)
			{
				pDoc->baduk[srow][scol] = 2;
				m_sunseo = true;
				m_row = srow; m_col =scol;
				Invalidate(false);
				return 1;
			}
			if( count == cnt && srow-cnt-1 >= 0 && scol+cnt+1 <= 18 && pDoc->baduk[srow-cnt-1][scol+cnt+1] == 0 && srow-cnt-2 >= 0 && scol+cnt+2 <= 18 && pDoc->baduk[srow-cnt-2][scol+cnt+2] == 2)
			{
				pDoc->baduk[srow-cnt-1][scol+cnt+1] = 2;
				m_sunseo = true;
				m_row = srow; m_col =scol;
				Invalidate(false);
				return 1;
			}
			
			count = 0;
		}
		srow++;
		scol--;
	}

	return 0;
	
}
