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
END_MESSAGE_MAP()


// ProjectDialog 消息处理程序


void ProjectDialog::OnSetColor()
{
	// TODO: 在此添加命令处理程序代码

}
