// LeftView.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCproject.h"
#include "LeftView.h"
#include <math.h>
#include "ProjectDialog.h"
#include "SelectDiolog.h"

// CLeftView



IMPLEMENT_DYNCREATE(CLeftView, CView)

CLeftView::CLeftView()
{
	operation = 1;
	choose_status = 1;
	load_status = 0;
	show_status = 0;
	zoom = 1.0;
	m_startX = 0;
	m_startY = 0;
	m_bmstartX = 0;
	m_bmStartY = 0;

	choose_rect = 1;
	choose_circle = 1;

	choose_head = choose_temp1 = choose_temp2 = NULL;
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
ON_COMMAND(ID_SET_COLOR, &CLeftView::OnSetColor)
ON_COMMAND(ID_VIEW_SHOW, &CLeftView::OnViewShow)
ON_UPDATE_COMMAND_UI(ID_VIEW_SHOW, &CLeftView::OnUpdateViewShow)
ON_COMMAND(ID_EDIT_CLEAR, &CLeftView::OnEditClear)
ON_COMMAND(ID_SELECT_COLOR, &CLeftView::OnSelectColor)
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
	if(load_status == 1)
		ShowInformation(pDC);
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
	pDC->SetStretchBltMode(STRETCH_HALFTONE);//防止失真
	pDC->StretchBlt(m_startX,m_startY,int (m_bmp.bmWidth * percentage * zoom) ,int (m_bmp.bmHeight * percentage * zoom),&dcBmp,m_bmstartX,m_bmStartY,m_bmp.bmWidth,m_bmp.bmHeight,SRCCOPY);

	if (color_status == 1)
	{
		color_status = 0;
		choose_generate1 = new choose_array;
		choose_generate1->change_color = 1;
		choose_generate1->left_or_right = 0;
		choose_generate1->color_to_set = color;
		choose_generate1->next = NULL;
		choose_generate2->next = choose_generate1;
		choose_generate2 = choose_generate1;
	}
	if (color_status >= 2 && color_status <= 4)
	{
		color_status = 0;
		choose_generate1 = new choose_array;
		choose_generate1->left_or_right = 1;
		choose_generate1->choose = color_status - 1;
		choose_generate1->operation = operation;
		choose_generate1->point1.x = GetRValue(color);
		choose_generate1->point1.y = GetGValue(color);
		choose_generate1->point1_z = GetBValue(color);
		if (color_status == 3)
		{
			choose_generate1->point2.x = GetRValue(color1);
			choose_generate1->point2.y = GetGValue(color1);
			choose_generate1->point2_z = GetBValue(color1);
		}
		if (color_status == 4)
		{
			choose_generate1->radius = sqrt(double( (GetRValue(color) - GetRValue(color1)) * (GetRValue(color) - GetRValue(color1)) + (GetGValue(color) - GetGValue(color1)) * (GetGValue(color) - GetGValue(color1)) + (GetBValue(color) - GetBValue(color1)) * (GetBValue(color) - GetBValue(color1))));
		}
		choose_generate1->next = NULL;
		choose_generate2->next = choose_generate1;
		choose_generate2 = choose_generate1;
	}
		
	int x,y;
	CPoint temp;
	for (x = 0;x <= int (m_bmp.bmWidth * percentage * zoom);x++)
	{
		for (y = 0;y <= int (m_bmp.bmHeight * percentage * zoom);y++)
		{
			temp.x = x + m_startX;
			temp.y = y + m_startY;
			if (ChangeOrNot(temp))
			{
				pDC->SetPixel(temp,ColorChangeTo(temp));
			}
		}
	}
	if (show_status == 1)
	{	
		for (x = 0;x <= int (m_bmp.bmWidth * percentage * zoom);x++)
		{
			for (y = 0;y <= int (m_bmp.bmHeight * percentage * zoom);y++)
			{
				temp.x = x + m_startX;
				temp.y = y + m_startY;	
				if (!IsInChoose(temp))
				{
					pDC->SetPixel(temp,RGB(255,255,255));
				}
			}
		}
	}

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
	s1.Format(_T("请选择点"));
	s2.Format(_T("请选择矩形的第一个点"));
	s3.Format(_T("请选择矩形的第二个点"));
	s4.Format(_T("请选择圆心"));
	s5.Format(_T("请选择圆周上一点"));
	S1.Format(_T("目前所作运算:交"));
	S2.Format(_T("目前所作运算:并"));
	S3.Format(_T("目前所作运算:差"));
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
	if ((zoom <= 20 && zoom >= 0.1) || (zoom > 20 && zDelta < 0) || ( zoom < 0.1 && zDelta > 0))
		zoom *= (1.0 + double(zDelta) / 2400);
	m_startX = p.x - double(p.x - m_startX) * (1.0 + double(zDelta) / 2400.0);
	m_startY = p.y - double(p.y - m_startY) * (1.0 + double(zDelta) / 2400.0);
	for (choose_temp1 = choose_head;choose_temp1 != NULL;choose_temp1 = choose_temp1->next)
	{
		if (choose_temp1->choose == 1)
		{
			choose_temp1->point1.x = p.x - double(p.x - choose_temp1->point1.x) * (1.0 + double(zDelta) / 2400.0);
			choose_temp1->point1.y = p.y - double(p.y - choose_temp1->point1.y) * (1.0 + double(zDelta) / 2400.0);
			continue;
		}
		if (choose_temp1->choose == 2)
		{
			choose_temp1->point1.x = p.x - double(p.x - choose_temp1->point1.x) * (1.0 + double(zDelta) / 2400.0);
			choose_temp1->point1.y = p.y - double(p.y - choose_temp1->point1.y) * (1.0 + double(zDelta) / 2400.0);
			choose_temp1->point2.x = p.x - double(p.x - choose_temp1->point2.x) * (1.0 + double(zDelta) / 2400.0);
			choose_temp1->point2.y = p.y - double(p.y - choose_temp1->point2.y) * (1.0 + double(zDelta) / 2400.0);
			continue;
		}
		if (choose_temp1->choose == 3)
		{
			choose_temp1->point1.x = p.x - double(p.x - choose_temp1->point1.x) * (1.0 + double(zDelta) / 2400.0);
			choose_temp1->point1.y = p.y - double(p.y - choose_temp1->point1.y) * (1.0 + double(zDelta) / 2400.0);
			choose_temp1->radius = choose_temp1->radius * (1.0 + double(zDelta) / 2400.0);
			continue;
		}
	}
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
		for (choose_temp1 = choose_head;choose_temp1 != NULL;choose_temp1 = choose_temp1->next)
		{
			if (choose_temp1->choose == 1 || choose_temp1->choose == 3)
			{
				choose_temp1->point1.x += (lkeyup.x - lkeydown.x);
				choose_temp1->point1.y += (lkeyup.y - lkeydown.y);
				continue;
			}
			if (choose_temp1->choose == 2)
			{
				choose_temp1->point1.x += (lkeyup.x - lkeydown.x);
				choose_temp1->point1.y += (lkeyup.y - lkeydown.y);
				choose_temp1->point2.x += (lkeyup.x - lkeydown.x);
				choose_temp1->point2.y += (lkeyup.y - lkeydown.y);
				continue;
			}
		}
	}
	else
	{
		if(choose_status == 1)
		{		
			if (choose_head == NULL)
			{
				choose_head = new choose_array;
				choose_head->change_color = 0;
				choose_head->choose = 1;
				choose_head->left_or_right = 0;
				choose_head->operation = operation;
				choose_head->point1 = lkeydown;
				choose_head->next = NULL;
				choose_generate2 = choose_head;
			}
			else
			{
				choose_generate1 = new choose_array;
				choose_generate1->change_color = 0;
				choose_generate1->choose = 1;
				choose_generate1->left_or_right = 0;
				choose_generate1->operation = operation;
				choose_generate1->point1 = lkeydown;
				choose_generate1->next = NULL;
				choose_generate2->next = choose_generate1;
				choose_generate2 = choose_generate1;
			}
		}
		if (choose_status == 2)
		{
			if (choose_rect == 1)
			{
				if (choose_head == NULL)
				{
					choose_head = new choose_array;
					choose_head->change_color = 0;
					choose_head->choose = 2;
					choose_head->left_or_right = 0;
					choose_head->operation = operation;
					choose_head->point1 = lkeydown;
					choose_head->next = NULL;
					choose_generate2 = choose_head;
				}
				else
				{
					choose_generate1 = new choose_array;
					choose_generate1->change_color = 0;
					choose_generate1->choose = 2;
					choose_generate1->left_or_right = 0;
					choose_generate1->operation = operation;
					choose_generate1->point1 = lkeydown;
					choose_generate1->next = NULL;
					choose_generate2->next = choose_generate1;
					choose_generate2 = choose_generate1;
				}
				choose_rect = 2;
			}
			else
			{
				if (choose_head->next == NULL)
				{
					choose_head->point2 = lkeydown;
				}
				else
				{
					choose_generate2->point2 = lkeydown;
				}
				choose_rect = 1;
			}
		}
		if (choose_status == 3)
		{
			if (choose_circle == 1)
			{
				if (choose_head == NULL)
				{
					choose_head = new choose_array;
					choose_head->change_color = 0;
					choose_head->choose = 3;
					choose_head->left_or_right = 0;
					choose_head->operation = operation;
					choose_head->point1 = lkeydown;
					choose_head->next = NULL;
					choose_generate2 = choose_head;
				}
				else
				{
					choose_generate1 = new choose_array;
					choose_generate1->change_color = 0;
					choose_generate1->choose = 3;
					choose_generate1->left_or_right = 0;
					choose_generate1->operation = operation;
					choose_generate1->point1 = lkeydown;
					choose_generate1->next = NULL;
					choose_generate2->next = choose_generate1;
					choose_generate2 = choose_generate1;
				}
				choose_circle = 2;
			}
			else
			{
				if (choose_head->next == NULL)
				{
					choose_head->radius = distance(lkeydown,choose_head->point1);
				}
				else
				{
					choose_generate2->radius = distance(lkeydown,choose_generate2->point1);
				}
				choose_circle = 1;
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
	Invalidate();
}


void CLeftView::OnChooseRect()
{
	// TODO: 在此添加命令处理程序代码
	choose_status = 2;
	Invalidate();
}


void CLeftView::OnChooseCircle()
{
	// TODO: 在此添加命令处理程序代码
	choose_status = 3;
	Invalidate();
}


void CLeftView::OnUpdateChoosePoint(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(choose_status == 1);
	pCmdUI->Enable(!((choose_circle == 2) || (choose_rect == 2)));
}


void CLeftView::OnUpdateChooseRect(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(choose_status == 2);
	pCmdUI->Enable (!((choose_circle == 2) || (choose_rect == 2)));
}


void CLeftView::OnUpdateChooseCircle(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(choose_status == 3);
	pCmdUI->Enable(!((choose_circle == 2) || (choose_rect == 2)));
}


void CLeftView::OnAnd()
{
	// TODO: 在此添加命令处理程序代码
	operation = 1;
	Invalidate();
}


void CLeftView::OnOr()
{
	// TODO: 在此添加命令处理程序代码
	operation = 2;
	Invalidate();
}


void CLeftView::OnMinus()
{
	// TODO: 在此添加命令处理程序代码
	operation  = 3;
	Invalidate();
}


void CLeftView::OnUpdateAnd(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(operation == 1);
	pCmdUI->Enable(!((choose_circle == 2) || (choose_rect == 2)));
}


void CLeftView::OnUpdateOr(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(operation == 2);
	pCmdUI->Enable(!((choose_circle == 2) || (choose_rect == 2)));
}


void CLeftView::OnUpdateMinus(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(operation == 3);
	pCmdUI->Enable(!((choose_circle == 2) || (choose_rect == 2)));
}


void CLeftView::OnSetColor()
{
	// TODO: 在此添加命令处理程序代码
	ProjectDialog *td=new ProjectDialog;
	td->Create(IDD_SET_COLOR,this);
	td->ShowWindow(SW_SHOW);
}


void CLeftView::OnViewShow()
{
	// TODO: 在此添加命令处理程序代码
	show_status = show_status == 1? 0 : 1;
	Invalidate();
}


void CLeftView::OnUpdateViewShow(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(show_status == 1);
}


bool CLeftView::IsInChoose(CPoint p)
{	
	bool inStatus = 0;
	if (choose_head == NULL)
		return false;
	if (choose_head->choose == 1)
	{
		if (p.x == choose_head->point1.x && p.y == choose_head->point1.y)
		{
			inStatus = 1;
		}
		else
		{
			inStatus = 0;
		}
	}
	if (choose_head->choose == 2)
	{
		if (PointInRect(p,choose_head->point1,choose_head->point2))
		{
			inStatus = 1;		
		}
		else
		{
			inStatus = 0;		
		}

	}
	if (choose_head->choose == 3)
	{
		if ((p.x - choose_head->point1.x) * (p.x - choose_head->point1.x) + (p.y - choose_head->point1.y) * (p.y - choose_head->point1.y) <= choose_head->radius * choose_head->radius)
		{
			inStatus = 1;
		}
		else
		{	
			inStatus = 0;
		}
	}



	//////////
	for (choose_temp1 = choose_head->next;choose_temp1 != NULL;choose_temp1 = choose_temp1->next)
	{
		if(choose_temp1->left_or_right == 0)
		{
			if (choose_temp1->change_color == 1)
			{
				continue;
			}
			if (choose_temp1->choose == 1)
			{
				if (p.x == choose_temp1->point1.x && p.y == choose_temp1->point1.y)
				{
					if (choose_temp1->operation == 2)
					{
						inStatus = 1;
					}
					if (choose_temp1->operation == 3)
					{						
						inStatus = 0;	
					}
				}
				else
				{
					if (choose_temp1->operation == 1)
					{
						inStatus = 0;					
					}
				}
				continue;
			}
			if (choose_temp1->choose == 2)
			{
				if (PointInRect(p,choose_temp1->point1,choose_temp1->point2))
				{
					if (choose_temp1->operation == 2)
					{
						inStatus = 1;
						continue;
					}
					if (choose_temp1->operation == 3)
					{						
						inStatus = 0;	
						continue;
					}
				}
				else
				{
					if (choose_temp1->operation == 1)
					{
						inStatus = 0;
						continue;
					}
				}
			
			}
			if (choose_temp1->choose == 3)
			{
				if ((p.x - choose_temp1->point1.x) * (p.x - choose_temp1->point1.x) + (p.y - choose_temp1->point1.y) * (p.y - choose_temp1->point1.y) <= choose_temp1->radius * choose_temp1->radius)
				{
					if (choose_temp1->operation == 2)
					{
						inStatus = 1;
					}
					if (choose_temp1->operation == 3)
					{						
						inStatus = 0;	
					}
				}
				else
				{
					if (choose_temp1->operation == 1)
					{
						inStatus = 0;					
					}
				}
				continue;
			}
		}


		//////////////////////
		else
		{
			CRect Rect;
			COLORREF temp_color;
			GetWindowRect(Rect);
			HDC hDC = ::GetDC(NULL);
			temp_color = ::GetPixel(hDC,p.x + Rect.left,p.y + Rect.top);
			DeleteDC(hDC);
			if (choose_temp1->choose == 1)
			{
				if (choose_temp1->point1.x == GetRValue(temp_color) && choose_temp1->point1.y == GetGValue(temp_color) && choose_temp1->point1_z == GetBValue(temp_color))
				{
					if (choose_temp1->operation == 2)
					{
						inStatus = 1;
					}
					if (choose_temp1->operation == 3)
					{						
						inStatus = 0;	
					}
				}
				else
				{
					if (choose_temp1->operation == 1)
					{
						inStatus = 0;					
					}
				}
				continue;

			}
			if (choose_temp1->choose == 2)
			{
				if (((choose_temp1->point1.x <= GetRValue(temp_color)) && 
					(choose_temp1->point2.x >= GetRValue(temp_color)) && 
					(choose_temp1->point1.y <= GetGValue(temp_color)) && 
					(choose_temp1->point2.y >= GetGValue(temp_color)) && 
					(choose_temp1->point1_z <= GetBValue(temp_color))&& 
					(choose_temp1->point2_z >= GetBValue(temp_color)))
					|| 
					((choose_temp1->point2.x <= GetRValue(temp_color)) && 
					(choose_temp1->point1.x >= GetRValue(temp_color)) && 
					(choose_temp1->point2.y <= GetGValue(temp_color)) && 
					(choose_temp1->point1.y >= GetGValue(temp_color)) && 
					(choose_temp1->point2_z <= GetBValue(temp_color))&& 
					(choose_temp1->point1_z >= GetBValue(temp_color))))
				{
					if (choose_temp1->operation == 2)
					{
						inStatus = 1;
						continue;
					}
					if (choose_temp1->operation == 3)
					{						
						inStatus = 0;	
						continue;
					}
				}
				else
				{
					if (choose_temp1->operation == 1)
					{
						inStatus = 0;
						continue;
					}
				}

			}
			if (choose_temp1->choose == 3)
			{
				if ((GetRValue(temp_color) - choose_temp1->point1.x) * (GetRValue(temp_color) - choose_temp1->point1.x) 
					+ (GetGValue(temp_color) - choose_temp1->point1.y) * (GetGValue(temp_color) - choose_temp1->point1.y)
					+ (GetBValue(temp_color) - choose_temp1->point1_z) * (GetBValue(temp_color) - choose_temp1->point1_z)
					<= choose_temp1->radius * choose_temp1->radius)
				{
					if (choose_temp1->operation == 2)
					{
						inStatus = 1;
					}
					if (choose_temp1->operation == 3)
					{						
						inStatus = 0;	
					}
				}
				else
				{
					if (choose_temp1->operation == 1)
					{
						inStatus = 0;					
					}
				}
				continue;
			}
		}
	}
	return inStatus;
}


bool CLeftView::PointInRect(CPoint p,CPoint point1,CPoint point2)
{
	bool res = 0;
	if ((p.x >= point1.x && p.x <= point2.x && point1.x <= point2.x) || (p.x >= point2.x && p.x <= point1.x && point2.x <= point1.x))
	{
		if ((p.y >= point1.y && p.y <= point2.y && point1.y <= point2.y) || (p.y >= point2.y && p.y <= point1.y && point2.y <= point1.y))
		{
			res = 1;
		}
	}
	return res;
}//p:判断的点
//point1,point2矩形顶点

void CLeftView::OnEditClear()
{
	// TODO: 在此添加命令处理程序代码
	if (choose_head == NULL)
	{
		MessageBox(_T("选择集为空,无需清空"),_T("提示消息"),MB_ICONASTERISK);
	}
	else
	{
		for (choose_temp1 = choose_head;choose_temp1 != NULL;)
		{
			choose_temp2 = choose_temp1;
			choose_temp1 = choose_temp1->next;
			free(choose_temp2);
		}
		choose_head = NULL;
		MessageBox(_T("已清空选择集"),_T("提示消息"),MB_ICONASTERISK);
		Invalidate();
	}
}


bool CLeftView::ChangeOrNot(CPoint p)
{
	int inStatus = 0;
	if (choose_head == NULL)
		return false;
	if (choose_head->choose == 1)
	{
		if (p.x == choose_head->point1.x && p.y == choose_head->point1.y)
		{
			inStatus = 1;
		}
		else
		{
			inStatus = 0;
		}
	}
	if (choose_head->choose == 2)
	{
		if (PointInRect(p,choose_head->point1,choose_head->point2))
		{
			inStatus = 1;		
		}
		else
		{
			inStatus = 0;		
		}

	}
	if (choose_head->choose == 3)
	{
		if ((p.x - choose_head->point1.x) * (p.x - choose_head->point1.x) + (p.y - choose_head->point1.y) * (p.y - choose_head->point1.y) <= choose_head->radius * choose_head->radius)
		{
			inStatus = 1;
		}
		else
		{	
			inStatus = 0;
		}
	}
	for (choose_temp1 = choose_head->next;choose_temp1 != NULL;choose_temp1 = choose_temp1->next)
	{
		if (choose_temp1->change_color == 1)
		{
			inStatus = inStatus == 0 ? 0: 2;
			if (inStatus == 2)
				return true;
			else
				continue;
		}
		if (choose_temp1->choose == 1)
		{
			if (p.x == choose_temp1->point1.x && p.y == choose_temp1->point1.y)
			{
				if (choose_temp1->operation == 2)
				{
					inStatus = 1;
				}
				if (choose_temp1->operation == 3)
				{						
					inStatus = 0;	
				}
			}
			else
			{
				if (choose_temp1->operation == 1)
				{
					inStatus = 0;					
				}
			}
			continue;
		}
		if (choose_temp1->choose == 2)
		{
			if (PointInRect(p,choose_temp1->point1,choose_temp1->point2))
			{
				if (choose_temp1->operation == 2)
				{
					inStatus = 1;
				}
				if (choose_temp1->operation == 3)
				{						
					inStatus = 0;	
				}
			}
			else
			{
				if (choose_temp1->operation == 1)
				{
					inStatus = 0;					
				}

			}
			continue;
		}
		if (choose_temp1->choose == 3)
		{
			if ((p.x - choose_temp1->point1.x) * (p.x - choose_temp1->point1.x) + (p.y - choose_temp1->point1.y) * (p.y - choose_temp1->point1.y) <= choose_temp1->radius * choose_temp1->radius)
			{
				if (choose_temp1->operation == 2)
				{
					inStatus = 1;
				}
				if (choose_temp1->operation == 3)
				{						
					inStatus = 0;	
				}
			}
			else
			{
				if (choose_temp1->operation == 1)
				{
					inStatus = 0;					
				}
			}
			continue;
		}
	}
	return inStatus == 2 ? 1 : 0;
}


COLORREF CLeftView::ColorChangeTo(CPoint p)
{
	COLORREF res;
	int inStatus = 0;
	if (choose_head->choose == 1)
	{
		if (p.x == choose_head->point1.x && p.y == choose_head->point1.y)
		{
			inStatus = 1;
		}
		else
		{
			inStatus = 0;
		}
	}
	if (choose_head->choose == 2)
	{
		if (PointInRect(p,choose_head->point1,choose_head->point2))
		{
			inStatus = 1;		
		}
		else
		{
			inStatus = 0;		
		}

	}
	if (choose_head->choose == 3)
	{
		if ((p.x - choose_head->point1.x) * (p.x - choose_head->point1.x) + (p.y - choose_head->point1.y) * (p.y - choose_head->point1.y) <= choose_head->radius * choose_head->radius)
		{
			inStatus = 1;
		}
		else
		{	
			inStatus = 0;
		}
	}
	for (choose_temp1 = choose_head->next;choose_temp1 != NULL;choose_temp1 = choose_temp1->next)
	{
		if (choose_temp1->change_color == 1)
		{
			if (inStatus == 1)
				res = choose_temp1->color_to_set;
			continue;
		}
		if (choose_temp1->choose == 1)
		{
			if (p.x == choose_temp1->point1.x && p.y == choose_temp1->point1.y)
			{
				if (choose_temp1->operation == 2)
				{
					inStatus = 1;
					continue;
				}
				if (choose_temp1->operation == 3)
				{						
					inStatus = 0;	
					continue;
				}
			}
			else
			{
				if (choose_temp1->operation == 1)
				{
					inStatus = 0;
					continue;
				}
			}
			
		}
		if (choose_temp1->choose == 2)
		{
			if (PointInRect(p,choose_temp1->point1,choose_temp1->point2))
			{
				if (choose_temp1->operation == 2)
				{
					inStatus = 1;
					continue;
				}
				if (choose_temp1->operation == 3)
				{						
					inStatus = 0;
					continue;
				}
			}
			else
			{
				if (choose_temp1->operation == 1)
				{
					inStatus = 0;	
					continue;
				}

			}
			
		}
		if (choose_temp1->choose == 3)
		{
			if ((p.x - choose_temp1->point1.x) * (p.x - choose_temp1->point1.x) + (p.y - choose_temp1->point1.y) * (p.y - choose_temp1->point1.y) <= choose_temp1->radius * choose_temp1->radius)
			{
				if (choose_temp1->operation == 2)
				{
					inStatus = 1;
					continue;
				}
				if (choose_temp1->operation == 3)
				{						
					inStatus = 0;
					continue;
				}
			}
			else
			{
				if (choose_temp1->operation == 1)
				{
					inStatus = 0;	
					continue;
				}
			}
		}
	}
	return res;
}


void CLeftView::OnSelectColor()
{
	// TODO: 在此添加命令处理程序代码
	SelectDiolog *td=new SelectDiolog;	
	td->Create(IDD_SELECT_COLOR,this);
	td->ShowWindow(SW_SHOW);
}
