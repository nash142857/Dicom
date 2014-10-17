// Cshowperson.cpp : 实现文件
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
	, cutnum(0)
	, adc_threshold(0)
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
	DDX_Text(pDX, IDC_EDIT_12, cutnum);
	DDX_Text(pDX, IDC_EDIT_13, adc_threshold);
	DDX_Control(pDX, IDC_SLIDER1, cut_slider);
	DDX_Control(pDX, IDC_SLIDER2, adc_slider);
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


// Cshowperson 消息处理程序


BOOL Cshowperson::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	cut_slider.SetRange(0, 100);
	cut_slider.SetPos(0);
	adc_slider.SetRange(0, 100);
	adc_slider.SetPos(50);
	SetWindowText(CommonLib::string_to_lpsctr("病人" + id));
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

	int mohu = 2;
	vector <const UINT16 *> store_data =  patient_data -> getDWIdata();
	/*vector <UINT16 *>
	for(int i = 0; i < store_data.size(); ++i){
		UINT16 * tmp = new UINT16[patient_data -> mDWIWidth * patient_data -> mDWIHeight];
		for(int j = 0; j < patient_data -> mDWIHeight; ++j)
			for(int k = 0; k < patient_data -> mDWIWidth; ++k){
				if(j - mohu >= 0 && j + mohu < patient_data -> mDWIHeight &&
					k - mohu >= 0 && k + mohu < patient_data -> mDWIWidth	){
						for(int o1 = -mohu; o1 <= mohu; ++o1){
							for(int o2 = -mohu; o2 <= mohu; ++o2){
								
							}
						}
				}
				else{
					tmp[j * patient_data -> mDWIWidth + k] = store_data[i] = 
				}
			}
	}
	*/
	const int margin = 50;
	int totalrow =  margin * 5 + patient_data -> mDWIHeight * 4;
	int totalcol = margin * 6 + patient_data -> mDWIWidth * 5;
	int size = totalrow * totalcol;
	UINT16 * total = new UINT16[size];
	for(int i = 0; i < size; ++i)
		total[i] = 600;
	byte * data = new byte[3 * patient_data -> mDWIWidth * patient_data -> mDWIHeight];
	for(int i = 0; i < store_data.size(); ++i){
		CommonLib::generate_bmp("E:\\research\\" + CommonLib::ito_string(i) + ".bmp", patient_data -> mDWIHeight,
			patient_data -> mDWIWidth, store_data[i],data,10000);
		int row = i / 5;
		int col = i % 5;
		int baserow = row * patient_data -> mDWIHeight + (row + 1) * margin;
		int basecol = col * patient_data -> mDWIWidth + (col + 1) * margin;
		for(int j = 0; j < patient_data -> mDWIWidth * patient_data -> mDWIHeight; ++j){
			int row1 = j / patient_data -> mDWIWidth;
			int col1 = j % patient_data -> mDWIWidth;
			int pos = (baserow + row1) * totalcol + basecol + col1;
			total[pos] = store_data[int(store_data.size()) - i - 1][j];
		}
	}
	delete [] data;
	data = new byte[3 * totalrow * totalcol];
	CommonLib::generate_bmp("E:\\research\\total.bmp", totalrow,
		totalcol, total,data,10000);//generate total
	delete [] data;
	delete [] total;
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void Cshowperson::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	Cshowperson p;
	p.DoModal();
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}

void Cshowperson::OnBnClickedButton2()
{
	int a = 3;
	if(numofpic == totalpic){
		AfxMessageBox(L"已经是最后一张了");
		return;
	}
	++numofpic;
	updateview();
		// TODO: 在此添加控件通知处理程序代码
}


void Cshowperson::OnBnClickedButton1()
{
	if(numofpic == 1){
		AfxMessageBox(L"已经是第一张了");
		return;
	}
	--numofpic;
	updateview();
	// TODO: 在此添加控件通知处理程序代码
}



void Cshowperson::ShowADC()
{
	numofpic = 1;
	totalpic = 25;
	nowshowwhat = "ADC";
	updateview();
	// TODO: 在此添加命令处理程序代码
}


void Cshowperson::showMTT()
{
	numofpic = 1;
	totalpic = 22;
	
	nowshowwhat = "MTT";
	updateview();
	// TODO: 在此添加命令处理程序代码
}


void Cshowperson::showCBF()
{
	numofpic = 1;
	totalpic = 25;
	picname.SetWindowTextW(L"CBF");
	updateview();
	// TODO: 在此添加命令处理程序代码
}


void Cshowperson::showCBV()
{
	numofpic = 1;
	totalpic = 25;
	picname.SetWindowTextW(L"CBV");
	updateview();
	// TODO: 在此添加命令处理程序代码
}


void Cshowperson::showfirstversion()
{
	numofpic = 1;
	totalpic = 25;
	picname.SetWindowTextW(L"ADC");
	updateview();
	// TODO: 在此添加命令处理程序代码
}


void Cshowperson::showsecondversion()
{
	numofpic = 1;
	totalpic = 25;
	picname.SetWindowTextW(L"ADC");
		
	updateview();
	// TODO: 在此添加命令处理程序代码
}


void Cshowperson::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	Cnamesavefile namefile;
	namefile.DoModal();
}


void Cshowperson::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}


void Cshowperson::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类
	if_save(); // before cancel do some work
	CDialogEx::OnCancel();
}
