#version 330 core


// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 input_VertexPosition;
layout(location = 1) in vec2 input_VertexTexcoord;

// Output data ; will be interpolated for each fragment.
out vec2 VertexTexcoord;

void main() {
	gl_Position = vec4(input_VertexPosition,1);
	VertexTexcoord = input_VertexTexcoord;
}

