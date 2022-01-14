#include "WSLedDisplay.h"

byte            drawing_Memory[DISPLAY_WIDTH * DISPLAY_HEIGHT * 3];        //  3 bytes per LED for RGB
DMAMEM byte     display_Memory[DISPLAY_WIDTH * DISPLAY_HEIGHT * 12];       // 12 bytes per LED for RGB

//========================     Class DisplayGrid    ======================
DisplayGrid::DisplayGrid(int width, int height, int dimmer, int wsLedPin) : 
                m_width(width), m_height(height), m_dimmer(dimmer),
                m_leds(width * height, display_Memory, drawing_Memory, wsLedPin, WS2812_GRB)
{
    m_screenTimer = 0;
}

void    DisplayGrid::init()
{
    rgb initColor = {0, 0, 0};
    m_leds.begin();
    m_leds.setBrightness(200); // 0=off, 255=brightest
    setAllToSingleColor(initColor);

    updateDisplay();
}

void    DisplayGrid::changeSingleValue(int x, int y, hsv hsv)
{
    int ledNumber = coordToArrayPosition(x, y);

    if(ledNumber == -1)
    {
        return;
    }
    else
    {
        m_displayMatrix[ledNumber].setHSB(hsv);
    }
}

void    DisplayGrid::changeSingleValue(int x, int y, rgb rgb)
{
    int ledNumber = coordToArrayPosition(x, y);

    if(ledNumber == -1)
    {
        return;
    }
    else
    {
        m_displayMatrix[ledNumber].setRGB(rgb);
    }
}

void    DisplayGrid::maintainCurrentBackground(uint32_t maintainTime)
{
    // If we have a maintain time defined and we aren't already maintaining a screen
    if(maintainTime != 0 && m_screenTimer == 0)
    {
        m_screenTimer = millis();
        m_screenMaintainTime = maintainTime;
    }
}

void    DisplayGrid::setAllToSingleColor(hsv hsv)
{
    if(m_screenTimer == 0 || millis() - m_screenTimer > m_screenMaintainTime)
    {
        m_screenTimer = 0;
        for(int i = 0; i < m_height * m_width; i++)
        {
            m_displayMatrix[i].setHSB(hsv);
        }
    }
}

void    DisplayGrid::setAllToSingleColor(rgb rgb)
{
    if(m_screenTimer == 0 || millis() - m_screenTimer > m_screenMaintainTime)
    {
        m_screenTimer = 0;
        for(int i = 0; i < m_height * m_width; i++)
        {
            m_displayMatrix[i].setRGB(rgb);
        }
    }
}

void    DisplayGrid::setAllToSingleColor(int r, int g, int b)
{
    rgb rgbColor = {r, g, b};

    if(m_screenTimer == 0 || millis() - m_screenTimer > m_screenMaintainTime)
    {
        m_screenTimer = 0;
        for(int i = 0; i < m_height * m_width; i++)
        {
            m_displayMatrix[i].setRGB(rgbColor);
        }
    }
}

void    DisplayGrid::setAllThroughTableRGB(bool colorTable[][3])
{
    if(m_screenTimer == 0 || millis() - m_screenTimer > m_screenMaintainTime)
    {
        m_screenTimer = 0;
        for(int i = 0; i < m_height * m_width; i++)
        {
            m_displayMatrix[i].setRGB(colorTable[i][0] * 255, colorTable[i][1] * 255, colorTable[i][2] * 255);
        }
    }
}

void    DisplayGrid::setAllThroughTableHSV(hsv colorTable[])
{
    if(m_screenTimer == 0 || millis() - m_screenTimer > m_screenMaintainTime)
    {
        m_screenTimer = 0;
        for(int i = 0; i < m_height * m_width; i++)
        {
            m_displayMatrix[i].setHSB(colorTable[i]);
        }
    }
}

Pixel       DisplayGrid::getSingleValue(int x, int y)
{
    int ledNumber = coordToArrayPosition(x, y);

    return m_displayMatrix[ledNumber];
}

Pixel*      DisplayGrid::getAllValues()
{
        return m_displayMatrix;
}

void        DisplayGrid::updateDisplay()
{
    for (int i = 0; i < m_height * m_width; i++)
    {
        m_leds.setPixel(arrayPositionToLedAddress(i), 
                            m_displayMatrix[i].getRGB().r * m_dimmer / 255, 
                            m_displayMatrix[i].getRGB().g * m_dimmer / 255,
                            m_displayMatrix[i].getRGB().b * m_dimmer / 255);
    }
    m_leds.show();
}

int DisplayGrid::coordToArrayPosition(int x, int y)
{
    if(x > m_width || y > m_height || x < 1 || y < 1)
    {
        DEBUG_PRINTLN("Led coordinates out of bound");
        return -1;
    }
    else
    {
        return (y - 1) * m_width + (x - 1); 
    }
}

