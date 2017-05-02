// BottomFormView.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCproject.h"
#include "BottomFormView.h"


// CBottomFormView

IMPLEMENT_DYNCREATE(CBottomFormView, CFormView)

CBottomFormView::CBottomFormView()
	: CFormView(CBottomFormView::IDD)
{

}

CBottomFormView::~CBottomFormView()
{
}

void CBottomFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CBottomFormView, CFormView)
END_MESSAGE_MAP()


// CBottomFormView 诊断

#ifdef _DEBUG
void CBottomFormView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CBottomFormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CBottomFormView 消息处理程序
