#pragma once


// CLeftView 视图

class CLeftView : public CView
{
	DECLARE_DYNCREATE(CLeftView)

public:
	int state;
	CString BmpName;
	CString extname;
	CBitmap m_bitmap;
	void ShowBitmap(CString BmpName);
	BOOL ShowJpgGif(CDC* pDC,CString strPath,int x,int y);

protected:
	CLeftView();           // 动态创建所使用的受保护的构造函数
	virtual ~CLeftView();

public:
	virtual void OnDraw(CDC* pDC);      // 重写以绘制该视图
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFileOpen();
};


