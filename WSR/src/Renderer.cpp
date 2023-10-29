#include "Renderer.hpp"

#include <iostream>

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

void Renderer::SetPixel(int x, int y, const Color& color)
{
	if (x < 0 || x >= width || y < 0 || y >= height) return;

	y = height - y;

	int pixel = (y * width * 3) + (x * 3);
	data[pixel] = color.r;
	data[++pixel] = color.g;
	data[++pixel] = color.b;
	std::cout << "Written on: " << x << ", " << y << std::endl;
}