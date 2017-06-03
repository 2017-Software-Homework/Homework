// ProjectDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCproject.h"
#include "ProjectDialog.h"
#include "afxdialogex.h"
#include "Data.h"

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
	ON_BN_CLICKED(IDOK, &ProjectDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// ProjectDialog ��Ϣ�������


void ProjectDialog::OnSetColor()
{
	// TODO: �ڴ���������������

}


void ProjectDialog::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
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
		wrong += 2;
	}
	if (b < 0 || b > 255)
	{
		wrong += 4;
	}	
	if (wrong == 0)
	{
		//MessageBox(_T("RֵΪ:") + str1 + _T("\nGֵΪ:") + str2 + _T("\nBֵΪ:") + str3,_T("�������н��"),MB_OK);
		//�����ʾ��,ֻ���ڲ���,����ҵʱ��ע��
		CDialog::OnOK();
		color = RGB(r,g,b);
		color_status = 1;
		Invalidate();
	}
	else
	{
		str_wrong = _T("");
		if (wrong % 2 == 1)
			str_wrong += _T("Rֵ����");
		if ((wrong / 2) % 2 == 1)
			str_wrong += _T("Gֵ����");
		if (wrong >= 4)
			str_wrong += _T("Bֵ����");
		MessageBox(str_wrong,_T("������ʾ"),MB_OK);
	}
}