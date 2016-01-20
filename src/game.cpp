// Implementation file for Game object
#include <iostream>
#include <fstream>
#include <SFML/Graphics/Color.hpp>
#include "Game.h"

using namespace std;

/************************************************
 * Constructor Game() creates a new Game object *
 * containing everything else when the program  *
 * starts up.									*
 ************************************************/
 Game::Game() {
	// Create game render window
	window.create(sf::VideoMode(1280, 720), "Mutant Run");
	window.setMouseCursorVisible(true);
	window.setKeyRepeatEnabled(false);

	velocity = 0;
	giveAnother = true;

	//window.setFramerateLimit(30);
	window.setVerticalSyncEnabled(true);

	camera.setCenter(640, 360);

	mutant = new Mutant();
	enemy = new Enemy();

	gameState_ = GameState::titleScreen;

	jumpCount = atkCount = points = 0;

	loadAssets();

}

/************************************************
 * The mainLoop() function handles in game		*
 * occurences while the program window remains	*
 * open.										*
 ************************************************/
void Game::mainLoop() {
	sf::Event event;
	deltaTime = sf::Time::Zero;

	while (window.isOpen()) {
		sf::Time elapsedTime = clock.restart();
		deltaTime += elapsedTime;

		while (deltaTime > TimePerFrame) {
			// Reset deltaTime
			deltaTime -= TimePerFrame;

			// Check for events
			while (window.pollEvent(event))
				handleEvent(event);

			// Switch between different gamestates

			checkMusic();
			
		}
		render();
	}

}

/************************************************
 * Event handler								*
 ************************************************/
void Game::handleEvent(sf::Event &event) {
	if (event.type == sf::Event::Closed)
		window.close();

	// Pressing escape closes the window
	if (sf::Event::KeyPressed)
		if (event.key.code == sf::Keyboard::Escape) {
			window.close();
		}

	// Switch statement controls what actions are done in each game state
	switch (gameState_) {
	case GameState::titleScreen:
		if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Return || event.key.code == sf::Keyboard::Space)) {
			gameState_ = GameState::inGame;
		}
		break;
	case GameState::inGame:
		mutant->inputHandler(event);
		break;
	case GameState::gameOver:
		if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Return || event.key.code == sf::Keyboard::Space)) {
			gameState_ = GameState::titleScreen;
			delete mutant;
			mutant = new Mutant();
			delete enemy;
			enemy = new Enemy();
			jumpCount = atkCount = points = 0;
		}
	}
}

/************************************************
 * The loadAssets() function loads all the		*
 * resources needed by the Game object for		*
 * title screen, main menu, etc.				*
 ************************************************/
void Game::loadAssets() {
	// Load game images
	titleTexture.loadFromFile("..\\..\\assets\\bg\\titleScreen.png");
	skyTexture.loadFromFile("..\\..\\assets\\bg\\SOR4_01.png");
	sidewalk.loadFromFile("..\\..\\assets\\bg\\ground.png");
	GOTexture.loadFromFile("..\\..\\assets\\bg\\gameover.png");
	// Load game music
	titleMusic.openFromFile("..\\..\\assets\\music\\frankenstein.ogg");
	themeSong.openFromFile("..\\..\\assets\\music\\theme.ogg");
	gameOverMusic.openFromFile("..\\..\\assets\\music\\gameover.ogg");
	// Load fonts
	heroic.loadFromFile("..\\..\\assets\\heroic.otf");


	// Set game images
	title.setTexture(titleTexture);
	title.setOrigin(0, 0);
	title.setPosition(0, 0);

	GOimage.setTexture(GOTexture);
	GOimage.setOrigin(0, 0);
	GOimage.setPosition(0, 0);

	skyline.setTexture(skyTexture);
	skyline.setOrigin(400, 0);
	skyline.setScale(2, 1.75);
	skyline.setPosition(640, -50);

	ground[0].setTexture(sidewalk);
	ground[0].setOrigin(0, 231);
	ground[0].setScale(1, 1);
	ground[0].setPosition(0, 720);

	ground[1].setTexture(sidewalk);
	ground[1].setOrigin(0, 231);
	ground[1].setScale(1, 1);
	ground[1].setPosition(1836, 720);

	score.setFont(heroic);
	score.setOrigin(0, 0);
	score.setCharacterSize(42);
	score.setColor(sf::Color::White);
	score.setPosition(40, 30);
	score.setString("Score: ");
	
	number.setFont(heroic);
	number.setOrigin(0, 0);
	number.setCharacterSize(42);
	number.setColor(sf::Color::White);
	number.setPosition(180, 30);
	number.setString(std::to_string(points));

	attack.setFont(heroic);
	attack.setOrigin(0, 0);
	attack.setCharacterSize(36);
	attack.setColor(sf::Color(250, 0, 0, 200));
	attack.setPosition(40, 90);
	attack.setString("Attack Available");

	spaceOrEnter.setFont(heroic);
	spaceOrEnter.setCharacterSize(42);
	spaceOrEnter.setOrigin(attack.getLocalBounds().width / 2, 0);
	spaceOrEnter.setColor(sf::Color::White);
	spaceOrEnter.setString("Press 'Space' or 'Enter'");

}

