#include "imgui.h"
#include "imgui-SFML.h"
#include "SFML/Graphics.hpp"

#include "Shape.h"

#include <iostream>
#include <fstream>

void read_config_file(
	std::string, sf::RenderWindow&,
	sf::Font&, std::vector<Shape>&
);

void read_config_file_window(sf::RenderWindow&, std::ifstream&);
void read_config_file_font(sf::Font&, std::ifstream&);
void read_config_file_circle(std::vector<Shape>&, std::ifstream&);
void read_config_file_rectangle(std::vector<Shape>&, std::ifstream&);

int main()
{
	std::vector<Shape> shapes;
	sf::RenderWindow render_window;
	sf::Font font;
	read_config_file("config.txt", render_window, font, shapes);

	//sf::RenderWindow render_window(sf::VideoMode(1080, 720), "Bouncing Balls");
	ImGui::SFML::Init(render_window);
	sf::Clock delta_clock;

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

		render_window.clear(sf::Color(0, 0, 0));

		ImGui::SFML::Render(render_window);
		render_window.display();
	}

	ImGui::SFML::Shutdown(render_window);

	return 0;
}

void read_config_file(
	std::string filepath, sf::RenderWindow& render_window,
	sf::Font& font, std::vector<Shape>& shapes
)
{
	std::ifstream file_input(filepath);

	std::string line_type;

	while (file_input >> line_type)
	{
		std::cout << line_type << ": ";

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
	std::string font_type;
	int font_size;
	int red_value;
	int green_value;
	int blue_value;

	file_input >> font_type >> font_size >> red_value >> green_value
		>> blue_value;

	std::cout << font_type << ", " << font_size << ", " << red_value << ", "
		<< green_value << ", " << blue_value << std::endl;
}

void read_config_file_circle(std::vector<Shape>& shapes, std::ifstream& file_input)
{
	// Circle CGreen 100 100 -3 2 0 255 0 50
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

	std::cout << circle_colour << ", " << circle_position_x << ", "
		<< circle_position_y << ", " << circle_velocity_x << ", "
		<< circle_velocity_y << ", " << circle_red_value << ", "
		<< circle_green_value << ", " << circle_blue_value << ", "
		<< circle_radius << std::endl;
}

void read_config_file_rectangle(std::vector<Shape>& shapes, std::ifstream& file_input)
{
	// Rectangle RGrey 300 250 -2 2 100 100 100 50 100
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

	std::cout << rectangle_colour << ", " << rectangle_position_x << ", "
		<< rectangle_position_y << ", " << rectangle_velocity_x << ", "
		<< rectangle_velocity_y << ", " << rectangle_red_value << ", "
		<< rectangle_green_value << ", " << rectangle_blue_value << ", "
		<< rectangle_width << ", " << rectangle_height << std::endl;
}
