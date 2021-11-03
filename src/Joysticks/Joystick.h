#pragma once
#include "../helperFunctions.h"

class Joystick
{
    public:
    Joystick(int upAddress, int downAddress, int leftAddress, int rightAddress);

    bool wentUp();
    bool wentDown();
    bool wentLeft();
    bool wentRight();

    void getLastFallingEdgeState(int fallingEdgeState);

    private:
    int m_upAddress;
    int m_downAddress;
    int m_leftAddress;
    int m_rightAddress;
    int m_fallingEdgeState;
};