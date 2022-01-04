#include "Snake.h"

Cube::Cube(int initX, int initY, int maxX, int maxY)
{
    

    m_maxX = maxX;
    m_maxY = maxY;

    m_color.setRGB(initColor);
}

Cube::Cube() : m_x(1), m_y(1)
{
    rgb black = {0, 0, 0};
    m_color.setRGB(black);
    m_maxX = DISPLAY_WIDTH;
    m_maxY = DISPLAY_HEIGHT;
}

void    Cube::setCoordinates(int x, int y)
{
    if(x > m_maxX)
        m_x = m_maxX;
    else if(x<1)
        m_x = 1;
    else 
        m_x = x;
   
    if(y > m_maxY)
        m_y = m_maxY;
    else if(y<1)
        m_y = 1;
    else
        m_y = y;
}

bool    Cube::move(bool up, bool down, bool left, bool right)
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

bool    Cube::moveRight()
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

bool    Cube::moveLeft()
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

bool    Cube::moveUp()
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

bool    Cube::moveDown()
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

int Cube::getX()
{
    return m_x;
}

int Cube::getY()
{
    return m_y;
}

/*
void    Cube::setColor(rgb color)
{
    m_color.setRGB(color);
}
*/

/*
void    Cube::setColorThroughPot(int huePot, int brightnessPot)
{
    hsv hsvTmp;
    hsvTmp.h = map(huePot,0, 1023,0, 359);
    hsvTmp.v = max(map(brightnessPot,0, 1023,0, 100), 10);   
    hsvTmp.s = 100;

    m_color.setHSB(hsvTmp);
}
*/

/*
Pixel     Cube::getColor()
{
    return m_color;
}
*/



/*
void Cube::draw(DisplayGrid& displayGrid)
{
    displayGrid.changeSingleValue(this->getX(), this->getY(), this->getColor().getRGB())
}
*/

Snake::Snake(int initHeadX, int initHeadY, int maxX, int maxY, int initBodySize = 0, int initStepInterval = 0) : 
                m_head(initHeadX, initHeadY, maxX, maxY), m_currentBodySize(initBodySize), m_currentStepInterval(initStepInterval),
                m_maxX(maxX), m_maxY(maxY), m_snack(1, 1, maxX, maxY), m_bodyColor(0, 125, 0), m_headColor(0, 255, 125)
{
    m_hasLost = false;
    m_currentDirection = 4;
    m_timer = 0; 
    // if size = 0, the snake is just a simple pointer
    if(m_currentSize != 0)
    {
        m_body = new Cube[MAX_SNAKE_SIZE];

        for(int i=0; i<m_currentSize; i++)
        {
            // we start by setting all the elements of the body equal to the head
            m_body[i].setCoordinates(m_head.getX(), m_head.getY());
        }

        randomSnack();
    }
}

Snake::~Snake()
{
    delete m_body;
}

bool Snake::hasLost();
bool Snake::hasWon();

void Snake::updateDirection(bool up, bool down, bool left, bool right)
{
    // Direction 1 = up, 2 = down, 3 = left, 4 = right

    m_head.move(up, down, left, right);
    
    if(up)
    {
        if(m_currentDirection == 2)
        {
            m_hasLost = true;
        }
        m_currentDirection = 1;
    }
    else if(down)
    {
        if(m_currentDirection == 1)
        {
            m_hasLost = true;
        }
        m_currentDirection = 2;
    }
    else if(left)
    {
        if(m_currentDirection == 4)
        {
            m_hasLost = true;
        }
        m_currentDirection = 3;
    }
    else if(right)
    {
        if(m_currentDirection == 3)
        {
            m_hasLost = true;
        }
        m_currentDirection = 4;
    }

    // If m_currentStepInterval = 0, we only move the snake on user action
    if(m_currentStepInterval == 0 && (up || down || left || right))
    {
        updateBody(m_currentStepInterval);
    }
}

bool Snake::move()
{
    if(!m_hasLost)
    {
        if(m_timer == 0)
            m_timer = millis();
        
        // if m_currentStepInterval != 0 the snake moves automatically after a time interval
        if(m_currentStepInterval != 0 && millis() - m_timer > m_currentStepInterval)
        {
            m_timer = millis();

            m_hasLost = updateBody(m_currentDirection);
        }
    }

    return m_hasLost;
}

void Snake::reset(int initHeadX, int initHeadY, int initBodySize = 0, int initStepInterval = 0)
{
    delete m_body;

    m_bodyColor.setRGB(0, 125, 0);
    m_headColor.setRGB(0, 255, 125);

    m_currentBodySize = initBodySize;
    m_currentStepInterval = initStepInterval;

    m_hasLost = false;
    m_currentDirection = 4;
    m_timer = 0;

    // if size = 0, the snake is just a simple pointer
    if(m_currentSize != 0)
    {
        m_body = new Cube[MAX_SNAKE_SIZE];

        for(int i=0; i<m_currentSize; i++)
        {
            // we start by setting all the elements of the body equal to the head
            m_body[i].setCoordinates(m_head.getX(), m_head.getY());
        }

        randomSnack();
    }
}

void Snake::draw(DisplayGrid& displayGrid)
{
    if(m_currentBodySize != 0)
    {
        for(int i=0; i < m_currentBodySize; i++)
        {
            displayGrid.changeSingleValue(m_body[i].getX(), m_body[i].getY(), m_bodyColor.getRGB());
        }
    }

    // If StepInterval = 0 we use the snake body for drawing so no snack
    if(m_currentStepInterval != 0)
    {
        rgb snackColor = {random(128, 256) , random(128, 256), random(128, 256)};
        displayGrid.changeSingleValue(m_snack.getX(), m_snack.getY(), snackColor);
    }

    displayGrid.changeSingleValue(m_body.getX(), m_body.getY(), m_bodyColor.getRGB());
}

void Snake::setStepInterval(int stepInterval)
{
    m_currentStepInterval = stepInterval;
}

void Snake::randomSnack()
{
    bool newSnack = false;
    while(!newSnack)
    {
        int x = random(1, m_maxX + 1);
        int y = random(1, m_maxY + 1);
        newSnack = true;
        for(int i = 0; i < m_currentBodySize; i++)
        {
            if(x == m_body[i].getX() && y == m_body[i].getY())
            {
                newSnack == false;
                break;
            }
        }
    }

    m_snack.setCoordinates(x, y);
}

bool Snake::updateBody(int direction)
{
    int newHeadX = 
}