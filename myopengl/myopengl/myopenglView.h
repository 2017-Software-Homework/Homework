
// myopenglView.h : CmyopenglView ��Ľӿ�
//

#pragma once
#include "enableview.h"
#include<GL\glut.h>
#include<stdlib.h>
#include<GL\gl.h>
#include<GL\glu.h>
#include<GL\glaux.h>
#include<cmath>
#include<iostream>
#include<Windows.h>
#include<stdio.h>
#include<vector>
using namespace std;


struct Vertex
{
	float x, y, z;
};

struct Texture
{
	float s, t;
};

struct Face
{
	int v[3];
	int vt[3];
	int vn[3];
};

struct FaceQ
{
	int v[4];
	int vt[4];
	int vn[4];
};
class CmyopenglView : public enableview
{
protected: // �������л�����
	CmyopenglView();
	DECLARE_DYNCREATE(CmyopenglView)

// ����
public:
	CmyopenglDoc* GetDocument() const;

// ����
public:

// ��д
public:
	//virtual void OnDrawGL(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	//MeshData *mesh, *last_mesh;
	CPoint MouseDownPoint;
	double X_Angle;
	double Y_Angle;

	// ����ģʽ
	int style;
	int cull;
	int zbuffer;
	int show_view;
	int PNormal;

	CString myText;//�ϲ�����
	CString myInfo;//������ʾ����

	void OnDrawGL(CDC* pDC);//���ƺ���
	void drawMyText();	//��ʾ��ʾ����,���Ը���

	virtual ~CmyopenglView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:


	BOOL read_block = false;
	CWinThread* m_pThread;     // �̶߳���ָ��
	HANDLE h1, h2; //�����߳̾��
	BOOL stopSmooth = FALSE;
	void ordination();
	afx_msg void Oncube();
	afx_msg void OnSphere();
	afx_msg void OnBamianti();
	afx_msg void OnErshimianti();
	afx_msg void OnFill();
	afx_msg void OnLine();
	afx_msg void OnPoint();
	afx_msg void OnWhite();
	afx_msg void OnMulticolor();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);





	void InitalLigt();
	virtual BOOL PreTranslateMessage(MSG* pMsg);



	float worldx, worldy, worldz;
	vector<Vertex> V, VN;
	vector<Face> F;
	vector<FaceQ>FQ;
	vector<Texture> VT;
	void ReadObj(char* Filename);
	afx_msg void OnReadobj();
	void Draw_obj();

	GLuint texture[6];
	//GLfloat xRotate = 0.0;

	char** resource_path = new char*[6];
	//GLuint		texture[1];							// �洢һ������
	//AUX_RGBImageRec *LoadBMP(char *Filename); //��������ͼƬ

	BOOL LoadImageResources();
	void Draw_textrue();
	afx_msg void OnTextrue();
	//int LoadGLTexturess(char * fileName);

	afx_msg void On32802();
	afx_msg void On32803();
	afx_msg void On32807();
	afx_msg void On32809();
	afx_msg void Onearth();
	afx_msg void Onyuanzhu();
	afx_msg void Onyuanzhui();
	afx_msg void Onord();
};

#ifndef _DEBUG  // myopenglView.cpp �еĵ��԰汾
inline CmyopenglDoc* CmyopenglView::GetDocument() const
   { return reinterpret_cast<CmyopenglDoc*>(m_pDocument); }
#endif

