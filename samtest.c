/*
 * samtest.c :: control a samsung TV via the "ex-link" jack, in "uart" mode.  By Mark Lord.
 *
 * The stereo mini-plug is wired for RS232 levels as follows:
 *	tip  == send to the tv
 *	ring == receive from the tv
 *	base == ground
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

static unsigned char csum (unsigned char *cmd)
{
	unsigned char csum = 0;
	int i;

	for (i = 0; i < 6; i++)
		csum += cmd[i];
	csum = (~csum + 1) & 0xff;
	return csum;
}

static void make_cmd (unsigned char *cmd, unsigned char *codes)
{
	memcpy(cmd + 2, codes, 4);
	cmd[6] = csum(cmd);
}

struct command_s {
	char *name;
	unsigned char codes[4];
} commands[] = {
	{"power_on",		{0x00,0x00,0x00,0x02}},
	{"power_off",		{0x00,0x00,0x00,0x01}},

	{"dcoff",		{0x0b,0x09,0x01,0x00}},
	{"dclow",		{0x0b,0x09,0x01,0x01}},
	{"dcmedium",		{0x0b,0x09,0x01,0x02}},
	{"dchigh",		{0x0b,0x09,0x01,0x03}},

	/* signal sources */
	{"tv",			{0x0a,0x00,0x00,0x00}},
	{"hdmi_1",		{0x0a,0x00,0x05,0x00}},  /* "duke" (MythTV PVR) */
	{"hdmi_2",		{0x0a,0x00,0x05,0x01}},
	{"hdmi_3",		{0x0a,0x00,0x05,0x02}},
	{"hdmi_4",		{0x0a,0x00,0x05,0x03}},
	{"component_1",		{0x0a,0x00,0x03,0x00}},
	{"component_2",		{0x0a,0x00,0x03,0x01}},  /* DVD player */

	{"backlight_10",	{0x0b,0x01,0x00,10}},
	{"backlight_15",	{0x0b,0x01,0x00,15}},
	{"backlight_20",	{0x0b,0x01,0x00,20}},

	{"contrast_50",		{0x0b,0x02,0x00,50}},
	{"contrast_95",		{0x0b,0x02,0x00,95}},
	{"contrast_100",	{0x0b,0x02,0x00,100}},

	{"bright_40",		{0x0b,0x03,0x00,40}},
	{"bright_50",		{0x0b,0x03,0x00,50}},
	{"bright_55",		{0x0b,0x03,0x00,55}},

	{"sharp_15",		{0x0b,0x04,0x00,15}},
	{"sharp_20",		{0x0b,0x04,0x00,20}},
	{"sharp_25",		{0x0b,0x04,0x00,25}},
	{"sharp_50",		{0x0b,0x04,0x00,50}},

	{"color_40",		{0x0b,0x05,0x00,40}},
	{"color_50",		{0x0b,0x05,0x00,50}},

	{"edge_enh_off",	{0x0b,0x09,0x11,0x00}},  // nfg
	{"edge_enh_on",		{0x0b,0x09,0x11,0x01}},  // nfg

	{"tone_cool",		{0x0b,0x0a,0x00,0x00}},
	{"tone_normal",		{0x0b,0x0a,0x00,0x01}},

	{"picsize_16x9",	{0x0b,0x0a,0x01,0x00}},
	{"picsize_fit",		{0x0b,0x0a,0x01,0x05}},

	{"mpegnoise_off",	{0x0b,0x0a,0x03,0x00}},
	{"mpegnoise_low",	{0x0b,0x0a,0x03,0x01}},

	{"film_off",		{0x0b,0x0a,0x05,0x00}},  // nfg
	{"film_normal",		{0x0b,0x0a,0x05,0x01}},  // nfg

	/* in theory, these should be the 120Hz/clearmotion codes, but.. no: */
	//{"cm_0",		{0x0b,0x0a,0x06,0x00}},
	//{"cm_1",		{0x0b,0x0a,0x06,0x01}},
	//{"cm_2",		{0x0b,0x0a,0x06,0x02}},

	{"pic_reset_all",	{0x0b,0x0b,0x00,0x00}},

	{NULL, {0,0,0,0}}
};

static unsigned char *get_raw_hex (int first, char *argv[])
{
	static unsigned char codes[4] = {0,0,0,0};
	int i;

	for (i = 0; i < 4; ++i) {
		unsigned long long code = strtoull(argv[first + i], NULL, 0);
		codes[i] = code;
	}
	return codes;
}

int main (int argc, char *argv[])
{
	int i, c, fd, len;
	unsigned char rsp[3], cmd[7] = {0x08,0x22,0,0,0,0,0};

	if (-1 == system("stty -F /dev/ttyAMA0 -ixon -ixoff -crtscts speed 9600")) {
		perror("stty");
		return EIO;
	}

	fd = open("/dev/ttyAMA0", O_RDWR);
	if (fd == -1) {
		perror("/dev/ttyAMA0");
		return EIO;
	}

	for (i = 1; i < argc ; ++i) {
		char *arg = argv[i];
		unsigned char *codes = NULL;
		if (0 == strcmp("raw", arg)) {
			codes = get_raw_hex(++i, argv);
			i += 4;
		} else {
			for (c = 0; commands[c].name; ++c) {
				if (0 == strcmp(commands[c].name, arg)) {
					codes = commands[c].codes;
					break;
				}
			}
		}
		if (!codes) {
			fprintf(stderr, "unknown command: %s\n", arg);
			return EINVAL;
		}
		make_cmd(cmd, codes);
		if (7 != write(fd, cmd, 7)) {
			perror("write()");
			return EIO;
		}
		memset(rsp, 0, 3);
		len = read(fd, rsp, 3);
		printf("response: (%d) 0x%02x 0x%02x 0x%02x\n", len, rsp[0], rsp[1], rsp[2]);
		if ((i + 1) < argc)
			sleep(1);
	}
	return 0;
}
