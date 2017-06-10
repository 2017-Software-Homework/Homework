#pragma once
#include "Data.h"
#include <GL/glut.h>

extern COLORREF color_to_set,color;
extern int color_change;
extern int red,green,blue;

// CRightView ��ͼ

class CRightView : public CView
{
	DECLARE_DYNCREATE(CRightView)


public:
#define PI 3.1415926535
	float	 c;
	int du;
	float r,h;
	GLfloat scale_right;
	CPoint point_pos;
	COLORREF changed_color;
	void ShowTheColor(CDC *pDC);
	void ordination();
	HGLRC m_hRC;    //Rendering Context��ɫ������

    CDC* m_pDC;        //Device Context�豸������

    BOOL InitializeOpenGL();    //Initialize OpenGL

    BOOL SetupPixelFormat();    //Set up the Pixel Format

    void RenderScene();            //Render the Scene

public:
	int oldmy,oldmx;
	GLfloat rotate_x;
	GLfloat rotate_y;
	GLfloat rotate_z;



protected:
	CRightView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CRightView();

public:
	void OnDraw(CDC* pDC);      // ��д�Ի��Ƹ���ͼ
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEditRefresh();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};


