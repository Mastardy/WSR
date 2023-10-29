#include "Line.hpp"

#include <cmath>

Line::Line(const Point& a, const Point& b, const Color& c)
{
	start = a;
	end = b;
	this->color = c;
}

void Line::Render(Renderer& renderer)
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

	renderer.SetColor(color);

	int y = start.y;
	for (int x = start.x; x <= end.x; x++)
	{
		if (steep)
		{
			renderer.SetPixel(y, x);
		}
		else
		{
			renderer.SetPixel(x, y);
		}

		error += dError;

		if (error > dx)
		{
			y += (end.y > start.y ? 1 : -1);
			error -= dx * 2;
		}
	}
}