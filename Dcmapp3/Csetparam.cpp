// Csetparam.cpp : 实现文件
//

#include "stdafx.h"
#include "Dcmapp3.h"
#include "Csetparam.h"
#include "afxdialogex.h"
#include "Dcmapp3Dlg.h"
#include <fstream>
#include "CalParam.h"
#include <map>
#include "common.h"
using namespace CommonLib;
// Csetparam 对话框
std::string const Csetparam::paramfilename =  "parameter.txt";
map <string, string> Csetparam::explain;
IMPLEMENT_DYNAMIC(Csetparam, CDialogEx)
Csetparam::Csetparam(CWnd* pParent /*=NULL*/)
	: CDialogEx(Csetparam::IDD, pParent)
	, Psetnum(0)
	, Pslicenum(0)
	, TE(0)
	, TR(0)
	, STDNum(0)
	, ck1(0)
	, ck2(0)
	, ck3(0)
	, TType(0)
	, Pmask(0)
	, x00(0)
	, x01(0)
	, x02(0)
	, x10(0)
	, x11(0)
	, x12(0)
	, pr(0)
	, ro(0)
	, hsv(0)
	, hlv(0)
	, coef(0)
	, cbfc(0)
	, mttc(0)
	, Tmax_th(0)
	, VP_th(0)
	, Dsetnum(0)
	, Dslicenum(0)
	, b(0)
	, adcmin(0)
	, adcmax(0)
	, adc_th(0)
	, VD_th(0)
{

}

Csetparam::~Csetparam()
{
}
void Csetparam::setconfig(){
		CalParam::Psetnum =  Psetnum;
		CalParam::Pslicenum =  Pslicenum;
		CalParam::TE = TE;
		CalParam::TR =  TR;
		CalParam::STDNum = STDNum;
		CalParam::Pmask =  Pmask;
		CalParam::ck1 =  ck1;
		CalParam::ck2 = ck2;
		CalParam::ck3= ck3;
		CalParam::TType = TType;
		CalParam::x00 = x00;
		CalParam::x01 = x01;
		CalParam::x02 = x02;
		CalParam::x10 = x10;
		CalParam::x11 = x11;
		CalParam::x12 = x12;
		CalParam::pr =  pr;
		CalParam::ro = ro;
		CalParam::hsv = hsv;
		CalParam::hlv = hlv;
		CalParam::coef = coef;
		CalParam::cbfc = cbfc;
		CalParam::mttc =  mttc;
		CalParam::Tmax_th = Tmax_th;
		CalParam::VP_th = VP_th;
		CalParam::Dsetnum = Dsetnum;
		CalParam::Dslicenum = Dslicenum;
		CalParam::b =  b;
		CalParam::adcmin = adcmin;
		CalParam::adcmax = adcmax;
		CalParam::adc_th = adc_th;
		CalParam::VD_th = VD_th;
}
void Csetparam::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, Psetnum);
	DDX_Text(pDX, IDC_EDIT2, Pslicenum);
	DDX_Text(pDX, IDC_EDIT3, TE);
	DDX_Text(pDX, IDC_EDIT4, TR);
	DDX_Text(pDX, IDC_EDIT5, STDNum);
	DDX_Text(pDX, IDC_EDIT7, ck1);
	DDX_Text(pDX, IDC_EDIT8, ck2);
	DDX_Text(pDX, IDC_EDIT9, ck3);
	DDX_Text(pDX, IDC_EDIT10, TType);
	DDX_Text(pDX, IDC_EDIT6, Pmask);
	DDX_Text(pDX, IDC_EDIT13, x00);
	DDX_Text(pDX, IDC_EDIT14, x01);
	DDX_Text(pDX, IDC_EDIT15, x02);
	DDX_Text(pDX, IDC_EDIT17, x10);
	DDX_Text(pDX, IDC_EDIT16, x11);
	DDX_Text(pDX, IDC_EDIT18, x12);
	DDX_Text(pDX, IDC_EDIT111, pr);
	DDX_Text(pDX, IDC_EDIT12, ro);
	DDX_Text(pDX, IDC_EDIT21, hsv);
	DDX_Text(pDX, IDC_EDIT22, hlv);
	DDX_Text(pDX, IDC_EDIT23, coef);
	DDX_Text(pDX, IDC_EDIT24, cbfc);
	DDX_Text(pDX, IDC_EDIT25, mttc);
	DDX_Text(pDX, IDC_EDIT26, Tmax_th);
	DDX_Text(pDX, IDC_EDIT27, VP_th);
	DDX_Text(pDX, IDC_EDIT20, Dsetnum);
	DDX_Text(pDX, IDC_EDIT29, Dslicenum);
	DDX_Text(pDX, IDC_EDIT300, b);
	DDX_Text(pDX, IDC_EDIT31, adcmin);
	DDX_Text(pDX, IDC_EDIT32, adcmax);
	DDX_Text(pDX, IDC_EDIT33, adc_th);
	DDX_Text(pDX, IDC_EDIT34, VD_th);
}


