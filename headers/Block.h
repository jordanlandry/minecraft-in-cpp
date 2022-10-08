#ifndef BLOCK_CLASS_H
#define BLOCK_CLASS_H

#include "Texture.h"
#include <vector>
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "shaderClass.h"

class Block
{
public:
	char* id;
	float pos[3];

	const static int xSize = 9;
	const static int ySize = 9;
	const static int zSize = 9;

	std::vector<unsigned int> indices;
	char* textures[6];

	VAO VAOs[6];

	std::vector<VBO> VBOs;
	std::vector<EBO> EBOs;
	std::vector<Texture> Textures;

	Block(char* aId, float aPos[3]);
	void Init(Shader shaderProgram);
	void Render(bool world[xSize][ySize][zSize]);
};
#endif