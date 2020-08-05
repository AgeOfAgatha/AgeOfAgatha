CCW32 = i686-w64-mingw32-g++
CCW64 = x86_64-w64-mingw32-g++
CCL = g++
CFLAGS = -std=c++14 -w -g -D_FILE_OFFSET_BITS=64 -D_LARGEFILE64_SOURCE -D_LARGEFILE_SOURCE -I/usr/include -I/usr/include/x86_64-linux-gnu -I$(shell pwd)/deps  -static-libgcc -static
LIBSW32 = -L/usr/lib/x86_64-linux-gnu/ -lopengl32 -lglu32 -lglut32
LIBSW64 = -L/usr/lib/x86_64-linux-gnu/ -lopengl32 -lglu32 ./freeglut.dll
LIBSL = -lGL -lGLU -lglut
EXTW32 = .x32.exe
EXTW64 = .x64.exe
EXTL = .pe

.PHONY: all help clean clean-all linux windows32 windows64 run

all:
	@echo making linux executable... && $(MAKE) linux --no-print-directory
	@echo making windows 32 bit executable... && $(MAKE) windows32 --no-print-directory
	@echo making windows 64 bit executable... && $(MAKE) windows64 --no-print-directory

linux:
	@(echo '\t'Compiling object code... && $(MAKE) -C binl all --no-print-directory && echo '\t'Done Compiling) | grep -vE "(Nothing to be done for|is up to date)"
	@(echo '\t'Assembling executable... && $(MAKE) run$(EXTL) --no-print-directory && echo '\t'Done Assembling) | grep -vE "(Nothing to be done for|is up to date)"

windows32:
	@(echo '\t'Compiling object code... && $(MAKE) -C binw32 all --no-print-directory && echo '\t'Done Compiling) | grep -vE "(Nothing to be done for|is up to date)"
	@(echo '\t'Assembling executable... && $(MAKE) run$(EXTW32) --no-print-directory && echo '\t'Done Assembling) | grep -vE "(Nothing to be done for|is up to date)"

windows64:
	@(echo '\t'Compiling object code... && $(MAKE) -C binw64 all --no-print-directory && echo '\t'Done Compiling) | grep -vE "(Nothing to be done for|is up to date)"
	@(echo '\t'Assembling executable... && $(MAKE) run$(EXTW64) --no-print-directory && echo '\t'Done Assembling) | grep -vE "(Nothing to be done for|is up to date)"

help:
	@echo Available build targets:
	@echo -e '\t'all
	@echo -e '\t'linux
	@echo -e '\t'windows32
	@echo -e '\t'windows64
	@echo -e '\t'run$(EXTW32)
	@echo -e '\t'run$(EXTW64)
	@echo -e '\t'run$(EXTL)
	@echo -e '\t'run
	@echo -e '\t'clean
	@echo -e '\t'clean-all
	@echo -e '\t'help

run$(EXTW32): binw32/*.o
	@echo -e '\t\t'Executable is being assembled...
	@$(CCW32) $(CFLAGS) $^ -o $@ $(LIBSW32)

run$(EXTW64): binw64/*.o
	@echo -e '\t\t'Executable is being assembled...
	@$(CCW64) $(CFLAGS) $^ -o $@ $(LIBSW64)

run$(EXTL): binl/*.o
	@echo -e '\t\t'Executable is being assembled...
	@$(CCL) $(CFLAGS) $^ -o $@ $(LIBSL)

run: run$(EXTL)
	@MESA_GL_VERSION_OVERRIDE=4.3 ./run$(EXTL)

clean-all:
	@echo -ne Cleaning...'\n\t'
	@$(MAKE) clean --no-print-directory
	@echo -e '\t'Cleaning object files in binl...
	@rm ./binl/*.o -f 2>/dev/null
	@echo -e '\t'Cleaning object files in binw32...
	@rm ./binw32/*.o -f 2>/dev/null
	@echo -e '\t'Cleaning object files in binw64...
	@rm ./binw64/*.o -f 2>/dev/null
	@echo Done cleaning

clean:
	@echo Cleaning shader files in root...
	@rm ./*.bin -f 2>/dev/null
	@rm ./*.format -f 2>/dev/null
