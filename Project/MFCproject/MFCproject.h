
// MFCproject.h : MFCproject Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CMFCprojectApp:
// �йش����ʵ�֣������ MFCproject.cpp
//

class CMFCprojectApp : public CWinApp
{
public:
	CMFCprojectApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMFCprojectApp theApp;
