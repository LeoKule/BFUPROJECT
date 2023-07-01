#pragma once
#ifndef SFML_SAMPLE_DART_H
#define SFML_SAMPLE_DART_H

#include "SFML/Graphics.hpp"
#include "Scoreboard.h"
#include "gameobject.h"
#include <memory>
namespace dg {
    class Dart : GameObject {
    public:
        Dart(float x, float y, float w, float h, float angle, float v0);

        ~Dart() override;

        bool uploadTexture();

        sf::Sprite *getShape();

        void setPushed(bool put);

        void setStartPosition(float x0, float y0) override;

        void setAngle(float angle);

        void setInitialSpeed(float v0);

        void setSelfTime(float time);

        void addSelfTime(float time);

        void setPosition(float x, float y) override;

        void Move(Scoreboard &scoreboard);

        float getX() override;

        float getY() override;

        float getHeight();

        float getWidth();

        float getAngle();


    private:
        // текущее положение
        float s_x;
        float s_y;
        // начальное положение
        float s_x0;
        float s_y0;
        // высота и ширина изображения
        float s_h;
        float s_w;
        // текущий угол
        float s_angle;
        // начальная скорость
        float s_v0;
        // текущее время
        float s_t;

        // переменная для обозначения был ли дротик брошен из начального положения, необходимо для застревания в
        // столе на старте броска
        bool isPushed = false;

        sf::Texture m_texture;
        //sf::Sprite *m_shape;
        std::unique_ptr<sf::Sprite> m_shape;

        int getPoints();
    };

}
#endif //SFML_SAMPLE_DART_H
