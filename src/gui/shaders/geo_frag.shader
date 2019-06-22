#version 330 core

in vec2 VertexTexcoord;

// Ouput data
out vec4 color;

uniform sampler2D myTextureSampler;
uniform float status;

void main(){
	color = texture(myTextureSampler, VertexTexcoord).rgba + vec4(status, status, status, 0);
	// Output color = color of the texture at the specified UV
	//color = vec3(1, 0, 0);
}