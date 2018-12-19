//[VERTEX SHADER]
#version 330 core
layout(location = 0) in vec4 gl_Vertex;
layout(location = 1) in vec3 gl_Normal;
layout(location = 2) in vec4 gl_Color;
layout(location = 3) in vec4 col;
layout(location = 4) in vec2 TexCoord;

out VERTEXOUT{
	vec4 color;
	float light;
	vec2 texcoord;
}vertexout;

uniform mat4 gl_ModelViewMatrix;
uniform mat4 ViewMatrix;
uniform mat4 gl_ModelViewProjectionMatrix;

uniform vec3 light_position;

void main(){
	float ambient = 0.1;
	float intensity = 25.0;

	vec4 clip_position = gl_ModelViewMatrix * gl_Vertex;
	mat4 NormalMatrix = transpose(inverse(gl_ModelViewMatrix));
	vec3 eye = (NormalMatrix * vec4(gl_Normal, 0.0)).xyz;
	vec3 light = light_position - clip_position.xyz;

	float distance = pow(pow(gl_Vertex.x-light.x, 2) + pow(gl_Vertex.y-light.y, 2) + pow(gl_Vertex.z-light.z, 2), 0.5);
	float diffuse = max(dot(normalize(eye), normalize(light)), 0.0) * intensity * (1.0 / (1.0 + (0.25 * pow(distance,2))));

	gl_Position = gl_ModelViewProjectionMatrix * ViewMatrix * clip_position;
	vertexout.color = col;
	vertexout.light = max(min(diffuse,1.0), ambient);
	vertexout.texcoord = TexCoord;
}