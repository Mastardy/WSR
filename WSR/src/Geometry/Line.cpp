#include "Line.hpp"

Line::Line(const Point& a, const Point& b, const Color& c)
{
	start = a;
	end = b;
	this->color = c;
}

void Line::Render(Renderer& renderer)
{
	for (float t = 0.0f; t < 1.0f; t += 0.01f)
	{
		int x = start.x + (end.x - start.x) * t;
		int y = start.y + (end.y - start.y) * t;
		renderer.SetPixel(x, y, color);
	}
}