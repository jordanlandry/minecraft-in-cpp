#include "headers/Chunk.h"


Chunk::Chunk(int i, int j)
{
	x = i;
	y = j;
}


void Chunk::Init(Shader* shaderProgram, float points[128][128], std::vector<Texture> Texels)
{

	for (int i = 0; i < chunkSize; i++)
	{
		std::vector<std::vector<Block>> temp;
		blocks.push_back(temp);

		for (int j = 0; j < chunkSize; j++)
		{
			std::vector <Block> temp1;
			blocks[i].push_back(temp1);

			int height = points[i + x * chunkSize][j + y * chunkSize] * 5 + 2;		// Get perlin noise value eventually

			for (int k = 0; k <= 10; k++)
			{
				char* id;
				if (k == 0) id = (char*)"bedrock_block";
				else if (k == height) id = (char*)"grass_block";
				else if (k > height) id = (char*)"air";
				else id = (char*)"dirt_block";

				float pos[] = { i + x * chunkSize, k, j + y * chunkSize };
				Block b(id, pos);

				bool n[] = { false, false, false, false, false, false };
				b.Init(shaderProgram, n, Texels);
				blocks[i][j].push_back(b);
			}
		}
	}
}

void Chunk::Render()
{
	for (int i = 0; i < chunkSize; i++)
		for (int j = 0; j < chunkSize; j++) {
			int a = blocks[i][j].size();

			for (int k = 0; k < a; k++)
			{
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
	for (int i = 0; i < blocks.size(); i++)
		for (int j = 0; j < blocks.size(); j++)
			for (int k = 0; k < blocks.size(); k++)
			{
				blocks[i][j][k].Delete();
			}
}
