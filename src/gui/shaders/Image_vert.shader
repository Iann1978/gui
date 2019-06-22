#version 330 core

uniform vec4 rect;
uniform float screenWidth;
uniform float screenHeight;

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 input_VertexPosition;
layout(location = 1) in vec2 input_VertexTexcoord;

// Output data ; will be interpolated for each fragment.
out vec2 VertexTexcoord;

void main() {

	// Output position of the vertex, in clip space : MVP * position
	float x = input_VertexPosition.x;
	float y = input_VertexPosition.y;
	float xx = (rect.x + x * rect.z)/screenWidth*2 - 1;
	float yy = 1-(rect.y + y * rect.w)/screenHeight*2;
	gl_Position = vec4(xx,yy,0,1);

	// UV of the vertex. No special space for this one.
	VertexTexcoord = input_VertexTexcoord;
}

