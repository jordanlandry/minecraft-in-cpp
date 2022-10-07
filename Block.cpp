#include "headers/Block.h"


Block::Block(int aId, float aPos[3])
{
	indices = { 0, 2, 1, 0, 3, 2 };
	id = aId;
	if (id == 1)
	{
		textures[0] = (char*) "assets/grass_block_side.png";
		textures[1] = (char*) "assets/grass_block_side.png";
		textures[2] = (char*) "assets/grass_block_side.png";
		textures[3] = (char*) "assets/grass_block_side.png";
		textures[4] = (char*) "assets/grass.png";
		textures[5] = (char*) "assets/dirt.png";
	}

	if (id == 2)
	{
		textures[0] = (char*)"assets/dirt.png";
		textures[1] = (char*)"assets/dirt.png";
		textures[2] = (char*)"assets/dirt.png";
		textures[3] = (char*)"assets/dirt.png";
		textures[4] = (char*)"assets/dirt.png";
		textures[5] = (char*)"assets/dirt.png";
	}

	pos[0] = aPos[0];
	pos[1] = aPos[1];
	pos[2] = aPos[2];
}

void Block::Init(Shader shaderProgram)
{
	float x = pos[0];
	float y = pos[1];
	float z = pos[2];

	GLfloat vertices1[] = {
		-0.5f + x, -0.5f + y,  0.5f + z,		0.0f, 0.0f, 0.0f,	0.0f, 0.0f,
		 0.5f + x, -0.5f + y,  0.5f + z,		0.0f, 0.0f, 0.0f,	1.0f, 0.0f,
		 0.5f + x,  0.5f + y,  0.5f + z,		0.0f, 0.0f, 0.0f,	1.0f, 1.0f,
		-0.5f + x,  0.5f + y,  0.5f + z,		0.0f, 0.0f, 0.0f,	0.0f, 1.0f,
	};

	GLfloat vertices2[] = {
		0.5f + x, -0.5f + y,  0.5f + z,		0.0f, 0.0f, 0.0f,	0.0f, 0.0f,
		0.5f + x, -0.5f + y, -0.5f + z,		0.0f, 0.0f, 0.0f,	1.0f, 0.0f,
		0.5f + x,  0.5f + y, -0.5f + z,		0.0f, 0.0f, 0.0f,	1.0f, 1.0f,
		0.5f + x,  0.5f + y,  0.5f + z,		0.0f, 0.0f, 0.0f,	0.0f, 1.0f,
	};

	GLfloat vertices3[] = {
		-0.5f + x, -0.5f + y, -0.5f + z,		0.0f, 0.0f, 0.0f,	0.0f, 0.0f,
		 0.5f + x, -0.5f + y, -0.5f + z,		0.0f, 0.0f, 0.0f,	1.0f, 0.0f,
		 0.5f + x,  0.5f + y, -0.5f + z,		0.0f, 0.0f, 0.0f,	1.0f, 1.0f,
		-0.5f + x,  0.5f + y, -0.5f + z,		0.0f, 0.0f, 0.0f,	0.0f, 1.0f,
	};

	GLfloat vertices4[] = {
		-0.5f + x, -0.5f + y,  0.5f + z,		0.0f, 0.0f, 0.0f,	0.0f, 0.0f,
		-0.5f + x, -0.5f + y, -0.5f + z,		0.0f, 0.0f, 0.0f,	1.0f, 0.0f,
		-0.5f + x,  0.5f + y, -0.5f + z,		0.0f, 0.0f, 0.0f,	1.0f, 1.0f,
		-0.5f + x,  0.5f + y,  0.5f + z,		0.0f, 0.0f, 0.0f,	0.0f, 1.0f,
	};

	GLfloat vertices5[] = {
		-0.5f + x,  0.5f + y,  0.5f + z,		0.0f, 0.0f, 0.0f,	0.0f, 0.0f,
		 0.5f + x,  0.5f + y,  0.5f + z,		0.0f, 0.0f, 0.0f,	1.0f, 0.0f,
		 0.5f + x,  0.5f + y, -0.5f + z,		0.0f, 0.0f, 0.0f,	1.0f, 1.0f,
		-0.5f + x,  0.5f + y, -0.5f + z,		0.0f, 0.0f, 0.0f,	0.0f, 1.0f,
	};

	GLfloat vertices6[] = {
		-0.5f + x, -0.5f + y,  0.5f + z,		0.0f, 0.0f, 0.0f,	0.0f, 0.0f,
		 0.5f + x, -0.5f + y,  0.5f + z,		0.0f, 0.0f, 0.0f,	1.0f, 0.0f,
		 0.5f + x, -0.5f + y, -0.5f + z,		0.0f, 0.0f, 0.0f,	1.0f, 1.0f,
		-0.5f + x, -0.5f + y, -0.5f + z,		0.0f, 0.0f, 0.0f,	0.0f, 1.0f,
	};

	GLuint indices[] = {0, 2, 1, 0, 3, 2};
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

		Texture tex(textures[i], GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
		Textures.push_back(tex);

		tex.texUnit(shaderProgram, "tex0", 0);
	}
}

void Block::Render()
{
	for (int i = 0; i < 6; i++)
	{
		Textures[i].Bind();
		VAOs[i].Bind();
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
	}
}