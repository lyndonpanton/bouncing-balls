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

void game_loop_update(sf::RenderWindow&, std::vector<Shape*>&);
void game_loop_draw(sf::RenderWindow& window, std::vector<Shape*>&, sf::Font&);

int main()
{
	/*
		TODO

		- SFML
			- [x] Shapes should bounce off the bounds of the window
			- [ ] Add point count to Circle class
			- [ ] Circle class only needs a primitive for the scale (not an
			array)
			- [ ] Display the name of shapes in the center of shapes on the screen
				- [x] Display names
				- [ ] Center names
			- You do not have to handle the event where users rapidly change a shape's
			scale which causes it to go out of the bounds of the window

		- ImGui
			- [ ] Have a list of all shapes (combo box)
			- [ ] Allow users to edit the name of a shape
			- [ ] Allow users to edit the visibility of a shape
			- [ ] Allow users to edit the velocity of a shape
			- [ ] Allow users to edit the colour of a shape
			- [ ] Allow users to edit the scale of a shape (0 to 4)

		- Submission
			- The only file that needs to be submitted is main.cpp
			- [ ] Refactor the project to have all custom .cpp and .h code in main.cpp
			- [ ] Write the full names of all team members at the top of the main.cpp file
			- [ ] If you did not manage to get a specific feature working, please try to
			explain why you did not manage it and what approaches you took
	*/

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

		// Input?

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
				|| circle->get_position()[0] + circle->get_radius() * 2
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
				|| circle->get_position()[1] + circle->get_radius() * 2
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
				|| rectangle->get_position()[0] + rectangle->get_width()
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
				|| rectangle->get_position()[1] + rectangle->get_height()
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
		if (shape->get_visibility())
		{
			if (Circle* circle = dynamic_cast<Circle*>(shape))
			{
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
				sf::Text circle_text(circle->get_name(), font, 24);
				circle_text.setPosition(
					sf_circle.getGlobalBounds().getPosition().x + sf_circle.getLocalBounds().width / 4,
					sf_circle.getGlobalBounds().getPosition().y + sf_circle.getLocalBounds().height / 3
				);

				window.draw(sf_circle);
				window.draw(circle_text);
			}
			else if (Rectangle* rectangle = dynamic_cast<Rectangle*>(shape))
			{
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
				sf::Text rectangle_text(rectangle->get_name(), font, 24);
				rectangle_text.setPosition(
					sf_rectangle.getGlobalBounds().getPosition().x + sf_rectangle.getLocalBounds().width / 4,
					sf_rectangle.getGlobalBounds().getPosition().y + sf_rectangle.getLocalBounds().height / 4
				);

				window.draw(sf_rectangle);
				window.draw(rectangle_text);
			}
		}
	}
}
