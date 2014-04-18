
// Dcmapp3Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Dcmapp3.h"
#include "Dcmapp3Dlg.h"
#include "afxdialogex.h"
#include "Login.h"
#include "Cshowhelp.h"
#include "Autoinit.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
bool CDcmapp3Dlg::login_state = false;
CString CDcmapp3Dlg::username("");
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
BOOL CAboutDlg::OnInitDialog(){
	return true;
}
CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CDcmapp3Dlg 对话框


CDcmapp3Dlg::CDcmapp3Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDcmapp3Dlg::IDD, pParent)

{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDcmapp3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON4, login_button);
	DDX_Control(pDX, IDC_EDIT9, welcome);
	DDX_Control(pDX, IDC_BUTTON2, onlinebutton);
	DDX_Control(pDX, IDC_BUTTON1, offlinebutton);
	DDX_Control(pDX, IDC_BUTTON9, setbutton);
}

BEGIN_MESSAGE_MAP(CDcmapp3Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON3, &CDcmapp3Dlg::OnBnClickedButton3)
	ON_WM_SIZING()
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CDcmapp3Dlg::OnNMDblclkList1)
	ON_BN_CLICKED(IDC_BUTTON2, &CDcmapp3Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &CDcmapp3Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON9, &CDcmapp3Dlg::OnBnClickedButton9)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON4, &CDcmapp3Dlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CDcmapp3Dlg 消息处理程序

BOOL CDcmapp3Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CFont * font = new CFont();
	font -> CreateFont(30,0,0,0,700,0,0,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,
							DEFAULT_QUALITY,DEFAULT_PITCH|FF_DONTCARE,L"Courier New"); 
	welcome.SetFont(font);
	pon = nullptr;
	poff = nullptr;
	GetClientRect(&m_rect);
	CWnd * pwnd = GetWindow(GW_CHILD);
	MoveWindow(0, 0, 1300, 700);
	while(pwnd){
		change(pwnd, 1300, 700);
		pwnd = pwnd -> GetNextWindow();
	}
	// 将“关于...”菜单项添加到系统菜单中。
	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	// first to show the online window
	if(pon == NULL){
		pon.reset(new Conlinedeal(this));
		pon->Create(IDD_DIALOG2);
		pon->SetParent(this);//设置dialog1为父窗口
		CRect pos;
		GetDlgItem(IDC_STATIC) -> GetWindowRect(pos);
		ScreenToClient(&pos);
		pon -> MoveWindow(pos);
	}
	pon->ShowWindow(SW_SHOW);
	onlinebutton.EnableWindow(false);
	Autoinit::init();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}
void CDcmapp3Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CDcmapp3Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CDcmapp3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
void CDcmapp3Dlg::OnBnClickedButton3()
{
	Cshowhelp helper;
	helper.DoModal();
}




void CDcmapp3Dlg::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	Cshowperson show_person;
	show_person.DoModal();
	*pResult = 0;
}


void CDcmapp3Dlg::OnBnClickedButton2()
{
	if(poff != NULL){
		poff -> ShowWindow(SW_HIDE);
		offlinebutton.EnableWindow(true);
	}
	if(pparam != NULL){
		pparam -> ShowWindow(SW_HIDE);
		setbutton.EnableWindow(true);
	}
	if(pon == NULL){
		pon.reset(new Conlinedeal(this));
		pon->Create(IDD_DIALOG2);
		pon->SetParent(this);//设置dialog1为父窗口
		CRect pos;
		GetDlgItem(IDC_STATIC) -> GetWindowRect(pos);
		ScreenToClient(&pos);
		pon -> MoveWindow(pos);
	}
	pon->ShowWindow(SW_SHOW);
	onlinebutton.EnableWindow(false);
	// TODO: 在此添加控件通知处理程序代码
}


void CDcmapp3Dlg::OnBnClickedButton1()
{
	if(pon != NULL){
		pon -> ShowWindow(SW_HIDE);
		onlinebutton.EnableWindow(true);
	}
	if(pparam != NULL){
		pparam -> ShowWindow(SW_HIDE);
		setbutton.EnableWindow(true);
	}
	if(poff == NULL){
		poff.reset(new Cofflinedeal(this));
		poff -> Create(IDD_DIALOG3);
		poff -> SetParent(this);
		CRect pos;
		GetDlgItem(IDC_STATIC) -> GetWindowRect(pos);
		ScreenToClient(&pos);
		poff -> MoveWindow(pos);
	}
	poff -> ShowWindow(SW_SHOW);
	offlinebutton.EnableWindow(false);
	// TODO: 在此添加控件通知处理程序代码
}


void CDcmapp3Dlg::OnBnClickedButton9()
{
	if(pon != NULL){
		pon -> ShowWindow(SW_HIDE);
		onlinebutton.EnableWindow(true);
	}
	if(poff != NULL){
		poff -> ShowWindow(SW_HIDE);
		offlinebutton.EnableWindow(true);
	}
	if(pparam == NULL){
		pparam.reset(new Csetparam(this));
		pparam -> Create(IDD_DIALOG4);
		pparam -> SetParent(this);
		CRect pos;
		GetDlgItem(IDC_STATIC) -> GetWindowRect(pos);
		ScreenToClient(&pos);
		pparam -> MoveWindow(pos);
	}
	pparam -> ShowWindow(SW_SHOW);
	if(login_state)
		pparam -> GetDlgItem(IDC_BUTTON7) -> ShowWindow(SW_SHOW);
	else
		pparam -> GetDlgItem(IDC_BUTTON7) -> ShowWindow(SW_HIDE);
	setbutton.EnableWindow(false);
}


void CDcmapp3Dlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	
	// TODO: 在此处添加消息处理程序代码
}


void CDcmapp3Dlg::OnBnClickedButton4()
{
	if(login_state){
		login_state = false;
		AfxMessageBox(L"注销成功");
		login_button.SetWindowTextW(L"登录");
		welcome.SetWindowTextW(L"");
		if(pparam != nullptr)
		pparam -> GetDlgItem(IDC_BUTTON7) -> ShowWindow(SW_HIDE);
		return;
	}
	else{
		CLogin login = new CLogin(); 
		login.DoModal();
		if(login_state){
			login_button.SetWindowTextW(L"注销");
			welcome.SetWindowTextW(L"你好 , "+username);	
			if(pparam != nullptr)
				pparam -> GetDlgItem(IDC_BUTTON7) -> ShowWindow(SW_SHOW);
		}
	}
	// TODO: 在此添加控件通知处理程序代码
}
