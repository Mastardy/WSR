#pragma once

struct Point
{
	Point()
	{
		x = 0;
		y = 0;
	}

	Point(int x, int y)
	{
		this->x = x;
		this->y = y;
	}

	Point operator+(const Point& other)
	{
		return Point(x + other.x, y + other.y);
	}

	Point operator-(const Point& other)
	{
		return Point(x - other.x, y - other.y);
	}

	Point operator*(float scalar)
	{
		return Point(x * scalar, y * scalar);
	}

	int x, y;
};