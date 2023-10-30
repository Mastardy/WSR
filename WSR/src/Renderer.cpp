#include "Renderer.hpp"

#include <iostream>
#include <cmath>

Renderer::Renderer(int width, int height)
{
	this->width = width;
	this->height = height;
	this->data = new GLubyte[width * height * 3];

	int pixel = 0;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width * 3; j += 3)
		{
			data[pixel] = 255;
			data[pixel + 1] = 180;
			data[pixel + 2] = 255;
			pixel += 3;
		}
	}
}

Renderer::~Renderer()
{
	delete[] data;
}

void Renderer::DrawLine(Point start, Point end)
{
	bool steep = false;

	if (std::abs(start.x - end.x) < std::abs(start.y - end.y))
	{
		std::swap(start.x, end.x);
		std::swap(start.y, end.y);
		steep = true;
	}

	if (start.x > start.y)
	{
		std::swap(start.x, end.x);
		std::swap(start.y, end.y);
	}

	int dx = end.x - start.x;
	int dy = end.y - start.y;

	int dError = std::abs(dy) * 2;
	int error = 0;

	int y = start.y;
	for (int x = start.x; x <= end.x; x++)
	{
		if (steep)
		{
			SetPixel(y, x);
		}
		else
		{
			SetPixel(x, y);
		}

		error += dError;

		if (error > dx)
		{
			y += (end.y > start.y ? 1 : -1);
			error -= dx * 2;
		}
	}
}

void Renderer::DrawTriangle(Point a, Point b, Point c)
{
	DrawLine(a, b);
	DrawLine(b, c);
	DrawLine(c, a);
}

void Renderer::SetColor(const Color& color)
{
	currentColor = color;
}

void Renderer::SetPixel(int x, int y)
{
	if (x < 0 || x >= width || y < 0 || y >= height) return;
		
	y = height - y;

	int pixel = (y * width * 3) + (x * 3);
	data[pixel] = currentColor.r;
	data[++pixel] = currentColor.g;
	data[++pixel] = currentColor.b;
}