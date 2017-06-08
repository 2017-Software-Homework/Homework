
// myopenglView.cpp : CmyopenglView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "myopengl.h"
#endif
#include"enableview.h"
#include "myopenglDoc.h"
#include "myopenglView.h"
#include <vector>
#include<stdio.h>
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>  
using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
static int model = 0;
static int type = 0;
static int zuobiao = 0;
// 设置材质颜色
GLfloat mat_ambient[] = { 0.6f, 0.6f, 0.6f, 1.0f };						// 蓝色的材质环境光
GLfloat mat_diffuse[] = { 0.6f, 0.6f, 0.9f, 1.0f };						// 蓝色的材质漫反射光
GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };					// 全白色的材质镜面反射光
GLfloat mat_emission[] = { 0.5f, 0.5f, 0.5f, 1.0f };					// 淡白色的材质辐射光

GLfloat no_mat[] = { 0.0f, 0.0f, 0.0f, 1.0f };							// 无光(黑色光),用于关闭某种属性光时应用
GLfloat no_shininess[] = { 0.0f };										// 无镜面反射
GLfloat low_shininess[] = { 5.0f };										// 低镜面反射指数
GLfloat high_shininess[] = { 70.0f };									// 高镜面反射指数
// CmyopenglView

IMPLEMENT_DYNCREATE(CmyopenglView, enableview)

BEGIN_MESSAGE_MAP(CmyopenglView, enableview)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_cube, &CmyopenglView::Oncube)
	ON_COMMAND(ID_SPHERE, &CmyopenglView::OnSphere)
	ON_COMMAND(ID_Bamianti, &CmyopenglView::OnBamianti)
	ON_COMMAND(ID_Ershimianti, &CmyopenglView::OnErshimianti)
	ON_COMMAND(ID_FILL, &CmyopenglView::OnFill)
	ON_COMMAND(ID_LINE, &CmyopenglView::OnLine)
	ON_COMMAND(ID_POINT, &CmyopenglView::OnPoint)
	ON_COMMAND(ID_WHITE, &CmyopenglView::OnWhite)
	ON_COMMAND(ID_MULTICOLOR, &CmyopenglView::OnMulticolor)
	ON_WM_CREATE()
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_READOBJ, &CmyopenglView::OnReadobj)
	ON_COMMAND(ID_TEXTRUE, &CmyopenglView::OnTextrue)

	ON_COMMAND(ID_32802, &CmyopenglView::On32802)
	ON_COMMAND(ID_32803, &CmyopenglView::On32803)
	ON_COMMAND(ID_32807, &CmyopenglView::On32807)
	ON_COMMAND(ID_32809, &CmyopenglView::On32809)
	ON_COMMAND(ID_earth, &CmyopenglView::Onearth)
	ON_COMMAND(ID_yuanzhu, &CmyopenglView::Onyuanzhu)
	ON_COMMAND(ID_yuanzhui, &CmyopenglView::Onyuanzhui)
	ON_COMMAND(ID_ord, &CmyopenglView::Onord)
END_MESSAGE_MAP()

// CmyopenglView 构造/析构

CmyopenglView::CmyopenglView()
{
	 model = 1;
	 type = 1;
	 zuobiao = 1;
}

CmyopenglView::~CmyopenglView()
{
}

BOOL CmyopenglView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	if (!enableview::PreCreateWindow(cs)) {
		return FALSE;
	}

	return TRUE;
}

