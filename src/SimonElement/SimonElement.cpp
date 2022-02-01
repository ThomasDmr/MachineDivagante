#include "SimonElement.h"

SimonElement::SimonElement(int imageId, int buttonId, int ledId, int soundFrequency, int soundLength) : 
                m_soundFrequency(soundFrequency), m_soundLength(soundLength), 
                m_ledId(ledId), m_buttonId(buttonId), m_imageId(imageId)   
{
    m_wasPlayed = false;
}

int     SimonElement::getImageId() { return m_imageId; }
int     SimonElement::getFrequency() { return m_soundFrequency; }
int     SimonElement::getSoundLength() { return m_soundLength; }
int     SimonElement::getButtonId() { return m_buttonId; }
int     SimonElement::getLedId() { return m_ledId; }
void    SimonElement::setPlayedStatus(bool yesOrNo){ m_wasPlayed = yesOrNo; }
bool    SimonElement::hasBeenPlayed() { return m_wasPlayed; }
