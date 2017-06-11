// RightView.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCproject.h"
#include "RightView.h"
#include <cmath>
#include "ProjectDialog.h"
#include "SelectDiolog.h"

//#pragma comment(linker,"/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
// CRightView

IMPLEMENT_DYNCREATE(CRightView, CView)

CRightView::CRightView()
{
	point_pos.x = 0;
	point_pos.y = 0;
	scale_right = -13;
	rotate_x = 1.0;
	rotate_y = 1.0;
	rotate_z = 1.0;
	du = 90;
	r = 1.5f,h = 0.0f;
	c = PI / 180.0f;
}

CRightView::~CRightView()
{
}

BEGIN_MESSAGE_MAP(CRightView, CView)
	ON_COMMAND(ID_EDIT_REFRESH, &CRightView::OnEditRefresh)
	//ON_WM_LBUTTONUP()
	//ON_COMMAND(ID_SELECT_COLOR, &CRightView::OnSelectColor)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEHWHEEL()
	ON_WM_MOUSEWHEEL()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_AND, &CRightView::OnAnd)
	ON_COMMAND(ID_OR, &CRightView::OnOr)
	ON_COMMAND(ID_MINUS, &CRightView::OnMinus)
	ON_UPDATE_COMMAND_UI(ID_AND, &CRightView::OnUpdateAnd)
	ON_UPDATE_COMMAND_UI(ID_OR, &CRightView::OnUpdateOr)
	ON_UPDATE_COMMAND_UI(ID_MINUS, &CRightView::OnUpdateMinus)
	ON_COMMAND(ID_CHOOSE_POINT, &CRightView::OnChoosePoint)
	ON_COMMAND(ID_CHOOSE_RECT, &CRightView::OnChooseRect)
	ON_COMMAND(ID_CHOOSE_CIRCLE, &CRightView::OnChooseCircle)
	ON_UPDATE_COMMAND_UI(ID_CHOOSE_CIRCLE, &CRightView::OnUpdateChooseCircle)
	ON_UPDATE_COMMAND_UI(ID_CHOOSE_POINT, &CRightView::OnUpdateChoosePoint)
	ON_UPDATE_COMMAND_UI(ID_CHOOSE_RECT, &CRightView::OnUpdateChooseRect)
	ON_COMMAND(ID_SET_COLOR, &CRightView::OnSetColor)
	ON_COMMAND(ID_SELECT_COLOR, &CRightView::OnSelectColor)
	ON_UPDATE_COMMAND_UI(ID_SET_COLOR, &CRightView::OnUpdateSetColor)
	ON_UPDATE_COMMAND_UI(ID_SELECT_COLOR, &CRightView::OnUpdateSelectColor)
END_MESSAGE_MAP()


// CRightView 绘图

void CRightView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	//
	::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	RenderScene();//绘图都放在这
	::glFinish();
	::SwapBuffers( m_pDC->GetSafeHdc() );
	//
	//ShowTheColor(pDC);

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

void GLGrid(float pt1x, float pt1y, float pt1z, float pt2x, float pt2y, float pt2z, int num)
{

    const float _xLen = (pt2x - pt1x) / num;
    const float _yLen = (pt2y - pt1y) / num;
    const float _zLen = (pt2z - pt1z) / num;
    glLineWidth(2.f);
    glLineStipple(1, 0x0303);//线条样式

    glBegin(GL_LINES);
    glEnable(GL_LINE_SMOOTH);

    int xi = 0;
    int yi = 0;
    int zi = 0;

    //绘制平行于X的直线
    for (zi = 0; zi <= num; zi++)
    {
        float z = _zLen * zi + pt1z;
        for (yi = 0; yi <= num; yi++)
        {
            float y = _yLen * yi + pt1y;
            glVertex3f(pt1x, y, z);
            glVertex3f(pt2x, y, z);
        }
    }
    //绘制平行于Y的直线
    for (zi = 0; zi <= num; zi++)
    {
        float z = _zLen * zi + pt1z;
        for (xi = 0; xi <= num; xi++)
        {
            float x = _xLen * xi + pt1x;
            glVertex3f(x, pt1y, z);
            glVertex3f(x, pt2y, z);
        }
    }
    //绘制平行于Z的直线
    for (yi = 0; yi <= num; yi++)
    {
        float y = _yLen * yi + pt1y;
        for (xi = 0; xi <= num; xi++)
        {
            float x = _xLen * xi + pt1x;  
            glVertex3f(x, y, pt1z);
            glVertex3f(x, y, pt2z);
        }
    }
    glEnd();
}


