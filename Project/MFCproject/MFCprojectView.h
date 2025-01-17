
// MFCprojectView.h : CMFCprojectView 类的接口
//

#pragma once


class CMFCprojectView : public CView
{
protected: // 仅从序列化创建
	CMFCprojectView();
	DECLARE_DYNCREATE(CMFCprojectView)

// 特性
public:
	CMFCprojectDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CMFCprojectView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnAnd();
	afx_msg void OnOr();
	afx_msg void OnMinus();
};

#ifndef _DEBUG  // MFCprojectView.cpp 中的调试版本
inline CMFCprojectDoc* CMFCprojectView::GetDocument() const
   { return reinterpret_cast<CMFCprojectDoc*>(m_pDocument); }
#endif

