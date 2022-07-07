/*******************************************************************/
/*                                                                 */
/*  A1 Part 3: Majority Element starter file                       */
/*                                                                 */
/*  Author1 Name: Soodeh Vanaki		 							   */
/*      - function list: all                                       */
/*                                                                 */
/*                                                                 */
/*******************************************************************/
bool findCandidate(int array[], int& candidate, int sz);
bool majorityElement(const int arr[], int& majority, int sz);

// This function will count the number of occurances in the original array 
// and check that more than 50% of the array is that value then return true
bool majorityElement(const int arr[], int& majority, int sz) {
	bool result = false;		
	int numOfCandidate = 0;
	int can = 0;
	int* arrCopy = new int[sz];

	// Create a duplicate of arr
	for (int i = 0; i < sz; i++) {
		arrCopy[i] = arr[i];			
	}
	// Find the only possible candidate that might be the majority element
	if (findCandidate(arrCopy, can, sz)) {
		for (int i = 0; i < sz; i++) {
			if (can == arr[i])
				numOfCandidate++;
		}
		if (numOfCandidate > sz / 2)
			result = true;
	}
	if (result)
		majority = can;		// Set the majority
	return result;
}

// This is a recursive function which returns true if a candidate is found, false otherwise.
// The function will also pass back the candidate if it is found.
bool findCandidate(int array[], int& candidate, int sz) {
	bool result = false;
	int* temp = new int[sz];
	int temp_counter = 0;
	if (sz != 0) {
		if (sz == 1) {
			candidate = array[0];
			result = true;
		}
		else {
			// Go through each pair of values in the array
			for (int i = 0; i < sz - 1; i += 2) {
				// If the numbers are the same, keep one of them for the next iteration.
				if (array[i] == array[i + 1]) {		
					temp[temp_counter++] = array[i];
				}
				// If the numbers are different, keep neither of them.
				temp[temp_counter] = 0;
			}
			result = findCandidate(temp, candidate, temp_counter);
			
			if (sz % 2 != 0 && !result) {
				candidate = array[sz - 1];
				result = true;
			}
		}
	}
	return result;
}