// LeftView.cpp : ʵ���ļ�
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


// CLeftView ��ͼ

void CLeftView::OnDraw(CDC* pDC)
{
	
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


void CLeftView::OnFileOpen()
{
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,_T("λͼ�ļ�(*.BMP)|*.BMP|jpg�ļ�(*.jpg)|*.jpg||"));
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
	// TODO: �ڴ���������������
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