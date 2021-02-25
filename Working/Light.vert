#version 450

layout (location = 0) in vec3 Position;
layout (location = 4) in vec3 VertColor;
out vec3 Color;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

void main()
{
	Color = VertColor;
	gl_Position = (projectionMatrix * viewMatrix * modelMatrix) * vec4(Position, 1);
}