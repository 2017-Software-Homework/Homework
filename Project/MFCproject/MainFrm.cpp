
// MainFrm.cpp : CMainFrame ���ʵ��
//

#include "stdafx.h"

#include "MainFrm.h"

#include "LeftView.h"
#include "RightView.h"
#include <set>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

COLORREF color,color1;
int color_status = 0;//�Ƿ�ı���ɫ 0-���ı� 1-�ı� 2-ѡ����һ���� 3-ѡ���˳����������� 4-ѡ������
int red,green,blue;
choose_array *choose_head,*choose_temp1,*choose_temp2,*choose_generate1,*choose_generate2;//generate��������������Ԫ��
set<int> color_to_show;

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
//	ON_COMMAND(ID_SET_COLOR, &CMainFrame::OnSetColor)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // ״̬��ָʾ��
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame ����/����

CMainFrame::CMainFrame()
{
	// TODO: �ڴ���ӳ�Ա��ʼ������
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("δ�ܴ���״̬��\n");
		return -1;      // δ�ܴ���
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return TRUE;
}



// CMainFrame ���

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame ��Ϣ�������



BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: �ڴ����ר�ô����/����û���
	BOOL bFlag = m_splitWnd.CreateStatic(this,1,2);
	if (bFlag)
	{
		CSize sz(550,100);
		m_splitWnd.CreateView(0,0,RUNTIME_CLASS(CLeftView),sz,pContext);
		m_splitWnd.CreateView(0,1,RUNTIME_CLASS(CRightView),sz,pContext);

	}
	return bFlag;
	//return CFrameWnd::OnCreateClient(lpcs, pContext);
}

