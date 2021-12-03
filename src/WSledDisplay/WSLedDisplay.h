// LedDisplay.h
/**
 * © Thomas Demmer - 2021 | www.thomasdmr.com
 */

#pragma once

// PRJC Library to solve audio and WSled conflict 
// https://github.com/PaulStoffregen/WS2812Serial
#include "WS2812Serial.h"
#include "../../include/helperFunctions.h"
#include "../../config.h"

using namespace helper;

/**
 * @brief cell permet de gérer un peu plus proprement les valeurs des cellules de la grille"
 */
class Pixel
{
    public:
    
    Pixel();
    Pixel(int red, int green, int blue);
    Pixel(const rgb& rgb);
    void    setRGB(int red, int green, int blue);
    void    setRGB(const rgb& RGB);
    void    setHSB(int hue, int saturation, int brightness);
    void    setHSB(const hsv& HSV);

    rgb    getRGB();
    hsv    getHSB();

    static hsv   rgb2hsv(rgb in);
    static rgb   hsv2rgb(hsv in); 
    
    private:
    rgb m_rgb;
    hsv m_hsv;
};

/**
 * @brief DisplayGrid Contient l'état de chaque led de la matrice d'affichage et permet de lire ou écrire dedans
 */
class DisplayGrid
{
public:

    /**
     * DisplayGrid : default constructor initializing the attributes
     */
    DisplayGrid(int width, int height, int dimmer, int wsLedPin);

    void    init();

    void    changeSingleValue(int x, int y, hsv hsv);
    void    changeSingleValue(int x, int y, rgb rgb);

    void    setAllToSingleColor(hsv hsv);
    void    setAllToSingleColor(rgb rgb);
    void    setAllToSingleColor(int r, int g, int b);

    void    setAllThroughTableRGB(int colorTable[][3]);
    void    setAllThroughTableRGB(bool colorTable[][3]);

    Pixel   getSingleValue(int x, int y);

    Pixel*  getAllValues();

    void    updateDisplay();

private:

    int     coordToArrayPosition(int x, int y);
    int     arrayPositionToLedAddress(int position);

    int     m_width;
    int     m_height;
    int     m_dimmer;
    Pixel   m_displayMatrix[DISPLAY_WIDTH * DISPLAY_WIDTH];

    WS2812Serial   m_leds;
};