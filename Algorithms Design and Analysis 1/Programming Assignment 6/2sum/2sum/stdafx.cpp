
#include "stdafx.h"


bool Hash_table::look_up(long long key) const {
	// get the bucket number where to look for
	long long k = hash(key);
	auto bucket = data[k];

	// when the bucket is not empty
	if (bucket) {
		auto result = find(bucket->begin(), bucket->end(), key);

		if (result == bucket->end())return false;
		return true;
	}
	return false;
	
}

void Hash_table::insert(long long key) {
	long long k = hash(key);
	auto& bucket = data[k];
	//when the bucket is empty create a new list element
	if (!bucket) {
		bucket = new list<long long>;// create a new list
		bucket->push_front(key);
		return;
	}
	// if the bucket is not empty just insert at the front
	bucket->push_front(key);
}