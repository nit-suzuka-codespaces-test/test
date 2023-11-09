// Ball.cpp
#include <cmath>
#include <iostream>
#include "Ball.h"
using namespace std;

void Ball::setVelocity(sf::Vector2f v){
    vel = v;
}

void Ball::update(double dt){
    setPosition(positionAfter(dt));
}

void Ball::boundaryCheck(double dt, unsigned w_width, unsigned w_height){
    sf::Vector2f newPos = positionAfter(dt);
    sf::Vector2f size = getSize();

    if(newPos.x < 0){
        setVelocity(sf::Vector2f(-vel.x, vel.y));

        sf::Vector2f pos = this->getPosition();
        setPosition(sf::Vector2f(-pos.x, pos.y));
    }

    if(newPos.x + size.x > w_width){
        setVelocity(sf::Vector2f(-vel.x, vel.y));

        sf::Vector2f pos = this->getPosition();
        setPosition(sf::Vector2f(2 * (w_width - size.x) - pos.x, pos.y));
    }

    if(newPos.y < 0){
        setVelocity(sf::Vector2f(vel.x, -vel.y));

        sf::Vector2f pos = this->getPosition();
        setPosition(sf::Vector2f(pos.x, -pos.y));
    }
    
    if(newPos.y + size.y > w_height){
        setVelocity(sf::Vector2f(vel.x, -vel.y));

        sf::Vector2f pos = this->getPosition();
        setPosition(sf::Vector2f(pos.x, 2 * (w_height - size.y) - pos.y));
    }
}

bool Ball::collision(double dt, const sf::RectangleShape& rect){
    sf::Vector2f newPos = positionAfter(dt);
    sf::Vector2f size = getSize();

    sf::Vector2f rectPos = rect.getPosition();
    sf::Vector2f rectSize = rect.getSize();

    if(newPos.x < rectPos.x + rectSize.x && newPos.x + size.x > rectPos.x && newPos.y < rectPos.y + rectSize.y && newPos.y + size.y > rectPos.y){
        sf::Vector2f pos = this->getPosition();

        if(pos.x >= rectPos.x + rectSize.x){
            setVelocity(sf::Vector2f(-vel.x, vel.y));
            setPosition(sf::Vector2f(2 * (rectPos.x + rectSize.x) - pos.x, pos.y));
        }
        else if(pos.x + size.x <= rectPos.x){
            setVelocity(sf::Vector2f(-vel.x, vel.y));
            setPosition(sf::Vector2f(2 * (rectPos.x - size.x) - pos.x, pos.y));
        }

        if(pos.y >= rectPos.y + rectSize.y){
            setVelocity(sf::Vector2f(vel.x, -vel.y));
            setPosition(sf::Vector2f(pos.x, 2 * (rectPos.y + rectSize.y) - pos.y));
        }
        else if(pos.y + size.y <= rectPos.y){
            setVelocity(sf::Vector2f(vel.x, -vel.y));
            setPosition(sf::Vector2f(pos.x, 2 * (rectPos.y - size.y) - pos.y));
        }

        return true;
    }

    return false;
}

sf::Vector2f Ball::positionAfter(double dt){
    sf::Vector2f pos = this->getPosition();
    return sf::Vector2f(pos.x + vel.x * dt, pos.y + vel.y * dt);
}