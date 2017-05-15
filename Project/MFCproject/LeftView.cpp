// LeftView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCproject.h"
#include "LeftView.h"
#include <math.h>
#include "ProjectDialog.h"

// CLeftView

IMPLEMENT_DYNCREATE(CLeftView, CView)

CLeftView::CLeftView()
{
	operation = 1;
	choose_status = 1;
	load_status = 0;
	zoom = 1.0;
	m_startX = 0;
	m_startY = 0;
	m_bmstartX = 0;
	m_bmStartY = 0;

	choose_rect = 1;
	choose_circle = 1;

	count = 1;

	point_head = point_temp1 = point_temp2 = NULL;
	rect_head = rect_temp1 = rect_temp2 = NULL;
	circle_head = circle_temp1 = circle_temp2 = NULL;
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
	ON_COMMAND(ID_EDIT_REFRESH, &CLeftView::OnEditRefresh)
	ON_COMMAND(ID_CHOOSE_POINT, &CLeftView::OnChoosePoint)
	ON_COMMAND(ID_CHOOSE_CIRCLE, &CLeftView::OnChooseCircle)
	ON_COMMAND(ID_CHOOSE_RECT, &CLeftView::OnChooseRect)
	ON_UPDATE_COMMAND_UI(ID_CHOOSE_POINT, &CLeftView::OnUpdateChoosePoint)
	ON_UPDATE_COMMAND_UI(ID_CHOOSE_RECT, &CLeftView::OnUpdateChooseRect)
	ON_UPDATE_COMMAND_UI(ID_CHOOSE_CIRCLE, &CLeftView::OnUpdateChooseCircle)
	ON_COMMAND(ID_AND, &CLeftView::OnAnd)
	ON_COMMAND(ID_OR, &CLeftView::OnOr)
	ON_COMMAND(ID_MINUS, &CLeftView::OnMinus)
	ON_UPDATE_COMMAND_UI(ID_AND, &CLeftView::OnUpdateAnd)
	ON_UPDATE_COMMAND_UI(ID_OR, &CLeftView::OnUpdateOr)
	ON_UPDATE_COMMAND_UI(ID_MINUS, &CLeftView::OnUpdateMinus)
//	ON_COMMAND(ID_SET_COLOR, &CLeftView::OnSetColor)
ON_COMMAND(ID_SET_COLOR, &CLeftView::OnSetColor)
END_MESSAGE_MAP()


// CLeftView ��ͼ

void CLeftView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	
	if (extname.Compare(_T("bmp")) == 0)
	{
		ShowBitmap(BmpName,pDC);
	}
	if(load_status == 1)
		ShowInformation(pDC);
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
	load_status = 1;
//	Invalidate();
	
}

