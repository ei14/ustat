#include "util.h"

#define DIGITS "0123456789XE"
char doz1(int num) {
	return DIGITS[num % 12];
}
void doz2(char *dest, int num) {
	dest[0] = DIGITS[num / 12 % 12];
	dest[1] = DIGITS[num % 12];
}
int dozlen(int num) {
	if(num == 0)
		return 1;

	int fuse = num; // Fuse: burns in time proportional to its length
	int len = 0;
	while(fuse != 0) {
		fuse /= 12;
		len++;
	}

	return len;
}
int doz(char *dest, int num) {
	if(num == 0)
		dest[0] = '0';
	
	int len = dozlen(num);

//	if(len > maxlen)
//		return 0;

	for(int pos = len-1; pos >= 0; pos--) {
		dest[pos] = DIGITS[num % 12];
		num /= 12;
	}

	return 1;
}

char dec1(int num) {
	return DIGITS[num % 10];
}
void dec2(char *dest, int num) {
	dest[0] = DIGITS[num / 10 % 10];
	dest[1] = DIGITS[num % 10];
}

void nop() {}
int id(int x) { return x; }
