#include "stdafx.h"
#include "TextInput.h"


TextInput::TextInput(float x, float y, float width, float height,
    sf::Font* font, std::string placeholder,
    sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor)
    : font(font), idleColor(idleColor), hoverColor(hoverColor), activeColor(activeColor)
{
    this->textInputState = TI_IDLE;
    this->isActive = false;
    this->box.setPosition(sf::Vector2f(x, y));
    this->box.setSize(sf::Vector2f(width, height));
    this->box.setFillColor(this->idleColor);

    this->placeholdertest = placeholder;
    this->text.setFont(*this->font);
    this->text.setFillColor(sf::Color::Black);
    this->text.setCharacterSize(12);
    this->text.setPosition(
        (int)this->box.getPosition().x + (this->box.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
        (int)this->box.getPosition().y + (this->box.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f
    );
   
    this->placeholder.setFont(*this->font);
    this->placeholder.setString(placeholder);
    this->placeholder.setCharacterSize(12);
    this->placeholder.setFillColor(sf::Color(150, 150, 150));
    this->placeholder.setPosition(
        (int)this->box.getPosition().x + (this->box.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
        (int)this->box.getPosition().y + (this->box.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f
    );
   
}

TextInput::~TextInput()
{
}

const bool TextInput::getIsActive() const
{
    return this->isActive;
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
            std::cout << "active" << this->placeholdertest << std::endl;
          
        }
    }
    if (!this->box.getGlobalBounds().contains(mousePos) && 
        sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        this->textInputState = TI_IDLE;
        this->isActive = false;
        std::cout << "idle" << this->placeholdertest << std::endl;
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