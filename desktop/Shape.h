#ifndef SHAPE
#define SHAPE

#include <string>
#include <array>

class Shape
{
	std::string m_name;
	bool m_is_visible = true;
	int m_position;
	float m_velocity;
	float m_colour;
	float m_scale[2];

public:
	// General
	//Shape();
	//Shape(Shape&);
	//Shape(std::string, int[], float[], float[], float[]);
	//~Shape();

	//// Getters
	//bool get_visibility() const;
	//int* get_position() const;
	//float* get_velocity() const;
	//float* get_colour() const;
	//float* get_scale() const;

	//// Setters
	//void set_visibility(bool);
	//void set_position(int[]);
	//void set_velocity(float[]);
	//void set_colour(float[]);
	//void set_scale();
};

#endif
