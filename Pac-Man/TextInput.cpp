#include "stdafx.h"
#include "TextInput.h"


void TextInput::initInfo()
{
    std::string line1 = "Password must contain:";
    std::string line2 = "- minimum 8 characters";
    std::string line3 = "- at least one digit";
    std::string line4 = "- at least one special symbol";
    std::string line5 = "- at least one small letter";
    std::string line6 = "- at least one capital letter";
    information.push_back(line1);
    information.push_back(line2);
    information.push_back(line3);
    information.push_back(line4);
    information.push_back(line5);
    information.push_back(line6);
}

TextInput::TextInput(float x, float y, float width, float height,
    sf::Font* font, std::string placeholder,
    sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor)
    : font(font), idleColor(idleColor), hoverColor(hoverColor), activeColor(activeColor)
{
    this->initInfo();
    this->textInputState = TI_IDLE;
    this->isActive = false;
    this->box.setPosition(sf::Vector2f(x, y));
    this->box.setSize(sf::Vector2f(width, height));
    this->box.setFillColor(this->idleColor);

    this->placeholdertest = placeholder;
    this->text.setFont(*this->font);
    this->text.setFillColor(sf::Color::White);
    this->text.setCharacterSize(18);
    this->text.setPosition(x + 10.f, y + 5.f);
      
  
    this->placeholder.setFont(*this->font);
    this->placeholder.setString(placeholder);
    this->placeholder.setCharacterSize(16);
    this->placeholder.setFillColor(sf::Color::Black);
    this->placeholder.setPosition(x + 10.f, y + 5.f);
  
}

TextInput::~TextInput()
{
}

const bool TextInput::getIsActive() const
{
    return this->isActive;
}

const std::string TextInput::getUserInput() const
{
    return this->input;
}

void TextInput::clearInput()
{
    this->input = "";

}

std::vector<std::string> TextInput::getInformationText()
{
    return this->information;
}

void TextInput::update(const sf::Vector2f mousePos)
{

    if(!isActive)
        this->textInputState = TI_IDLE;

    ////Hover
    if (this->box.getGlobalBounds().contains(mousePos))
    {
        if(!isActive)
            this->textInputState = TI_HOVER;

        //Pressed
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            this->textInputState = TI_ACTIVE;
            isActive = true;
            
          
        }
    }
    if (!this->box.getGlobalBounds().contains(mousePos) && 
        sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        this->textInputState = TI_IDLE;
        this->isActive = false;
       
    }

    switch (this->textInputState)
    {
    case TI_IDLE:
        this->box.setFillColor(this->idleColor);
        break;
    case TI_HOVER:
        this->box.setFillColor(this->hoverColor);
        break;
    case TI_ACTIVE:
        this->box.setFillColor(this->activeColor);
        break;
    default:
        this->box.setFillColor(sf::Color::Red);
        break;
    }

}

void TextInput::handleEvent(sf::Event event) {
  
    if (this->textInputState = TI_ACTIVE && event.type == sf::Event::TextEntered) {
        if (event.text.unicode == '\b') { // Handle backspace
            if (!input.empty()) {
                input.pop_back();
            }
        }
        else if (event.text.unicode < 128 && event.text.unicode != '\r') { // Ignore Enter key
            input += static_cast<char>(event.text.unicode);
        }
        text.setString(input);
    }
}

void TextInput::render(sf::RenderTarget& target) {

    target.draw(this->box);
    if (input.empty() && this->textInputState != TI_ACTIVE) {
        target.draw(placeholder);
    }
    else {
        target.draw(text);
    }
    
}