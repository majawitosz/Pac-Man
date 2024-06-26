#include "stdafx.h"
#include "RegisterState.h"



void RegisterState::initVariables()
{
}

void RegisterState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Emulogic-zrEw.ttf")) {
		throw("ERROR::MAINMENUSTATE::COULD_NOT_LOAD_FONT");

	}
	if (!this->font2.loadFromFile("Fonts/RobotoMono-Bold.ttf")) {
		throw("ERROR::MAINMENUSTATE::COULD_NOT_LOAD_FONT");
	}

}

void RegisterState::initKeybinds()
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

void RegisterState::initButtons()
{
	this->buttons["SUBMIT"] = new Button(320, 360, 150, 50,
		&this->font, "SUBMIT",
		sf::Color::Transparent, sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
	this->buttons["EXIT_STATE"] = new Button(320, 440, 150, 50,
		&this->font, "BACK",
		sf::Color::Transparent, sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

}

void RegisterState::initTextInput()
{
	this->textInputs["USERNAME"] = new TextInput(250, 200, 300, 30, 
		&this->font2, "username", 
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
	this->textInputs["PASSWORD"] = new TextInput(250, 280, 300, 30, 
		&this->font2, "password", 
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

}

RegisterState::RegisterState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initButtons();
	this->initTextInput();

}

RegisterState::~RegisterState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it) {
		delete it->second;
	}

}



void RegisterState::initBackground()
{
	this->background.setSize(
		sf::Vector2f(static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y)));

	if (!this->bgTexture.loadFromFile("Resources/Images/Backgrounds/bg1.png"))
	{
		throw "ERRPR::MAIN_MENU_STATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}

	this->background.setTexture(&this->bgTexture);
}


void RegisterState::updateInput(const float& dt)
{
	//this->endStateUpdate();


}

void RegisterState::updateButtons()
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

		this->checkRegex();
	}
	if (this->buttons["EXIT_STATE"]->isPressed())
	{
		sf::sleep(sf::milliseconds(100));
		this->endState();
	}

}

void RegisterState::updateTextInputs()
{
	for (auto& it : this->textInputs)
	{
		it.second->update(this->mousePosView);
	}
}

void RegisterState::checkRegex()
{
	std::string username = this->textInputs["USERNAME"]->getUserInput();
	std::string password = this->textInputs["PASSWORD"]->getUserInput();

	if (!this->isValidPassword(password) || !this->isValidUsername(username)) {
		for (auto& it : this->textInputs)
		{
			it.second->clearInput();
			this->displayInfo = true;
		}
	} 
	else {
		std::thread(&RegisterState::sendRequest, this).detach();
		
	}

}
static size_t my_write(void* buffer, size_t size, size_t nmemb, void* param)
{
	std::string& text = *static_cast<std::string*>(param);
	size_t totalsize = size * nmemb;
	text.append(static_cast<char*>(buffer), totalsize);
	return totalsize;
}
void RegisterState::sendRequest()
{
	CURL* curl;
	CURLcode res;
	std::string result;
	long httpCode = 0;

	curl_global_init(CURL_GLOBAL_DEFAULT);
	curl = curl_easy_init();

	if (curl) {
		std::string url = "http://localhost:3000/register";
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
			handleResponse(result, httpCode);
		}

		// Cleanup
		curl_easy_cleanup(curl);
	}

	curl_global_cleanup();

}

void RegisterState::handleResponse(const std::string& response, long httpCode)
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
	case 200: // Registration successful
		this->serverInformation = "Registration successful";
		std::cout << "Registration successful\n";
		sf::sleep(sf::milliseconds(1500));
		this->endState();
		break;
	case 400: // Username already exists
		if (jsonResponse.contains("error") && jsonResponse["error"] == "Username already exists") {
			this->serverInformation = "Username already exists";
			std::cout << "Username already exists\n";
		}
		else {
			this->serverInformation = "Bad request";
			std::cout << "Bad request\n";
		}
		//this->displayInfo = true;
		break;
	case 500: // Internal server error
		this->serverInformation = "Internal server error";
		std::cout << "Internal server error\n";
		//this->displayInfo = true;
		break;
	default:
		this->serverInformation = "Unknown error occurred";
		std::cout << "Unknown error occurred\n";
		//this->displayInfo = true;
		break;
	}
}

bool RegisterState::isValidPassword(const std::string& password)
{
	std::regex password_regex("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)(?=.*[@$!%*?&])[A-Za-z\\d@$!%*?&]{8,}$");
	return std::regex_match(password, password_regex);
}

bool RegisterState::isValidUsername(const std::string& username)
{
	std::regex username_regex("^[a-zA-Z0-9]{5,12}$");
	return std::regex_match(username, username_regex);
}

void RegisterState::handleEvent(sf::Event event)
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


void RegisterState::update(const float& dt)
{
	this->updateMousePosition();
	this->updateInput(dt);
	this->updateButtons();
	this->updateTextInputs();
}

void RegisterState::renderButtons(sf::RenderTarget& target)
{
	for (auto& it : this->buttons) {
		it.second->render(target);
	}
}

void RegisterState::renderTextInput(sf::RenderTarget& target)
{
	for (auto& it : this->textInputs) {
		it.second->render(target);
	}
	
}

void RegisterState::render(sf::RenderTarget* target)
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
}