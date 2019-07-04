#version 330 core

layout(location = 0) in vec3 input_VertexPosition;


void main() {
	gl_Position = vec4(input_VertexPosition,1);
}

