#pragma once

#include "Data.h"
// SelectDiolog �Ի���

class SelectDiolog : public CDialogEx
{
	DECLARE_DYNAMIC(SelectDiolog)

public:
	SelectDiolog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~SelectDiolog();

// �Ի�������
	enum { IDD = IDD_SELECT_COLOR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSelectColor();
	afx_msg void OnBnClickedOk();
};
