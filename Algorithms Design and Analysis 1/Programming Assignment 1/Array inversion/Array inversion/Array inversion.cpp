// Array inversion.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

class Inv {
public:
	Inv(vector<int>x, double y) :
		sorted{ x }, count{ y } {}
	double count;
	vector<int>sorted;
};

Inv merge_split(Inv&left, Inv&right) {
	vector<int> result(left.sorted.size() + right.sorted.size());
	int i = 0, j = 0;
	double count = 0;
	for (int k = 0; k < result.size(); ++k) {
		if (i != left.sorted.size() && j != right.sorted.size()) {
			if (left.sorted[i] > right.sorted[j]) {
				result[k] = right.sorted[j];
				count += left.sorted.size() - i ;
				++j;
			}
			else {
				result[k] = left.sorted[i];
				++i;
			}
		}
		else if (j == right.sorted.size()) {
			result[k] = left.sorted[i];
			++i;
		}
		else if (i == left.sorted.size()) {
			result[k] = right.sorted[j];
			++j;
		}
	}
	return Inv{result, count};
}

Inv sort_count(Inv& ar,int start,int end) {
	if (start + 1 == end) {
		return Inv{ vector<int>{ar.sorted[start]},0 };
	}
	else {
		int q = (start + end) / 2;
		Inv left = sort_count(ar, start, q);
		Inv right = sort_count(ar, q, end);
		Inv split = merge_split(left, right);
		return Inv{split.sorted, split.count + left.count+ right.count};
	}

}

int main()
{
	ifstream ist{ "input.txt" };
	vector<int> trial(100000);
	for (int i = 0; i < trial.size(); ++i) {
		ist >> trial[i];
	}
	Inv t{ trial, 0 };
	cout<<fixed << sort_count(t,0,trial.size()).count << ' ';
    return 0;
}

