// LeftView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCproject.h"
#include "LeftView.h"
#include <math.h>

// CLeftView

IMPLEMENT_DYNCREATE(CLeftView, CView)

CLeftView::CLeftView()
{
	zoom = 1.0;
	m_startX = 0;
	m_startY = 0;
	m_bmstartX = 0;
	m_bmStartY = 0;
	
}

CLeftView::~CLeftView()
{
}

BEGIN_MESSAGE_MAP(CLeftView, CView)
	ON_COMMAND(ID_FILE_OPEN, &CLeftView::OnFileOpen)
	ON_COMMAND(ID_FILE_OPEN, &CLeftView::OnFileOpen)
	ON_WM_MOUSEWHEEL()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
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
int CLeftView::distance(CPoint p1,CPoint p2)
{
	double d1 = p1.x - p2.x;
	double d2 = p1.y - p2.y;
	return int(sqrt(d1 * d1 + d2 * d2));
}



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

	pDC->StretchBlt(m_startX,m_startY,int (m_bmp.bmWidth * percentage * zoom) ,int (m_bmp.bmHeight * percentage * zoom),&dcBmp,m_bmstartX,m_bmStartY,m_bmp.bmWidth,m_bmp.bmHeight,SRCCOPY);
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



BOOL CLeftView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CRect Rect;
	GetWindowRect(Rect);
	CPoint p;
	p.x = pt.x - Rect.left;
	p.y = pt.y - Rect.top;
	if (zoom <= 20 && zoom > 0.1)
		zoom *= (1.0 + double(zDelta) / 2400);
	m_startX = p.x - double(p.x - m_startX) * (1.0 + double(zDelta) / 2400);
	m_startY = p.y - double(p.y - m_startY) * (1.0 + double(zDelta) / 2400);
	Invalidate();
	return TRUE;
}



void CLeftView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	lkeydown = point;
	CView::OnLButtonDown(nFlags, point);
}


void CLeftView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	lkeyup = point;
	if (distance(lkeyup,lkeydown) > 8)
	{
		m_startX += (lkeyup.x - lkeydown.x);
		m_startY += (lkeyup.y - lkeydown.y);
	}
	else
	{
		CRect Rect;
		GetWindowRect(Rect);
		HDC hDC = ::GetDC(NULL);
		color = ::GetPixel(hDC,lkeydown.x + Rect.left,lkeydown.y + Rect.top);
		red = GetRValue(color);  
		green = GetGValue(color);  
		blue = GetBValue(color); 
		point_pos = lkeydown;
	}
	Invalidate();
	CView::OnLButtonUp(nFlags, point);
}


