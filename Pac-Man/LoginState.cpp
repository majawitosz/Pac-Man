#include "stdafx.h"
#include "LoginState.h"



void LoginState::initVariables()
{
}

void LoginState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Emulogic-zrEw.ttf")) {
		throw("ERROR::MAINMENUSTATE::COULD_NOT_LOAD_FONT");

	}
	if (!this->font2.loadFromFile("Fonts/Roboto-Light.ttf")) {
		throw("ERROR::MAINMENUSTATE::COULD_NOT_LOAD_FONT");
	}

}

void LoginState::initKeybinds()
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

void LoginState::initButtons()
{
	this->buttons["SUBMIT"] = new Button(320, 360, 150, 50,
		&this->font, "SUBMIT",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
	this->buttons["EXIT_STATE"] = new Button(320, 440, 150, 50,
		&this->font, "BACK",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

}

void LoginState::initTextInput()
{
	this->textInputs["USERNAME"] = new TextInput(250, 200, 300, 30,
		&this->font2, "username",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
	this->textInputs["PASSWORD"] = new TextInput(250, 280, 300, 30,
		&this->font2, "password",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

}

LoginState::LoginState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, 
	std::stack<State*>* states, AccountState* accountState, MainMenuState* mainMenuState)
	: State(window, supportedKeys, states), accountState(accountState), mainMenuState(mainMenuState)
{
	//this->accountState = nullptr;
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initButtons();
	this->initTextInput();

}

LoginState::~LoginState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it) {
		delete it->second;
	}

}



void LoginState::initBackground()
{
	this->background.setSize(
		sf::Vector2f(static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y)));

	if (!this->bgTexture.loadFromFile("Resources/Images/Backgrounds/bg1.png"))
	{
		throw "ERRPR::MAIN_MENU_STATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}

	this->background.setTexture(&this->bgTexture);
}


void LoginState::updateInput(const float& dt)
{
	//this->endStateUpdate();


}

void LoginState::updateButtons()
{
	// Updates all the button in the state
	for (auto& button : this->buttons | std::views::values)
	{
		button->update(this->mousePosView);
	}

	//for (auto& it : this->buttons)
	//{
	//	it.second->update(this->mousePosView);
	//}
	if (this->buttons["SUBMIT"]->isPressed())
	{
		sf::sleep(sf::milliseconds(100));

		std::thread(&LoginState::sendRequest, this).detach();
		//this->checkRegex();
	}
	if (this->buttons["EXIT_STATE"]->isPressed())
	{
		sf::sleep(sf::milliseconds(100));
		this->endState();
	}

}

void LoginState::updateTextInputs()
{
	for (auto& it : this->textInputs)
	{
		it.second->update(this->mousePosView);
	}
}


static size_t my_write(void* buffer, size_t size, size_t nmemb, void* param)
{
	std::string& text = *static_cast<std::string*>(param);
	size_t totalsize = size * nmemb;
	text.append(static_cast<char*>(buffer), totalsize);
	return totalsize;
}
void LoginState::sendRequest()
{
	CURL* curl;
	CURLcode res;
	std::string result;
	long httpCode = 0;

	curl_global_init(CURL_GLOBAL_DEFAULT);
	curl = curl_easy_init();

	if (curl) {
		std::string url = "http://localhost:3000/login";
		std::string username = this->textInputs["USERNAME"]->getUserInput();
		std::string password = this->textInputs["PASSWORD"]->getUserInput();
		std::string postFields = "username=" + username + "&password=" + password;

		// Set the URL
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

		// Set POST request
		curl_easy_setopt(curl, CURLOPT_POST, 1L);

		// Set POST fields
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postFields.c_str());

		// Set the write function callback
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, my_write);

		// Set the string to store the result
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result);

		// Optional: Set verbose mode to 1 (for debugging)
		curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

		// Perform the request
		res = curl_easy_perform(curl);

		curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);

		// Check for errors
		if (res != CURLE_OK) {
			std::cerr << "CURL error: " << curl_easy_strerror(res) << std::endl;
		}
		else {
			//std::cout << "Response: " << result << std::endl;
			handleResponse(result, httpCode, username);
		}

		// Cleanup
		curl_easy_cleanup(curl);
	}

	curl_global_cleanup();

}

void LoginState::handleResponse(const std::string& response, long httpCode, std::string username)
{
	json jsonResponse;
	try {
		jsonResponse = json::parse(response);
	}
	catch (json::parse_error& e) {
		std::cerr << "JSON parse error: " << e.what() << std::endl;
		return;
	}

	// Handle response based on HTTP status code
	switch (httpCode) {
	case 201: // Login successful
		this->serverInformation = "Login successful";
		std::cout << "Login successful\n";
		//this->userName = username;
		//this->logedIn = true;
		this->mainMenuState->setLoginStatus(true);
		this->mainMenuState->setUsername(username);
		
		//setUsername(username);
		//setLoginStatus(true);
		//sf::sleep(sf::milliseconds(1500));
		//this->endState();
		break;
	case 400: // Username doesn't exist
		this->serverInformation = "Username doesn't exist";
		std::cout << "Username doesn't exist\n";
		break;
	case 401: // Wrong password
		this->serverInformation = "Wrong password";
		std::cout << "Wrong password\n";
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

void LoginState::handleEvent(sf::Event event)
{
	if (event.type == sf::Event::Closed) {
		this->window->close();
	}
	if (this->textInputs["USERNAME"]->getIsActive()) {
		this->textInputs["USERNAME"]->handleEvent(event);
	}
	else if (this->textInputs["PASSWORD"]->getIsActive()) {
		this->textInputs["PASSWORD"]->handleEvent(event);
	}
}


void LoginState::update(const float& dt)
{
	this->updateMousePosition();
	this->updateInput(dt);
	this->updateButtons();
	this->updateTextInputs();
}

void LoginState::renderButtons(sf::RenderTarget& target)
{
	for (auto& it : this->buttons) {
		it.second->render(target);
	}
}

void LoginState::renderTextInput(sf::RenderTarget& target)
{
	for (auto& it : this->textInputs) {
		it.second->render(target);
	}

}

void LoginState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);

	this->renderButtons(*target);
	this->renderTextInput(*target);

	if (!this->textInputs["PASSWORD"]->getInformationText().empty() && this->displayInfo) {
		for (int i = 0; i < this->textInputs["PASSWORD"]->getInformationText().size() - 1; i++)
		{
			sf::Text text;
			this->info.push_back(text);
			this->info[i].setFont(this->font2);
			this->info[i].setCharacterSize(12);
			this->info[i].setPosition(580.f, 200.f + i * 20.f);
			std::stringstream ss;
			ss << this->textInputs["PASSWORD"]->getInformationText()[i];
			this->info[i].setString(ss.str());
			target->draw(this->info[i]);
		}
	}
	this->serverInfo.setPosition(270.f, 170.f);
	this->serverInfo.setFont(this->font2);
	this->serverInfo.setCharacterSize(12);
	this->serverInfo.setString(this->serverInformation);
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