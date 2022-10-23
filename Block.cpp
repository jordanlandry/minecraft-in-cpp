#include "headers/Block.h"
#include <chrono>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>


Block::Block()
{
	id = (char*)"air";
	hasInit = false;
	pos[0] = 0;
	pos[1] = 0;
	pos[2] = 0;
}

Block::Block(char* aId, float aPos[3])
{
	id = aId;

	hasInit = false;

	pos[0] = aPos[0];
	pos[1] = aPos[1];
	pos[2] = aPos[2];
}

void Block::Init(Shader* shaderProgram, bool chunks[6], std::vector<Texture>* Texels)
{
	int x = pos[0];
	int y = pos[1];
	int z = pos[2];

	if (chunks[0] == true && chunks[1] == true && chunks[2] == true && chunks[3] == true && chunks[4] == true && chunks[5] == true) return;

	// Front
	GLfloat vertices1[] = {
		-0.5f + x, -0.5f + y,  0.5f + z,		0.0f, 0.0f, 0.0f,	0.0f, 0.0f,		-0.5f, -0.5f,  0.5f,
		 0.5f + x, -0.5f + y,  0.5f + z,		0.0f, 0.0f, 0.0f,	1.0f, 0.0f,		-0.5f, -0.5f,  0.5f,
		 0.5f + x,  0.5f + y,  0.5f + z,		0.0f, 0.0f, 0.0f,	1.0f, 1.0f,		 0.0f, -0.5f,  0.5f,
		-0.5f + x,  0.5f + y,  0.5f + z,		0.0f, 0.0f, 0.0f,	0.0f, 1.0f,		 0.0f, -0.5f,  0.5f,
	};

	// Right
	GLfloat vertices2[] = {
		0.5f + x, -0.5f + y,  0.5f + z,			0.0f, 0.0f, 0.0f,	0.0f, 0.0f,		0.0f, -0.5f,  0.5f,
		0.5f + x, -0.5f + y, -0.5f + z,			0.0f, 0.0f, 0.0f,	1.0f, 0.0f,		0.0f, -0.5f,  0.5f,
		0.5f + x,  0.5f + y, -0.5f + z,			0.0f, 0.0f, 0.0f,	1.0f, 1.0f,		0.0f, -0.5f,  0.5f,
		0.5f + x,  0.5f + y,  0.5f + z,			0.0f, 0.0f, 0.0f,	0.0f, 1.0f,		0.0f, -0.5f,  0.5f,
	};

	// Back
	GLfloat vertices3[] = {
		-0.5f + x,  0.5f + y, -0.5f + z,		0.0f, 0.0f, 0.0f,	0.0f, 1.0f,		0.0f, -0.5f,  0.5f,
		 0.5f + x,  0.5f + y, -0.5f + z,		0.0f, 0.0f, 0.0f,	1.0f, 1.0f,		0.0f, -0.5f,  0.5f,
		 0.5f + x, -0.5f + y, -0.5f + z,		0.0f, 0.0f, 0.0f,	1.0f, 0.0f,		0.0f, -0.5f,  0.5f,
		-0.5f + x, -0.5f + y, -0.5f + z,		0.0f, 0.0f, 0.0f,	0.0f, 0.0f,		0.0f, -0.5f,  0.5f,
	};

	// Left
	GLfloat vertices4[] = {
		-0.5f + x,  0.5f + y,  0.5f + z,		0.0f, 0.0f, 0.0f,	0.0f, 1.0f,		0.0f, -0.5f,  0.5f,
		-0.5f + x,  0.5f + y, -0.5f + z,		0.0f, 0.0f, 0.0f,	1.0f, 1.0f,		0.0f, -0.5f,  0.5f,
		-0.5f + x, -0.5f + y, -0.5f + z,		0.0f, 0.0f, 0.0f,	1.0f, 0.0f,		0.0f, -0.5f,  0.5f,
		-0.5f + x, -0.5f + y,  0.5f + z,		0.0f, 0.0f, 0.0f,	0.0f, 0.0f,		0.0f, -0.5f,  0.5f,
	};

	// Top
	GLfloat vertices5[] = {
		-0.5f + x,  0.5f + y,  0.5f + z,		0.0f, 0.0f, 0.0f,	0.0f, 0.0f,		0.0f, -0.5f,  0.5f,
		 0.5f + x,  0.5f + y,  0.5f + z,		0.0f, 0.0f, 0.0f,	1.0f, 0.0f,		0.0f, -0.5f,  0.5f,
		 0.5f + x,  0.5f + y, -0.5f + z,		0.0f, 0.0f, 0.0f,	1.0f, 1.0f,		0.0f, -0.5f,  0.5f,
		-0.5f + x,  0.5f + y, -0.5f + z,		0.0f, 0.0f, 0.0f,	0.0f, 1.0f,		0.0f, -0.5f,  0.5f,
	};

	// Bottom
	GLfloat vertices6[] = {
		-0.5f + x, -0.5f + y, -0.5f + z,		0.0f, 0.0f, 0.0f,	0.0f, 1.0f,		0.0f, -0.5f,  0.5f,
		 0.5f + x, -0.5f + y, -0.5f + z,		0.0f, 0.0f, 0.0f,	1.0f, 1.0f,		0.0f, -0.5f,  0.5f,
		 0.5f + x, -0.5f + y,  0.5f + z,		0.0f, 0.0f, 0.0f,	1.0f, 0.0f,		0.0f, -0.5f,  0.5f,
		-0.5f + x, -0.5f + y,  0.5f + z,		0.0f, 0.0f, 0.0f,	0.0f, 0.0f,		0.0f, -0.5f,  0.5f,
	};

	// Assign textures based on id
	if		(id == "grass_block")		Textures = { (*Texels)[1],  (*Texels)[1],  (*Texels)[1],  (*Texels)[1],  (*Texels)[0],  (*Texels)[2]  };
	else if (id == "dirt_block")		Textures = { (*Texels)[2],  (*Texels)[2],  (*Texels)[2],  (*Texels)[2],  (*Texels)[2],  (*Texels)[2]  };
	else if (id == "bedrock_block")		Textures = { (*Texels)[3],  (*Texels)[3],  (*Texels)[3],  (*Texels)[3],  (*Texels)[3],  (*Texels)[3]  };
	else if (id == "stone_block")		Textures = { (*Texels)[4],  (*Texels)[4],  (*Texels)[4],  (*Texels)[4],  (*Texels)[4],  (*Texels)[4]  };
	else if (id == "sand_block")		Textures = { (*Texels)[5],  (*Texels)[5],  (*Texels)[5],  (*Texels)[5],  (*Texels)[5],  (*Texels)[5]  };
	else if (id == "water")				Textures = { (*Texels)[6],  (*Texels)[6],  (*Texels)[6],  (*Texels)[6],  (*Texels)[6],  (*Texels)[6]  };
	else if (id == "oak_log")			Textures = { (*Texels)[7],  (*Texels)[7],  (*Texels)[7],  (*Texels)[7],  (*Texels)[8],  (*Texels)[8]  };
	else if (id == "oak_leaves")		Textures = { (*Texels)[9],  (*Texels)[9],  (*Texels)[9],  (*Texels)[9],  (*Texels)[9],  (*Texels)[9]  };
	else if (id == "birch_log")			Textures = { (*Texels)[10], (*Texels)[10], (*Texels)[10], (*Texels)[10], (*Texels)[11], (*Texels)[11] };
	else if (id == "birch_leaves")		Textures = { (*Texels)[12], (*Texels)[12], (*Texels)[12], (*Texels)[12], (*Texels)[12], (*Texels)[12] };
	else								Textures = { (*Texels)[1],  (*Texels)[1],  (*Texels)[1],  (*Texels)[1],  (*Texels)[1],  (*Texels)[1]  };


	// Link VAOs, VBOs, EBOs
	for (int i = 0; i < 6; i++) {
		//if (chunks[i] == true) continue;

		VAOs[i].Bind();
		VBO VBO1(i == 0 ? vertices1 : i == 1 ? vertices2 : i == 2 ? vertices3 : i == 3 ? vertices4 : i == 4 ? vertices5 : vertices6, sizeof(vertices1));
		EBO EBO1(indices, sizeof(indices));

		VBOs.push_back(VBO1);
		EBOs.push_back(EBO1);

		/*VAOs[i].LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
		VAOs[i].LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		VAOs[i].LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));*/


		VAOs[i].LinkAttrib(VBO1, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
		VAOs[i].LinkAttrib(VBO1, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
		VAOs[i].LinkAttrib(VBO1, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
		VAOs[i].LinkAttrib(VBO1, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));

		VAOs[i].Unbind();
		VBO1.Unbind();
		EBO1.Unbind();

		EBO1.Delete();
		VBO1.Delete();	
	}

	/*glm::vec3 blockPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 blockModel = glm::mat4(1.0f);
	blockModel = glm::translate(blockModel, blockPos);
	shaderProgram->Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram->ID, "model"), 1, GL_FALSE, glm::value_ptr(blockModel));
	glUniform4f(glGetUniformLocation(shaderProgram->ID, "lightColor"), 1.0f, 1.0f, 1.0f, 1.0f);
	glUniform3f(glGetUniformLocation(shaderProgram->ID, "lightPos"), 1.0f, 25.0f, 10.0f);*/

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
		if (neighbours[i]) continue;
		Textures[i].Bind();
		VAOs[i].Bind();

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
}


void Block::Delete()
{
	for (int i = 0; i < sizeof(VAOs) / sizeof(VAO); i++) VAOs[i].Delete();
	for (int i = 0; i < VBOs.size(); i++) VBOs[i].Delete();
	for (int i = 0; i < EBOs.size(); i++) EBOs[i].Delete();
}
