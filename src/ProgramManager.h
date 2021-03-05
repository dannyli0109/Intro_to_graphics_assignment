#pragma once
#include "Graphics.h"
#include "Window.h"
#include "Utilities.h"
#include "ShaderProgram.h"
#include "Camera.h"
#include "Entity.h"
#include "Texture.h"
#include "GUI.h"
#include "FrameBuffer.h"

// Components
#include "Transform.h"
#include "PointLight.h"
#include "PhongShadingMaterial.h"
#include "PhongFlatShadingMaterial.h"
#include "ColorShadingMaterial.h"
#include "AmbientLight.h"
#include "MeshContainer.h"

// Mesh data
#include "CubeMeshData.h"
#include "ObjMeshData.h"
#include "QuadMeshData.h"

#include <string>
#include <functional>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

class ResourceManager;

class ProgramManager
{
public:
	Window* window = nullptr;
	Camera* camera = nullptr;
	FrameBuffer* frameBuffer = nullptr;
	ShaderProgram* outlineShader = nullptr;
	ResourceManager* resourceManager = nullptr;

	std::vector<Entity*> entities;
	int selected = 0;
	bool Initialise();
	void Run();
	void ShutDown();
	float time = 0;
	float deltaTime = 0;

private:
	void InitGUI();
	void Update();
	void Draw();
	void DrawGUI();
	void LateUpdate();
	void DestroyGUI();
};

