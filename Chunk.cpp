#include "headers/Chunk.h"
#include <chrono>

Chunk::Chunk(int i, int j)
{
	x = i;
	z = j;
	heightMultiplier = 16;

	std::vector<std::vector<std::vector<Block>>> c(chunkSize, std::vector<std::vector<Block>>(chunkSize, std::vector<Block>(maxHeight)));
	chunkBlocks = c;
}

void Chunk::Init(Shader* aShaderProgram, std::vector<Texture>* aTexels, siv::PerlinNoise::seed_type aSeed)
{
	shaderProgram = aShaderProgram;
	Texels = aTexels;
	seed = aSeed;

	// Generate perlin height at that position
	const siv::PerlinNoise perlin{ seed };

	char* id;

	char* surface;
	char* secondary;
	char* rock;
	for (int i = 0; i < chunkSize + 2; i++)
	{
		for (int j = 0; j < chunkSize + 2; j++)
		{
			SetBiome(i + x * chunkSize, j + z * chunkSize);

			// Get perlin
			map[i][j] = perlin.octave2D_01(((i + (x * chunkSize)) * 0.01), ((j + (z * chunkSize)) * 0.01), biomeOctaves);

			// Don't run if you are on the boundries because that is just to check for conditional rendering
			if (i == 0 || j == 0 || i == chunkSize + 1 || j == chunkSize + 1) continue;
			int height = map[i][j] * biomeMultiplier + 1;

			if (currentBiome == (char*)"desert")
			{
				surface = (char*)"sand_block";
				secondary = (char*)"sand_block";
				rock = (char*)"stone_block";
				treeDensity = 0;
			}

			else if (currentBiome == (char*)"plains" || currentBiome == (char*)"forest" || currentBiome == (char*)"mountains")
			{
				surface = (char*)"grass_block";
				secondary = (char*)"dirt_block";
				rock = (char*)"stone_block";
				treeDensity = currentBiome == (char*)"forest" ? 0.1f : currentBiome == "mountains" ? 0.0f : 0.02f;
			}
			else
			{
				surface = (char*) "grass_block";
				surface = (char*)"grass_block";
				secondary = (char*)"dirt_block";
				rock = (char*)"stone_block";
				treeDensity = 0.1f;
			}

			for (int k = maxHeight - 1; k >= 0; k--)
			{
				if (k == height) neighbours[4] = false;
				if (map[i - 1][j] > map[i][j]) neighbours[0] = true;
				if (map[i + 1][j] > map[i][j]) neighbours[1] = true;
				if (map[i][j + 1] > map[i][j]) neighbours[2] = true;
				if (map[i][j - 1] > map[i][j]) neighbours[3] = true;

				// Get the correct block id

				// Check what blocks to use based on the biome
				if (k == 0) id = (char*)"bedrock_block";		// Bedrock is always on y = 0
				else if (k > height) id = (char*)"air";
				else if (k == height) id = surface;
				else if (k > height - 4) id = secondary;
				else id = rock;

				// Generate trees
				if (k == height) CreateTree(i, j, k);

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
					// TODO experiment instead of a block class, have a matrix of block ids and access the texture in realtime to use less memory, also to limit the block ID to a certain value to only use a few bits instead of 4 bytes
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
	for (int i = 0; i < chunkSize; i++) {
		for (int j = 0; j < chunkSize; j++) {
			for (int k = 0; k < maxHeight; k++) {
				if (chunkBlocks[i][j][k].id == "air") continue;

				bool n[] = { false, false, false, false, false, false };

				if (chunkBlocks[i].size() > j + 1 && chunkBlocks[i][j + 1][k].id != "air")		n[0] = true;
				if (chunkBlocks.size() > i + 1 && chunkBlocks[i + 1][j][k].id != "air")			n[1] = true;
				if (j > 0 && chunkBlocks[i][j - 1][k].id != "air")								n[2] = true;
				if (i > 0 && chunkBlocks[i - 1][j][k].id != "air")								n[3] = true;
				if (chunkBlocks[i][j].size() > k + 1 && chunkBlocks[i][j][k + 1].id != "air")	n[4] = true;
				if (k > 0 && chunkBlocks[i][j][k - 1].id != "air")								n[5] = true;

				if (k == 0) n[5] = true;		// Don't render bottom of bedrock

				// Front
				if (i == 0)
				{
					if ((int)(map[i + 1][j] * heightMultiplier) >= k) n[3] = true;
				}

				// Right
				if (j == 0)
				{
					if ((int)(map[i][j + 1] * heightMultiplier) >= k -1) n[2] = true;
				}

				// Back
				if (i == maxHeight - 1)
				{
					if ((int)(map[i + 1][j + 2] * heightMultiplier) >= k) n[1] = true;
				}

				// Left
				if (j == maxHeight - 1)
				{
					if ((int)(map[i + 2][j + 1] * heightMultiplier) >= k) n[0] = true;
				}

				chunkBlocks[i][j][k].Render(n);
			}
		}
	}
}


// TODO Create more biomes
void Chunk::SetBiome(int i, int j)
{
	const siv::PerlinNoise perlin{ seed };
	float rm = perlin.octave2D_01(((i + x * chunkSize + biomeMapOffset) * 0.01), ((j + z * chunkSize + biomeMapOffset) * 0.01), 1);
	if (rm < 0.5) { 
		currentBiome = (char*)"desert";
		biomeOctaves = 1; 
		biomeMultiplier = 12;
	}
	else if (rm < 1) {
		currentBiome = (char*)"mountains";
		biomeOctaves = 512;
		biomeMultiplier = 64;
	}
	else if (rm < 0.7) {
		currentBiome = (char*)"forest";
		biomeOctaves = 16;
		biomeMultiplier = 12;
	}
	else if (rm < 0.8) {
		currentBiome = (char*)"jungle";
		biomeOctaves = 32;
		biomeMultiplier = 12;
	}
	else if (rm < 0.9) {
		currentBiome = (char*)"snowy";
		biomeOctaves = 24;
		biomeMultiplier = 12;
	}
	else {
		currentBiome = (char*)"plains";
		biomeOctaves = 8;
		biomeMultiplier = 12;
	}
}

// TODO Add more leaves and fix leaf textures
void Chunk::CreateTree(int i, int j, int k)
{
	const siv::PerlinNoise perlin{ seed };
	float relativeMap = perlin.octave2D_01((i + x * chunkSize + treeMapOffset) * 0.01, (j + z * chunkSize + treeMapOffset) * 0.01, octaves);
	treeMapOffset = treeMapOffset > 10000 ? 500 : treeMapOffset + 500;

	if (relativeMap < treeDensity)
	{
		//unsigned int size = (1 / treeDensity * rm * 10);	// If I do this, then birch trees will be shorter than oak
		float negRelativeMap = perlin.octave2D_01((i + x * chunkSize - treeMapOffset) * 0.01, (j + z * chunkSize - treeMapOffset) * 0.01, octaves);

		unsigned int minSize = 6;
		unsigned int maxSize = 4;		// Maximum size will be this + the minSize
		unsigned int size = negRelativeMap * maxSize + minSize;

		for (int n = 0; n < size; n++)
		{
			if (n + k >= maxHeight) continue;

			float pos[] = { i + x * chunkSize, k + n, j + z * chunkSize };
			bool ln[] = { false, false, false, false, false, false };

			char* id = (char*)"oak_log";
			if (relativeMap < treeDensity * 0.5) id = (char*)"birch_log";

			// Leaves
			if (n == size - 1)
			{
				if (id == (char*)"birch_log") id = (char*)"birch_leaves";
				if (id == (char*)"oak_log") id = (char*)"oak_leaves";
			}
			
			if (chunkBlocks[i - 1][j - 1][k + n].hasInit == true)
			{
				// Logs
				chunkBlocks[i - 1][j - 1][k + n].id = id;
				chunkBlocks[i - 1][j - 1][k + n].hasInit = false;
				chunkBlocks[i - 1][j - 1][k + n].pos[0] = pos[0];
				chunkBlocks[i - 1][j - 1][k + n].pos[1] = pos[1];
				chunkBlocks[i - 1][j - 1][k + n].pos[2] = pos[2];

				chunkBlocks[i - 1][j - 1][k + n].Init(shaderProgram, ln, Texels);
			}
			else
			{
				Block b(id, pos);
				b.Init(shaderProgram, ln, Texels);
				chunkBlocks[i - 1][j - 1][k + n] = b;
			}
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