// CmyopenglView 绘制


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
void CmyopenglView::ordination() {
	
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
	glPushMatrix();
	glColor3f(0.9f, 0.9f, 0.9f);
	glTranslatef(-4, -4, -4);
	GLGrid(0,0,0,8,0,8,20);
	glPopMatrix();


	glPushMatrix();
	glTranslated(-4,4, -4);
	glRotatef(90, 1.0, 0.0, 0.0);
	glColor3f(0.9f, 0.9f, 0.0f);
	GLGrid(0, 0, 0, 8, 0, 8, 20);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(-4, -4, -4);
	glRotatef(90, 0.0, 0.0, 1.0);
	glColor3f(0.0f, 0.9f, 0.0f);
	GLGrid(0, 0, 0, 8, 0, 8, 20);
	glPopMatrix();

	//x
	//glTranslatef(-2, -2, -2);
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(3.5, 0.0f, 0.0f);
	glEnd();
	glPushMatrix();
	glTranslatef(3.5, 0.0f, 0.0f);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	glutWireCone(0.027, 0.09, 10, 10);
	glPopMatrix();


	//y
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0, 3.5, 0.0f);
	glEnd();
	glPushMatrix();
	glTranslatef(0.0, 3.5, 0.0f);
	glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
	glutWireCone(0.027, 0.09, 10, 10);
	glPopMatrix();


	//z
	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0, 0.0f, 3.5);
	glEnd();
	glPushMatrix();
	glTranslatef(0.0, 0.0f, 3.5);
	glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
	glutWireCone(0.027, 0.09, 10, 10);
	glPopMatrix();


	glDisable(GL_BLEND);
	glDisable(GL_LINE_SMOOTH);
	glDisable(GL_POINT_SMOOTH);
	glDisable(GL_POLYGON_SMOOTH);
	
}




void CmyopenglView::OnDrawGL(CDC* pDC)
{

	

	if (model == 5)
	{
		LoadImageResources();
		Draw_textrue();
	}
	else
	{

	
	glClearColor(0.0f, 0.1f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	InitalLigt();		///初始化光照信息
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, scale);		//滚轮缩放
	gluLookAt(r*cos(c*du), h, r*sin(c*du), 0, 0, 0, 0, 1, 0); //从视点看远点,y轴方向(0,1,0)是上方向，鼠标拖动
	glRotatef(this->rotate_x, 1.0, 0.0, 0.0);
	glRotatef(this->rotate_y, 0.0, 1.0, 0.0);
	glRotatef(this->rotate_z, 0.0, 0.0, 1.0);
	if (zuobiao)
		ordination();
	glColor3f(1.0f, 1.0f, 1.0f);
	if (model == 1)
	{
		if (type == 1)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		if (type == 2)
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		if (type == 3)
			glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		auxSolidCube(4);

	}
	if (model == 2)
	{
		if (type == 1)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		if (type == 2)
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);		
		if(type == 3)
			glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		auxSolidSphere(3.0);
	}

	if (model == 3)
	{
		glPushMatrix();
		glRotatef(90, -1.0, 0.0, 0.0);
		if (type == 1)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		if (type == 2)
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		if (type == 3)
			glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		glutSolidCone(3, 3, 100, 100);
		glPopMatrix();

	}

	if (model == 4)
	{
		if (type == 1)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		if (type == 2)
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		if (type == 3)
			glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		glutSolidTeapot(2.5);
	}

	if (model == 6) {
		Draw_obj();
	}
	

	glPopMatrix();
	}
	// TODO: 在此处为本机数据添加绘制代码
}


// CmyopenglView 打印

BOOL CmyopenglView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CmyopenglView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CmyopenglView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CmyopenglView 诊断

#ifdef _DEBUG
void CmyopenglView::AssertValid() const
{
	CView::AssertValid();
}

void CmyopenglView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CmyopenglDoc* CmyopenglView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CmyopenglDoc)));
	return (CmyopenglDoc*)m_pDocument;
}
#endif //_DEBUG


// CmyopenglView 消息处理程序

void CmyopenglView::drawMyText()
{
	CDC *pDC = GetWindowDC();
	pDC->DrawText(myText, CRect(6, 6, 160, 420), DT_WORDBREAK); ReleaseDC(pDC);
	pDC->DrawText(myInfo, CRect(160, 420, 320, 840), DT_WORDBREAK); ReleaseDC(pDC);
}

// 弹出对话框


