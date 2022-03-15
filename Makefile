PREFIX=/usr/local
MANPREFIX=$(PREFIX)/share/man

.PHONY: all clean install uninstall

all: shtpl

shtpl: shtpl.c
	$(CC) $(CFLAGS) -o $@ $^

install: shtpl
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp -f shtpl $(DESTDIR)$(PREFIX)/bin
	chmod 755 $(DESTDIR)$(PREFIX)/bin/shtpl
	mkdir -p $(DESTDIR)$(MANPREFIX)/man1
	cp -f shtpl.1 $(DESTDIR)$(MANPREFIX)/man1
	chmod 644 $(DESTDIR)$(MANPREFIX)/man1/shtpl.1

uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/shtpl
	rm -f $(DESTDIR)$(MANPREFIX)/bin/shtpl.1

clean:
	rm shtpl

