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
	int chunkZ;
	int nextX;
	int nextZ;

	int firstX;
	int firstZ;
	int lastX;
	int lastZ;

	std::vector<Texture> Texels;

	double points[256][256];
	std::vector<Chunk> chunks;

	World();
	void Generate(Shader *shaderProgram);
	void Render(float x, float z, Shader* shaderProgram);
};

#endif