#pragma once
#include "Graphics.h"
#include "Window.h"
#include "Utilities.h"
#include "ShaderProgram.h"
#include "ObjMesh.h"
#include "CubeMesh.h"
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
#include "QuadMesh.h"
#include <string>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

class ProgramManager
{
public:
	Window* window = nullptr;
	ShaderProgram* phongShading = nullptr;
	ShaderProgram* colorShading = nullptr;
	Camera* camera = nullptr;
	Texture* diffuseTexture = nullptr;
	Texture* normalTexture = nullptr;
	Texture* specularTexture = nullptr;
	FrameBuffer* frameBuffer = nullptr;
	ShaderProgram* outlineShader = nullptr;
	QuadMesh* quadMesh = nullptr;

	std::vector<Entity*> entities;
	int selected = 0;
	bool Initialise();
	void Run();
	void ShutDown();
	float time = 0;
	float deltaTime = 0;

private:
	void Update();
	void Draw();


	static bool VectorOfStringGetter(void* data, int n, const char** out_text);
};

