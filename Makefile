#########################
#Main Makefile
#########################
CCW32 = i686-w64-mingw32-g++
CCW64 = x86_64-w64-mingw32-g++
CCL = g++
CFLAGS = -std=c++14 -w -g -D_FILE_OFFSET_BITS=64 -D_LARGEFILE64_SOURCE -D_LARGEFILE_SOURCE -static-libgcc
LIBSL = -lGL -lGLU -lglut
LIBSM = -lGL -lGLU -lglut
LIBSW32 = -L/usr/lib/x86_64-linux-gnu/ -lopengl32 -lglu32 -lglut32 -static
LIBSW64 = -L/usr/lib/x86_64-linux-gnu/ -lopengl32 -lglu32 bin/binw64/freeglut.dll -static
EXTL = .pe
EXTM = .mac
EXTW32 = .x32.exe
EXTW64 = .x64.exe

#Get OS and configure based on OS
ifeq ($(OS),Windows_NT)
    CFLAGSW += -D WIN32
    ifeq ($(PROCESSOR_ARCHITEW6432),AMD64)
        CFLAGSW += -D AMD64
   		DISTRO = w64
    else
        ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
            CFLAGSW += -D AMD64
   			DISTRO = w64
        endif
        ifeq ($(PROCESSOR_ARCHITECTURE),x86)
            CFLAGSW += -D IA32
   			DISTRO = w32
        endif
    endif
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        CFLAGSL += -D LINUX
   		DISTRO = lin
    endif
    ifeq ($(UNAME_S),Darwin)
        CFLAGSL += -D OSX
   		DISTRO = mac
    endif
    ifeq ($(UNAME), Solaris)
   		DISTRO = sol
    endif
    UNAME_P := $(shell uname -p)
    ifeq ($(UNAME_P),x86_64)
        CFLAGSL += -D AMD64
    endif
    ifneq ($(filter %86,$(UNAME_P)),)
        CFLAGSL += -D IA32
    endif
    ifneq ($(filter arm%,$(UNAME_P)),)
        CFLAGSL += -D ARM
    endif
endif

.PHONY: main all help fix linux mac windows32 windows64 run c cl  clean clean-all clean-lin clean-mac clean-w32 clean-w64 clean-lin-shaders clean-mac-shaders clean-w32-shaders clean-w64-shaders

#########################
#assemble for my distro
#########################
main:
	@echo making for $(DISTRO)... && $(MAKE) $(DISTRO) --no-print-directory

#########################
#assemble for all distros
#########################
all:
	@echo making for linux... && $(MAKE) lin --no-print-directory
	@echo making for mac... && $(MAKE) mac --no-print-directory
	@echo making for windows 32 bit... && $(MAKE) w32 --no-print-directory
	@echo making for windows 64 bit... && $(MAKE) w64 --no-print-directory

#########################
#Assemble OS specific
#########################
lin:
	@(echo '\t'Compiling object code... && $(MAKE) -C bin/binl all --no-print-directory && echo '\t'Done Compiling) | grep -vE "(Nothing to be done for|is up to date)"
	@(echo '\t'Assembling executable... && $(MAKE) release/lin/run$(EXTL) --no-print-directory && echo '\t'Done Assembling) | grep -vE "(Nothing to be done for|is up to date)"

mac:
	@(echo '\t'Compiling object code... && $(MAKE) -C bin/binm all --no-print-directory && echo '\t'Done Compiling) | grep -vE "(Nothing to be done for|is up to date)"
	@(echo '\t'Assembling executable... && $(MAKE) release/mac/run$(EXTM) --no-print-directory && echo '\t'Done Assembling) | grep -vE "(Nothing to be done for|is up to date)"

w32:
	@(echo '\t'Compiling object code... && $(MAKE) -C bin/binw32 all --no-print-directory && echo '\t'Done Compiling) | grep -vE "(Nothing to be done for|is up to date)"
	@(echo '\t'Assembling executable... && $(MAKE) release/w32/run$(EXTW32) --no-print-directory && echo '\t'Done Assembling) | grep -vE "(Nothing to be done for|is up to date)"

w64:
	@(echo '\t'Compiling object code... && $(MAKE) -C bin/binw64 all --no-print-directory && echo '\t'Done Compiling) | grep -vE "(Nothing to be done for|is up to date)"
	@(echo '\t'Assembling executable... && $(MAKE) release/w64/run$(EXTW64) --no-print-directory && echo '\t'Done Assembling) | grep -vE "(Nothing to be done for|is up to date)"

