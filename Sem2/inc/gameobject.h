#pragma once
#include <SFML/Graphics.hpp>

namespace dg {
    class GameObject {
    public:
        virtual ~GameObject() = default;

        virtual void setPosition(float x, float y) = 0;
        virtual void setStartPosition(float x0, float y0) = 0;
        virtual float getX() = 0;
        virtual float getY() = 0;
    };
}
