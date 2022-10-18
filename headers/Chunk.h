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

	int chunkSize = 16;
	int maxHeight = 16;

	std::vector <std::vector<std::vector<Block>>> blocks;
	std::vector <std::vector<std::vector<Block>>> chunkBlocks;

	Chunk(int i, int j);
	void Init(Shader* shaderProgram, double (&points)[256][256], std::vector<Texture> *Texels);
	void Init(Shader* shaderProgram, std::vector<Texture>* Texels, siv::PerlinNoise::seed_type seed);
	void Render();
	void Delete();
};

#endif