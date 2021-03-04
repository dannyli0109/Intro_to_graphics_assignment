#version 450

uniform sampler2D defaultTexture;

out vec4 FragColor;


// diffuse
in vec4 WorldPos;
in vec4 MeshNormal;
uniform vec3 diffuseColor;

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
uniform vec3 specularColor;


vec4 calculateNormal()
{
	return normalize(MeshNormal);
}

vec4 calculateAmbientLighting()
{
	return vec4(ambientLightIntensity, 1.0) * vec4(ka, 1.0);
}

vec4 calculateDiffuseLighting(vec4 toLight, vec4 normal, float attenuation, vec3 lightIntensity)
{
	float diffuseLevel = max(0.0, dot(toLight, normal));
	vec4 diffuseTerm = vec4(kd, 1.0) * vec4(lightIntensity, 1) * attenuation * diffuseLevel;
	return diffuseTerm * vec4(diffuseColor, 1.0);
}

vec4 calculateSpecularLighting(vec4 toLight, vec4 normal, float attenuation, vec3 lightIntensity)
{
	vec4 toCamera = normalize(vec4(cameraPos, 1.0) - WorldPos);
	vec4 reflection = reflect(-toLight, normal);
	float specularLevel = pow(max(0.0, dot(toCamera, reflection)), specularPower);
	vec4 specularTerm = vec4(ks, 1.0) * vec4(lightIntensity, 1.0) * attenuation * specularLevel;
	return specularTerm * vec4(specularColor, 1.0);
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
	
	//vec4 toCamera = normalize(vec4(cameraPos, 1.0) - WorldPos);
	//float CameraFacingPercentage = dot(toCamera, normal);
	//FragColor = result * CameraFacingPercentage + vec4(0, 1, 0, 0) * (1 - CameraFacingPercentage);
	FragColor = result;
}