void CmyopenglView::InitalLigt()
{
	GLfloat light_position1[4] = { -52, -16, -50, 0 };
	GLfloat light_position2[4] = { -26, -48, -50, 0 };
	GLfloat light_position3[4] = { 16, -52, -50, 0 };

	GLfloat direction1[3] = { 52, 16, 50 };
	GLfloat direction2[3] = { 26, 48, 50 };
	GLfloat direction3[3] = { -16, 52, 50 };

	GLfloat light_position4[4] = { 52, 16, 50, 0 };
	GLfloat light_position5[4] = { 26, 48, 50, 0 };
	GLfloat light_position6[4] = { -16, 52, 50, 0 };

	GLfloat direction4[3] = { -52, -16, -50 };
	GLfloat direction5[3] = { -26, -48, -50 };
	GLfloat direction6[3] = { 16, -52, -50 };

	GLfloat color1[4], color2[4], color3[4], color4[4], color5[4], color6[4];

	glClearColor(1, 1, 1, 0);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	if (color_type == 0) {	//彩色灯光
		color1[0] = 1; color1[1] = 0; color1[2] = 0; color1[3] = 1;
		color2[0] = 0.5; color2[1] = 1; color2[2] = 0; color2[3] = 1;
		color3[0] = 0; color3[1] = 0; color3[2] = 1; color3[3] = 1;

		color4[0] = 1; color4[1] = 0; color4[2] = 0; color4[3] = 1;
		color5[0] = 0.5; color5[1] = 1; color5[2] = 0; color5[3] = 1;
		color6[0] = 0; color6[1] = 0; color6[2] = 1; color6[3] = 1;

		GLfloat ambient[4] = { 0.3f, 0.3f, 0.3f, 1.0f };

		GLfloat material_color[4] = { 1, 1, 1, 0.5f };
		GLfloat material_specular[4] = { 0.5f, 0.5f, 0.5f, 0.5f };
		GLfloat material_ambient[4] = { 0.0, 0.0, 0.0, 0.0 };

		glLightfv(GL_LIGHT3, GL_POSITION, light_position4);
		glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, direction4);
		glLightfv(GL_LIGHT3, GL_DIFFUSE, color4);
		glLightfv(GL_LIGHT3, GL_SPECULAR, color4);

		glLightfv(GL_LIGHT4, GL_POSITION, light_position5);
		glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, direction5);
		glLightfv(GL_LIGHT4, GL_DIFFUSE, color5);
		glLightfv(GL_LIGHT4, GL_SPECULAR, color5);

		glLightfv(GL_LIGHT5, GL_POSITION, light_position6);
		glLightfv(GL_LIGHT5, GL_SPOT_DIRECTION, direction6);
		glLightfv(GL_LIGHT5, GL_DIFFUSE, color6);
		glLightfv(GL_LIGHT5, GL_SPECULAR, color6);

		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);

		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_specular);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_color);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_ambient);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 128);

		glDisable(GL_LIGHT0);
		glDisable(GL_LIGHTING);
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT3);
		glEnable(GL_LIGHT4);
		glEnable(GL_LIGHT5);

		glDisable(GL_COLOR_MATERIAL);
		return;
	}


	if (color_type == 1)
	{
		//白色灯光
		glDisable(GL_LIGHT3);
		glDisable(GL_LIGHT4);
		glDisable(GL_LIGHT5);
		glDisable(GL_LIGHTING);
		GLfloat m_LightPostion[4] = { 0.0f, 10.0f, 10.0f, 1.0f };

		GLfloat ambientLight[] = { 0.25f, 0.25f, 0.25f, 1.0f };
		GLfloat diffuseLight[] = { 0.5, 0.5f, 0.5f, 1.0f };
		GLfloat specularLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };

		glEnable(GL_LIGHTING);
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
		glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
		glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
		glLightfv(GL_LIGHT0, GL_POSITION, m_LightPostion);
		glEnable(GL_LIGHT0);

		glEnable(GL_COLOR_MATERIAL);
		glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	}
	else {
		
		glDisable(GL_LIGHT3);
		glDisable(GL_LIGHT4);
		glDisable(GL_LIGHT5);
		glDisable(GL_LIGHTING);
		glDisable(GL_COLOR_MATERIAL);
		glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
		//glDisable(GL_LIGHTING);
		GLfloat no_ambientLight[] = { 0.0f, 0.0f, 0.0f, 1.0f };					// 用于关掉默认的全局环境光
																				// 设置光源的颜色
		GLfloat ambientLight[] = { 0.8f, 0.8f, 0.8f, 1.0f };					// 白色环境光
		GLfloat diffuseLight[] = { 0.8f, 0.8f, 0.8f, 1.0f };					// 白色漫射光
		GLfloat specularLight[] = { 0.8f, 0.8f, 0.8f, 1.0f };					// 白色镜面反射光
		GLfloat m_LightPostion[] = { 0.0f, 0.0f, 1.0f, 0.0f };					// 光源起始位置
		
		// 2.仅漫射光
		if (color_type == 12) {
			glEnable(GL_LIGHTING);
			//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, no_ambientLight);			// 关掉默认的全局环境光
			glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
			glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
			glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
			glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
			glLightfv(GL_LIGHT0, GL_POSITION, m_LightPostion);
			
			glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);					// 关闭材质的环境反射光颜色
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);			// 设置mat_diffuse的材质漫反射光
			glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);				// 关闭材质的镜面反射光颜色
			glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);			// 设置材质的镜面反射指数为0
			glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);				// 关闭材质的辐射光
			glEnable(GL_LIGHT0);
		}
		// 3.仅镜面光
		if (color_type == 13) {
			glEnable(GL_LIGHTING);
			//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, no_ambientLight);			// 关掉默认的全局环境光
			glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
			glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
			glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
			glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
			glLightfv(GL_LIGHT0, GL_POSITION, m_LightPostion);

			glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, no_mat);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
			glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
			glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
			glEnable(GL_LIGHT0);
		}
		
	
		// 6.漫射光与低镜面光
		if (color_type == 16) {
			glEnable(GL_LIGHTING);
			glLightModelfv(GL_LIGHT_MODEL_AMBIENT, no_ambientLight);			// 关掉默认的全局环境光
			glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
			glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
			glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
			glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
			glLightfv(GL_LIGHT0, GL_POSITION, m_LightPostion);

			glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
			glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
			glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
			glEnable(GL_LIGHT0);
		}
	
		// 8.辐射光与低镜面光
		if (color_type == 18) {
			glEnable(GL_LIGHTING);
			glLightModelfv(GL_LIGHT_MODEL_AMBIENT, no_ambientLight);			// 关掉默认的全局环境光
			glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
			glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
			glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
			glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
			glLightfv(GL_LIGHT0, GL_POSITION, m_LightPostion);

			glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, no_mat);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
			glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
			glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
			glEnable(GL_LIGHT0);
		}
	}
}


