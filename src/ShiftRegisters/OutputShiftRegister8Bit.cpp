#include "OutputShiftRegister8Bit.h"

OutputShiftRegister8Bit::OutputShiftRegister8Bit(int latchPin, int dataPin, int clockPin) :
                        m_latchPin(latchPin), m_dataPin(dataPin), m_clockPin(clockPin)
{
    clearOutput();
}

void    OutputShiftRegister8Bit::init()
{
    pinMode(m_latchPin, OUTPUT);
    pinMode(m_dataPin, INPUT);
    pinMode(m_clockPin, OUTPUT);
    digitalWrite(m_latchPin, HIGH);
    digitalWrite(m_clockPin, LOW);
}

void    OutputShiftRegister8Bit::changeOneOutput(int outputAdress, bool state)
{
    m_registerState = helper::writeBit(m_registerState, outputAdress, state);    
}

void    OutputShiftRegister8Bit::setAllOutputs(bool out0, bool out1, bool out2, bool out3, bool out4, bool out5, bool out6, bool out7)
{
    changeOneOutput(0, out0);
    changeOneOutput(1, out1);
    changeOneOutput(2, out2);
    changeOneOutput(3, out3);
    changeOneOutput(4, out4);
    changeOneOutput(5, out5);
    changeOneOutput(6, out6);
    changeOneOutput(7, out7);
}

void    OutputShiftRegister8Bit::setAllOutputs(byte outputState)
{
    m_registerState = outputState;
}

void    OutputShiftRegister8Bit::updateState()
{
    if(m_registerState != m_previousRegisterState)
    {
        // Freeze current outputs
        digitalWriteFast(m_latchPin, LOW);

        // Loop to write each bit value from the serial in line of the SN74HC595 to the output.
        for(int i = 8; i >= 0; i--)
        {
            digitalWriteFast(m_dataPin, helper::getBit(m_registerState, i));
            // Pulse the Clock (rising edge shifts the next bit).
            digitalWriteFast(m_clockPin, HIGH);
            digitalWriteFast(m_clockPin, LOW);
        }

        // Write shift register values to storage register (change the outputs)
        digitalWriteFast(m_latchPin, HIGH);

        m_previousRegisterState = m_registerState;
    }
}   

void    OutputShiftRegister8Bit::clearOutput()
{
    m_registerState = 0;
}