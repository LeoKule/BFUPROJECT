#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "SFML/Graphics.hpp"
#define WIDTH 1164
#define HEIGHT 640
namespace dg {
    class Drawable {
    public:
        virtual void draw(sf::RenderWindow& window) = 0;
    };
}

#endif  // DRAWABLE_H
