// MyListCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "ZhuHuiBeiShaDiaoARK.h"
#include "DLGPROCESS.h"
#include "MyListCtrl.h"


// CMyListCtrl

IMPLEMENT_DYNAMIC(CMyListCtrl, CListCtrl)

CMyListCtrl::CMyListCtrl()
: m_needSetItem(0)
, m_firstrun(false)
{
	m_OddItemBkColor=0xFEF1E3;//奇数行背景颜色
	m_EvenItemBkColor=0xFFFFFF;//偶数行背景颜色
	m_HoverItemBkColor=0xFF;//热点行背景颜色
	m_SelectItemBkColor=GetSysColor(COLOR_HIGHLIGHT);//选中行背景颜色
	m_OddItemTextColor=GetSysColor(COLOR_BTNTEXT);//奇数行文本颜色
	m_EvenItemTextColor=GetSysColor(COLOR_BTNTEXT);//偶数行文本颜色
	m_HoverItemTextColor=GetSysColor(COLOR_HIGHLIGHTTEXT);//热点行文本颜色
	m_SelectItemTextColor=GetSysColor(COLOR_BTNTEXT);//选中行文本颜色
	m_nHoverIndex=-1;
	m_firstrun = TRUE;
	m_bTracking=FALSE;

	for (int i = 0; i < 200; i++)
	{
		Arry[i] = -1;
	}
}

CMyListCtrl::~CMyListCtrl()
{
}


BEGIN_MESSAGE_MAP(CMyListCtrl, CListCtrl)
	ON_WM_MOUSEMOVE()
	ON_MESSAGE(WM_MOUSELEAVE,OnMouseLeave)
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, &CMyListCtrl::OnNMCustomdraw)
	//ON_NOTIFY(NM_RCLICK, IDC_LIST1, &CMyListCtrl::OnNMRClickList1)
END_MESSAGE_MAP()



// CMyListCtrl 消息处理程序


void CMyListCtrl::SetOddItemBkColor(COLORREF color,BOOL bDraw)//设置奇数行背景颜色
{
	m_OddItemBkColor=color;
	if(bDraw)InvalidateRect(NULL);
}
void CMyListCtrl::SetEvenItemBkColor(COLORREF color,BOOL bDraw)//设置偶数行背景颜色
{
	m_EvenItemBkColor=color;
	if(bDraw)InvalidateRect(NULL);
}
void CMyListCtrl::SetHoverItemBkColor(COLORREF color,BOOL bDraw)//设置热点行背景颜色
{
	m_HoverItemBkColor=color;
	if(bDraw)InvalidateRect(NULL);
}
void CMyListCtrl::SetSelectItemBkColor(COLORREF color,BOOL bDraw)//设置选中行背景颜色
{
	m_SelectItemBkColor=color;
	if(bDraw)InvalidateRect(NULL);
}
void CMyListCtrl::SetOddItemTextColor(COLORREF color,BOOL bDraw)//设置奇数行文本颜色
{
	m_OddItemTextColor=color;
	if(bDraw)InvalidateRect(NULL);
}
void CMyListCtrl::SetEvenItemTextColor(COLORREF color,BOOL bDraw)//设置偶数行文本颜色
{
	m_EvenItemTextColor=color;
	if(bDraw)InvalidateRect(NULL);
}
void CMyListCtrl::SetHoverItemTextColor(COLORREF color,BOOL bDraw)//设置热点行文本颜色
{
	m_HoverItemTextColor=color;
	if(bDraw)InvalidateRect(NULL);
}
void CMyListCtrl::SetSelectItemTextColor(COLORREF color,BOOL bDraw)//设置选中行文本颜色
{
	m_SelectItemTextColor=color;
	if(bDraw)InvalidateRect(NULL);
}


