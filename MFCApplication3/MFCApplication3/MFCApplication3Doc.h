
// MFCApplication3Doc.h : CMFCApplication3Doc Ŭ������ �������̽�
//


#pragma once


class CMFCApplication3Doc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CMFCApplication3Doc();
	DECLARE_DYNCREATE(CMFCApplication3Doc)

// Ư���Դϴ�.
public:
	int baduk[19][19];
// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// �����Դϴ�.
public:
	virtual ~CMFCApplication3Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// �˻� ó���⿡ ���� �˻� �������� �����ϴ� ����� �Լ�
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
