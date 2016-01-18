#ifndef  MUTANT_H
#define  MUTANT_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Mutant {
private:
	enum Action {running, jumps, attack, jumpAttack} action_;

	bool isJump, 
		 isAlive,
		 isAttack,
		 canAttack;
	int frameTimer,
		xFrame,
		yFrame,
		attackTimer,
		rechargeTimer,
		jumpTimer;

	sf::Sprite spriteSheet;
	sf::Texture spriteTexture;
	sf::Sprite effect;
	sf::Texture effectSheet;
	sf::RectangleShape attackRange;

	// Voice Clips
	sf::Music jumpGrunt,
			  berserker;

	void loadAssets();
	void animationUpdate();
	void jumpAnim();
	void runAnim();
	void attackAnim();
	void jump();
	void render(sf::RenderWindow&);

public:
	Mutant();
	~Mutant();

	void inputHandler(sf::Event &event);
	void update(sf::RenderWindow &window);

	bool getCanAttack() {
		return canAttack;
	};
	int getRecharge() {
		return rechargeTimer;
	};
	double getX() {
		return int(spriteSheet.getPosition().x);
	};
	double getY() {
		return spriteSheet.getPosition().y;
	};
	bool getAtk() {
		return isAttack;
	};
	bool getJump() {
		return isJump;
	};

};

#endif