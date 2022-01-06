#pragma once

#include "../../include/helperFunctions.h"
#include "../WSledDisplay/WSLedDisplay.h"

using namespace helper;

const int MAX_SNAKE_SIZE = 12;
enum direction {UP, DOWN, LEFT, RIGHT, STOP};

class Cube
{
    public:
    Cube(int initX, int initY, rgb initColor, int maxX = DISPLAY_WIDTH, int maxY = DISPLAY_HEIGHT);
    Cube(int maxX = DISPLAY_WIDTH, int maxY = DISPLAY_HEIGHT);

    bool    move(bool up, bool down, bool left, bool right);
    bool    moveRight();
    bool    moveLeft();
    bool    moveUp();
    bool    moveDown();
    void    setCoordinates(int x, int y);

    int     getX();
    int     getY();
    
    void    setColor(rgb color);
    void    setColor(hsv color);
    Pixel   getColor();
    void    draw(DisplayGrid& displayGrid);

    private:
    int     m_x, m_maxX;
    int     m_y, m_maxY;
    Pixel   m_color;
};


class Snake
{
    public:
    Snake(int initHeadX, int initHeadY, int initBodySize = 0, int initStepInterval = 0, int maxX = DISPLAY_WIDTH, int maxY = DISPLAY_HEIGHT);
    ~Snake();

    // Main methods
    void        reset(int initHeadX, int initHeadY, int initBodySize = 0, int initStepInterval = 0);
    void        draw(DisplayGrid& displayGrid);
    void        updateDirection(bool up, bool down, bool left, bool right);

    bool        hasLost();
    bool        hasWon();

    // Setters
    void        updateStepInterval(uint32_t stepInterval);
    uint32_t    getCurrentStepInterval();
    void        useSnack(bool useSnack);
    void        setBodyColor(hsv newColor);
    void        setHeadColor(hsv newColor);

    private:

    void    m_init(int initHeadX, int initHeadY, int initBodySize, int initStepInterval);
    void    m_randomSnack();
    bool    m_updateBody(int direction);
    void    m_move();

    bool     m_hasLost, m_allowSnack;
    uint32_t m_timer, m_currentStepInterval;

    int     m_currentBodySize;
    int     m_maxX, m_maxY;
    int     m_currentDirection;

    Pixel   m_bodyColor;
    Pixel   m_headColor;

    Cube    m_head;
    Cube    m_snack;
    Cube    *m_body;
    int     m_headIndex, m_tailIndex;
};
