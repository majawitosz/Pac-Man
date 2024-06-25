#include "stdafx.h"
#include "Game.h"

//Initialization
void Game::initVariables()
{
	this->window = nullptr;
	this->fullscreen = false;
	this->dt = 0.f;
	
}

void Game::initWindow()
{
	/* Creates SFML window using options from a window.ini file */

	std::ifstream file("Config/window.ini");
	this->videoModes = sf::VideoMode::getFullscreenModes();

	std::string title = "None";
	sf::VideoMode window_bounds = sf::VideoMode::getDesktopMode();


	bool fullscreen = false;
	unsigned framerate_limit = 120;
	bool vertical_sync_enabled = false;
	unsigned antialiasing_level = 0;
	if (file.is_open())
	{
		std::getline(file, title);
		file >> window_bounds.width >> window_bounds.height;
		file >> fullscreen;
		file >> framerate_limit;
		file >> vertical_sync_enabled;
		file >> antialiasing_level;
	}
	file.close();

	this->fullscreen = fullscreen;
	this->windowSettings.antialiasingLevel = antialiasing_level;
	if (this->fullscreen)
		this->window = std::make_unique<sf::RenderWindow>(window_bounds, title, sf::Style::Fullscreen, this->windowSettings);
	else
		this->window = std::make_unique<sf::RenderWindow>(window_bounds, title, sf::Style::Titlebar | sf::Style::Close, this->windowSettings);
	this->window->setFramerateLimit(framerate_limit);
	this->window->setVerticalSyncEnabled(vertical_sync_enabled);

}



void Game::initKeys()
{
	std::ifstream file("Config/supported_keys.ini");

	if (file.is_open()) {

		std::string key = "";
		int keyValue = 0;

		while (file >> key >> keyValue) {
			this->supportedKeys[key] = keyValue;
		}
	}

	file.close();

}

void Game::initStates()
{

	//this->states.push(new GameState(this->window, &this->supportedKeys, &this->states));
	this->states.push(new MainMenuState(this->window.get(), &this->supportedKeys, &this->states));
}

//Constructor and deconstructor
Game::Game()
{
	this->initWindow();
	this->initKeys();
	this->initStates();
	this->gameRunning = true;
	this->gameThread = std::thread(&Game::run, this);
}

Game::~Game()
{
	//delete this->window;

	while (!this->states.empty()) {
		delete this->states.top();
		this->states.pop();
	}
}

void Game::setGameThread(bool run)
{
	this->gameRunning = run;
}


//Functions
void Game::updateSFMLEvents()
{
	while (this->window->pollEvent(this->event))
	{
		if (this->event.type == sf::Event::Closed)
			this->window->close();
	}
}

void Game::updateDt()
{
	/* Updates the dt variable with the time it takes to update and render one frame. */

	this->dt = this->dtClock.restart().asSeconds();
}


void Game::update()
{
	this->updateSFMLEvents();

	if (!this->states.empty())
	{
		this->states.top()->update(this->dt);

		if (this->states.top()->getQuit())
		{

			this->states.top()->endState();
			delete this->states.top();
			this->states.pop();
		}

	}
	//Application end
	else
	{
		this->endGame();
		this->window->close();
	}

}


void Game::render()
{
	this->window->clear();

	if (!this->states.empty())
		this->states.top()->render(this->window.get());

	this->window->display();
}


void Game::run()
{
	

	if (this->gameRunning) {
		while (this->window->isOpen())
		{
			this->update();
			this->updateDt();
			this->render();
		}
	}
	
}

void Game::endGame()
{
	std::cout << "End" << std::endl;
}


