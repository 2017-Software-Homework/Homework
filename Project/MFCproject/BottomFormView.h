#pragma once



// CBottomFormView ������ͼ

class CBottomFormView : public CFormView
{
	DECLARE_DYNCREATE(CBottomFormView)

protected:
	CBottomFormView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CBottomFormView();

public:
	enum { IDD = IDD_BOTTOMFORMVIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};


