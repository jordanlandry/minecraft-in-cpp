#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include"Texture.h"
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"Camera.h"
#include "Block.h"

const unsigned int width = 1280;
const unsigned int height = 720;

// Vertices coordinates
// Front
GLfloat vertices1[] =
{
	-0.5f, -0.5f,  0.5f,		0.0f, 0.0f, 0.0f,	0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,		0.0f, 0.0f, 0.0f,	1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,		0.0f, 0.0f, 0.0f,	1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,		0.0f, 0.0f, 0.0f,	0.0f, 1.0f,
};

// Right
GLfloat vertices2[] =
{
	 0.5f, -0.5f,  0.5f,		0.0f, 0.0f, 0.0f,	0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,		0.0f, 0.0f, 0.0f,	1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,		0.0f, 0.0f, 0.0f,	1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,		0.0f, 0.0f, 0.0f,	0.0f, 1.0f,
};

// Back
GLfloat vertices3[] =
{
	-0.5f, -0.5f, -0.5f,		0.0f, 0.0f, 0.0f,	0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,		0.0f, 0.0f, 0.0f,	1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,		0.0f, 0.0f, 0.0f,	1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,		0.0f, 0.0f, 0.0f,	0.0f, 1.0f,
};

// Left
GLfloat vertices4[] =
{
	-0.5f, -0.5f,  0.5f,		0.0f, 0.0f, 0.0f,	0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,		0.0f, 0.0f, 0.0f,	1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,		0.0f, 0.0f, 0.0f,	1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,		0.0f, 0.0f, 0.0f,	0.0f, 1.0f,
};

// Top
GLfloat vertices5[] =
{
	-0.5f,  0.5f,  0.5f,		0.0f, 0.0f, 0.0f,	0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,		0.0f, 0.0f, 0.0f,	1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,		0.0f, 0.0f, 0.0f,	1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,		0.0f, 0.0f, 0.0f,	0.0f, 1.0f,
};

// Bottom
GLfloat vertices6[] =
{
	-0.5f, -0.5f,  0.5f,		0.0f, 0.0f, 0.0f,	0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,		0.0f, 0.0f, 0.0f,	1.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,		0.0f, 0.0f, 0.0f,	1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,		0.0f, 0.0f, 0.0f,	0.0f, 1.0f,
};

GLuint indices[] = {0, 2, 1, 0, 3, 2};

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
	Shader shaderProgram("default.vert", "default.frag");

	VAO VAO1;
	VAO1.Bind();
	VBO VBO1(vertices1, sizeof(vertices1));
	EBO EBO1(indices, sizeof(indices));

	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	// Textures
	Texture grassTex1("assets/grass_block_side.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	grassTex1.texUnit(shaderProgram, "tex0", 0);


	VAO VAO2;
	VAO2.Bind();
	VBO VBO2(vertices2, sizeof(vertices2));
	EBO EBO2(indices, sizeof(indices));

	VAO2.LinkAttrib(VBO2, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO2.LinkAttrib(VBO2, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO2.LinkAttrib(VBO2, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	VAO2.Unbind();
	VBO2.Unbind();
	EBO2.Unbind();

	// Textures
	Texture grassTex2("assets/grass_block_side.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	grassTex2.texUnit(shaderProgram, "tex0", 0);


	VAO VAO3;
	VAO3.Bind();
	VBO VBO3(vertices3, sizeof(vertices3));
	EBO EBO3(indices, sizeof(indices));

	VAO3.LinkAttrib(VBO3, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO3.LinkAttrib(VBO3, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO3.LinkAttrib(VBO3, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	VAO3.Unbind();
	VBO3.Unbind();
	EBO3.Unbind();


	// Textures
	Texture grassTex3("assets/grass_block_side.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	grassTex3.texUnit(shaderProgram, "tex0", 0);


	VAO VAO4;
	VAO4.Bind();
	VBO VBO4(vertices4, sizeof(vertices4));
	EBO EBO4(indices, sizeof(indices));

	VAO4.LinkAttrib(VBO4, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO4.LinkAttrib(VBO4, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO4.LinkAttrib(VBO4, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	VAO4.Unbind();
	VBO4.Unbind();
	EBO4.Unbind();

	// Textures
	Texture grassTex4("assets/grass_block_side.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	grassTex4.texUnit(shaderProgram, "tex0", 0);


	VAO VAO5;
	VAO5.Bind();
	VBO VBO5(vertices5, sizeof(vertices5));
	EBO EBO5(indices, sizeof(indices));

	VAO5.LinkAttrib(VBO5, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO5.LinkAttrib(VBO5, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO5.LinkAttrib(VBO5, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	VAO5.Unbind();
	VBO5.Unbind();
	EBO5.Unbind();

	// Textures
	Texture grassTex5("assets/grass.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	grassTex5.texUnit(shaderProgram, "tex0", 0);



	VAO VAO6;
	VAO6.Bind();
	VBO VBO6(vertices6, sizeof(vertices6));
	EBO EBO6(indices, sizeof(indices));

	VAO6.LinkAttrib(VBO6, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO6.LinkAttrib(VBO6, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO6.LinkAttrib(VBO6, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	VAO6.Unbind();
	VBO6.Unbind();
	EBO6.Unbind();

	// Textures
	Texture grassTex6("assets/dirt.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	grassTex6.texUnit(shaderProgram, "tex0", 0);

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
		camera.Matrix(90.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");

		// Drawing all objects
		grassTex1.Bind();
		VAO1.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

		grassTex2.Bind();
		VAO2.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

		grassTex3.Bind();
		VAO3.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

		grassTex4.Bind();
		VAO4.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

		grassTex5.Bind();
		VAO5.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

		grassTex6.Bind();
		VAO6.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Delete all the objects we've created
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	grassTex1.Delete();

	shaderProgram.Delete();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}