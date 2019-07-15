#version 330 core
layout(points) in;
layout(line_strip, max_vertices = 33) out;

uniform float screenWidth;
uniform float screenHeight;
uniform float radius = 20;
uniform float startAngle = 0;
uniform float endAngle = 6.28318530716;

vec4 transfer(vec4 v)
{
	float x = v.x;
	float y = v.y;
	float xx = x / screenWidth * 2 - 1;
	float yy = 1 - y / screenHeight * 2;
	return vec4(xx,yy,v.z,v.w);
}

void main() {

	float angle = 0;
	float x = cos(angle);
	float y = sin(angle);
	float pi = 3.14159265358;

	int count = 32;

	for (int i = 0; i <= count; i++)
	{
		angle = startAngle + i * (endAngle-startAngle) / count;
		float x = radius * cos(angle);
		float y = radius * sin(angle);
		gl_Position = transfer(gl_in[0].gl_Position + vec4(x, y, 0.0, 0.0));
		EmitVertex();
	}

	EndPrimitive();
}