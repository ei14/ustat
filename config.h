#include "components.h"
#include "util.h"

#include "battery.h"
#include "cpu.h"
#include "datetime.h"
#include "disk.h"
#include "ram.h"
#include "temp.h"
#include "volume.h"
#include "wifi.h"

#define BARLEN 512
#define WIDTH_UPDATE 8

Comp COMPS[] = {
	{ .init=nop, .update=wifiupdate, .len=wifilen, .print=wifiprint, .reprint=wifireprint, .period=2, .sig=0 },
	{ .init=cpuinit, .update=cpuupdate, .len=cpulen, .print=cpuprint, .reprint=cpureprint, .period=1, .sig=0 },
	{ .init=nop, .update=tempupdate, .len=templen, .print=tempprint, .reprint=tempreprint, .period=16, .sig=0 },
	{ .init=nop, .update=ramupdate, .len=ramlen, .print=ramprint, .reprint=ramreprint, .period=4, .sig=0 },
	{ .init=batinit, .update=batupdate, .len=batlen, .print=batprint, .reprint=batreprint, .period=4, .sig=0 },
	{ .init=volinit, .update=volupdate, .len=vollen, .print=volprint, .reprint=volreprint, .period=4, .sig=1 },
	{ .init=nop, .update=diskupdate, .len=disklen, .print=diskprint, .reprint=diskreprint, .period=16, .sig=0 },
	{ .init=nop, .update=nop, .len=datelen, .print=dateprint, .reprint=datereprint, .period=8, .sig=0 },
	{ .init=nop, .update=nop, .len=timelen, .print=timeprint, .reprint=timereprint, .period=2, .sig=0 },
	{ .init=nop, .update=timeupdate, .len=secslen, .print=secsprint, .reprint=secsreprint, .period=1, .sig=0 },
};
