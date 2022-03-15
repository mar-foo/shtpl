#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMMANDSIZE 4096

void addc(char*, char, int);
void dotemplate(char*);
void blank(char*, int);

enum states {
	TEXT = 0,
	BEGIN_T,
	IN_T,
	END_T,
};

int
main(void)
{
	char buf[MAX_COMMANDSIZE], c;
	int state;
	state = TEXT;

	memset(buf, 0, MAX_COMMANDSIZE * sizeof(char));
	int buf_pos = 0;

	while((c = getchar()) != EOF){
		switch(c){
		case '{':
			if(state == TEXT){
				state = BEGIN_T;
			}else if(state == BEGIN_T){
				state = IN_T;
			}
			break;
		case '}':
			if(state == IN_T){
				state = END_T;
			}else if(state == END_T){
				state = TEXT;
				addc(buf, '\0', buf_pos);
				dotemplate(buf);
				blank(buf, MAX_COMMANDSIZE);
				buf_pos = 0;
			}
			break;
		default:
			if(state == IN_T){
				addc(buf, c, buf_pos++);
			}else{
				printf("%c", c);
			}
		}
	}
	return 0;
}

void
dotemplate(char *command)
{
	char c;
	FILE *pipe;

	pipe = popen(command, "r");
	while((c = getc(pipe)) != EOF)
		printf("%c", c);
}

void
blank(char *buf, int size)
{
	for(int i = 0; i < size; i++)
		buf[i] = '\0';
}

void
addc(char *buf, char c, int pos)
{
	if(pos + 2 >= MAX_COMMANDSIZE){
		fprintf(stderr, "Command too long %s\n", buf);
		exit(1);
	}

	buf[pos] = c;
}
