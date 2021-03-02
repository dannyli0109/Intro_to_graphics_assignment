#include "PhongShadingMaterial.h"
#include "ShaderProgram.h"

PhongShadingMaterial::PhongShadingMaterial(
	ShaderProgram* shader, 
	glm::vec3 ka, glm::vec3 kd, glm::vec3 ks, float specularPower, 
	Texture* diffuseMap, Texture* normalMap, Texture* specularMap) : Material(shader)
{
	this->name = "Phong Shading Material";

	this->ka = ka;
	this->kd = kd;
	this->ks = ks;
	this->specularPower = specularPower;
	this->diffuseMap = diffuseMap;
	this->normalMap = normalMap;
	this->specularMap = specularMap;
}


void PhongShadingMaterial::OnDraw()
{
	shader->SetUniform("ka", ka);
	shader->SetUniform("kd", kd);
	shader->SetUniform("ks", ks);
	shader->SetUniform("specularPower", specularPower);

	diffuseMap->Bind(0);
	specularMap->Bind(1);
	normalMap->Bind(2);
}

void PhongShadingMaterial::DrawGui()
{
	if (ImGui::CollapsingHeader(name.c_str(), ImGuiTreeNodeFlags_DefaultOpen))
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

		if (ImGui::TreeNodeEx("Diffuse Texture"))
		{
			float width = ImGui::GetContentRegionAvail().x;
			float aspect = diffuseMap->GetWidth() / diffuseMap->GetHeight();
			ImGui::Image((void*)(diffuseMap->GetId()), ImVec2(width, width / aspect));
			ImGui::TreePop();
		}

		if (ImGui::TreeNodeEx("Normal Texture"))
		{
			float width = ImGui::GetContentRegionAvail().x;
			float aspect = normalMap->GetWidth() / normalMap->GetHeight();
			ImGui::Image((void*)(normalMap->GetId()), ImVec2(width, width / aspect));
			ImGui::TreePop();
		}

		if (ImGui::TreeNodeEx("Specular Texture"))
		{
			float width = ImGui::GetContentRegionAvail().x;
			float aspect = specularMap->GetWidth() / specularMap->GetHeight();
			ImGui::Image((void*)(specularMap->GetId()), ImVec2(width, width / aspect));
			ImGui::TreePop();
		}
	}
}
