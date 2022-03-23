#include <stdio.h>
#include <string.h>

#define PROMPT	"TEST> "

static char *getcmd(void)
{
	// output the promption
	fputs(PROMPT, stdout);
	fflush(stdout);

	// get command input
	char line[256];
	char *r = fgets(line, sizeof(line), stdin);
	if (!r)
		return NULL;

	// trim tailling newline
	if (r[strlen(r) - 1] == '\n')
		r[strlen(r) - 1] = 0;

	return strdup(r);
}

static void usage()
{
	fprintf(stderr,
		"Usage: ./a.out\n"
		"A simple interactive command line interface\n"
		"\n"
		"COMMAND:\n"
		"  ? | help	This help message.\n"
		"  quit | exit	Say byebye.\n"
	       );
}

static void run_command(const char *cmd)
{
	printf("Run command [%s] with\n", cmd);

	int i = 1;
	char *arg = strtok(NULL, "\t ");
	while (arg) {
		printf("ARG#%d = [%s]\n", i, arg);
		arg = strtok(NULL, "\t ");
		i++;
	}
}

int main()
{
	while (1) {
		char *cmdstr = getcmd();
		char *cmd = strtok(cmdstr, "\t ");
		if (!cmd || cmd[0] == '?' || !strcasecmp(cmd, "help")) {
			usage();
			continue;
		}

		if (!strcasecmp(cmd, "quit") || !strcasecmp(cmd, "exit")) {
			printf("Bye!\n");
			break;
		}

		run_command(cmd);
	}

	return 0;
}
