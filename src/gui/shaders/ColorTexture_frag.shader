#version 330 core

// Uniform data
uniform sampler2D baseTexture;
uniform vec4 color = vec4(1, 1, 1, 1);

// Input data
in vec2 VertexTexcoord;

// Ouput data
out vec4 outColor;


void main(){
	outColor = texture(baseTexture, VertexTexcoord).rgba * color;
}