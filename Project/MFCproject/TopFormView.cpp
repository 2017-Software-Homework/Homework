// TopFormView.cpp : ʵ���ļ�
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


// CTopFormView ���

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


// CTopFormView ��Ϣ�������
