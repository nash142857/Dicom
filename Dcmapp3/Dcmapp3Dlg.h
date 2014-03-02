
// Dcmapp3Dlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "Cshowperson.h"
#include "Conlinedeal.h"
#include "Cofflinedeal.h"
#include "Csetparam.h"
#include <memory>
#include <string>
using std::string;
// CDcmapp3Dlg 对话框
class CDcmapp3Dlg : public CDialogEx
{
// 构造
public:
	CDcmapp3Dlg(CWnd* pParent = NULL);	// 标准构造函数
	static bool login_state;
	static CString username;
// 对话框数据
	enum { IDD = IDD_DCMAPP3_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	CRect m_rect;
	std::shared_ptr <Cofflinedeal>  poff;
	std::shared_ptr <Conlinedeal> pon;
	std::shared_ptr <Csetparam> pparam;
	virtual BOOL OnInitDialog();
	void change(CWnd *pWnd, int cx, int cy) {
		if(pWnd){
			CRect rect;   //获取控件变化前的大小    
			 pWnd->GetWindowRect(&rect);  
			 ScreenToClient(&rect);//将控件大小转换为在对话框中的区域坐标  
			rect.left=rect.left*cx/m_rect.Width();//调整控件大小  
			rect.right=rect.right*cx/m_rect.Width();  
			rect.top=rect.top*cy/m_rect.Height();  
			rect.bottom=rect.bottom*cy/m_rect.Height();  
			pWnd->MoveWindow(rect);//设置控件大小  
		}  
	}
	/*
	void change_size(int a, int b){
		CRect rect;
		CList<CRect, CRect> listRect;
		listRect.AddTail(rect);//对话框的区域
		CWnd* pWnd = GetWindow(GW_CHILD);//获取子窗体
		while(pWnd){
			 pWnd->GetWindowRect(rect);//子窗体的区域
			 listRect.AddTail(rect);           //CList<CRect,CRect> m_listRect成员变量
			 pWnd = pWnd->GetNextWindow();//取下一个子窗体
		}
		SetWindowPos(NULL,0,0,a,b,SWP_NOMOVE); 
		 if (listRect.GetCount() > 0){
			CRect dlgNow;
			GetWindowRect(&dlgNow);
			 POSITION pos = listRect.GetHeadPosition();//第一个保存的是对话框的Rect

			 CRect dlgSaved;
				dlgSaved = listRect.GetNext(pos);
				ScreenToClient(dlgNow);

				float x = dlgNow.Width() * 1.0 / dlgSaved.Width();//根据当前和之前保存的对话框的宽高求比例
				float y = dlgNow.Height()  *1.0/ dlgSaved.Height();
				ClientToScreen(dlgNow);

				CRect childSaved;

				 CWnd* pWnd = GetWindow(GW_CHILD);
				 while(pWnd)
			 {
   childSaved = listRect.GetNext(pos);//依次获取子窗体的Rect
   childSaved.left = dlgNow.left + (childSaved.left - dlgSaved.left)*x;//根据比例调整控件上下左右距离对话框的距离
   childSaved.right = dlgNow.right + (childSaved.right - dlgSaved.right)*x;
   childSaved.top = dlgNow.top + (childSaved.top - dlgSaved.top)*y;
   childSaved.bottom = dlgNow.bottom + (childSaved.bottom - dlgSaved.bottom)*y;
   ScreenToClient(childSaved);
   pWnd->MoveWindow(childSaved);
   pWnd = pWnd->GetNextWindow();
  }
 }

	}
	*/
 //Invalidate(); //强制重绘窗口
	// 生成的消息映射函数
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton3();
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedButton4();
	CButton login_button;
	CStatic welcome;
};
