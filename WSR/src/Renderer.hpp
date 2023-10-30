#pragma once

#include <GLFW/glfw3.h>

#include "Color.hpp"
#include "Point.hpp"

class Renderer
{
public:
	Renderer(int width, int height);
	~Renderer();

	void DrawLine(Point start, Point end);
	void DrawTriangle(Point a, Point b, Point c);
	void SetColor(const Color& color);
	void SetPixel(int x, int y);

	int width;
	int height;
	GLubyte* data;

private:
	Color currentColor;
};