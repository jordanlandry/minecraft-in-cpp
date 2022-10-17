#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

#include"shaderClass.h"

class Camera
{
public:
	glm::vec3 Position;
	glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);

	bool firstClick = true;

	int width;
	int height;

	float speed = 0.1f;
	float sensitivity = 100.0f;

	int maxReach = 6;
	int clickPositions[6][3];
	int rightClickPositions[6][3];

	float yVel = 0;
	bool isJumping = false;
	float jumpSpeed = 0.015f;
	int playerHeight = 1;

	float G = 0.01f;

	Camera(int width, int height, glm::vec3 position);

	void Matrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform);
	void Inputs(GLFWwindow* window);
	int* GetClickPosition(GLFWwindow* window);

	void PrintCoords();
};
#endif