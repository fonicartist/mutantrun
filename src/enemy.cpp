#include "enemy.h"

Enemy::Enemy() {

	loadAssets();

}

void Enemy::loadAssets() {
	spriteTexture.loadFromFile("..\\..\\assets\\sprites\\soldier.png");

	spriteSheet.setTexture(spriteTexture);
	spriteSheet.setTextureRect(sf::IntRect(0, 0, 192, 204));
	spriteSheet.setScale(1.2f, 1.2f);
	spriteSheet.setOrigin(96, 204);
	spriteSheet.setPosition(1920, 570);

}

void Enemy::render(sf::RenderWindow & window) {
	window.draw(spriteSheet);

}

void Enemy::update(sf::RenderWindow & window) {

	render(window);
}

Enemy::~Enemy() {

}