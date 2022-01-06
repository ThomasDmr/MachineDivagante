#include "Snake.h"

//================================================================================
//================================  CLASS CUBE  ==================================
//================================================================================

Cube::Cube(int initX, int initY, rgb initColor, int maxX, int maxY)
{
    m_maxX = maxX;
    m_maxY = maxY;

    m_color.setRGB(initColor);
    setCoordinates(initX, initY);
}

Cube::Cube(int maxX, int maxY) : m_x(1), m_y(1)
{
    rgb black = {0, 0, 0};
    m_color.setRGB(black);
    m_maxX = maxX;
    m_maxY = maxY;
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
    else
        return true;
}

bool    Cube::moveRight()
{
    if(m_x + 1 > m_maxX)
    {
        return true;
    }
    else
    {
        m_x += 1;
        return false;
    }
}

bool    Cube::moveLeft()
{
    if(m_x - 1 <= 0)
    {
        return true;
    }
    else
    {
        m_x -= 1;
        return false;
    }
}

bool    Cube::moveUp()
{
    if(m_y - 1 <= 0)
    {
        return true;
    }
    else
    {
        m_y -= 1;
        return false;
    }
}

bool    Cube::moveDown()
{
    if(m_y + 1 > m_maxY)
    {
        return true;
    }
    else
    {
        m_y += 1;
        return false;
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

void    Cube::setColor(rgb color)
{
    m_color.setRGB(color);
}

void    Cube::setColor(hsv color)
{
    m_color.setHSB(color);
}

Pixel     Cube::getColor()
{
    return m_color;
}

void Cube::draw(DisplayGrid& displayGrid)
{
    displayGrid.changeSingleValue(this->getX(), this->getY(), this->getColor().getRGB());
}

//================================================================================
//================================  CLASS SNAKE  =================================
//================================================================================

Snake::Snake(int initHeadX, int initHeadY, int initBodySize, int initStepInterval, int maxX, int maxY) : 
                m_bodyColor(0, 125, 0), m_headColor(0, 255, 125),
                m_head(maxX, maxY), m_snack(maxX, maxY),
                m_maxX(maxX), m_maxY(maxY)
{
    m_maxX = maxX;
    m_maxY = maxY;
    m_init(initHeadX, initHeadY, initBodySize, initStepInterval);
}

Snake::~Snake()
{
    delete m_body;
}

void Snake::reset(int initHeadX, int initHeadY, int initBodySize, int initStepInterval)
{
    delete m_body;

    m_init(initHeadX, initHeadY, initBodySize, initStepInterval);
}

void Snake::draw(DisplayGrid& displayGrid)
{
    rgb dark = {0, 0, 0};
    displayGrid.setAllToSingleColor(dark);
    // If body Size = 0, we only draw the head to use as a cursor
    if(m_currentBodySize != 0)
    {
        for(int i=m_tailIndex; i < m_tailIndex + m_currentBodySize; i++)
        {
            m_body[i%MAX_SNAKE_SIZE].draw(displayGrid);
        }
    }

    if(m_allowSnack)
        m_snack.draw(displayGrid);

    m_head.draw(displayGrid);
}

void Snake::updateDirection(bool up, bool down, bool left, bool right)
{
    // Direction 1 = up, 2 = down, 3 = left, 4 = right  
    if(up)
    {
        if(m_currentDirection == DOWN)
        {
            m_hasLost = true;
        }
        m_currentDirection = UP;
    }
    else if(down)
    {
        if(m_currentDirection == UP)
        {
            m_hasLost = true;
        }
        m_currentDirection = DOWN;
    }
    else if(left)
    {
        if(m_currentDirection == RIGHT)
        {
            m_hasLost = true;
        }
        m_currentDirection = LEFT;
    }
    else if(right)
    {
        if(m_currentDirection == LEFT)
        {
            m_hasLost = true;
        }
        m_currentDirection = RIGHT;
    }

    // If m_currentStepInterval = 0, we only update the body when there is a user action
    // Otherwise the movement is updated automatically when move() is called
    if(m_currentStepInterval == 0)
    {
        if(up || down || left || right)
        {
            m_hasLost = m_updateBody(m_currentDirection);
        }
    }
    else
    {
        m_move();
    }
}

bool Snake::hasLost()
{
    return m_hasLost;
}

bool Snake::hasWon()
{
    return m_currentBodySize >= MAX_SNAKE_SIZE;
}

void Snake::useSnack(bool useSnack)
{
    if(m_currentBodySize != 0)
        m_allowSnack = useSnack;
}

void Snake::updateStepInterval(uint32_t stepInterval)
{
    m_currentStepInterval = stepInterval;
}

void Snake::setBodyColor(hsv newColor)
{
    for(int i = 0; i < MAX_SNAKE_SIZE; i++)
    {
        m_body[i].setColor(newColor);
    }
}

void Snake::setHeadColor(hsv newColor)
{
    m_head.setColor(newColor);
}

uint32_t    Snake::getCurrentStepInterval()
{
    return m_currentStepInterval;
}

void Snake::m_move()
{
    if(!m_hasLost)
    {
        if(m_timer == 0)
            m_timer = millis();
        
        // if m_currentStepInterval != 0 the snake moves automatically after a time interval
        if(m_currentStepInterval != 0 && millis() - m_timer > m_currentStepInterval)
        {
            m_timer = millis();
            m_hasLost = m_updateBody(m_currentDirection);
        }
    }
}

void Snake::m_init(int initHeadX, int initHeadY, int initBodySize, int initStepInterval )
{
    m_bodyColor.setRGB(0, 125, 0);
    m_headColor.setRGB(0, 255, 125);
    m_currentBodySize = initBodySize;
    m_currentStepInterval = initStepInterval;

    m_hasLost = false;
    m_allowSnack = false;
    m_currentDirection = (initHeadX >= m_maxX / 2) ? LEFT : RIGHT;
    m_timer = 0; 
    m_tailIndex = 0;

    m_head.setColor(m_headColor.getRGB());
    m_head.setCoordinates(initHeadX, initHeadY);
    // if size = 0, the snake is just a simple pointer
    if(m_currentBodySize != 0)
    {
        m_body = new Cube[MAX_SNAKE_SIZE];
        m_allowSnack = true;
        for(int i=0; i<MAX_SNAKE_SIZE; i++)
        {
            // we start by setting all the elements of the body equal to the head
            m_body[i].setCoordinates(m_head.getX(), m_head.getY());
            m_body[i].setColor(m_bodyColor.getRGB());
        }
    }

    m_randomSnack();
}

void Snake::m_randomSnack()
{
    bool newSnack = false;
    int x, y;
    while(!newSnack)
    {
        x = random(1, m_maxX + 1);
        y = random(1, m_maxY + 1);
        newSnack = true;
        for(int i = m_tailIndex; i < m_tailIndex + m_currentBodySize; i++)
        {
            if(x == m_body[i%MAX_SNAKE_SIZE].getX() && y == m_body[i%MAX_SNAKE_SIZE].getY()) 
            {
                newSnack = false;
                break;
            }
        }

        if(x == m_head.getX() && y == m_head.getY())
        {
            newSnack = false;
        }
    }

    m_snack.setCoordinates(x, y);

    rgb snackColor = {255 , random(10, 125), random(10, 125)};
    
    m_snack.setColor(snackColor);
}

bool Snake::m_updateBody(int direction)
{
    bool lost = false;
    // 1 : we convert the current head to a part of the body and increment the head index
    if(m_currentBodySize != 0)
        m_body[(m_tailIndex + m_currentBodySize)%MAX_SNAKE_SIZE].setCoordinates(m_head.getX(), m_head.getY());
 
    // 2 : We move the head
    switch (m_currentDirection)
    {
    case UP:
        lost |= m_head.moveUp();
        break;
    case DOWN:
        lost |= m_head.moveDown();
        break;
    case LEFT:
        lost |= m_head.moveLeft();
        break;
    case RIGHT:
        lost |= m_head.moveRight();
        break;
    default:
        break;
    }

    // 3 : we verify we didn't collide with the body
    if(m_currentBodySize != 0)
    {
        for(int i = m_tailIndex; i < m_tailIndex + m_currentBodySize; i++)
        {
            if(m_body[i%MAX_SNAKE_SIZE].getX() == m_head.getX() && m_body[i%MAX_SNAKE_SIZE].getY() == m_head.getY())
            {
                lost = true;
                break;
            }
        }
    }

    // 3 : we verify we if we catched the snack
    if(m_allowSnack && m_snack.getX() == m_head.getX() && m_snack.getY() == m_head.getY())
    {
        // If we did we generate a new snack and increase the body size
        m_currentBodySize += 1;

        if(m_currentBodySize > MAX_SNAKE_SIZE)
        {
            m_currentBodySize = MAX_SNAKE_SIZE;
            // We increment the tail index because the snake cannot grow more
            m_tailIndex = (m_tailIndex + 1 == MAX_SNAKE_SIZE) ? 0 : m_tailIndex + 1;
        }

        m_randomSnack();
    }
    else
    {
        // If we didn't we remove the tail by incrementing the tail index
        m_tailIndex = (m_tailIndex + 1 == MAX_SNAKE_SIZE) ? 0 : m_tailIndex + 1;
    }

    /*
    String output = "[ ";

    for(int i = 0; i < MAX_SNAKE_SIZE; i++)
    {
        if(m_tailIndex + m_currentBodySize < MAX_SNAKE_SIZE)
        {
            if(i < m_tailIndex)
                output+= "_ ";
            else if(i < m_tailIndex + m_currentBodySize)
                output+= "B ";
            else
                output+= "_ ";
        }
        else
        {
            if(i < (m_tailIndex + m_currentBodySize)%MAX_SNAKE_SIZE)
                output+= "B ";
            else if(i < m_tailIndex)
                output+= "_ ";
            else
                output+= "B ";
        }
    }

    output += "]";
    DEBUG_PRINTLN(output);
    */

    return lost;
}
