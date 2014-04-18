// Cshowperson.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Dcmapp3.h"
#include "Cshowperson.h"
#include "afxdialogex.h"
#include "common.h"
#include "Cnamesavefile.h"
std::shared_ptr <DCMPatientInfo> Cshowperson::patient_data;
std::string Cshowperson::id;
IMPLEMENT_DYNAMIC(Cshowperson, CDialogEx)

Cshowperson::Cshowperson(CWnd* pParent /*=NULL*/)
	: CDialogEx(Cshowperson::IDD, pParent)
	, dwivalue(0)
{

}

Cshowperson::~Cshowperson()
{
}

void Cshowperson::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PIC_STATIC, picdata2);
	DDX_Control(pDX, IDC_NUM_STATIC, show_num_static);
	DDX_Text(pDX, IDC_ADC_1, dwivalue);
}


BEGIN_MESSAGE_MAP(Cshowperson, CDialogEx)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &Cshowperson::OnNMDblclkList1)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON2, &Cshowperson::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &Cshowperson::OnBnClickedButton1)
	ON_COMMAND(ID_32779, &Cshowperson::ShowADC)
	ON_COMMAND(ID_32782, &Cshowperson::showMTT)
	ON_COMMAND(ID_32783, &Cshowperson::showCBF)
	ON_COMMAND(ID_32784, &Cshowperson::showCBV)
	ON_COMMAND(ID_32778, &Cshowperson::showfirstversion)
	ON_COMMAND(ID_32785, &Cshowperson::showsecondversion)
	ON_BN_CLICKED(IDC_BUTTON3, &Cshowperson::OnBnClickedButton3)
	ON_BN_CLICKED(IDOK, &Cshowperson::OnBnClickedOk)
END_MESSAGE_MAP()


// Cshowperson ��Ϣ�������


BOOL Cshowperson::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	SetWindowText(CommonLib::string_to_lpsctr("����" + id));
	

	double pwivalue = (int)((patient_data -> getPWIVolumn()) * 100);
	pwivalue /= 100;
	dwivalue = (int)((patient_data -> getDWIVolumn()) * 100);
	dwivalue /= 100;
	double mismatch = pwivalue / dwivalue;
	mismatch = (int)(mismatch * 100);
	mismatch /= 100;
	UpdateData(false);
	numofpic = 2;
	totalpic = 25;
	nowshowwhat = "ADC";
	UpdateData(false);
	update_menu();

	/*****store_pic******/
	vector <const UINT16 *> store_data =  patient_data -> getDWIdata();
	for(int i = 0; i < store_data.size(); ++i){
		CommonLib::generate_bmp("E:\\research\\" + CommonLib::ito_string(i) + ".bmp", patient_data -> mDWIHeight,
			patient_data -> mDWIWidth, store_data[i], 10000);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void Cshowperson::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	Cshowperson p;
	p.DoModal();
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}


void Cshowperson::OnPaint()
{
	/*
	CPaintDC dc(this); // device context for painting
	CImage img;
	//choose img to show
	{
		CString str;
		if(nowshowwhat == "MTT")
			str.Format(L"E:\\vs2012\\Dcmapp3\\Dcmapp3\\MTT\\MTT_%d.jpg", numofpic);
		else
			str.Format(L"E:\\vs2012\\Dcmapp3\\Dcmapp3\\ADC\\ADC_%d.jpg", numofpic);
		img.Load(str);
	}
	CRect rect;
	picdata2.GetClientRect(&rect);
	CDC * pdc = picdata2.GetDC();
	pdc -> SetROP2(R2_NOTXORPEN);
	SetStretchBltMode(pdc -> m_hDC, STRETCH_HALFTONE);
	int width = img.GetWidth();
	int height = img.GetHeight();
	img.StretchBlt(pdc -> m_hDC, rect, SRCCOPY);    // ��Ӧ��������Ĵ�С
	ReleaseDC(pdc);
	*/
}


void Cshowperson::OnBnClickedButton2()
{
	int a = 3;
	if(numofpic == totalpic){
		AfxMessageBox(L"�Ѿ������һ����");
		return;
	}
	++numofpic;
	updateview();
		// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void Cshowperson::OnBnClickedButton1()
{
	if(numofpic == 1){
		AfxMessageBox(L"�Ѿ��ǵ�һ����");
		return;
	}
	--numofpic;
	updateview();
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}



void Cshowperson::ShowADC()
{
	numofpic = 1;
	totalpic = 25;
	nowshowwhat = "ADC";
	updateview();
	// TODO: �ڴ���������������
}


void Cshowperson::showMTT()
{
	numofpic = 1;
	totalpic = 22;
	
	nowshowwhat = "MTT";
	updateview();
	// TODO: �ڴ���������������
}


void Cshowperson::showCBF()
{
	numofpic = 1;
	totalpic = 25;
	picname.SetWindowTextW(L"CBF");
	updateview();
	// TODO: �ڴ���������������
}


void Cshowperson::showCBV()
{
	numofpic = 1;
	totalpic = 25;
	picname.SetWindowTextW(L"CBV");
	updateview();
	// TODO: �ڴ���������������
}


void Cshowperson::showfirstversion()
{
	numofpic = 1;
	totalpic = 25;
	picname.SetWindowTextW(L"ADC");
	updateview();
	// TODO: �ڴ���������������
}


void Cshowperson::showsecondversion()
{
	numofpic = 1;
	totalpic = 25;
	picname.SetWindowTextW(L"ADC");
		
	updateview();
	// TODO: �ڴ���������������
}


void Cshowperson::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	Cnamesavefile namefile;
	namefile.DoModal();
}


void Cshowperson::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnCancel();
}


void Cshowperson::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���
	if_save(); // before cancel do some work
	CDialogEx::OnCancel();
}