BEGIN_MESSAGE_MAP(Csetparam, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON7, &Csetparam::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON2, &Csetparam::OnBnClickedButton2)
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_BUTTON3, &Csetparam::OnBnClickedButton3)
END_MESSAGE_MAP()


// Csetparam 消息处理程序


BOOL Csetparam::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	init_map();
	try{
	std::ifstream fin(paramfilename);
	fin >> Psetnum >> Pslicenum >> TE >> TR >> STDNum >> Pmask >> ck1
		>> ck2 >> ck3 >> TType >> x00 >> x01 >> x02 >> x10 >>
		x11 >> x12 >> pr >> ro >> hsv>> hlv >> coef >> cbfc >> mttc 
		>> Tmax_th >> VP_th >> Dsetnum >> Dslicenum >> b >> adcmin >>
		adcmax >> adc_th >> VD_th;
	fin.close();
	setconfig();
	}
	catch(...){
		AfxMessageBox(L"读取数据失败");
	}
	UpdateData(false);
	return TRUE;  
}


void Csetparam::OnBnClickedButton7()
{
	
	AfxMessageBox(L"保存成功");
	/*
	UpdateData(true);
	try{
		ofstream out(paramfilename);
		out << Psetnum << " " << Pslicenum << " " << TE<< " " << TR << " " << STDNum << " " << Pmask << " " << ck1
		<< " " << ck2 << " " << ck3 << " " << TType << " " << x00 << " " << x01 << " " << x02 << " " << x10 << " " <<
		x11 << " " << x12<< " " << pr << " " <<ro<< " " << hsv<< " " << hlv << " " << coef << " " << cbfc << " " << mttc 
		<< " " <<Tmax_th << " " <<VP_th << " " << Dsetnum << " " << Dslicenum<< " " << b << " " << adcmin << " " <<
		adcmax << " " << adc_th<< " " << VD_th;
		out.close();
		setconfig();
		AfxMessageBox(L"保存成功");
	}
	catch(...){
		AfxMessageBox(L"保存错误");
	}
	*/
}


void Csetparam::OnBnClickedButton2()
{
	   CFileDialog dlg(TRUE, //TRUE为OPEN对话框，FALSE为SAVE AS对话框
        NULL, 
        NULL,
        OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
        (LPCTSTR)_TEXT("dicom file (*.dcg)"),
        NULL);
	   if(dlg.DoModal() == IDOK){
	   }
}


void Csetparam::OnMouseMove(UINT nFlags, CPoint point)
{
	static CWnd * lastvisit = nullptr;// last visited term to avoid move 
	// lastvisit is used to avoid frequently update explain label
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CWnd * child = this -> GetWindow(GW_CHILD);
	
	RECT standardrect;
	this -> GetWindowRect(&standardrect);
	point.x += standardrect.left;
	point.y += standardrect.top;
	while(child){
		CString str;
		child -> GetWindowTextW(str);
		CStringA tmpstr(str.GetBuffer(0));
		string res(tmpstr.GetBuffer(0));
		tmpstr.ReleaseBuffer();
		str.ReleaseBuffer();
		RECT rect;
		child -> GetWindowRect(&rect);
		for(int i = 0; i < res.size(); ++i){
			if(res[i] >= 'A' && res[i] <= 'Z'){
				res[i] = res[i] +'a' - 'A';
			}
		}

		if(explain.find(res) != explain.end()){
			if(point.x >= rect.left && point.x <= rect.right
				&& point.y <= rect.bottom && point.y >= rect.top){	
					if(explain_label.use_count() == 0){
						explain_label.reset(new CStatic());
						explain_label -> Create(L"hello world", WS_CHILD|WS_VISIBLE|SS_CENTER, CRect(50,80,150,150), this);
						CFont * font = new CFont();
						font -> CreateFont(15,0,0,0,700,0,0,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,
							DEFAULT_QUALITY,DEFAULT_PITCH|FF_DONTCARE,L"Courier New"); 
						explain_label -> SetFont(font, false);
					}
					if(lastvisit != child){
						explain_label -> MoveWindow(rect.right - standardrect.left, 
							rect.bottom - standardrect.top,  100, 50);
						lastvisit = child;
						explain_label -> SetWindowTextW(CommonLib::string_to_lpsctr(explain[res]));
					}
					explain_label -> ShowWindow(true);
					CDialogEx::OnMouseMove(nFlags, point);
					return;
				}
		}
		child = child -> GetWindow(GW_HWNDNEXT);
	}
	if(explain_label.use_count() > 0){
		explain_label -> ShowWindow(false);
	}
	CDialogEx::OnMouseMove(nFlags, point);
}


void Csetparam::OnBnClickedButton3()
{
	update_input();
	setconfig();
	AfxMessageBox(L"参数设置成功, 你可以进行下一步的计算了O(∩_∩)O");
	// TODO: 在此添加控件通知处理程序代码
}
void Csetparam::update_input(){

}
