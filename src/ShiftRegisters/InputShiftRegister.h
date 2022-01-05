#pragma once
#include "Arduino.h"
#include "../../include/helperFunctions.h"

class InputShiftRegister
{
    public: 

    InputShiftRegister(int latchPin, int dataPin, int clockPin, int numberOfRegisters = 2);

    void    init();
    void    updateState();
    int     getCurrentState();
    int     getFallingEdgeState();
    void    clearState(); 

    private:

    int m_latchPin;
    int m_dataPin;
    int m_clockPin;
    int m_numberOfRegisters;
    int m_registerState;
    int m_fallingEdgeState;
};