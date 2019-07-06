#version 330 core

uniform float screenWidth;
uniform float screenHeight;

layout(location = 0) in vec3 input_VertexPosition;


void main() {


	float xx = input_VertexPosition.x / screenWidth * 2 - 1;
	float yy = 1 - input_VertexPosition.y / screenHeight * 2;
	gl_Position = vec4(xx,yy,0,1);
}

