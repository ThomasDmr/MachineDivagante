#include "BananaPlug.h"

BananaPlug::BananaPlug(int pin, int type) : m_pin(pin), m_type(type), m_bouncer()
{}

void BananaPlug::init()
{
    // Define pin as output to simulate connection to GND
    if(m_type == OUTPUT)
    {
        pinMode(m_pin, OUTPUT);
        digitalWrite(m_pin, LOW);
    }
    else
    {
        pinMode(m_pin, INPUT_PULLUP);
        m_bouncer.attach(m_pin);
        m_bouncer.interval(5);
    }
}

void BananaPlug::update()
{
    if(m_type != OUTPUT)
    {
        m_bouncer.update();
    }
}

bool BananaPlug::isActive()
{
    if(m_type == OUTPUT)
    {
        return false;
    }
    else
    {
        return (m_bouncer.read() == 0);
    }
}

bool BananaPlug::wasActivated()
{
    if(m_type == OUTPUT)
    {
        return false;
    }
    else
    {
        return m_bouncer.fell();
    }
}
