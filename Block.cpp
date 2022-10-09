#include "headers/Block.h"

Block::Block(char* aId, float aPos[3])
{
	hasInit = false;

	indices = { 0, 2, 1, 0, 3, 2 };
	id = aId;
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
	else
	{
		textures[0] = (char*)"";
		textures[1] = (char*)"";
		textures[2] = (char*)"";
		textures[3] = (char*)"";
		textures[4] = (char*)"";
		textures[5] = (char*)"";
	}

	pos[0] = aPos[0];
	pos[1] = aPos[1];
	pos[2] = aPos[2];
}

void Block::Init(Shader shaderProgram, bool world[101][60][101])
{
	if (hasInit) return;
	int x = pos[0];
	int y = pos[1];
	int z = pos[2];

	if (world[x + 1][y + 1][z + 2] == true && world[x + 2][y + 1][z + 1] == true && world[x + 1][y + 1][z] == true && world[x][y + 1][z + 1] == true && world[x + 1][y + 2][z + 1] == true && world[x + 1][y][z + 1] == true) {
		return;
	}

	// Front
	GLfloat vertices1[] = {
		-0.5f + x, -0.5f + y,  0.5f + z,		0.0f, 0.0f, 0.0f,	0.0f, 0.0f,
		 0.5f + x, -0.5f + y,  0.5f + z,		0.0f, 0.0f, 0.0f,	1.0f, 0.0f,
		 0.5f + x,  0.5f + y,  0.5f + z,		0.0f, 0.0f, 0.0f,	1.0f, 1.0f,
		-0.5f + x,  0.5f + y,  0.5f + z,		0.0f, 0.0f, 0.0f,	0.0f, 1.0f,
	};

	// Right
	GLfloat vertices2[] = {
		0.5f + x, -0.5f + y,  0.5f + z,		0.0f, 0.0f, 0.0f,	0.0f, 0.0f,
		0.5f + x, -0.5f + y, -0.5f + z,		0.0f, 0.0f, 0.0f,	1.0f, 0.0f,
		0.5f + x,  0.5f + y, -0.5f + z,		0.0f, 0.0f, 0.0f,	1.0f, 1.0f,
		0.5f + x,  0.5f + y,  0.5f + z,		0.0f, 0.0f, 0.0f,	0.0f, 1.0f,
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

	GLuint indices[] = { 0, 2, 1, 0, 3, 2 };
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

		Texture tex(textures[i], GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
		Textures.push_back(tex);

		tex.texUnit(shaderProgram, "tex0", 0);
	}

	hasInit = true;
}

void Block::Render(bool world[101][60][101])
{
	int x = pos[0] + 1;
	int y = pos[1] + 1;
	int z = pos[2] + 1;
	for (int i = 0; i < Textures.size(); i++)
	{
		if (i == 0 && world[x][y][z + 1] == true) continue;		// Front
		if (i == 1 && world[x + 1][y][z] == true) continue;		// Right
		if (i == 2 && world[x][y][z - 1] == true) continue;		// Back
		if (i == 3 && world[x - 1][y][z] == true) continue;		// Left
		if (i == 4 && world[x][y + 1][z] == true) continue;		// Top
		if (i == 5 && world[x][y - 1][z] == true) continue;		// Bottom

		Textures[i].Bind();
		VAOs[i].Bind();
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
	}
}

void Block::Delete()
{
	for (int i = 0; i < VBOs.size(); i++)
	{
		VBOs[i].Delete();
	}
}