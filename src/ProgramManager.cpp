#include "ProgramManager.h"
#include "ResourceManager.h"


#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif

bool ProgramManager::Initialise()
{
	window = new Window(WINDOW_WIDTH, WINDOW_HEIGHT, "Graphics Assignment");
	if (!window->Created()) return false;
	glEnable(GL_DEPTH_TEST);

	InitGUI();
	resourceManager = ResourceManager::CreateInstance();

	frameBuffer = new FrameBuffer(WINDOW_WIDTH, WINDOW_HEIGHT);

	resourceManager->AddShader("phong", new ShaderProgram("Phong.vert", "Phong.frag"));
	resourceManager->AddShader("phongFlat", new ShaderProgram("PhongFlat.vert", "PhongFlat.frag"));
	resourceManager->AddShader("color", new ShaderProgram("Color.vert", "Color.frag"));

	// add the post processing shader separately
	outlineShader = new ShaderProgram("Outline.vert", "Outline.frag");

	// loading the texture and mesh in advanced so that they can be reused later
	resourceManager->AddTexture("blank", new Texture("soulspear\\black.jpg"));
	resourceManager->AddTexture("soulspear_diffuse", new Texture("soulspear\\soulspear_diffuse.tga"));
	resourceManager->AddTexture("soulspear_specular", new Texture("soulspear\\soulspear_specular.tga"));
	resourceManager->AddTexture("soulspear_normal", new Texture("soulspear\\soulspear_normal.tga"));

	resourceManager->AddMesh("soulspear", new ObjMeshData("soulspear/soulspear.obj"));
	resourceManager->AddMesh("cube", new CubeMeshData());
	resourceManager->AddMesh("quad", new QuadMeshData());

	camera = new Camera(glm::vec3(0, 2.0, 10.0f), glm::vec3(0, 1.0f, 0), 270.0f, 0.0f, glm::pi<float>() * 0.25f, window->GetAspectRatio(), 0.1f, 100.0f);
	
	// adding different entities to the scene
	entities.push_back(
		new Entity(
			"Soul Spear",
			{
				new Transform({3.0f,-0.6f,-2.0f}, {0, 0, 0}, {1, 1, 1}),
				new MeshContainer("soulspear"),
				new PhongShadingMaterial(
					glm::vec3(0.0f, 0.0f, 0.0f),
					glm::vec3(0.8f, 0.8f, 0.8f),
					glm::vec3(0.5f, 0.5f, 0.5f),
					20.0f,
					"soulspear_diffuse",
					"soulspear_normal",
					"soulspear_specular"
				)
			}
		)
	);

	entities.push_back(
		new Entity(
			"Soul Spear Flat",
			{
				new Transform({-3.0f,-0.6f,-2.0f}, {0, 0, 0}, {1, 1, 1}),
				new MeshContainer("soulspear"),
				new PhongFlatShadingMaterial(
					glm::vec3(0.1f, 0.1f, 0.1f),
					glm::vec3(1.0f, 1.0f, 1.0f),
					glm::vec3(1.0f, 1.0f, 1.0f),
					64.0f,
					glm::vec3(1.0f, 1.0f, 1.0f),
					glm::vec3(1.0f, 1.0f, 1.0f)
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
					{ resourceManager->GetShader("phong"), resourceManager->GetShader("phongFlat") },
					{ 1.0f, 1.0f, 1.0f }, 
					20.0f
				),
				new MeshContainer("cube"),
				new ColorShadingMaterial(
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
					{ resourceManager->GetShader("phong"), resourceManager->GetShader("phongFlat") },
					{1.0f, 1.0f, 1.0f}, 
					20.0f
				),
				new MeshContainer("cube"),
				new ColorShadingMaterial(
					{ 1.0f, 1.0f, 1.0f }
				)
			}
		)
	);

	entities.push_back(
		new Entity(
			"Ambient Light",
			{
				new AmbientLight(
					{ resourceManager->GetShader("phong"), resourceManager->GetShader("phongFlat") },
					{ 1.0f, 1.0f, 1.0f },
					1.0f
				)
			}
		)
	);
	return true;
}

void ProgramManager::InitGUI()
{
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(window->Get(), true);
	ImGui_ImplOpenGL3_Init();
}

void ProgramManager::Run()
{
	while (!window->ShouldClose())
	{
		Update();
		Draw();
		window->Update();
		LateUpdate();
	}
}

void ProgramManager::ShutDown()
{
	delete window;
	delete camera;

	delete outlineShader;

	delete frameBuffer;
	for (Entity* entity : entities)
	{
		delete entity;
	}

	resourceManager->Destroy();
	DestroyGUI();
}

void ProgramManager::Update()
{
	// calculate deltatime
	deltaTime = glfwGetTime() - time;
	time = glfwGetTime();

	// handle window resize
	// resize the viewport as well as the frame buffer
	if (window->ShouldUpdateSize())
	{
		glm::vec2 size = window->GetSize();
		glViewport(0, 0, size.x, size.y);
		frameBuffer->Create(size.x, size.y);
	}

	// Updates the camera and the entities
	camera->HandleInput(deltaTime, window);
	std::vector<ShaderProgram*> shaders = resourceManager->GetShaders();
	for (ShaderProgram* shader : shaders)
	{
		camera->Update(deltaTime, window, shader);
	}
	for (Entity* entity : entities)
	{
		entity->Update(deltaTime);
	}

}

void ProgramManager::Draw()
{
	// Bind frame buffer, everything from now on will only render to the frame buffer
	frameBuffer->Bind();
	glEnable(GL_DEPTH_TEST);

	// use alpha channel to detect edge in the outline shader
	glClearColor(
		0.2, 0.2, 0.2, 0.0
	);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// render only the selected object to the outline shader
	for (int i = 0; i < entities.size(); i++)
	{
		if (i == selected)
		{
			entities[i]->Draw();
		}
	}

	FrameBuffer::Unbind();

	// render the frame buffer to a quad
	glDisable(GL_DEPTH_TEST);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	outlineShader->UseShader();
	outlineShader->SetUniform("thickness", 2.0f);
	frameBuffer->BindTexture();

	MeshData* quadMesh = resourceManager->GetMesh("quad");
	quadMesh->Bind();
	quadMesh->Draw();

	MeshData::Unbind();
	Texture::Unbind();

	// render the rest of the scene, don't clear the color bufffer otherwise the quad drawn on the screen will be erased.
	glEnable(GL_DEPTH_TEST);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_DEPTH_BUFFER_BIT);
	for (int i = 0; i < entities.size(); i++)
	{
		entities[i]->Draw();
	}

	DrawGUI();
}

void ProgramManager::DrawGUI()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);
	// GUI Related
	// Display all entity as list box and change the selected item accordingly
	std::vector<std::string> entityNames;
	for (Entity* entity : entities)
	{
		entityNames.push_back(entity->GetName());
	}

	if (entities.size() > selected)
	{
		ImGui::Begin("Entities");
		ImGui::ListBox("Entities", &selected, VectorOfStringGetter, static_cast<void*>(&entityNames), entityNames.size());

		// Display the GUI for the selected enetity
		entities[selected]->DrawGui();
		ImGui::End();
	}

	//resourceManager->DrawGUI();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	ImGui::EndFrame();
}

void ProgramManager::LateUpdate()
{
	// For when deleting a component in an entity, the component will be tag as should delete and will be deleted at the end of the frame
	for (Entity* entity : entities)
	{
		entity->LateUpdate();
	}
}

void ProgramManager::DestroyGUI()
{
	// Cleanup GUI related
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

