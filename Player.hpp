#ifndef OUTRUN_PLAYER_HPP
#define OUTRUN_PLAYER_HPP

#include "Vehicle.hpp"

class Player : public Vehicle {
    const float speedMul, maxAcc, accInc, scaleY;
    float acceleration, minCrashAcc, xDest;
    int inertia;

    sf::Sprite sprite;
    bool crashing; // True if crashing state is on
    bool smoking; // True if player generates smoke
    bool skidding; // True if player is skidding

    bool firstCrash, firstTurnLeft, firstTurnRight;

public:
    
    Player(float maxSpeed, float speedMul, float accInc, float scaleX, float scaleY, int maxCounterToChange,
           const std::string &vehicle, float pX, float pY);

    
    float getPreviousY() const;

    
    void hitControl(bool vehicleCrash);

    
    bool isCrashing() const;

    
    float getRealSpeed() const;

    
    Action accelerationControl(Config &c, bool hasGotOut);

    
    Direction rotationControl(Config &c, float curveCoefficient);

    
    void draw(Config &c, const Action &a, const Direction &d, const Elevation &e, bool enableSound = true);

    
    void drawInitialAnimation(Config &c, float x, bool &end);

    
    void drawGoalAnimation(Config &c, int &step, bool &end, bool smoke = true);

    
    void setSmoking(bool smoke);
};


#endif //OUTRUN_PLAYER_HPP
