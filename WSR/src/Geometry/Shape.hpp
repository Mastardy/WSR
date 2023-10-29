#pragma once

#include "../Renderer.hpp"
#include "Point.hpp"
#include "Color.hpp"

class Shape
{
public:
	virtual void Render(Renderer& renderer) = 0;
};