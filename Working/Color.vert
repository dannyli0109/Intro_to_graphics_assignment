#version 450
layout (location = 0) in vec3 Position;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

void main()
{
	gl_Position = (projectionMatrix * viewMatrix * modelMatrix) * vec4(Position, 1);
}