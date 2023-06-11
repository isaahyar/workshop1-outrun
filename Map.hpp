#ifndef OUTRUN_MAP_HPP
#define OUTRUN_MAP_HPP

#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "Menu.hpp"
#include "Enemy.hpp"

#define PRE_POS 2
#define FORK_RADIUS 10.0f

const int RECTANGLE = PRE_POS * 2 + 1; // the number of lines that form a rectangle


class Map {
    
    struct SpriteInfo {
        int spriteNum;
        float offset, spriteMinX, spriteMaxX, spriteToSideX; // spriteToSideX is the space from spriteMinX to another minX side
        bool repetitive;

        
        SpriteInfo();
    };

    
    struct Line {
        float x, y, z; // 3d center of line
        float X{}, Y{}, W{}; // screen coord (X: road center, Y: road top, W: road width / 2)
        float curve, clip{}, scale{};
        bool mainColor;
        SpriteInfo spriteLeft, spriteRight;
        float bgX; // background position
        float offsetX, yOffsetX;

        
        explicit Line();

        
        void
        project(float camX, float camY, float camZ, float camD, float width, float height, float rW, float zOffset);

        enum HitCoeffType {
            HIT_CENTER,
            HIT_LEFT,
            HIT_RIGHT,
            HIT_SIDES // Example arc
        };

        
        void drawSprite(sf::RenderTexture &w, const std::vector<sf::Texture> &objs, const std::vector<float> &hitCoeff,
                        const std::vector<HitCoeffType> &hitCoeffType, const std::vector<float> &scaleCoeff,
                        SpriteInfo &object, bool left) const;
    };

    // Circles info for forks (with different centers):
    // Circle 1: y = -sqrt(r² - x²) + r
    // Circle 2: y = sqrt(r² - (x - a)²) + b
    const float aOffsetX = sqrt(2.0f) * FORK_RADIUS; // a value for C1
    const float bOffsetX = FORK_RADIUS - sqrt(2.0f) * FORK_RADIUS; // b value for C1
    const float xChange = static_cast<const float>(FORK_RADIUS * sin(0.75f * M_PI)); // x increment

    // Background
    sf::Texture bg;

    // Objects
    std::vector<sf::Texture> objects;
    std::vector<float> hitCoeffs;
    std::vector<Line::HitCoeffType> hitCoeffTypes;
    std::vector<float> scaleCoeffs;
    std::vector<Line> lines;

    // Colors
    sf::Color roadColor[2], grassColor[2], rumbleColor, dashColor;

    // Camera
    float posX, posY;

    // Next map
    Map *next, *nextRight;

    bool initMap;
    bool goalMap;

    int maxTime;

    
    Line *getLine(int n);

    
    Line getLine(int n) const;

    
    Line *getPreviousLine(int n);

    
    Line getPreviousLine(int n) const;

    
    void addLine(float x, float y, float &z, float prevY, float curve, bool mainColor, const SpriteInfo &spriteLeft,
                 const SpriteInfo &spriteRight, float &bgX, float &offsetX, float offsetInc = 0.0f);

    
    void addLines(float x, float y, float &z, float &bgX, const std::vector<std::vector<std::string>> &instructions);

    
    void
    loadObjects(const std::string &path, const std::vector<std::string> &objectNames, std::vector<int> &objectIndexes);

public:

    Map(Config &c, const std::string &path, const std::string &bgName,
        const std::vector<std::string> &objectNames, bool random, int time);

    
    Map(const Map &map, int &flagger, int &semaphore);

    
    Map(int &flagger, int &goalEnd);

    
    void setColors(const Map &map);

    
    void incrementSpriteIndex(int line, bool right, int increment = 1);

    
    void addNextMap(Map *map);

    
    void addFork(Map *left, Map *right);

    
    void setOffset(float yOffset);

    
    void updateView(float pX, float pY);

    
    float getCamX() const;

    
    float getCamY() const;

    
    void draw(Config &c, std::vector<Enemy> &vehicles);

    
    bool hasCrashed(const Config &c, float prevY, float currentY, float currentX, float minX, float maxX,
                    float &crashPos) const;

    
    bool hasGotOut(float currentX, float currentY) const;

    
    float getCurveCoefficient(float currentY) const;

    
    Vehicle::Elevation getElevation(float currentY) const;

    
    bool isOver() const;

    
    float getMaxY() const;

    
    float getOffsetX() const;

    
    bool inFork(float currentY) const;

    
    Map *getNext() const;

    
    bool isInitMap() const;

    
    bool isGoalMap() const;

    
    int getTime() const;
};


#endif //OUTRUN_MAP_HPP
