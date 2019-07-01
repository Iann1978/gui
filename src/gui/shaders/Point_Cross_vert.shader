#version 330 core

uniform float screenWidth;
uniform float screenHeight;

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 input_VertexPosition;


void main() {

	// Output position of the vertex, in clip space : MVP * position
	float x = input_VertexPosition.x;
	float y = input_VertexPosition.y;
	float xx = x/screenWidth*2 - 1;
	float yy = 1-y/screenHeight*2;
	gl_Position = vec4(xx,yy,0,1);
	//gl_Position = vec4(input_VertexPosition, 1);

}

