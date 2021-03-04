#include "PhongShadingMaterial.h"
#include "ShaderProgram.h"

PhongShadingMaterial::PhongShadingMaterial(
	glm::vec3 ka, glm::vec3 kd, glm::vec3 ks, float specularPower, 
	std::string diffuseId, std::string normalId, std::string specularId) : Material()
{
	ResourceManager* resourceManager = ResourceManager::GetInstance();
	this->name = "Phong Shading Material";

	this->shader = resourceManager->GetShader("phong");

	this->shader->SetUniform("diffuseTexture", 0);
	this->shader->SetUniform("normalTexture", 1);
	this->shader->SetUniform("specularTexture", 2);


	this->ka = ka;
	this->kd = kd;
	this->ks = ks;
	this->specularPower = specularPower;
	this->diffuseMap = resourceManager->GetTexture(diffuseId);
	this->normalMap = resourceManager->GetTexture(normalId);
	this->specularMap = resourceManager->GetTexture(specularId);

	this->selectedDiffuse = resourceManager->GetTextureIndex(diffuseId);
	this->selectedNormal = resourceManager->GetTextureIndex(normalId);
	this->selectedSpecular = resourceManager->GetTextureIndex(specularId);
}

void PhongShadingMaterial::Update(float deltaTime)
{
	ResourceManager* resourceManager = ResourceManager::GetInstance();

	this->diffuseMap = resourceManager->GetTexture(selectedDiffuse);
	this->normalMap = resourceManager->GetTexture(selectedNormal);
	this->specularMap = resourceManager->GetTexture(selectedSpecular);
}


void PhongShadingMaterial::OnDraw()
{
	shader->SetUniform("ka", ka);
	shader->SetUniform("kd", kd);
	shader->SetUniform("ks", ks);
	shader->SetUniform("specularPower", specularPower);

	if (diffuseMap)
	{
		diffuseMap->Bind(0);
	}	
	if (normalMap)
	{
		normalMap->Bind(1);
	}
	if (specularMap)
	{
		specularMap->Bind(2);
	}
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

		ResourceManager* resourceManager = ResourceManager::GetInstance();
		std::vector<std::string> textureNames = resourceManager->GetTextureNames();

		if (ImGui::TreeNodeEx("Diffuse Texture"))
		{
			ImGui::ListBox("Textures###1", &selectedDiffuse, VectorOfStringGetter, static_cast<void*>(&textureNames), textureNames.size());
			if (diffuseMap)
			{
				float width = ImGui::GetContentRegionAvail().x;
				float aspect = diffuseMap->GetWidth() / diffuseMap->GetHeight();
				ImGui::Image((void*)(diffuseMap->GetId()), ImVec2(width, width / aspect));
			}
			ImGui::TreePop();
		}

		if (ImGui::TreeNodeEx("Normal Texture"))
		{
			ImGui::ListBox("Textures###2", &selectedNormal, VectorOfStringGetter, static_cast<void*>(&textureNames), textureNames.size());
			if (normalMap)
			{
				float width = ImGui::GetContentRegionAvail().x;
				float aspect = normalMap->GetWidth() / normalMap->GetHeight();
				ImGui::Image((void*)(normalMap->GetId()), ImVec2(width, width / aspect));
			}
			ImGui::TreePop();
		}

		if (ImGui::TreeNodeEx("Specular Texture"))
		{
			ImGui::ListBox("Textures###3", &selectedSpecular, VectorOfStringGetter, static_cast<void*>(&textureNames), textureNames.size());
			if (specularMap)
			{
				float width = ImGui::GetContentRegionAvail().x;
				float aspect = specularMap->GetWidth() / specularMap->GetHeight();
				ImGui::Image((void*)(specularMap->GetId()), ImVec2(width, width / aspect));
			}
			ImGui::TreePop();
		}
	}
}
