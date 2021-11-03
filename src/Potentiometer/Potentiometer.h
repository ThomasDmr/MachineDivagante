#pragma once

class Potentiometer
{
    public:
    Potentiometer(int analogPin) : m_analogPin(analogPin) {};

    int getValue()
    {
        return analogRead(m_analogPin);
    };

    int getValueMapped(int min, int max)
    {
        return map(analogRead(m_analogPin), 0, 1023, min, max);
    };

    private:
    int m_analogPin;
};