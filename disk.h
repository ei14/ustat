#include <sys/statvfs.h>
#include <string.h>

#include "util.h"

#define PHOLDER1 " ^c#FFFFFF^ᴴᴰᴰ"
#define LEN1 (sizeof(PHOLDER1) - 1)
#define PHOLDER2 "^c#FFFFFF^"
#define LEN2 (sizeof(PHOLDER2) - 1)

// " ^c#FFFFFF^HHHDDDDDD?^c#FFFFFF^ "
//        |             |
//  01234567890123456789012345
#define DISK_COLOR_POS 6
#define DISK_AVAIL_POS 20

int space;
int numlen;

void diskupdate() {
	struct statvfs fs;
	statvfs("/", &fs);
	space = fs.f_frsize * fs.f_bavail / 0x40000000;
	numlen = dozlen(space);
}

const int disklen() {
	return LEN1 + numlen + LEN2;
}

void diskprint(char *dest) {
	if(space < 0x20)
		memcpy(dest + DISK_COLOR_POS, "5555", 4);
	else if(space < 0x40)
		memcpy(dest + DISK_COLOR_POS, "FF55", 4);
	else
		memcpy(dest + DISK_COLOR_POS, "FFFF", 4);

	doz(dest + DISK_AVAIL_POS, space);
}

void diskreprint(char *dest) {
	memcpy(dest, PHOLDER1, LEN1);
	memcpy(dest + LEN1 + numlen, PHOLDER2, LEN2);
	diskprint(dest);
}
