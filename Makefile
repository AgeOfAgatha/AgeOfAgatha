CCW = i686-w64-mingw32-g++
CCL = g++
CFLAGS = -std=c++14 -w -g -D_FILE_OFFSET_BITS=64 -D_LARGEFILE64_SOURCE -D_LARGEFILE_SOURCE -I/usr/include -I/usr/include/x86_64-linux-gnu -I$(shell pwd)/deps  -static-libgcc
LIBSW = -mwindows -L/usr/lib/x86_64-linux-gnu/ -lopengl32 -lglu32 -lglut32
LIBSL = -lGL -lGLU -lglut
EXTW = .exe
EXTL = .pe

.PHONY: all help clean

all:
	@(echo Compiling object code... && $(MAKE) -C bin all --no-print-directory && echo 	Done Compiling) | grep -vE "(Nothing to be done for|is up to date)"
	@(echo Assembling executable... && $(MAKE) run$(EXEEXT) --no-print-directory && echo 	Done Assembling) | grep -vE "(Nothing to be done for|is up to date)"
	@rm ./*.bin -f 2>/dev/null
	@rm ./*.format -f 2>/dev/null
	@echo Running executable... && ./run$(EXEEXT)

help:
	@echo Available build targets:
	@echo 	all
	@echo 	run
	@echo 	clean
	@echo 	help

run$(EXTW): bin/*.o
	@echo 	Executable is being assembled...
	@$(CCW) $(CFLAGS) $^ -o $@ $(LIBSW)

run$(EXTL): bin/*.o
	@echo 	Executable is being assembled...
	@$(CCL) $(CFLAGS) $^ -o $@ $(LIBSL)

clean:
	@echo Cleaning...
	@$(MAKE) -C bin clean --no-print-directory
