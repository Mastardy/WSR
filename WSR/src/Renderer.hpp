#pragma once

#include <GLFW/glfw3.h>

#include "Geometry/Color.hpp"

class Renderer
{
public:
	Renderer(int width, int height);
	~Renderer();

	void SetColor(const Color& color);
	void SetPixel(int x, int y);

	int width;
	int height;
	GLubyte* data;

private:
	Color currentColor;
};