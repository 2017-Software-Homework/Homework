// RightView.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCproject.h"
#include "RightView.h"


// CRightView

IMPLEMENT_DYNCREATE(CRightView, CView)

CRightView::CRightView()
{
	point_pos.x = 0;
	point_pos.y = 0;
	red = green = blue = 0;
}

CRightView::~CRightView()
{
}

BEGIN_MESSAGE_MAP(CRightView, CView)
END_MESSAGE_MAP()


// CRightView 绘图

void CRightView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 在此添加绘制代码
}


// CRightView 诊断

#ifdef _DEBUG
void CRightView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CRightView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CRightView 消息处理程序
