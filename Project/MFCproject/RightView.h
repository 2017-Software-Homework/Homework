#pragma once


// CRightView ��ͼ

class CRightView : public CView
{
	DECLARE_DYNCREATE(CRightView)


public:
	int red;
	int green;
	int blue;
	CPoint point_pos;
	COLORREF color;
	COLORREF changed_color;
	void ShowTheColor(CDC *pDC);

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
//	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
};


