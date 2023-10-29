#pragma once

#include <GLFW/glfw3.h>

#include "Geometry/Color.hpp"

class Renderer
{
public:
	Renderer(int width, int height);
	~Renderer();

	void SetPixel(int x, int y, const Color& color);

	int width;
	int height;
	GLubyte* data;
};