#pragma once
#include "Arduino.h"
#include <Bounce2.h>

class BananaPlug
{
    public:
    BananaPlug(int pin, int type);

    void init();
    void update();
    bool isActive();
    bool wasActivated();

    private:
    int     m_pin;
    int     m_type;
    Bounce  m_bouncer;
};