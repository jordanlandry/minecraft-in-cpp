#ifndef CHUNK_CLASS_H
#define CHUNK_CLASS_H

#include <vector>
#include "Block.h"
#include "shaderClass.h"
class Chunk {
public:
	int x;
	int z;

	int chunkSize = 8;
	int maxHeight = 16;

	std::vector <std::vector<std::vector<Block>>> blocks;

	Chunk(int i, int j);
	void Init(Shader* shaderProgram, double (&points)[256][256], std::vector<Texture> *Texels);
	void Render();
	void Delete();
};

#endif