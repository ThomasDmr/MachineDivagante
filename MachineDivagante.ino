#include "config.h"
#include "globalVariables.h"
#include "gameLevels/introLevel.h"

void setup()
{
    // A19 is an unconnected analog pin that allows us to generate different random seeds 
    randomSeed(analogRead(A19));
    
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

    tmpPixel.setRGB(0, 0, 0);
    displayGrid.setAllToSingleColor(tmpPixel.getRGB());
    //displayGrid.setAllThroughTableRGB(definedDisplays::simonGame[0]);
}

void loop()
{
    uint32_t timer = micros(); //DEBUG
    // Reading and updating the hardware input variables
    LedControllers::updateLedsStates();
    ButtonControllers::updateButtonsStates();
    joystick1.getLastFallingEdgeState(ButtonControllers::switchRegister.getFallingEdgeState());
    joystick2.getLastFallingEdgeState(ButtonControllers::switchRegister.getFallingEdgeState());   
    greenPlugLow.update();
    redPlugLow.update();
    blackPlugLow.update();
    bluePlugLow.update();
    yellowPlugLow.update();

    Serial.println("1\t" + String(micros() - timer)); // DEBUG
    timer = micros(); //DEBUG
    
    runIntroLevel();

    Serial.println("2\t" + String(micros() - timer)); //DEBUG
    timer = micros(); //DEBUG
    // update the display
    displayGrid.updateDisplay();
    Serial.println("3\t" + String(micros() - timer)); //DEBUG
    timer = micros(); //DEBUG
}
