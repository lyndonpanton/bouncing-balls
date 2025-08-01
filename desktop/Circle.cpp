#include "Shape.h"
#include "Circle.h"

#include <iostream>

Circle::Circle()
	: Shape()
	, m_radius(50)
	, m_point_count(32)
	, m_initial_point_count(m_point_count)
{

}

Circle::Circle(const Circle& circle)
	: Shape(
		circle.get_name(), circle.get_position(), circle.get_velocity(), circle.get_colour(), circle.get_scale(),
		circle.get_name(), circle.get_position(), circle.get_velocity(), circle.get_colour(), circle.get_scale()
	)
	, m_radius(circle.get_radius())
	, m_point_count(circle.get_point_count())
{
	m_initial_point_count = m_point_count;
}


Circle::Circle(
	char* name, int position[], float velocity[], float colour[], float scale, int radius, int point_count,
	char* initial_name, int initial_position[], float initial_velocity[], float initial_colour[], float initial_scale,
	int initial_point_count
)
	: Shape(
		name, position, velocity, colour, scale,
		initial_name, initial_position, initial_velocity, initial_colour, initial_scale
	)
	, m_radius(radius)
	, m_point_count(point_count)
	, m_initial_point_count(initial_point_count)
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

int Circle::get_point_count() const
{
	return m_point_count;
}

void Circle::set_segments(int segments)
{
	m_point_count = segments;
}

void Circle::reset()
{
	Shape::reset();
	std::cout << "Child" << std::endl;
	m_point_count = m_initial_point_count;
}
