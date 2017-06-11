#pragma once
#include "Data.h"
#include <GL/glut.h>

extern COLORREF color_to_set,color;
extern int color_change;
extern int red,green,blue;

// CRightView 视图

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
	HGLRC m_hRC;    //Rendering Context着色描述表

    CDC* m_pDC;        //Device Context设备描述表

    BOOL InitializeOpenGL();    //Initialize OpenGL

    BOOL SetupPixelFormat();    //Set up the Pixel Format

    void RenderScene();            //Render the Scene

public:
	int oldmy,oldmx;
	GLfloat rotate_x;
	GLfloat rotate_y;
	GLfloat rotate_z;



protected:
	CRightView();           // 动态创建所使用的受保护的构造函数
	virtual ~CRightView();

public:
	void OnDraw(CDC* pDC);      // 重写以绘制该视图
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
	afx_msg void OnAnd();
	afx_msg void OnOr();
	afx_msg void OnMinus();
	afx_msg void OnUpdateAnd(CCmdUI *pCmdUI);
	afx_msg void OnUpdateOr(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMinus(CCmdUI *pCmdUI);
	afx_msg void OnChoosePoint();
	afx_msg void OnChooseRect();
	afx_msg void OnChooseCircle();
	afx_msg void OnUpdateChooseCircle(CCmdUI *pCmdUI);
	afx_msg void OnUpdateChoosePoint(CCmdUI *pCmdUI);
	afx_msg void OnUpdateChooseRect(CCmdUI *pCmdUI);
	afx_msg void OnSetColor();
	afx_msg void OnSelectColor();
	afx_msg void OnUpdateSetColor(CCmdUI *pCmdUI);
	afx_msg void OnUpdateSelectColor(CCmdUI *pCmdUI);
	afx_msg void OnViewInformation();
	afx_msg void OnUpdateViewInformation(CCmdUI *pCmdUI);
	afx_msg void OnViewShow();
	afx_msg void OnUpdateViewShow(CCmdUI *pCmdUI);
};


