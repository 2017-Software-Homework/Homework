#pragma once


// CLeftView ��ͼ

class CLeftView : public CView
{
	DECLARE_DYNCREATE(CLeftView)

public:
	CString BmpName;
	CString extname;
	CBitmap m_bitmap;
	void ShowBitmap(CString BmpName,CDC *pDC);

protected:
	CLeftView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CLeftView();

public:
	virtual void OnDraw(CDC* pDC);      // ��д�Ի��Ƹ���ͼ
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


