#include <time.h>
#include <string.h>

#include "util.h"

#define DATE_PHOLDER " ?-?? ? "
#define DATE_LEN (sizeof(DATE_PHOLDER) - 1)

#define TIME_PHOLDER "? ?:??"
#define TIME_LEN (sizeof(TIME_PHOLDER) - 1)

#define SECS_PHOLDER " ?? "
#define SECS_LEN (sizeof(SECS_PHOLDER) - 1)

// " 0-31 S "
//   | |  |
//  01234567890123
#define WDY_POS 6
#define MON_POS 1
#define DAY_POS 3

// "P E:59"
//  | | |
//  01234567
#define AMPM_POS 0
#define HOUR_POS 2
#define MIN_POS 4

// " 4E "
//   |
//  0123
#define SECS_POS 1


const int datelen() { return DATE_LEN; }
const int timelen() { return TIME_LEN; }
const int secslen() { return SECS_LEN; }


struct tm *now;
time_t t;
void timeupdate() {
	t = time(NULL);
	now = localtime(&t);
}

void dateprint(char *dest) {
	//dest[WDY_POS] = doz1(now->tm_wday);
	dest[WDY_POS] = "UMTWRFS"[now->tm_wday];
	dest[MON_POS] = doz1(now->tm_mon + 1);
	dec2(dest + DAY_POS, now->tm_mday);
}

void timeprint(char *dest) {
	dest[AMPM_POS] = "AP"[now->tm_hour / 12];
	dest[HOUR_POS] = doz1(now->tm_hour % 12);
	dec2(dest + MIN_POS, now->tm_min);
}

void secsprint(char *dest) {
	doz2(dest + SECS_POS, now->tm_sec);
}


void datereprint(char *dest) {
	memcpy(dest, DATE_PHOLDER, DATE_LEN);
	dateprint(dest);
}
void timereprint(char *dest) {
	memcpy(dest, TIME_PHOLDER, TIME_LEN);
	timeprint(dest);
}
void secsreprint(char *dest) {
	memcpy(dest, SECS_PHOLDER, SECS_LEN);
	secsprint(dest);
}
