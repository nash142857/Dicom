#pragma once
#include "DCMPatientInfo.h"
#include <memory>
#include "afxwin.h"
#include "Cshowsavepic.h"
// Cshowperson 对话框
#include "Cshowsavpiclocal.h"
#include "common.h"
#include "afxcmn.h"
// Cshowperson 对话框
class Cshowperson : public CDialogEx
{
	DECLARE_DYNAMIC(Cshowperson)

public:
	Cshowperson(CWnd* pParent = NULL);   // 标准构造函数
	void setdata(std::shared_ptr <DCMPatientInfo> _patient_data, std::string _id){
		id = _id;
		patient_data = _patient_data;
	}
	virtual ~Cshowperson();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

public:
	static std::shared_ptr <DCMPatientInfo> patient_data;
	static std::string id;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
private:
	int numofpic;
	int totalpic;
	std::string nowshowwhat;
	void if_save(){
		Cshowsavepic dig;
		dig.DoModal();
	}
	//update text
	void updateview(){
		CStringW toshow;
		toshow.Format(L"第 %d / %d 张",numofpic, totalpic);
		show_num_static.SetWindowTextW(toshow);
		OnPaint();
	}
	void update_menu(){ // to update menu version
		if(!PathIsDirectory(CommonLib::string_to_lpsctr("E:\\dicom_data\\" + id))){
			CreateDirectory(CommonLib::string_to_lpsctr("E:\\dicom_data\\" + id), NULL);
		}
		WIN32_FIND_DATA fileinfo;
		HANDLE handle =  FindFirstFile(CommonLib::string_to_lpsctr("E:\\dicom_data\\" + id + "\\*"), &fileinfo);
		do{
			if(fileinfo.dwFileAttributes == 16 && fileinfo.cFileName[0] != '.'){
				CString s(fileinfo.cFileName);
				GetMenu() -> GetSubMenu(1) -> AppendMenuW(MF_POPUP, 1001, s);
			}
		}while(FindNextFile(handle, &fileinfo));
	}
public:
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
	CStatic show_num_static;
	afx_msg void ShowADC();
	CStatic picname;
	afx_msg void showMTT();
	afx_msg void showCBF();
	afx_msg void showCBV();
	afx_msg void showfirstversion();
	afx_msg void showsecondversion();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedOk();
	virtual void OnCancel();
	CStatic picdata;
	CStatic picdata2;
	double dwivalue;
	int cutnum;
	double adc_threshold;
	CSliderCtrl cut_slider;
	CSliderCtrl adc_slider;
};
