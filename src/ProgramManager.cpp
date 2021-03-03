#include "ProgramManager.h"

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif

bool ProgramManager::Initialise()
{
	window = DBG_NEW Window(WINDOW_WIDTH, WINDOW_HEIGHT, "Graphics Assignment");
	if (!window->Created()) return false;
	glEnable(GL_DEPTH_TEST);


	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(window->Get(), true);
	ImGui_ImplOpenGL3_Init();

	glm::vec2 windowSize = window->GetSize();
	frameBuffer = DBG_NEW FrameBuffer(windowSize.x, windowSize.y);
	//window->SetSizeCallback([](GLFWwindow* window, int newWidth, int newHeight)
	//	{
	//		glViewport(0, 0, newWidth, newHeight);
	//		frameBuffer->Create(newWidth, newHeight);
	//	}
	//);

	phongShading = DBG_NEW ShaderProgram("Plain.vert", "Plain.frag");
	colorShading = DBG_NEW ShaderProgram("Light.vert", "Light.frag");
	outlineShader = DBG_NEW ShaderProgram("Outline.vert", "Outline.frag");


	// TODO Load textures and mesh to a map and use a pointer to avoid loading the same thing multiple times

	diffuseTexture = DBG_NEW Texture("soulspear\\soulspear_diffuse.tga");
	phongShading->SetUniform("diffuseTexture", 0);
	specularTexture = DBG_NEW Texture("soulspear\\soulspear_specular.tga");
	phongShading->SetUniform("specularTexture", 1);
	normalTexture = DBG_NEW Texture("soulspear\\soulspear_normal.tga");
	phongShading->SetUniform("normalTexture", 2);

	quadMesh = DBG_NEW QuadMesh();

	camera = DBG_NEW Camera(glm::vec3(0, 2.0, 10.0f), glm::vec3(0, 1.0f, 0), 270.0f, 0.0f, glm::pi<float>() * 0.25f, window->GetAspectRatio(), 0.1f, 100.0f);
	entities.push_back(
		DBG_NEW Entity(
			"Soul Spear",
			{
				DBG_NEW Transform({0, 0, 0}, {0, 0, 0}, {1, 1, 1}),
				DBG_NEW ObjMesh("soulspear/soulspear.obj"),
				DBG_NEW PhongShadingMaterial(
					phongShading, 
					glm::vec3(0.0f, 0.0f, 0.0f),
					glm::vec3(0.8f, 0.8f, 0.8f),
					glm::vec3(0.5f, 0.5f, 0.5f),
					20.0f,
					diffuseTexture,
					normalTexture,
					specularTexture
				)
			}
		)
	);

	entities.push_back(
		DBG_NEW Entity(
			"Point Light1",
			{
				DBG_NEW Transform({-3.0f, 1.5f, 3.0f}, {0, 0, 0}, {0.5f, 0.5f, 0.5f}),
				DBG_NEW PointLight(
					{ phongShading },
					{ 1.0f, 1.0f, 1.0f }, 
					20.0f
				),
				DBG_NEW CubeMesh(),
				DBG_NEW ColorShadingMaterial(
					colorShading,
					{ 1.0f, 1.0f, 1.0f }
				)
			}
		)
	);

	entities.push_back(
		DBG_NEW Entity(
			"Point Light2",
			{
				DBG_NEW Transform({3.0f, 1.5f, 3.0f}, {0, 0, 0}, {0.5f, 0.5f, 0.5f}),
				DBG_NEW PointLight(
					{ phongShading },
					{1.0f, 1.0f, 1.0f}, 
					20.0f
				),
				DBG_NEW CubeMesh(),
				DBG_NEW ColorShadingMaterial(
					colorShading,
					{1.0f, 1.0f, 1.0f}
				)
			}
		)
	);

	entities.push_back(
		DBG_NEW Entity(
			"Ambient Light",
			{
				DBG_NEW AmbientLight(
					{ phongShading },
					{ 1.0f, 1.0f, 1.0f },
					1.0f
				)
			}
		)
	);
	return true;
}

void ProgramManager::Run()
{
	while (!window->ShouldClose())
	{
		Update();
		Draw();
		window->Update();
	}
}

void ProgramManager::ShutDown()
{
	delete window;
	delete phongShading;
	delete colorShading;
	delete outlineShader;
	delete camera;

	delete frameBuffer;
	delete quadMesh;
	for (Entity* entity : entities)
	{
		delete entity;
	}

	delete diffuseTexture;
	delete normalTexture;
	delete specularTexture;

	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void ProgramManager::Update()
{
	if (window->ShouldUpdateSize())
	{
		glm::vec2 size = window->GetSize();
		glViewport(0, 0, size.x, size.y);
		frameBuffer->Create(size.x, size.y);
	}
	deltaTime = glfwGetTime() - time;
	time = glfwGetTime();
	// GUI
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);
}

void ProgramManager::Draw()
{
	glm::vec2 windowSize = window->GetSize();
	frameBuffer->Bind();
	glEnable(GL_DEPTH_TEST);
	glClearColor(
		0.2, 0.2, 0.2, 0.0
	);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	camera->HandleInput(deltaTime, window);
	camera->Update(deltaTime, window, phongShading);
	camera->Update(deltaTime, window, colorShading);

	for (Entity* entity : entities)
	{
		entity->Update(deltaTime);
	}

	for (int i = 0; i < entities.size(); i++)
	{
		if (i == selected)
		{
			entities[i]->Draw();
		}
	}

	FrameBuffer::Unbind();
	//Mesh::Unbind();
	//Texture::Unbind();


	glDisable(GL_DEPTH_TEST);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	outlineShader->UseShader();
	frameBuffer->BindTexture();
	quadMesh->Draw();

	Mesh::Unbind();
	Texture::Unbind();


	glEnable(GL_DEPTH_TEST);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_DEPTH_BUFFER_BIT);
	for (int i = 0; i < entities.size(); i++)
	{
		entities[i]->Draw();
	}

	std::vector<std::string> entityNames;
	for (Entity* entity : entities)
	{
		entityNames.push_back(entity->GetName());
	}

	if (entities.size() > selected)
	{
		const char* label = "Entities";
		ImGui::Begin("Entities", 0, ImGuiWindowFlags_AlwaysVerticalScrollbar);
		ImGui::ListBox("Entities", &selected, VectorOfStringGetter, static_cast<void*>(&entityNames), entityNames.size());
		entities[selected]->DrawGui();
		ImGui::End();
	}

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

bool ProgramManager::VectorOfStringGetter(void* vec, int idx, const char** out_text)
{
	
	auto& vector = *static_cast<std::vector<std::string>*>(vec);
	if (idx < 0 || idx >= static_cast<int>(vector.size())) { return false; }
	*out_text = vector.at(idx).c_str();
	return true;

}
