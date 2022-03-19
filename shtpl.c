#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMMANDSIZE 4096

void addc(char*, char, int);
void blank(char*, int);
void dotemplate(char*);
void shtpl(FILE*);

enum states {
	TEXT = 0,
	BEGIN_T,
	IN_T,
	END_T,
};

int
main(int argc, char **argv)
{
	FILE *f;
	if(argc == 1){
		shtpl(stdin);
	}else{
		for(int i = 1; i < argc; i++){
			f = fopen(argv[i], "r");
			if(f == NULL){
				fprintf(stderr, "Error opening %s\n", argv[i]);
				continue;
			}
			shtpl(f);
			fclose(f);
		}
	}

	return 0;
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

void
blank(char *buf, int size)
{
	for(int i = 0; i < size; i++)
		buf[i] = '\0';
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
	pclose(pipe);
}

void
shtpl(FILE *f)
{
	char buf[MAX_COMMANDSIZE], c;
	int state;
	state = TEXT;

	memset(buf, 0, MAX_COMMANDSIZE * sizeof(char));
	int buf_pos = 0;

	while((c = getc(f)) != EOF){
		switch(state){
		case TEXT:
			if(c == '{'){
				state = BEGIN_T;
			}else{
				printf("%c", c);
			}
			break;
		case BEGIN_T:
			if(c == '{'){
				state = IN_T;
			}else{
				state = TEXT;
				printf("{%c", c);
			}
			break;
		case END_T:
			if(c == '}'){
				state = TEXT;
				addc(buf, '\0', buf_pos);
				dotemplate(buf);
				blank(buf, MAX_COMMANDSIZE);
				buf_pos = 0;
			}else{
				state = IN_T;
				addc(buf, '}', buf_pos++);
				addc(buf, c, buf_pos++);
			}
			break;
		case IN_T:
			if(c == '}'){
				state = END_T;
			}else{
				addc(buf, c, buf_pos++);
			}
		}
	}
}
