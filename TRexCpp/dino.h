#include <SFML/Graphics/Sprite.hpp>

class dino
{
public:
	static sf::Texture left;
	static sf::Texture right;
	static sf::Sprite model;
	enum ModelView
	{
		Right,
		Left
	};
	static ModelView modelView;
	dino();
	static void update();
};
