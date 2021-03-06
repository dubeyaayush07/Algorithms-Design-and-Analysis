// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include<iostream>
#include<iomanip>
#include<fstream>
#include<sstream>
#include<cmath>
#include<cstdlib>
#include<string>
#include<list>
#include <forward_list>
#include<vector>
#include<unordered_map>
#include<algorithm>
#include <array>
#include <regex>
#include<random>
#include<stdexcept>
#include<queue>
#include<unordered_map>
#include<unordered_set>
#include<list>


using namespace std;

inline void error(const string& s)
{
	throw runtime_error(s);
}





class Hash_table {
public:

	// constructors
	Hash_table(long long buck): buckets{buck} {
		data.resize(buckets);
	}

	// modifying functions
	void insert(long long key);

	// non modifying functions
	bool look_up(long long key) const;
	long long hash(long long num) const {
		return abs(num)% buckets;
	}

private:
	long long buckets;
	vector<list<long long>*> data;
};


// TODO: reference additional headers your program requires here
