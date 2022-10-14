#ifndef CHUNK_CLASS_H
#define CHUNK_CLASS_H

#include <vector>
#include "Block.h"
#include "shaderClass.h"
class Chunk {
public:
	int x;
	int y;

	const int chunkSize = 8;
	const int maxWorldHeight = 5;

	std::vector<std::vector<::std::vector<Block>>> blocks;

	Chunk(int i, int j);
	void Init(Shader* shaderProgram);
	void Render();
};

#endif