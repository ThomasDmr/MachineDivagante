#pragma once

class SimonElement
{
    public:
    SimonElement(bool* displayImage, int soundFrequency, int soundLength) : 
                m_displayImage(displayImage), m_soundFrequency(soundFrequency), m_soundLength(soundLength) {};

    bool*   getImage() { return m_displayImage; };
    int     getFrequency() { return m_soundFrequency; };
    int     getSoundLength() { return m_soundLength; };

    private:
    bool*   m_displayImage;
    int     m_soundFrequency;
    int     m_soundLength;
};