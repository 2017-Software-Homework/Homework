// ProjectDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCproject.h"
#include "ProjectDialog.h"
#include "afxdialogex.h"


// ProjectDialog �Ի���

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


// ProjectDialog ��Ϣ�������


void ProjectDialog::OnSetColor()
{
	// TODO: �ڴ���������������

}
