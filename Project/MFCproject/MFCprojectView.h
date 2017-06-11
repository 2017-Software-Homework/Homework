
// MFCprojectView.h : CMFCprojectView ��Ľӿ�
//

#pragma once


class CMFCprojectView : public CView
{
protected: // �������л�����
	CMFCprojectView();
	DECLARE_DYNCREATE(CMFCprojectView)

// ����
public:
	CMFCprojectDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CMFCprojectView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnAnd();
	afx_msg void OnOr();
	afx_msg void OnMinus();
};

#ifndef _DEBUG  // MFCprojectView.cpp �еĵ��԰汾
inline CMFCprojectDoc* CMFCprojectView::GetDocument() const
   { return reinterpret_cast<CMFCprojectDoc*>(m_pDocument); }
#endif

