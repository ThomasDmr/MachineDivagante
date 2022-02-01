#pragma once
#include "../../include/helperFunctions.h" 
#include "Arduino.h"

class SimonElement
{
    public:
    SimonElement(int imageId, int buttonId, int ledId, int soundFrequency, int soundLength);

    int     getImageId();
    int     getFrequency();
    int     getSoundLength();
    int     getButtonId();
    int     getLedId();

    void    setPlayedStatus(bool yesOrNo);
    bool    hasBeenPlayed();


    private:

    bool    m_wasPlayed;
    int     m_imageId;
    int     m_soundFrequency;
    int     m_soundLength;
    int     m_buttonId;
    int     m_ledId;
};