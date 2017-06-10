#pragma once

#include "Data.h"
// SelectDiolog 对话框

class SelectDiolog : public CDialogEx
{
	DECLARE_DYNAMIC(SelectDiolog)

public:
	SelectDiolog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~SelectDiolog();

// 对话框数据
	enum { IDD = IDD_SELECT_COLOR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSelectColor();
	afx_msg void OnBnClickedOk();
};
