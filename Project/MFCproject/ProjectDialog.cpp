// ProjectDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCproject.h"
#include "ProjectDialog.h"
#include "afxdialogex.h"


// ProjectDialog 对话框

IMPLEMENT_DYNAMIC(ProjectDialog, CDialog)

ProjectDialog::ProjectDialog(CWnd* pParent /*=NULL*/)
	: CDialog(ProjectDialog::IDD, pParent)
{

}

ProjectDialog::~ProjectDialog()
{
}

void ProjectDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ProjectDialog, CDialog)
	ON_COMMAND(ID_SET_COLOR, &ProjectDialog::OnSetColor)
	ON_BN_CLICKED(IDOK, &ProjectDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// ProjectDialog 消息处理程序


void ProjectDialog::OnSetColor()
{
	// TODO: 在此添加命令处理程序代码

}


void ProjectDialog::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialog::OnOK();
	CEdit *pBox1,*pBox2,*pBox3;
	pBox1 = (CEdit*) GetDlgItem(IDC_EDIT1);
	pBox2 = (CEdit*) GetDlgItem(IDC_EDIT2);
	pBox3 = (CEdit*) GetDlgItem(IDC_EDIT3);
	CString str1,str2,str3,str_wrong;
	int r,g,b;
	int wrong;
	pBox1->GetWindowText(str1);
	pBox2->GetWindowText(str2);
	pBox3->GetWindowText(str3);
	r = _ttoi(str1);
	g = _ttoi(str2);
	b = _ttoi(str3);
	wrong = 0;
	if (r < 0 || r > 255)
	{
		wrong += 1;
	}
	if (g < 0 || g > 255)
	{
		wrong += 10;
	}
	if (b < 0 || b > 255)
	{
		wrong += 100;
	}
	
	if (wrong == 0)
	{
		MessageBox(_T("R值为:") + str1 + _T("\nG值为:") + str2 + _T("\nB值为:") + str3,_T("程序运行结果"),MB_OK);//输出提示框,只用于测试,交作业时加注释
	}
	else
	{
		str_wrong = _T("");
		if (wrong % 10 == 1)
			str_wrong += _T("R值错误");
		if ((wrong / 10) % 10 == 1)
			str_wrong += _T("G值错误");
		if (wrong >= 100)
			str_wrong += _T("B值错误");
		MessageBox(str_wrong,_T("错误提示"),MB_OK);
	}

}
