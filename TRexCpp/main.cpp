#include <SFML/Graphics.hpp>
#include <iostream>

#pragma comment(lib, "C:\\Program Files (x86)\\Microsoft Visual Studio 14.0\\VC\\lib\\sfml-graphics-d.lib")
#pragma comment(lib, "C:\\Program Files (x86)\\Microsoft Visual Studio 14.0\\VC\\lib\\sfml-window-d.lib")
#pragma comment(lib, "C:\\Program Files (x86)\\Microsoft Visual Studio 14.0\\VC\\lib\\sfml-system-d.lib")

sf::Texture p_left;
sf::Texture p_right;
sf::Sprite p_model;
sf::Sprite p_background;
int p_frame = 0;
enum ModelView
{
	Right,
	Left
};
ModelView p_modelView;
int jump_rest;
int fly_rest;
bool jumping = false;
bool falling = false;
bool smoothFly = false;

/* CONSTANTS */
const int MAX_FPS = 60;
const int FRAME_SKIP = 5;
const int BACKGROUND_SPEED = 4;
const int JUMP_HEIGHT = 10;
const int JUMP_SPEED = 5;
const int FLY_LENGTH = 3;
const int WINDOW_WIDTH = 600;
const int WINDOW_HEIGHT = 150;

void update(sf::Window *window)
{
	if (p_frame == FRAME_SKIP) 
	{
		if (p_modelView == Right)
		{
			p_modelView = Left;
			p_model.setTexture(p_left);
		}
		else
		{
			p_modelView = Right;
			p_model.setTexture(p_right);
		}
		p_frame = 0;
	}
	else { p_frame++; }
	sf::Vector2f pos = p_background.getPosition();
	sf::Vector2u size = p_background.getTexture()->getSize();
	if(pos.x + size.x + BACKGROUND_SPEED - 1 == WINDOW_WIDTH)
	{
		std::cout << "End of image reached" << std::endl;
	}
	p_background.setPosition(pos.x - BACKGROUND_SPEED, pos.y);
	if (jumping)
	{
		if (jump_rest != 0)
		{
			sf::Vector2f p = p_model.getPosition();
			p_model.setPosition(p.x, p.y - JUMP_SPEED);
			jump_rest--;
		}
		else { jumping = false; jump_rest = JUMP_HEIGHT; smoothFly = true; fly_rest = FLY_LENGTH; }
	}
	if(smoothFly)
	{
		if (fly_rest == 0) { falling = true; smoothFly = false; }
		else { fly_rest--; }
	}
	if(falling)
	{
		if (jump_rest != 0)
		{
			sf::Vector2f p = p_model.getPosition();
			p_model.setPosition(p.x, p.y + JUMP_SPEED);
			jump_rest--;
		}
		else { falling = false; }
	}
}

int main()
{
	p_left.loadFromFile("left.png");
	p_right.loadFromFile("right.png");
	p_model.setTexture(p_right);
	p_modelView = Right;
	p_model.setPosition(100, 100);
	sf::Texture background;
	background.loadFromFile("floor.png");
	p_background.setTexture(background);
	p_background.setPosition(0, 75);
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "TRex in C++");
	window.setFramerateLimit(MAX_FPS);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Key::Up && !jumping && !falling && !smoothFly)
				{
					jumping = true;
					jump_rest = JUMP_HEIGHT;
				}
			}
		}

		update(&window);
		window.clear(sf::Color(247, 247, 247));
		window.draw(p_background);
		window.draw(p_model);
		window.display();
	}

	return 0;
}
