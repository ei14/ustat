#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"

#define BAT_READMAX 16

#define BAT_PHOLDER " ^c#FFFFFF^ᴮᴬᵀ??^c#FFFFFF^"
#define BAT_LEN (sizeof(BAT_PHOLDER) - 1)

// " ^c#FFFFFF^BBBAAATTT??^c#FFFFFF^"
//        |    |        |
//  0123456789012345678901234567
#define BAT_COLOR_POS 6
#define BAT_STATE_POS 11
#define BAT_LEVEL_POS 20

#define CAP(num, cap) (num <= cap ? num : cap)

FILE *fenergy;
FILE *fstatus;

char batbuf[BAT_READMAX];

int capacity;
int level;
char state;

void batinit() {
	FILE *fcapacity = fopen("/sys/class/power_supply/BAT0/energy_full", "r");
	fgets(batbuf, BAT_READMAX, fcapacity);
	fclose(fcapacity);
	capacity = atoi(batbuf);
}

void batupdate() {
	fenergy = fopen("/sys/class/power_supply/BAT0/energy_now", "r");
	fgets(batbuf, BAT_READMAX, fenergy);
	fclose(fenergy);
	level = CAP(143L * atoi(batbuf) / capacity, 143);

	fstatus = fopen("/sys/class/power_supply/BAT0/status", "r");
	fgets(batbuf, 2, fstatus);
	fclose(fstatus);
	state = batbuf[0];
}

const int batlen() {
	return BAT_LEN;
}

void batprint(char *dest) {
	doz2(dest + BAT_LEVEL_POS, level);

	switch(state) {
		case 'C':
		case 'F':
		memcpy(dest + BAT_STATE_POS, "ᴾᵂᴿ", 9);
		memcpy(dest + BAT_COLOR_POS, "FFFF", 4);
		break;

		case 'D':
		memcpy(dest + BAT_STATE_POS, "ᴮᴬᵀ", 9);
		if(level < 36)
			memcpy(dest + BAT_COLOR_POS, "5555", 4);
		else if(level < 72)
			memcpy(dest + BAT_COLOR_POS, "FF55", 4);
		else
			memcpy(dest + BAT_COLOR_POS, "FFFF", 4);
		break;
	}
}

void batreprint(char *dest) {
	memcpy(dest, BAT_PHOLDER, BAT_LEN);
	batprint(dest);
}
