#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"

#define CPU_PHOLDER " ^c#FFFFFF^ᵂᴿᴷ..^c#FFFFFF^"
#define CPU_LEN (sizeof(CPU_PHOLDER) - 1)

// " ^c#FFFFFF^WWWRRRKKK??^c#FFFFFF^"
//        |             |
//  0123456789012345678901234567
#define CPU_COLOR_POS 6
#define CPU_USAGE_POS 20

#define CAP(num, cap) (num <= cap ? num : cap)

long *pre; // Previous CPU numbers
long *cur; // Current CPU numbers
long *tmp; // Used to switch the two

long total; // Total CPU cycles elapsed during this interval
long work; // Number of said cycles spent doing work

int usage; // Quotient

void cpufetch() {
	FILE *fstat = fopen("/proc/stat", "r");
	fscanf(fstat, "%*s %ld %ld %ld %ld %ld %ld %ld",
		cur, cur+1, cur+2, cur+3, cur+4, cur+5, cur+6);
	fclose(fstat);
}

void cpuinit() {
	pre = malloc(7 * sizeof(long));
	cur = malloc(7 * sizeof(long));
	cpufetch();
}

void cpuupdate() {
	tmp = pre;
	pre = cur;
	cur = tmp;
	cpufetch();
}

const int cpulen() {
	return CPU_LEN;
}

void cpuprint(char *dest) {
	work = (cur[0] + cur[1] + cur[2] + cur[5] + cur[6])
		- (pre[0] + pre[1] + pre[2] + pre[5] + pre[6]);
	total = work + (cur[3] + cur[4]) - (pre[3] + pre[4]);

	if(total == 0)
		return;

	usage = CAP(144 * work / total, 143);

	doz2(dest + CPU_USAGE_POS, usage);

	if(usage >= 108)
		memcpy(dest + CPU_COLOR_POS, "5555", 4);
	else if(usage >= 72)
		memcpy(dest + CPU_COLOR_POS, "FF55", 4);
	else
		memcpy(dest + CPU_COLOR_POS, "FFFF", 4);
}

void cpureprint(char *dest) {
	memcpy(dest, CPU_PHOLDER, CPU_LEN);
	cpuprint(dest);
}
