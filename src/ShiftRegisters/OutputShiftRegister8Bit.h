#pragma once
#include "Arduino.h"
#include "../helperFunctions.h"

class OutputShiftRegister8Bit
{
    public: 

    OutputShiftRegister8Bit(int latchPin, int dataPin, int clockPin);

    void    init();
    void    updateState();
    void    changeOneOutput(int outputAdress, bool state);
    void    setAllOutputs(bool out0, bool out1, bool out2, bool out3, bool out4, bool out5, bool out6, bool out7);
    void    setAllOutputs(byte outputState);
    void    clearOutput(); 

    private:

    int     m_latchPin;
    int     m_dataPin;
    int     m_clockPin;
    byte    m_registerState;
    byte    m_previousRegisterState;
};