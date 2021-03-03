#version 450

out vec4 FragColor;
const float offset = 1.0 / 128.0;
in vec2 uvs;
uniform sampler2D colourTexture;
vec2 blurKernel[9] = {	vec2(-1.0, -1.0),
						vec2( 0.0, -1.0),
						vec2( 1.0, -1.0),
						vec2(-1.0,  0.0),
						vec2( 0.0,  0.0),
						vec2( 1.0,  0.0),
						vec2(-1.0,  1.0),
						vec2( 0.0,  1.0),
						vec2( 1.0,  1.0)
					};

void main()
{
	float thickness = 1.0;
	vec2 multiplier = thickness * 1.0 / textureSize(colourTexture, 0);
	vec4 color = texture(colourTexture, uvs);
	
	float total = 0.0;
	float alpha = 0.0;
	
	for (int xOff = -1; xOff <= 1; xOff++)
	{
		for (int yOff = -1 ; yOff <= 1; yOff++)
		{
			if (
				(uvs + vec2(xOff, yOff) * multiplier).x >= 0 && 
				(uvs + vec2(xOff, yOff) * multiplier).x <= 1.0 && 
				(uvs + vec2(xOff, yOff) * multiplier).y >= 0 && 
				(uvs + vec2(xOff, yOff) * multiplier).y <= 1.0
			)
			{
				alpha += texture(colourTexture, uvs + vec2(xOff, yOff) * multiplier).a;
				total += 1.0;
			}
		}
	}
	
	alpha -= color.a * total;

	vec4 final_color;
	if (color.a < 1.0 && alpha > 0.0) {
		final_color = vec4(0.0, 1.0, 0.0, 1.0);
	} else {
		final_color = color;
	}

	FragColor = final_color;
}