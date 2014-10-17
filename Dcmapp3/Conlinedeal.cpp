// Conlinedeal.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Dcmapp3.h"
#include "Conlinedeal.h"
#include "afxdialogex.h"
#include "Cshowperson.h"
#include "common.h"
#include "ShowCalProcess.h"
// Conlinedeal �Ի���

IMPLEMENT_DYNAMIC(Conlinedeal, CDialogEx)

Conlinedeal::Conlinedeal(CWnd* pParent /*=NULL*/)
	: CDialogEx(Conlinedeal::IDD, pParent)
{
}

Conlinedeal::~Conlinedeal()
{
}

void Conlinedeal::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, person_inf);
}
BEGIN_MESSAGE_MAP(Conlinedeal, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON3, &Conlinedeal::OnBnClickedButton3)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &Conlinedeal::OnNMDblclkList1)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST1, &Conlinedeal::OnLvnColumnclickList1)
END_MESSAGE_MAP()
// Conlinedeal ��Ϣ�������
BOOL Conlinedeal::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	SetWindowText(L"����");
	person_inf.InsertColumn( 0,L"����ID", LVCFMT_LEFT, 200);
	person_inf.InsertColumn( 1, L"����", LVCFMT_LEFT, 250);
	person_inf.InsertColumn( 2, L"���ʱ��",LVCFMT_LEFT, 200);
	person_inf.SetExtendedStyle(LVS_EX_GRIDLINES |LVS_EX_FULLROWSELECT);
	person_inf.InsertColumn( 3, L"���һ�μ���ʱ��",LVCFMT_LEFT, 200);
	vector <Patient_information> res;
	std::shared_ptr <ADOConn> getcon = ADOConn::sharedSingleton();
	res = getcon -> search_both("", "");
	std::sort(res.begin(), res.end(), [](const Patient_information & a, const Patient_information & b)
	-> bool {
		return a.modifytime < b.modifytime;
	});
	person_inf.DeleteAllItems();
	for(size_t i = 0; i < res.size(); ++i){
		int nrow = person_inf.InsertItem(0, res[i].id);
		person_inf.SetItemText(nrow, 1, res[i].name);
		person_inf.SetItemText(nrow, 2, res[i].modifytime.Format("%Y-%m-%d-%H:%M:%S"));
		person_inf.SetItemText(nrow, 3, res[i].modifytime.Format("%Y-%m-%d-%H:%M:%S"));
	}
	return TRUE;  
}
void Conlinedeal::OnBnClickedButton3()
{
	patient_id = GetDlgItemInt(IDC_EDIT2);
	GetDlgItemText(IDC_EDIT1, patient_name);
	CStringA sta(patient_name.GetBuffer(0));
	std::string name(sta.GetBuffer(0));
	patient_name.ReleaseBuffer();
	sta.ReleaseBuffer();
	std::string id = CommonLib::ito_string(patient_id);
	if(id == "0") id = ""; //some inner change
	std::shared_ptr <ADOConn> getcon = ADOConn::sharedSingleton();
	bool search_flag = true;
	vector <Patient_information> res;
	res = getcon -> search_both(id, name);
	std::sort(res.begin(), res.end(),[](const Patient_information & a, const Patient_information & b)
	-> bool {
		return a.modifytime < b.modifytime;
	});
	person_inf.DeleteAllItems();
	if(res.size() == 0)	
			search_flag = false;
	if(search_flag){
		for(size_t i = 0; i < res.size(); ++i){
			int nrow = person_inf.InsertItem(0, res[i].id);
			person_inf.SetItemText(nrow, 1, res[i].name);
			person_inf.SetItemText(nrow, 2, res[i].modifytime.Format("%Y-%m-%d-%H:%M:%S"));
			person_inf.SetItemText(nrow, 3, res[i].modifytime.Format("%Y-%m-%d-%H:%M:%S"));
		}
	}
	else
		AfxMessageBox(L"�Ҳ�����������");
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void Conlinedeal::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	int l = person_inf.GetItemCount();
	for(int i = 0; i < l; ++i){
		if(person_inf.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED){
			TCHAR szBuf[1024]; 
			LVITEM lvi; 
			lvi.iItem = i;
			lvi.iSubItem = 0;
			lvi.mask = LVIF_TEXT; 
			lvi.pszText = szBuf; 
			lvi.cchTextMax = 1024; 
			person_inf.GetItem(&lvi);
			shared_ptr<ADOConn> con = ADOConn::sharedSingleton();
			CStringA str(szBuf);
			string id = str.GetBuffer(0);
			str.ReleaseBuffer();
			Patient_information res = con -> search(id,0);
		/*	CShowCalProcess cal;
			cal.DoModal();
			if(CShowCalProcess::finished){// shared  variable
				// update the database
			*/	SYSTEMTIME now;
				GetLocalTime(&now);
				CTime cnowtime(int(now.wYear), int(now.wMonth),int(now.wDay), int(now.wHour),int(now.wMinute), int(now.wSecond));   
				std::shared_ptr <ADOConn> singleton = ADOConn::sharedSingleton();
				singleton -> update_checktime(id , cnowtime);
				//to show person
				shared_ptr <DCMPatientInfo> show_patient = CommonLib::get_patient_info(res);		
				show_patient -> resetconfig();
				show_patient -> getDWIVolumn();
				Cshowperson p = Cshowperson();
				p.setdata(show_patient, id);
				p.DoModal();
				//Cshowsavepic pp = Cshowsavepic();
				//pp.DoModal();
			return;
		}
	}
	AfxMessageBox(L"��ѡ��һ��");
	pResult = 0;
}

int CALLBACK comparemethod(LPARAM a, LPARAM b, LPARAM pa){
	std::pair<std::pair<int, int>, CListCtrl *> param = *(std::pair<std::pair<int, int>, CListCtrl *> *)(pa);
	CListCtrl * person_list = param.second;
	string s1 = CommonLib::wstr_to_stdstring(person_list -> GetItemText(a, param.first.second).AllocSysString());
	string s2 = CommonLib::wstr_to_stdstring(person_list -> GetItemText(b, param.first.second).AllocSysString());
	int sort = param.first.first;
	int ia, ib;
	CTime ta,tb;
	switch(param.first.second){
	case 0:
		ia = CommonLib::string_to_i(s1);
		ib = CommonLib::string_to_i(s2);
		if(sort)
			return ia < ib;
		else
			return ia > ib;
	case 1:
	case 3: 
			   if(sort)
				   return s1 < s2;
			   else
				   return s1 > s2;
	case 2:
		ta = CommonLib::string_to_ctime(s1);
		tb = CommonLib::string_to_ctime(s2);
		if(sort) 
			return ta < tb;
		else
			return tb < ta;
	default:
		return 0;
	}
}
void Conlinedeal::OnLvnColumnclickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	int length = person_inf.GetItemCount();
	for(int i = 0; i < length; ++i){
		person_inf.SetItemData(i, i);
	}
	static int sort = 0;
	sort = 1 - sort;
	person_inf.SortItems(comparemethod, (DWORD_PTR)&(std::make_pair(std::make_pair(sort, pNMLV -> iSubItem), &person_inf)));
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}