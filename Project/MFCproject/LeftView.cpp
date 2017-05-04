// LeftView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCproject.h"
#include "LeftView.h"


// CLeftView

IMPLEMENT_DYNCREATE(CLeftView, CView)

CLeftView::CLeftView()
{

}

CLeftView::~CLeftView()
{
}

BEGIN_MESSAGE_MAP(CLeftView, CView)
	ON_COMMAND(ID_FILE_OPEN, &CLeftView::OnFileOpen)
	ON_COMMAND(ID_FILE_OPEN, &CLeftView::OnFileOpen)
END_MESSAGE_MAP()


// CLeftView ��ͼ

void CLeftView::OnDraw(CDC* pDC)
{
	


	if (extname.Compare(_T("bmp")) == 0)
	{
		ShowBitmap(BmpName,pDC);
	}
	// TODO: �ڴ���ӻ��ƴ���
}


// CLeftView ���

#ifdef _DEBUG
void CLeftView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CLeftView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CLeftView ��Ϣ�������




void CLeftView::ShowBitmap(CString BmpName,CDC *pDC)
{
	
	HBITMAP m_hBitmap = (HBITMAP)LoadImage(NULL,BmpName,IMAGE_BITMAP,0,0,LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);	
		
	if (m_bitmap.m_hObject)
	{
		m_bitmap.Detach();
	}
	m_bitmap.Attach(m_hBitmap);

	CRect rect;
	GetClientRect(&rect);

	int m_showX = 0;
	int m_showY = 0;
	int m_nWindowWidth = rect.right - rect.left;
	int m_nWindowHeight = rect.bottom - rect.top;

	CDC dcBmp;
	if(!dcBmp.CreateCompatibleDC(pDC))
		return;

	
	BITMAP m_bmp;
	m_bitmap.GetBitmap(&m_bmp);

	CBitmap *pbmpOld = NULL;
	dcBmp.SelectObject(&m_bitmap);
	
	double percentage,percentage1,percentage2;
	percentage1 = double (m_nWindowWidth) / double(m_bmp.bmWidth);
	percentage2 = double(m_nWindowHeight) / double(m_bmp.bmHeight);
	percentage = percentage1 > percentage2 ? percentage2 : percentage1;

	pDC->StretchBlt(0,0,int (m_bmp.bmWidth * percentage) ,int (m_bmp.bmHeight * percentage),&dcBmp,0,0,m_bmp.bmWidth,m_bmp.bmHeight,SRCCOPY);
	dcBmp.SelectObject(pbmpOld);
	DeleteObject(&m_bitmap);
	dcBmp.DeleteDC();
//	Invalidate();
	
}

void CLeftView::OnFileOpen()
{
	CString filter;  
    filter="�����ļ�(*.bmp,*.jpg,*.gif,*tiff)|*.bmp;*.jpg;*.gif;*.tiff| BMP(*.bmp)|*.bmp| JPG(*.jpg)|*.jpg| GIF(*.gif)|*.gif| TIFF(*.tiff)|*.tiff||";  
    CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY,filter,NULL);
	if (IDOK == dlg.DoModal())
	{
		BmpName.Format(_T("%s"),dlg.GetPathName());
		extname = dlg.GetFileExt();
		extname.MakeLower();
		Invalidate();
	}
	// TODO: �ڴ���������������
}

