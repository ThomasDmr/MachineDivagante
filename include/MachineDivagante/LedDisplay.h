// LedDisplay.h
/**
 * © Thomas Demmer - 2021 | www.thomasdmr.com
 */

#pragma once

/**
 * @brief DisplayGrid Contient l'état de chaque led de la matrice d'affichage ainsi que les notes associées et permet de lire ou écrire dedans
 */
class DisplayGrid
{
public:

    /**
     * DisplayGrid : default constructor initializing the attributes
     */
    DisplayGrid(int width, int height);

    void changeSingleValue(int x, int y, HSBValue hsb);

    void changeAllValues(HSBValue hsb);

    HSBValue getSingleValue(int x, int y);

    HSBValue* getAllValues();

    void updateDisplay();

private:

    int convertCoordToAddress(int x, int y);

    int         m_width;
    int         m_height;
    HSBValue*   displayMatrix;
    int*        toneMatrix;
};


/**
 * @brief cell permet de gérer un peu plus proprement les valeurs des cellules de la grille
 */
class cell
{
    public:
    
    HSBValue() : m_h(0), m_s(0), m_b(0) {};
    HSBValue(int hue, int saturation, int brightness) : m_h(hue), m_s(saturation), m_b(brightness) {};

    void set(int hue, int saturation, int brightness);
    void setH(int hue);
    void setS(int saturation);
    void setB(int brightness);

    int H();
    int S();
    int B();

    private:
    int m_h;
    int m_s;
    int m_b;
};