int CRightView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
		// TODO:  在此添加您专用的创建代码
	InitializeOpenGL();
	return 0;	
}

BOOL CRightView::InitializeOpenGL()
{
	m_pDC = new CClientDC(this);
	if (m_pDC == NULL)
	{
		return FALSE;
	}
	if (!SetupPixelFormat())
	{
		return FALSE;
	}
	m_hRC = ::wglCreateContext(m_pDC->GetSafeHdc());
	if (m_hRC == 0)
	{
		return FALSE;
	}
	if (::wglMakeCurrent (m_pDC->GetSafeHdc(),m_hRC) == FALSE)
	{
		return FALSE;
	}
	::glClearColor(0.0f,0.0f,0.0f,0.0f);
	::glClearDepth(1.0f);
	::glEnable(GL_DEPTH_TEST);
	return TRUE;
}

BOOL CRightView::SetupPixelFormat()
{

	static PIXELFORMATDESCRIPTOR pfd =

	{
		sizeof(PIXELFORMATDESCRIPTOR), // size of this pfd	
		1,                              // version number
		PFD_DRAW_TO_WINDOW |            // support window
		PFD_SUPPORT_OPENGL |            // support OpenGL
		PFD_DOUBLEBUFFER,                // double buffered
		PFD_TYPE_RGBA,                  // RGBA type
		24,                             // 24-bit color depth
		0, 0, 0, 0, 0, 0,               // color bits ignored
		0,                              // no alpha buffer
		0,                              // shift bit ignored
		0,                              // no accumulation buffer
		0, 0, 0, 0,                     // accum bits ignored
		16,                             // 16-bit z-buffer
		0,                              // no stencil buffer
		0,                              // no auxiliary buffer
		PFD_MAIN_PLANE,                 // main layer
		0,                              // reserved
		0, 0, 0                         // layer masks ignored
	};
	int m_nPixelFormat = ::ChoosePixelFormat(m_pDC->GetSafeHdc(), &pfd);
	if ( m_nPixelFormat == 0 )
	{
	    return FALSE;
	}
	if ( ::SetPixelFormat(m_pDC->GetSafeHdc(), m_nPixelFormat, &pfd) == FALSE)
	{
	     return FALSE;
	}
	 return TRUE;
}

void CRightView::OnDestroy()
{
	CView::OnDestroy();
	if(::wglMakeCurrent (0,0) == FALSE)
    {
        MessageBox(_T("Could not make RC non-current"));
    }
	if(::wglDeleteContext (m_hRC)==FALSE)
	{
        MessageBox(_T("Could not delete RC"));
    }
	if(m_pDC)
    {
        delete m_pDC;
    } 
	m_pDC = NULL;
	// TODO: 在此处添加消息处理程序代码
}


void CRightView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	GLdouble aspect_ratio; // width/height ratio
	if ( 0 >= cx || 0 >= cy )
	{
		return;
	}
 // select the full client area 
	::glViewport(0, 0, cx, cy);
 // compute the aspect ratio
 // this will keep all dimension scales equal 
	aspect_ratio = (GLdouble)cx/(GLdouble)cy;
 // select the projection matrix and clear it
	::glMatrixMode(GL_PROJECTION);
	::glLoadIdentity();
 // select the viewing volume
	::gluPerspective(45.0f, aspect_ratio, .01f, 200.0f);//画三维
 //::gluOrtho2D(-10.0f, 10.0f, -10.0f, 10.0f);    //二维
 // switch back to the modelview matrix and clear it
	::glMatrixMode(GL_MODELVIEW);
	::glLoadIdentity();
	// TODO: 在此处添加消息处理程序代码
}


BOOL CRightView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	return TRUE;
}


BOOL CRightView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此添加专用代码和/或调用基类
	cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
	return CView::PreCreateWindow(cs);
}

void CRightView::RenderScene()

{
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, scale_right);		//滚轮缩放
	gluLookAt(r*cos(c*du), h, r*sin(c*du), 0, 0, 0, 0, 1, 0);
	glRotatef(this->rotate_x, 1.0, 0.0, 0.0);
	glRotatef(this->rotate_y, 0.0, 1.0, 0.0);
	glRotatef(this->rotate_z, 0.0, 0.0, 1.0);
	ordination();
	glPopMatrix();


}

