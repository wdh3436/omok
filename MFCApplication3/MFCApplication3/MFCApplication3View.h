
// MFCApplication3View.h : CMFCApplication3View Ŭ������ �������̽�
//

#pragma once

#include "SubDialog.h"
#include "SubDialog2.h"
#include "MFCApplication3Doc.h"

class CMFCApplication3View : public CFormView
{
protected: // serialization������ ��������ϴ�.
	CMFCApplication3View();
	DECLARE_DYNCREATE(CMFCApplication3View)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_MFCAPPLICATION3_FORM };
#endif

// Ư���Դϴ�.
public:
	CMFCApplication3Doc* GetDocument() const;
	void CMFCApplication3View::OnDraw(CDC *pDC);

	void CMFCApplication3View::OmokGround(CDC *pDC) {      // ������ ����
		CDC memDC;
		CBitmap bitmap, *poldbitmap;;

		bitmap.LoadBitmapW(IDB_BITMAP9);
		memDC.CreateCompatibleDC(pDC);

		poldbitmap = memDC.SelectObject(&bitmap);
		pDC->BitBlt(250, 100, 540, 540, &memDC, 0, 0, SRCCOPY);
		memDC.SelectObject(poldbitmap);
	}
	void CMFCApplication3View::BackGround(CDC *pDC) {      // ��� ����
		CDC memDC;
		CBitmap bitmap, *poldbitmap;;

		bitmap.LoadBitmapW(IDB_BACKGROUND3);
		memDC.CreateCompatibleDC(pDC);

		poldbitmap = memDC.SelectObject(&bitmap);

		pDC->StretchBlt(0, 0, 1057, 793, &memDC, 0, 0, 1057, 793, SRCCOPY);
		memDC.SelectObject(poldbitmap);

	}
	void CMFCApplication3View::BackGround2(CDC *pDC);
// �۾��Դϴ�.
public:
	boolean m_start;  //���� ������ '1'�� �ٲ� �ٵ����� �׷���
	
	BOOL m_sunseo;    // false =�� true = ��
	int m_row, m_col; // ��ġ���� ����
	int b_win, w_win;
	int c_row, c_col;
	int strSeconds, TimeSet; // Ÿ�̸ӱ�� ��,��
	bool m_set; // Ÿ�̸ӱ�� ���� ���ư��� ����
	
	BOOL m_computerStart;
	bool player_black;

	CSubDialog subDlg;
	CSubDialog2 subDlg2;

	int mouseCount;
	int trace;
	
	int timeSelect; // �ð����� ����
	int winCount; // �¼� ī��Ʈ

	enum pick{btn1=1};  // btn1= ���۹�ư
// �������Դϴ�.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	virtual void OnInitialUpdate(); // ���� �� ó�� ȣ��Ǿ����ϴ�.

	
// �����Դϴ�.
public:
	virtual ~CMFCApplication3View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	
	afx_msg void OnClickedStart();  // ���۹�ư �޽��� ó��
	afx_msg void OnClickedConfig(); // ������ư �޽��� ó��
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);  
	
	int Checkvictory(int a, int r, int c);
	
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	int AI(int r, int c);
	void Delay(long d);
	int ibaduk[19][19];
	int obaduk[19][19];   //  ����
	int dbaduk[19][19];   //  ��뵹
	int AI_White_Do(int r, int c);            //�����Բ�
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
		six = 300000,            //6��
		o_five = 20000,         //5�� ����
		d_five = 3000,         //5�� ����
		o_four = 800,          //4�� ����
		d_four = 700,          //4�� ����
		o_four_three = 900,         //4_3�� ����
		d_four_three = 600,         //4_3�� ����

	};
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
	int murgi();
};

#ifndef _DEBUG  // MFCApplication3View.cpp�� ����� ����
inline CMFCApplication3Doc* CMFCApplication3View::GetDocument() const
   { return reinterpret_cast<CMFCApplication3Doc*>(m_pDocument); }
#endif

