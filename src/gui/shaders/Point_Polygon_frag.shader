#version 330 core

uniform vec3 centerColor;

// Ouput data
out vec4 outColor;



void main(){
	outColor = vec4(centerColor,1);
}