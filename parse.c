#include <stdio.h>
#include <string.h>

static void parse(char *str)
{
	char *tok = NULL;
	char *sp = NULL;

	char *first = strtok_r(str, "{}", &sp);
	printf("#0: [%s]\n", first);

	int i = 1;
	do {
		tok = strtok_r(NULL, "{}", &sp);
		printf("#%d: [%s]\n", i, tok);
		i++;
	} while(tok);
}

int main()
{
	char str[] = "{ aaa:111 bbb:222 { a:1 b:2 } ccc:333 }  { ABC:444 BCD:555 {A:3   B:4} CCC:666} DD:77 EE:88";
	printf("TEST: %s\n", str);

	parse(str);

	return 0;
}
