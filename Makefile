install: main.c
	cc main.c -o /usr/local/bin/trisutils

uninstall:
	rm /usr/local/bin/trisutils
