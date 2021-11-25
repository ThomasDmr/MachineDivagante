#include "config.h"
#include "src/Joysticks/Joystick.h"
#include "src/Potentiometer/Potentiometer.h"
#include "src/BananaPlug/BananaPlug.h"
#include "src/ledControllers.h"
#include "src/buttonControllers.h"
#include "src/WSledDisplay/WSLedDisplay.h"

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

DisplayGrid displayGrid(DISPLAY_WIDTH, DISPLAY_HEIGHT, 50, PIN_WS_SCREEN);

void setup()
{
    // Initializing Hardware components
    LedControllers::initLeds();
    ButtonControllers::initButtons();

    greenPlugLow.init();
    redPlugLow.init();
    blackPlugLow.init();
    bluePlugLow.init();
    yellowPlugLow.init();
    greenPlugLeft.init();
    redPlugLeft.init();
    blackPlugLeft.init();
    bluePlugLeft.init();
    yellowPlugLeft.init();

    displayGrid.init();
}

void loop()
{
    // Reading and updating the hardware input variables
    LedControllers::updateLedsStates();
    ButtonControllers::updateButtonsStates();

    joystick1.getLastFallingEdgeState(ButtonControllers::switchRegister.getFallingEdgeState());
    joystick2.getLastFallingEdgeState(ButtonControllers::switchRegister.getFallingEdgeState());

    LedControllers::turnOnLed(LedControllers::LED_B6);

    ButtonControllers::wasButtonPressed(ButtonControllers::SW_B4);
    
    greenPlugLow.update();
    redPlugLow.update();
    blackPlugLow.update();
    bluePlugLow.update();
    yellowPlugLow.update();
    displayGrid.updateDisplay();
}
