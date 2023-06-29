#ifndef DART_H
#define DART_H
#define _USE_MATH_DEFINES
#include "Drawable.h"
#include "Scoreboard.h"
#include <thread>
#include <chrono>
#include <vector>
#include <iostream>
#include <cmath>


namespace dg {
    class Dart : public Drawable {
    public:
        Dart(float x, float y, float w, float h, float angle, float v0);

        void setPushed(bool put);

        bool uploadTexture();

        sf::Sprite& getShape();

        void setStartPosition(float x0, float y0);

        void setAngle(float angle);

        void setInitialSpeed(float v0);

        void setSelfTime(float time);

        void addSelfTime(float time);

        void setPosition(float x, float y);

        void Move(Scoreboard& scoreboard);

        float getX() const;

        float getY() const;

        float getHeight() const;

        float getWidth() const;

        //float getAngle(float x1, float y1, float x2, float y2);

        void draw(sf::RenderWindow& window) override;

    private:
        float s_x, s_y;
        float s_x0, s_y0;
        float s_w, s_h;
        float s_angle;
        float s_v0;
        float s_t;
        bool isPushed;

        sf::Texture m_texture;
        sf::Sprite m_shape;

        int getPoints() const;
    };
}

#endif  // DART_H
