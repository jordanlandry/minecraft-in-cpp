#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include"headers/Texture.h"
#include"headers/shaderClass.h"
#include"headers/VAO.h"
#include"headers/VBO.h"
#include"headers/EBO.h"
#include"headers/Camera.h"
#include"headers/World.h"



const unsigned int width = 1280;
const unsigned int height = 720;

GLfloat lightVertices[] =
{ //     COORDINATES     //
	-0.1f, -0.1f,  0.1f,
	-0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f,  0.1f,
	-0.1f,  0.1f,  0.1f,
	-0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f,  0.1f
};

GLuint lightIndices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7
};


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


	Shader* shaderProgram = new Shader("shaders/default.vert", "shaders/default.frag");


	// Shader for light cube
	Shader* lightShader = new Shader("shaders/light.vert", "shaders/light.frag");
	VAO lightVAO;
	lightVAO.Bind();

	VBO lightVBO(lightVertices, sizeof(lightVertices));
	EBO lightEBO(lightIndices, sizeof(lightIndices));
	lightVAO.LinkAttrib(lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);

	lightVAO.Unbind();
	lightVBO.Unbind();
	lightEBO.Unbind();

	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.0f, 60.0f, 0.0f);
	glm::mat4 lightModel = glm::mat4(100.0f);
	lightModel = glm::translate(lightModel, lightPos);

	glm::vec3 Pos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 Model = glm::mat4(1.0f);
	Model = glm::translate(Model, Pos);


	lightShader->Activate();
	glUniformMatrix4fv(glGetUniformLocation(lightShader->ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(lightShader->ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);

	shaderProgram->Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram->ID, "model"), 1, GL_FALSE, glm::value_ptr(Model));
	glUniform4f(glGetUniformLocation(shaderProgram->ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram->ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);


	// Window Props
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glFrontFace(GL_CCW);

	// Camera
	Camera* camera = new Camera(width, height, glm::vec3(16.0f, 16.0f, 32.0f));

	// Frame rate
	double prevTime = 0.0;
	double crntTime = 0.0;
	double timeDiff;
	unsigned int counter = 0;

	glfwSwapInterval(0);          // Turning this on will disable VSync

	World* world = new World();
	world->Generate(shaderProgram);

	// TODO Add multi-threading for either movement or chunk rendering so it doesn't lag when you enter a new chunk
	
	bool pressing = false;
	bool showLines = true;

	// Game Loop
	while (!glfwWindowShouldClose(window))
	{

		camera->PrintCoords();
		// Toggle wireframe
		if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
		{
			if (showLines) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

			pressing = true;
		}

		if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_RELEASE)
		{
			if (pressing)
			{
				pressing = false;

				if (showLines) showLines = false;
				else showLines = true;
			}
		}

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

		camera->Inputs(window);
		camera->updateMatrix(70.0f, 0.1f, 100.0f);
		camera->Matrix(shaderProgram, "camMatrix");

		glUniform3f(glGetUniformLocation(shaderProgram->ID, "camPos"), camera->Position.x, camera->Position.y, camera->Position.z);

		// Render World
		world->Render(camera->Position.x, camera->Position.z, shaderProgram);

		// Lighting
		/*lightShader->Activate();
		camera->Matrix(lightShader, "camMatrix");
		lightVAO.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int), GL_UNSIGNED_INT, 0);*/

		// Window buffer
		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	delete camera;
	delete world;
	shaderProgram->Delete();
	lightVAO.Delete();
	lightVBO.Delete();
	lightEBO.Delete();
	lightShader->Delete();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}