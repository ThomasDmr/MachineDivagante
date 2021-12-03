#include "Snake.h"

Cursor::Cursor(int initX, int initY, rgb initColor, int maxX, int maxY)
{
    m_x = (initX < maxX) ? initX : maxX;
    m_y = (initY < maxY) ? initY : maxY;

    m_maxX = maxX;
    m_maxY = maxY;

    m_color.setRGB(initColor);
}

Cursor::Cursor() : m_x(1), m_y(1)
{
    rgb black = {0, 0, 0};
    m_color.setRGB(black);
    m_maxX = DISPLAY_WIDTH;
    m_maxY = DISPLAY_HEIGHT;
}

bool    Cursor::move(bool up, bool down, bool left, bool right)
{
    if(up)
        return moveUp();
    else if(down)
        return moveDown();
    else if(left)
        return moveLeft();
    else if(right)
        return moveRight();
}

bool    Cursor::moveRight()
{
    if(m_x + 1 > m_maxX)
    {
        return false;
    }
    else
    {
        m_x += 1;
        return true;
    }
}

bool    Cursor::moveLeft()
{
    if(m_x - 1 < 0)
    {
        return false;
    }
    else
    {
        m_x -= 1;
        return true;
    }
}

bool    Cursor::moveUp()
{
    if(m_y - 1 < 0)
    {
        return false;
    }
    else
    {
        m_y -= 1;
        return true;
    }
}

bool    Cursor::moveDown()
{
    if(m_y + 1 > m_maxY)
    {
        return false;
    }
    else
    {
        m_y += 1;
        return true;
    }
}

void    Cursor::setColor(rgb color)
{
    m_color.setRGB(color);
}

void    Cursor::setColorThroughPot(int huePot, int brightnessPot)
{
    hsv hsvTmp;
    hsvTmp.h = map(huePot,0, 1023,0, 359);
    hsvTmp.v = max(map(brightnessPot,0, 1023,0, 100), 10);   
    hsvTmp.s = 100;

    m_color.setHSB(hsvTmp);
}

Pixel     Cursor::getColor()
{
    return m_color;
}

int Cursor::getX()
{
    return m_x;
}

int Cursor::getY()
{
    return m_y;
}

void Cursor::draw(DisplayGrid& displayGrid)
{
    displayGrid.changeSingleValue(this->getX(), this->getY(), this->getColor().getRGB())
}

Snake::Snake(int initSize, int initSpeed, Cursor& initHead) : 
                m_currentSize(initSize), m_currentSpeed(initSpeed), m_head(initHead), m_snack(1,1)
{
    m_body = new Cursor[MAX_SNAKE_SIZE];
}

Snake::~Snake()
{
    delete m_body;
}

bool Snake::hasLost();
bool Snake::hasWon();

bool Snake::move(bool up, bool down, bool left, bool right);

void Snake::reset();
void Snake::draw(DisplayGrid& displayGrid);
void Snake::setSpeed(int speed);
void Snake::setInitSize(int size);

void Snake::randomSnack();
void Snake::updateBody();