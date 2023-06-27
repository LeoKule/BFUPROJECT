#include "Dart.h"
#include "Dart_game.h"
#include "Logger.h"

namespace dg {
    Dart::Dart(float X, float Y, float W, float H, float Angle, float V0){
        x = X; y = Y; w = W; h = H; angle = Angle; v0 = V0; t = 0; isPushed = false; x0 = X; y0 = Y;
        m_shape.setPosition(x, y);
        m_shape.setOrigin(sf::Vector2f(w, h));
        uploadTexture();
        m_shape.setTexture(m_texture);
    }

    float dt;

    bool Dart::uploadTexture() {
        if (!m_texture.loadFromFile("data/img/drotic.png")) {
            std::cout << "ERROR when loading drotic.png" << std::endl;
            return false;
        }
        m_texture.setSmooth(true);
        return true;
    }

    sf::Sprite &Dart::getShape() {
        return m_shape;
    }

    void Dart::setPushed(bool put) {
        isPushed = put;
    }

    void Dart::setStartPosition(float x0, float y0) {
        this->x0 = x0;
        this->y0 = y0;
        x = x0;
        y = y0;
        m_shape.setPosition(x, y);
    }

    void Dart::setAngle(float Angle) {
        this->angle = Angle;
    }

    void Dart::setInitialSpeed(float V0) {
        this->v0 = V0;
    }

    void Dart::setSelfTime(float Time) {
        t = Time;
    }

    void Dart::addSelfTime(float time) {
        t += time;
    }

    void Dart::setPosition(float X, float Y) {
        if (X - w + 30 < 0)
            x = w - 30;
        else if (x + w - 30 > WIDTH)
            x = WIDTH - w + 30;
        else
            X = x;
        if (y - h < 0)
            y = h;
        else if (y + h > HEIGHT)
            y = HEIGHT - h;
        else
            y = Y;
        m_shape.setPosition(x, y);
    }

    void Dart::Move(Scoreboard &scoreboard) {
        if ((x + w - 30 >= WIDTH && (y < 64 || y > 414)) ||
            (x + w - 10 >= WIDTH && !(y < 64 || y > 414))) {
            scoreboard.addScore(getPoints());
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            this->v0 = 5;
            this->angle = M_PI / 2;
            this->setPosition(250, 150);
            this->setStartPosition(250, 150);
            t = 0;
            isPushed = false;
        } else if ((!isPushed && y + h <= 400) ||
                   (isPushed && x - w + 30 > 0 && y - h > 0 && y + h < HEIGHT)) {
            // Perform dart movement based on the elapsed time and initial velocity
            float x = x0 + v0 * cos(angle) * t;
            float y = y0 + v0 * sin(angle) * t + G * t * t / 2;
            m_shape.setPosition(x, y);
            m_shape.setRotation(getAngle(x0, y0, x, y) * (180.0 / M_PI));

            // Check for collision or any other conditions to stop the movement
            if (isPushed) {
                scoreboard.addScore(-10);
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
                this->v0 = 5;
                this->angle = M_PI / 2;
                this->setPosition(240, 150);
                this->setStartPosition(240, 150);
                t = 0;
                isPushed = false;
            }

            t += dt;
        }
    }

    float Dart::getX() const {
        return x;
    }

    float Dart::getY() const {
        return y;
    }

    float Dart::getHeight() const {
        return h;
    }

    float Dart::getWidth() const {
        return w;
    }

    float Dart::getAngle(float x1, float y1, float x2, float y2) {
        float dx = x2 - x1;
        float dy = y2 - y1;
        return atan2(dy, dx);
    }


    void Dart::draw(sf::RenderWindow &window) {
        window.draw(m_shape);
    }


    int Dart::getPoints() const {
        if (64 <= y && y <= 139 || 339 <= y && y <= 414) {
            return 1;
        } else if (139 < y && y <= 189 || 289 <= y && y < 339) {
            return 3;
        } else if (189 < y && y <= 224 || 254 <= y && y < 289) {
            return 5;
        } else if (224 <= y && y <= 254) {
            return 10;
        } else
            return -5;
    }

}
