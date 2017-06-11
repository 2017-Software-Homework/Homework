
// MFCprojectView.cpp : CMFCprojectView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MFCproject.h"
#endif

#include "MFCprojectDoc.h"
#include "MFCprojectView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCprojectView

IMPLEMENT_DYNCREATE(CMFCprojectView, CView)

BEGIN_MESSAGE_MAP(CMFCprojectView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CMFCprojectView 构造/析构

CMFCprojectView::CMFCprojectView()
{
	// TODO: 在此处添加构造代码
	/*CMenu* menu = GetMenu()->GetSubMenu(2);
	menu->CheckMenuRadioItem(ID_CHOOSE_POINT,ID_CHOOSE_CIRCLE, ID_CHOOSE_POINT,MF_BYCOMMAND);*/
}

CMFCprojectView::~CMFCprojectView()
{
}

BOOL CMFCprojectView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMFCprojectView 绘制

void CMFCprojectView::OnDraw(CDC* /*pDC*/)
{
	CMFCprojectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CMFCprojectView 打印

BOOL CMFCprojectView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMFCprojectView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMFCprojectView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CMFCprojectView 诊断

#ifdef _DEBUG
void CMFCprojectView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCprojectView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCprojectDoc* CMFCprojectView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCprojectDoc)));
	return (CMFCprojectDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCprojectView 消息处理程序


