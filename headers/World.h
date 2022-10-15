#ifndef WORLD_CLASS_H
#define WORLD_CLASS_H

#include <vector>
#include "headers/Chunk.h"

class World {
public:
	int chunkSize;
	int renderDistance;
	int maxHeight;

	float treeFreq;		// From 0 to 1

	int chunkX;
	int chunkY;
	int nextX;
	int nextY;

	float points[128][128];
	std::vector<Chunk> chunks;

	World();
	void Generate(Shader *shaderProgram);
	void Render();
};

#endif