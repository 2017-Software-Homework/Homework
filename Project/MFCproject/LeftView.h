#pragma once
// CLeftView 视图
#include "Data.h"
extern COLORREF color_to_set,color,color1;
extern int color_change;
extern int color_status;
extern int red,green,blue;



class CLeftView : public CView
{
	DECLARE_DYNCREATE(CLeftView)

public:	
	int choose_status,operation,choose_rect,choose_circle,load_status,show_status;
	double zoom;
	int m_startX;
	int m_startY;//图片相对位置
	int m_bmstartX;
	int m_bmStartY;//没什么用
	CString BmpName;
	CString extname;
	CBitmap m_bitmap;
	void ShowBitmap(CString BmpName,CDC *pDC);
	CRect Rect;
	CPoint lkeydown,lkeyup;
	int distance(CPoint p1,CPoint p2);
	void ShowInformation(CDC *pDC);

protected:
	CLeftView();           // 动态创建所使用的受保护的构造函数
	virtual ~CLeftView();

public:
	virtual void OnDraw(CDC* pDC);      // 重写以绘制该视图
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFileOpen();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnEditRefresh();
	afx_msg void OnChoosePoint();
	afx_msg void OnChooseCircle();
	afx_msg void OnChooseRect();
	afx_msg void OnUpdateChoosePoint(CCmdUI *pCmdUI);
	afx_msg void OnUpdateChooseRect(CCmdUI *pCmdUI);
	afx_msg void OnUpdateChooseCircle(CCmdUI *pCmdUI);
	afx_msg void OnAnd();
	afx_msg void OnOr();
	afx_msg void OnMinus();
	afx_msg void OnUpdateAnd(CCmdUI *pCmdUI);
	afx_msg void OnUpdateOr(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMinus(CCmdUI *pCmdUI);
	afx_msg void OnSetColor();
	afx_msg void OnViewShow();
	afx_msg void OnUpdateViewShow(CCmdUI *pCmdUI);
	bool IsInChoose(CPoint p,CDC *pDC);
	bool PointInRect(CPoint p,CPoint point1,CPoint point2);
	afx_msg void OnEditClear();
	bool ChangeOrNot(CPoint p,CDC *pDC);
	COLORREF ColorChangeTo(CPoint p,CDC *pDC);
	afx_msg void OnSelectColor();
	afx_msg void OnUpdateSetColor(CCmdUI *pCmdUI);
	afx_msg void OnUpdateSelectColor(CCmdUI *pCmdUI);
};