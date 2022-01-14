#pragma once

#include "../globalVariables.h"

namespace SnakeLevel
{
const uint32_t  initSnakeStepInterval = 400;
uint32_t        currentStepInterval = initSnakeStepInterval;
bool            snakeLevelInitiated = false;
uint32_t        snakeGameTimer = 0;

void initSnakeLevel()
{
    globalSnake.reset(3, 4, 2, 0);
    snakeLevelInitiated = true;
    globalSnake.useSnack(true);
    
    rgb initColor = {100, 100, 100};
    displayGrid.setAllToSingleColor(initColor);
    displayGrid.maintainCurrentBackground(800);
    snakeGameTimer = 0;
}

void exitSnakeLevel()
{
    snakeLevelInitiated = false;
}

void runSnakeLevel()
{
    if(!snakeLevelInitiated)
        initSnakeLevel();

    if(globalSnake.hasLost())
    {
        if(snakeGameTimer == 0)
        {
            snakeGameTimer = millis();
            displayGrid.setAllThroughTableRGB(definedDisplays::sadFace);
            displayGrid.maintainCurrentBackground(2000);
        }
        else if(millis() - snakeGameTimer > 2000)
        {
            initSnakeLevel();
            currentStepInterval = initSnakeStepInterval;
        }
    }
    else if(globalSnake.hasWon())
    {
        if(snakeGameTimer == 0)
        {
            snakeGameTimer = millis();
            displayGrid.setAllThroughTableRGB(definedDisplays::happyFace);
            displayGrid.maintainCurrentBackground(2000);
        }
        else if(millis() - snakeGameTimer > 2000)
        {
            currentStepInterval = currentStepInterval * 0.66;
            initSnakeLevel();
        }
    }
    else
    {
        if(globalSnake.getCurrentStepInterval() == 0)
        {
            if(joystick1.moved() || joystick2.moved())
            {   
                globalSnake.updateStepInterval(currentStepInterval);
            }
        }

        globalSnake.updateDirection(joystick1.wentUp() || joystick2.wentUp(), joystick1.wentDown() || joystick2.wentDown(), 
                                    joystick1.wentLeft() || joystick2.wentLeft(), joystick1.wentRight() || joystick2.wentRight());
        
        hsv bodyColorFromPot = {pot1.getValueMapped(0, 359), 100, pot2.getValueMapped(10, 100)};
        globalSnake.setBodyColor(bodyColorFromPot);

        hsv headColorFromPot = {pot3.getValueMapped(0, 359), 100, pot4.getValueMapped(10, 100)};
        globalSnake.setHeadColor(headColorFromPot);
        
        globalSnake.draw(displayGrid);

        #ifdef AUDIO_ENABLED
        if(globalSnake.hasCapturedSnack())
        {
            AudioController::triggerSound(200, 800);
        }
        #endif
    }
}

} // namespace Snakelevel