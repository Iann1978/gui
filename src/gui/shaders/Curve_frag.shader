#version 330 core

in vec3 VertexColor;

// Ouput data
out vec4 color;



void main(){
	color = vec4(VertexColor, 1);
	
}