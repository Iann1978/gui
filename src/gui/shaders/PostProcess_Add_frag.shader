#version 330 core

in vec2 VertexTexcoord;

// Ouput data
out vec4 color;

uniform sampler2D texture0;
uniform sampler2D texture1;


void main(){
	vec4 p0 = texture(texture0, VertexTexcoord);
	vec4 p1 = texture(texture1, VertexTexcoord);
	color = (p0+0.45)*(p0+0.45) + p1;
	color.a = 1;
}