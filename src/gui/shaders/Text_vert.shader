#version 330 core

uniform float screenWidth;
uniform float screenHeight;

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec2 vertexPosition_screenspace;
layout(location = 1) in vec2 vertexUV;

// Output data ; will be interpolated for each fragment.
out vec2 UV;

void main(){

	// Output position of the vertex, in clip space
	// map [0..800][0..600] to [-1..1][-1..1]
	float xx = vertexPosition_screenspace.x / screenWidth * 2 - 1;
	float yy = 1 - vertexPosition_screenspace.y / screenHeight * 2;

	//vec2 vertexPosition_homoneneousspace = vertexPosition_screenspace - vec2(400,300); // [0..800][0..600] -> [-400..400][-300..300]
	//vertexPosition_homoneneousspace /= vec2(400,300);
	gl_Position =  vec4(xx,yy,0,1);
	
	// UV of the vertex. No special space for this one.
	UV = vertexUV;
}

