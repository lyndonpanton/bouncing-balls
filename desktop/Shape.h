#pragma once

#ifndef SHAPE
#define SHAPE

#include <string>
#include <array>

class Shape
{
	int* m_position;

public:
	std::string m_name;
	bool m_is_visible = true;
	float* m_velocity;
	float* m_colour;
	float* m_scale;

	// General
	Shape();
	Shape(const Shape&);
	Shape(std::string, int[], float[], float[], float[]);
	virtual ~Shape();

	// Getters
	std::string get_name() const;
	bool get_visibility() const;
	int* get_position() const;
	float* get_velocity() const;
	float* get_colour() const;
	float* get_scale() const;

	// Setters
	void set_name(std::string);
	void set_visibility(bool);
	void set_position(int*);
	void set_velocity(float*);
	void set_colour(float*);
	void set_scale(float*);
};

#endif
