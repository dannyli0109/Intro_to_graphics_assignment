#pragma once
#include "MeshData.h"
#include "Texture.h"
#include "GUI.h"
#include "Utilities.h"
#include <vector>
#include <map>

class ResourceManager
{
public:
	static ResourceManager* GetInstance();
	static ResourceManager* CreateInstance();
	void AddMesh(std::string id, MeshData* mesh);
	void AddTexture(std::string id, Texture* texture);
	Texture* GetTexture(std::string id);
	MeshData* GetMesh(std::string id);
	Texture* GetTexture(int index);
	MeshData* GetMesh(int index);
	int GetTextureIndex(std::string id);
	int GetMeshIndex(std::string id);
	std::vector<std::string> GetMeshNames();
	std::vector<std::string> GetTextureNames();
	const std::vector<MeshData*>& GetMeshes();
	const std::vector<Texture*>& GetTextures();

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
};

