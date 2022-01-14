#include "SimonElement.h"

SimonElement::SimonElement(int imageId, int buttonId, int ledId, int soundFrequency, int soundLength) : 
                m_soundFrequency(soundFrequency), m_soundLength(soundLength), 
                m_ledId(ledId), m_buttonId(buttonId), m_imageId(imageId)   
{
    m_wasPlayed = false;
}

//bool**  SimonElement::getImage() { return m_displayImage; }
int     SimonElement::getImageId() { return m_imageId; }
int     SimonElement::getFrequency() { return m_soundFrequency; }
int     SimonElement::getSoundLength() { return m_soundLength; }
int     SimonElement::getButtonId() { return m_buttonId; }
int     SimonElement::getLedId() { return m_ledId; }
void    SimonElement::setPlayedStatus(bool yesOrNo){ m_wasPlayed = yesOrNo; }
bool    SimonElement::hasBeenPlayed() { return m_wasPlayed; }

/*
void    SimonElement::printImage()
{
    String output = "";
    for(int i=0; i<48; i++)
    {
        bool on = false;
        for (int j=0; j<3; j++)
        {
            if(m_displayImage[i][j] != 0)
                on = true;
        }
        output += String(on) + " ";
        if(i%8 == 0)
        {
            DEBUG_PRINTLN(output);
            output = "";
        }
    }
    DEBUG_PRINTLN(output);
}
*/