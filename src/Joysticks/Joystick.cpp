#include "Joystick.h"

Joystick::Joystick(int upAddress, int downAddress, int leftAddress, int rightAddress):
                    m_upAddress(upAddress), m_downAddress(downAddress), m_leftAddress(leftAddress), m_rightAddress(rightAddress), m_fallingEdgeState(0)
{}

bool Joystick::wentUp()
{
    return helper::getBit(m_fallingEdgeState, m_upAddress);
}

bool Joystick::wentDown()
{
    return helper::getBit(m_fallingEdgeState, m_downAddress);
}

bool Joystick::wentLeft()
{
    return helper::getBit(m_fallingEdgeState, m_leftAddress);
}

bool Joystick::wentRight()
{
    return helper::getBit(m_fallingEdgeState, m_rightAddress);
}

void Joystick::getLastFallingEdgeState(int fallingEdgeState)
{
    m_fallingEdgeState = fallingEdgeState;
}