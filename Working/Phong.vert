#version 450

layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 VertNormal;
layout (location = 2) in vec3 VertTangent;
layout (location = 3) in vec3 VertBitangent;
layout (location = 4) in vec3 VertColor;
layout (location = 5) in vec2 VertUVs;

out vec3 Color;
out vec2 UVs;
out vec4 MeshNormal;
out vec4 WorldPos;

out mat3 tbn;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;


void main()
{
	Color = VertColor;
	UVs = VertUVs;
	
	vec3 t = normalize(vec3(modelMatrix * vec4(VertTangent, 0.0)));
	vec3 n = normalize(vec3(modelMatrix * vec4(VertNormal, 0.0)));
	t = normalize(t - dot(t,n) * n);
	vec3 b = cross(n, t);
	tbn = mat3(
		t, b, n
	);
	WorldPos = modelMatrix * vec4(Position,1);
	gl_Position = (projectionMatrix * viewMatrix * modelMatrix) * vec4(Position, 1);
}