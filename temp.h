#define TEMP_MED 21000

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"

#define TEMP_READMAX 8

#define TEMP_PHOLDER " ^c#FFFFFF^ᵀᴹᴾ??^c#FFFFFF^"
#define TEMP_LEN (sizeof(TEMP_PHOLDER) - 1)

// " ^c#FFFFFF^TTTMMMPPP??^c#FFFFFF^"
//        |             |
//  01234567890123456789012345
#define TEMP_COLOR_POS 6
#define TEMP_LEVEL_POS 20

#define CLAMP(a, x, b) (a <= x ? (x <= b ? x : b) : a)

FILE *ftemp;

char tempbuf[TEMP_READMAX];

int temp;

void tempupdate() {
	ftemp = fopen("/sys/class/thermal/thermal_zone0/temp", "r");
	fgets(tempbuf, TEMP_READMAX, ftemp);
	fclose(ftemp);
	temp = CLAMP(0, atoi(tempbuf) / 1000, 143);
}

const int templen() {
	return TEMP_LEN;
}

void tempprint(char *dest) {
	doz2(dest + TEMP_LEVEL_POS, temp);

	if(temp >= 22)
		memcpy(dest + TEMP_COLOR_POS, "5555", 4);
	else if(temp >= 21)
		memcpy(dest + TEMP_COLOR_POS, "FF55", 4);
	else
		memcpy(dest + TEMP_COLOR_POS, "FFFF", 4);
}

void tempreprint(char *dest) {
	memcpy(dest, TEMP_PHOLDER, TEMP_LEN);
	tempprint(dest);
}
