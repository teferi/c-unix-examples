all: send init recieve

init: init.c

send: send.c

recieve: recieve.c

.PHONY: clean
clean:
	rm send recieve init
	ipcrm -Q 0xABC
