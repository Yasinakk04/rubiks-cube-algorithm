#pragma once
#include <algorithm>


short short_pow(short num, short exp) {
	short sum = 1;
	for (short i = 0; i != exp; i++) {
		sum *= num;
	}
	return sum;
}

short b_coefficient(short n, short k) {
	if (n - k > k) { k = n-k;}

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