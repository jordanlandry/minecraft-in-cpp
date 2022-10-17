#include "headers/Chunk.h"
#include <chrono>

Chunk::Chunk(int i, int j)
{
	x = i;
	z = j;

	std::vector<std::vector<std::vector<Block>>> b(chunkSize, std::vector<std::vector<Block>>(chunkSize, std::vector<Block>(maxHeight)));
	blocks = b;
}

void Chunk::Init(Shader* shaderProgram, double (&points)[256][256], std::vector<Texture>* Texels)
{
	//auto start = std::chrono::high_resolution_clock::now();

	//std::vector<std::vector<std::vector<Block>>> newBlocks(chunkSize, std::vector<std::vector<Block>>(chunkSize, std::vector<Block>(maxHeight)));

	for (int i = 0; i < chunkSize; i++) {
	
		for (int j = 0; j < chunkSize; j++)
		{
			int height = points[i + x * chunkSize][j + z * chunkSize] * 10 + 2;
		
			for (int k = 0; k < maxHeight; k++)
			{
				bool neighbours[6] = { false, false, false, false, false, false };

				char* id;

				if (k == 0) id = (char*)"bedrock_block";
				else if (height <= 5 && k == height) id = (char*)"water";
				else if (k == height && height < 7) id = (char*)"sand_block";
				else if (k == height) id = (char*)"grass_block";
				else if (k > height) id = (char*)"air";
				else id = (char*) "dirt_block";

				// Check blocks beside 
				/*if (j > 0 && blocks[i][j - 1][k].id != "air") neighbours[0] = true;
				if (i < chunkSize - 1 && blocks[i + 1][j][k].id != "air") neighbours[1] = true;
				if (j < chunkSize - 1 && blocks[i][j + 1][k].id != "air") neighbours[2] = true;
				if (i > 0 && blocks[i - 1][j][k].id != "air") neighbours[3] = true;
				if (k < maxHeight - 1 && blocks[i][j][k + 1].id != "air") neighbours[4] = true;
				if (k > 0 && blocks[i][j][k - 1].id != "air") neighbours[5] = true;*/

				if (neighbours[0] && neighbours[1] && neighbours[2] && neighbours[3] && neighbours[4] && neighbours[5]) continue;

				float pos[] = { i + x * chunkSize, k, j + z * chunkSize };
				Block b(id, pos);

				b.Init(shaderProgram, neighbours, Texels);
				blocks[i][j][k] = b;
			}
		}
	}

	
	/*auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	std::cout << duration.count() << " millis" << std::endl;*/
			
}

void Chunk::Render()
{
	for (int i = 0; i < chunkSize; i++)
		for (int j = 0; j < chunkSize; j++) {
			for (int k = 0; k < maxHeight; k++)
			{ 
				if (blocks[i][j][k].id == "air") continue;
				bool neighbours[6] = { false, false, false, false, false, false };

				if (blocks[i].size() > j + 1)
					if (blocks[i][j + 1][k].id != "air") neighbours[0] = true;

				if (blocks.size() > i + 1)
					if (blocks[i + 1][j][k].id != "air") neighbours[1] = true;

				if (j > 0)
					if (blocks[i][j - 1][k].id != "air") neighbours[2] = true;

				if (i > 0)
					if (blocks[i - 1][j][k].id != "air") neighbours[3] = true;

				if (blocks[i][j].size() > k + 1)
					if (blocks[i][j][k + 1].id != "air") neighbours[4] = true;

				if (k > 0)
					if (blocks[i][j][k - 1].id != "air") neighbours[5] = true;

				blocks[i][j][k].Render(neighbours);
			}
		}
}

void Chunk::Delete()
{
	/*for (int i = 0; i < chunkSize; i++)
		for (int j = 0; j < chunkSize; j++)
			for (int k = 0; k < 128; k++)
			{
				chunk[i][j][k].Delete();
			}*/
}
