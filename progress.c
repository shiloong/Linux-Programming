#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <sys/param.h>

#define PBWIDTH_MAX	100
#define PBSTR		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"

static int pb_width = 0;

static void init_pb(void)
{
	struct winsize ws;

	ioctl(0, TIOCGWINSZ, &ws); // get width of the terminal
	if (ws.ws_col > 16)
		pb_width = MIN(ws.ws_col - 8, PBWIDTH_MAX);

	if (pb_width != 0)
		fprintf(stdout, "\r  0%% [%*s]", pb_width, "");
	else
		fprintf(stdout, "\r  0%%");

	fflush(stdout);
}

static void  print_pb(float percentage)
{
	int progress = percentage * 100;
	int lpad = percentage * pb_width;

	printf("\r%3d%% [%.*s%*s]", progress, lpad, PBSTR, (pb_width - lpad), "");
	fflush(stdout);
}

int main(void)
{
	init_pb();

	for (int i = 0; i <= 100; i++) {
		print_pb(i / 100.0);
		sleep(1);
	}

	return 0;
}

