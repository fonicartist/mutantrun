#ifndef  ENEMY_H
#define  ENEMY_H


#include <SFML/Graphics.hpp>

class Enemy {
private:
	
	bool isAttack;

	sf::Sprite spriteSheet;
	sf::Texture spriteTexture;
	
	sf::RectangleShape attackRange;
	
	void loadAssets();
	void render(sf::RenderWindow&);

public:
	Enemy();
	~Enemy();

	void update(sf::RenderWindow &window);
	float getX() {
		return spriteSheet.getPosition().x;
	};
	void setX(float x) {
		spriteSheet.setPosition(x, spriteSheet.getPosition().y);
	};
	void move(float x) {
		spriteSheet.move(sf::Vector2f(x, 0));
	};

};

#endif