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
    ifeq ($(PROCESSOR_ARCHITEW6432),AMD64)
        CFLAGSW += -D AMD64
   		DISTRO = windows64
   	else
	    ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
	        CFLAGSW += -D AMD64
			DISTRO = windows64
	    endif
	    ifeq ($(PROCESSOR_ARCHITECTURE),x86)
	        CFLAGSW += -D IA32 WIN32
			DISTRO = windows32
	    endif
    endif
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        CFLAGSL += -D LINUX
   		DISTRO = linux
    endif
    ifeq ($(UNAME_S),Darwin)
        CFLAGSL += -D OSX
   		DISTRO = mac
    endif
    ifeq ($(UNAME), Solaris)
   		DISTRO = solaris
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

.PHONY: main all help fix linux mac solaris windows32 windows64 run c cl clean clean-all clean-linux clean-mac clean-windows32 clean-windows64 clean-linux-shaders clean-mac-shaders clean-windows32-shaders clean-windows64-shaders

#########################
#assemble for my distro
#########################
main:
	@echo making for `tput bold`$(DISTRO)`tput sgr0`... && $(MAKE) $(DISTRO) --no-print-directory

#########################
#assemble for all distros
#########################
all:
	@echo making for `tput bold`linux`tput sgr0`... && $(MAKE) linux --no-print-directory
	@echo making for `tput bold`mac`tput sgr0`... && $(MAKE) mac --no-print-directory
	@echo making for `tput bold`windows 32 bit`tput sgr0`... && $(MAKE) windows32 --no-print-directory
	@echo making for `tput bold`windows 64 bit`tput sgr0`... && $(MAKE) windows64 --no-print-directory

#########################
#Assemble OS specific
#########################
linux:
	@(echo '\t'Compiling object code... && $(MAKE) -C bin/binl all --no-print-directory && echo '\t'Done Compiling) | grep -vE "(Nothing to be done for|is up to date)"
	@(echo '\t'Assembling executable... && $(MAKE) release/lin/run$(EXTL) --no-print-directory && echo '\t'Done Assembling) | grep -vE "(Nothing to be done for|is up to date)"

mac:
	@(echo '\t'Compiling object code... && $(MAKE) -C bin/binm all --no-print-directory && echo '\t'Done Compiling) | grep -vE "(Nothing to be done for|is up to date)"
	@(echo '\t'Assembling executable... && $(MAKE) release/mac/run$(EXTM) --no-print-directory && echo '\t'Done Assembling) | grep -vE "(Nothing to be done for|is up to date)"

windows32:
	@(echo '\t'Compiling object code... && $(MAKE) -C bin/binw32 all --no-print-directory && echo '\t'Done Compiling) | grep -vE "(Nothing to be done for|is up to date)"
	@(echo '\t'Assembling executable... && $(MAKE) release/w32/run$(EXTW32) --no-print-directory && echo '\t'Done Assembling) | grep -vE "(Nothing to be done for|is up to date)"

windows64:
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
	@echo "Available build targets:\
\n\t`tput bold`Command;Description`tput sgr0`\
\n\tmain;Build for detected operating system\
\n\tall;Build for all operating systems\
\n\tlinux;Build for linux\
\n\tmac;Build for mac\
\n\twindows32;Build for Windows 32 bit\
\n\twindows64;Build for windows 64 bit\
\n\trelease/lin/run$(EXTL);Assemble linux executable\
\n\trelease/mac/run$(EXTM);Assemble mac executable\
\n\trelease/w32/run$(EXTW32);Assemble Windows 32 bit executable\
\n\trelease/w64/run$(EXTW64);Assemble Windows 64 bit executable\
\n\trun;Run for detected operating system\
\n\tc;Clean shaders for detected operating system\
\n\tcl;full clean for detected operating system\
\n\tclean;Clean shaders for all operating systems\
\n\tclean-all;full clean for all operating systems\
\n\tclean-linux;full clean for linux\
\n\tclean-mac;full clean for mac\
\n\tclean-windows32;full clean for windows 32 bit\
\n\tclean-windows64;full clean for windows 64 bit\
\n\tclean-linux-shaders;Clean shaders for linux\
\n\tclean-mac-shaders;Clean shaders for mac\
\n\tclean-windows32-shaders;Clean shaders for windows 32 bit\
\n\tclean-windows64-shaders;Clean shaders for windows 64 bit\
\n\tfix;Replaces spaces with tabs in source files\
\n\thelp;Print availabe commands" | column -t -s ';'
	@echo "`tput bold`requires: export MESA_GL_VERSION_OVERRIDE=4.3`tput sgr0`"

