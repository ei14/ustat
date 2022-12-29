#include "util.h"

#define _POSIX_SOURCE 1
#include <alloca.h>
#include <alsa/asoundlib.h>

#define VOL_PHOLDER " ⱽᴼᴸ??"
#define VOL_LEN (sizeof(VOL_PHOLDER) - 1)

// " VVVOOOLLL??"
//            |
//  01234567890
#define VOL_POS 10

#define CAP(num, cap) (num <= cap ? num : cap)

static snd_mixer_t* handle;
static snd_mixer_elem_t* elem;
static snd_mixer_selem_id_t* sid;

static long minvol;
static long maxvol;
static long outvol;

void volinit() {
	snd_mixer_selem_id_alloca(&sid);

	snd_mixer_selem_id_set_index(sid, 0);
	snd_mixer_selem_id_set_name(sid, "Master");

	snd_mixer_open(&handle, 0);
	snd_mixer_attach(handle, "default");
	snd_mixer_selem_register(handle, NULL, NULL);
	snd_mixer_load(handle);
	elem = snd_mixer_find_selem(handle, sid);

	snd_mixer_selem_get_playback_volume_range(elem, &minvol, &maxvol);

	snd_mixer_close(handle);
}

void volupdate() {
	snd_mixer_selem_id_alloca(&sid);

	snd_mixer_selem_id_set_index(sid, 0);
	snd_mixer_selem_id_set_name(sid, "Master");

	snd_mixer_open(&handle, 0);
	snd_mixer_attach(handle, "default");
	snd_mixer_selem_register(handle, NULL, NULL);
	snd_mixer_load(handle);
	elem = snd_mixer_find_selem(handle, sid);

	snd_mixer_selem_get_playback_volume(elem, 0, &outvol);

	outvol -= minvol;
	maxvol -= minvol;

	snd_mixer_close(handle);
}

const int vollen() {
	return VOL_LEN;
}

void volprint(char *dest) {
	doz2(dest + VOL_POS, CAP(144 * outvol / maxvol, 143));
}

void volreprint(char *dest) {
	memcpy(dest, VOL_PHOLDER, VOL_LEN);
	volprint(dest);
}
