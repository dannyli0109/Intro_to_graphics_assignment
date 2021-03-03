#version 450
layout (location = 0) in vec2 Position;
layout (location = 5) in vec2 UVs;

out vec2 uvs;
void main()
{
	uvs = vec2(UVs.x, 1.0 - UVs.y);
	gl_Position = vec4(Position * 2.0, 0, 1);
}