CC = g++
CFLAGS = -Wl,--enable-stdcall-fixup -Wall -g
LIBS = -lglu32 -lopengl32 -L ./ -lglut32

.PHONY: all clean

all:
	$(MAKE) -C bin all --no-print-directory | FIND /V /I "Nothing to be done for"
	$(CC) $(CFLAGS) bin/*.o -o run$(EXEEXT) $(LIBS)

clean:
	$(MAKE) -C bin clean --no-print-directory	