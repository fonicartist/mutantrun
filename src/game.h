#ifndef  GAME_H
#define  GAME_H

#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include "mutant.h"
#include "enemy.h"

const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);

class Game {
private:
	// Enumeration controls the different states the game goes into.
	enum GameState {titleScreen, intro, inGame, gameOver, pause} gameState_;

	bool giveAnother;
	int atkCount,
		jumpCount,
		points;
	double velocity;


	// Game objects
	Mutant *mutant;
	Enemy *enemy;

	// SFML Objects
	sf::RenderWindow window;

	sf::Clock clock;
	sf::Time deltaTime;

	sf::View camera;

	// In game text
	sf::Font heroic;
	sf::Text score,
			 number,
			 attack,
			 spaceOrEnter;

	// Game Music
	sf::Music titleMusic,
			  gameOverMusic,
			  themeSong;

	// Game sounds but using music implementation
	sf::Music pressEnter;

	// Background Pictures
	sf::Sprite title;
	sf::Texture titleTexture;
	sf::Sprite skyline;
	sf::Texture skyTexture;
	sf::Sprite ground[2];
	sf::Texture sidewalk;
	sf::Sprite GOimage;
	sf::Texture GOTexture;


	// Game mechanic functions
	void handleEvent(sf::Event &event);

	void playIntro();
	void titleUpdate();
	void gameoverUpdate();
	void loadAssets();
	void checkMusic();
	void checkHit();
	void velocityUpdate();
	void update();
	void render();

public:
	Game();
	~Game();
	void mainLoop();

};

#endif 