#include "Shape.h"

#include <iostream>

// General

Shape::Shape()
	: m_position(new int[2] { 0, 0 })
	, m_velocity(new float[2] { 0.0f, 0.0f })
	, m_colour(new float[3] { 0, 0, 0 })
	, m_scale(1.0f)
	, m_initial_position(m_position)
	, m_initial_velocity(m_velocity)
	, m_initial_colour(m_colour)
	, m_initial_scale(m_scale)
{
	/*char initial_buffer[] = "Shape";
	m_initial_name = initial_buffer;*/
	
	char buffer[] = "Shape";
	m_name = buffer;

	m_initial_name = { m_name };
	m_initial_velocity = { m_velocity };
	m_initial_position = { m_position };
	m_initial_colour = { m_colour };
	m_initial_scale = m_scale;
}

Shape::Shape(
	char* name, int position[], float velocity[], float colour[], float scale,
	std::string initial_name, int initial_position[], float initial_velocity[], float initial_colour[], float initial_scale
)
	: m_name(name)
	, m_position(new int[2] { position[0], position[1] })
	, m_velocity(new float[2] { velocity[0], velocity[1] })
	, m_colour(new float[3] { colour[0], colour[1], colour[2] })
	, m_scale(scale)
	, m_initial_name(initial_name)
	, m_initial_position(initial_position)
	, m_initial_velocity(initial_velocity)
	, m_initial_colour(initial_colour)
	, m_initial_scale(initial_scale)
{

}

Shape::Shape(const Shape& shape)
	: m_name(shape.get_name())
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

char* Shape::get_name() const
{
	return m_name;
}

bool Shape::get_shape_visibility() const
{
	return m_shape_is_visible;
}

bool Shape::get_text_visibility() const
{
	return m_text_is_visible;
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

float Shape::get_scale() const
{
	return m_scale;
}

// Setters

void Shape::set_name(char* name)
{
	m_name = name;
}

void Shape::set_shape_visibility(bool is_visibile)
{
	m_shape_is_visible = is_visibile;
}

void Shape::set_text_visibility(bool is_visibile)
{
	m_text_is_visible = is_visibile;
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

void Shape::set_scale(float scale)
{
	m_scale = scale;
}

// General

void Shape::reset()
{
	strcpy_s(m_name, m_initial_name.length() + 1, m_initial_name.data());
	m_position = m_initial_position;
	m_velocity = m_initial_velocity;
	m_colour = m_initial_colour;
	m_scale = m_initial_scale;
}
