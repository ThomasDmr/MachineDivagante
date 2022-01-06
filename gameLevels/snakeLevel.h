#pragma once

#include "../globalVariables.h"

namespace SnakeLevel
{
const int initSnakeStepInterval = 400;
bool snakeLevelInitiated = false;

void initSnakeLevel(uint32_t stepInterval)
{
    globalSnake.reset(3, 3, 2, stepInterval);
    snakeLevelInitiated = true;
    globalSnake.useSnack(true);
}

void exitSnakeLevel()
{
    snakeLevelInitiated = false;
}

void runSnakeLevel()
{
    if(!snakeLevelInitiated)
        initSnakeLevel(initSnakeStepInterval);

    if(globalSnake.hasLost())
    {
        displayGrid.setAllThroughTableRGB(definedDisplays::sadFace);
        displayGrid.updateDisplay();
        delay(2000);
        initSnakeLevel(initSnakeStepInterval);
    }
    else if(globalSnake.hasWon())
    {
        displayGrid.setAllThroughTableRGB(definedDisplays::happyFace);
        displayGrid.updateDisplay();
        delay(2000);
        uint32_t newStepInterval = globalSnake.getCurrentStepInterval() * 0.66;
        initSnakeLevel(newStepInterval);
    }
    else
    {
        globalSnake.updateDirection(joystick1.wentUp() || joystick2.wentUp(), joystick1.wentDown() || joystick2.wentDown(), 
                                    joystick1.wentLeft() || joystick2.wentLeft(), joystick1.wentRight() || joystick2.wentRight());
        
        hsv bodyColorFromPot = {pot1.getValueMapped(0, 359), 100, pot2.getValueMapped(10, 100)};
        globalSnake.setBodyColor(bodyColorFromPot);

        hsv headColorFromPot = {pot3.getValueMapped(0, 359), 100, pot4.getValueMapped(10, 100)};
        globalSnake.setHeadColor(headColorFromPot);
        
        globalSnake.draw(displayGrid);
    }
}

} // namespace Snakelevel