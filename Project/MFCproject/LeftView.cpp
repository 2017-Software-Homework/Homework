// LeftView.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCproject.h"
#include "LeftView.h"
#include <math.h>

// CLeftView

IMPLEMENT_DYNCREATE(CLeftView, CView)

CLeftView::CLeftView()
{
	operation = 1;
	choose_status = 1;
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
END_MESSAGE_MAP()


// CLeftView 绘图

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
	// TODO: 在此添加绘制代码
}


// CLeftView 诊断

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


// CLeftView 消息处理程序
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
    filter="所有文件(*.bmp,*.jpg,*.gif,*tiff)|*.bmp;*.jpg;*.gif;*.tiff| BMP(*.bmp)|*.bmp| JPG(*.jpg)|*.jpg| GIF(*.gif)|*.gif| TIFF(*.tiff)|*.tiff||";  
    CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY,filter,NULL);
	if (IDOK == dlg.DoModal())
	{
		BmpName.Format(_T("%s"),dlg.GetPathName());
		extname = dlg.GetFileExt();
		extname.MakeLower();
		Invalidate();
	}
	// TODO: 在此添加命令处理程序代码
}



BOOL CLeftView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
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
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	lkeydown = point;
	CView::OnLButtonDown(nFlags, point);
}


void CLeftView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	lkeyup = point;
	if (distance(lkeyup,lkeydown) >= 5)
	{
		m_startX += (lkeyup.x - lkeydown.x);
		m_startY += (lkeyup.y - lkeydown.y);
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
	// TODO: 在此添加命令处理程序代码
	Invalidate();
}


void CLeftView::OnChoosePoint()
{
	// TODO: 在此添加命令处理程序代码
	choose_status = 1;
}


void CLeftView::OnChooseCircle()
{
	// TODO: 在此添加命令处理程序代码
	choose_status = 3;
}


void CLeftView::OnChooseRect()
{
	// TODO: 在此添加命令处理程序代码
	choose_status = 2;
}


void CLeftView::OnUpdateChoosePoint(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(choose_status == 1);
}


void CLeftView::OnUpdateChooseRect(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(choose_status == 2);
}


void CLeftView::OnUpdateChooseCircle(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(choose_status == 3);
}


void CLeftView::OnAnd()
{
	// TODO: 在此添加命令处理程序代码
	operation = 1;
}


void CLeftView::OnOr()
{
	// TODO: 在此添加命令处理程序代码
	operation = 2;
}


void CLeftView::OnMinus()
{
	// TODO: 在此添加命令处理程序代码
	operation  = 3;
}


void CLeftView::OnUpdateAnd(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(operation == 1);
}


void CLeftView::OnUpdateOr(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(operation == 2);
}


void CLeftView::OnUpdateMinus(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(operation == 3);
}
