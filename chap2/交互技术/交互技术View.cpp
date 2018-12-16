// ��������View.cpp : implementation of the CMyView class
//

#include "stdafx.h"
#include "��������.h"
#include "MessageDlg.h"
#include "��������Doc.h"
#include "��������View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyView

IMPLEMENT_DYNCREATE(CMyView, CView)

BEGIN_MESSAGE_MAP(CMyView, CView)
	//{{AFX_MSG_MAP(CMyView)
	ON_COMMAND(ID_DRAW_LINE, OnDrawLine)
	ON_COMMAND(ID_DRAW_TEXT, OnDrawText)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_DRAW_RECT, OnDrawRect)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyView construction/destruction

CMyView::CMyView()
{
//	m_dot_number=0;
 m_draw=false;
 m_bdoing=false;
  m_nwidth=1;
 m_color=RGB(0,0,255);
 m_pmdc = new CDC;
 m_pbmp = new CBitmap;

}


CMyView::~CMyView()
{delete m_pmdc;
 delete m_pbmp;
}

BOOL CMyView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMyView drawing

void CMyView::OnDraw(CDC* pDC)
{
	CMyDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CBitmap* poldbmp=m_pmdc->SelectObject(m_pbmp);
	pDC->BitBlt(0,0,m_nmx,m_nmy,m_pmdc,0,0,SRCCOPY);
	pDC->SelectObject(poldbmp);
}

/////////////////////////////////////////////////////////////////////////////
// CMyView printing

BOOL CMyView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMyView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMyView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMyView diagnostics

#ifdef _DEBUG
void CMyView::AssertValid() const
{
	CView::AssertValid();
}

void CMyView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyDoc* CMyView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyDoc)));
	return (CMyDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyView message handlers

void CMyView::OnDrawLine() 
{
m_type=1;
	
}
void CMyView::OnDrawRect() 
{
m_type=2;
	
}
void CMyView::OnDrawText() 
{
m_type=3;
CDC*pDC=GetDC();
CMessageDlg dlg(this);
int TextLong;
if(dlg.DoModal()==IDOK)
{
	str=dlg.m_Text;		//�õ���ע��������Ϣ
TextLong=str.GetLength();	//��ע���ֵĳ���
	if(TextLong>0){
	
	pDC->TextOut(dot_begin.x,dot_begin.y,str);
	}
	else 
	{pDC->TextOut(dot_begin.x,dot_begin.y,"�������ı�");}

}
	ReleaseDC(pDC);
}

void CMyView::OnLButtonDown(UINT nFlags, CPoint point) 
{


	//��ȡ�豸����
	CDC* pDC = GetDC() ;
	//�����GDI����ѡ���豸����
	pDC->SelectStockObject(NULL_BRUSH) ;
	m_draw=true;//��ʼ��ͼ
	switch(m_type){//����ͼ������ȷ��������ֵ
		case 1:
			dot_begin=point;//ȷ��ֱ�ߵ�ʼĩ�˵�ֵ
			dot_end=point;
            break;
	case 2:
		if(m_bdoing)//�ж��Ƿ��ڻ�ͼ״̬
		return;       
       {m_bdoing=true;
       SetCapture();//�����������
       m_pnew=point;//��Ϊ��û��ƾ��Σ�Բ�Ǿ��Σ���Բ�������в������Ͻǵ㣬�ͻ���ֱ�ߵ���ʼ��ֵ��
       m_pold=point;//��Ϊ��û��ƾ��Σ�Բ�Ǿ��Σ���Բ�������в������½ǵ㣬�ͻ���ֱ�ߵĽ�����ֵ��
		CBitmap* poldbmp;
		CPen pen;
	    pen.CreatePen(PS_SOLID,m_nwidth,m_color);
	    CPen* poldpen=m_pmdc->SelectObject(&pen);
		poldbmp=m_pmdc->SelectObject(m_pbmp);
		m_pmdc->SelectObject(poldpen);
     m_pmdc->SelectObject(poldbmp);
	}
		break;
	    case 3:
			dot_begin=point;
			break;
	  
		default:
			break;		
	}
	ReleaseDC(pDC) ;
	CView::OnLButtonDown(nFlags, point);
}

void CMyView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	 m_draw=false;	
	CDC* pDC = GetDC() ;//��ȡ�豸����
	CBitmap* poldbmp=m_pmdc->SelectObject(m_pbmp);
	CPen pen;
	pen.CreatePen(PS_SOLID,m_nwidth,m_color);		
	CPen* poldpen=m_pmdc->SelectObject(&pen);//�����GDI����ѡ���豸����	
	pDC->SelectStockObject(NULL_BRUSH) ;
	switch(m_type){
		case 1:
			dot_end=point;
			pDC->MoveTo(dot_begin.x,dot_begin.y);
			pDC->LineTo(dot_end.x,dot_end.y);
		break;
	   case 2:
			 if(m_bdoing)
			 {
			m_bdoing=false;
			CRect rect(m_pnew,m_pold);
			m_pmdc->Rectangle(rect);	
			Invalidate(false);//ʹ������Ч������OnDraw()�������������ڴ�����ͼ����ʾ����Ļ��
			m_pmdc->SelectObject(poldbmp);
			m_pmdc->SelectObject(poldpen);
			 }
			break;	
		default:
			break;
	}
ReleaseCapture();//�ͷ���겶��
}

