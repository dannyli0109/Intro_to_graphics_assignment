#include "ResourceManager.h"

ResourceManager* ResourceManager::GetInstance()
{
	return instance;
}

ResourceManager* ResourceManager::CreateInstance()
{
	if (!instance)
	{
		instance = new ResourceManager();
	}
	return instance;
}
void ResourceManager::AddMesh(std::string id, MeshData* mesh)
{
	int index = meshes.size();
	meshes.push_back(mesh);
	meshIds[id] = index;
	mesh->SetName(id);
}
void ResourceManager::AddTexture(std::string id, Texture* texture)
{
	int index = textures.size();
	textures.push_back(texture);
	textureIds[id] = index;
	texture->SetName(id);
}

void ResourceManager::AddShader(std::string id, ShaderProgram* shader)
{
	int index = shaders.size();
	shaders.push_back(shader);
	shaderIds[id] = index;
	shader->SetName(id);
}

void ResourceManager::AddComponent(std::string id, void* creator)
{
	int index = components.size();
	components.push_back(creator);
	componentIds[id] = index;
}

Texture* ResourceManager::GetTexture(std::string id)
{
	int index = textureIds[id];
	return GetTexture(index);
}

MeshData* ResourceManager::GetMesh(std::string id)
{
	int index = meshIds[id];
	return GetMesh(index);
}

ShaderProgram* ResourceManager::GetShader(std::string id)
{
	int index = shaderIds[id];
	return GetShader(index);
}

void* ResourceManager::GetComponent(std::string id)
{
	 int index = componentIds[id];
	 return GetComponent(index);
}

Texture* ResourceManager::GetTexture(int index)
{
	if (index < 0 || index > textures.size() - 1) return nullptr;
	return textures[index];
}

MeshData* ResourceManager::GetMesh(int index)
{
	if (index < 0 || index > meshes.size() - 1) return nullptr;
	return meshes[index];
}

ShaderProgram* ResourceManager::GetShader(int index)
{
	if (index < 0 || index > shaders.size() - 1) return nullptr;
	return shaders[index];
}

void* ResourceManager::GetComponent(int index)
{
	if (index < 0 || index > components.size() - 1) return nullptr;
	return components[index];
}

int ResourceManager::GetTextureIndex(std::string id)
{
	return textureIds[id];
}

int ResourceManager::GetMeshIndex(std::string id)
{
	return meshIds[id];
}

int ResourceManager::GetShaderIndex(std::string id)
{
	return shaderIds[id];
}

std::vector<std::string> ResourceManager::GetMeshNames()
{
	std::vector<std::string> meshNames;
	meshNames.reserve(meshes.size());
	for (MeshData* mesh : meshes)
	{
		meshNames.push_back(mesh->GetName());
	}
	return meshNames;
}

std::vector<std::string> ResourceManager::GetTextureNames()
{
	std::vector<std::string> textureNames;
	textureNames.reserve(textures.size());
	for (Texture* texture : textures)
	{
		textureNames.push_back(texture->GetName());
	}
	return textureNames;
}

std::vector<std::string> ResourceManager::GetShaderNames()
{
	std::vector<std::string> shaderNames;
	shaderNames.reserve(shaders.size());
	for (ShaderProgram* shader : shaders)
	{
		shaderNames.push_back(shader->GetName());
	}
	return shaderNames;
}

const std::vector<MeshData*>& ResourceManager::GetMeshes()
{
	return meshes;
}
const std::vector<Texture*>& ResourceManager::GetTextures()
{
	return textures;
}

const std::vector<ShaderProgram*>& ResourceManager::GetShaders()
{
	return shaders;
}

void ResourceManager::DrawGUI()
{
	/*if (meshes.size() > selectedMesh)
	{
		std::vector<std::string> meshNames;
		for (MeshData* mesh : meshes)
		{
			meshNames.push_back(mesh->GetName());
		}

		ImGui::ListBox("Meshes", &selectedMesh, VectorOfStringGetter, static_cast<void*>(&meshNames), meshNames.size());
	}*/
}
void ResourceManager::Destroy()
{
	for (Texture* texture : textures)
	{
		delete texture;
	}

	for (MeshData* mesh : meshes)
	{
		delete mesh;
	}

	for (ShaderProgram* shader : shaders)
	{
		delete shader;
	}
	delete instance;
	instance = nullptr;
}
ResourceManager* ResourceManager::instance = nullptr;
