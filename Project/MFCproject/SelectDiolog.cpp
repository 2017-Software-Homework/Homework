// SelectDiolog.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCproject.h"
#include "SelectDiolog.h"
#include "afxdialogex.h"


// SelectDiolog 对话框

IMPLEMENT_DYNAMIC(SelectDiolog, CDialogEx)

SelectDiolog::SelectDiolog(CWnd* pParent /*=NULL*/)
	: CDialogEx(SelectDiolog::IDD, pParent)
{

}

SelectDiolog::~SelectDiolog()
{
}

void SelectDiolog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(SelectDiolog, CDialogEx)
	ON_COMMAND(ID_SELECT_COLOR, &SelectDiolog::OnSelectColor)
	ON_BN_CLICKED(IDOK, &SelectDiolog::OnBnClickedOk)
END_MESSAGE_MAP()


// SelectDiolog 消息处理程序


void SelectDiolog::OnSelectColor()
{
	// TODO: 在此添加命令处理程序代码
}


void SelectDiolog::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	int wrong = 0;
	CString strText(_T(""));
	GetDlgItemText(IDC_SELECT,strText);
	if (strText == _T(""))
	{
		wrong += 1;
	}
	CEdit *pBox1,*pBox2,*pBox3,*pBox4,*pBox5,*pBox6;
	pBox1 = (CEdit*) GetDlgItem(IDC_EDIT1);
	pBox2 = (CEdit*) GetDlgItem(IDC_EDIT2);
	pBox3 = (CEdit*) GetDlgItem(IDC_EDIT3);
	pBox4 = (CEdit*) GetDlgItem(IDC_EDIT4);
	pBox5 = (CEdit*) GetDlgItem(IDC_EDIT5);
	pBox6 = (CEdit*) GetDlgItem(IDC_EDIT6);
	CString str1,str2,str3,str4,str5,str6,str_wrong;
	int r,g,b,r1,g1,b1;
	pBox1->GetWindowText(str1);
	pBox2->GetWindowText(str2);
	pBox3->GetWindowText(str3);
	pBox4->GetWindowText(str4);
	pBox5->GetWindowText(str5);
	pBox6->GetWindowText(str6);
	r = _ttoi(str1);
	g = _ttoi(str2);
	b = _ttoi(str3);
	r1 = _ttoi(str4);
	g1 = _ttoi(str5);
	b1 = _ttoi(str6);
	if (r < 0 || r > 255)
	{
		wrong += 2;
	}
	if (g < 0 || g > 255)
	{
		wrong += 4;
	}
	if (b < 0 || b > 255)
	{
		wrong += 8;
	}	
	if (r1 < 0 || r1 > 255)
	{
		wrong += 16;
	}
	if (g1 < 0 || g1 > 255)
	{
		wrong += 32;
	}
	if (b1 < 0 || b1 > 255)
	{
		wrong += 64;
	}
	if (strText != _T("点") && strText != _T("球") && strText != _T("长方体"))
	{
		color_status += 128;
	}
	if (wrong == 0)
	{
		///MessageBox(_T("R值为:") + str1 + _T("\nG值为:") + str2 + _T("\nB值为:") + str3,_T("程序运行结果"),MB_OK);
		//输出提示框,只用于测试,交作业时加注释
		
		color = RGB(r,g,b);
		color1 = RGB(r1,g1,b1);
		if (strText == _T("点"))
		{
			color_status = 2;
		}
		if (strText == _T("球"))
		{
			color_status = 4;
		}
		if (strText == _T("长方体"))
		{
			color_status = 3;
		}
		CDialog::OnOK();
	}
	else
	{
		str_wrong = _T("");
		if (wrong % 2 == 1)
		{
			str_wrong += _T("未选择范围");
		}
		else
		{
			if ((wrong / 128) % 2 == 1)
				str_wrong += _T("选择范围错误");
		}
		if ((wrong / 2) % 2 == 1)
			str_wrong += _T("第一个点R值错误");
		if ((wrong / 4) % 2 == 1)
			str_wrong += _T("第一个点G值错误");
		if ((wrong / 8) % 2 == 1)
			str_wrong += _T("第一个点B值错误");
		if ((wrong / 16) % 2 == 1)
			str_wrong += _T("第二个点R值错误");
		if ((wrong / 32) % 2 == 1)
			str_wrong += _T("第二个点G值错误");
		if ((wrong / 64) % 2 == 1)
			str_wrong += _T("第二个点B值错误");
		MessageBox(str_wrong,_T("错误提示"),MB_OK);
	}
}
