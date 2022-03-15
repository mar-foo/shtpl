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
			}else if(state == IN_T){
				addc(buf, c, buf_pos++);
			}
			break;
		case '}':
			if(state == IN_T){
				state = END_T;
				break;
			}else if(state == END_T){
				state = TEXT;
				addc(buf, '\0', buf_pos);
				dotemplate(buf);
				blank(buf, MAX_COMMANDSIZE);
				buf_pos = 0;
				break;
			} // FALLTHROUGH
		default:
			if(state == IN_T){
				addc(buf, c, buf_pos++);
			}else if(state == BEGIN_T){
				printf("{%c", c);
				state = TEXT;
			}else if(state == END_T){
				addc(buf, '}', buf_pos++);
				addc(buf, c, buf_pos++);
				state = IN_T;
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
	char c1, c2;
	FILE *pipe;

	pipe = popen(command, "r");
	c1 = getc(pipe);
	while((c2 = getc(pipe)) != EOF){
		printf("%c", c1);
		c1 = c2;
	}
	if(c1 != '\n')
		printf("%c", c1);
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