void CLeftView::ShowInformation(CDC *pDC)
{
	CString s1,s2,s3,s4,s5;
	CString S1,S2,S3;
	s1.Format(_T("��ѡ���"));
	s2.Format(_T("��ѡ����εĵ�һ����"));
	s3.Format(_T("��ѡ����εĵڶ�����"));
	s4.Format(_T("��ѡ��Բ��"));
	s5.Format(_T("��ѡ��Բ����һ��"));
	S1.Format(_T("Ŀǰ��������:��"));
	S2.Format(_T("Ŀǰ��������:��"));
	S3.Format(_T("Ŀǰ��������:��"));
	if (choose_status == 1)
	{
		pDC->TextOutW(0,0,s1);
	}
	if(choose_status == 2)
	{
		if(choose_rect == 1)
			pDC->TextOutW(0,0,s2);
		else
			pDC->TextOutW(0,0,s3);
	}
	if(choose_status == 3)
	{
		if(choose_circle == 1)
			pDC->TextOutW(0,0,s4);
		else
			pDC->TextOutW(0,0,s5);
	}
	if(operation == 1)
	{
		pDC->TextOutW(0,20,S1);
	}
	if(operation == 2)
	{
		pDC->TextOutW(0,20,S2);

	}
	if(operation == 3)
	{
		pDC->TextOutW(0,20,S3);
	}
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
	if ((zoom <= 20 && zoom >= 0.1) || (zoom > 20 && zDelta < 0) || ( zoom < 0.1 && zDelta > 0))
		zoom *= (1.0 + double(zDelta) / 2400);
	m_startX = p.x - double(p.x - m_startX) * (1.0 + double(zDelta) / 2400.0);
	m_startY = p.y - double(p.y - m_startY) * (1.0 + double(zDelta) / 2400.0);
	for (point_temp1 = point_head;point_temp1 != NULL;point_temp1 = point_temp1->next)
	{
		point_temp1->point.x = p.x - double(p.x - point_temp1->point.x) * (1.0 + double(zDelta) / 2400.0);
		point_temp1->point.y = p.y - double(p.y - point_temp1->point.y) * (1.0 + double(zDelta) / 2400.0);
	}
	for(rect_temp1 = rect_head;rect_temp1 != NULL;rect_temp1 = rect_temp1->next)
	{
		rect_temp1->point1.x = p.x - double(p.x - rect_temp1->point1.x) * (1.0 + double(zDelta) / 2400.0);
		rect_temp1->point1.y = p.y - double(p.y - rect_temp1->point1.y) * (1.0 + double(zDelta) / 2400.0);
		rect_temp1->point2.x = p.x - double(p.x - rect_temp1->point2.x) * (1.0 + double(zDelta) / 2400.0);
		rect_temp1->point2.y = p.y - double(p.y - rect_temp1->point2.y) * (1.0 + double(zDelta) / 2400.0);
	}
	for (circle_temp1 = circle_head;circle_temp1 != NULL;circle_temp1 = circle_temp1->next)
	{
		circle_temp1->central.x = p.x - double(p.x - circle_temp1->central.x) * (1.0 + double(zDelta) / 2400.0);
		circle_temp1->central.y = p.y - double(p.y - circle_temp1->central.y) * (1.0 + double(zDelta) / 2400.0);
		circle_temp1->radius = circle_temp1->radius * (1.0 + double(zDelta) / 2400.0);
	}
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
	if (distance(lkeyup,lkeydown) >= 5)
	{
		m_startX += (lkeyup.x - lkeydown.x);
		m_startY += (lkeyup.y - lkeydown.y);
		for (point_temp1 = point_head;point_temp1 != NULL;point_temp1 = point_temp1->next)
		{
			point_temp1->point.x += (lkeyup.x - lkeydown.x);
			point_temp1->point.y += (lkeyup.y - lkeydown.y);
		}
		for(rect_temp1 = rect_head;rect_temp1 != NULL;rect_temp1 = rect_temp1->next)
		{
			rect_temp1->point1.x += (lkeyup.x - lkeydown.x);
			rect_temp1->point1.y += (lkeyup.y - lkeydown.y);
			rect_temp1->point2.x += (lkeyup.x - lkeydown.x);
			rect_temp1->point2.y += (lkeyup.y - lkeydown.y);
		}
		for (circle_temp1 = circle_head;circle_temp1 != NULL;circle_temp1 = circle_temp1->next)
		{
			circle_temp1->central.x += (lkeyup.x - lkeydown.x);
			circle_temp1->central.y += (lkeyup.y - lkeydown.y);
		}
	}
	else
	{
		if(choose_status == 1)
		{
			CRect Rect;
			GetWindowRect(Rect);
			HDC hDC = ::GetDC(NULL);
			color = ::GetPixel(hDC,lkeydown.x + Rect.left,lkeydown.y + Rect.top);
			red = GetRValue(color);
			green = GetGValue(color);
			blue = GetBValue(color); 
			point_pos = lkeydown;

			if (point_head == NULL)
			{
				point_head = new point_array;
				point_head->operation = operation;
				point_head->count_num = count;
				point_head->point = lkeydown;
				point_head->next = NULL;
				point_temp2 = point_head;
				count++;
			}
			else
			{
				point_temp1 = new point_array;
				point_temp1->operation = operation;
				point_temp1->point = lkeydown;
				point_temp1->count_num = count;
				point_temp1->next = NULL;
				point_temp2->next = point_temp1;
				point_temp2 = point_temp1;
				count++;
			}

		}
		if (choose_status == 2)
		{
			if (choose_rect == 1)
			{
				if (rect_head == NULL)
				{
					rect_head = new rect_array;
					rect_head->operation = operation;
					rect_head->point1 = lkeydown;
					rect_head->count_num = count;
					rect_head->next = NULL;
					rect_temp2 = rect_head;
				}
				else
				{
					rect_temp1 = new rect_array;
					rect_temp1->operation = operation;
					rect_temp1->point1 = lkeydown;
					rect_temp1->count_num = count;
					rect_temp1->next = NULL;
					rect_temp2->next = rect_temp1;
					rect_temp2 = rect_temp1;
				}
				choose_rect = 2;
			}
			else
			{
				if (rect_head->next == NULL)
				{
					rect_head->point2 = lkeydown;
				}
				else
				{
					rect_temp2->point2 = lkeydown;
				}
				choose_rect = 1;
				count++;
			}

		}
		if (choose_status == 3)
		{
			if (choose_circle == 1)
			{
				if (circle_head == NULL)
				{
					circle_head = new circle_array;
					circle_head->operation = operation;
					circle_head->central = lkeydown;
					circle_head->count_num = count;
					circle_head->next = NULL;
					circle_temp2 = circle_head;
				}
				else
				{
					circle_temp1 = new circle_array;
					circle_temp1->operation = operation;
					circle_temp1->central = lkeydown;
					circle_temp1->count_num = count;
					circle_temp1->next = NULL;
					circle_temp2->next = circle_temp1;
					circle_temp2 = circle_temp1;
				}
				choose_circle = 2;
			}
			else
			{
				if (circle_head->next == NULL)
				{
					circle_head->radius = distance(lkeydown,circle_head->central);
				}
				else
				{
					circle_temp2->radius = distance(lkeydown,circle_temp2->central);
				}
				choose_circle = 1;
				count++;
			}
		}
	}
	Invalidate();
	CView::OnLButtonUp(nFlags, point);
}


