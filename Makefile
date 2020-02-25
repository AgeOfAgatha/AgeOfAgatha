CC = /opt/mingw64/bin/x86_64-w64-mingw32-g++
CFLAGS = -std=c++11 -w -g -D_FILE_OFFSET_BITS=64 -D_LARGEFILE64_SOURCE -D_LARGEFILE_SOURCE -I/usr/include/GL
LIBS = ./lib/libfltk.a ./lib/libfltk_gl.a ./lib/libfltk.a ./lib/glew32.lib ./lib/glew32s.lib ./lib/libfreeglut.dll.a ./lib/libfreeglut_static.a ./glew32.dll ./libfreeglut.dll -lcomctl32 -lws2_32 -lopengl32 -lwinmm -lglu32 -lkernel32 -luser32 -lgdi32 -lwinspool -lshell32 -lole32 -loleaut32 -luuid -lcomdlg32 -ladvapi32
EXEEXT = .exe

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

run$(EXEEXT): bin/*.o
	@echo 	Executable is being assembled...
	@$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

clean:
	@echo Cleaning...
	@$(MAKE) -C bin clean --no-print-directory