void CRightView::ordination() {

   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glEnable(GL_POINT_SMOOTH);                   //设置反走样
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);       //设置反走样
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_POLYGON_SMOOTH);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    glRotatef(-45, 0.0, 1.0, 0.0);
    //网格
   /* glPushMatrix();

    glColor3f(1.0f, 1.0f, 0.0f);
    glTranslatef(-4, -4, -4);
    GLGrid(0,0,0,8,0,8,20);
    glPopMatrix();//xy


    glPushMatrix();
    glTranslated(-4,4, -4);
    glRotatef(90, 1.0, 0.0, 0.0);
    glColor3f(0.0f, 0.9f, 0.9f);
    GLGrid(0, 0, 0, 8, 0, 8, 20);
    glPopMatrix();//yz


    glPushMatrix();
    glTranslatef(-4, -4, -4);
    glRotatef(90, 0.0, 0.0, 1.0);
    glColor3f(0.9f, 0.0f, 0.9f);
    GLGrid(0, 0, 0, 8, 0, 8 ,20);
    glPopMatrix();//xz*/

    //x
    //glTranslatef(-2, -2, -2);
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(5, 0.0f, 0.0f);
    glEnd();
    glPushMatrix();
    glTranslatef(5, 0.0f, 0.0f);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    glutWireCone(0.09, 0.3, 10, 10);
    glPopMatrix();
	for (int i = 1;i <=9;i++)
	{
		glBegin(GL_LINES);
		glVertex3f(0.5 * i, 0.0f, 0.0f);
		glVertex3f(0.5 * i, 0.1f, 0.0f);
		glEnd();
	}


    //y
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0, 5, 0.0f);
    glEnd();
    glPushMatrix();
    glTranslatef(0.0, 5, 0.0f);
    glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
    glutWireCone(0.09, 0.3, 10, 10);
    glPopMatrix();
	for (int i = 1;i <= 9;i++)
	{
		glBegin(GL_LINES);
		glVertex3f( 0.0f,0.5 * i, 0.0f);
		glVertex3f(0.0f, 0.5 * i, 0.1f);
		glEnd();
	}


    //z
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0, 0.0f, 5);
    glEnd();
    glPushMatrix();
    glTranslatef(0.0, 0.0f, 5);
    glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
    glutWireCone(0.09, 0.3, 10, 10);
    glPopMatrix();
	for (int i = 1;i <= 9;i++)
	{
		glBegin(GL_LINES);
		glVertex3f( 0.0f, 0.0f, 0.5 * i);
		glVertex3f( 0.1f, 0.0f,0.5 * i);
		glEnd();
	}
	
	glDisable(GL_BLEND);
    glDisable(GL_LINE_SMOOTH);
    glDisable(GL_POINT_SMOOTH);
    glDisable(GL_POLYGON_SMOOTH);
	
	set<COLORREF>::iterator it;
	glColor3f(1.0f,1.0f,0.0f);
	glPointSize(1.2f);
	glBegin(GL_POINTS);
	for (it = color_to_show.begin();it != color_to_show.end();it++)
	{
		float r = ((float)GetRValue(*it)) / 64.0;
		float g = ((float)GetGValue(*it)) / 64.0;
		float b = ((float)GetBValue(*it)) / 64.0;
		glVertex3f(r,g,b);
	}
	glEnd();

}



BOOL CRightView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	double a = zDelta / 120;
	if ((scale_right + a * 0.1) < 10)
		scale_right += a * 0.1;
	this->InvalidateRect(NULL, FALSE);
	return CView::OnMouseWheel(nFlags, zDelta, pt);
}


void CRightView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	 if (nFlags & MK_LBUTTON == TRUE) {

        //MessageBox("mouse move function triggered!", "attentino", MB_OK);
        du += point.x - oldmx;              //鼠标在窗口x轴方向上的增量加到视点绕y轴的角度上，这样就左右转了
        h += 0.03f*(point.y - oldmy);       //鼠标在窗口y轴方向上的改变加到视点的y坐标上，就上下转了
        if (h>15.0f) h = 15.0f;             //视点y坐标作一些限制，不会使视点太奇怪
        else if (h<-5.0f) h = -5.0f;
        oldmx = point.x, oldmy = point.y;   //把此时的鼠标坐标作为旧值，为下一次计算增量做准备
                                            /*CString debug;
                                            debug.Format(_T("h,du= %0.3f %3d\n"), h, du);
                                            OutputDebugString(debug);*/
                                            //OnPaint();
        this->OnDraw(this->GetDC());    //重绘界面
    }
    else if (nFlags & MK_RBUTTON == TRUE)
    {
        oldmx += point.x - oldmx;
        oldmy += point.y - oldmy;
        glTranslatef(oldmx, oldmy, -0.1f);
        this->OnDraw(this->GetDC());
        oldmx = point.x, oldmy = point.y;
    }
    else {
        oldmx = point.x, oldmy = point.y;
        //OutputDebugString(_T("mouse up\n"));
    }
	//CView::OnMouseMove(nFlags, point);
}


