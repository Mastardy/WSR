#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>

class Window
{
public:
	Window(int width, int height);
	~Window();

	void SetFramebufferSizeCallback(GLFWframebuffersizefun callback);
	void ProcessInput();
	void UpdateTexture(int width, int height, unsigned char* data);
	void Update();
	int ShouldClose();

private:
	GLFWwindow* window;
	int width, height;
	unsigned int VAO, VBO, EBO, shaderProgram;
};