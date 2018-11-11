
// MFCApplication3View.h : CMFCApplication3View 클래스의 인터페이스
//

#pragma once

#include "SubDialog.h"
#include "SubDialog2.h"
#include "MFCApplication3Doc.h"

class CMFCApplication3View : public CFormView
{
protected: // serialization에서만 만들어집니다.
	CMFCApplication3View();
	DECLARE_DYNCREATE(CMFCApplication3View)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_MFCAPPLICATION3_FORM };
#endif

// 특성입니다.
public:
	CMFCApplication3Doc* GetDocument() const;
	void CMFCApplication3View::OnDraw(CDC *pDC);

	void CMFCApplication3View::OmokGround(CDC *pDC) {      // 오목판 생성
		CDC memDC;
		CBitmap bitmap, *poldbitmap;;

		bitmap.LoadBitmapW(IDB_BITMAP9);
		memDC.CreateCompatibleDC(pDC);

		poldbitmap = memDC.SelectObject(&bitmap);
		pDC->BitBlt(250, 100, 540, 540, &memDC, 0, 0, SRCCOPY);
		memDC.SelectObject(poldbitmap);
	}
	void CMFCApplication3View::BackGround(CDC *pDC) {      // 배경 생성
		CDC memDC;
		CBitmap bitmap, *poldbitmap;;

		bitmap.LoadBitmapW(IDB_BACKGROUND3);
		memDC.CreateCompatibleDC(pDC);

		poldbitmap = memDC.SelectObject(&bitmap);

		pDC->StretchBlt(0, 0, 1057, 793, &memDC, 0, 0, 1057, 793, SRCCOPY);
		memDC.SelectObject(poldbitmap);

	}
	void CMFCApplication3View::BackGround2(CDC *pDC);
// 작업입니다.
public:
	boolean m_start;  //시작 누르면 '1'로 바뀌어서 바둑판이 그려짐
	
	BOOL m_sunseo;    // false =백 true = 흑
	int m_row, m_col; // 위치지정 변수
	int b_win, w_win;
	int c_row, c_col;
	int strSeconds, TimeSet; // 타이머기능 분,초
	bool m_set; // 타이머기능 순서 돌아가는 변수
	
	BOOL m_computerStart;
	bool player_black;

	CSubDialog subDlg;
	CSubDialog2 subDlg2;

	int mouseCount;
	int trace;
	
	int timeSelect; // 시간설정 변수
	int winCount; // 승수 카운트

	enum pick{btn1=1};  // btn1= 시작버튼
// 재정의입니다.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.

	
// 구현입니다.
public:
	virtual ~CMFCApplication3View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	
	afx_msg void OnClickedStart();  // 시작버튼 메시지 처리
	afx_msg void OnClickedConfig(); // 설정버튼 메시지 처리
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);  
	
	int Checkvictory(int a, int r, int c);
	
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	int AI(int r, int c);
	void Delay(long d);
	int ibaduk[19][19];
	int obaduk[19][19];   //  내돌
	int dbaduk[19][19];   //  상대돌
	int AI_White_Do(int r, int c);            //교수님꺼
	int CMFCApplication3View::hansu_ap(int o, int d, int r, int c);

	void defendWeight(int o, int d);
	void OffendWeight(int o, int d);
	void OffendWeight3(int o, int d);
	void OffendWeight4(int o, int d);
	void OffendWeight4_2(int o, int d);
	void OffendWeight4_3_1(int o, int d);
	void OffendWeight4_3(int o, int d);
	void OffendWeight4_3_2(int o, int d);
	void OffendWeight4_3_3(int o, int d);
	void OffendWeight5(int o, int d);
	void OffendWeight5_2(int o, int d);
	void OffendWeight5_3(int o, int d);
	void OffendWeight6(int o, int d);
	void OffendWeight6_2(int o, int d);
	void CMFCApplication3View::OffendWeight6_3(int o, int d);


	void dffendWeight_three_by_three(int o, int d);
	void offendWeight_three_by_three(int o, int d);

	enum weight {
		six = 300000,            //6목
		o_five = 20000,         //5목 공격
		d_five = 3000,         //5목 수비
		o_four = 800,          //4목 공격
		d_four = 700,          //4목 수비
		o_four_three = 900,         //4_3목 공격
		d_four_three = 600,         //4_3목 수비

	};
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
	int murgi();
};

#ifndef _DEBUG  // MFCApplication3View.cpp의 디버그 버전
inline CMFCApplication3Doc* CMFCApplication3View::GetDocument() const
   { return reinterpret_cast<CMFCApplication3Doc*>(m_pDocument); }
#endif

