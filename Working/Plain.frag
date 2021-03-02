#version 450

uniform sampler2D defaultTexture;

out vec4 FragColor;

// color
in vec3 Color;

// texture
in vec2 UVs;
uniform sampler2D diffuseTexture;
uniform sampler2D specularTexture;
uniform sampler2D normalTexture;

// diffuse
in vec4 WorldPos;
// in vec4 MeshNormal;

// point light
uniform vec3 lightPositions[16];
uniform vec3 lightIntensities[16];
uniform int lightCount;

// ambient light
uniform vec3 ambientLightIntensity;
uniform vec3 ka;
// uniform vec3 lightPos;
// uniform vec3 lightIntensity;

// diffuse coefficient
uniform vec3 kd;

uniform mat4 modelMatrix;

// ambient
// uniform vec4 ambientColor;

// specular
// uniform vec4 specularColor;
uniform vec3 cameraPos;
uniform float specularPower;
uniform vec3 ks;

// normal
in mat3 tbn;

vec4 calculateNormal()
{
	vec4 normalTap = texture(normalTexture, UVs);
	vec3 mapNormal = normalTap.xyz * 2 - 1;
	return normalize(vec4(tbn * mapNormal, 0));
}

vec4 calculateAmbientLighting()
{
	return vec4(ambientLightIntensity, 1.0) * vec4(ka, 1.0);
}

vec4 calculateDiffuseLighting(vec4 toLight, vec4 normal, float attenuation, vec3 lightIntensity)
{
	vec4 diffuseColor = texture(diffuseTexture, UVs);
	float diffuseLevel = max(0.0, dot(toLight, normal));
	vec4 diffuseTerm = vec4(kd, 1.0) * vec4(lightIntensity, 1) * attenuation * diffuseLevel;
	return diffuseTerm * diffuseColor;
}

vec4 calculateSpecularLighting(vec4 toLight, vec4 normal, float attenuation, vec3 lightIntensity)
{
	vec4 specularColor = texture(specularTexture, UVs);
	vec4 toCamera = normalize(vec4(cameraPos, 1.0) - WorldPos);
	vec4 reflection = reflect(-toLight, normal);
	float specularLevel = pow(max(0.0, dot(toCamera, reflection)), specularPower);
	vec4 specularTerm = vec4(ks, 1.0) * vec4(lightIntensity, 1) * attenuation * specularLevel;
	return specularTerm * specularColor;
}

void main()
{
	
	vec4 normal = calculateNormal();
	vec4 result = {0.0, 0.0, 0.0, 0.0};
	for(int i = 0; i < lightCount; i++)
	{
		vec4 toLight = normalize(vec4(lightPositions[i], 1.0) - WorldPos);
		float lightDistSquared = dot(vec4(lightPositions[i], 1.0) - WorldPos, vec4(lightPositions[i], 1.0) - WorldPos);
		float attenuation = 1.0 / lightDistSquared;
		
		vec4 diffuseTerm = calculateDiffuseLighting(toLight, normal, attenuation, lightIntensities[i]);
		vec4 specularTerm = calculateSpecularLighting(toLight, normal, attenuation, lightIntensities[i]);
		
		result += diffuseTerm;
		result += specularTerm;
	}
	vec4 ambientTerm = calculateAmbientLighting();
	result += ambientTerm;
	FragColor = result;
}