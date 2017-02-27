#include <SFML/Graphics/Texture.hpp>
#include "dino.h"

dino::dino()
{
	left.loadFromFile("left.png");
	right.loadFromFile("right.png");
	model.setTexture(right);
	modelView = Right;
	model.setPosition(100, 100);
}

void dino::update()
{
	if(modelView == Right)
	{
		modelView = Left;
		model.setTexture(left);
	}
	else
	{
		modelView = Right;
		model.setTexture(right);
	}
}

