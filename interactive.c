#include <stdio.h>
#include <string.h>

#define PROMPT	"TEST> "

static char *readline(const char *prompt)
{
	char line[1024];

	fputs(prompt, stdout);
	fflush(stdout);

	char *r = fgets(line, sizeof(line), stdin);
	if (!r)
		return NULL;

	//TODO: trim space and '\n'
	int len = strlen(r);
	if (len > 0 && r[len - 1] == '\n')
		r[len - 1] = '\0';

	return strdup(r);
}

static int command_parse(const char *cmdstr)
{
	//TODO: comand line parsing
	printf("%s: do something...\n", cmdstr);

	if (!strcasecmp(cmdstr, "quit") || !strcasecmp(cmdstr, "exit")) {
		printf("Bye!\n");
		return 1;
	}

	return 0;
}

int main()
{
	char *cmd;

	while (1) {
		cmd = readline(PROMPT);
		if (!cmd)
			break;

		if (command_parse(cmd))
			break;
	}

	return 0;
}
