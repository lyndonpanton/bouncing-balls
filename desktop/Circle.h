#pragma once

#ifndef CIRCLE
#define CIRCLE

#include "Shape.h"

class Circle : public Shape
{
	int m_radius;

public:
	int m_point_count;

	// General
	Circle();
	Circle(const Circle&);
	Circle(char*, int[], float[], float[], float[], int, int);
	~Circle();

	// Getters
	int get_radius() const;
	int get_point_count() const;

	// Setters
	void set_radius(int);
	void set_segments(int);
};

#endif
