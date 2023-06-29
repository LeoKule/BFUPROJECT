#ifndef TEXTBOX_H
#define TEXTBOX_H

#include "Drawable.h"
#include "SFML/Graphics.hpp"

namespace dg {
    class TextBox : public Drawable {
    public:
        TextBox(float x, float y, const std::string& text);

        void setText(const std::string& text);

        sf::Text getShape();

        void setPosition(float x, float y);

        void draw(sf::RenderWindow& window) override;

    private:
        float x, y;
        sf::Font font;
        sf::Text text;

        void loadFont();
    };
}

#endif  // TEXTBOX_H
