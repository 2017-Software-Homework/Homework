
// MainFrm.cpp : CMainFrame 类的实现
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
int color_status = 0;//是否改变颜色 0-不改变 1-改变 2-选择了一个点 3-选择了长方体两个点 4-选择了球
int red,green,blue;
choose_array *choose_head,*choose_temp1,*choose_temp2,*choose_generate1,*choose_generate2;//generate仅适用于生成新元素
set<int> color_to_show;

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
//	ON_COMMAND(ID_SET_COLOR, &CMainFrame::OnSetColor)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
	// TODO: 在此添加成员初始化代码
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
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return TRUE;
}



// CMainFrame 诊断

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


// CMainFrame 消息处理程序



BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: 在此添加专用代码和/或调用基类
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

