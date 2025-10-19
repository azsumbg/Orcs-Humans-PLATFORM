#include "pch.h"
#include "platform.h"

// PROTON ***********************

dll::PROTON::PROTON()
{
	_width = 1.0f;
	_height = 1.0f;

	end.x = start.x + _width;
	end.y = start.y + _height;

	radiusX = _width / 2.0f;
	radiusY = _height / 2.0f;

	center.x = start.x + radiusX;
	center.y = start.y + radiusY;
}
dll::PROTON::PROTON(float _sx, float _sy)
{
	start.x = _sx;
	start.y = _sy;

	_width = 1.0f;
	_height = 1.0f;

	end.x = start.x + _width;
	end.y = start.y + _height;

	radiusX = _width / 2.0f;
	radiusY = _height / 2.0f;

	center.x = start.x + radiusX;
	center.y = start.y + radiusY;
}
dll::PROTON::PROTON(float _sx, float _sy, float _swidth, float _sheight)
{
	start.x = _sx;
	start.y = _sy;

	_width = _swidth;
	_height = _sheight;

	end.x = start.x + _width;
	end.y = start.y + _height;

	radiusX = _width / 2.0f;
	radiusY = _height / 2.0f;

	center.x = start.x + radiusX;
	center.y = start.y + radiusY;
}

void dll::PROTON::SetEdges()
{
	end.x = start.x + _width;
	end.y = start.y + _height;

	center.x = start.x + radiusX;
	center.y = start.y + radiusY;
}
void dll::PROTON::NewWidth(float _new_width)
{
	_width = _new_width;
	
	end.x = start.x + _width;
	
	radiusX = _width / 2.0f;

	center.x = start.x + radiusX;
}
void dll::PROTON::NewHeight(float _new_height)
{
	_height = _new_height;

	end.y = start.y + _height;

	radiusY = _height / 2.0f;

	center.y = start.y + radiusY;
}
void dll::PROTON::NewDims(float _new_width, float _new_height)
{
	_width = _new_width;
	_height = _new_height;

	end.x = start.x + _width;
	end.y = start.y + _height;

	radiusX = _width / 2.0f;
	radiusY = _height / 2.0f;

	center.x = start.x + radiusX;
	center.y = start.y + radiusY;
}

float dll::PROTON::GetWidth() const
{
	return _width;
}
float dll::PROTON::GetHeight() const
{
	return _height;
}

/////////////////////////////////















// FUNCTIONS *******************************************

bool dll::Intersect(FRECT first, FRECT second)
{
	if (!(first.up_left.x >= second.up_right.x || first.up_right.x <= second.up_left.x
		|| first.up_left.y >= second.down_left.y || first.down_left.y <= second.up_left.y))return true;

	return false;
}