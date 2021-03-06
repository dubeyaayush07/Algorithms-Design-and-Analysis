// 2sum.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


long long buckets = 373587883;


int main()
{
	Hash_table group(buckets);
	vector<long long>set;

	ifstream ist{ "input.txt" };
	if (!ist) error("Cannot open file");

	long long x;
	while (ist >> x) {
		if (!group.look_up(x)) {
			group.insert(x);
			set.push_back(x);
		}
	}


	int num = 0;
	for (long long t = -10000; t <= 10000; ++t) {
		for (int i = 0; i < set.size();++i) {
			long long y = t - set[i];
			if (y != set[i] && group.look_up(y)) {
				++num;
				break;
			}
			if(i==0)cout << "t:  " << t << endl;
		}
	}
	cout <<"num:  "<< num << endl;
    return 0;
}

