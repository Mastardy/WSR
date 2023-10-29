#pragma once

struct Color
{
	Color()
	{
		r = 0;
		g = 0;
		b = 0;
		a = 0;
	}

	Color(int r, int g, int b, int a)
	{
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}

	int r, g, b, a;
};