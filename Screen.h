#ifndef SCREEN_CLASS_H
#define SCREEN_CLASS_H

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Screen
{
public:
	int width;
	int height;

	GLFWwindow* window;

	Screen(int w, int h);
	int Init();
	void Update();
	void Delete();
};

#endif