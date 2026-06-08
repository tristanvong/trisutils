install: main.c
	cc main.c -o /usr/local/bin/trisutils -lcrypto

uninstall:
	rm /usr/local/bin/trisutils
