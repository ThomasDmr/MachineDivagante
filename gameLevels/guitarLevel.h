#pragma once

#include "../globalVariables.h"
#include "../include/audioChords.h"

namespace GuitarLevel
{
    int scale1, scale2;
    float velocity1, velocity2;

    void drawYLineOnDisplay(DisplayGrid& display, int Xcoord, int initY, int endY, int r, int g, int b)
    {
        rgb lineColor = {r, g, b};
        for(int i=initY; i <= endY; i++)
        {
            display.changeSingleValue(Xcoord, i, lineColor);
        }
    }
    
    #ifdef AUDIO_ENABLED
    void playNoteOnJoystick(Joystick& joystick, AudioSynthKarplusStrong& string, int scaleNumber, float velocity)
    {
        if(joystick.wentUp())
        {
            string.noteOn(chordScale[scaleNumber][2], velocity);
        }

        if(joystick.wentDown())
        {
            string.noteOn(chordScale[scaleNumber][3], velocity);
        }

        if(joystick.wentLeft())
        {
            string.noteOn(chordScale[scaleNumber][1], velocity);
        }

        if(joystick.wentRight())
        {
            string.noteOn(chordScale[scaleNumber][0], velocity);
        }
    }
    #endif

    void runGuitarLevel()
    {   
        // Set background color through pot5 and pot6
        rgb backGroundColor = {pot5.getValueMapped(10, 255), pot6.getValueMapped(10, 255), 0};
        displayGrid.setAllToSingleColor(backGroundColor);

        // get scales and velocities  
        scale1 = pot3.getValueMapped(0, 13);
        velocity1 = (float)pot4.getValueMapped(0, 1000) / 1000;
        
        scale2 = pot1.getValueMapped(0, 13);
        velocity2 = (float)pot2.getValueMapped(0, 1000) / 1000;

        // Draw the scale and velocity lines
        // Player 1
        drawYLineOnDisplay(displayGrid, 1, 1, pot4.getValueMapped(0, 6), 255, 125, 0);
        drawYLineOnDisplay(displayGrid, 2, 1, pot3.getValueMapped(0, 6), 125, 125, 125);
        //Player 2
        drawYLineOnDisplay(displayGrid, 8, 1, pot2.getValueMapped(0, 6), 0, 125, 255);
        drawYLineOnDisplay(displayGrid, 7, 1, pot1.getValueMapped(0, 6), 125, 125, 125);
        
        // Play guitar chords
        #ifdef AUDIO_ENABLED
        if(joystick1.moved())
        {
            playNoteOnJoystick(joystick1, AudioController::string1, scale1, velocity1);
        }

        if(joystick2.moved())
        {
            playNoteOnJoystick(joystick2, AudioController::string2, scale2, velocity2);
        }
        #endif
    }
} // namespace GuitarLevel