#########################
#Assemble executable
#########################
release/lin/run$(EXTL): bin/binl/*.o
	@echo -e '\t\t'Executable is being assembled...
	@rm -rf ./release/lin/* 2>/dev/null
	@$(CCL) $(CFLAGS) $(CFLAGSL) $^ -o $@ $(LIBSL)
	@mkdir ./release/lin/shaders
	@mkdir ./release/lin/models
	@mkdir ./release/lin/textures
	@cp models/* release/lin/models
	@cp textures/* release/lin/textures
	@cp src/shaders/*.fragment release/lin/shaders
	@cp src/shaders/*.vertex release/lin/shaders
	@cp src/shaders/*.geometry release/lin/shaders
	@cp bin/binl/*.dll release/lin/
	@cp bin/*.dll release/lin/
	
release/mac/run$(EXTM): bin/binm/*.o
	@echo -e '\t\t'Executable is being assembled...
	@rm -rf ./release/mac/* 2>/dev/null
	@$(CCL) $(CFLAGS) $(CFLAGSL) $^ -o $@ $(LIBSM)
	@mkdir ./release/mac/shaders
	@mkdir ./release/mac/models
	@mkdir ./release/mac/textures
	@cp models/* release/mac/models
	@cp textures/* release/mac/textures
	@cp src/shaders/*.fragment release/mac/shaders
	@cp src/shaders/*.vertex release/mac/shaders
	@cp src/shaders/*.geometry release/mac/shaders
	@cp bin/binm/*.dll release/mac/
	@cp bin/*.dll release/mac/
	
release/w32/run$(EXTW32): bin/binw32/*.o
	@echo -e '\t\t'Executable is being assembled...
	@rm -rf ./release/w32/* 2>/dev/null
	@$(CCW32) $(CFLAGS) $(CFLAGSW) $^ -o $@ $(LIBSW32)
	@mkdir ./release/w32/shaders
	@mkdir ./release/w32/models
	@mkdir ./release/w32/textures
	@cp models/* release/w32/models
	@cp textures/* release/w32/textures
	@cp src/shaders/*.fragment release/w32/shaders
	@cp src/shaders/*.vertex release/w32/shaders
	@cp src/shaders/*.geometry release/w32/shaders
	@cp bin/binw32/*.dll release/w32/
	@cp bin/*.dll release/w32/
	
release/w64/run$(EXTW64): bin/binw64/*.o
	@echo -e '\t\t'Executable is being assembled...
	@rm -rf ./release/w64/* 2>/dev/null
	@$(CCW64) $(CFLAGS) $(CFLAGSW) $^ -o $@ $(LIBSW64)
	@mkdir ./release/w64/shaders
	@mkdir ./release/w64/models
	@mkdir ./release/w64/textures
	@cp models/* release/w64/models
	@cp textures/* release/w64/textures
	@cp src/shaders/*.fragment release/w64/shaders
	@cp src/shaders/*.vertex release/w64/shaders
	@cp src/shaders/*.geometry release/w64/shaders
	@cp bin/binw64/*.dll release/w64/
	@cp bin/*.dll release/w64/

#########################
#Utility functions
#########################
help:
	@echo Available build targets:
	@echo -e '\t'all
	@echo -e '\t'lin
	@echo -e '\t'mac
	@echo -e '\t'w32
	@echo -e '\t'w64
	@echo -e '\t'release/lin/run$(EXTL)
	@echo -e '\t'release/mac/run$(EXTM)
	@echo -e '\t'release/w32/run$(EXTW32)
	@echo -e '\t'release/w64/run$(EXTW64)
	@echo -e '\t'run
	@echo -e '\t'clean
	@echo -e '\t'clean-all
	@echo -e '\t'help
	@echo -e '\t'requires: export MESA_GL_VERSION_OVERRIDE=4.3

run: release/lin/run$(EXTL)
	@cd release/lin && MESA_GL_VERSION_OVERRIDE=4.3 ./run$(EXTL)

c:
	@(echo cleaning $(DISTRO)... && $(MAKE) clean-$(DISTRO)-shaders --no-print-directory && echo Done Cleaning) | grep -vE "(Nothing to be done for|is up to date)"

cl:
	@(echo cleaning $(DISTRO) shaders... && $(MAKE) clean-$(DISTRO) --no-print-directory && echo Done Cleaning) | grep -vE "(Nothing to be done for|is up to date)"

clean:
	@echo -ne Cleaning...'\n\t'
	@(echo '\t'Cleaning linux shaders... && $(MAKE) clean-lin-shaders --no-print-directory && echo '\t'Done Cleaning) | grep -vE "(Nothing to be done for|is up to date)"
	@(echo '\t'Cleaning mac shaders... && $(MAKE) clean-mac-shaders --no-print-directory && echo '\t'Done Cleaning) | grep -vE "(Nothing to be done for|is up to date)"
	@(echo '\t'Cleaning w32 shaders... && $(MAKE) clean-w32-shaders --no-print-directory && echo '\t'Done Cleaning) | grep -vE "(Nothing to be done for|is up to date)"
	@(echo '\t'Cleaning w64 shaders... && $(MAKE) clean-w64-shaders --no-print-directory && echo '\t'Done Cleaning) | grep -vE "(Nothing to be done for|is up to date)"
	@echo Done cleaning

clean-all:
	@echo -ne Cleaning...'\n\t'
	@(echo '\t'Cleaning linux... && $(MAKE) clean-lin --no-print-directory && echo '\t'Done Cleaning) | grep -vE "(Nothing to be done for|is up to date)"
	@(echo '\t'Cleaning mac... && $(MAKE) clean-mac --no-print-directory && echo '\t'Done Cleaning) | grep -vE "(Nothing to be done for|is up to date)"
	@(echo '\t'Cleaning w32... && $(MAKE) clean-w32 --no-print-directory && echo '\t'Done Cleaning) | grep -vE "(Nothing to be done for|is up to date)"
	@(echo '\t'Cleaning w64... && $(MAKE) clean-w64 --no-print-directory && echo '\t'Done Cleaning) | grep -vE "(Nothing to be done for|is up to date)"
	@echo Done cleaning

clean-lin:
	@echo -e '\t'Cleaning object files in binl...
	@rm ./bin/binl/*.o -f 2>/dev/null
	@echo -e '\t'Cleaning files in release...
	@rm -rf ./release/lin/* -f 2>/dev/null

clean-mac:
	@echo -e '\t'Cleaning object files in binm...
	@rm ./bin/binm/*.o -f 2>/dev/null
	@echo -e '\t'Cleaning files in release...
	@rm -rf ./release/mac/* -f 2>/dev/null

clean-w32:
	@echo -e '\t'Cleaning object files in binw32...
	@rm ./bin/binw32/*.o -f 2>/dev/null
	@echo -e '\t'Cleaning files in release...
	@rm -rf ./release/w32/* -f 2>/dev/null

clean-w64:
	@echo -e '\t'Cleaning object files in binw64...
	@rm ./bin/binw64/*.o -f 2>/dev/null
	@echo -e '\t'Cleaning files in release...
	@rm -rf ./release/w64/* -f 2>/dev/null

clean-lin-shaders:
	@echo -e '\t'Cleaning shader files in release...
	@rm ./release/lin/*.bin -f 2>/dev/null
	@rm ./release/lin/*.format -f 2>/dev/null
	@rm ./release/lin/shaders/* -f 2>/dev/null
	@mkdir -p ./release/lin/shaders 2>/dev/null
	@cp src/shaders/*.fragment release/lin/shaders
	@cp src/shaders/*.vertex release/lin/shaders
	@cp src/shaders/*.geometry release/lin/shaders

clean-mac-shaders:
	@echo -e '\t'Cleaning shader files in release...
	@rm ./release/mac/*.bin -f 2>/dev/null
	@rm ./release/mac/*.format -f 2>/dev/null
	@rm ./release/mac/shaders/* -f 2>/dev/null
	@mkdir -p ./release/mac/shaders 2>/dev/null
	@cp src/shaders/*.fragment release/mac/shaders
	@cp src/shaders/*.vertex release/mac/shaders
	@cp src/shaders/*.geometry release/mac/shaders

clean-w32-shaders:
	@echo -e '\t'Cleaning shader files in release...
	@rm ./release/w32/*.bin -f 2>/dev/null
	@rm ./release/w32/*.format -f 2>/dev/null
	@rm ./release/w32/shaders/* -f 2>/dev/null
	@mkdir -p ./release/w32/shaders 2>/dev/null
	@cp src/shaders/*.fragment release/w32/shaders
	@cp src/shaders/*.vertex release/w32/shaders
	@cp src/shaders/*.geometry release/w32/shaders

clean-w64-shaders:
	@echo -e '\t'Cleaning shader files in release...
	@rm ./release/w64/*.bin -f 2>/dev/null
	@rm ./release/w64/*.format -f 2>/dev/null
	@rm ./release/w64/shaders/* -f 2>/dev/null
	@mkdir -p ./release/w64/shaders 2>/dev/null
	@cp src/shaders/*.fragment release/w64/shaders
	@cp src/shaders/*.vertex release/w64/shaders
	@cp src/shaders/*.geometry release/w64/shaders


fix:
	@echo Replacing spaces with tabs in source files
	@./fix.sh