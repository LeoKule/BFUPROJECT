#include "Textbox.h"
#include "Logger.h"

namespace dg {
    TextBox::TextBox(float x, float y, const std::string& initialText) : x(x), y(y) {
        loadFont();
        text.setFont(font);
        text.setCharacterSize(24);
        text.setString(initialText);
        text.setFillColor(sf::Color::White);
        text.setPosition(x, y);
    }

    void TextBox::setText(const std::string& Newtext) {
        text.setString(Newtext);
    }

    void TextBox::setPosition(float x, float y) {
        this->x = x;
        this->y = y;
        text.setPosition(x, y);
    }

    void TextBox::draw(sf::RenderWindow& window) {
        window.draw(text);
    }

    void TextBox::loadFont() {
        if (!font.loadFromFile("data/ttf/arial.ttf")) {
            // Handle font loading error
            Logger::error("ERROR when loading arial.ttf");
        }
    }
}
