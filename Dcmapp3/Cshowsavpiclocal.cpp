// Cshowsavpiclocal.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Dcmapp3.h"
#include "Cshowsavpiclocal.h"
#include "afxdialogex.h"
#include "Cnamesavefile.h"
#include "common.h"
// Cshowsavpiclocal �Ի���

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


// Cshowsavpiclocal ��Ϣ�������


void Cshowsavpiclocal::OnBnClicked1()
{
	//edit here to edit new version
	if(!PathIsDirectory(CommonLib::string_to_lpsctr(CommonLib::base_save_data_dir + Cshowperson::id))){
		if(!CreateDirectory(CommonLib::string_to_lpsctr(CommonLib::base_save_data_dir + Cshowperson::id), NULL)){
			AfxMessageBox(L"�����ļ���ʧ��,����ʧ��");
			OnCancel();
			return;
		}
	}
	if(!PathIsDirectory(CommonLib::string_to_lpsctr(CommonLib::base_save_data_dir + Cshowperson::id + "\\") + versionname)){
		if(!CreateDirectory(CommonLib::string_to_lpsctr(CommonLib::base_save_data_dir + Cshowperson::id + "\\") + versionname , NULL)){
			AfxMessageBox(L"�����ļ���ʧ��,����ʧ��");
			OnCancel();
			return;
		}
	}
	else{
		AfxMessageBox(L"����汾�����Ѵ��ڣ�����ʧ��");
		OnCancel();
		return;
	}
	AfxMessageBox(L"���غͷ���˱���ɹ�");
	OnOK(); // to dismiss
}


void Cshowsavpiclocal::OnBnClicked2()
{
	AfxMessageBox(L"����˱���ɹ�");
	CDialogEx::OnOK();
}
