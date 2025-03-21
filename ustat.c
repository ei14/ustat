#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <X11/Xlib.h>
#include <signal.h>

#include "config.h"

#define LEN(arr) (sizeof(arr) / sizeof(arr[0]))

Display *dpy;

char bartext[BARLEN];

void resizeAndPrint(int start) {
	int diff = COMPS[start].len() - COMPS[start].prevlen;

	if(diff == 0) { // No need to resize
		COMPS[start].print(bartext + COMPS[start].pos);
		return;
	}

	COMPS[start].prevlen += diff;
	COMPS[start].reprint(bartext + COMPS[start].pos);
	int i;
	for(i = start + 1; i < LEN(COMPS); i++) {
		COMPS[i].pos += diff;
		COMPS[i].reprint(bartext + COMPS[i].pos);
	}
	bartext[COMPS[i-1].pos + COMPS[i-1].prevlen] = '\0';
}

void handler_busy(int signum) {
	return;
}
void handler(int signum) {
	signal(SIGUSR1, handler_busy);

	for(int i = 0; i < LEN(COMPS); i++) {
		if(COMPS[i].sig == 1) {
			COMPS[i].t = 0;
			COMPS[i].update();
			resizeAndPrint(i);
		}
	}
	XStoreName(dpy, DefaultRootWindow(dpy), bartext);
	XFlush(dpy);

	signal(SIGUSR1, handler);
}

int main() {
	dpy = XOpenDisplay(NULL);
	if(!dpy) {
		fprintf(stderr, "Failed to open display\n");
		return 0;
	}

	memset(bartext, '\0', BARLEN);

	COMPS[0].pos = 0;
	for(int i = 0; i < LEN(COMPS); i++) {
		COMPS[i].t = 0;
		COMPS[i].init();
		COMPS[i].update();
		COMPS[i].prevlen = COMPS[i].len();
	}
	for(int i = 1; i < LEN(COMPS); i++) {
		COMPS[i].pos = COMPS[i-1].pos + COMPS[i-1].prevlen;
	}
	for(int i = 0; i < LEN(COMPS); i++) {
		COMPS[i].reprint(bartext + COMPS[i].pos);
	}
	XStoreName(dpy, DefaultRootWindow(dpy), bartext);
	XFlush(dpy);

	signal(SIGUSR1, handler);

	for(;;) {
		sleep(1);
		for(int i = 0; i < LEN(COMPS); i++) {
			COMPS[i].t++;
			if(COMPS[i].t == COMPS[i].period) {
				COMPS[i].t = 0;
				COMPS[i].update();
				resizeAndPrint(i);
			}
		}
		XStoreName(dpy, DefaultRootWindow(dpy), bartext);
		XFlush(dpy);
	}
}
