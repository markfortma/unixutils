CFLAGS ?= -Wall -O0 -g

all: wcat wgrep wunzip wzip

wcat: wcat.c
	$(CC) $(CFLAGS) $(CINCS) $(CLIBS) -o $@ $^

wgrep: wgrep.c
	$(CC) $(CFLAGS) $(CINCS) $(CLIBS) -lpcre -o $@ $^

wunzip: wunzip.c
	$(CC) $(CFLAGS) $(CINCS) $(CLIBS) -lzip -o $@ $^

wzip: wzip.c
	$(CC) $(CFLAGS) $(CINCS) $(CLIBS) -lzip -o $@ $^

.PHONY: clean
clean:
	$(RM) wcat wgrep wzip wunzip *~

