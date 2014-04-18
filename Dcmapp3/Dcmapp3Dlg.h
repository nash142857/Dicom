
// Dcmapp3Dlg.h : ͷ�ļ�
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
// CDcmapp3Dlg �Ի���
class CDcmapp3Dlg : public CDialogEx
{
// ����
public:
	CDcmapp3Dlg(CWnd* pParent = NULL);	// ��׼���캯��
	static bool login_state;
	static CString username;
// �Ի�������
	enum { IDD = IDD_DCMAPP3_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	CRect m_rect;
	std::shared_ptr <Cofflinedeal>  poff;
	std::shared_ptr <Conlinedeal> pon;
	std::shared_ptr <Csetparam> pparam;
	virtual BOOL OnInitDialog();
	void change(CWnd *pWnd, int cx, int cy) {
		if(pWnd){
			CRect rect;   //��ȡ�ؼ��仯ǰ�Ĵ�С    
			 pWnd->GetWindowRect(&rect);  
			 ScreenToClient(&rect);//���ؼ���Сת��Ϊ�ڶԻ����е���������  
			rect.left=rect.left*cx/m_rect.Width();//�����ؼ���С  
			rect.right=rect.right*cx/m_rect.Width();  
			rect.top=rect.top*cy/m_rect.Height();  
			rect.bottom=rect.bottom*cy/m_rect.Height();  
			pWnd->MoveWindow(rect);//���ÿؼ���С  
		}  
	}
	/*
	void change_size(int a, int b){
		CRect rect;
		CList<CRect, CRect> listRect;
		listRect.AddTail(rect);//�Ի��������
		CWnd* pWnd = GetWindow(GW_CHILD);//��ȡ�Ӵ���
		while(pWnd){
			 pWnd->GetWindowRect(rect);//�Ӵ��������
			 listRect.AddTail(rect);           //CList<CRect,CRect> m_listRect��Ա����
			 pWnd = pWnd->GetNextWindow();//ȡ��һ���Ӵ���
		}
		SetWindowPos(NULL,0,0,a,b,SWP_NOMOVE); 
		 if (listRect.GetCount() > 0){
			CRect dlgNow;
			GetWindowRect(&dlgNow);
			 POSITION pos = listRect.GetHeadPosition();//��һ��������ǶԻ����Rect

			 CRect dlgSaved;
				dlgSaved = listRect.GetNext(pos);
				ScreenToClient(dlgNow);

				float x = dlgNow.Width() * 1.0 / dlgSaved.Width();//���ݵ�ǰ��֮ǰ����ĶԻ���Ŀ�������
				float y = dlgNow.Height()  *1.0/ dlgSaved.Height();
				ClientToScreen(dlgNow);

				CRect childSaved;

				 CWnd* pWnd = GetWindow(GW_CHILD);
				 while(pWnd)
			 {
   childSaved = listRect.GetNext(pos);//���λ�ȡ�Ӵ����Rect
   childSaved.left = dlgNow.left + (childSaved.left - dlgSaved.left)*x;//���ݱ��������ؼ��������Ҿ���Ի���ľ���
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
 //Invalidate(); //ǿ���ػ洰��
	// ���ɵ���Ϣӳ�亯��
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
	CButton onlinebutton;
	CButton offlinebutton;
	CButton setbutton;
};
