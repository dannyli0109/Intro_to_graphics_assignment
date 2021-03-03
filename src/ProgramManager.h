#pragma once
#include "Graphics.h"
#include "Window.h"
#include "Utilities.h"
#include "ShaderProgram.h"
#include "Camera.h"
#include "Entity.h"
#include "Transform.h"
#include "PointLight.h"
#include "Texture.h"
#include "GUI.h"
#include "PhongShadingMaterial.h"
#include "ColorShadingMaterial.h"
#include "AmbientLight.h"
#include "FrameBuffer.h"
#include "CubeMeshData.h"
#include "ObjMeshData.h"
#include "MeshContainer.h"
#include "QuadMeshData.h"

#include <string>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

class ResourceManager;

class ProgramManager
{
public:
	Window* window = nullptr;
	ShaderProgram* phongShader = nullptr;
	ShaderProgram* colorShader = nullptr;
	Camera* camera = nullptr;
	FrameBuffer* frameBuffer = nullptr;
	ShaderProgram* outlineShader = nullptr;
	ResourceManager* resourceManager = nullptr;

	std::vector<Entity*> entities;
	int selected = 0;
	bool Initialise();
	void InitGUI();
	void Run();
	void ShutDown();
	float time = 0;
	float deltaTime = 0;

private:
	void Update();
	void Draw();


	static bool VectorOfStringGetter(void* data, int n, const char** out_text);
};

