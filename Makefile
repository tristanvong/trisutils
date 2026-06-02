install: main.c
	cc main.c -o /usr/local/bin/trisutil

uninstall:
	rm /usr/local/bin/trisutil
