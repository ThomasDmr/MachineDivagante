#pragma once
#include "../globalVariables.h"

void runIntroLevel()
{
    displayGrid.setAllToSingleColor(0, 0, 0);

    cursorP1.setColorThroughPot(pot3.getValue(), pot4.getValue());
    cursorP2.setColorThroughPot(pot1.getValue(), pot2.getValue());
   
    displayGrid.changeSingleValue(cursorP1.getX(), cursorP1.getY(), cursorP1.getColor().getRGB());
    displayGrid.changeSingleValue(cursorP2.getX(), cursorP2.getY(), cursorP2.getColor().getRGB());

}
