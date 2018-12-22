CC = g++
CFLAGS = -Wall -Wno-psabi -Wno-write-strings -Wno-narrowing -g -c

.PHONY: all dependencies common objects actors interface interface_text simulation main clean

all:
	$(MAKE) dependencies --no-print-directory
	$(MAKE) common --no-print-directory
	$(MAKE) objects --no-print-directory
	$(MAKE) actors --no-print-directory
	$(MAKE) interface --no-print-directory
	$(MAKE) interface_text --no-print-directory
	$(MAKE) simulation --no-print-directory
	$(MAKE) main --no-print-directory

#########################
#Build groups
#########################
dependencies:
common: angles.o vector.o line.o plane.o sorting.o quaternion.o
objects: common dependencies texture.o vertex.o triangle.o mesh.o world.o
actors: common dependencies bone.o joint.o boneVertex.o skeleton.o
interface: common dependencies element.o interface.o
interface_text: common dependencies frameDelay.o
simulation: common interface_text interface actors objects dependencies game.o shader.o
main: simulation dependencies main.o

#########################
#Dependencies Section
#########################

#########################
#Common Section
#########################
angles.o: ../src/common/angles.cpp ../src/common/angles.h
	$(CC) $(CFLAGS) ../src/common/angles.cpp

line.o: ../src/common/line.cpp ../src/common/line.h
	$(CC) $(CFLAGS) ../src/common/line.cpp

plane.o: ../src/common/plane.cpp ../src/common/plane.h
	$(CC) $(CFLAGS) ../src/common/plane.cpp

sorting.o: ../src/common/sorting.cpp ../src/common/sorting.h
	$(CC) $(CFLAGS) ../src/common/sorting.cpp

vector.o: ../src/common/vector.cpp ../src/common/vector.h
	$(CC) $(CFLAGS) ../src/common/vector.cpp

quaternion.o: ../src/common/quaternion.cpp ../src/common/quaternion.h
	$(CC) $(CFLAGS) ../src/common/quaternion.cpp

#########################
#Actor Section
#########################
bone.o: ../src/objects/actors/bone.cpp ../src/objects/actors/bone.h
	$(CC) $(CFLAGS) ../src/objects/actors/bone.cpp

joint.o: ../src/objects/actors/joint.cpp ../src/objects/actors/joint.h
	$(CC) $(CFLAGS) ../src/objects/actors/joint.cpp

boneVertex.o: ../src/objects/actors/boneVertex.cpp ../src/objects/actors/boneVertex.h
	$(CC) $(CFLAGS) ../src/objects/actors/boneVertex.cpp

skeleton.o: ../src/objects/actors/skeleton.cpp ../src/objects/actors/skeleton.h
	$(CC) $(CFLAGS) ../src/objects/actors/skeleton.cpp

#########################
#Object Section
#########################
texture.o: ../src/objects/texture.cpp ../src/objects/texture.h
	$(CC) $(CFLAGS) ../src/objects/texture.cpp

vertex.o: ../src/objects/vertex.cpp ../src/objects/vertex.h
	$(CC) $(CFLAGS) ../src/objects/vertex.cpp

triangle.o: ../src/objects/triangle.cpp ../src/objects/triangle.h
	$(CC) $(CFLAGS) ../src/objects/triangle.cpp

mesh.o: ../src/objects/mesh.cpp ../src/objects/mesh.h
	$(CC) $(CFLAGS) ../src/objects/mesh.cpp

world.o: ../src/objects/world.cpp ../src/objects/world.h
	$(CC) $(CFLAGS) ../src/objects/world.cpp

#########################
#Interface Section
#########################
element.o: ../src/interface/element.cpp ../src/interface/element.h
	$(CC) $(CFLAGS) ../src/interface/element.cpp

interface.o: ../src/interface/interface.cpp ../src/interface/interface.h
	$(CC) $(CFLAGS) ../src/interface/interface.cpp

frameDelay.o: ../src/interface/text/frameDelay.cpp ../src/interface/text/frameDelay.h
	$(CC) $(CFLAGS) ../src/interface/text/frameDelay.cpp

#########################
#Simulation Section
#########################
game.o: ../src/simulation/game.cpp ../src/simulation/game.h
	$(CC) $(CFLAGS) ../src/simulation/game.cpp

shader.o: ../src/shader/shader.cpp ../src/shader/shader.h
	$(CC) $(CFLAGS) ../src/shader/shader.cpp

#########################
#Main section
#########################
main.o: ../src/main.cpp
	$(CC) $(CFLAGS) ../src/main.cpp

clean:
	cmd.exe /c del *.o