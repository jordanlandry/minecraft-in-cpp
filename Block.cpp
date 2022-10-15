#include "headers/Block.h"
#include <chrono>


Block::Block()
{
	id =(char*)"dirt_block";
	hasInit = false;
	//getTextures();
	pos[0] = 0;
	pos[1] = 0;
	pos[2] = 0;
}

Block::Block(char* aId, float aPos[3])
{
	id = aId;

	hasInit = false;

	getTextures();

	pos[0] = aPos[0];
	pos[1] = aPos[1];
	pos[2] = aPos[2];
}

void Block::Init(Shader* shaderProgram, bool chunks[6], std::vector<Texture> *Texels)
{
	if (id == "air") return;
	if (hasInit) return;

	int x = pos[0];
	int y = pos[1];
	int z = pos[2];

	if (chunks[0] == true && chunks[1] == true && chunks[2] == true && chunks[3] == true && chunks[4] == true && chunks[5] == true) return;

	// Front
	GLfloat vertices1[] = {
		-0.5f + x, -0.5f + y,  0.5f + z,		0.0f, 0.0f, 0.0f,	0.0f, 0.0f,
		 0.5f + x, -0.5f + y,  0.5f + z,		0.0f, 0.0f, 0.0f,	1.0f, 0.0f,
		 0.5f + x,  0.5f + y,  0.5f + z,		0.0f, 0.0f, 0.0f,	1.0f, 1.0f,
		-0.5f + x,  0.5f + y,  0.5f + z,		0.0f, 0.0f, 0.0f,	0.0f, 1.0f,
	};

	// Right
	GLfloat vertices2[] = {
		0.5f + x, -0.5f + y,  0.5f + z,			0.0f, 0.0f, 0.0f,	0.0f, 0.0f,
		0.5f + x, -0.5f + y, -0.5f + z,			0.0f, 0.0f, 0.0f,	1.0f, 0.0f,
		0.5f + x,  0.5f + y, -0.5f + z,			0.0f, 0.0f, 0.0f,	1.0f, 1.0f,
		0.5f + x,  0.5f + y,  0.5f + z,			0.0f, 0.0f, 0.0f,	0.0f, 1.0f,
	};

	// Back
	GLfloat vertices3[] = {
		-0.5f + x,  0.5f + y, -0.5f + z,		0.0f, 0.0f, 0.0f,	0.0f, 1.0f,
		 0.5f + x,  0.5f + y, -0.5f + z,		0.0f, 0.0f, 0.0f,	1.0f, 1.0f,
		 0.5f + x, -0.5f + y, -0.5f + z,		0.0f, 0.0f, 0.0f,	1.0f, 0.0f,
		-0.5f + x, -0.5f + y, -0.5f + z,		0.0f, 0.0f, 0.0f,	0.0f, 0.0f,
	};

	// Left
	GLfloat vertices4[] = {
		-0.5f + x,  0.5f + y,  0.5f + z,		0.0f, 0.0f, 0.0f,	0.0f, 1.0f,
		-0.5f + x,  0.5f + y, -0.5f + z,		0.0f, 0.0f, 0.0f,	1.0f, 1.0f,
		-0.5f + x, -0.5f + y, -0.5f + z,		0.0f, 0.0f, 0.0f,	1.0f, 0.0f,
		-0.5f + x, -0.5f + y,  0.5f + z,		0.0f, 0.0f, 0.0f,	0.0f, 0.0f,
	};

	// Top
	GLfloat vertices5[] = {
		-0.5f + x,  0.5f + y,  0.5f + z,		0.0f, 0.0f, 0.0f,	0.0f, 0.0f,
		 0.5f + x,  0.5f + y,  0.5f + z,		0.0f, 0.0f, 0.0f,	1.0f, 0.0f,
		 0.5f + x,  0.5f + y, -0.5f + z,		0.0f, 0.0f, 0.0f,	1.0f, 1.0f,
		-0.5f + x,  0.5f + y, -0.5f + z,		0.0f, 0.0f, 0.0f,	0.0f, 1.0f,
	};

	// Bottom
	GLfloat vertices6[] = {
		-0.5f + x, -0.5f + y, -0.5f + z,		0.0f, 0.0f, 0.0f,	0.0f, 1.0f,
		 0.5f + x, -0.5f + y, -0.5f + z,		0.0f, 0.0f, 0.0f,	1.0f, 1.0f,
		 0.5f + x, -0.5f + y,  0.5f + z,		0.0f, 0.0f, 0.0f,	1.0f, 0.0f,
		-0.5f + x, -0.5f + y,  0.5f + z,		0.0f, 0.0f, 0.0f,	0.0f, 0.0f,
	};


	for (int i = 0; i < 6; i++) {
		VAOs[i].Bind();
		VBO VBO1(i == 0 ? vertices1 : i == 1 ? vertices2 : i == 2 ? vertices3 : i == 3 ? vertices4 : i == 4 ? vertices5 : vertices6, sizeof(vertices1));
		EBO EBO1(indices, sizeof(indices));

		VBOs.push_back(VBO1);

		EBOs.push_back(EBO1);

		VAOs[i].LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
		VAOs[i].LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		VAOs[i].LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

		VAOs[i].Unbind();
		VBO1.Unbind();
		EBO1.Unbind();

		EBO1.Delete();
		VBO1.Delete();

		if (id == "grass_block") Textures = { (*Texels)[1], (*Texels)[1], (*Texels)[1], (*Texels)[1], (*Texels)[0], (*Texels)[2] };

		else if (id == "dirt_block") Textures = { (*Texels)[2],(*Texels)[2], (*Texels)[2], (*Texels)[2], (*Texels)[2], (*Texels)[2]};

		
		else if (id == "bedrock_block") Textures = { (*Texels)[3], (*Texels)[3], (*Texels)[3], (*Texels)[3], (*Texels)[3], (*Texels)[3] };

		else if (id == "stone_block") Textures = { (*Texels)[4],(*Texels)[4], (*Texels)[4], (*Texels)[4], (*Texels)[4], (*Texels)[4] };

		else Textures = { (*Texels)[1], (*Texels)[1], (*Texels)[1], (*Texels)[1], (*Texels)[1], (*Texels)[1] };
	}

	hasInit = true;
}