void CMyView::OnMouseMove(UINT nFlags, CPoint point) 
{
	CDC* pDC = GetDC() ;
	CBitmap* poldbmp=m_pmdc->SelectObject(m_pbmp);
	CPen pen;
	pen.CreatePen(PS_SOLID,m_nwidth,m_color);
	CPen* poldpen=pDC->SelectObject(&pen);
	//���û�ͼģʽ��������ǰ�Ļ�ͼģʽ���Ա���

	CPoint pre_dot, cur_dot ;
	CStatusBar* pStatus=(CStatusBar*)
		AfxGetApp()->m_pMainWnd->GetDescendantWindow(ID_VIEW_STATUS_BAR);
	if(pStatus)
	{
		char tbuf[40];
		sprintf(tbuf,"(%8d,%8d)",point.x, point.y);
		//��״̬���ĵڶ��������������ǰ����λ��
		pStatus->SetPaneText(1,tbuf);
	}	   
	switch(m_type){
		case 1:
			if(m_draw){	int nDrawmode = pDC->SetROP2(R2_NOT) ;
	//�����GDI����ѡ���豸����
	pDC->SelectStockObject(NULL_BRUSH) ;
				pre_dot = dot_end ;
		        cur_dot = point ;
				//����ֱ��
				pDC->MoveTo(dot_begin.x,dot_begin.y);
                pDC->LineTo(pre_dot.x,pre_dot.y);
				pDC->MoveTo(dot_begin.x,dot_begin.y);
                pDC->LineTo(cur_dot.x,cur_dot.y);
				dot_end=point;				
				pDC->SetROP2(nDrawmode) ;}
			break;
         	
	   case 2:
		if (m_bdoing){
	CRect rectold(m_pold,m_pnew);//����ƶ�ǰ�ľ�������
   
   
	rectold.NormalizeRect();//ʹ���ι�񻯣����ƾ��ζ�������λ��
	rectold.InflateRect(m_nwidth,m_nwidth);//ʹԭ���εĿ��߷ֱ���չm_nwidth,m_nwidth������
	pDC->BitBlt(rectold.left,rectold.top,rectold.Width(),rectold.Height(),m_pmdc,rectold.left,rectold.top,SRCCOPY);//���ڴ����������ʾ������������Ļ��
	CRect rectnew(m_pold,point);
	pDC->Rectangle(rectnew);
		}
     	break;

	default:		
		break;	}
		 
    m_pmdc->SelectObject(poldbmp);
	pDC->SelectObject(poldpen);
	m_pnew=point;	//�ָ�����ǰ�Ļ�ͼģʽ
	ReleaseDC(pDC) ;	//�ͷŵ�����ʹ�õ�DC ��
	CView::OnMouseMove(nFlags, point);

}



int CMyView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	m_nmx=GetSystemMetrics(SM_CXSCREEN);
	m_nmy=GetSystemMetrics(SM_CXSCREEN);
	CDC* pDC=GetDC();
	m_pmdc->CreateCompatibleDC(pDC);
	m_pbmp->CreateCompatibleBitmap(pDC,m_nmx,m_nmy);//����һ���ߴ�Ϊm_nmx,m_nmy������ʾ�豸�������ݵ�λͼ
    CBitmap* pOldbitmap=m_pmdc->SelectObject(m_pbmp);//��λͼѡ�뵱ǰ�豸������ͬʱ����ԭ��λͼ

	CBrush brush;
	brush.CreateStockObject(WHITE_BRUSH);
	CRect rect(-1,-1,m_nmx,m_nmy);

	m_pmdc->FillRect(rect,&brush);
	m_pmdc->SelectObject(pOldbitmap);
	ReleaseDC(pDC);
	
	return 0;
}
