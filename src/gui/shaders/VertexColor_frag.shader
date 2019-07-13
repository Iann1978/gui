#version 330 core

uniform vec4 mainColor;
in vec4 VertexColor;
out vec4 color;

void main(){
	color = VertexColor;
}