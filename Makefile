.PHONY: all clean

all: shtpl

shtpl: shtpl.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm shtpl

