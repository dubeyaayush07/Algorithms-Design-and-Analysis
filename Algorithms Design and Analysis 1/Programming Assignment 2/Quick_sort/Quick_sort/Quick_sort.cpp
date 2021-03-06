// Quick_sort.cpp : Defines the quick sort algorithm for sorting an integer array(vector)
//

#include "stdafx.h"

void choose_pivot(vector<int>&ar, int start, int end) {
	int number = rand() % (end - start) + start;
	swap(ar[start], ar[number]);
}

int partition(vector<int>&ar, int start, int end) {
	int p = ar[start];
	int i = start + 1;
	for (int j = start + 1; j < end; ++j) {
		if (ar[j] < p) {
			swap(ar[j], ar[i]);
			++i;
		}
	}
	swap(ar[start], ar[i - 1]);
	return (i - 1);
}


void quick_sort1(vector<int>&ar, int start, int end) {
	// base case
	if (start == end - 1 || start == end) return;

	//makes the choosen pivot the first element in the range
	choose_pivot(ar, start, end);

	//partition the array according to the pivot and return the index of the pivot at the end
	int index = partition(ar, start, end);

	//recurse on the two halves divided by the pivot
	quick_sort1(ar, start, index);
	quick_sort1(ar, index+1, end);

	
}




int main()
{
	srand((unsigned)time(0));
	vector<int> trial{ 8,3,6,9,2 };
	quick_sort1(trial, 0, trial.size());
	for (int i : trial)cout << i << ' ';
	return 0;
}

