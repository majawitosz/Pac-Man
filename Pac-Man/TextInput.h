#pragma once



enum textInputStates {
    TI_IDLE = 0,
    TI_HOVER,
    TI_ACTIVE
};

class TextInput {
private:
    short unsigned textInputState;
    sf::RectangleShape box;
    sf::Text text;
    sf::Text placeholder;
    sf::Font* font;
    std::string input;

    std::string placeholdertest;
    std::vector<std::string> information;
    std::string info;

    sf::Color idleColor;
    sf::Color hoverColor;
    sf::Color activeColor;
    void initInfo();

    bool isActive;
public:
    TextInput(float x, float y, float width, float height,
        sf::Font* font, std::string text,
        sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);
    virtual ~TextInput();
    const bool getIsActive() const;
    const std::string getUserInput() const;
    void clearInput();
    std::vector<std::string> getInformationText();

    void handleEvent(sf::Event event);
    void update(const sf::Vector2f mousePos);
    void render(sf::RenderTarget& target);
      


};
