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


	bool world[16][16][16];
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			for (int k = 0; k < 16; k++)
			{
				world[i][j][k] = false;
			}
		}
	}
	const int maxHeight = 15;
	std::vector<Block> blocks;

	srand((unsigned)time(NULL));
	const unsigned int maxBedrockLayer = 4;
	for (int i = 1; i < 15; i++)
	{
		for (int j = 1; j < maxHeight; j++)
		{

			for (int k = 1; k < 15; k++)
			{

				if ((float)rand() / RAND_MAX > 0.5f) continue;

				bool isBedrock;
				if (j > maxBedrockLayer) isBedrock = false;
				else
				{
					if (j == 0) isBedrock = true;
					else if ((float)rand() / RAND_MAX > 0.5f) isBedrock = true;
					else isBedrock = false;
				}

				float pos[] = { i, j, k };
				char* id;
				if (j == maxHeight - 1) id = (char*)"grass_block";
				else if (isBedrock) id =  (char*) "bedrock_block";
				else id =  (char*) "dirt_block";

				Block b(id, pos);
				b.Init(shaderProgram);
				blocks.push_back(b);
				world[i][j][k] = true;
			}
		}
	}

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glFrontFace(GL_CCW);

	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	// Frame rate
	double prevTime = 0.0;
	double crntTime = 0.0;
	double timeDiff;
	unsigned int counter = 0;

	glfwSwapInterval(0);

	// Game loop
	while (!glfwWindowShouldClose(window))
	{
		crntTime = glfwGetTime();
		timeDiff = crntTime - prevTime;
		counter++;
		if (timeDiff >= 1.0 / 30)
		{
			std::string FPS = std::to_string((1.0 / timeDiff) * counter);
			std::string newTitle = "FPS: " + FPS;
			glfwSetWindowTitle(window, newTitle.c_str());

			prevTime = crntTime;
			counter = 0;
			camera.Inputs(window);
		}


		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);				// Background Color
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		shaderProgram.Activate();

		// Handles camera inputs
		camera.Matrix(70.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");

		for (int i = 0; i < blocks.size(); i++)
		{
			blocks[i].Render(world);
		}

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