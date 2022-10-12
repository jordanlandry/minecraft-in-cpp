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
#include <random>

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
	float points[128][128];

	std::mt19937 random_engine;
	random_engine.seed(100);	// Add a seed
	std::uniform_real_distribution<float> random_distribution(0, 1);
	std::vector<float> terrain(128, 0);


	const unsigned int octaves = 12;
	for (int i = 0; i < 128; i++)
	{
		for (int j = 0; j < 128; j++)
		{
			points[i][j] = random_distribution(random_engine);
			for (int k = 1; k < octaves; k++)
			{
				int weight = k / octaves / 2;
				points[i][j] += weight * points[i][j];
			}
		}
	}

	const float treeDensity = 0.025f;
	unsigned int treeLocations[128][128];
	for (int i = 0; i < 128; i++)
	// Generate Trees
	for (int i = 0; i < 128; i++)
	{
		for (int j = 0; j < 128; j++)
		{
			if (random_distribution(random_engine) <= treeDensity)
			{
				treeLocations[i][j] = random_distribution(random_engine) * 6 + 5;
			}
			else treeLocations[i][j] = 0;
		}
	}

	// Generate Seed
	float* fNoiseSeed2D = nullptr;
	float* fPerlinNoise2D = nullptr;
	fNoiseSeed2D = new float[128 * 128];
	fPerlinNoise2D = new float[128 * 128];
	for (int i = 0; i < 128 * 128; i++) fNoiseSeed2D[i] = (float)rand() / (float)RAND_MAX;
	PerlinNoise2D(128, 128, fNoiseSeed2D, 8, 32.0f, fPerlinNoise2D);


	// Camera
	Camera camera(width, height, glm::vec3(0, 12, 0));


	// Frame rate
	double prevTime = 0.0;
	double crntTime = 0.0;
	double timeDiff;
	unsigned int counter = 0;


	//glfwSwapInterval(0);          // Turning this on will disable VSync

	

	/*std::vector<Block> blocks;*/
	// Rendering Information
	const int chunkSize = 8;
	int renderDistance = 2;
	int currentChunk = 0;
	int lastChunk = 0;
	int loadedChunks = 0;

	int chunkX = 0;
	int chunkZ = 0;

	int lastX = 0;
	int lastZ = 0;
	const int maxBuildHeight = 128;

	// Generate world
	std::vector<std::vector<std::vector<Block>>> chunks;
	for (int x = 0; x < chunkSize * renderDistance; x++)
	{
		std::vector<std::vector<Block>> temp;
		chunks.push_back(temp);
		for (int z = 0; z < chunkSize * renderDistance; z++)
		{
			std::vector <Block> temp1;
			chunks[x].push_back(temp1);

			int height = (int)(points[chunkX * chunkSize + x][chunkZ * chunkSize + z] * 2 + 10);
			if (height < 0) height = 0;
			for (int y = 0; y < maxBuildHeight; y++)
			{

				bool isBedrock;
				if (y == 0) isBedrock = true;
				else isBedrock = false;

				float pos[] = { x, y, z };
				char* id;
				
				if (isBedrock) id = (char*)"bedrock_block";
				else if (y > height) id = (char*)"air";
				else if (y == height) id = (char*)"grass_block";
				else if (y > 0 && y < height - 4) id = (char*)"stone_block";
				else id = (char*)"dirt_block";

				if (treeLocations[x][z] > 0 && y == height && (id == (char*) "grass_block" || id == (char*) "dirt_block"))
				{
					// Place a tree
					for (int h = 0; h < treeLocations[x][z]; h++)
					{
						//std::cout << treeLocations[x][z] << std::endl;
						float p[] = { x, y + h, z };
						Block b((char*)"oak_log", p);
						chunks[x][z].push_back(b);
					}
				}
				else if (chunks[x][z].size() < maxBuildHeight)
				{
					Block b(id, pos);
					chunks[x][z].push_back(b);
				}
			}
		}
	}

	// Initialize Chunk Buffer
	std::vector<std::vector<std::vector<Block>>> chunkBuffer;

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


		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);				// Background Color
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		shaderProgram.Activate();

		// Handles camera inputs
		camera.Matrix(70.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");

		// Get current chunk position
		chunkX = camera.Position.x / chunkSize;
		chunkZ = camera.Position.z / chunkSize;

		// Render Chunk
		for (int x = 0; x < chunkSize * renderDistance; x++)
		{
			for (int z = 0; z < chunkSize * renderDistance; z++)
			{
				int height = (int)(points[chunkX * chunkSize + x][chunkZ * chunkSize + z] * 2 + 10);
				if (height < 0) height = 0;

				for (int y = 0; y < maxBuildHeight; y++)
				{
					bool pos[6] = { false, false, false, false, false, false };

					if (chunks[x].size() > z + 1)
						if (chunks[x][z + 1][y].id != "air") pos[0] = true;

					if (chunks.size() > x + 1)
						if (chunks[x + 1][z][y].id != "air") pos[1] = true;

					if (z > 0)
						if (chunks[x][z - 1][y].id != "air") pos[2] = true;

					if (x > 0)
						if (chunks[x - 1][z][y].id != "air") pos[3] = true;

					if (chunks[x][z].size() > y + 1)
						if (chunks[x][z][y + 1].id != "air") pos[4] = true;

					if (y > 0)
						if (chunks[x][z][y - 1].id != "air") pos[5] = true;

					
					//auto start = std::chrono::system_clock::now();
					chunks[x][z][y].Init(&shaderProgram, pos);
					/*auto end = std::chrono::system_clock::now();

					std::chrono::duration<double> elapsed_seconds = end - start;
					std::time_t end_time = std::chrono::system_clock::to_time_t(end);

					std::cout << "elapsed time: " << elapsed_seconds.count() * 1000 << "ms" << std::endl;*/
					chunks[x][z][y].Render(pos);
				
				}
			}
		}

		// Load new chunk
		if (chunkX != lastX || chunkZ != lastZ)
		{
			// Overwrite the current chunk data
			for (int x = 0; x < renderDistance * chunkSize; x++)
			{
				for (int z = 0; z < renderDistance * chunkSize; z++)
				{
					int height = (int)(points[chunkX * chunkSize + x][chunkZ * chunkSize + z] * 2 + 10);
					if (height < 0) height = 0;


					for (int y = 0; y < maxBuildHeight; y++)
					{
						// Get block
						bool isBedrock;
						if (y == 0) isBedrock = true;
						else isBedrock = false;

						float pos[] = { x + chunkX * chunkSize, y, z + chunkZ * chunkSize };
						char* id;

						if (isBedrock) id = (char*)"bedrock_block";
						else if (y > height) id = (char*)"air";
						else if (y == height) id = (char*)"grass_block";
						else if (y > 0 && y < height - 4) id = (char*)"stone_block";
						else id = (char*)"dirt_block";

						int i = x + chunkX * chunkSize;
						int j = z + chunkZ * chunkSize;
						if (treeLocations[i][j] > 0 && y == height && id == (char*)"grass_block")
						{
							// Place a tree
							for (int h = 0; h < treeLocations[i][j]; h++)
							{
								std::cout << y + h << std::endl;
								char* id = (char*)"oak_log";

								chunks[x][z][y + h].id = id;
								chunks[x][z][y + h].pos[0] = i;
								chunks[x][z][y + h].pos[1] = y + h;
								chunks[x][z][y + h].pos[2] = j;

								std::vector<VBO> VBOs;
								std::vector<EBO> EBOs;
								std::vector<Texture> Textures;

								chunks[x][z][y + h].VBOs = VBOs;
								chunks[x][z][y + h].EBOs = EBOs;
								chunks[x][z][y + h].Textures = Textures;

								chunks[x][z][y + h].hasInit = false;
								chunks[x][z][y + h].getTextures();
							}
						}
						else
						{
							chunks[x][z][y].id = id;
							chunks[x][z][y].pos[0] = x + chunkX * chunkSize;
							chunks[x][z][y].pos[2] = z + chunkZ * chunkSize;
						

							std::vector<VBO> VBOs;
							std::vector<EBO> EBOs;
							std::vector<Texture> Textures;

							chunks[x][z][y].VBOs = VBOs;
							chunks[x][z][y].EBOs = EBOs;
							chunks[x][z][y].Textures = Textures;
						
							chunks[x][z][y].hasInit = false;
							chunks[x][z][y].getTextures();
						}
					}
				}
			}
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
