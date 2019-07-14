#version 330 core

in vec3 VertexColor;
in vec3 VertexColor1;
// Ouput data
out vec4 color;



void main(){
	color = vec4(VertexColor, 1);
	
}