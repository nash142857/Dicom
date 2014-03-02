#pragma once
#include "stdafx.h"
#include <wchar.h>
struct Patient_information{
	CStringW id;
	CStringW name;
	CStringW dir;
	CTime modifytime;
	int dwicount;
	int pwicount;
	Patient_information(CTime _modifytime, CStringW _id = L"", CStringW _name= L"", CStringW _dir= L"", int _pwicount = 0, int _dwicount = 0)
		:id(_id), name(_name),dir(_dir), pwicount(_pwicount), dwicount(_dwicount), modifytime(_modifytime){
	}
};

