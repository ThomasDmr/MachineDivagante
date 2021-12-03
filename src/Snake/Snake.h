#pragma once

#include "../../include/helperFunctions.h"
#include "../WSledDisplay/WSLedDisplay.h"

using namespace helper;

const int MAX_SNAKE_SIZE = 12;

class Cursor
{
    public:
    Cursor(int initX, int initY, rgb initColor, int maxX, int maxY);
    Cursor();

    bool    move(bool up, bool down, bool left, bool right);
    bool    moveRight();
    bool    moveLeft();
    bool    moveUp();
    bool    moveDown();

    void    setColor(rgb color);
    void    setColorThroughPot(int huePot, int brightnessPot);
    Pixel   getColor();
    int     getX();
    int     getY();

    void    draw(DisplayGrid& displayGrid)

    private:
    int     m_x, m_maxX;
    int     m_y, m_maxY;
    Pixel   m_color;
};


class Snake
{
    public:
    Snake(int initSize, int initSpeed, Cursor& initHead);
    ~Snake();

    bool hasLost();
    bool hasWon();

    bool move(bool up, bool down, bool left, bool right);

    void reset();
    void draw(DisplayGrid& displayGrid);
    void setSpeed(int speed);
    void setInitSize(int size);

    private:

    void    randomSnack();
    void    updateBody();
    
    int     m_currentSize;
    int     m_currentSpeed; 
    Cursor  *m_head;
    Cursor  m_snack;
    Cursor  *m_body;
};