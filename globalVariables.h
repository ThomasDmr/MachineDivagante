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
#include "src/SimonGame/SimonGame.h"

Pixel tmpPixel(50, 50, 50);


Joystick joystick1(ADR_J1_UP, ADR_J1_DOWN, ADR_J1_LEFT, ADR_J1_RIGHT);
Joystick joystick2(ADR_J2_UP, ADR_J2_DOWN, ADR_J2_LEFT, ADR_J2_RIGHT);


Potentiometer pot1(PIN_POT1);
Potentiometer pot2(PIN_POT2);
Potentiometer pot3(PIN_POT3);
Potentiometer pot4(PIN_POT4);
Potentiometer pot5(PIN_POT5);
Potentiometer pot6(PIN_POT6);

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
Snake   globalSnake(3, 3, 0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT);

/*
SimonElement simonElementB1(definedDisplays::simonGame[0], 200, 1000);
SimonElement simonElementB2(definedDisplays::simonGame[1], 2000, 2000);
SimonElement simonElementB3(definedDisplays::simonGame[2], 1000, 4000);
SimonElement simonElementB4(definedDisplays::simonGame[3], 200, 400);
SimonElement simonElementB5(definedDisplays::simonGame[4], 500, 1000);
SimonElement simonElementB6(definedDisplays::simonGame[5], 1000, 1000);
SimonElement simonElementBR(definedDisplays::simonGame[6], 1400, 1000);
SimonElement simonElementBL(definedDisplays::simonGame[7], 1200, 1000);
SimonElement simonElementBM(definedDisplays::simonGame[8], 1800, 500);
*/
