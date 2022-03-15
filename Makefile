PREFIX=/usr/local

.PHONY: all clean install uninstall

all: shtpl

shtpl: shtpl.c
	$(CC) $(CFLAGS) -o $@ $^

install: shtpl
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp -f shtpl $(DESTDIR)$(PREFIX)/bin
	chmod 755 $(DESTDIR)$(PREFIX)/bin/shtpl

uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/shtpl

clean:
	rm shtpl

