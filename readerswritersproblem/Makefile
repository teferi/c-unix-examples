all: reader writer init

init: init.c

reader: reader.c

writer: writer.c

.PHONY: clean
clean:
	rm reader writer init
	ipcrm -S 0xABC
