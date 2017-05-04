#pragma once


// CLeftView 视图

class CLeftView : public CView
{
	DECLARE_DYNCREATE(CLeftView)

public:
	double zoom;
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
};


