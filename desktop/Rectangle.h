#pragma once

#ifndef RECTANGLE
#define RECTANGLE

#include "Shape.h"

class Rectangle : public Shape
{
	int m_width;
	int m_height;

public:
	// General
	Rectangle();
	Rectangle(const Rectangle&);
	Rectangle(std::string, int[], float[], int[], float[], int, int);
	~Rectangle();

	// Getters
	int get_width() const;
	int get_height() const;

	// Setters
	void set_width(int);
	void set_height(int);
};

#endif
