main = ../../src/main.cpp
deps = ../../deps/GL/GLee.c
#includes = ../../src/common/vector.cpp ../../src/shaders/shader.cpp ../../src/renderer/render.cpp ../../src/renderer/fps_counter.cpp ../../src/renderer/scene.cpp ../../src/renderer/Extensions/ARB_multitexture_extension.cpp ../../src/renderer/Extensions/EXT_texture_env_combine_extension.cpp ../../src/renderer/Maths/COLOR.cpp ../../src/renderer/Maths/MATRIX4X4.cpp ../../src/renderer/Maths/PLANE.cpp ../../src/renderer/Maths/VECTOR2D.cpp ../../src/renderer/Maths/VECTOR3D.cpp ../../src/renderer/Maths/VECTOR4D.cpp ../../src/common/angles.cpp ../../src/common/line.cpp ../../src/common/plane.cpp ../../src/common/sorting.cpp ../../src/common/quaternion.cpp ../../src/objects/actors/bone.cpp ../../src/objects/actors/joint.cpp ../../src/objects/actors/boneVertex.cpp ../../src/objects/actors/skeleton.cpp ../../src/objects/texture.cpp ../../src/objects/vertex.cpp ../../src/objects/triangle.cpp ../../src/objects/mesh.cpp ../../src/objects/world.cpp ../../src/interface/element.cpp ../../src/interface/interface.cpp ../../src/interface/text/frameDelay.cpp ../../src/simulation/game.cpp
.PHONY: all
all:
	@echo -e '\t\t'Making dependencies...
	@../../scripts/deps.sh $(deps) $(CC) $(CFLAGS)
	@echo -e '\t\t'Making source...
	@../../scripts/includes.sh $(main) $(CC) $(CFLAGS)
	@touch *
