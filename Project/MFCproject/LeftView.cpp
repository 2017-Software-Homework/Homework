// LeftView.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCproject.h"
#include "LeftView.h"


// CLeftView

IMPLEMENT_DYNCREATE(CLeftView, CView)

CLeftView::CLeftView()
{
	state = 0;
}

CLeftView::~CLeftView()
{
}

BEGIN_MESSAGE_MAP(CLeftView, CView)
	ON_COMMAND(ID_FILE_OPEN, &CLeftView::OnFileOpen)
END_MESSAGE_MAP()


// CLeftView 绘图

void CLeftView::OnDraw(CDC* pDC)
{
	
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


void CLeftView::OnFileOpen()
{
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,_T("位图文件(*.BMP)|*.BMP|jpg文件(*.jpg)|*.jpg||"));
	if (IDOK == dlg.DoModal())
	{
		state = 0;
		BmpName.Format(_T("%s"),dlg.GetPathName());
		extname = dlg.GetFileExt();
		extname.MakeLower();

		if (!extname.Compare(_T("bmp")))
		{
			ShowBitmap(BmpName);
		}
		else
		{
			state  = 1;
		}
		Invalidate();
	}
	// TODO: 在此添加命令处理程序代码
}

void CLeftView::ShowBitmap(CString BmpName)
{
	if (state == 0)
	{
		HBITMAP hBitmap = (HBITMAP)LoadImage(NULL,BmpName,IMAGE_BITMAP,0,0,LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
		m_bitmap.Detach();
		m_bitmap.Attach(hBitmap);
		state = 1;
		Invalidate();
	}
}

BOOL CLeftView::ShowJpgGif(CDC* pDC,CString strPath,int x,int y)
{
	IStream *pStm;
	CFileStatus fstatus;
	CFile file;
	LONG cb;
	return true;
}