// RightView.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCproject.h"
#include "RightView.h"
#include "ProjectDialog.h"

// CRightView

IMPLEMENT_DYNCREATE(CRightView, CView)

CRightView::CRightView()
{
	point_pos.x = 0;
	point_pos.y = 0;
}

CRightView::~CRightView()
{
}

BEGIN_MESSAGE_MAP(CRightView, CView)
	ON_COMMAND(ID_EDIT_REFRESH, &CRightView::OnEditRefresh)
//	ON_WM_LBUTTONUP()
//ON_COMMAND(ID_SELECT_COLOR, &CRightView::OnSelectColor)
END_MESSAGE_MAP()


// CRightView 绘图

void CRightView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	ShowTheColor(pDC);
	// TODO: 在此添加绘制代码
}

void CRightView::ShowTheColor(CDC *pDC)
{
	CString s_red,s_green,s_blue;
	s_red.Format(_T("R值为:%d"),red);
	s_green.Format(_T("G值为:%d"),green);
	s_blue.Format(_T("B值为:%d"),blue);
	pDC->TextOutW(0,0,s_red);
	pDC->TextOutW(0,20,s_green);
	pDC->TextOutW(0,40,s_blue);
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


void CRightView::OnEditRefresh()
{
	// TODO: 在此添加命令处理程序代码
	Invalidate();
}




