#include "mutant.h"
#include <iostream>

using namespace std;

// Constructor
Mutant::Mutant() {

	frameTimer = 0;
	xFrame = 0;
	jumpTimer = 0;
	attackTimer = 0;
	rechargeTimer = 100;
	isJump = false;
	isAlive = true;
	isAttack = false;
	canAttack = true;
	loadAssets();

}

void Mutant::loadAssets() {
	spriteTexture.loadFromFile("..\\..\\assets\\sprites\\wolverine.png");
	berserker.openFromFile("..\\..\\assets\\sounds\\berserker.ogg");
	jumpGrunt.openFromFile("..\\..\\assets\\sounds\\jump.ogg");
	effectSheet.loadFromFile("..\\..\\assets\\sprites\\effect.png");

	spriteSheet.setTexture(spriteTexture);
	spriteSheet.setTextureRect(sf::IntRect(0, 0, 160, 140));
	spriteSheet.setScale(2, 2);
	spriteSheet.setOrigin(80, 140);
	spriteSheet.setPosition(350, 600);

	effect.setTexture(effectSheet);
	effect.setTextureRect(sf::IntRect(0, 0, 640, 480));
	effect.setScale(2, 2);
	effect.setOrigin(320, 330);
	effect.setPosition(350, 600);
}

void Mutant::animationUpdate() {

	switch (action_) {
	case running:
		runAnim();
		spriteSheet.setOrigin(80, 140);
		break;
	case jumps:
		jumpAnim();
		break;
	case attack:
		attackAnim();
		spriteSheet.setOrigin(60, 140);
		break;
	}

}

void Mutant::runAnim() {
	frameTimer++;
	spriteSheet.setTextureRect(sf::IntRect(160 * xFrame, 0, 160, 140));
	if (frameTimer > 5) {
		xFrame++;
		frameTimer = 0;
		if (xFrame == 6)
			xFrame = 0;
	}
}

void Mutant::jumpAnim() {
	if (xFrame != 9) {
		frameTimer++;
		if (xFrame < 4) {
			if (frameTimer > 7) {
				xFrame++;
				frameTimer = 0;
				spriteSheet.setTextureRect(sf::IntRect(160 * xFrame, 140, 160, 140));
			}
		}
		else
			if (frameTimer > 6) {
				xFrame++;
				frameTimer = 0;
				spriteSheet.setTextureRect(sf::IntRect(160 * xFrame, 140, 160, 140));
			}
	}
}

void Mutant::attackAnim() {
	rechargeTimer = 0;
	frameTimer++;
	spriteSheet.setTextureRect(sf::IntRect(160 * xFrame, 280, 160, 140));
	effect.setTextureRect(sf::IntRect(640 * xFrame, 0, 640, 480));
	if (frameTimer > 4) {
		xFrame++;
		frameTimer = 0;
		if (xFrame == 5) {
			xFrame = 0;
			attackTimer--;
		}
	}

	if (attackTimer == 0) {
		isAttack = false;
		xFrame = 0;
	}


}

void Mutant::jump() {

	if (jumpTimer > 1)
		spriteSheet.setPosition(spriteSheet.getPosition().x, spriteSheet.getPosition().y - 30 * jumpTimer / 30);
	else if (jumpTimer < -1)
		spriteSheet.setPosition(spriteSheet.getPosition().x, spriteSheet.getPosition().y + 30 * abs(jumpTimer) / 30);

	jumpTimer--;

	if (spriteSheet.getPosition().y == 600) {
		isJump = false;
		jumpTimer = 0;
		xFrame = 0;
	}
}

void Mutant::inputHandler(sf::Event &event) {

	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space && !isJump && !isAttack) {
		jumpTimer = 25;
		xFrame = 0;
		frameTimer = 0;
		isJump = true;
		action_ = jumps;
		jumpGrunt.play();
	}
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return && !isJump && !isAttack && canAttack) {
		xFrame = 0;
		attackTimer = 2;
		frameTimer = 0;
		isAttack = true;
		action_ = attack;
		berserker.play();
	}

}

void Mutant::render(sf::RenderWindow & window) {
	window.draw(spriteSheet);
	if (isAttack)
		window.draw(effect);
}

void Mutant::update(sf::RenderWindow & window) {

	animationUpdate();

	if (rechargeTimer == 111)
		canAttack = true;
	else {
		rechargeTimer++;
		canAttack = false;
	}

	if (isJump)
		jump();
	else if (isAttack) {

	}
	else
		action_ = running;

	render(window);
}

// Destructor
Mutant::~Mutant() {

}