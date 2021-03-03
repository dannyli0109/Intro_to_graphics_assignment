#pragma once
#include "MeshData.h"
#include "Texture.h"
#include <map>
#include "GUI.h"
#include "Utilities.h"
#include <vector>

class ResourceManager
{
public:
	static ResourceManager* GetInstance();
	static ResourceManager* CreateInstance();
	void AddMesh(MeshData* mesh);
	void AddTexture(std::string name, Texture* texture);
	Texture* GetTexture(std::string name);
	MeshData* GetMesh(int index);
	const std::vector<MeshData*>& GetMeshes();
	const std::map<std::string, Texture*>& GetTextureDict();

	void DrawGUI();
	void Destroy();
private:
	int selectedTexture = 0;
	int selectedMesh = 0;
	ResourceManager() {};
	~ResourceManager() {};
	static ResourceManager* instance;
	//std::map<std::string, MeshData*> meshDictionary;
	std::vector<MeshData*> meshes;
	std::map<std::string, Texture*> textureDictionary;
};

