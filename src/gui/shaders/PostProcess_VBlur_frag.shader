#version 330 core

in vec2 VertexTexcoord;

// Ouput data
out vec4 color;

uniform sampler2D myTextureSampler;
uniform float screenWidth;
uniform float screenHeight;

void main(){
	vec4 p = texture(myTextureSampler, VertexTexcoord);
	vec4 p0 = texture(myTextureSampler, vec2(VertexTexcoord.x, VertexTexcoord.y + 2 / screenHeight));
	vec4 p1 = texture(myTextureSampler, vec2(VertexTexcoord.x, VertexTexcoord.y - 2 / screenHeight));
	color = 0.5 * p + 0.25 * p0 + 0.25 * p1;
	color.a = 1;
	//color = vec4(1, 1, 0, 1);
}