BOOL CmyopenglView::PreTranslateMessage(MSG* pMsg)
{
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

			this->rotate_x += 6.0;
			if (this->rotate_x < -360)this->rotate_x = 360;
			this->InvalidateRect(NULL, FALSE);
		}
		if (pMsg->wParam == _T('A'))
		{

			this->rotate_y -= 6.0;
			if (this->rotate_y < -360)this->rotate_y = 360;
			this->InvalidateRect(NULL, FALSE);
		}
		if (pMsg->wParam == _T('D'))
		{

			this->rotate_y += 6.0;
			if (this->rotate_y > 360)this->rotate_y = -360;
			this->InvalidateRect(NULL, FALSE);
		}
		if (pMsg->wParam == _T('Z'))
		{

			this->rotate_z -= 6.0;
			if (this->rotate_z < -360)this->rotate_z = 360;
			this->InvalidateRect(NULL, FALSE);
		}
		if (pMsg->wParam == _T('E'))
		{

			this->rotate_z += 6.0;
			if (this->rotate_z > 360)this->rotate_z = -360;
			this->InvalidateRect(NULL, FALSE);
		}
		if (pMsg->wParam == _T('Q'))
		{
			if ((scale + 2)  <  10)
				scale += 2;

			this->InvalidateRect(NULL, FALSE);
		}
		if (pMsg->wParam == _T('R'))
		{
				scale -= 2;

			this->InvalidateRect(NULL, FALSE);
		}
		

	}

	return CView::PreTranslateMessage(pMsg);
}


