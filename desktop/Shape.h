#pragma once

#ifndef SHAPE
#define SHAPE

#include <string>
#include <array>

class Shape
{
	int* m_position;
	char* m_initial_name;
	int* m_initial_position;
	float* m_initial_velocity;
	float* m_initial_colour;
	float m_initial_scale;

public:
	char* m_name;
	bool m_shape_is_visible = true;
	bool m_text_is_visible = true;
	float* m_velocity;
	float* m_colour;
	float m_scale;

	// General
	Shape();
	Shape(const Shape&);
	Shape(
		char*, int[], float[], float[], float,
		char*, int[], float[], float[], float
	);
	virtual ~Shape();

	// Getters
	char* get_name() const;
	bool get_shape_visibility() const;
	bool get_text_visibility() const;
	int* get_position() const;
	float* get_velocity() const;
	float* get_colour() const;
	float get_scale() const;

	// Setters
	void set_name(char*);
	void set_shape_visibility(bool);
	void set_text_visibility(bool);
	void set_position(int*);
	void set_velocity(float*);
	void set_colour(float*);
	void set_scale(float);
	
	// Custom
	virtual void reset();
};

#endif
