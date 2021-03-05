#pragma once
#include "MeshData.h"
#include "Texture.h"
#include "GUI.h"
#include "Utilities.h"
#include <vector>
#include <map>
#include "ShaderProgram.h"
#include "AmbientLight.h"

/**
 * Singleton Resouce manager that stores the mesh and texture data.
 */
class ResourceManager
{
public:
	static ResourceManager* GetInstance();
	static ResourceManager* CreateInstance();
	void AddMesh(std::string id, MeshData* mesh);
	void AddTexture(std::string id, Texture* texture);
	void AddShader(std::string id, ShaderProgram* shader);
	void AddComponent(std::string id, void* creator);
	

	Texture* GetTexture(std::string id);
	MeshData* GetMesh(std::string id);
	ShaderProgram* GetShader(std::string id);
	void* GetComponent(std::string id);

	Texture* GetTexture(int index);
	MeshData* GetMesh(int index);
	ShaderProgram* GetShader(int index);
	void* GetComponent(int index);

	int GetTextureIndex(std::string id);
	int GetMeshIndex(std::string id);
	int GetShaderIndex(std::string id);

	std::vector<std::string> GetMeshNames();
	std::vector<std::string> GetTextureNames();
	std::vector<std::string> GetShaderNames();

	const std::vector<MeshData*>& GetMeshes();
	const std::vector<Texture*>& GetTextures();
	const std::vector<ShaderProgram*>& GetShaders();

	void DrawGUI();
	void Destroy();
private:
	int selectedTexture = 0;
	int selectedMesh = 0;
	ResourceManager() {};
	~ResourceManager() {};
	static ResourceManager* instance;
	std::map<std::string, int> meshIds;
	std::vector<MeshData*> meshes;
	std::map<std::string, int> textureIds;
	std::vector<Texture*> textures;
	std::map<std::string, int> shaderIds;
	std::vector<ShaderProgram*> shaders;
	std::map<std::string, int> componentIds;
	std::vector<void*> components;
};

