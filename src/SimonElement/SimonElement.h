#pragma once
#include "../../include/helperFunctions.h" 
#include "Arduino.h"

class SimonElement
{
    public:
    SimonElement(int imageId, int buttonId, int ledId, int soundFrequency, int soundLength);
    //bool**  getImage();
    int     getImageId();
    int     getFrequency();
    int     getSoundLength();
    int     getButtonId();
    int     getLedId();

    void    setPlayedStatus(bool yesOrNo);
    bool    hasBeenPlayed();

    //void    printImage();

    private:

    bool    m_wasPlayed;
    //bool    m_displayImage[48][3];
    int     m_imageId;
    int     m_soundFrequency;
    int     m_soundLength;
    int     m_buttonId;
    int     m_ledId;
};