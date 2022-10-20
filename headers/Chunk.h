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
	float treeDensity;

	const unsigned int biomeMapOffset = 100000;		// Perlin map for biomes
	const unsigned int octaves = 64;
	unsigned int treeMapOffset = 500;
	unsigned int heightMultiplier;

	bool neighbours[6] = { false, false, false, false, false, false };

	Shader* shaderProgram;
	std::vector<Texture>* Texels;
	siv::PerlinNoise::seed_type seed;

	std::vector <std::vector<std::vector<Block>>> blocks;
	std::vector <std::vector<std::vector<Block>>> chunkBlocks;

	char* currentBiome;

	// TODO Make shaderProgram, Texels, their own variables here to avoid passing them into every function
	// TODO Make seed a reference to variable in world class
	Chunk(int i, int j);
	void Init(Shader* shaderProgram, std::vector<Texture>* Texels, siv::PerlinNoise::seed_type seed);
	void Render();
	void Delete();
	void SetBiome(int i, int j);
	void CreateTree(int i, int j, int k); 
};

#endif