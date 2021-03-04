#include "PhongFlatShadingMaterial.h"
#include "ShaderProgram.h"

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
