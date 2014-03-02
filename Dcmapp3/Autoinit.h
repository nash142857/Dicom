#pragma once
#include "stdafx.h"
#include <Windows.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <cstring>
#include <utility>
class Autoinit{
public:
	static void init();	
private:
	static const int is_dir = 16;
	static const char * basedirname;
	static const char * lastmodify;
	static void getdir(std::vector <std::pair<std::string, CTime> > &);
	static FILETIME get_last_modify();
	static bool cmp(FILETIME & a, FILETIME & b){
		if(a.dwHighDateTime > b.dwHighDateTime)
			return true;
		else
			if(a.dwHighDateTime == b.dwHighDateTime) return a.dwLowDateTime > b.dwLowDateTime;
			else
				return false;
	}
	static void save_modify();
};
