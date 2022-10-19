#ifndef CHUNK_CLASS_H
#define CHUNK_CLASS_H

#include <vector>
#include "Block.h"
#include "shaderClass.h"
#include "headers/PerlinNoise.hpp"

class Chunk {
public:
	int x;
	int z;

	unsigned int chunkSize = 16;
	unsigned int maxHeight = 128;

	double map[18][18];

	const unsigned int biomeMapOffset = 100000;		// Perlin map for biomes
	const unsigned int octaves = 64;
	unsigned int heightMultiplier;

	bool neighbours[6] = { false, false, false, false, false, false };

	std::vector <std::vector<std::vector<Block>>> blocks;
	std::vector <std::vector<std::vector<Block>>> chunkBlocks;

	Chunk(int i, int j);
	void Init(Shader* shaderProgram, std::vector<Texture>* Texels, siv::PerlinNoise::seed_type seed);
	void Render();
	void Delete();

	char* GetBiome(int i, int j, siv::PerlinNoise::seed_type seed);
};

#endif