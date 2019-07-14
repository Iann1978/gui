#version 330 core

layout(lines) in;
layout(triangle_strip, max_vertices = 4) out;
out vec3 VertexColor;
in vec3 vColor[];

uniform float screenWidth;
uniform float screenHeight;
uniform float width = 1;
vec4 transfer(vec4 v)
{
	float x = v.x;
	float y = v.y;
	float xx = x / screenWidth * 2 - 1;
	float yy = 1 - y / screenHeight * 2;
	return vec4(xx, yy, v.z, v.w);
}

void main()
{

	float r = width/2;
	vec4 p1 = gl_in[0].gl_Position;
	vec4 p2 = gl_in[1].gl_Position;
	
	VertexColor = vColor[0];
	vec2 dir = normalize(p2.xy - p1.xy);
	vec2 normal = vec2(dir.y, -dir.x);

	vec4 offset1, offset2;
	offset1 = vec4(normal * r, 0, 0);
	offset2 = vec4(normal * r, 0, 0);

	vec4 coords[4];
	coords[0] = p1 + offset1;
	coords[1] = p1 - offset1;
	coords[2] = p2 + offset2;
	coords[3] = p2 - offset2;

	for (int i = 0; i < 4; ++i) {
		gl_Position = transfer(coords[i]);
		EmitVertex();
	}
	EndPrimitive();
}