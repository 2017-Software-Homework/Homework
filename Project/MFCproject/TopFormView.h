#pragma once



// CTopFormView ������ͼ

class CTopFormView : public CFormView
{
	DECLARE_DYNCREATE(CTopFormView)

protected:
	CTopFormView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CTopFormView();

public:
	enum { IDD = IDD_TOPFORMVIEW };
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


