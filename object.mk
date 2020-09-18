.PHONY: all shaders dependencies common objects actors interface interface_text simulation main
all: main

#########################
#Build groups
#########################
shaders: shader.o
dependencies: glew.o
renderer: renderer-deps render.o
renderer-deps: fps_counter.o scene.o GLee.o COLOR.o MATRIX4X4.o PLANE.o VECTOR2D.o VECTOR3D.o VECTOR4D.o
common: dependencies angles.o vector.o line.o plane.o sorting.o quaternion.o ../../src/globals.h
objects: dependencies common actors texture.o vertex.o triangle.o mesh.o world.o
actors: dependencies common bone.o joint.o boneVertex.o skeleton.o
interface: common dependencies interface_text element.o interface.o
interface_text: common dependencies frameDelay.o
simulation: dependencies common objects interface shaders game.o
main:  common simulation dependencies renderer main.o  

#########################
#Renderer Section
#########################
render.o: ../../src/renderer/render.cpp ../../src/renderer/render.h
	@echo -e '\t\t'Making renderer...
	@$(CC) $(CFLAGS) ../../src/renderer/render.cpp -o $@

fps_counter.o: ../../src/renderer/fps_counter.cpp ../../src/renderer/fps_counter.h
	@echo -e '\t\t'Making fps counter...
	@$(CC) $(CFLAGS) ../../src/renderer/fps_counter.cpp -o $@

scene.o: ../../src/renderer/scene.cpp ../../src/renderer/scene.h
	@echo -e '\t\t'Making scene...
	@$(CC) $(CFLAGS) ../../src/renderer/scene.cpp -o $@

GLee.o: ../../deps/GL/GLee.c ../../deps/GL/GLee.h
	@echo -e '\t\t'Making GLee...
	@$(CC) $(CFLAGS) ../../deps/GL/GLee.c -o $@

ARB_multitexture_extension.o: ../../src/renderer/Extensions/ARB_multitexture_extension.cpp ../../src/renderer/Extensions/ARB_multitexture_extension.h
	@echo -e '\t\t'Making ARB_multitexture_extension...
	@$(CC) $(CFLAGS) ../../src/renderer/Extensions/ARB_multitexture_extension.cpp -o $@

EXT_texture_env_combine_extension.o: ../../src/renderer/Extensions/EXT_texture_env_combine_extension.cpp ../../src/renderer/Extensions/EXT_texture_env_combine_extension.h
	@echo -e '\t\t'Making EXT_texture_env_combine_extension...
	@$(CC) $(CFLAGS) ../../src/renderer/Extensions/EXT_texture_env_combine_extension.cpp -o $@
	
COLOR.o: ../../src/renderer/Maths/COLOR.cpp ../../src/renderer/Maths/COLOR.h
	@echo -e '\t\t'Making COLOR...
	@$(CC) $(CFLAGS) ../../src/renderer/Maths/COLOR.cpp -o $@
	
MATRIX4X4.o: ../../src/renderer/Maths/MATRIX4X4.cpp ../../src/renderer/Maths/MATRIX4X4.h
	@echo -e '\t\t'Making MATRIX4X4...
	@$(CC) $(CFLAGS) ../../src/renderer/Maths/MATRIX4X4.cpp -o $@
	
PLANE.o: ../../src/renderer/Maths/PLANE.cpp ../../src/renderer/Maths/PLANE.h
	@echo -e '\t\t'Making PLANE...
	@$(CC) $(CFLAGS) ../../src/renderer/Maths/PLANE.cpp -o $@
	
VECTOR2D.o: ../../src/renderer/Maths/VECTOR2D.cpp ../../src/renderer/Maths/VECTOR2D.h
	@echo -e '\t\t'Making VECTOR2D...
	@$(CC) $(CFLAGS) ../../src/renderer/Maths/VECTOR2D.cpp -o $@
	
VECTOR3D.o: ../../src/renderer/Maths/VECTOR3D.cpp ../../src/renderer/Maths/VECTOR3D.h
	@echo -e '\t\t'Making VECTOR3D...
	@$(CC) $(CFLAGS) ../../src/renderer/Maths/VECTOR3D.cpp -o $@
	
VECTOR4D.o: ../../src/renderer/Maths/VECTOR4D.cpp ../../src/renderer/Maths/VECTOR4D.h
	@echo -e '\t\t'Making VECTOR4D...
	@$(CC) $(CFLAGS) ../../src/renderer/Maths/VECTOR4D.cpp -o $@
#########################
#Shader Section
#########################
shader.o: ../../src/shaders/shader.cpp ../../src/shaders/shader.h
	@echo -e '\t\t'Making shaders...
	@$(CC) $(CFLAGS) ../../src/shaders/shader.cpp -o $@

