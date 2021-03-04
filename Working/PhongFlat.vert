#version 450

layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 VertNormal;
layout (location = 2) in vec3 VertTangent;
layout (location = 3) in vec3 VertBitangent;
layout (location = 4) in vec3 VertColor;
layout (location = 5) in vec2 VertUVs;


out vec4 MeshNormal;
out vec4 WorldPos;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;


void main()
{
	WorldPos = modelMatrix * vec4(Position,1);
	MeshNormal = transpose(inverse(modelMatrix)) * vec4(VertNormal, 0.0);
	
	gl_Position = (projectionMatrix * viewMatrix * modelMatrix) * vec4(Position, 1);
}