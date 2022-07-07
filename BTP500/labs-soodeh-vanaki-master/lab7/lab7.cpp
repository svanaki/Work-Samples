/******************************/
/* Soodeh Vanaki **************/
/* SID: 075782128 *************/
/* Email: svanaki@myseneca.ca */
/******************************/

#include <cstdlib>
#include <iostream>
#include <fstream>


using namespace std;



void heapify(int arr[], int size, int idx) {
	int min = idx;
	int l = 2 * idx + 1;
	int r = 2 * idx + 2;
	if (l < size && arr[l] < arr[min]) {
		min = l;
	}
	if (r < size && arr[r] < arr[min]) {
		min = r;
	}
	if (min != idx) {
		swap(arr[idx], arr[min]);
		heapify(arr, size, min);
	}
}

/*Only modify this function*/
void insertionSortModified(int arr[], int left, int right) {
	
	int size = right - left + 1;
	for (int i = (size / 2) - 1; i >= 0; i--) {
		heapify(arr, size, i);
	}

	int curr;
	int i, j;
	for (i = (size / 2) - 1; i <= right; i++) {
		curr = arr[i];
		for (j = i; j > 0 && arr[j - 1] > curr; j--) {
			arr[j] = arr[j - 1];
		}
		arr[j] = curr;
	}
}


int partition(int array[], int left, int right) {

	int location = left + rand() % (right - left + 1);
	int pivot = array[location];
	array[location] = array[right];
	array[right] = pivot;//fix this.

	int i = left - 1;
	for (int j = left; j < right; j++) {
		if (array[j] <= pivot) {
			i = i + 1;
			int tmp = array[i];
			array[i] = array[j];
			array[j] = tmp;
		}
	}
	int tmp = array[i + 1];
	array[i + 1] = array[right];
	array[right] = tmp;
	return i + 1;
}


void quickSortModified(int arr[], int left, int right, int threshold) {

	if (right - left <= threshold) {
		insertionSortModified(arr, left, right);
	}
	else {
		int i = partition(arr, left, right);
		quickSortModified(arr, left, i - 1, threshold);
		quickSortModified(arr, i + 1, right, threshold);
	}
}

void quickSortModified(int arr[], int size, int threshold) {
	quickSortModified(arr, 0, size - 1, threshold);
}


/*performs the insertion sort algorithm on array from index
left to index right inclusive.  You don't need to change this function*/
void insertionSortStandard(int arr[], int left, int right) {
	int curr;
	int i, j;
	for (i = left + 1; i <= right; i++) {
		curr = arr[i];
		for (j = i; j > 0 && arr[j - 1] > curr; j--) {
			arr[j] = arr[j - 1];
		}
		arr[j] = curr;
	}
}

void quickSortStandard(int arr[], int left, int right, int threshold) {
	if (right - left <= threshold) {
		insertionSortStandard(arr, left, right);
	}
	else {
		int i = partition(arr, left, right);
		quickSortStandard(arr, left, i - 1, threshold);
		quickSortStandard(arr, i + 1, right, threshold);
	}
}
void quickSortStandard(int arr[], int size, int threshold) {
	quickSortStandard(arr, 0, size - 1, threshold);
}
