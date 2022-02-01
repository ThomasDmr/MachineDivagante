#pragma once
#include "../globalVariables.h"
#include "guitarLevel.h"

using namespace ButtonControllers;

namespace sequencerLevel
{

// sequencerGrid is a table of hsv colors that stores the "notes"
hsv sequencerGrid[DISPLAY_WIDTH * DISPLAY_HEIGHT]; 

// We use 2 Cube object that will act as cursors for both players
Cube playerCursor1(DISPLAY_WIDTH, DISPLAY_HEIGHT);
Cube playerCursor2(DISPLAY_WIDTH, DISPLAY_HEIGHT);

bool sequencerInitialized = false;

const int maxFreq = 3000;
const int minFreq = 75;
const int maxAmpli = 1400;
const int minAmpli = 600;

void initSequencer()
{
    playerCursor1.setCoordinates(4, 3);
    playerCursor2.setCoordinates(6, 3);

    // Make the cursors blink  
    playerCursor1.blink(1000);
    playerCursor2.blink(1000);
}

void generateRandomNoteMapping(int fillRatePercentage)
{
    for (int i = 0; i < DISPLAY_WIDTH * DISPLAY_HEIGHT; i++)
    {
        int acceptanceValue = random(100);
        if(acceptanceValue < fillRatePercentage)
        {
            sequencerGrid[i].h = random(0, 359);
            sequencerGrid[i].v = random(10, 100);
            sequencerGrid[i].s = 100;
        }
        else
        {
            sequencerGrid[i].h = 0;
            sequencerGrid[i].v = 0;
            sequencerGrid[i].s = 0;
        }
    }
}

void playSineNote(float frequency, float amplitude, int player)
{
#ifdef AUDIO_ENABLED
    if(player == 1)
    {
        AudioController::sine1.frequency(frequency);
        AudioController::sine1.amplitude(amplitude);
    }
    else if(player == 2)
    {
        AudioController::sine2.frequency(frequency);
        AudioController::sine2.amplitude(amplitude);
    }
    else if(player == 3)
    {
        AudioController::sine3.frequency(frequency);
        AudioController::sine3.amplitude(amplitude);
    }
    else if(player == 4)
    {
        AudioController::sine4.frequency(frequency);
        AudioController::sine4.amplitude(amplitude);
    }
    else if(player == 5)
    {
        AudioController::sine5.frequency(frequency);
        AudioController::sine5.amplitude(amplitude);
    }
    else if(player == 6)
    {
        AudioController::sine6.frequency(frequency);
        AudioController::sine6.amplitude(amplitude);
    }
#endif
    return;
}

void turnOffPlayers()
{
    for(int i=0; i<6; i++)
    {
        playSineNote(0, 0 , i + 1);
    }
}

void exitSequencerLevel()
{
    if(sequencerInitialized)
    {
        // Turn off playing notes when leaving the sequencer mode
        generateRandomNoteMapping(0);
        turnOffPlayers();
    }
    sequencerInitialized = false;
}

void addCursorToSequencer(Cube& cursor)
{
    int gridPosition = (cursor.getX() - 1) + (cursor.getY() - 1) * DISPLAY_WIDTH;
    sequencerGrid[gridPosition].h = cursor.getColor().getHSB().h;
    sequencerGrid[gridPosition].s = cursor.getColor().getHSB().s;
    sequencerGrid[gridPosition].v = cursor.getColor().getHSB().v;
}

void runSequencerReader(uint32_t reader1Interval, uint32_t reader2Interval)
{
    static int reader1Index = 0;
    static uint32_t reader1Timer = 0;

    static int reader2Index = 0;
    static uint32_t reader2Timer = 0;

    // Look for the notes of the first reader
    if(millis() - reader1Timer > reader1Interval)
    {
        reader1Index = (reader1Index + 1)%DISPLAY_WIDTH;
        reader1Timer = millis();
        for(int i = 0; i < DISPLAY_HEIGHT / 2; i++)
        {
            // We check the 3 values corresponding to the index on the lower half of the screen
            int noteIndex = i * DISPLAY_WIDTH + reader1Index;
            if(sequencerGrid[noteIndex].s != 0)
            {
                // Convert hue to frequency
                float frequency = map(sequencerGrid[noteIndex].h, 0, 359, minFreq, maxFreq);
                // Convert brightness to amplitude
                float amplitude = (float)map(sequencerGrid[noteIndex].v, 10, 100, minAmpli, maxAmpli) / maxAmpli;

                playSineNote(frequency, amplitude, i + 1);
            }
        }
    }

    // Look for the notes of the second bar
    if(millis() - reader2Timer > reader2Interval)
    {
        reader2Index = (reader2Index + 1)%DISPLAY_WIDTH;
        reader2Timer = millis();
        for(int i = 0; i < DISPLAY_HEIGHT / 2; i++)
        {
            // We check the 3 values corresponding to the index on the upper half of the screen
            int noteIndex = (i + DISPLAY_HEIGHT / 2) * DISPLAY_WIDTH + reader2Index;
            if(sequencerGrid[noteIndex].s != 0)
            {
                // Convert hue to frequency
                float frequency = map(sequencerGrid[noteIndex].h, 0, 359, minFreq, maxFreq);
                // Convert brightness to amplitude
                float amplitude = (float)map(sequencerGrid[noteIndex].v, 10, 100, minAmpli, maxAmpli) / maxAmpli;

                playSineNote(frequency, amplitude, i + DISPLAY_HEIGHT / 2 + 1);
            }
        }
    }

    GuitarLevel::drawYLineOnDisplay(displayGrid, reader1Index + 1, 1, 3, 255, 0, 0);
    GuitarLevel::drawYLineOnDisplay(displayGrid, reader2Index + 1, 4, 6, 0, 0, 255);
}

void runSequencerLevel()
{   
    static bool newRandomNotes = false;

    if(!sequencerInitialized)
    {
        sequencerInitialized = true;
        initSequencer();
        newRandomNotes = true;
    }

    if(newRandomNotes)
    {
        generateRandomNoteMapping(30);
        newRandomNotes = false;
    }

    // Button main is pressed
    if(wasButtonPressed(SW_BM))
    {
        newRandomNotes = true;
    }

    // Button 1 to 6 are pressed
    if(wasButtonPressed(SW_B1) || wasButtonPressed(SW_B2) || wasButtonPressed(SW_B3)
        || wasButtonPressed(SW_B4) || wasButtonPressed(SW_B5) || wasButtonPressed(SW_B6))
    {
        generateRandomNoteMapping(0);
        turnOffPlayers();
    }

    // Button left button is pressed
    if(wasButtonPressed(SW_BL))
    {
        addCursorToSequencer(playerCursor1);
    }

    // Button right button is pressed
    if(wasButtonPressed(SW_BR))
    {
        addCursorToSequencer(playerCursor2);
    }

    // Manage the player cursors
    playerCursor1.move(joystick1.wentUp(), joystick1.wentDown(), joystick1.wentLeft(), joystick1.wentRight());
    hsv p1Color = {pot3.getValueMapped(0, 359), 100, pot4.getValueMapped(10, 100)};
    playerCursor1.setColor(p1Color);
    
    playerCursor2.move(joystick2.wentUp(), joystick2.wentDown(), joystick2.wentLeft(), joystick2.wentRight());
    hsv p2Color = {pot1.getValueMapped(0, 359), 100, pot2.getValueMapped(10, 100)};
    playerCursor2.setColor(p2Color);

    // draw all the elements (first the grid then the cursors !)
    displayGrid.setAllThroughTableHSV(sequencerGrid);
    playerCursor1.draw(displayGrid);
    playerCursor2.draw(displayGrid);

    // Finally run the sequencer
    // The potentiometer values are inverted for better user experience
    int reader1Speed = pot5.getValueMapped(800, 20);
    int reader2Speed = pot6.getValueMapped(800, 20);
    runSequencerReader(reader1Speed, reader2Speed);
}

} // namespace sequencerLevel