BOOL CRightView::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN)  // If a keydown message
	{

		if (pMsg->wParam == _T('W'))
		{

			this->rotate_x += 6.0;
			if (this->rotate_x > 360)this->rotate_x = -360;
			this->InvalidateRect(NULL, FALSE);
		}
		if (pMsg->wParam == _T('X'))
		{

			this->rotate_x -= 6.0;
			if (this->rotate_x < -360)this->rotate_x = 360;
			this->InvalidateRect(NULL, FALSE);
		}
		if (pMsg->wParam == _T('A'))
		{

			this->rotate_y += 6.0;
			if (this->rotate_y < -360)this->rotate_y = 360;
			this->InvalidateRect(NULL, FALSE);
		}
		if (pMsg->wParam == _T('D'))
		{

			this->rotate_y -= 6.0;
			if (this->rotate_y > 360)this->rotate_y = -360;
			this->InvalidateRect(NULL, FALSE);
		}
		if (pMsg->wParam == _T('Z'))
		{

			this->rotate_z -= 6.0;
			if (this->rotate_z < -360)this->rotate_z = 360;
			this->InvalidateRect(NULL, FALSE);
		}
		if (pMsg->wParam == _T('C'))
		{

			this->rotate_z += 6.0;
			if (this->rotate_z > 360)this->rotate_z = -360;
			this->InvalidateRect(NULL, FALSE);
		}
		if (pMsg->wParam == _T('Q'))
		{
			if ((scale_right + 2)  <  10)
				scale_right += 2;

			this->InvalidateRect(NULL, FALSE);
		}
		if (pMsg->wParam == _T('E'))
		{
				scale_right -= 2;

			this->InvalidateRect(NULL, FALSE);
		}
	}
	return CView::PreTranslateMessage(pMsg);
}


void CRightView::OnAnd()
{
	// TODO: 在此添加命令处理程序代码
	operation = 1;
	Invalidate();
}


void CRightView::OnOr()
{
	// TODO: 在此添加命令处理程序代码
	operation = 2;
	Invalidate();
}


void CRightView::OnMinus()
{
	// TODO: 在此添加命令处理程序代码
	operation  = 3;
	Invalidate();
}


void CRightView::OnUpdateAnd(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(operation == 1);
	pCmdUI->Enable(!((choose_circle == 2) || (choose_rect == 2)));
}


void CRightView::OnUpdateOr(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(operation == 2);
	pCmdUI->Enable(!((choose_circle == 2) || (choose_rect == 2)));
}


void CRightView::OnUpdateMinus(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(operation == 3);
	pCmdUI->Enable(!((choose_circle == 2) || (choose_rect == 2)));
}


void CRightView::OnChoosePoint()
{
	// TODO: 在此添加命令处理程序代码
	choose_status = 1;
	Invalidate();
}


void CRightView::OnChooseRect()
{
	// TODO: 在此添加命令处理程序代码
	choose_status = 2;
	Invalidate();
}


void CRightView::OnChooseCircle()
{
	// TODO: 在此添加命令处理程序代码
	choose_status = 3;
	Invalidate();
}


void CRightView::OnUpdateChooseCircle(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(choose_status == 3);
	pCmdUI->Enable(!((choose_circle == 2) || (choose_rect == 2)));
}


void CRightView::OnUpdateChoosePoint(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(choose_status == 1);
	pCmdUI->Enable(!((choose_circle == 2) || (choose_rect == 2)));
}


void CRightView::OnUpdateChooseRect(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(choose_status == 2);
	pCmdUI->Enable (!((choose_circle == 2) || (choose_rect == 2)));
}


void CRightView::OnSetColor()
{
	// TODO: 在此添加命令处理程序代码
	ProjectDialog *td=new ProjectDialog;
	td->Create(IDD_SET_COLOR,this);
	td->ShowWindow(SW_SHOW);
}


void CRightView::OnSelectColor()
{
	// TODO: 在此添加命令处理程序代码
	SelectDiolog *td=new SelectDiolog;	
	td->Create(IDD_SELECT_COLOR,this);
	td->ShowWindow(SW_SHOW);
}


void CRightView::OnUpdateSetColor(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(choose_head != NULL && choose_rect == 1 && choose_circle == 1);
}


void CRightView::OnUpdateSelectColor(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(choose_head != NULL && choose_rect == 1 && choose_circle == 1);
}
