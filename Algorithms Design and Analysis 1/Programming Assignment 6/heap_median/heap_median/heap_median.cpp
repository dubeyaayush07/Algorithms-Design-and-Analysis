// heap_median.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int main()
try
{
	priority_queue<int>h_low;
	priority_queue<int, std::vector<int>, std::greater<int> > h_high;
	vector<int>medians;


	ifstream ist{ "input.txt" };
	if (!ist)error("Cannot open file");

	// insert the first two elements and compute median
	int x1, x2, x;
	ist >> x1 >> x2;
	h_low.push(min(x1, x2));
	h_high.push(max(x1, x2));
	medians.push_back(x1);
	medians.push_back(h_low.top());

	//compute the rest
	while (ist >> x) {
		//figure out where to insert new number
		if (h_low.top() >= x)h_low.push(x);
		else h_high.push(x);

		// balance the two heaps if they are out of balance
		if ((h_low.size() - h_high.size()) == 2) {
			h_high.push(h_low.top());
			h_low.pop();
		}
		else if ((h_high.size() - h_low.size()) == 2) {
			h_low.push(h_high.top());
			h_high.pop();
		}

		// find out the current median and add it to the vector
		int size = h_high.size() + h_low.size();

		if (size % 2 == 0) medians.push_back(h_low.top());
		else {
			if(h_high.size() > h_low.size()) medians.push_back(h_high.top());
			else if (h_high.size() < h_low.size()) medians.push_back(h_low.top());
		}
	}

	int sum = 0;
	for (int median : medians) {
		sum += median;
	}

	cout << sum << endl;
	getchar();



    return 0;
}
catch (exception &e) {
	cerr << e.what() << endl;
	return 1;
}

