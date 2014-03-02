// plist.h : Cplist 类的实现



// Cplist 实现

// 代码生成在 2013年10月24日, 17:50

#include "stdafx.h"
#include "plist.h"
IMPLEMENT_DYNAMIC(Cplist, CRecordset)

Cplist::Cplist(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_pid = "";
	m_pname = "";
	m_pdir = "";
	m_pwicount = 0;
	m_dwicount = 0;
	m_modifytime;
	m_nFields = 6;
	m_nDefaultType = dynaset;
}
// 此连接字符串中可能包含明文密码和/或其他重要
// 信息。请在查看完此连接字符串并找到所有与安全
// 有关的问题后移除 #error。可能需要将此密码存
// 储为其他格式或使用其他的用户身份验证。
CString Cplist::GetDefaultConnect()
{
	return _T("DSN=attacker;Description=attacker;UID=sa;PWD=kobe31413;APP=Microsoft\x00ae Visual Studio\x00ae 2012;WSID=ATTACKER-PC;DATABASE=attacker;QuotedId=No;");
}

CString Cplist::GetDefaultSQL()
{
	return _T("[dbo].[plist]");
}

void Cplist::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() 和 RFX_Int() 这类宏依赖的是
// 成员变量的类型，而不是数据库字段的类型。
// ODBC 尝试自动将列值转换为所请求的类型
	RFX_Text(pFX, _T("[pid]"), m_pid);
	RFX_Text(pFX, _T("[pname]"), m_pname);
	RFX_Text(pFX, _T("[pdir]"), m_pdir);
	RFX_Long(pFX, _T("[pwicount]"), m_pwicount);
	RFX_Long(pFX, _T("[dwicount]"), m_dwicount);
	RFX_Date(pFX, _T("[modifytime]"), m_modifytime);

}
/////////////////////////////////////////////////////////////////////////////
// Cplist 诊断

#ifdef _DEBUG
void Cplist::AssertValid() const
{
	CRecordset::AssertValid();
}

void Cplist::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


