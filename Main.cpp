#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include <vector>

#include "headers/Texture.h"
#include "headers/shaderClass.h"
#include "headers/VAO.h"
#include "headers/VBO.h"
#include "headers/EBO.h"
#include "headers/Camera.h"
#include "headers/Block.h"

const unsigned int width = 1280;
const unsigned int height = 720;

// Vertices coordinates
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

	glfwMakeContextCurrent(window);

	gladLoadGL();
	glViewport(0, 0, width, height);

	// Generates Shader object using shaders default.vert and default.frag
	Shader shaderProgram("shaders/default.vert", "shaders/default.frag");

	float pos1[] = { 0.0f, 0.0f, 0.0f };
	Block b1(2, pos1);
	b1.Init(shaderProgram);

	float pos2[] = { 0.0f, 3.0f, 0.0f };
	Block b2(1, pos2);
	b2.Init(shaderProgram);

	float pos3[] = { 0.0f, 1.0f, 0.0f };
	Block b3(2, pos3);
	b3.Init(shaderProgram);

	float pos4[] = { 0.0f, 2.0f, 0.0f };
	Block b4(2, pos4);
	b4.Init(shaderProgram);


	glEnable(GL_DEPTH_TEST);
	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	// Game loop
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);				// Background Color
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		shaderProgram.Activate();

		// Handles camera inputs
		camera.Inputs(window);
		camera.Matrix(70.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");

		b1.Render();
		b2.Render();
		b3.Render();
		b4.Render();
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Delete all the objects we've created
	/*VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();*/
	//grassTex1.Delete();

	// b1.Delete();

	shaderProgram.Delete();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}