void Game::checkMusic() {
	// Play title theme music
	if (titleMusic.getStatus() != sf::Music::Playing && (gameState_ == GameState::titleScreen))
		titleMusic.play();
	else if (titleMusic.getStatus() == sf::Music::Playing && (gameState_ != GameState::titleScreen))
		titleMusic.stop();
	// Play in game music
	if (themeSong.getStatus() != sf::Music::Playing && gameState_ == GameState::inGame)
		themeSong.play();
	else if (themeSong.getStatus() == sf::Music::Playing && gameState_ != GameState::inGame)
		themeSong.stop();
	// Play gameover music
	if (gameOverMusic.getStatus() != sf::Music::Playing && gameState_ == GameState::gameOver)
		gameOverMusic.play();
	else if (gameOverMusic.getStatus() == sf::Music::Playing && gameState_ != GameState::gameOver)
		gameOverMusic.stop();
}

void Game::checkHit() {

	if (enemy->getX() - mutant->getX() < 130 && enemy->getX() - mutant->getX() > -100) {
		if (mutant->getAtk()) {
			enemy->setX(float(enemy->getX() - mutant->getX() + 2166 - (rand() % 250)));
			atkCount += 1;
		}
		else if (mutant->getY() < 380){
			if (giveAnother) {
				jumpCount += 1;
				giveAnother = false;
			}
		}
		else
			gameState_ = gameOver;
	}

}

void Game::velocityUpdate() {

	if (points == 0)
		velocity = 0;
	else if (points > 900) {
		int add = (points - 900) / 60;
		velocity = -7.5 - .2 * add;
	}
	else if (points > 100) {
		int add = points / 60;
		velocity = -.5 * add;
	}

	/*
	if (points == 0)
		velocity = 0;
	else if (points > 100 && velocity == 0)
		velocity -= .5;
	else if (points > 150 && velocity == -.5)
		velocity -= .5;
	else if (points > 200 && velocity == -1)
		velocity -= .5;
	else if (points > 250 && velocity == -1.5)
		velocity -= .5;
	else if (points > 300 && velocity == -2)
		velocity -= .5;
	else if (points > 350 && velocity == -2.5)
		velocity -= .5;
	else if (points > 400 && velocity == -3)
		velocity -= .5;
	else if (points > 450 && velocity == -3.5)
		velocity -= .5;
	else if (points > 500 && velocity == -4)
		velocity -= .5;
	else if (points > 550 && velocity == -4.5)
		velocity -= .5;
	else if (points > 600 && velocity == -5)
		velocity -= .5;
	else if (points > 650 && velocity == -5.5)
		velocity -= .5;
	else if (points > 700 && velocity == -6)
		velocity -= .5;
	else if (points > 750 && velocity == -6.5)
		velocity -= .5;
	else if (points > 800 && velocity == -7)
		velocity -= .5;
	else if (points > 850 && velocity == -7.5)
		velocity -= .5;
	else if (points > 900 && velocity == -8)
		velocity -= .2;
	else if (points > 950 && velocity == -8.2)
		velocity -= .2;
	else if (points > 1000 && velocity == -8.4)
		velocity -= .2;
	else if (points > 1050 && velocity == -8.6)
		velocity -= .2;
	else if (points > 1100 && velocity == -8.8)
		velocity -= .2;
	else if (points > 1150 && velocity == -9)
		velocity -= .2;
	else if (points > 1200 && velocity == -9.2)
		velocity -= .2;
	else if (points > 1250 && velocity == -9.4)
		velocity -= .2;
	else if (points > 1300 && velocity == -9.6)
		velocity -= .1;
	else if (points > 1350 && velocity == -9.7)
		velocity -= .1;
	else if (points > 1400 && velocity == -9.8)
		velocity -= .1;
	else if (points > 1450 && velocity == -9.9)
		velocity -= .1;
	*/

}

void Game::update() {

	// Camera
	camera.setSize(sf::Vector2f(1280, 720));
	//camera.setCenter(640, 360);
	camera.zoom(1.0);
	window.setView(camera);

	if (gameState_ == inGame) {

		for (int i = 0; i < 2; i++) {
			ground[i].move(sf::Vector2f(float(-15 + velocity), 0));
			if (ground[i].getPosition().x < -1836)
				ground[i].setPosition(ground[i].getPosition().x + 3672, ground[i].getPosition().y);
		}

		if (mutant->getY() == 600)
			giveAnother = true;

		if (enemy->getX() < -100)
			enemy->setX(1723 - rand()%100 + abs(-100 - enemy->getX()));

		enemy->move(float(-15 + velocity));

		checkHit();
		points = jumpCount * 10 + atkCount * 25;
		number.setString(std::to_string(points));
		velocityUpdate();
		cout << velocity << endl;

	}
	else if (gameState_ == gameOver) {

	}

}

void Game::render() {
	// Clear window of every image
	window.clear();

	// Render functions for other objects
	if (gameState_ == GameState::titleScreen) {
		window.draw(title);
		spaceOrEnter.setPosition(300, 500);
		window.draw(spaceOrEnter);
	}
	else if (gameState_ == GameState::inGame) {
		window.draw(skyline);
		window.draw(ground[0]);
		window.draw(ground[1]);
		enemy->update(window);
		mutant->update(window);
		window.draw(score);
		window.draw(number);

		if (mutant->getCanAttack())
			window.draw(attack);
	}
	else if (gameState_ == GameState::gameOver) {
		window.draw(GOimage);
		window.draw(score);
		window.draw(number);
		spaceOrEnter.setPosition(640, 570);
		window.draw(spaceOrEnter);

	}
	update();

	window.display();

}

/************************************************
 * Destructor ~Game() deletes any objects and	*
 * instances before the program shuts down.		*
 ************************************************/
Game::~Game() {

}