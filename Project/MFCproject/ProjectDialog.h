#pragma once


// ProjectDialog �Ի���

class ProjectDialog : public CDialog
{
	DECLARE_DYNAMIC(ProjectDialog)

public:
	ProjectDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ProjectDialog();

// �Ի�������
	enum { IDD = IDD_SET_COLOR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSetColor();
	afx_msg void OnBnClickedOk();
};