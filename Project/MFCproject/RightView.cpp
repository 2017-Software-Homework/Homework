// RightView.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCproject.h"
#include "RightView.h"


// CRightView

IMPLEMENT_DYNCREATE(CRightView, CFormView)

CRightView::CRightView()
	: CFormView(CRightView::IDD)
{

}

CRightView::~CRightView()
{
}

void CRightView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CRightView, CFormView)
END_MESSAGE_MAP()


// CRightView 诊断

#ifdef _DEBUG
void CRightView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CRightView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CRightView 消息处理程序
