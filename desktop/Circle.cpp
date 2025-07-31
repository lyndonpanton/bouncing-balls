#include "Shape.h"
#include "Circle.h"

Circle::Circle()
	: Shape()
	, m_radius(50)
{

}

Circle::Circle(const Circle& circle)
	: Shape(circle.get_c_name(), circle.get_position(), circle.get_velocity(), circle.get_colour(), circle.get_scale())
	, m_radius(circle.get_radius())
{
}


Circle::Circle(char* name, int position[], float velocity[], float colour[], float scale[], int radius)
	: Shape(name, position, velocity, colour, scale)
	, m_radius(radius)
{

}

Circle::~Circle()
{

}

int Circle::get_radius() const
{
	return m_radius;
}

void Circle::set_radius(int radius)
{
	m_radius = radius;
}
