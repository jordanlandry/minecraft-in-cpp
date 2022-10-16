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

	const static int xSize = 101;
	const static int ySize = 60;
	const static int zSize = 101;

	char* textures[6];
	bool hasInit;

	VAO VAOs[6];
	unsigned int indices[6] = { 0, 2, 1, 0, 3, 2 };

	std::vector<VBO> VBOs;
	std::vector<EBO> EBOs;
	std::vector<Texture> Textures;

	std::vector<Texture> texels;

	Block();
	Block(char* aId, float aPos[3]);
	void Init(Shader* shaderProgram, bool chunks[6], std::vector<Texture> *Texels);
	void Render(bool neighbours[6]);
	void Delete();

};
#endif