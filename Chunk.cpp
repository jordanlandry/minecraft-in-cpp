#include "headers/Chunk.h"
#include <chrono>

Chunk::Chunk(int i, int j)
{
	x = i;
	z = j;

	std::vector<std::vector<std::vector<Block>>> c(chunkSize, std::vector<std::vector<Block>>(chunkSize, std::vector<Block>(maxHeight)));
	chunkBlocks = c;
}

void Chunk::Init(Shader* shaderProgram, std::vector<Texture>* Texels, siv::PerlinNoise::seed_type seed)
{
	double map[18][18];

	// Generate perlin height at that position
	const unsigned int octaves = 12;
	const siv::PerlinNoise perlin{ seed };
	for (int i = 0; i < chunkSize + 2; i++)
	{
		for (int j = 0; j < chunkSize + 2; j++)
		{
			map[i][j] = perlin.octave2D_01(((i + (x * chunkSize)) * 0.01), ((j + (z * chunkSize)) * 0.01), octaves);

			// Don't run if you are on the boundries because that is just to check for conditional rendering
			if (i == 0 || j == 0 || i == chunkSize + 1 || j == chunkSize + 1) continue;
			int height = map[i][j] * 12;

			for (int k = maxHeight - 1; k >= 0; k--)
			{
				bool neighbours[6] = { false, false, false, false, false, false};

				if (k == height) neighbours[4] = false;
				if (map[i - 1][j] > map[i][j]) neighbours[0] = true;
				if (map[i + 1][j] > map[i][j]) neighbours[1] = true;
				if (map[i][j + 1] > map[i][j]) neighbours[2] = true;
				if (map[i][j - 1] > map[i][j]) neighbours[3] = true;

				// Get the correct block id
				char* id;

				if (k == 0) id = (char*)"bedrock_block";
				else if (k == height) id = (char*)"grass_block";
				else if (k > height) id = (char*)"air";
				else id = (char*)"dirt_block";

				if (id == (char*)"air" && chunkBlocks[i - 1][j - 1][k].id == (char*)"air") continue;
				if (neighbours[0] && neighbours[1] && neighbours[2] && neighbours[3] && neighbours[4] && neighbours[5]) continue;

				float pos[] = { i + x * chunkSize, k, j + z * chunkSize };

				if (chunkBlocks[i - 1][j - 1][k].hasInit == true)
				{
					chunkBlocks[i - 1][j - 1][k].id = id;
					chunkBlocks[i - 1][j - 1][k].hasInit = false;

					chunkBlocks[i - 1][j - 1][k].pos[0] = pos[0];
					chunkBlocks[i - 1][j - 1][k].pos[1] = pos[1];
					chunkBlocks[i - 1][j - 1][k].pos[2] = pos[2];

					chunkBlocks[i - 1][j - 1][k].Init(shaderProgram, neighbours, Texels);
				}
				else
				{
					Block b(id, pos);
					b.Init(shaderProgram, neighbours, Texels);
					chunkBlocks[i - 1][j - 1][k] = b;
				}
			}
		}
	}
	
}

void Chunk::Render()
{
	for (int i = 0; i < chunkSize; i++)
		for (int j = 0; j < chunkSize; j++) {
			for (int k = 0; k < maxHeight; k++)
			{ 
				if (chunkBlocks[i][j][k].id == "air") continue;
				bool neighbours[6] = { false, false, false, false, false, false };

				if (chunkBlocks[i].size() > j + 1)
					if (chunkBlocks[i][j + 1][k].id != "air") neighbours[0] = true;

				if (chunkBlocks.size() > i + 1)
					if (chunkBlocks[i + 1][j][k].id != "air") neighbours[1] = true;

				if (j > 0)
					if (chunkBlocks[i][j - 1][k].id != "air") neighbours[2] = true;

				if (i > 0)
					if (chunkBlocks[i - 1][j][k].id != "air") neighbours[3] = true;

				if (chunkBlocks[i][j].size() > k + 1)
					if (chunkBlocks[i][j][k + 1].id != "air") neighbours[4] = true;

				if (k > 0)
					if (chunkBlocks[i][j][k - 1].id != "air") neighbours[5] = true;

				chunkBlocks[i][j][k].Render(neighbours);
			}
		}
}

void Chunk::Delete()
{
	/*for (int i = 0; i < chunkSize; i++)
		for (int j = 0; j < chunkSize; j++)
			for (int k = 0; k < 128; k++)
			{
				chunkBlocks[i][j][k].Delete();
			}*/
}