run: release/lin/run$(EXTL)
	@cd release/lin && MESA_GL_VERSION_OVERRIDE=4.3 ./run$(EXTL)

c:
	@(echo cleaning `tput bold`$(DISTRO)`tput sgr0`... && $(MAKE) clean-$(DISTRO)-shaders --no-print-directory && echo Done Cleaning) | grep -vE "(Nothing to be done for|is up to date)"

cl:
	@(echo cleaning `tput bold`$(DISTRO)`tput sgr0` shaders... && $(MAKE) clean-$(DISTRO) --no-print-directory && echo Done Cleaning) | grep -vE "(Nothing to be done for|is up to date)"

clean:
	@echo Cleaning...
	@(echo '\t'Cleaning `tput bold`linux`tput sgr0` shaders... && $(MAKE) clean-linux-shaders --no-print-directory && echo '\t'Done Cleaning) | grep -vE "(Nothing to be done for|is up to date)"
	@(echo '\t'Cleaning `tput bold`mac`tput sgr0` shaders... && $(MAKE) clean-mac-shaders --no-print-directory && echo '\t'Done Cleaning) | grep -vE "(Nothing to be done for|is up to date)"
	@(echo '\t'Cleaning `tput bold`windows32`tput sgr0` shaders... && $(MAKE) clean-windows32-shaders --no-print-directory && echo '\t'Done Cleaning) | grep -vE "(Nothing to be done for|is up to date)"
	@(echo '\t'Cleaning `tput bold`windows64`tput sgr0` shaders... && $(MAKE) clean-windows64-shaders --no-print-directory && echo '\t'Done Cleaning) | grep -vE "(Nothing to be done for|is up to date)"
	@echo Done cleaning

clean-all:
	@echo Cleaning...
	@(echo '\t'Cleaning `tput bold`linux`tput sgr0`... && $(MAKE) clean-linux --no-print-directory && echo '\t'Done Cleaning) | grep -vE "(Nothing to be done for|is up to date)"
	@(echo '\t'Cleaning `tput bold`mac`tput sgr0`... && $(MAKE) clean-mac --no-print-directory && echo '\t'Done Cleaning) | grep -vE "(Nothing to be done for|is up to date)"
	@(echo '\t'Cleaning `tput bold`windows32`tput sgr0`... && $(MAKE) clean-windows32 --no-print-directory && echo '\t'Done Cleaning) | grep -vE "(Nothing to be done for|is up to date)"
	@(echo '\t'Cleaning `tput bold`windows64`tput sgr0`... && $(MAKE) clean-windows64 --no-print-directory && echo '\t'Done Cleaning) | grep -vE "(Nothing to be done for|is up to date)"
	@echo Done cleaning

clean-linux:
	@echo -e '\t'Cleaning object files in binl...
	@rm ./bin/binl/*.o -f 2>/dev/null
	@echo -e '\t'Cleaning files in release...
	@rm -rf ./release/lin/* -f 2>/dev/null

clean-mac:
	@echo -e '\t'Cleaning object files in binm...
	@rm ./bin/binm/*.o -f 2>/dev/null
	@echo -e '\t'Cleaning files in release...
	@rm -rf ./release/mac/* -f 2>/dev/null

clean-windows32:
	@echo -e '\t'Cleaning object files in binw32...
	@rm ./bin/binw32/*.o -f 2>/dev/null
	@echo -e '\t'Cleaning files in release...
	@rm -rf ./release/w32/* -f 2>/dev/null

clean-windows64:
	@echo -e '\t'Cleaning object files in binw64...
	@rm ./bin/binw64/*.o -f 2>/dev/null
	@echo -e '\t'Cleaning files in release...
	@rm -rf ./release/w64/* -f 2>/dev/null

clean-linux-shaders:
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

clean-windows32-shaders:
	@echo -e '\t'Cleaning shader files in release...
	@rm ./release/w32/*.bin -f 2>/dev/null
	@rm ./release/w32/*.format -f 2>/dev/null
	@rm ./release/w32/shaders/* -f 2>/dev/null
	@mkdir -p ./release/w32/shaders 2>/dev/null
	@cp src/shaders/*.fragment release/w32/shaders
	@cp src/shaders/*.vertex release/w32/shaders
	@cp src/shaders/*.geometry release/w32/shaders

clean-windows64-shaders:
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