#########################
#Dependencies section
#########################
glew.o: ../../deps/GL/glew.c ../../deps/GL/glew.h
	@echo -e '\t\t'Making glew...
	@$(CC) $(CFLAGS) ../../deps/GL/glew.c -o $@

#########################
#Common Section
#########################
angles.o: ../../src/common/angles.cpp ../../src/common/angles.h
	@echo -e '\t\t'Making angles...
	@$(CC) $(CFLAGS) ../../src/common/angles.cpp -o $@

line.o: ../../src/common/line.cpp ../../src/common/line.h
	@echo -e '\t\t'Making line...
	@$(CC) $(CFLAGS) ../../src/common/line.cpp -o $@

plane.o: ../../src/common/plane.cpp ../../src/common/plane.h
	@echo -e '\t\t'Making plane...
	@$(CC) $(CFLAGS) ../../src/common/plane.cpp -o $@

sorting.o: ../../src/common/sorting.cpp ../../src/common/sorting.h
	@echo -e '\t\t'Making sorting...
	@$(CC) $(CFLAGS) ../../src/common/sorting.cpp -o $@

vector.o: ../../src/common/vector.cpp ../../src/common/vector.h
	@echo -e '\t\t'Making vector...
	@$(CC) $(CFLAGS) ../../src/common/vector.cpp -o $@

quaternion.o: ../../src/common/quaternion.cpp ../../src/common/quaternion.h
	@echo -e '\t\t'Making quaternion...
	@$(CC) $(CFLAGS) ../../src/common/quaternion.cpp -o $@

#########################
#Actor Section
#########################
bone.o: ../../src/objects/actors/bone.cpp ../../src/objects/actors/bone.h
	@echo -e '\t\t'Making bone...
	@$(CC) $(CFLAGS) ../../src/objects/actors/bone.cpp

joint.o: ../../src/objects/actors/joint.cpp ../../src/objects/actors/joint.h
	@echo -e '\t\t'Making joint...
	@$(CC) $(CFLAGS) ../../src/objects/actors/joint.cpp

boneVertex.o: ../../src/objects/actors/boneVertex.cpp ../../src/objects/actors/boneVertex.h
	@echo -e '\t\t'Making boneVertex...
	@$(CC) $(CFLAGS) ../../src/objects/actors/boneVertex.cpp

skeleton.o: ../../src/objects/actors/skeleton.cpp ../../src/objects/actors/skeleton.h
	@echo -e '\t\t'Making skeleton...
	@$(CC) $(CFLAGS) ../../src/objects/actors/skeleton.cpp

#########################
#Object Section
#########################
texture.o: ../../src/objects/texture.cpp ../../src/objects/texture.h
	@echo -e '\t\t'Making texture...
	@$(CC) $(CFLAGS) ../../src/objects/texture.cpp

vertex.o: ../../src/objects/vertex.cpp ../../src/objects/vertex.h
	@echo -e '\t\t'Making vertex...
	@$(CC) $(CFLAGS) ../../src/objects/vertex.cpp

triangle.o: ../../src/objects/triangle.cpp ../../src/objects/triangle.h
	@echo -e '\t\t'Making triangle...
	@$(CC) $(CFLAGS) ../../src/objects/triangle.cpp

mesh.o: ../../src/objects/mesh.cpp ../../src/objects/mesh.h
	@echo -e '\t\t'Making mesh...
	@$(CC) $(CFLAGS) ../../src/objects/mesh.cpp

world.o: ../../src/objects/world.cpp ../../src/objects/world.h ../../src/objects/light/light.h ../../src/objects/light/direclight.h ../../src/objects/light/spotlight.h
	@echo -e '\t\t'Making world...
	@$(CC) $(CFLAGS) ../../src/objects/world.cpp

#########################
#Interface Section
#########################
element.o: ../../src/interface/element.cpp ../../src/interface/element.h
	@echo -e '\t\t'Making element...
	@$(CC) $(CFLAGS) ../../src/interface/element.cpp

interface.o: ../../src/interface/interface.cpp ../../src/interface/interface.h
	@echo -e '\t\t'Making interface...
	@$(CC) $(CFLAGS) ../../src/interface/interface.cpp

frameDelay.o: ../../src/interface/text/frameDelay.cpp ../../src/interface/text/frameDelay.h
	@echo -e '\t\t'Making frameDelay...
	@$(CC) $(CFLAGS) ../../src/interface/text/frameDelay.cpp


#########################
#Simulation Section
#########################
game.o: ../../src/simulation/game.cpp ../../src/simulation/game.h
	@echo -e '\t\t'Making game...
	@$(CC) $(CFLAGS) ../../src/simulation/game.cpp

#########################
#Main section
#########################
main.o: ../../src/main.cpp
	@echo -e '\t\t'Making main...
	@$(CC) $(CFLAGS) $^ -o $@
