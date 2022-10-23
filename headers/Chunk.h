#ifndef CHUNK_CLASS_H
#define CHUNK_CLASS_H

#include <vector>
#include "Block.h"
#include "shaderClass.h"
#include "headers/PerlinNoise.hpp"
#include "headers/Texture.h"

class Chunk {
public:
	int x;
	int z;

	const unsigned int chunkSize = 16;
	const unsigned int maxHeight = 128;

	double map[18][18];
	float treeDensity;

	const unsigned int biomeMapOffset = 100000;		// Perlin map for biomes
	unsigned int octaves = 64;
	unsigned int treeMapOffset = 500;
	unsigned int heightMultiplier;

	unsigned int biomeOctaves = 64;
	unsigned int biomeMultiplier = 12;

	

	bool neighbours[6] = { false, false, false, false, false, false };

	std::vector<std::vector<std::vector<int>>> blocks;

	Shader* shaderProgram;
	std::vector<Texture>* Texels;
	siv::PerlinNoise::seed_type seed;

	//std::vector <std::vector<std::vector<Block>>> blocks;
	std::vector <std::vector<std::vector<Block>>> chunkBlocks;


	std::vector<GLfloat> vertices1;
	VAO* VAO1 = new VAO();

	char* currentBiome;

	Chunk(int i, int j);
	void Init(Shader* shaderProgram, std::vector<Texture>* Texels, siv::PerlinNoise::seed_type seed);
	void Render();
	void Delete();
	void SetBiome(int i, int j);
	void CreateTree(int i, int j, int k); 
};

#endif