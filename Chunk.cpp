#include "headers/Chunk.h"


Chunk::Chunk(int i, int j)
{
	x = i;
	y = j;
}


void Chunk::Init(Shader* shaderProgram)
{
	for (int i = 0; i < chunkSize; i++)
	{
		std::vector<std::vector<Block>> temp;
		blocks.push_back(temp);

		for (int j = 0; j < chunkSize; j++)
		{
			std::vector <Block> temp1;
			blocks[i].push_back(temp1);
			for (int k = 0; k < maxWorldHeight; k++)
			{
				float pos[] = { i + x * chunkSize, k, j + y * chunkSize };
				Block b((char*)"dirt_block", pos);

				bool n[] = { false, false, false, false, false, false };
				b.Init(shaderProgram, n);
				blocks[i][j].push_back(b);
			}
		}
	}
}

void Chunk::Render()
{
	for (int i = 0; i < chunkSize; i++)
	{
		for (int j = 0; j < chunkSize; j++)
		{
			for (int k = 0; k < maxWorldHeight; k++)
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
	
}
