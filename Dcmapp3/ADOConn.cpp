#include "StdAfx.h"
#include "ADOConn.h"
#include "plist.h"
#include "DCMConst.h"
#include "common.h"
ADOConn::ADOConn(void):m_rs(new Cplist(&m_db)){
	m_rs -> Open(CRecordset::dynaset, _T( "Select * from plist" ));
}

ADOConn::~ADOConn(void){
	m_rs->Close();//关闭记录
	m_db.Close();
}

shared_ptr<ADOConn> ADOConn::sharedSingleton(){
	static shared_ptr<ADOConn> ptr;
	if (ptr.get() == NULL){
		ptr = shared_ptr<ADOConn>(new ADOConn);
	}
	return ptr;
}
vector<Patient_information> ADOConn::search_both(const string & id, const string & name){
	const char * _id = id.c_str();
	const char * _name = name.c_str();
	m_rs->m_strFilter.Format(_T("pid like '%s%%' and pname like '%s%%'"),CStringW(_id), CStringW(_name));
	try{
		if (m_rs->IsOpen()){
			m_rs->Requery();
		}
		else{
			m_rs->Open();
		}
	}
	catch (CDBException *e)
	{
		AfxMessageBox(e->m_strError);
	}
	vector <Patient_information> res;
	m_rs -> MoveFirst();
	while(!m_rs -> IsEOF()){
		res.push_back(Patient_information(m_rs -> m_modifytime, m_rs -> m_pid, m_rs -> m_pname, m_rs -> m_pdir, m_rs -> m_pwicount, m_rs -> m_dwicount));
		m_rs -> MoveNext();
	}
	return res;
}
Patient_information  ADOConn::search(const string& search, bool flag) const{
	const char *ch = search.c_str();
	if(!flag)
		m_rs->m_strFilter.Format(_T("pid = '%s'"),CStringW(ch));
	else
		m_rs->m_strFilter.Format(_T("pname = '%s'"),CStringW(ch));
	try{
		if (m_rs->IsOpen()){
			m_rs->Requery();
		}
		else{
			m_rs->Open();
		}
	}
	catch (CDBException *e)
	{
		AfxMessageBox(e->m_strError);
	}
	return Patient_information(m_rs -> m_modifytime, m_rs -> m_pid, m_rs -> m_pname, m_rs -> m_pdir, m_rs -> m_pwicount, m_rs -> m_dwicount);
}
bool ADOConn::exist(const string & search, bool flag) const{
	const char *ch = search.c_str();
	if(!flag)
		m_rs->m_strFilter.Format(_T("pid = '%s'"),CStringW(ch));
	else
		m_rs->m_strFilter.Format(_T("pname = '%s'"),CStringW(ch));
	try{
		if (m_rs->IsOpen()){
			m_rs->Requery();
		}
		else{
			m_rs->Open();
		}
		if(flag){
			if(m_rs -> m_pid == search.c_str())
				return true;
			else
				return false;
		}
		else{
			if(m_rs -> m_pname == search.c_str())
				return true;
			else
				return false;
		}
	}
	catch (CDBException *e)
	{
		AfxMessageBox(e->m_strError);
		return false;
	}
}
vector <Patient_information> ADOConn::search_range(const string & id, bool flag){
	if(!flag)
		m_rs->m_strFilter.Format(_T("pid like '%s%%'"),CStringW(id.c_str()));
	else
		m_rs->m_strFilter.Format(_T("pname like '%s%%'"),CStringW(id.c_str()));
	try{
		if (m_rs->IsOpen()){
			m_rs->Requery();
		}
		else{
			m_rs->Open();
		}
	}
	catch (CDBException *e)
	{
		AfxMessageBox(e->m_strError);
	}
	vector <Patient_information> res;
	m_rs -> MoveFirst();
	while(!m_rs -> IsEOF()){
		res.push_back(Patient_information(m_rs -> m_modifytime, m_rs -> m_pid, m_rs -> m_pname, m_rs -> m_pdir, m_rs -> m_pwicount, m_rs -> m_dwicount));
		m_rs -> MoveNext();
	}
	return res;
}
void ADOConn::addPatient(const string& pId, const string& pName, const string& pDir, const int pwicount, const int dwicount, const CTime & ctime){//添加病人
	try{
		if(!exist(pId, true)){
			m_rs -> AddNew();
		}
		else{
			m_rs -> Edit();
		}
		m_rs -> m_pid = pId.c_str();
		m_rs->m_pname = pName.c_str();
		m_rs->m_pdir = pDir.c_str();
		m_rs -> m_pwicount = pwicount;
		m_rs -> m_dwicount = dwicount;
		m_rs -> m_modifytime = ctime;
		m_rs->Update();		
	}
	catch(CException *e){
		TCHAR szError[100];
		e -> GetErrorMessage(szError,100);
		AfxMessageBox(szError);
	}
}