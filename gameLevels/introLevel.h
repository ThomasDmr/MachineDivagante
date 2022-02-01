#pragma once
#include "../globalVariables.h"
#include "simonLevel.h"

namespace introLevel
{
bool introLevelInitiated = false;
// We create a second snake
Snake localSnake(4, 3, 0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT);

void initIntroLevel()
{   
    // We set the global snake to size 0 so that it only acts as a pointer
    globalSnake.reset(3, 4, 0, 0);
    globalSnake.useSnack(false);
    // We set the global snake size to max size with no timer and no snack for drawing only
    localSnake.reset(6, 4, MAX_SNAKE_SIZE, 0);
    localSnake.useSnack(false);
    introLevelInitiated = true;
}

void exitIntroLevel()
{
    localSnake.reset(6, 3, 0, 0); // free dynamic memory
    
    if(introLevelInitiated)
    {
        // Cutting the sound when leaving the intro level
        AudioController::sine2.amplitude(0);
        AudioController::sine1.amplitude(0);
        AudioController::sine2.frequency(0);
        AudioController::sine1.frequency(0);
    }
    
    introLevelInitiated = false;
}

void runIntroLevel()
{
    if(!introLevelInitiated)
        initIntroLevel();
    
    globalSnake.updateDirection(joystick1.wentUp(), joystick1.wentDown(), joystick1.wentLeft(), joystick1.wentRight());
    localSnake.updateDirection(joystick2.wentUp(), joystick2.wentDown(), joystick2.wentLeft(), joystick2.wentRight());

    hsv snake2HeadColor = {pot1.getValueMapped(0, 359), 100, pot2.getValueMapped(10, 100)};
    localSnake.setHeadColor(snake2HeadColor);

    hsv snake1HeadColor = {pot3.getValueMapped(0, 359), 100, pot4.getValueMapped(10, 100)};
    globalSnake.setHeadColor(snake1HeadColor);
    
    localSnake.draw(displayGrid);
    globalSnake.draw(displayGrid);

    // Show Simon game elements
    SimonLevel::playElementsWhenPressed();

#ifdef AUDIO_ENABLED
    // Play sine waves 
    AudioController::sine2.amplitude(100);
    AudioController::sine1.amplitude(100);
    AudioController::sine2.frequency(pot5.getValueMapped(100, 1500));
    AudioController::sine1.frequency(pot6.getValueMapped(100, 1500));

    // Play sound on joystick movement: 
    if(joystick1.moved())
    {
        AudioController::string1.noteOn(float(random(440) + 20), 0.2);
    }

    if(joystick2.moved())
    {
        AudioController::string1.noteOn(float(random(440) + 20), 0.2);
    }
#endif
}

} // namespace introLevel