#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>  

#include "Utilities.h"
#include "ShaderProgram.h"
#include "Mesh.h"
#include "Texture.h"
#include "GameObject.h"
#include "Camera.h"
#include "PointLight.h"
#include "AmbientLight.h"
#include "Window.h"
#include <vector>

#include <sstream>

int main(void)
{
	{
		double time = 0;
		Window* window = Window::CreateInstance(1280, 720, "My window");

		if (!gladLoadGL()) return -1;
		glEnable(GL_DEPTH_TEST);

		int width;
		int height;
		glfwGetWindowSize(window->Get(), &width, &height);
		glfwSetWindowSizeCallback(window->Get(), OnWindowSizeChange);

		ShaderProgram program("Plain.vert", "Plain.frag");
		ShaderProgram lightShader("Light.vert", "Light.frag");

		Mesh mesh("soulspear/soulspear.obj");

		Texture diffuseTexture("soulspear\\soulspear_diffuse.tga");
		program.SetUniform("diffuseTexture", 0);
		Texture SpecularTexture("soulspear\\soulspear_specular.tga");
		program.SetUniform("specularTexture", 1);
		Texture normalTexture("soulspear\\soulspear_normal.tga");
		program.SetUniform("normalTexture", 2);

		Camera camera(glm::vec3(0, 0.0, 10.0f), glm::vec3(0, 1.0f, 0), 270.0f, 0.0f, glm::pi<float>() * 0.25f, width / (float)height, 0.1f, 100.0f);
		GameObject soulSpear(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
		PointLight pointLight1(glm::vec3(3.0f, 1.5f, 3.0), glm::vec3(20.0f, 20.0f, 20.0f));
		PointLight pointLight2(glm::vec3(-3.0f, 1.5f, 3.0), glm::vec3(20.0f, 20.0f, 20.0f));

		PointLight lights[2] = { pointLight1, pointLight2 };

		Mesh lightMesh1(glm::normalize(pointLight1.GetIntensity()));
		Mesh lightMesh2(glm::normalize(pointLight2.GetIntensity()));

		Mesh lightMeshes[2] = { lightMesh1, lightMesh2 };

		GameObject lightCube1(pointLight1.GetPosition(), glm::vec3(0, 0, 0), glm::vec3(0.5f, 0.5f, 0.5f));
		GameObject lightCube2(pointLight2.GetPosition(), glm::vec3(0, 0, 0), glm::vec3(0.5f, 0.5f, 0.5f));

		GameObject lightCubes[2] = { lightCube1, lightCube2 };
		AmbientLight ambientLight(glm::vec3(1, 1, 1));
		
		while (!glfwWindowShouldClose(window->Get()))
		{
			float deltaTime = glfwGetTime() - time;
			time = glfwGetTime();
			// pointLight.SetPosition(lightCube.position.x, lightCube.position.y, lightCube.position.z);


			glClearColor(
				0.2, 0.2, 0.2, 1.0
			);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			camera.Update(deltaTime);

			program.UseShader();

			// light
			for (int i = 0; i < 2; i++)
			{
				std::stringstream lightPos;
				lightPos << "lightPositions[" << i << "]";
				program.SetUniform(lightPos.str(), lights[i].GetPosition());
				std::stringstream lightIntensity;
				lightIntensity << "lightIntensities[" << i << "]";
				program.SetUniform(lightIntensity.str(), lights[i].GetIntensity());
			}
			program.SetUniform("lightCount", 2);

			//// ambient
			//program.SetUniform("ambientColor", glm::vec4(ambientColor.x, ambientColor.y, ambientColor.z, 1.0f));

			//// specular
			//program.SetUniform("specularColor", glm::vec4(specularColor.x, specularColor.y, specularColor.z, 1.0f));
			program.SetUniform("specularPower", 20.0f);
			
			program.SetUniform("ambientLightIntensity", ambientLight.GetIntensity());
			program.SetUniform("ka", glm::vec3(0.0f, 0.0f, 0.0f));
			program.SetUniform("kd", glm::vec3(0.8f, 0.8f, 0.8f));
			program.SetUniform("ks", glm::vec3(0.5f, 0.5f, 0.5f));

			glfwGetWindowSize(window->Get(), &width, &height);

			glm::vec3 cameraPos = camera.GetPosition();
			glm::mat4 cameraViewMatrix = camera.GetViewMatrix();
			glm::mat4 cameraProjectionMatrix = camera.GetProjectionMatrix(width, height);
			
			program.SetUniform("cameraPos", cameraPos);
			program.SetUniform("viewMatrix", cameraViewMatrix);
			program.SetUniform("projectionMatrix", cameraProjectionMatrix);
			
			//soulSpear.RotateY(glfwGetTime());
			program.SetUniform("modelMatrix", soulSpear.GetModelMatrix());
			mesh.Bind();
			diffuseTexture.Bind(0);
			SpecularTexture.Bind(1);
			normalTexture.Bind(2);
			mesh.Draw();
			//soulSpear.Draw();
			Mesh::Unbind();
			Texture::Unbind();

			lightShader.UseShader();
			lightShader.SetUniform("cameraPos", cameraPos);
			lightShader.SetUniform("viewMatrix", cameraViewMatrix);
			lightShader.SetUniform("projectionMatrix", cameraProjectionMatrix);

			for (int i = 0; i < 2; i++)
			{
				lightMeshes[i].Bind();
				lightShader.SetUniform("lightColor", glm::normalize(lights[i].GetIntensity()));
				lightShader.SetUniform("modelMatrix", lightCubes[i].GetModelMatrix());
				lightMeshes[i].Draw();
			}
			
			Mesh::Unbind();
			Texture::Unbind();

			glfwSwapBuffers(window->Get());
			glfwPollEvents();
		}
		Window::DeleteInstance();
		glfwTerminate();
	}
	_CrtDumpMemoryLeaks();


	return 0;
}
