#include "InputShiftRegister.h"

InputShiftRegister::InputShiftRegister(int latchPin, int dataPin, int clockPin, int dataSize):
                        m_latchPin(latchPin), m_dataPin(dataPin), m_clockPin(clockPin), m_dataSize(dataSize)
{
    clearState();
}

void InputShiftRegister::init()
{
    pinMode(m_latchPin, OUTPUT);
    pinMode(m_dataPin, INPUT);
    pinMode(m_clockPin, OUTPUT);
    digitalWrite(m_latchPin, HIGH);
    digitalWrite(m_clockPin, LOW);
}

void     InputShiftRegister::updateState()
{
    int previousState = m_registerState;
    // Load the data of all the parallel lines into the register
    digitalWrite(m_latchPin, LOW);
    digitalWrite(m_latchPin, HIGH);

    // Loop to read each bit value from the serial out line of the SN74HC165N.
    for(int i = m_dataSize; i >=0; i--)
    {
        bool bitVal = digitalReadFast(m_dataPin);
        // Set the corresponding bit.
        m_registerState = helper::writeBit(m_registerState, i, bitVal);

        // Pulse the Clock (rising edge shifts the next bit).
        digitalWriteFast(m_clockPin, HIGH);
        digitalWriteFast(m_clockPin, LOW);
    }

    // a^b donne la différence de bits entre a et b, puis & a donne cette différence uniquement quand a est à 1
    m_fallingEdgeState = (m_registerState ^ previousState) & previousState;
}

int     InputShiftRegister::getCurrentState()
{
    return m_registerState;
}

int     InputShiftRegister::getFallingEdgeState()
{
    return m_fallingEdgeState;
}

void    InputShiftRegister::clearState()
{
    // set all the bits of the register state to 1
    m_registerState = ~(m_registerState & 0);
}