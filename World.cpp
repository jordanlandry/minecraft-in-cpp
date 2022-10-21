#include "headers/World.h"
#include <random>
#include "headers/PerlinNoise.hpp"

World::World()
{
	maxHeight = 128;
	chunkSize = 16;
	renderDistance = 4;
}

void World::Generate(Shader *shaderProgram)
{
	// Generate textures
	char* textures[] = {
		(char*)"assets/grass.png",
		(char*)"assets/grass_block_side.png",
		(char*)"assets/dirt.png",
		(char*)"assets/bedrock.png",
		(char*)"assets/stone.png",
		(char*)"assets/sand.png",
		(char*)"assets/water_flow.png",
		(char*)"assets/oak_log.png",
		(char*)"assets/oak_log_top.png",
		(char*)"assets/oak_leaves.png",
		(char*)"assets/birch_log.png",
		(char*)"assets/birch_log_top.png",
		(char*)"assets/birch_leaves.png",
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

	for (int i = 0; i < chunks.size(); i++) chunks[i].Init(shaderProgram, &Texels, seed);
}

void World::Render(float x, float z, Shader* shaderProgram)
{
	for (int i = 0; i < chunks.size(); i++) chunks[i].Render();




	

	// Enter new chunk in X direction
	//if (chunkX != lastX)
	//{
	//	// New chunk
	//	if (chunkX > lastX)
	//	{
	//		nextX = chunkX + renderDistance / 2 + 1;
	//		firstX = chunkX - (renderDistance - 1) / 2;
	//	}
	//		
	//	else if (chunkX < lastX)
	//	{ 
	//		nextX = chunkX - (renderDistance - 1) / 2;
	//		firstX = chunkX + renderDistance / 2 + 1;
	//	}
	//		
	//	Chunk chunk(nextX, chunkZ);

	//	// Unrender last chunk And render new chunk X
	//	/*for (int iterator = 0; iterator < chunks.size(); iterator++)
	//	{*/
	//		if (firstX == chunks[iterator].x)
	//		{
	//			chunks[iterator].Delete();

	//			chunks[iterator].x = nextX;
	//			chunks[iterator].Init(shaderProgram, &Texels, seed);
	//		}
	//	//}
	//}

	//// Enter new chunk in Z direction
	//if (chunkZ != lastZ)
	//{
	//	if (chunkZ > lastZ)
	//	{
	//		nextZ = chunkZ + renderDistance - 1;
	//		firstZ = lastZ;
	//	}

	//	else if (chunkZ < lastZ)
	//	{
	//		nextZ = lastZ;
	//		firstZ = chunkZ + renderDistance - 1;
	//	}

	//	Chunk chunk(chunkX, nextZ);
	//	/*for (int iterator = 0; iterator < chunks.size(); iterator++)
	//	{*/
	//		if (firstZ == chunks[iterator].z)
	//		{
	//			chunks[iterator].Delete();

	//			chunks[iterator].z = nextZ;
	//			chunks[iterator].Init(shaderProgram, &Texels, seed);
	//		}
	//	//}
	//}
}




// TODO Fix Break block
/*
void World::BreakBlock(int pos[6][3], Shader* shaderProgram)
{
	bool n[] = { false, false, false, false, false, false };
	for (int i = 0; i < 6; i++)
	{
		if (pos[i][1] > maxHeight) continue;

		for (int j = 0; j < chunks.size(); j++)
		{
			int targetChunkX = pos[i][0] / chunkSize;
			int targetChunkZ = pos[i][2] / chunkSize;

			int relativeX = (pos[i][0] % chunkSize);
			int relativeZ = (pos[i][2] % chunkSize);

			// Check if the chunk you're in contains the blocks you're looking at
			if (chunks[j].x == targetChunkX && chunks[j].z == targetChunkZ)
			{
				chunks[j].blocks[relativeX][relativeZ][pos[i][1]].id = (char*)"air";
				chunks[j].blocks[relativeX][relativeZ][pos[i][1]].Init(shaderProgram, n, &Texels);
				// Don't break any other blocks
				return;
			}
		}
	}
}

// TODO fix place block
void World::PlaceBlock(int pos[6][3], Shader* shaderProgram)
{
	bool n[] = { false, false, false, false, false, false };
	for (int i = 0; i < 6; i++)
	{
		if (pos[i][1] >= maxHeight) continue;

		for (int j = 0; j < chunks.size(); j++)
		{
			int targetChunkX = pos[i][0] / chunkSize;
			int targetChunkZ = pos[i][2] / chunkSize;

			int relativeX = (pos[i][0] % chunkSize);
			int relativeZ = (pos[i][2] % chunkSize);

			// Check if the chunk you're in contains the blocks you're looking at
			if (chunks[j].x == targetChunkX && chunks[j].z == targetChunkZ)
			{
				chunks[j].blocks[relativeX][relativeZ][pos[i][1]].id = (char*)"stone_block";
				chunks[j].blocks[relativeX][relativeZ][pos[i][1]].hasInit = false;
				chunks[j].blocks[relativeX][relativeZ][pos[i][1]].Init(shaderProgram, n, &Texels);
				return;
			}
		}
	}
}
*/