void CmyopenglView::ReadObj(char* Filename)
{
	VN.clear();
	V.clear();
	VT.clear();
	F.clear();
	FQ.clear();
	ifstream in(Filename);
	string aline; //逐行读入
	string erase;
	while (getline(in, aline))
	{
		if (aline[0] == 'v')
		{
			if (aline[1] == 'n') //vn
			{
				istringstream sin(aline);
				Vertex v;
				sin >> erase >> v.x >> v.y >> v.z;
				VN.push_back(v);
			}

			else if (aline[1] == 't')//vt
			{
				istringstream sin(aline);
				Texture v;
				sin >> erase >> v.s >> v.t;
				VT.push_back(v);
			}

			else //v
			{
				istringstream sin(aline);
				Vertex v;
				sin >> erase >> v.x >> v.y >> v.z;
				V.push_back(v);
			}
		}

		else if (aline[0] == 'f')
		{
			istringstream sin(aline);
			sin >> erase;
			vector<string> strvector;
			string temp;


			while (sin >> temp) {
				strvector.push_back(temp);
			}

			if (strvector.size() == 3) {//三角面片
				Face fff;
				for (int count = 0; count < 3; count++) {
					string kkk = strvector[count];
					int i = 0;
					int num = 0;
					//顶点索引
					for (; i < kkk.size() && kkk[i] != '/'; i++)
						num = num * 10 + kkk[i] - '0';
					fff.v[count] = num;
					i++;
					num = 0;
					//vt
					num = 0;
					for (; i < kkk.size() && kkk[i] != '/'; i++)
						num = num * 10 + kkk[i] - '0';
					fff.vt[0] = num;
					i++;
					num = 0;
					//法向量索引
					for (; i < kkk.size() && kkk[i] != '/'; i++)
						num = num * 10 + kkk[i] - '0';
					fff.vn[count] = num;

				}
				F.push_back(fff);
			}

			else if (strvector.size() == 4)
			{


				FaceQ fff;
				for (int count = 0; count < strvector.size(); count++) {
					string kkk = strvector[count];
					int i = 0;
					int num = 0;
					//顶点索引
					for (; i < kkk.size() && kkk[i] != '/'; i++)
						num = num * 10 + kkk[i] - '0';
					fff.v[count] = num;
					i++;
					num = 0;
					//vt
					num = 0;
					for (; i < kkk.size() && kkk[i] != '/'; i++)
						num = num * 10 + kkk[i] - '0';
					fff.vt[0] = num;
					i++;
					num = 0;
					//法向量索引
					for (; i < kkk.size() && kkk[i] != '/'; i++)
						num = num * 10 + kkk[i] - '0';
					fff.vn[count] = num;

				}

				FQ.push_back(fff);
			}

		}
	}


}

void CmyopenglView::OnReadobj()
{
	model = 6;


	wchar_t filters[] =
		L"3D模型文件(*.obj)\
|*.obj|所有文件(*.*)|*.*||";
	CFileDialog fileDlg(TRUE, NULL, NULL,
		OFN_HIDEREADONLY, filters);
	if (fileDlg.DoModal() == IDOK)
	{

		CString strBuf = fileDlg.GetPathName();
		USES_CONVERSION;
		char *Filename = T2A(strBuf.GetBuffer(0));
		ReadObj(Filename);
	}
	stringstream ss;
	ss <<"OK!";
	string str;
	ss >> str;
	CString s;
	s = str.c_str();
	MessageBox(s);

	float min_x, min_y, min_z, max_x, max_y, max_z;
	min_x = min_y = min_z = 10000000;
	max_x = max_y = max_z = -1000000;
	for (int i = 0; i < V.size(); i++)
	{
		min_x = min(min_x, V[i].x);
		min_y = min(min_y, V[i].y);
		min_z = min(min_z, V[i].z);
		max_x = max(max_x, V[i].x);
		max_y = max(max_y, V[i].y);
		max_z = max(max_z, V[i].z);
	}
	worldx = (min_x + max_x) / 2;
	worldy = (min_y + max_y) / 2;
	worldz = (min_z + max_z) / 2;
	type = 1;
	Invalidate();
	CDC* ppDC = GetWindowDC();
	OnDrawGL(ppDC);
	// TODO: 在此添加命令处理程序代码
}

