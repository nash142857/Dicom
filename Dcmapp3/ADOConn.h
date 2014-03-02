#pragma once
#include <afxdb.h>
#include <string>
#include <vector>
#include <memory>
#include "plist.h"
#include "Patient_information.h"
using namespace std;

class ADOConn
{
public:
	ADOConn(void);
	~ADOConn(void);
	Patient_information search(const string& pId, bool flag) const;
	void addPatient(const string& pId, const string& pName, const string& pDir, const int pwicount, const int dwicount, const CTime &);
	static shared_ptr<ADOConn> sharedSingleton();
	vector<Patient_information> search_both(const string & id, const string & name);
	bool exist(const string &, bool flag) const;
	vector <Patient_information> search_range(const string & id,  bool flag = false);
	shared_ptr <Cplist> getlist(){
		return m_rs;
	}
private:
	CDatabase m_db;
	shared_ptr <Cplist> m_rs;
};


