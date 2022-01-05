#pragma once
/*
#include "../../include/helperFunctions.h"
#include "../WSledDisplay/WSLedDisplay.h"

using namespace helper;

const int MAX_SNAKE_SIZE = 12;

class Cube
{
    public:
    Cube(int initX, int initY, int maxX, int maxY);
    Cube();

    bool    move(bool up, bool down, bool left, bool right);
    bool    moveRight();
    bool    moveLeft();
    bool    moveUp();
    bool    moveDown();
    void    setCoordinates(int x, int y);

    int     getX();
    int     getY();
    

    private:
    int     m_x, m_maxX;
    int     m_y, m_maxY;
};


class Snake
{
    public:
    Snake(int initHeadX, int initHeadY, int initSize = 1, int initStepInterval = 0);
    ~Snake();

    bool hasLost();
    bool hasWon();

    void updateDirection(bool up, bool down, bool left, bool right);
    bool move();

    void reset();
    void draw(DisplayGrid& displayGrid);
    void updateStepInterval(int stepInterval);
    void setInitSize(int size);

    void headColorThroughPot(int huePot, int brightnessPot);
    void bodyColorThroughPot(int huePot, int brightnessPot);

    private:

    void    randomSnack();
    bool    updateBody(int direction);

    bool     m_hasLost;
    uint32_t m_timer;

    int     m_currentBodySize;
    int     m_currentStepInterval; 
    int     m_maxX, m_maxY;
    int     m_currentDirection;

    Cube    m_head;
    Cube    m_snack;
    Cube    *m_body;

    Pixel   m_bodyColor;
    Pixel   m_headColor;
};
*/