int DisplayGrid::arrayPositionToLedAddress(int position)
{
    int y = (position / m_width) + 1;
    int x = position%m_width + 1;
    if(y%2 == 0)
        return m_width * (y) - x;
    else
        return (y - 1) * m_width + (x - 1); 
}

//===========================     Class Pixel    =========================
Pixel::Pixel(int red, int green, int blue)
{
    m_rgb.r = red;
    m_rgb.b = green;
    m_rgb.g = blue;

    m_hsv = this->rgb2hsv(m_rgb);
}

Pixel::Pixel()
{
    Pixel(0, 0, 0);
}

Pixel::Pixel(const rgb& rgb)
{
    Pixel(rgb.r, rgb.g, rgb.b);
}

void Pixel::setHSB(int hue, int saturation, int brightness)
{
    if(hue > 360 || hue < 0 || saturation > 100 || saturation < 0 || brightness > 100 || brightness < 0){
        DEBUG_PRINTLN("HSB Values out of range");
        return;
    }

    m_hsv.h = hue;
    m_hsv.s = saturation;
    m_hsv.v = brightness;

    m_rgb = this->hsv2rgb(m_hsv);
}

void    Pixel::setHSB(const hsv& HSV)
{
    this->setHSB(HSV.h, HSV.s, HSV.v);
}

void    Pixel::setRGB(int red, int green, int blue)
{
    if(red > 255 || red < 0 || green > 255 || green < 0 || blue > 255 || blue < 0){
        DEBUG_PRINTLN("RGB Values out of range");
        return;
    }

    m_rgb.r = red;
    m_rgb.g = green;
    m_rgb.b = blue;
    
    m_hsv = this->rgb2hsv(m_rgb);
}

void    Pixel::setRGB(const rgb& RGB)
{
    this->setRGB(RGB.r, RGB.g, RGB.b);
} 

rgb Pixel::getRGB()
{
    return m_rgb;
}

hsv Pixel::getHSB()
{
    return m_hsv;
}

hsv Pixel::rgb2hsv(rgb in)
{
    hsv         out;
    double      h, s, v;
    double      min, max, delta;
    double r = (double)in.r / 255;
    double g = (double)in.g / 255;
    double b = (double)in.b / 255;

    min = r < g ? r : g;
    min = min  < b ? min  : b;

    max = r > g ? r : g;
    max = max  > b ? max  : b;

    v = max;                                // v
    delta = max - min;
    if (delta < 0.00001)
    {
        out.v = v * 100;
        out.s = 0;
        out.h = 0; // undefined, maybe nan?
        return out;
    }
    if( max > 0.0 ) { // NOTE: if Max is == 0, this divide would cause a crash
        s = (delta / max);                  // s
    } else {
        // if max is 0, then r = g = b = 0              
        // s = 0, h is undefined
        out.v = v * 100;
        out.s = 0;
        out.h = 0;                            // its now undefined
        return out;
    }
    if( r >= max )                           // > is bogus, just keeps compilor happy
        h = ( g - b ) / delta;        // between yellow & magenta
    else
    if( g >= max )
        h = 2.0 + ( b - r ) / delta;  // between cyan & yellow
    else
        h = 4.0 + ( r - g ) / delta;  // between magenta & cyan

    h *= 60.0;                              // degrees

    if( h < 0.0 )
        h += 360.0;

    out.h = h;
    out.v = v * 100;
    out.s = s * 100;
    return out;
}


rgb Pixel::hsv2rgb(hsv in)
{
    double      hh, p, q, t, ff;
    long        i;
    rgb         out;

    double v = (double)in.v / 100;
    double s = (double)in.s / 100;
    double h = (double)in.h;


    if(s <= 0.0) {       // < is bogus, just shuts up warnings
        out.r = v * 255;
        out.g = v * 255;
        out.b = v * 255;
        return out;
    }

    hh = h;
    if(hh >= 360.0) hh = 0.0;
    hh /= 60.0;
    i = (long)hh;
    ff = hh - i;
    p = v * (1.0 - s);
    q = v * (1.0 - (s * ff));
    t = v * (1.0 - (s * (1.0 - ff)));

    switch(i) {
    case 0:
        out.r = v * 255;
        out.g = t * 255;
        out.b = p * 255;
        break;
    case 1:
        out.r = q * 255;
        out.g = v * 255;
        out.b = p * 255;
        break;
    case 2:
        out.r = p * 255;
        out.g = v * 255;
        out.b = t * 255;
        break;

    case 3:
        out.r = p * 255;
        out.g = q * 255;
        out.b = v * 255;
        break;
    case 4:
        out.r = t * 255;
        out.g = p * 255;
        out.b = v * 255;
        break;
    case 5:
    default:
        out.r = v * 255;
        out.g = p * 255;
        out.b = q * 255;
        break;
    }
    return out;     
}