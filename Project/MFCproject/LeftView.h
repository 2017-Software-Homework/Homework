#pragma once

#include "RightView.h"
// CLeftView 视图

struct point_array
{
	int operation;
	int count_num;
	CPoint point;

	point_array* next;
};

struct rect_array
{

	int operation;
	int count_num;
	CPoint point1;
	CPoint point2;

	rect_array* next;
};

struct circle_array
{
	int operation;
	int count_num;
	CPoint central;
	int radius;

	circle_array* next;

};


class CLeftView : public CRightView
{
	DECLARE_DYNCREATE(CLeftView)

public:
	point_array *point_head,*point_temp1,*point_temp2;
	rect_array *rect_head,*rect_temp1,*rect_temp2;
	circle_array *circle_head,*circle_temp1,*circle_temp2;
	int choose_status,operation,choose_rect,choose_circle,load_status;
	double zoom;
	int count;
	int m_startX;
	int m_startY;
	int m_bmstartX;
	int m_bmStartY;
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
};


