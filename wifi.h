#include <stdio.h>
#include <string.h>

#include <linux/wireless.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "util.h"

#define CLAMP(a, x, b) (a <= x ? (x <= b ? x : b) : a)

#define WIFI_PHOLDER " ^c#FFFFFF^..^c#FFFFFF^"
#define WIFI_LEN (sizeof(WIFI_PHOLDER) - 1)

// "  ^c#FFFFFF^..^c#FFFFFF^ "
//         |    |
//  0
//   123456789012345678901234
#define WIFI_SPEED_POS 12
#define WIFI_COLOR_POS 7

#define WIFI_READMAX 128

int connected;
int strength;
char ssid[33]; // An SSID can be up to 32 characters long
int ssidlen;

void wifiinit() {
	memset(ssid, 0, 33);
	ssidlen = 0;
}

FILE *fp;
char wifibuf[WIFI_READMAX];
struct iwreq wreq;
int sockfd;
void wifiupdate() {

	fp = fopen("/sys/class/net/wlp2s0/operstate", "r");
	fgets(wifibuf, 2, fp);
	fclose(fp);
	connected = (wifibuf[0] == 'u');

	if(connected) {
		fp = fopen("/proc/net/wireless", "r");
		fgets(wifibuf, WIFI_READMAX, fp); // Ignore first 2 lines of file
		fgets(wifibuf, WIFI_READMAX, fp); // Ignore first 2 lines of file
		fscanf(fp, "%*s %*d %*d. -%d", &strength);
		fclose(fp);
		strength = CLAMP(0, 216 - 2*strength, 143);

		memset(&wreq, 0, sizeof(struct iwreq));
		wreq.u.essid.length = 33;
		snprintf(wreq.ifr_name, 7, "wlp2s0");
		wreq.u.essid.pointer = ssid;

		sockfd = socket(AF_INET, SOCK_DGRAM, 0);
		ioctl(sockfd, SIOCGIWESSID, &wreq);
		close(sockfd);

		ssidlen = strlen(ssid);
	}
}

const int wifilen() {
	if(!connected)
		return 0;

	return 1 + ssidlen + WIFI_LEN;
}

void wifiprint(char *dest) {
	if(!connected)
		return;

	memcpy(dest + 1, ssid, ssidlen);
	doz2(dest + WIFI_SPEED_POS + ssidlen, strength);

	if(strength < 48)
		memcpy(dest + WIFI_COLOR_POS + ssidlen, "5555", 4);
	else if(strength < 72)
		memcpy(dest + WIFI_COLOR_POS + ssidlen, "FF55", 4);
	else
		memcpy(dest + WIFI_COLOR_POS + ssidlen, "FFFF", 4);
}

void wifireprint(char *dest) {
	if(!connected)
		return;

	dest[0] = ' ';
	memcpy(dest + 1 + ssidlen, WIFI_PHOLDER, WIFI_LEN);
	wifiprint(dest);
}
