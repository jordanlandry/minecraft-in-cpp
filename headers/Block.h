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
	int id;
	float pos[3];

	std::vector<unsigned int> indices;
	char* textures[6];

	VAO VAOs[6];

	std::vector<VBO> VBOs;
	std::vector<EBO> EBOs;
	std::vector<Texture> Textures;

	Block(int aId, float aPos[3]);
	void Init(Shader shaderProgram);
	void Render(bool world[16][16][16]);
};
#endif
