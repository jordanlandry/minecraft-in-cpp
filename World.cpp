#include "headers/World.h"
#include <random>
#include "headers/PerlinNoise.hpp"

World::World()
{
	maxHeight = 128;
	chunkSize = 16;
	renderDistance = 3;
}

void World::Generate(Shader *shaderProgram)
{
	// Create world
	const unsigned int octaves = 12;
	const siv::PerlinNoise::seed_type seed = 123456u;

	const siv::PerlinNoise perlin{ seed };

	for (int y = 0; y < 128; ++y)
	{
		for (int x = 0; x < 128; ++x)
		{
			points[x][y] = perlin.octave2D_01((x * 0.01), (y * 0.01), 128);
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