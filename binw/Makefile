CC = i686-w64-mingw32-g++
CFLAGS = -std=c++14 -w -g -c -D_FILE_OFFSET_BITS=64 -D_LARGEFILE64_SOURCE -D_LARGEFILE_SOURCE -I$(shell pwd)/../deps/gl -I$(shell pwd)/../deps -I$(shell pwd)/../deps/GL -static-libgcc -mwindows


.PHONY: all shaders dependencies common objects actors interface interface_text simulation main
all: main

#########################
#Build groups
#########################
shaders: shader.o
dependencies: glew.o
common: dependencies angles.o vector.o line.o plane.o sorting.o quaternion.o ../src/globals.h
objects: dependencies common actors texture.o vertex.o triangle.o mesh.o world.o
actors: dependencies common bone.o joint.o boneVertex.o skeleton.o
interface: common dependencies interface_text element.o interface.o
interface_text: common dependencies frameDelay.o
simulation: dependencies common objects interface shaders game.o
main: common simulation dependencies main.o

#########################
#Shader Section
#########################
shader.o: ../src/shaders/shader.cpp ../src/shaders/shader.h
	@echo -e '\t\t'Making shaders...
	@$(CC) $(CFLAGS) ../src/shaders/shader.cpp -o $@

#########################
#Dependencies section
#########################
glew.o: ../deps/GL/glew.c ../deps/GL/glew.h
	@echo -e '\t\t'Making glew...
	@$(CC) $(CFLAGS) ../deps/GL/glew.c -o $@

#########################
#Common Section
#########################
angles.o: ../src/common/angles.cpp ../src/common/angles.h
	@echo -e '\t\t'Making angles...
	@$(CC) $(CFLAGS) ../src/common/angles.cpp -o $@

line.o: ../src/common/line.cpp ../src/common/line.h
	@echo -e '\t\t'Making line...
	@$(CC) $(CFLAGS) ../src/common/line.cpp -o $@

plane.o: ../src/common/plane.cpp ../src/common/plane.h
	@echo -e '\t\t'Making plane...
	@$(CC) $(CFLAGS) ../src/common/plane.cpp -o $@

sorting.o: ../src/common/sorting.cpp ../src/common/sorting.h
	@echo -e '\t\t'Making sorting...
	@$(CC) $(CFLAGS) ../src/common/sorting.cpp -o $@

vector.o: ../src/common/vector.cpp ../src/common/vector.h
	@echo -e '\t\t'Making vector...
	@$(CC) $(CFLAGS) ../src/common/vector.cpp -o $@

quaternion.o: ../src/common/quaternion.cpp ../src/common/quaternion.h
	@echo -e '\t\t'Making quaternion...
	@$(CC) $(CFLAGS) ../src/common/quaternion.cpp -o $@

#########################
#Actor Section
#########################
bone.o: ../src/objects/actors/bone.cpp ../src/objects/actors/bone.h ../src/globals.h
	@echo -e '\t\t'Making bone...
	@$(CC) $(CFLAGS) ../src/objects/actors/bone.cpp

joint.o: ../src/objects/actors/joint.cpp ../src/objects/actors/joint.h ../src/globals.h
	@echo -e '\t\t'Making joint...
	@$(CC) $(CFLAGS) ../src/objects/actors/joint.cpp

boneVertex.o: ../src/objects/actors/boneVertex.cpp ../src/objects/actors/boneVertex.h ../src/globals.h
	@echo -e '\t\t'Making boneVertex...
	@$(CC) $(CFLAGS) ../src/objects/actors/boneVertex.cpp

skeleton.o: ../src/objects/actors/skeleton.cpp ../src/objects/actors/skeleton.h ../src/globals.h
	@echo -e '\t\t'Making skeleton...
	@$(CC) $(CFLAGS) ../src/objects/actors/skeleton.cpp

#########################
#Object Section
#########################
texture.o: ../src/objects/texture.cpp ../src/objects/texture.h ../src/globals.h
	@echo -e '\t\t'Making texture...
	@$(CC) $(CFLAGS) ../src/objects/texture.cpp

vertex.o: ../src/objects/vertex.cpp ../src/objects/vertex.h ../src/globals.h
	@echo -e '\t\t'Making vertex...
	@$(CC) $(CFLAGS) ../src/objects/vertex.cpp

triangle.o: ../src/objects/triangle.cpp ../src/objects/triangle.h ../src/globals.h
	@echo -e '\t\t'Making triangle...
	@$(CC) $(CFLAGS) ../src/objects/triangle.cpp

mesh.o: ../src/objects/mesh.cpp ../src/objects/mesh.h ../src/globals.h
	@echo -e '\t\t'Making mesh...
	@$(CC) $(CFLAGS) ../src/objects/mesh.cpp

world.o: ../src/objects/world.cpp ../src/objects/world.h ../src/objects/light/light.h ../src/objects/light/direclight.h ../src/objects/light/spotlight.h ../src/globals.h
	@echo -e '\t\t'Making world...
	@$(CC) $(CFLAGS) ../src/objects/world.cpp

#########################
#Interface Section
#########################
element.o: ../src/interface/element.cpp ../src/interface/element.h ../src/globals.h
	@echo -e '\t\t'Making element...
	@$(CC) $(CFLAGS) ../src/interface/element.cpp

interface.o: ../src/interface/interface.cpp ../src/interface/interface.h ../src/globals.h
	@echo -e '\t\t'Making interface...
	@$(CC) $(CFLAGS) ../src/interface/interface.cpp

frameDelay.o: ../src/interface/text/frameDelay.cpp ../src/interface/text/frameDelay.h ../src/globals.h
	@echo -e '\t\t'Making frameDelay...
	@$(CC) $(CFLAGS) ../src/interface/text/frameDelay.cpp


#########################
#Simulation Section
#########################
game.o: ../src/simulation/game.cpp ../src/simulation/game.h ../src/globals.h
	@echo -e '\t\t'Making game...
	@$(CC) $(CFLAGS) ../src/simulation/game.cpp

#########################
#Main section
#########################
main.o: ../src/main.cpp
	@echo -e '\t\t'Making main...
	@$(CC) $(CFLAGS) $^ -o $@
