#pragma once
#include "State.h"
#include "TileMap.h"
#include "Ghosts.h"
#include "Dot.h"



class GameState : public State
{
private:

	bool caughtPacMan;

	Player* player;
	TileMap map;
	Ghosts* blueGhost;
	Ghosts* redGhost;
	Ghosts* pinkGhost;
	Ghosts* yellowGhost;
	
	sf::Sprite mapImage;
	sf::Texture pacManTexture; 
	std::vector<sf::Sprite> pacManLivesSprites;
	sf::Font font;
	sf::Text scoreTextPoints;
	sf::Text scoreText;
	sf::Text highScore;
	int direction; // 0 - left, 1 - right, 2 - up, 3 - down
	bool isWall = false; // do wyjebania
	bool foundPath = false;
	bool startedGhost = false;
	bool ghostFree = false;

	bool test = false;
	int score;
	int lives = 3;


	
	//Initializer functions
	void initKeybinds();
	void initTextures();
	void initPlayers();
	void initMapBackground();
	void initPacManLives();
	void initMap();
	void initFonts();

	
public:
	GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states, std::string userName);
	virtual ~GameState();

	//Functions
	//sf::FloatRect getGhostPosition();
	bool checkMapPlayerIntersect();
	void collisionManagement(sf::FloatRect playerBounds, sf::FloatRect wallBounds);
	bool teleportLeft();
	bool teleportRight();
	void eatDots();

	void moveRedGhost(const float& dt);
	void updateRedGhost();

	void startGhosts();
	bool checkMapGhostIntersect(Ghosts *ghost);
	void ghostCollisionManagement(sf::FloatRect ghostBounds, sf::FloatRect wallBounds, Ghosts* ghost);
	void moveGhost(Ghosts* ghost, const float& dt);
	bool checkPacManGhostCollision(Ghosts* ghost);
	void stopGame();

	bool checkMoveLeft(Entity *entity);
	bool checkMoveRight(Entity* entity);
	bool checkMoveUp(Entity* entity);
	bool checkMoveDown(Entity* entity);
	bool checkIfGhostMoves(Ghosts* ghost);

	void display();
	
	void updateInput(const float& dt) override;
	void movementManager(const float& dt);

	void lightresetGame();
	void update(const float& dt) override;
	void render(sf::RenderTarget* target = nullptr) override;

	void sendRequest(const std::string& username, int score);
	
};