void CmyopenglView::Draw_obj()
{
	if (type == 1) {
		if (!VN.empty()) {
			for (int i = 0; i < F.size(); i++) {
				glBegin(GL_LINE_LOOP);
				for (int j = 0; j < 3; j++) {
					glVertex3f(V[F[i].v[j] - 1].x, V[F[i].v[j] - 1].y, V[F[i].v[j] - 1].z);
				}
				glEnd();
			}

			for (int i = 0; i < FQ.size(); i++) {
				glBegin(GL_LINE_LOOP);
				for (int j = 0; j < 4; j++) {

					glVertex3f(V[FQ[i].v[j] - 1].x, V[FQ[i].v[j] - 1].y, V[FQ[i].v[j] - 1].z);
				}
				glEnd();
			}

		}
		else {
			for (int i = 0; i < F.size(); i++) {
				glBegin(GL_LINE_LOOP);
				for (int j = 0; j < 3; j++) {
					glVertex3f(V[F[i].v[j] - 1].x, V[F[i].v[j] - 1].y, V[F[i].v[j] - 1].z);

				}
				glEnd();
			}

			for (int i = 0; i < FQ.size(); i++) {
				glBegin(GL_LINE_LOOP);
				for (int j = 0; j < 4; j++) {
					glVertex3f(V[FQ[i].v[j] - 1].x, V[FQ[i].v[j] - 1].y, V[FQ[i].v[j] - 1].z);

				}
				glEnd();
			}
		}

	}

	else if (type == 3) {
		glBegin(GL_POINTS);
		for (int i = 0; i < V.size(); i++)
			glVertex3f(V[i].x, V[i].y, V[i].z);
		glEnd();
	}

	else
	{
		if (!VN.empty()) {
			for (int i = 0; i < F.size(); i++) {
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				glBegin(GL_TRIANGLES);

				for (int j = 0; j < 3; j++) {

					glNormal3f(VN[F[i].vn[j] - 1].x, VN[F[i].vn[j] - 1].y, VN[F[i].vn[j] - 1].z);
					glVertex3f(V[F[i].v[j] - 1].x, V[F[i].v[j] - 1].y, V[F[i].v[j] - 1].z);

				}
				glEnd();
			}

			for (int i = 0; i < FQ.size(); i++) {
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				glBegin(GL_QUADS);
				for (int j = 0; j < 4; j++) {

					glNormal3f(VN[FQ[i].vn[j] - 1].x, VN[FQ[i].vn[j] - 1].y, VN[FQ[i].vn[j] - 1].z);
					glVertex3f(V[FQ[i].v[j] - 1].x, V[FQ[i].v[j] - 1].y, V[FQ[i].v[j] - 1].z);

				}
				glEnd();
			}
		}

		else
		{
			for (int i = 0; i < F.size(); i++) {
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				glBegin(GL_TRIANGLES);

				for (int j = 0; j < 3; j++) {
					glVertex3f(V[F[i].v[j] - 1].x, V[F[i].v[j] - 1].y, V[F[i].v[j] - 1].z);
				}
				glEnd();

			}

			for (int i = 0; i < FQ.size(); i++) {
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				glBegin(GL_QUADS);

				for (int j = 0; j < 4; j++) {
					glVertex3f(V[FQ[i].v[j] - 1].x, V[FQ[i].v[j] - 1].y, V[FQ[i].v[j] - 1].z);
				}
				glEnd();

			}
		}

	}
}




