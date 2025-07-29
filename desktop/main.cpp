#include "imgui.h"
#include "imgui-SFML.h"
#include "SFML/Graphics.hpp"

#include "Shape.h"
#include "Circle.h"
#include "Rectangle.h"

#include <iostream>
#include <fstream>

void read_config_file(
	std::string, sf::RenderWindow&,
	sf::Font&, std::vector<Shape*>&
);
void read_config_file_window(sf::RenderWindow&, std::ifstream&);
void read_config_file_font(sf::Font&, std::ifstream&);
void read_config_file_circle(std::vector<Shape*>&, std::ifstream&);
void read_config_file_rectangle(std::vector<Shape*>&, std::ifstream&);

void game_loop_update(std::vector<Shape*>&);
void game_loop_draw(sf::RenderWindow& window, std::vector<Shape*>&);

int main()
{
	// Add point count to Circle class
	// Circle class only needs one scale component (not an array)
	std::vector<Shape*> shapes;
	sf::RenderWindow render_window;
	sf::Font font;
	read_config_file("config.txt", render_window, font, shapes);

	ImGui::SFML::Init(render_window);
	sf::Clock delta_clock;
	render_window.setFramerateLimit(60);

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

		//ImGui::Checkbox();

		ImGui::End();

		// Clear
		render_window.clear(sf::Color(0, 0, 0));

		// Update
		game_loop_update(shapes);

		// Draw
		game_loop_draw(render_window, shapes);


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
		// error...
	}

	std::cout << font_path << ", " << font_size << ", " << red_value << ", "
		<< green_value << ", " << blue_value << std::endl;
}

void read_config_file_circle(std::vector<Shape*>& shapes, std::ifstream& file_input)
{
	std::string circle_colour;
	int circle_position_x;
	int circle_position_y;
	float circle_velocity_x;
	float circle_velocity_y;
	int circle_red_value;
	int circle_green_value;
	int circle_blue_value;
	int circle_radius;

	file_input >> circle_colour >> circle_position_x
		>> circle_position_y >> circle_velocity_x >> circle_velocity_y
		>> circle_red_value >> circle_green_value >> circle_blue_value
		>> circle_radius;

	Circle* circle = new Circle(
		circle_colour,
		new int[2] { circle_position_x, circle_position_y },
		new float[2] { circle_velocity_x, circle_velocity_y },
		new int[3] { circle_red_value, circle_green_value, circle_blue_value },
		new float[2] { 1.0f, 1.0f },
		circle_radius
	);

	shapes.push_back(circle);
}

void read_config_file_rectangle(std::vector<Shape*>& shapes, std::ifstream& file_input)
{
	std::string rectangle_colour;
	int rectangle_position_x;
	int rectangle_position_y;
	float rectangle_velocity_x;
	float rectangle_velocity_y;
	int rectangle_red_value;
	int rectangle_green_value;
	int rectangle_blue_value;
	int rectangle_width;
	int rectangle_height;

	file_input >> rectangle_colour >> rectangle_position_x
		>> rectangle_position_y >> rectangle_velocity_x
		>> rectangle_velocity_y >> rectangle_red_value
		>> rectangle_green_value >> rectangle_blue_value
		>> rectangle_width >> rectangle_height;


	Rectangle* rectangle = new Rectangle(
		rectangle_colour,
		new int[2] { rectangle_position_x, rectangle_position_y },
		new float[2] { rectangle_velocity_x, rectangle_velocity_y },
		new int[3] { rectangle_red_value, rectangle_green_value, rectangle_blue_value },
		new float[2] { 1.0f, 1.0f },
		rectangle_width,
		rectangle_height
	);

	shapes.push_back(rectangle);
}

void game_loop_update(std::vector<Shape*>& shapes)
{
	for (auto& shape : shapes)
	{
		// Calculate collisions first
		shape->set_position(new int[2] {
			shape->get_position()[0] + (int)shape->get_velocity()[0],
			shape->get_position()[1] + (int)shape->get_velocity()[1]
		});

		if (Circle* circle = dynamic_cast<Circle*>(shape))
		{

		} 
		else if (Rectangle* rectangle = dynamic_cast<Rectangle*>(shape))
		{

		}
	}
}

void game_loop_draw(sf::RenderWindow& window, std::vector<Shape*>& shapes)
{
	for (auto& shape : shapes)
	{
		if (shape->get_visibility())
		{
			if (Circle* circle = dynamic_cast<Circle*>(shape))
			{
				/*
					- name (TODO)
					- visibility (done)
					- position (done)
					- velocity (done in update)
					- colour (done)
					- scale (done)
					- radius (done)
				*/
				sf::CircleShape sf_circle(
					(circle->get_radius() * circle->get_scale()[0]),
					64
				);
				sf_circle.setPosition(circle->get_position()[0], circle->get_position()[1]);
				sf_circle.setFillColor(sf::Color(
					circle->get_colour()[0],
					circle->get_colour()[1],
					circle->get_colour()[2]
				));

				window.draw(sf_circle);
			}
			else if (Rectangle* rectangle = dynamic_cast<Rectangle*>(shape))
			{
				/*
					- name
					- visibility (done)
					- position (done)
					- velocity (done in update)
					- colour (done)
					- scale (done)
					- width (done)
					- height (done)
				*/
				sf::RectangleShape sf_rectangle(sf::Vector2f(
					rectangle->get_width() * rectangle->get_scale()[0],
					rectangle->get_height() * rectangle->get_scale()[1]
				));
				sf_rectangle.setPosition(sf::Vector2f(
					rectangle->get_position()[0], rectangle->get_position()[1]
				));
				sf_rectangle.setFillColor(sf::Color(
					rectangle->get_colour()[0],
					rectangle->get_colour()[1],
					rectangle->get_colour()[2]
				));

				window.draw(sf_rectangle);
			}
		}
	}
}
