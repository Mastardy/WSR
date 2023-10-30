#include "Renderer.hpp"

#include <iostream>
#include <cmath>

Renderer::Renderer(int width, int height)
{
	this->width = width;
	this->height = height;
	this->data = new GLubyte[width * height * 3];
	this->wireframe = false;

	int pixel = 0;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width * 3; j += 3)
		{
			data[pixel] = 25;
			data[pixel + 1] = 25;
			data[pixel + 2] = 25;
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
		std::swap(start.x, start.y);
		std::swap(end.x, end.y);
		steep = true;
	}

	if (start.x > end.x)
	{
		std::swap(start.x, end.x);
		std::swap(start.y, end.y);
	}

	int dx = end.x - start.x;
	int dy = end.y - start.y;

	int dError = std::abs(dy) * 2;
	int error = 0;

	int y = start.y;
	if (steep)
	{
		for (int x = start.x; x <= end.x; ++x)
		{
			SetPixel(y, x);
			error += dError;
			if (error > dx)
			{
				y += (end.y > start.y ? 1 : -1);
				error -= dx * 2;
			}
		}
	}
	else
	{
		for (int x = start.x; x <= end.x; ++x)
		{
			SetPixel(x, y);
			error += dError;
			if (error > dx)
			{
				y += (end.y > start.y ? 1 : -1);
				error -= dx * 2;
			}
		}
	}
}

void Renderer::DrawTriangle(Point a, Point b, Point c)
{
	if (wireframe)
	{
		DrawLine(a, b);
		DrawLine(b, c);
		DrawLine(c, a);
		return;
	}

	if (a.y == b.y && a.y == c.y) return;

	if (a.y > b.y) std::swap(a, b);
	if (a.y > c.y) std::swap(a, c);
	if (b.y > c.y) std::swap(b, c);

	int totalHeight = c.y - a.y;

	for (int i = 0; i < totalHeight; i++)
	{
		bool secondHalf = i > b.y - a.y || b.y == a.y;
		int segmentHeight = secondHalf ? c.y - b.y : b.y - a.y;
		float alpha = (float)i / totalHeight;
		float beta = (float)(i - (secondHalf ? b.y - a.y : 0)) / segmentHeight;
		Point A = a + (c - a) * alpha;
		Point B = secondHalf ? b + (c - b) * beta : a + (b - a) * beta;
		if (A.x > B.x) std::swap(A, B);
		for (int j = A.x; j < B.x; ++j)
		{
			SetPixel(j, a.y + i);
		}
	}
}

void Renderer::SetColor(const Color& color)
{
	currentColor = color;
}

void Renderer::SetPixel(int x, int y)
{
	if (x < 0 || x >= width || y < 0 || y >= height) return;
		
	//y = height - y;

	int pixel = (y * width * 3) + (x * 3);
	data[pixel] = currentColor.r;
	data[++pixel] = currentColor.g;
	data[++pixel] = currentColor.b;
}