
// MFCApplication3.h : MFCApplication3 ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CMFCApplication3App:
// �� Ŭ������ ������ ���ؼ��� MFCApplication3.cpp�� �����Ͻʽÿ�.
//

class CMFCApplication3App : public CWinApp
{
public:
	CMFCApplication3App();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMFCApplication3App theApp;
