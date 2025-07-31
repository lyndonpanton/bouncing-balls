#include "Shape.h"
#include "Rectangle.h"

Rectangle::Rectangle()
	: Shape()
	, m_width(100)
	, m_height(50)
{

}

Rectangle::Rectangle(const Rectangle& rectangle)
	: Shape(rectangle.get_name(), rectangle.get_position(), rectangle.get_velocity(), rectangle.get_colour(), rectangle.get_scale())
	, m_width(rectangle.get_width())
	, m_height(rectangle.get_height())
{

}


Rectangle::Rectangle(std::string name, int position[], float velocity[], float colour[], float scale[], int width, int height)
	: Shape(name, position, velocity, colour, scale)
	, m_width(width)
	, m_height(height)
{

}

Rectangle::~Rectangle()
{

}

int Rectangle::get_width() const
{
	return m_width;
}

void Rectangle::set_width(int width)
{
	m_width = width;
}

int Rectangle::get_height() const
{
	return m_height;
}

void Rectangle::set_height(int height)
{
	m_height = height;
}