void Block::Render(bool neighbours[6])
{
	if (id == "air") return;

	int x = pos[0] + 1;
	int y = pos[1] + 1;
	int z = pos[2] + 1;
	for (int i = 0; i < 6; i++)
	{
		if (neighbours[i] == true) continue;

		Textures[i].Bind();
		VAOs[i].Bind();

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
}

void Block::getTextures()
{
	if (id == "grass_block")
	{
		textures[0] = (char*)"assets/grass_block_side.png";
		textures[1] = (char*)"assets/grass_block_side.png";
		textures[2] = (char*)"assets/grass_block_side.png";
		textures[3] = (char*)"assets/grass_block_side.png";
		textures[4] = (char*)"assets/grass.png";
		textures[5] = (char*)"assets/dirt.png";
	}

	else if (id == "dirt_block")
	{
		textures[0] = (char*)"assets/dirt.png";
		textures[1] = (char*)"assets/dirt.png";
		textures[2] = (char*)"assets/dirt.png";
		textures[3] = (char*)"assets/dirt.png";
		textures[4] = (char*)"assets/dirt.png";
		textures[5] = (char*)"assets/dirt.png";
	}

	else if (id == "bedrock_block")
	{
		textures[0] = (char*)"assets/bedrock.png";
		textures[1] = (char*)"assets/bedrock.png";
		textures[2] = (char*)"assets/bedrock.png";
		textures[3] = (char*)"assets/bedrock.png";
		textures[4] = (char*)"assets/bedrock.png";
		textures[5] = (char*)"assets/bedrock.png";
	}

	else if (id == "stone_block")
	{
		textures[0] = (char*)"assets/stone.png";
		textures[1] = (char*)"assets/stone.png";
		textures[2] = (char*)"assets/stone.png";
		textures[3] = (char*)"assets/stone.png";
		textures[4] = (char*)"assets/stone.png";
		textures[5] = (char*)"assets/stone.png";
	}

	else if (id == "water")
	{
		textures[0] = (char*)"assets/water_flow.png";
		textures[1] = (char*)"assets/water_flow.png";
		textures[2] = (char*)"assets/water_flow.png";
		textures[3] = (char*)"assets/water_flow.png";
		textures[4] = (char*)"assets/water_flow.png";
		textures[5] = (char*)"assets/water_flow.png";
	}

	else if (id == "oak_log")
	{
		textures[0] = (char*)"assets/oak_log.png";
		textures[1] = (char*)"assets/oak_log.png";
		textures[2] = (char*)"assets/oak_log.png";
		textures[3] = (char*)"assets/oak_log.png";
		textures[4] = (char*)"assets/oak_log_top.png";
		textures[5] = (char*)"assets/oak_log_top.png";
	}

	else if (id == "air")
	{
		textures[0] = (char*)"a";
		textures[1] = (char*)"a";
		textures[2] = (char*)"a";
		textures[3] = (char*)"a";
		textures[4] = (char*)"a";
		textures[5] = (char*)"a";
	}
}


void Block::Delete()
{
	for (int i = 0; i < sizeof(VAOs) / sizeof(VAO); i++) VAOs[i].Delete();
	for (int i = 0; i < VBOs.size(); i++) VBOs[i].Delete();
	for (int i = 0; i < EBOs.size(); i++) EBOs[i].Delete();
	//for (int i = 0; i < Textures.size(); i++) { Textures[i].Delete(); }
}

