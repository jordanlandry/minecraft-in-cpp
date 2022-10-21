#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include <vector>
#include <string>
#include <time.h>
#include <thread>
#include <chrono>
#include <random>

// Include Headers
#include "headers/Texture.h"
#include "headers/shaderClass.h"
#include "headers/VAO.h"
#include "headers/VBO.h"
#include "headers/EBO.h"
#include "headers/Camera.h"
#include "headers/Block.h"
#include "headers/Chunk.h"
#include "headers/World.h"

#include <memory>

const unsigned int width = 1280;
const unsigned int height = 720;

struct AllocationMetrics
{
	uint32_t TotalAllocated = 0;
	uint32_t TotalFreed = 0;

	uint32_t CurrentUsage() { return TotalAllocated - TotalFreed; }
};

static AllocationMetrics s;

void* operator new(size_t size)
{
	s.TotalAllocated += size;
	return malloc(size);
}

void operator delete(void* memory, size_t size)
{
	s.TotalFreed += size;
	free(memory);
}


int main()
{
	// Initialize GLFW
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(width, height, "Minecraft", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Making Window
	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, width, height);

	// TODO Set window to middle of screen

	// Generates Shader object using shaders default.vert and default.frag
	Shader* shaderProgram = new Shader("shaders/default.vert", "shaders/default.frag");

	// Window Props
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glFrontFace(GL_CCW);




	// Camera
	Camera* camera = new Camera(width, height, glm::vec3(0, 12, 0));

	// Frame rate
	double prevTime = 0.0;
	double crntTime = 0.0;
	double timeDiff;
	unsigned int counter = 0;

	glfwSwapInterval(0);          // Turning this on will disable VSync

	// Generate World
	World* world = new World();
	world->Generate(shaderProgram);


	// TODO Add lighting
	// TODO Add multi-threading for either movement or chunk rendering so it doesn't lag when you enter a new chunk

	// Game loop
	while (!glfwWindowShouldClose(window))
	{
		// FPS
		crntTime = glfwGetTime();
		timeDiff = crntTime - prevTime;
		counter++;
		camera->Inputs(window);
		if (timeDiff >= 1.0 / 165)
		{
			std::string FPS = std::to_string((1.0 / timeDiff) * counter);
			std::string newTitle = "FPS: " + FPS;
			glfwSetWindowTitle(window, newTitle.c_str());

			prevTime = crntTime;
			counter = 0;
		}

		glClearColor(0.68f, 0.85f, 0.9f, 1.0f);				// Background Color
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		shaderProgram->Activate();

		// Handles camera inputs
		camera->Matrix(70.0f, 0.1f, 100.0f, *shaderProgram, "camMatrix");

		// Render world
		world->Render(camera->Position.x, camera->Position.z, shaderProgram);

		// Window buffer
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	delete camera;
	delete world;
	shaderProgram->Delete();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

