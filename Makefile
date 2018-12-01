CC = g++
CFLAGS = -Wl,--enable-stdcall-fixup -Wall -g
LIBS = -lglu32 -lopengl32 -L ./ -lglut32

.PHONY: all build clean

all:
	$(MAKE) -C bin all --no-print-directory
	$(MAKE) build --no-print-directory

build:
	$(MAKE) run$(EXEEXT) --no-print-directory

clean:
	$(MAKE) -C bin clean --no-print-directory

run$(EXEEXT):
	$(CC) $(CFLAGS) bin/*.o -o run$(EXEEXT) $(LIBS)