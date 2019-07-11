#version 330 core

in vec2 VertexTexcoord;

// Ouput data
out vec4 outColor;

uniform sampler2D myTextureSampler;
uniform float status = 0;
uniform vec4 color = vec4(1,1,1,1);

void main(){
	outColor = texture(myTextureSampler, VertexTexcoord).rgba + vec4(status, status, status, 0);
	outColor *= color;
	//outColor = vec4(1, 0, 0, 1);
	// Output color = color of the texture at the specified UV
	//color = vec3(1, 0, 0);
}