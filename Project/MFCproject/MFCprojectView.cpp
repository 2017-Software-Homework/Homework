
// MFCprojectView.cpp : CMFCprojectView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CMFCprojectView ����/����

CMFCprojectView::CMFCprojectView()
{
	// TODO: �ڴ˴���ӹ������
	/*CMenu* menu = GetMenu()->GetSubMenu(2);
	menu->CheckMenuRadioItem(ID_CHOOSE_POINT,ID_CHOOSE_CIRCLE, ID_CHOOSE_POINT,MF_BYCOMMAND);*/
}

CMFCprojectView::~CMFCprojectView()
{
}

BOOL CMFCprojectView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CMFCprojectView ����

void CMFCprojectView::OnDraw(CDC* /*pDC*/)
{
	CMFCprojectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CMFCprojectView ��ӡ

BOOL CMFCprojectView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CMFCprojectView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CMFCprojectView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CMFCprojectView ���

#ifdef _DEBUG
void CMFCprojectView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCprojectView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCprojectDoc* CMFCprojectView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCprojectDoc)));
	return (CMFCprojectDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCprojectView ��Ϣ�������


