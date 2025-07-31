#pragma once

#ifndef SHAPE
#define SHAPE

#include <string>
#include <array>

class Shape
{
	std::string m_name;
	int* m_position;
	float* m_velocity;
	int* m_colour;
	float* m_scale;

public:
	bool m_is_visible = true;

	// General
	Shape();
	Shape(const Shape&);
	Shape(std::string, int[], float[], int[], float[]);
	virtual ~Shape();

	// Getters
	std::string get_name() const;
	bool get_visibility() const;
	int* get_position() const;
	float* get_velocity() const;
	int* get_colour() const;
	float* get_scale() const;

	// Setters
	void set_name(std::string);
	void set_visibility(bool);
	void set_position(int*);
	void set_velocity(float*);
	void set_colour(int*);
	void set_scale(float*);
};

#endif
