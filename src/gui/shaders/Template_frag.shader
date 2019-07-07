#version 330 core

/*
	x: width of base texture
	y:height of base texture
	z:width of template texture
	w:height of template texture
*/
uniform int baseWidth;
uniform int baseHeight;
uniform int templateWidth;
uniform int templateHeight;
uniform sampler2D baseTexture;
uniform sampler2D templateTexture;

in vec2 VertexTexcoord;

// Ouput data
out vec4 outColor;




void main(){

	vec4 newColor = vec4(0,0,0,0);

	for (int i = -templateWidth/2; i < templateWidth/2; i++)
	{
		for (int j = -templateHeight/2; j < templateHeight/2; j++)
		{
			vec2 baseTexcoord = VertexTexcoord +vec2(1.0f * i / baseWidth, 1.0f * j / baseHeight);
			vec2 templateTexcoord = vec2(1.0f * i / templateWidth, 1.0f * j / templateHeight);
			vec4 baseColor = texture(baseTexture, baseTexcoord);
			vec4 templateColor = texture(templateTexture, templateTexcoord);
			newColor += baseColor * templateColor;
			//newColor = vec4(1.0f*baseWidth/1100, 1.0f*baseHeight/1100,0, 1);
		}
	}
		
	outColor = newColor;
	outColor.a = 0.2;
	//outColor = vec4(1, 0, 0, 1);
}