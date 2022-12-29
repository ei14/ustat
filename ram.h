#include <stdio.h>
#include <string.h>

#include "util.h"

#define RAM_PHOLDER " ^c#FFFFFF^ᴿᴬᴹ..^c#FFFFFF^"
#define RAM_LEN (sizeof(RAM_PHOLDER) - 1)

// " ^c#FFFFFF^RRRAAAMMM..^c#FFFFFF^"
//        |             |
//  0123456789012345678901234567
#define RAM_COLOR_POS 6
#define RAM_AVAIL_POS 20

#define RAM_READMAX 64

FILE *fp;
char rambuf[RAM_READMAX];
int ram_avail;
void ramupdate() {
	fp = fopen("/proc/meminfo", "r");
	fgets(rambuf, RAM_READMAX, fp); // Ignore first 2 lines
	fgets(rambuf, RAM_READMAX, fp); // Ignore first 2 lines
	fscanf(fp, "%*s %d", &ram_avail);
	fclose(fp);
	ram_avail >>= 20;
}

const int ramlen() {
	return RAM_LEN;
}

void ramprint(char *dest) {
	doz2(dest + RAM_AVAIL_POS, ram_avail);

	if(ram_avail < 4)
		memcpy(dest + RAM_COLOR_POS, "5555", 4);
	else if(ram_avail < 8)
		memcpy(dest + RAM_COLOR_POS, "FF55", 4);
	else
		memcpy(dest + RAM_COLOR_POS, "FFFF", 4);
}

void ramreprint(char *dest) {
	memcpy(dest, RAM_PHOLDER, RAM_LEN);
	ramprint(dest);
}
