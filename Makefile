CC = g++
CFLAGS = -Wl,--enable-stdcall-fixup -Wall -g
LIBS = -lwinmm -lgdi32 -lglu32 -lopengl32 -L ./ -llibfreeglut -Wl,--subsystem,windows

.PHONY: all clean

all:
	$(MAKE) -C bin all --no-print-directory | FIND /V /I "Nothing to be done for"
	$(CC) $(CFLAGS) bin/*.o lib/*.a -o run$(EXEEXT) $(LIBS)

clean:
	$(MAKE) -C bin clean --no-print-directory	