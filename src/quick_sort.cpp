//============================================================================
// Name        : quick_sort.cpp
// Author      : totrit
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <assert.h>
#include <stdlib.h>
#include <time.h>

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

void swap(int* array, int pos1, int pos2) {
	assert(pos1 >= 0 && pos2 >= 0);
	int tmp = array[pos1];
	array[pos1] = array[pos2];
	array[pos2] = tmp;
}

void quick_sort(int array[], int left, int right) {
	cout << "sorting " << left << ":" << right << endl;
	assert(left <= right);
	assert(left >= 0);
	assert(right >= 0);
	if (left == right) {
		return;
	}
	// 1. pick a pivot
	int sentinel = left; //TODO
	cout << "sentinel: " << array[sentinel] << endl;

	// 2. move the value of the pivot to the end
	swap(array, sentinel, right);
	int little_seacher = right - 1;
	int pivot = array[right];
	int cursor = left;

	// 3. left-to-right encounter the larger value, meanwhile right-to-left search the smaller value, swap them
	for (; cursor <= little_seacher; cursor++) {
		if (array[cursor] <= pivot) {
			// Those who are smaller than the pivot will not be moved to the tail of the array
			cout << "value at cursor=" << cursor
					<< " is smaller than pivot;value=" << array[cursor] << endl;
			continue;
		}
		// The left-to-right cursor should not proceed the right-to-left smaller-number-seacher
		for (; little_seacher >= cursor; little_seacher--) {
			// Have a smaller number to swap
			if (array[little_seacher] <= pivot) {
				cout << "swap big&small: " << cursor << ", "
						<< little_seacher << "where values are " << array[cursor] << ", " << array[little_seacher]<< endl;
				swap(array, cursor, little_seacher);
				break;
			}
		}
		if (little_seacher <= cursor) {
			cout << "little seacher is even beneth cursor, " << little_seacher << "&" << cursor << endl;
			break;
		}
	}

	// Make sure that the value at cursor should be larger than the pivot value(who was swaped to the end of the array)
	if (array[cursor] > array[right]) {
		cout << "at the end of recurcive, swap " << cursor << ", " << right << "whose values are " << array[cursor] << ", " << array[right] << endl;
		swap(array, cursor, right);
	}

	if (cursor > left) {
		quick_sort(array, left, cursor - 1);
	}
	if (right > cursor) {
		quick_sort(array, cursor + 1, right);
	}
}

int main() {
	const int array_size = 100000;
	int* array = new int[100000];
	srand(time(NULL));
	for (int i = 0; i < array_size; i++) {
		array[i] = rand() % 1000000;
	}

	// stl sort
	vector<int> v(array, array + array_size);
	sort(v.begin(), v.end());

	// quick sort
	quick_sort(array, 0, array_size - 1);

	// print it out
	for (int i = 0; i < array_size; i++) {
		cout << array[i] << ", ";
	}
	cout << endl;

	// check
	for (int i = 0; i < array_size; i++) {
		cout << v[i] << "?=" << array[i] << " on " << i << endl;
		assert(v[i] == array[i]);
	}
	cout << "OK!" << endl;
	return 0;
}
