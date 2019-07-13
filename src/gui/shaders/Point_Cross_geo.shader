#version 330 core
layout(points) in;
layout(line_strip, max_vertices = 8) out;
uniform float screenWidth;
uniform float screenHeight;
vec4 transfer(vec4 v)
{
	float x = v.x;
	float y = v.y;
	float xx = x / screenWidth * 2 - 1;
	float yy = 1 - y / screenHeight * 2;
	return vec4(xx,yy,v.z,v.w);
}

void main() {

	gl_Position = transfer(gl_in[0].gl_Position + vec4(0.0, 0.0, 0.0, 0.0));
	EmitVertex();

	gl_Position = transfer(gl_in[0].gl_Position + vec4(5, 0.0, 0.0, 0.0));
	EmitVertex();

	gl_Position = transfer(gl_in[0].gl_Position + vec4(0.0, 0.0, 0.0, 0.0));
	EmitVertex();

	gl_Position = transfer(gl_in[0].gl_Position + vec4(0.0, 5, 0.0, 0.0));
	EmitVertex();

	gl_Position = transfer(gl_in[0].gl_Position + vec4(0.0, 0.0, 0.0, 0.0));
	EmitVertex();

	gl_Position = transfer(gl_in[0].gl_Position + vec4(-5, 0.0, 0.0, 0.0));
	EmitVertex();

	gl_Position = transfer(gl_in[0].gl_Position + vec4(0.0, 0.0, 0.0, 0.0));
	EmitVertex();

	gl_Position = transfer(gl_in[0].gl_Position + vec4(0.0, -5, 0.0, 0.0));
	EmitVertex();

	EndPrimitive();
}