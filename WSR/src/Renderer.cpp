#include "Renderer.hpp"

#include <random>
#include <iostream>

Renderer::Renderer(int width, int height)
{
	this->width = width;
	this->height = height;
	this->data = new GLubyte[width * height * 3];

	srand(time(nullptr));

	int pixel = 0;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width * 3; j += 3)
		{
			data[pixel] = rand() % 255;
			data[pixel + 1] = rand() % 255;
			data[pixel + 2] = rand() % 255;
			pixel += 3;
		}
	}
}

Renderer::~Renderer()
{
	delete[] data;
}

void Renderer::Update()
{

}

void Renderer::Resize(int width, int height)
{
	this->width = width;
	this->height = height;
	delete[] this->data;
	this->data = new GLubyte[width * height * 3];

	srand(time(nullptr));

	int pixel = 0;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width * 3; j += 3)
		{
			data[pixel] = rand() % 255;
			data[pixel + 1] = rand() % 255;
			data[pixel + 2] = rand() % 255;
			pixel += 3;
		}
	}
}