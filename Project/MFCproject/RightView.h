#pragma once
#include "Data.h"

extern COLORREF color_to_set,color;
extern int color_change;
extern int red,green,blue;

// CRightView 视图

class CRightView : public CView
{
	DECLARE_DYNCREATE(CRightView)


public:
	CPoint point_pos;
	COLORREF changed_color;
	void ShowTheColor(CDC *pDC);

protected:
	CRightView();           // 动态创建所使用的受保护的构造函数
	virtual ~CRightView();

public:
	void OnDraw(CDC* pDC);      // 重写以绘制该视图
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


