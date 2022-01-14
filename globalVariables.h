#pragma once

#include "config.h"
#include "src/Joysticks/Joystick.h"
#include "src/Potentiometer/Potentiometer.h"
#include "src/Banana/BananaPlug.h"
#include "include/ledControllers.h"
#include "include/buttonControllers.h"
#include "include/screenPixels.h"
#include "src/WSledDisplay/WSLedDisplay.h"
#include "src/Banana/BananaWSLeds.h"
#include "include/audioControllers.h"
#include "src/Snake/Snake.h"
#include "src/SimonElement/SimonElement.h"

Pixel tmpPixel(50, 50, 50);


Joystick joystick1(ADR_J1_UP, ADR_J1_DOWN, ADR_J1_LEFT, ADR_J1_RIGHT);
Joystick joystick2(ADR_J2_UP, ADR_J2_DOWN, ADR_J2_LEFT, ADR_J2_RIGHT);

// Watch out : all potentiometers have reverted outputs
Potentiometer pot1(PIN_POT1, true);
Potentiometer pot2(PIN_POT2, true);
Potentiometer pot3(PIN_POT3, true);
Potentiometer pot4(PIN_POT4, true);
Potentiometer pot5(PIN_POT5, true);
Potentiometer pot6(PIN_POT6, true);

BananaPlug greenPlugLow(BANANA_1_1, INPUT_PULLUP);
BananaPlug redPlugLow(BANANA_1_2, INPUT_PULLUP);
BananaPlug blackPlugLow(BANANA_1_3, INPUT_PULLUP);
BananaPlug bluePlugLow(BANANA_1_4, INPUT_PULLUP);
BananaPlug yellowPlugLow(BANANA_1_5, INPUT_PULLUP);

BananaPlug greenPlugLeft(BANANA_2_1, OUTPUT);
BananaPlug redPlugLeft(BANANA_2_2, OUTPUT);
BananaPlug blackPlugLeft(BANANA_2_3, OUTPUT);
BananaPlug bluePlugLeft(BANANA_2_4, OUTPUT);
BananaPlug yellowPlugLeft(BANANA_2_5, OUTPUT);

DisplayGrid displayGrid(DISPLAY_WIDTH, DISPLAY_HEIGHT, 10, PIN_WS_SCREEN);

BananaLed   bananaLeds(PIN_WS_BANANA, 5);

// We initialize the Snake globally because it will be used in different modes
Snake   globalSnake(3, 4, 0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT);

const int numberOfSimonElements = 9;
SimonElement simonElements[numberOfSimonElements] = {
    SimonElement(0, (int)ButtonControllers::SW_B1, (int)LedControllers::LED_B1, 200, 1000),
    SimonElement(1, (int)ButtonControllers::SW_B2, (int)LedControllers::LED_B2, 2000, 2000),
    SimonElement(2, (int)ButtonControllers::SW_B3, (int)LedControllers::LED_B3, 1000, 4000),
    SimonElement(3, (int)ButtonControllers::SW_B4, (int)LedControllers::LED_B4, 200, 400),
    SimonElement(4, (int)ButtonControllers::SW_B5, (int)LedControllers::LED_B5, 500, 1000),
    SimonElement(5, (int)ButtonControllers::SW_B6, (int)LedControllers::LED_B6, 1000, 1000),
    SimonElement(6, (int)ButtonControllers::SW_BR, (int)LedControllers::LED_BR, 1400, 1000),
    SimonElement(7, (int)ButtonControllers::SW_BL, (int)LedControllers::LED_BL, 1200, 1000),
    SimonElement(8, (int)ButtonControllers::SW_BM, (int)LedControllers::LED_BM, 1800, 500)
};

