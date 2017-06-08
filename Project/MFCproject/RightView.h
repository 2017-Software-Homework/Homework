#pragma once
#include "Data.h"

extern COLORREF color_to_set,color;
extern int color_change;
extern int red,green,blue;

// CRightView ��ͼ

class CRightView : public CView
{
	DECLARE_DYNCREATE(CRightView)


public:
	CPoint point_pos;
	COLORREF changed_color;
	void ShowTheColor(CDC *pDC);

protected:
	CRightView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CRightView();

public:
	void OnDraw(CDC* pDC);      // ��д�Ի��Ƹ���ͼ
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEditRefresh();
//	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
//	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};


