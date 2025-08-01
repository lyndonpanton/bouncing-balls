/*
	Team members

	- Lyndon Mykal Panton
*/

#include "imgui.h"
#include "imgui-SFML.h"
#include "SFML/Graphics.hpp"

#include "Shape.h"
#include "Circle.h"
#include "Rectangle.h"

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <array>

class Shape
{
	int* m_position;
	std::string m_initial_name;
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
		std::string, int[], float[], float[], float
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

void Shape::reset()
{
	// Both methods work
	//strcpy_s(m_name, m_initial_name.length() + 1, m_initial_name.data());
	memcpy(m_name, m_initial_name.c_str(), sizeof m_initial_name);

	m_position = m_initial_position;
	m_velocity = m_initial_velocity;

	m_colour[0] = *(&m_initial_colour[0]);
	m_colour[1] = *(&m_initial_colour[1]);
	m_colour[2] = *(&m_initial_colour[2]);

	m_scale = m_initial_scale;
}


void read_config_file(
	std::string, sf::RenderWindow&,
	sf::Font&, std::vector<Shape*>&
);
void read_config_file_window(sf::RenderWindow&, std::ifstream&);
void read_config_file_font(sf::Font&, std::ifstream&);
void read_config_file_circle(std::vector<Shape*>&, std::ifstream&);
void read_config_file_rectangle(std::vector<Shape*>&, std::ifstream&);

void game_loop_update(sf::RenderWindow&, std::vector<Shape*>&);
void game_loop_draw(sf::RenderWindow& window, std::vector<Shape*>&, sf::Font&);

int main()
{
	std::vector<Shape*> shapes;
	sf::RenderWindow render_window;
	sf::Font font;

	read_config_file("config.txt", render_window, font, shapes);

	std::vector<std::string> s_shape_names;

	for (auto const& shape : shapes)
	{
		s_shape_names.push_back(shape->get_name());
	}

	std::vector<const char*> c_shape_names;

	for (auto const& shape_name : s_shape_names)
	{
		c_shape_names.push_back(shape_name.data());
	}

	int shape_index = 0;

	ImGui::SFML::Init(render_window);
	sf::Clock delta_clock;
	render_window.setFramerateLimit(60);

	ImGui::GetStyle().ScaleAllSizes(1.5f);
	ImGui::GetIO().FontGlobalScale = 1.5f;

	while (render_window.isOpen())
	{
		sf::Event event;

		while (render_window.pollEvent(event))
		{
			ImGui::SFML::ProcessEvent(event);

			if (event.type == sf::Event::Closed) render_window.close();
		}

		ImGui::SFML::Update(render_window, delta_clock.restart());

		ImGui::Begin("Edit Shapes");

		// Selected shape
		ImGui::Combo("Shapes", &shape_index, c_shape_names.data(), (int)c_shape_names.size());

		// Visibility
		bool& is_selected_shape_drawn = shapes.at(shape_index)->m_shape_is_visible;
		ImGui::Checkbox("Draw Shape", &is_selected_shape_drawn);

		ImGui::SameLine();

		bool& is_selected_text_drawn = shapes.at(shape_index)->m_text_is_visible;
		ImGui::Checkbox("Draw Text", &is_selected_text_drawn);

		// Scale
		float& shape_scale = shapes.at(shape_index)->m_scale;
		ImGui::SliderFloat("Scale", &shape_scale, 0, 4);

		// Velocity
		float*& shape_velocity = shapes.at(shape_index)->m_velocity;
		ImGui::SliderFloat2("Velocity", shape_velocity, -8, 8);

		// Colour
		float* shape_colour = shapes.at(shape_index)->m_colour;
		ImGui::ColorEdit3("Colour", shape_colour);

		// Name
		ImGui::InputText("Name", shapes.at(shape_index)->get_name(), 255);
		c_shape_names.at(shape_index) = shapes.at(shape_index)->get_name();

		// Segments
		if (Circle* circle = dynamic_cast<Circle*>(shapes.at(shape_index)))
		{
			int& circle_segments = circle->m_point_count;
			ImGui::SliderInt("Segments", &circle_segments, 3, 64);
		}

		// Reset
		if (ImGui::Button("Reset Shape"))
		{
			shapes.at(shape_index)->reset();
		}

		ImGui::End();

		// Clear
		render_window.clear(sf::Color(0, 0, 0));

		// Update
		game_loop_update(render_window, shapes);

		// Draw
		game_loop_draw(render_window, shapes, font);

		// Render
		ImGui::SFML::Render(render_window);
		render_window.display();
	}

	ImGui::SFML::Shutdown(render_window);

	return 0;
}

void read_config_file(
	std::string filepath, sf::RenderWindow& render_window,
	sf::Font& font, std::vector<Shape*>& shapes
)
{
	std::ifstream file_input(filepath);

	std::string line_type;

	while (file_input >> line_type)
	{
		if (line_type == "Window")
		{
			read_config_file_window(render_window, file_input);
		}
		else if (line_type == "Font")
		{
			read_config_file_font(font, file_input);
		}
		else if (line_type == "Circle")
		{
			read_config_file_circle(shapes, file_input);
		}
		else if (line_type == "Rectangle")
		{
			read_config_file_rectangle(shapes, file_input);
		}
		else
		{
			std::cout << "Error: Line type not recognised (config.txt)"
				<< std::endl;
		}
	}
}

void read_config_file_window(
	sf::RenderWindow& render_window,
	std::ifstream& file_input
)
{
	int width;
	int height;

	file_input >> width >> height;

	render_window.create(sf::VideoMode(width, height), "Bouncing Balls");
}

void read_config_file_font(sf::Font& font, std::ifstream& file_input)
{
	std::string font_path;
	int font_size;
	int red_value;
	int green_value;
	int blue_value;

	file_input >> font_path >> font_size >> red_value >> green_value
		>> blue_value;

	if (!font.loadFromFile(font_path))
	{
		std::cerr << "Error: Could not load font" << std::endl;
		exit(1);
	}

	std::cout << font_path << ", " << font_size << ", " << red_value << ", "
		<< green_value << ", " << blue_value << std::endl;
}

void read_config_file_circle(std::vector<Shape*>& shapes, std::ifstream& file_input)
{
	char* circle_name = new char[255];
	int circle_position_x;
	int circle_position_y;
	float circle_velocity_x;
	float circle_velocity_y;
	float circle_red_value;
	float circle_green_value;
	float circle_blue_value;
	int circle_radius;
	int circle_point_count = 32;

	file_input >> circle_name >> circle_position_x
		>> circle_position_y >> circle_velocity_x >> circle_velocity_y
		>> circle_red_value >> circle_green_value >> circle_blue_value
		>> circle_radius;

	Circle* circle = new Circle(
		circle_name,
		new int[2] { circle_position_x, circle_position_y },
		new float[2] { circle_velocity_x, circle_velocity_y },
		new float[3] { circle_red_value / 255.0f, circle_green_value / 255.0f, circle_blue_value / 255.0f },
		1.0f,
		circle_radius,
		circle_point_count,
		circle_name,
		new int[2] { circle_position_x, circle_position_y },
		new float[2] { circle_velocity_x, circle_velocity_y },
		new float[3] { circle_red_value / 255.0f, circle_green_value / 255.0f, circle_blue_value / 255.0f },
		1.0f,
		32
	);

	shapes.push_back(circle);
}

void read_config_file_rectangle(std::vector<Shape*>& shapes, std::ifstream& file_input)
{
	char* rectangle_name = new char[255];
	int rectangle_position_x;
	int rectangle_position_y;
	float rectangle_velocity_x;
	float rectangle_velocity_y;
	float rectangle_red_value;
	float rectangle_green_value;
	float rectangle_blue_value;
	int rectangle_width;
	int rectangle_height;

	file_input >> rectangle_name >> rectangle_position_x
		>> rectangle_position_y >> rectangle_velocity_x
		>> rectangle_velocity_y >> rectangle_red_value
		>> rectangle_green_value >> rectangle_blue_value
		>> rectangle_width >> rectangle_height;


	Rectangle* rectangle = new Rectangle(
		rectangle_name,
		new int[2] { rectangle_position_x, rectangle_position_y },
		new float[2] { rectangle_velocity_x, rectangle_velocity_y },
		new float[3] { rectangle_red_value / 255.0f, rectangle_green_value / 255.0f, rectangle_blue_value / 255.0f },
		1.0f,
		rectangle_width,
		rectangle_height,
		rectangle_name,
		new int[2] { rectangle_position_x, rectangle_position_y },
		new float[2] { rectangle_velocity_x, rectangle_velocity_y },
		new float[3] { rectangle_red_value / 255.0f, rectangle_green_value / 255.0f, rectangle_blue_value / 255.0f },
		1.0f
	);

	shapes.push_back(rectangle);
}

void game_loop_update(sf::RenderWindow& window, std::vector<Shape*>& shapes)
{
	int window_width = window.getSize().x;
	int window_height = window.getSize().y;

	for (auto& shape : shapes)
	{
		if (Circle* circle = dynamic_cast<Circle*>(shape))
		{
			if (
				circle->get_position()[0] + circle->get_velocity()[0] <= 0
				|| circle->get_position()[0] + (circle->get_radius() * 2 * circle->get_scale())
				+ circle->get_velocity()[0] >= window_width
				)
			{
				circle->set_velocity(new float[2] {
					circle->get_velocity()[0] * -1,
						circle->get_velocity()[1]
					});
			}

			if (
				circle->get_position()[1] + circle->get_velocity()[1] <= 0
				|| circle->get_position()[1] + (circle->get_radius() * 2 * circle->get_scale())
				+ circle->get_velocity()[1] >= window_height
				)
			{
				circle->set_velocity(new float[2] {
					circle->get_velocity()[0],
						circle->get_velocity()[1] * -1
					});
			}
		}
		else if (Rectangle* rectangle = dynamic_cast<Rectangle*>(shape))
		{
			if (
				rectangle->get_position()[0] + rectangle->get_velocity()[0] <= 0
				|| rectangle->get_position()[0] + (rectangle->get_width() * rectangle->get_scale())
				+ rectangle->get_velocity()[0] >= window_width
				)
			{
				rectangle->set_velocity(new float[2] {
					rectangle->get_velocity()[0] * -1,
						rectangle->get_velocity()[1]
					});
			}
			if (
				rectangle->get_position()[1] + rectangle->get_velocity()[1] <= 0
				|| rectangle->get_position()[1] + (rectangle->get_height() * rectangle->get_scale())
				+ rectangle->get_velocity()[0] >= window_height
				)
			{
				rectangle->set_velocity(new float[2] {
					rectangle->get_velocity()[0],
						rectangle->get_velocity()[1] * -1
					});
			}
		}

		shape->set_position(new int[2] {
			shape->get_position()[0] + (int)shape->get_velocity()[0],
				shape->get_position()[1] + (int)shape->get_velocity()[1]
			});
	}
}

void game_loop_draw(sf::RenderWindow& window, std::vector<Shape*>& shapes, sf::Font& font)
{
	for (auto& shape : shapes)
	{
		if (shape->get_shape_visibility() || shape->get_text_visibility())
		{
			if (Circle* circle = dynamic_cast<Circle*>(shape))
			{
				sf::CircleShape sf_circle(
					(circle->get_radius() * circle->get_scale()),
					64
				);
				sf_circle.setPosition(circle->get_position()[0], circle->get_position()[1]);
				sf_circle.setFillColor(sf::Color(
					(int)(circle->get_colour()[0] * 255),
					(int)(circle->get_colour()[1] * 255),
					(int)(circle->get_colour()[2] * 255)
				));
				sf::Text circle_text(circle->get_name(), font, 24);
				circle_text.setPosition(
					sf_circle.getGlobalBounds().getPosition().x + sf_circle.getLocalBounds().width / 4,
					sf_circle.getGlobalBounds().getPosition().y + sf_circle.getLocalBounds().height / 3
				);
				sf_circle.setPointCount(circle->get_point_count());

				if (circle->get_shape_visibility())
				{
					window.draw(sf_circle);
				}

				if (circle->get_text_visibility())
				{
					window.draw(circle_text);
				}
			}
			else if (Rectangle* rectangle = dynamic_cast<Rectangle*>(shape))
			{
				sf::RectangleShape sf_rectangle(sf::Vector2f(
					rectangle->get_width() * rectangle->get_scale(),
					rectangle->get_height() * rectangle->get_scale()
				));
				sf_rectangle.setPosition(sf::Vector2f(
					rectangle->get_position()[0], rectangle->get_position()[1]
				));
				sf_rectangle.setFillColor(sf::Color(
					(int)(rectangle->get_colour()[0] * 255),
					(int)(rectangle->get_colour()[1] * 255),
					(int)(rectangle->get_colour()[2] * 255)
				));
				sf::Text rectangle_text(rectangle->get_name(), font, 24);
				rectangle_text.setPosition(
					sf_rectangle.getGlobalBounds().getPosition().x + sf_rectangle.getLocalBounds().width / 4,
					sf_rectangle.getGlobalBounds().getPosition().y + sf_rectangle.getLocalBounds().height / 4
				);

				if (rectangle->get_shape_visibility())
				{
					window.draw(sf_rectangle);
				}

				if (rectangle->get_text_visibility())
				{
					window.draw(rectangle_text);
				}
			}
		}
	}
}
