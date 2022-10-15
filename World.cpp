#include "headers/World.h"
#include <random>

World::World()
{
	maxHeight = 128;
	chunkSize = 8;
	renderDistance = 3;
}

void World::Generate(Shader *shaderProgram)
{
	// Create world
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
				float weight = k / octaves / 2;
				points[i][j] += weight * points[i][j];
			}
		}
	}

	// Generate textures
	char* textures[] = {
		(char*)"assets/grass.png",
		(char*)"assets/grass_block_side.png",
		(char*)"assets/dirt.png",
		(char*)"assets/bedrock.png",
		(char*)"assets/stone.png",
	};


	for (int i = 0; i < sizeof(textures) / sizeof(*textures); i++)
	{
		Texture tex(textures[i], GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
		Texels.push_back(tex);
		tex.texUnit(*shaderProgram, "tex0", 0);
	}


	for (int i = 0; i < renderDistance; i++)
	{
		for (int j = 0; j < renderDistance; j++)
		{
			Chunk c(i, j);
			chunks.push_back(c);
		}
	}

	for (int i = 0; i < chunks.size(); i++) chunks[i].Init(shaderProgram, points, &Texels);
}

void World::Render(float x, float z, Shader* shaderProgram)
{
	for (int i = 0; i < chunks.size(); i++) chunks[i].Render();

	chunkX = x / chunkSize;
	chunkZ = z / chunkSize;

	// Enter new chunk
	if (chunkX != lastX)
	{
		// New chunk
		if (chunkX > lastX)
		{
			nextX = chunkX + renderDistance / 2 + 1;
			firstX = chunkX - (renderDistance - 1) / 2;
		}
			
		else if (chunkX < lastX)
		{ 
			nextX = chunkX - (renderDistance - 1) / 2;
			firstX = chunkX + renderDistance / 2 + 1;
		}
			
		Chunk chunk(nextX, chunkZ);

		// Unrender last chunkX
		for (int i = 0; i < chunks.size(); i++)
		{
			if (firstX == chunks[i].x)
			{
				chunks[i].Delete();
				chunks[i].blocks = chunk.blocks;
				chunks[i].x = nextX;

				chunks[i].Init(shaderProgram, points, &Texels);
			}
		}
	}

	lastX = chunkX;
	lastZ = chunkZ;
}