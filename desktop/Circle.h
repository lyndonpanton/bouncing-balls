#pragma once

#ifndef CIRCLE
#define CIRCLE

#include "Shape.h"

class Circle : public Shape
{
	int m_radius;

public:
	// General
	Circle();
	Circle(const Circle&);
	Circle(std::string, int[], float[], float[], float[], int);
	~Circle();

	// Getters
	int get_radius() const;

	// Setters
	void set_radius(int);
};

#endif
