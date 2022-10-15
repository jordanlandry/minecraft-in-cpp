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

#include "headers/Texture.h"
#include "headers/shaderClass.h"
#include "headers/VAO.h"
#include "headers/VBO.h"
#include "headers/EBO.h"
#include "headers/Camera.h"
#include "headers/Block.h"
#include "headers/Chunk.h"
#include "headers/World.h"

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

	//std::vector<Block> blocks;

	srand((unsigned)time(NULL));

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glFrontFace(GL_CCW);

	// Generate World
	const int maxHeight = 128;

	//float points[128][128];

	//// Create world
	//std::mt19937 random_engine;
	//random_engine.seed(100);	// Add a seed
	//std::uniform_real_distribution<float> random_distribution(0, 1);
	//std::vector<float> terrain(128, 0);

	//const unsigned int octaves = 12;
	//for (int i = 0; i < 128; i++)
	//{
	//	for (int j = 0; j < 128; j++)
	//	{
	//		points[i][j] = random_distribution(random_engine);
	//		for (int k = 1; k < octaves; k++)
	//		{
	//			float weight = k / octaves / 2;
	//			points[i][j] += weight * points[i][j];
	//		}
	//	}
	//}

	const float treeDensity = 0.025f;
	unsigned int treeLocations[128][128];
	
	// Generate Trees
	/*for (int i = 0; i < 128; i++)
	{
		for (int j = 0; j < 128; j++)
		{
			if (random_distribution(random_engine) <= treeDensity)
			{
				treeLocations[i][j] = random_distribution(random_engine) * 6 + 5;
			}
			else treeLocations[i][j] = 0;
		}
	}*/


	// Generate Seed
	/*float* fNoiseSeed2D = nullptr;
	float* fPerlinNoise2D = nullptr;
	fNoiseSeed2D = new float[128 * 128];
	fPerlinNoise2D = new float[128 * 128];
	for (int i = 0; i < 128 * 128; i++) fNoiseSeed2D[i] = (float)rand() / (float)RAND_MAX;
	PerlinNoise2D(128, 128, fNoiseSeed2D, 8, 32.0f, fPerlinNoise2D);*/


	// Camera
	Camera camera(width, height, glm::vec3(0, 12, 0));

	// Frame rate
	double prevTime = 0.0;
	double crntTime = 0.0;
	double timeDiff;
	unsigned int counter = 0;

	glfwSwapInterval(0);          // Turning this on will disable VSync

	// Rendering Information
	const int chunkSize = 8;
	int renderDistance = 5;
	int currentChunk = 0;
	int lastChunk = 0;
	int loadedChunks = 0;

	int chunkX = 0;
	int chunkZ = 0;

	int lastX = 0;
	int lastZ = 0;

	World world;
	world.Generate(&shaderProgram);

	// Initialize Chunk
	/*std::vector<Chunk> chunks;
	for (int i = 0; i < renderDistance; i++)
	{
		for (int j = 0; j < renderDistance; j++)
		{
			Chunk c(i, j);
			chunks.push_back(c);
		}
	}*/

	//for (int i = 0; i < chunks.size(); i++) chunks[i].Init(&shaderProgram, points);
	

	int nextX;
	int nextZ;
	int firstX = 0;
	int firstZ = 0;

	// Game loop
	while (!glfwWindowShouldClose(window))
	{
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

			camera.Inputs(window);
		}

		glClearColor(0.68f, 0.85f, 0.9f, 1.0f);				// Background Color
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		shaderProgram.Activate();

		// Handles camera inputs
		camera.Matrix(70.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");

		//camera.PrintCoords();

		// Get current chunk position
		chunkX = camera.Position.x / chunkSize;
		chunkZ = camera.Position.z / chunkSize;

		// Render chunks
		/*for (int i = 0; i < chunks.size(); i++)
		{
			chunks[i].Render();
		}*/

		world.Render();

		// Enter new chunk
		if (chunkX != lastX)
		{
			// New chunk
			if (chunkX > lastX)
			{
				nextX = chunkX + renderDistance / 2 + 1;
				firstX = chunkX - (renderDistance - 1) / 2;
			}
			
			/*else if (chunkX < lastX)
			{ 
				nextX = chunkX - (renderDistance - 1) / 2;
				firstX = chunkX + renderDistance / 2 + 1;
			}*/
			
			Chunk chunk(nextX, chunkZ);

			// Unrender last chunkX
			/*for (int i = 0; i < chunks.size(); i++)
			{
				if (firstX == chunks[i].x)
				{
					chunks[i].Delete();
					chunks[i].blocks = chunk.blocks;
					chunks[i].x = nextX;

					chunks[i].Init(&shaderProgram, points);
				}
			}*/
		}
		
		glfwSwapBuffers(window);
		glfwPollEvents();

		// Update last chunk
		lastX = chunkX;
		lastZ = chunkZ;
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
