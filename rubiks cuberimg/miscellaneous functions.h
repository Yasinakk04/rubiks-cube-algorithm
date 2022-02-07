#pragma once
#include <algorithm>


short short_pow(short num, short exp) {
	short sum = 1;
	for (short i = 0; i != exp; i++) {
		sum = sum * num;
	}
	return sum;
}

short b_coefficient(short n, short k) {
	short k = std::max(k, n - k);
	short j = 1
	for (short i = k + 1; i < n; i++; j++) {
		n = n * i;
		n = n / j;
	}



}