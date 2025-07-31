#include "Shape.h"

// General

Shape::Shape()
	: m_position(new int[2] { 0, 0 })
	, m_velocity(new float[2] { 0.0f, 0.0f })
	, m_colour(new float[3] { 0, 0, 0 })
	, m_scale(new float[2] { 1.0f, 1.0f })
{
	char buffer[] = "Shape";
	c_name = buffer;
}

//Shape::Shape(std::string name, int position[], float velocity[], float colour[], float scale[])
//	: m_name(name)
//	, m_position(new int[2] { position[0], position[1] })
//	, m_velocity(new float[2] { velocity[0], velocity[1] })
//	, m_colour(new float[3] { colour[0], colour[1], colour[2] })
//	, m_scale(new float[2] { scale[0], scale[1] })
//{
//
//}

Shape::Shape(char* name, int position[], float velocity[], float colour[], float scale[])
	: c_name(name)
	, m_position(new int[2] { position[0], position[1] })
	, m_velocity(new float[2] { velocity[0], velocity[1] })
	, m_colour(new float[3] { colour[0], colour[1], colour[2] })
	, m_scale(new float[2] { scale[0], scale[1] })
{

}

//Shape::Shape(const Shape& shape)
//	: m_name(shape.get_name())
//	, m_position(shape.get_position())
//	, m_velocity(shape.get_velocity())
//	, m_colour(shape.get_colour())
//	, m_scale(shape.get_scale())
//{
//
//}

Shape::Shape(const Shape& shape)
	: c_name(shape.get_c_name())
	, m_position(shape.get_position())
	, m_velocity(shape.get_velocity())
	, m_colour(shape.get_colour())
	, m_scale(shape.get_scale())
{

}

Shape::~Shape()
{

}

// Getters

//std::string Shape::get_name() const
//{
//	return m_name;
//}

char* Shape::get_c_name() const
{
	return c_name;
}

bool Shape::get_visibility() const
{
	return m_is_visible;
}

int* Shape::get_position() const
{
	return m_position;
}

float* Shape::get_velocity() const
{
	return m_velocity;
}

float* Shape::get_colour() const
{
	return m_colour;
}

float* Shape::get_scale() const
{
	return m_scale;
}

// Setters

//void Shape::set_name(std::string name)
//{
//	m_name = name;
//}

void Shape::set_c_name(char* name)
{
	c_name = name;
}

void Shape::set_visibility(bool is_visible)
{
	m_is_visible = is_visible;
}

void Shape::set_position(int* position)
{
	m_position = position;
}

void Shape::set_velocity(float* velocity)
{
	m_velocity = velocity;
}

void Shape::set_colour(float* colour)
{
	m_colour = colour;
}

void Shape::set_scale(float* scale)
{
	m_scale = scale;
}
