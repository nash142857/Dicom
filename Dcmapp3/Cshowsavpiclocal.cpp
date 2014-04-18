// Cshowsavpiclocal.cpp : 实现文件
//

#include "stdafx.h"
#include "Dcmapp3.h"
#include "Cshowsavpiclocal.h"
#include "afxdialogex.h"
#include "Cnamesavefile.h"
#include "common.h"
// Cshowsavpiclocal 对话框

IMPLEMENT_DYNAMIC(Cshowsavpiclocal, CDialogEx)

Cshowsavpiclocal::Cshowsavpiclocal(CWnd* pParent /*=NULL*/)
	: CDialogEx(Cshowsavpiclocal::IDD, pParent)
{

}

Cshowsavpiclocal::~Cshowsavpiclocal()
{
}

void Cshowsavpiclocal::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Cshowsavpiclocal, CDialogEx)
	ON_BN_CLICKED(ID_SAVE, &Cshowsavpiclocal::OnBnClicked1)
	ON_BN_CLICKED(ID_NOT_SAVE, &Cshowsavpiclocal::OnBnClicked2)
END_MESSAGE_MAP()


// Cshowsavpiclocal 消息处理程序


void Cshowsavpiclocal::OnBnClicked1()
{
	//edit here to edit new version
	if(!PathIsDirectory(CommonLib::string_to_lpsctr(CommonLib::base_save_data_dir + Cshowperson::id))){
		if(!CreateDirectory(CommonLib::string_to_lpsctr(CommonLib::base_save_data_dir + Cshowperson::id), NULL)){
			AfxMessageBox(L"创建文件夹失败,保存失败");
			OnCancel();
			return;
		}
	}
	if(!PathIsDirectory(CommonLib::string_to_lpsctr(CommonLib::base_save_data_dir + Cshowperson::id + "\\") + versionname)){
		if(!CreateDirectory(CommonLib::string_to_lpsctr(CommonLib::base_save_data_dir + Cshowperson::id + "\\") + versionname , NULL)){
			AfxMessageBox(L"创建文件夹失败,保存失败");
			OnCancel();
			return;
		}
	}
	else{
		AfxMessageBox(L"输入版本名称已存在，保存失败");
		OnCancel();
		return;
	}
	AfxMessageBox(L"本地和服务端保存成功");
	OnOK(); // to dismiss
}


void Cshowsavpiclocal::OnBnClicked2()
{
	AfxMessageBox(L"服务端保存成功");
	CDialogEx::OnOK();
}
