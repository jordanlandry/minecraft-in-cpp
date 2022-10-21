#ifndef WORLD_CLASS_H
#define WORLD_CLASS_H

#include <vector>
#include "headers/Chunk.h"

class World {
public:
	int chunkSize;
	int renderDistance;
	int maxHeight;

	const unsigned int octaves = 12;
	const siv::PerlinNoise::seed_type seed = 123456u;

	const siv::PerlinNoise perlin{ seed };

	int chunkX;
	int chunkZ;
	int nextX;
	int nextZ;

	int firstX;
	int firstZ;
	int lastX;
	int lastZ;

	int iterator = 0;

	int loadedChunks = 0;

	std::vector<Texture> Texels;

	double points[256][256];
	std::vector<Chunk> chunks;

	World();
	void Generate(Shader *shaderProgram);
	void Render(float x, float z, Shader* shaderProgram);

	/*void BreakBlock(int pos[6][3], Shader* shaderProgram);
	void PlaceBlock(int pos[6][3], Shader* shaderProgram);*/
};

#endif