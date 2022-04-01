#pragma once
#include <array>
#include <vector>

inline short short_pow(short num, short exp) {
	short sum = 1;
	if (exp == 0) { return 1; }

	for (short i = 0; i != exp; i++) {
		sum *= num;
	}
	return sum;
}

inline short b_coefficient(short n, short k) {
	if (k < 0) { return 0; }

	else if (k == 0) { return 1; }

	if (n - k > k) { k = n - k;}

	//I was going to use the
	//std::max function however it requires 
	//that you pass in ints
	//which are 2 bytes as oppose to 1

	if (k >= n) {
		return 1;
	}

	short final_value = n;
	short j = 1;
	for (short i = k + 1; i < n; i++) {
		final_value *= i;
		final_value /= j;
		j++;
	}
	final_value /= j;
	return final_value;
}


inline std::vector <short> rotate_right(std::vector <short> some_vector, short start, short end) {
	short temp = some_vector[end];
	for (short i = end - 1; i != start - 1; i--) {
		some_vector[i + 1] = some_vector[i];
	}
	some_vector[start] = temp;
	return some_vector;
}

inline std::vector <short> rotate_right(std::vector <short> some_vector) {
	some_vector.insert(some_vector.begin(), some_vector.back());
	some_vector.pop_back();

	return some_vector;
}

inline std::vector <short> rotate_left(std::vector <short> some_vector, short start, short end) {
	short temp = some_vector[start];
	for (short i = start; i != end; i++) {
		some_vector[i] = some_vector[i + 1];
	}
	some_vector[end] = temp;
	return some_vector;
}

inline std::vector <short> rotate_left(std::vector <short> some_vector) {
	short temp = some_vector[0];	
	for (short i = 0; i != some_vector.size() - 1; i++) {
		some_vector[i] = some_vector[i + 1];
	}
	some_vector.back() = temp;
	return some_vector;
}





//inline std::array <short, 4> rotate_left_4(std::array <short, 4> some_array) {
//	short temp = some_array[0];
//	for (short i = 0; i != 4; i++) {
//		some_array[i] = some_array[i + 1];
//	}
//	some_array[3] = temp;
//	
//	return some_array;
//}
//
//inline std::array <short, 4> rotate_right_4(std::array <short, 4> some_array) {
//	short temp = some_array[3];
//	for (short i = 4; i != 0; i--) {
//		some_array[i] = some_array[i - 1];
//	}
//	some_array[0] = temp;
//
//	return some_array;
//}