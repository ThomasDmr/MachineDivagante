#pragma once

class Potentiometer
{
    public:
    Potentiometer(int analogPin, bool reversed = false) : m_analogPin(analogPin), m_reversed(reversed) {};

    int getValue()
    {
        return (m_reversed) ? 1023 - analogRead(m_analogPin) : analogRead(m_analogPin);
    };

    int getValueMapped(int min, int max)
    {
        return map(getValue(), 0, 1023, min, max);
    };

    private:
    int     m_analogPin;
    bool    m_reversed;
};