#include "stdafx.h"
#include "ScoreState.h"


void ScoreState::initVariables()
{
}

void ScoreState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Emulogic-zrEw.ttf")) {
		throw("ERROR::MAINMENUSTATE::COULD_NOT_LOAD_FONT");

	}
	if (!this->font2.loadFromFile("Fonts/RobotoMono-Bold.ttf")) {
		throw("ERROR::MAINMENUSTATE::COULD_NOT_LOAD_FONT");
	}

}

void ScoreState::initKeybinds()
{
	std::ifstream file("Config/mainmenustate_keybinds.ini");

	if (file.is_open()) {

		std::string key = "";
		std::string key2 = "";

		while (file >> key >> key2) {
			this->keybinds[key] = this->supportedKeys->at(key2);
		}
	}

	file.close();
}

void ScoreState::initButtons()
{
	this->buttons["SAVE_SCORES"] = new Button(320, 360, 150, 50,
		&this->font, "SAVE SCORES",
		sf::Color::Transparent, sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
	this->buttons["EXIT_STATE"] = new Button(320, 440, 150, 50,
		&this->font, "BACK",
		sf::Color::Transparent, sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
}


ScoreState::ScoreState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys,
	std::stack<State*>* states, AccountState* accountState)
	: State(window, supportedKeys, states), accountState(accountState)
{
	//this->accountState = nullptr;
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initButtons();
	//std::thread(&ScoreState::sendRequest, this).detach();
}

ScoreState::~ScoreState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it) {
		delete it->second;
	}

}

void ScoreState::initBackground()
{
	this->background.setSize(
		sf::Vector2f(static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y)));

	if (!this->bgTexture.loadFromFile("Resources/Images/Backgrounds/bg1.png"))
	{
		throw "ERRPR::MAIN_MENU_STATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}

	this->background.setTexture(&this->bgTexture);
}


void ScoreState::updateButtons()
{
	// Updates all the button in the state
	for (auto& button : this->buttons | std::views::values)
	{
		button->update(this->mousePosView);
	}

	if (this->buttons["SAVE_SCORES"]->isPressed())
	{
		std::thread(&ScoreState::sendRequest, this).detach();
		sf::sleep(sf::milliseconds(100));

	}
	if (this->buttons["EXIT_STATE"]->isPressed())
	{
		sf::sleep(sf::milliseconds(100));
		this->endState();
	}

}

static size_t my_write(void* buffer, size_t size, size_t nmemb, void* param)
{
	std::string& text = *static_cast<std::string*>(param);
	size_t totalsize = size * nmemb;
	text.append(static_cast<char*>(buffer), totalsize);
	return totalsize;
}
void ScoreState::sendRequest()
{
	CURL* curl;
	CURLcode res;
	std::string result;
	long httpCode = 0;

	curl_global_init(CURL_GLOBAL_DEFAULT);
	curl = curl_easy_init();

	if (curl) {
		std::string url;
		if (accountState->getUsername() == "") {
			url = "http://localhost:3000/getEveryScore";
		}
		else {
			url = "http://localhost:3000/getScores?username=" + accountState->getUsername();
		}
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, my_write);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result);
		curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
		res = curl_easy_perform(curl);
		curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
		if (res != CURLE_OK) {
			std::cerr << "CURL error: " << curl_easy_strerror(res) << std::endl;
		}
		else {
			handleResponse(result, httpCode);
		}
		curl_easy_cleanup(curl);
	}

	curl_global_cleanup();

}

void ScoreState::handleResponse(const std::string& response, long httpCode)
{
	std::cout << response << std::endl;

	std::string filename = "response.json";
	fs::path filePath = fs::current_path() / filename;

	std::ofstream outFile(filePath);
	if (outFile.is_open()) {
		outFile << std::setw(4) << response << std::endl; // Pretty-print with indentation
		outFile.close();
		std::cout << "Response saved to " << filePath << std::endl;
	}
	else {
		std::cerr << "Failed to open file " << filePath << " for writing" << std::endl;
	}
	// Handle response based on HTTP status code
	switch (httpCode) {
	case 203: // Scores successfully fetched
		this->serverInformation = "Fetched scores for user: " + this->accountState->getUsername();
		std::cout << "Fetched scores for user: " << this->accountState->getUsername() << std::endl;
		break;
	case 200: // Fetched scores for anonymous user
		this->serverInformation = "Fetched scores";
		std::cout << "Fetched scores for anonymous user\n";
		break;
	case 500: // Internal server error
		this->serverInformation = "Internal server error";
		std::cout << "Internal server error\n";
		break;
	default:
		this->serverInformation = "Unknown error occurred";
		std::cout << "Unknown error occurred\n";
		break;
	}
}




void ScoreState::update(const float& dt)
{
	this->updateMousePosition();
	this->updateButtons();
}

void ScoreState::renderButtons(sf::RenderTarget& target)
{
	for (auto& it : this->buttons) {
		it.second->render(target);
	}
}


void ScoreState::render(sf::RenderTarget* target)
{
	//std::cout << this->serverInformation << std::endl;
	if (!target)
		target = this->window;

	target->draw(this->background);
	this->renderButtons(*target);

	this->serverInfo.setPosition(240.f, 240.f);
	this->serverInfo.setFont(this->font);
	this->serverInfo.setCharacterSize(24);
	this->serverInfo.setString(this->serverInformation);
	this->serverInfo.setFillColor(sf::Color(150, 150, 150, 255));
	target->draw(this->serverInfo);

	sf::Text mouseText;
	mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 10);
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(12);
	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y;
	mouseText.setString(ss.str());

	target->draw(mouseText);
}