void CmyopenglView::Draw_textrue() {
	GLUquadricObj* qobj;
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	InitalLigt();		///初始化光照信息
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	glPushMatrix();
	glTranslatef(0.0f, 0.0f, scale);		//滚轮缩放
	gluLookAt(r*cos(c*du), h, r*sin(c*du), 0, 0, 0, 0, 1, 0); //从视点看远点,y轴方向(0,1,0)是上方向，鼠标拖动
	glRotatef(this->rotate_x, 1.0, 0.0, 0.0);
	glRotatef(this->rotate_y, 0.0, 1.0, 0.0);
	glRotatef(this->rotate_z, 0.0, 0.0, 1.0);
	if (zuobiao)
		ordination();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	qobj = gluNewQuadric();
	//画球体

	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glEnable(GL_TEXTURE_2D);
	gluQuadricTexture(qobj, GL_TRUE);//纹理函数
	if (type == 51)
	{
		glBegin(GL_QUADS);
		// Front Face
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-3.0f, -3.0f, 3.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(3.0f, -3.0f, 3.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(3.0f, 3.0f, 3.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-3.0f, 3.0f, 3.0f);

		// Back Face
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-3.0f, -3.0f, -3.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-3.0f, 3.0f, -3.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(3.0f, 3.0f, -3.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(3.0f, -3.0f, -3.0f);

		// Top Face
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-3.0f, 3.0f, -3.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-3.0f, 3.0f, 3.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(3.0f, 3.0f, 3.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(3.0f, 3.0f, -3.0f);

		// Bottom Face
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-3.0f, -3.0f, -3.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(3.0f, -3.0f, -3.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(3.0f, -3.0f, 3.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-3.0f, -3.0f, 3.0f);

		// Right face
		glTexCoord2f(0.0f, 0.0f); glVertex3f(3.0f, -3.0f, -3.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(3.0f, 3.0f, -3.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(3.0f, 3.0f, 3.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(3.0f, -3.0f, 3.0f);

		// Left Face
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-3.0f, -3.0f, -3.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-3.0f, -3.0f, 3.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-3.0f, 3.0f, 3.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-3.0f, 3.0f, -3.0f);
		glEnd();
	}
	if( type == 52 )
	gluSphere(qobj, 4, 60, 60);//二次曲面qobj
	if( type == 53 )
	gluCylinder(qobj, 3.5, 3.5, 6, 26, 23);
	if( type == 54 )
	gluCylinder(qobj, 3.5, 0.0, 6, 26, 23);

	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

}



BOOL CmyopenglView::LoadImageResources()
{
	FILE *File = NULL;
	AUX_RGBImageRec* textrue_Resource[6];
	if (model == 5 && type == 51)
		resource_path[0] = "shuijing.bmp";
	if(model == 5 && type == 52 )
		resource_path[0] = "earth.bmp";
	if (model == 5 && type == 53)
		resource_path[0] = "painting1.bmp";	
	if (model == 5 && type == 54)
		resource_path[0] = "5.bmp";



	/*resource_path[1] = "image/2.bmp";
	resource_path[2] = "image/3.bmp";
	resource_path[3] = "image/4.bmp";
	resource_path[4] = "image/5.bmp";
	resource_path[5] = "image/6.bmp";*/
	
	//装载图像文件资源	
	for (int i = 0; i < 6; i++)//如果只需要一张贴图其实resource_path数组只需要一个元素就可以了
	{
		File = fopen(resource_path[0], "r");
		if (!File)
		{
			//MessageBox(NULL, "加载图像资源文件失败 !", "Fail", MB_OK);
			return FALSE;
		}
		fclose(File);
		CString str = CString(resource_path[0]);
		USES_CONVERSION;
		LPCWSTR wszClassName = A2CW(W2A(str));
		textrue_Resource[i] = auxDIBImageLoad(wszClassName);
		File = NULL;
	}

	//生成纹理
	glGenTextures(6, texture);
	for (int i = 0; i < 6; i++)
	{
		glBindTexture(GL_TEXTURE_2D, texture[i]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		//Use the mipmap texture
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, \
			textrue_Resource[i]->sizeX, textrue_Resource[i]->sizeY, \
			GL_RGB, GL_UNSIGNED_BYTE, textrue_Resource[i]->data);

		//删除堆上的临时图像
		delete textrue_Resource[i]->data;
		delete textrue_Resource[i];
	}

	return TRUE;
}


void CmyopenglView::Oncube()
{
	// TODO: 在此添加命令处理程序代码
	model = 1;
	Invalidate();
	CDC* ppDC = GetWindowDC();

	OnDrawGL(ppDC);

}


void CmyopenglView::OnSphere()
{
	// TODO: 在此添加命令处理程序代码
	model = 2;
	Invalidate();
	CDC* ppDC = GetDC();
	OnDrawGL(ppDC);
}


void CmyopenglView::OnBamianti()
{
	// TODO: 在此添加命令处理程序代码
	model = 3;
	Invalidate();
	CDC* ppDC = GetDC();
	OnDrawGL(ppDC);
}


void CmyopenglView::OnErshimianti()
{
	// TODO: 在此添加命令处理程序代码
	model = 4;
	Invalidate();
	CDC* ppDC = GetDC();
	OnDrawGL(ppDC);
}


void CmyopenglView::OnFill()
{
	// TODO: 在此添加命令处理程序代码

	type = 2;
	Invalidate();
	CDC* ppDC = GetWindowDC();

	OnDrawGL(ppDC);

}


void CmyopenglView::OnLine()
{
	// TODO: 在此添加命令处理程序代码
	type = 1;
	Invalidate();
	CDC* ppDC = GetWindowDC();

	OnDrawGL(ppDC);

}


void CmyopenglView::OnPoint()
{
	// TODO: 在此添加命令处理程序代码
	type = 3;
	Invalidate();
	CDC* ppDC = GetWindowDC();

	OnDrawGL(ppDC);
	//this->OnDraw(this->GetDC());	//重绘界面
}


void CmyopenglView::OnWhite()
{
	// TODO: 在此添加命令处理程序代码
	myInfo = "白色";
	color_type = 1;
	//this->InvalidateRect(NULL, FALSE);
	this->OnDraw(this->GetDC());	//重绘界面
}


void CmyopenglView::OnMulticolor()
{
	// TODO: 在此添加命令处理程序代码
	myInfo = "彩色";
	color_type = 0;
	//this->InvalidateRect(NULL, FALSE);
	this->OnDraw(this->GetDC());	//重绘界面
}


int CmyopenglView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (enableview::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码

	return 0;
}


void CmyopenglView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	enableview::OnKeyDown(nChar, nRepCnt, nFlags);
}



void CmyopenglView::On32802()
{
	// TODO: 在此添加命令处理程序代码
	color_type = 12;
	//this->InvalidateRect(NULL, FALSE);
	this->OnDraw(this->GetDC());	//重绘界面
}


void CmyopenglView::On32803()
{
	// TODO: 在此添加命令处理程序代码
	color_type = 13;
	//this->InvalidateRect(NULL, FALSE);
	this->OnDraw(this->GetDC());	//重绘界面
}







void CmyopenglView::On32807()
{
	// TODO: 在此添加命令处理程序代码
	color_type = 16;
	//this->InvalidateRect(NULL, FALSE);
	this->OnDraw(this->GetDC());	//重绘界面
}





void CmyopenglView::On32809()
{
	// TODO: 在此添加命令处理程序代码
	color_type = 18;
	//this->InvalidateRect(NULL, FALSE);
	this->OnDraw(this->GetDC());	//重绘界面
}




void CmyopenglView::OnTextrue()
{
	// TODO: 在此添加命令处理程序代码

	model = 5;
	type = 51;
	Invalidate();
	CDC* ppDC = GetWindowDC();

	OnDrawGL(ppDC);

}

void CmyopenglView::Onearth()
{
	// TODO: 在此添加命令处理程序代码
	model = 5;
	type = 52;
	Invalidate();
	CDC* ppDC = GetWindowDC();

	OnDrawGL(ppDC);
}

void CmyopenglView::Onyuanzhu()
{
	// TODO: 在此添加命令处理程序代码
	model = 5;
	type = 53;
	Invalidate();
	CDC* ppDC = GetWindowDC();

	OnDrawGL(ppDC);
}



void CmyopenglView::Onyuanzhui()
{
	// TODO: 在此添加命令处理程序代码
	model = 5;
	type = 54;
	Invalidate();
	CDC* ppDC = GetWindowDC();

	OnDrawGL(ppDC);
}





void CmyopenglView::Onord()
{
	// TODO: 在此添加命令处理程序代码
	zuobiao = !zuobiao;
	this->OnDraw(this->GetDC());	//重绘界面

}
