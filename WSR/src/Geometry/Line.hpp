#pragma once

#include "Shape.hpp"

class Line : public Shape
{
public:
	Line(const Point& a, const Point& b, const Color& c);

	virtual void Render(Renderer& renderer);

private:
	Point start, end;
	Color color;
};