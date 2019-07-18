#version 330 core
layout(points) in;
layout(triangle_strip, max_vertices = 8) out;
uniform float screenWidth;
uniform float screenHeight;
uniform float angle = 0;
vec4 transfer(vec4 v)
{
	float x = v.x;
	float y = v.y;
	float xx = x / screenWidth * 2 - 1;
	float yy = 1 - y / screenHeight * 2;
	return vec4(xx,yy,v.z,v.w);
}

void main() {


	//float angle = 0;
	//float x = cos(angle);
	//float y = sin(angle);

	int segment = 3;
	float radius = 9;
	float pi = 3.14159265358;

	for (int i = 0; i <= segment; i++)
	{
		float a = i * 2 * pi / segment + angle;
		float x = radius * cos(a);
		float y = radius * sin(a);
		gl_Position = transfer(gl_in[0].gl_Position + vec4(x, y, 0.0, 0.0));
		EmitVertex();
	}

	//gl_Position = transfer(gl_in[0].gl_Position + vec4(5.0, 0.0, 0.0, 0.0));
	//EmitVertex();

	//gl_Position = transfer(gl_in[0].gl_Position + vec4(0.0, 5.0, 0.0, 0.0));
	//EmitVertex();

	//gl_Position = transfer(gl_in[0].gl_Position + vec4(-5.0, 0.0, 0.0, 0.0));
	//EmitVertex();

	//gl_Position = transfer(gl_in[0].gl_Position + vec4(0.0, -5.0, 0.0, 0.0));
	//EmitVertex();

	//gl_Position = transfer(gl_in[0].gl_Position + vec4(5.0, 0.0, 0.0, 0.0));
	//EmitVertex();



	EndPrimitive();
}