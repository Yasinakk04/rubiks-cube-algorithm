#pragma once

short short_pow(short num, short exp) {
	short sum = 1;
	for (short i = 0; i != exp; i++) {
		sum = sum * num;
	}
	return sum;
}