void CMyListCtrl::OnMouseMove(UINT nFlags, CPoint point)
{
	//int nIndex=HitTest(point);
	//if(nIndex!=m_nHoverIndex){
	//	int nOldIndex=m_nHoverIndex;
	//	m_nHoverIndex=nIndex;
	//	CRect rc;
	//	if(nOldIndex!=-1){
	//		GetItemRect(nOldIndex,&rc,LVIR_BOUNDS);
	//		InvalidateRect(&rc);
	//	}		
	//	if(m_nHoverIndex!=-1){
	//		GetItemRect(m_nHoverIndex,&rc,LVIR_BOUNDS);
	//		InvalidateRect(&rc);
	//	}
	//}
	////=====================================================
	//if(!m_bTracking) 
	//{ 
	//	TRACKMOUSEEVENT   tme; 
	//	tme.cbSize   =   sizeof(tme); 
	//	tme.hwndTrack   =   m_hWnd; 
	//	tme.dwFlags   =   TME_LEAVE;//   |   TME_HOVER; 
	//	tme.dwHoverTime   =   1; 
	//	m_bTracking   =   _TrackMouseEvent(&tme); 
	//} 
	CListCtrl::OnMouseMove(nFlags, point);
}
LRESULT CMyListCtrl::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	m_bTracking=FALSE;
	
	if(m_nHoverIndex!=-1){
		CRect rc;
		GetItemRect(m_nHoverIndex,&rc,LVIR_BOUNDS);
		m_nHoverIndex=-1;
		InvalidateRect(&rc);
	}
	return 0;
}
void CMyListCtrl::OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLVCUSTOMDRAW pNMCD = reinterpret_cast<LPNMLVCUSTOMDRAW>(pNMHDR);
	*pResult = 0;
	CString str;
	int nItemIndex=(int)pNMCD->nmcd.dwItemSpec;
	int nItemNum = this->GetItemCount();
	str = this->GetItemText(nItemIndex,7);
	if (pNMCD->nmcd.dwDrawStage==CDDS_PREPAINT){
		*pResult = CDRF_NOTIFYITEMDRAW;
	}else{
		if(nItemIndex==m_nHoverIndex){ //热点行
			//pNMCD->clrTextBk=m_HoverItemBkColor;
			//pNMCD->clrText=m_HoverItemTextColor;
		}else if(GetItemState(nItemIndex,LVIS_SELECTED) == LVIS_SELECTED){ //选中行
			pNMCD->clrTextBk=m_SelectItemBkColor;
			pNMCD->clrText=pNMCD->clrFace=m_SelectItemTextColor;
			::SetTextColor(pNMCD->nmcd.hdc,m_SelectItemTextColor);
		}
		//}else if(nItemIndex % 2==0){//偶数行 比如 0、2、4、6
		//	pNMCD->clrTextBk=m_EvenItemBkColor;
		//	pNMCD->clrText=m_EvenItemTextColor;
		//}else{	//奇数行 比如 1、3、5、7
		//	pNMCD->clrTextBk=m_OddItemBkColor;
		//	pNMCD->clrText=m_OddItemTextColor;
		//}
		if(str!="Microsoft Corporation")
		{
			str = this->GetItemText(nItemIndex,9);
			if( str != "Microsoft Corporation" )
				pNMCD->clrText = RGB(58,58,255);
		}
		if(m_firstrun){
			m_firstrun = FALSE;
		}else
		{
			if(IsExistForArry(nItemIndex))
				pNMCD->clrText = m_TextColor;
		}
		
		*pResult = CDRF_NEWFONT;
	}
}



void CMyListCtrl::SetItemTextColor(int nItem,COLORREF rgb,bool IsRecovery)
{
	m_TextColor = rgb;
	for (int i = 0; i < 200; i++)
	{
		if(!IsRecovery){
			if(Arry[i] == -1)//添加
			{
				Arry[i] = nItem;
				goto End;
			}
		}else//取消
		{
			if(Arry[i] == nItem)
			{
				Arry[i] = -1;
				goto End;
			}
		}
	}
End:
	InvalidateRect(NULL);
}


BOOL CMyListCtrl::IsExistForArry(int nItem)
{
	bool IsExis = FALSE;
	for (int i = 0; i < 200; i++)
	{
		if(Arry[i] == nItem)
		{
			IsExis = TRUE;
		}
			
	}
	return IsExis;
}
