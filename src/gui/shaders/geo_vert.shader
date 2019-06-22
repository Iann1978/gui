#version 330 core

uniform mat4 mvp;

layout(location = 0) in vec3 input_VertexPosition;
layout(location = 1) in vec2 input_VertexTexcoord;

out vec2 VertexTexcoord;

void main() 
{
	gl_Position = mvp * vec4(input_VertexPosition.xyz,1);
	VertexTexcoord = input_VertexTexcoord;
}

