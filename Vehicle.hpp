#ifndef OUTRUN_VEHICLE_HPP
#define OUTRUN_VEHICLE_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "Menu.hpp"

#define XINC 0.033f // x increment
#define ACC_INC 0.01f


class Vehicle {
public:
    enum Elevation {
        UP,
        FLAT,
        DOWN
    };
    enum Action {
        NONE,
        BRAKE,
        ACCELERATE,
        CRASH,
        BOOT
    };
    enum Direction {
        RIGHT,
        TURNLEFT,
        TURNRIGHT
    };

protected:
    const float maxSpeed, halfMaxSpeed, scale;
    const int maxCounterToChange;

    float speed;
    float posX, posY, previousY, minScreenX, maxScreenX;

    std::vector<sf::Texture> textures;
    int current_code_image;
    int counter_code_image; // Counter to change actual_code_image

public:
    
    Vehicle(float maxSpeed, float scale, int maxCounterToChange, float speed, float posX, float posY, float previousY,
            float minScreenX, float maxScreenX, const std::string &vehicle, int numTextures, int currentCodeImage,
            int counterCodeImage);

    
    void setPosition(float pX, float pY);

    
    float getPosX() const;

    
    float getPosY() const;

    
    float getMinScreenX() const;

    
    float getMaxScreenX() const;

    
    float getAcceleration() const;
};


#endif //OUTRUN_VEHICLE_HPP
