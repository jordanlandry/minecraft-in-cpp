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

#include "headers/Texture.h"
#include "headers/shaderClass.h"
#include "headers/VAO.h"
#include "headers/VBO.h"
#include "headers/EBO.h"
#include "headers/Camera.h"
#include "headers/Block.h"
#include "headers/Player.h"

const unsigned int width = 1280;
const unsigned int height = 720;

// Perlin Noise
void PerlinNoise2D(int nWidth, int nHeight, float* fSeed, int nOctaves, float fBias, float* fOutput);


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

	// Generate world
	const int worldXSize = 64;
	const int worldYSize = 24;
	const int worldZSize = 64;

	bool world[101][60][101];

	std::vector<Block> blocks;

	srand((unsigned)time(NULL));
	const unsigned int maxBedrockLayer = 4;


	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glFrontFace(GL_CCW);

	float* fNoiseSeed2D = nullptr;
	float* fPerlinNoise2D = nullptr;
	fNoiseSeed2D = new float[worldXSize * worldZSize];
	fPerlinNoise2D = new float[worldXSize * worldZSize];
	for (int i = 0; i < worldXSize * worldZSize; i++) fNoiseSeed2D[i] = (float)rand() / (float)RAND_MAX;
	PerlinNoise2D(worldXSize, worldZSize, fNoiseSeed2D, 6, 128.0f, fPerlinNoise2D);

	// Camera
	Camera camera(width, height, glm::vec3(	29, 12, 29));

	// Frame rate
	double prevTime = 0.0;
	double crntTime = 0.0;
	double timeDiff;
	unsigned int counter = 0;
	
	//Player player;
	glfwSwapInterval(0);

	const int chunkSize = 16;
	int renderDistance = 3;
	int currentChunk = 0;
	int lastChunk = 0;
	int loadedChunks = 0;

	// Game loop
	while (!glfwWindowShouldClose(window))
	{
		/*player.HandleInputs(window);
		player.Update(world);*/

		//camera.PrintCoords();

		// FPS 
		crntTime = glfwGetTime();
		timeDiff = crntTime - prevTime;
		counter++;
		if (timeDiff >= 1.0 / 165)
		{
			std::string FPS = std::to_string((1.0 / timeDiff) * counter);
			std::string newTitle = "FPS: " + FPS;
			glfwSetWindowTitle(window, newTitle.c_str());

			prevTime = crntTime;
			counter = 0;

			camera.Inputs(window, world);
		}

		//player.camera.PrintCoords();

		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);				// Background Color
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		shaderProgram.Activate();

		// Handles camera inputs
		camera.Matrix(70.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");

		for (int i = 0; i < blocks.size(); i++)
		{
			blocks[i].Init(shaderProgram, world);
			blocks[i].Render(world);
		}

		glfwSwapBuffers(window);
		glfwPollEvents();

		int count = 0;

		// Load chunks
		for (int i = loadedChunks; i < renderDistance; i++)
		{
			for (int x = 0; x < (loadedChunks + 1) * chunkSize; x++)
			{
				for (int z = 0; z < (loadedChunks + 1) * chunkSize; z++)
				{
					int height = (int)(fPerlinNoise2D[z * worldZSize + x] * 64.0f -20);
					if (height < 0) height = 0;
					for (int y = 0; y <= height; y++)
					{
						bool isBedrock;
						if (y == 0) isBedrock = true;
						/*else if ((float)rand() / RAND_MAX > 0.5f) continue;
						else if (y > maxBedrockLayer) isBedrock = false;
						else if ((float)rand() / RAND_MAX > 0.5f) isBedrock = true;*/
						else isBedrock = false;

						float pos[] = { x, y, z };
						char* id;
						if (isBedrock) id = (char*)"bedrock_block";
						else if (height < 10 && y > height - 3) id = (char*)"water";
						else if (y == height) id = (char*)"grass_block";
						else if (y > 0 && y < height - 4) id = (char*)"stone_block";
						else id = (char*)"dirt_block";

						Block b(id, pos);

						blocks.push_back(b);
						world[x + 1][y + 1][z + 1] = true;
						count++;
					}
				}
			}
			loadedChunks++;
		}
	}

	// Delete all the objects we've created
	/*VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();*/

	for (int i = 0; i < blocks.size(); i++)
	{
		blocks[i].Delete();
	}

	shaderProgram.Delete();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

// Perlin Noise
void PerlinNoise2D(int nWidth, int nHeight, float* fSeed, int nOctaves, float fBias, float* fOutput)
{
	for (int x = 0; x < nWidth; x++)
		for (int y = 0; y < nHeight; y++)
		{
			float fNoise = 0.0f;
			float fScaleAcc = 0.0f;
			float fScale = 1.0f;

			for (int o = 0; o < nOctaves; o++)
			{
				int nPitch = nWidth >> o;
				int nSampleX1 = (x / nPitch) * nPitch;
				int nSampleY1 = (y / nPitch) * nPitch;

				int nSampleX2 = (nSampleX1 + nPitch) % nWidth;
				int nSampleY2 = (nSampleY1 + nPitch) % nWidth;

				float fBlendX = (float)(x - nSampleX1) / (float)nPitch;
				float fBlendY = (float)(y - nSampleY1) / (float)nPitch;

				float fSampleT = (1.0f - fBlendX) * fSeed[nSampleY1 * nWidth + nSampleX1] + fBlendX * fSeed[nSampleY1 * nWidth + nSampleX2];
				float fSampleB = (1.0f - fBlendX) * fSeed[nSampleY2 * nWidth + nSampleX1] + fBlendX * fSeed[nSampleY2 * nWidth + nSampleX2];

				fScaleAcc += fScale;
				fNoise += (fBlendY * (fSampleB - fSampleT) + fSampleT) * fScale;
				fScale = fScale / fBias;
			}

			// Scale to seed range
			fOutput[y * nWidth + x] = fNoise / fScaleAcc;
		}
}