void CLeftView::OnEditRefresh()
{
	// TODO: �ڴ���������������
	Invalidate();
}


void CLeftView::OnChoosePoint()
{
	// TODO: �ڴ���������������
	choose_status = 1;
	Invalidate();
}


void CLeftView::OnChooseRect()
{
	// TODO: �ڴ���������������
	choose_status = 2;
	Invalidate();
}

void CLeftView::OnChooseCircle()
{
	// TODO: �ڴ���������������
	choose_status = 3;
	Invalidate();
}

void CLeftView::OnUpdateChoosePoint(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetCheck(choose_status == 1);
	pCmdUI->Enable(!((choose_circle == 2) || (choose_rect == 2)));
}


void CLeftView::OnUpdateChooseRect(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetCheck(choose_status == 2);
	pCmdUI->Enable (!((choose_circle == 2) || (choose_rect == 2)));
}


void CLeftView::OnUpdateChooseCircle(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetCheck(choose_status == 3);
	pCmdUI->Enable(!((choose_circle == 2) || (choose_rect == 2)));
}


void CLeftView::OnAnd()
{
	// TODO: �ڴ���������������
	operation = 1;
	Invalidate();
}


void CLeftView::OnOr()
{
	// TODO: �ڴ���������������
	operation = 2;
	Invalidate();
}


void CLeftView::OnMinus()
{
	// TODO: �ڴ���������������
	operation  = 3;
	Invalidate();
}


void CLeftView::OnUpdateAnd(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetCheck(operation == 1);
	pCmdUI->Enable(!((choose_circle == 2) || (choose_rect == 2)));
}


void CLeftView::OnUpdateOr(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetCheck(operation == 2);
	pCmdUI->Enable(!((choose_circle == 2) || (choose_rect == 2)));
}


void CLeftView::OnUpdateMinus(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetCheck(operation == 3);
	pCmdUI->Enable(!((choose_circle == 2) || (choose_rect == 2)));
}



void CLeftView::OnSetColor()
{
	// TODO: �ڴ���������������
	ProjectDialog *td=new ProjectDialog;
	td->Create(IDD_SET_COLOR,this);
	td->ShowWindow(SW_SHOW);	
}
