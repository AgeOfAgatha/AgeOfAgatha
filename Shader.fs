//[FRAGMENT SHADER]
#version 330 core
in VERTEXOUT{
	vec4 color;
	float light;
	vec2 texcoord;
	float blend;
}fragmentin;

out vec4 color;

uniform int texture1set;
uniform sampler2D texture1;
uniform int texture2set;
uniform sampler2D texture2;

void main(){
	vec4 vertcolor = vec4(fragmentin.color[0]*fragmentin.light, fragmentin.color[1]*fragmentin.light, fragmentin.color[2]*fragmentin.light, fragmentin.color[3]);
	if (texture1set == 1 || texture2set == 1){
		if (texture1set == 1 && texture2set != 1){
			color = texture(texture1, fragmentin.texcoord) * vertcolor;
		}
		if (texture1set != 1 && texture2set == 1){
			color = texture(texture1, fragmentin.texcoord) * vertcolor;
		}
		if (texture1set == 1 && texture2set == 1){
			color = mix(texture(texture1, fragmentin.texcoord), texture(texture2, fragmentin.texcoord), fragmentin.blend) * vertcolor;
		}
	}else{
		color = vertcolor;
	}
}