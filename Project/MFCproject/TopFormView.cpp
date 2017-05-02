// TopFormView.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCproject.h"
#include "TopFormView.h"


// CTopFormView

IMPLEMENT_DYNCREATE(CTopFormView, CFormView)

CTopFormView::CTopFormView()
	: CFormView(CTopFormView::IDD)
{

}

CTopFormView::~CTopFormView()
{
}

void CTopFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTopFormView, CFormView)
END_MESSAGE_MAP()


// CTopFormView 诊断

#ifdef _DEBUG
void CTopFormView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CTopFormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CTopFormView 消息处理程序
