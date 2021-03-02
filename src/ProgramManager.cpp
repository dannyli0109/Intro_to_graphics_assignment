#include "ProgramManager.h"

bool ProgramManager::Initialise()
{
	window = new Window(WINDOW_WIDTH, WINDOW_HEIGHT, "Graphics Assignment");
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


	window->SetSizeCallback(OnWindowSizeChange);
	phongShading = new ShaderProgram("Plain.vert", "Plain.frag");
	colorShading = new ShaderProgram("Light.vert", "Light.frag");

	diffuseTexture = new Texture("soulspear\\soulspear_diffuse.tga");
	phongShading->SetUniform("diffuseTexture", 0);
	specularTexture = new Texture("soulspear\\soulspear_specular.tga");
	phongShading->SetUniform("specularTexture", 1);
	normalTexture = new Texture("soulspear\\soulspear_normal.tga");
	phongShading->SetUniform("normalTexture", 2);


	camera = new Camera(glm::vec3(0, 2.0, 10.0f), glm::vec3(0, 1.0f, 0), 270.0f, 0.0f, glm::pi<float>() * 0.25f, window->GetAspectRatio(), 0.1f, 100.0f);
	entities.push_back(
		new Entity(
			"Soul Spear",
			{
				new Transform({0, 0, 0}, {0, 0, 0}, {1, 1, 1}),
				new ObjMesh("soulspear/soulspear.obj"),
				new PhongShadingMaterial(
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
		new Entity(
			"Ambient Light",
			{
				new AmbientLight(
					{ phongShading },
					{ 1.0f, 1.0f, 1.0f },
					1.0f
				)
			}
		)
	);

	entities.push_back(
		new Entity(
			"Point Light1",
			{
				new Transform({-3.0f, 1.5f, 3.0f}, {0, 0, 0}, {0.5f, 0.5f, 0.5f}),
				new PointLight(
					{ phongShading },
					{ 1.0f, 1.0f, 1.0f }, 
					20.0f
				),
				new CubeMesh(),
				new ColorShadingMaterial(
					colorShading,
					{ 1.0f, 1.0f, 1.0f }
				)
			}
		)
	);

	entities.push_back(
		new Entity(
			"Point Light2",
			{
				new Transform({3.0f, 1.5f, 3.0f}, {0, 0, 0}, {0.5f, 0.5f, 0.5f}),
				new PointLight(
					{ phongShading },
					{1.0f, 1.0f, 1.0f}, 
					20.0f
				),
				new CubeMesh(),
				new ColorShadingMaterial(
					colorShading,
					{1.0f, 1.0f, 1.0f}
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
	delete camera;
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
	glClearColor(
		0.2, 0.2, 0.2, 1.0
	);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	camera->HandleInput(deltaTime, window);
	camera->Update(deltaTime, window, phongShading);
	camera->Update(deltaTime, window, colorShading);

	for (Entity* entity : entities)
	{
		entity->Update(deltaTime);
	}

	for (Entity* entity : entities)
	{
		entity->Draw();
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
	{
		auto& vector = *static_cast<std::vector<std::string>*>(vec);
		if (idx < 0 || idx >= static_cast<int>(vector.size())) { return false; }
		*out_text = vector.at(idx).c_str();
		return true;
	}

}