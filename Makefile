CCW = i686-w64-mingw32-g++
CCL = g++
CFLAGS = -std=c++14 -w -g -D_FILE_OFFSET_BITS=64 -D_LARGEFILE64_SOURCE -D_LARGEFILE_SOURCE -I/usr/include -I/usr/include/x86_64-linux-gnu -I$(shell pwd)/deps  -static-libgcc
LIBSW = -mwindows -L/usr/lib/x86_64-linux-gnu/ -lopengl32 -lglu32 -lglut32
LIBSL = -lGL -lGLU -lglut
EXTW = .exe
EXTL = .pe

.PHONY: all help clean clean-all

all:
	@echo making linux executable... && $(MAKE) linux --no-print-directory
	@echo making windows executable... && $(MAKE) windows --no-print-directory

linux:
	@(echo '\t'Compiling object code... && $(MAKE) -C binl all --no-print-directory && echo '\t'Done Compiling) | grep -vE "(Nothing to be done for|is up to date)"
	@(echo '\t'Assembling executable... && $(MAKE) run$(EXTL) --no-print-directory && echo '\t'Done Assembling) | grep -vE "(Nothing to be done for|is up to date)"

windows:
	@(echo '\t'Compiling object code... && $(MAKE) -C binw all --no-print-directory && echo '\t'Done Compiling) | grep -vE "(Nothing to be done for|is up to date)"
	@(echo '\t'Assembling executable... && $(MAKE) run$(EXTW) --no-print-directory && echo '\t'Done Assembling) | grep -vE "(Nothing to be done for|is up to date)"

help:
	@echo Available build targets:
	@echo -e '\t'all
	@echo -e '\t'linux
	@echo -e '\t'windows
	@echo -e '\t'run$(EXTW)
	@echo -e '\t'run$(EXTL)
	@echo -e '\t'clean
	@echo -e '\t'clean-all
	@echo -e '\t'help

run$(EXTW): binw/*.o
	@echo -e '\t\t'Executable is being assembled...
	@$(CCW) $(CFLAGS) $^ -o $@ $(LIBSW)

run$(EXTL): binl/*.o
	@echo -e '\t\t'Executable is being assembled...
	@$(CCL) $(CFLAGS) $^ -o $@ $(LIBSL)

clean-all:
	@echo Cleaning...
	@$(MAKE) clean --no-print-directory
	@echo -e '\t'Cleaning object files in binl...
	@rm ./binl/*.o -f 2>/dev/null
	@echo -e '\t'Cleaning object files in binw...
	@rm ./binw/*.o -f 2>/dev/null
	@echo Done cleaning

clean:
	@echo Cleaning shader files in root...
	@rm ./*.bin -f 2>/dev/null
	@rm ./*.format -f 2>/dev/null
