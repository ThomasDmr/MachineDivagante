#include "BananaWSLeds.h"
// Data for the banana WS leds : 
byte            drawing_Memory_Banana[10 * 3];        //  3 bytes per LED for RGB
DMAMEM byte     display_Memory_Banana[10 * 12];       // 12 bytes per LED for RGB

BananaLed::BananaLed(int wsLedPin, int dimmer) : m_dimmer(dimmer),
                m_leds(10, display_Memory_Banana, drawing_Memory_Banana, wsLedPin, WS2812_GRB)
{}

void BananaLed::init()
{
    m_leds.begin();
    m_leds.setBrightness(200); // 0=off, 255=brightest
    setAllLedsToSingleValue(0, 0, 0);
    updateLeds();
}

void BananaLed::setAllLedsToSingleValue(int r, int g, int b)
{
    for (int i = 0; i < 10; i++)
    {
        m_leds.setPixel(i, r * m_dimmer / 255, g * m_dimmer / 255, b * m_dimmer / 255);
    }
}

void BananaLed::setSingleLed(int ledNumber, int r, int g, int b)
{
    m_leds.setPixel(ledNumber, r * m_dimmer / 255, g * m_dimmer / 255, b * m_dimmer / 255);
}

void BananaLed::updateLeds()
{
    m_leds.show();
}