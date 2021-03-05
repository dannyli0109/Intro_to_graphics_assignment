#include "PhongFlatShadingMaterial.h"
#include "ShaderProgram.h"

/**
 * Phong flat shading material does phong lighting using color only.
 *
 * \param ka represents the ambient reflectivity
 * \param kd represents the diffuse reflectivity
 * \param ks represents the specular reflectivity
 * \param specularPower represents the specular exponent
 * \param diffuseColor represents the diffuse color for the material
 * \param specularColor represents the specular color for the material
 */
PhongFlatShadingMaterial::PhongFlatShadingMaterial(glm::vec3 ka, glm::vec3 kd, glm::vec3 ks, float specularPower, glm::vec3 diffuseColor, glm::vec3 specularColor) : Material()
{
	this->name = "Phong Flat Shading Material";
	this->ka = ka;
	this->kd = kd;
	this->ks = ks;
	this->specularPower = specularPower;
	this->diffuseColor = diffuseColor;
	this->specularColor = specularColor;

	this->shader = ResourceManager::GetInstance()->GetShader("phongFlat");
}

void PhongFlatShadingMaterial::OnDraw()
{
	shader->SetUniform("ka", ka);
	shader->SetUniform("kd", kd);
	shader->SetUniform("ks", ks);
	shader->SetUniform("specularPower", specularPower);
	shader->SetUniform("diffuseColor", diffuseColor);
	shader->SetUniform("specularColor", specularColor);

}

void PhongFlatShadingMaterial::DrawGui()
{
	ImGui::SliderFloat("Ka", &ka.x, 0.0f, 1.0f);
	ka.y = ka.x;
	ka.z = ka.x;
	ImGui::SliderFloat("Kd", &kd.x, 0.0f, 1.0f);
	kd.y = kd.x;
	kd.z = kd.x;
	ImGui::SliderFloat("Ks", &ks.x, 0.0f, 1.0f);
	ks.y = ks.x;
	ks.z = ks.x;
	ImGui::SliderFloat("Specular Power", &specularPower, 0.01f, 512.0f);
	ImGui::ColorEdit3("Albedo", &diffuseColor.x);
	ImGui::ColorEdit3("Specular", &specularColor.x);
}

PhongFlatShadingMaterial* PhongFlatShadingMaterial::Create(glm::vec3 ka, glm::vec3 kd, glm::vec3 ks, float specularPower, glm::vec3 diffuseColor, glm::vec3 specularColor)
{
	return new PhongFlatShadingMaterial(
		ka, kd, ks, specularPower, diffuseColor, specularColor
	);
}
