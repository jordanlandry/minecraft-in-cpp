#include "headers/World.h"

#include <random>


World::World()
{
	maxHeight = 128;
	chunkSize = 16;
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

	for (int i = 0; i < renderDistance; i++)
	{
		for (int j = 0; j < renderDistance; j++)
		{
			Chunk c(i, j);
			chunks.push_back(c);
		}
	}

	for (int i = 0; i < chunks.size(); i++) chunks[i].Init(shaderProgram, points);
}

void World::Render()
{
	for (int i = 0; i < chunks.size(); i++)
	{
		chunks[i].Render();
	}
}