#pragma once


// ProjectDialog 对话框

class ProjectDialog : public CDialog
{
	DECLARE_DYNAMIC(ProjectDialog)

public:
	ProjectDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ProjectDialog();

// 对话框数据
	enum { IDD = IDD_PROJECTDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSetColor();
};
