#pragma once

#include "../globalVariables.h"

using ButtonControllers::Button;
using LedControllers::LED;
using definedDisplays::simonGame;

namespace SimonLevel
{
const int   maxSequenceLength = 7;
const int   initialSequenceLength = 2;
const int   sequenceDisplayTime = 2000; // how long each element of the sequence is displayed
int         currentSequenceLength = initialSequenceLength;
int         gameSequence[maxSequenceLength] = {0};
bool        startIntroSequence = true;
bool        startSequenceDisplay = true;
bool        newSequence = true;

void generateNewSequence(int sequenceLength)
{
    for(int i=0; i<sequenceLength; i++)
    {
        gameSequence[i] = random(100) % 9;
    }
    newSequence = false;
}

int getLastElementSelected()
{
    for(int i=0; i<numberOfSimonElements; i++)
    {
        if(ButtonControllers::wasButtonPressed((Button)simonElements[i].getButtonId()))
        {
            return i;
        } 
    }

    return -1;
}

void playElementsWhenPressed()
{
    for(int i=0; i<numberOfSimonElements; i++)
    {
        if(ButtonControllers::isButtonActive((Button)simonElements[i].getButtonId()))
        {
            LedControllers::turnOnLed((LED)simonElements[i].getLedId());
            displayGrid.setAllThroughTableRGB(simonGame[simonElements[i].getImageId()]);
            displayGrid.maintainCurrentBackground(250);

            if(!simonElements[i].hasBeenPlayed())
            {
                #ifdef AUDIO_ENABLED
                AudioController::triggerSound(simonElements[i].getFrequency(), simonElements[i].getSoundLength());
                #endif
                simonElements[i].setPlayedStatus(true);
            }
        }
        else
        {
            simonElements[i].setPlayedStatus(false);
            LedControllers::turnOffLed((LED)simonElements[i].getLedId());
        }
    }
}

void introSequence()
{
    static int introIndex = 0;

    if(ButtonControllers::wasButtonPressed((Button)simonElements[introIndex].getButtonId()))
    {
        simonElements[introIndex].setPlayedStatus(false);
        LedControllers::turnOffLed((LED)simonElements[introIndex].getLedId());
        introIndex++;

        if(introIndex >= numberOfSimonElements)
        {
            startIntroSequence = false;
            introIndex = 0;
        }
    }
    else
    {
        LedControllers::turnOnLed((LED)simonElements[introIndex].getLedId());
        displayGrid.setAllThroughTableRGB(simonGame[simonElements[introIndex].getImageId()]);

        if(!simonElements[introIndex].hasBeenPlayed())
        {
            #ifdef AUDIO_ENABLED
            AudioController::triggerSound(simonElements[introIndex].getFrequency(), simonElements[introIndex].getSoundLength());
            #endif
            simonElements[introIndex].setPlayedStatus(true);
        }
    }
}

void playNewGameSequence()
{
    static int sequenceIndex = 0;
    static uint32_t timer = 0;
    
    if(newSequence)
    {
        sequenceIndex = 0;
        generateNewSequence(currentSequenceLength);
        timer = 0;
    }

    if(timer == 0)
    {
        timer = millis();
    }
    else if(millis() - timer < 250)
    {
        // First we switch off everything
        LedControllers::switchOffAllLeds();
        rgb black = {0, 0, 0};
        displayGrid.setAllToSingleColor(black);
    }
    else if(millis() - timer < sequenceDisplayTime)
    {
        // Then we show the current sequence
        int idxToDisplay = gameSequence[sequenceIndex];

        LedControllers::turnOnLed((LED)simonElements[idxToDisplay].getLedId());
        displayGrid.setAllThroughTableRGB(simonGame[simonElements[idxToDisplay].getImageId()]);

        if(!simonElements[idxToDisplay].hasBeenPlayed())
        {
            #ifdef AUDIO_ENABLED
            AudioController::triggerSound(simonElements[idxToDisplay].getFrequency(), simonElements[idxToDisplay].getSoundLength());
            #endif
            simonElements[idxToDisplay].setPlayedStatus(true);
        }
    }
    else
    {
        int idxToDisplay = gameSequence[sequenceIndex];
        simonElements[idxToDisplay].setPlayedStatus(false);
        LedControllers::turnOffLed((LED)simonElements[idxToDisplay].getLedId());
        timer = 0;
        sequenceIndex++;

        if(sequenceIndex == currentSequenceLength)
        {
            sequenceIndex = 0;
            startSequenceDisplay = false;
        }
    }    
}

int playGame()
{
    static int sequenceReplayIndex = 0;
    
    int lastSelected = getLastElementSelected();

    if(lastSelected != -1)
    {
        if(lastSelected == gameSequence[sequenceReplayIndex])
        {
            // Good Answer
            sequenceReplayIndex++;
        }
        else
        {
            // Bad answer
            sequenceReplayIndex = 0;
            return -1;
        }

        if(sequenceReplayIndex == currentSequenceLength)
        {
            sequenceReplayIndex = 0;
            return 1;
        }
    }
    return 0;
}

void blinkAllButtons(bool turnAllOff)
{
    static uint32_t timer = 0;
    static bool val = 0;

    if(turnAllOff)
    {
        val = 0; 
        timer = 0;
        for(int i=0; i<numberOfSimonElements; i++)
        {
            LedControllers::setLedState((LED)simonElements[i].getLedId(), 0);
        }
    }
    else
    {
        if(millis() - timer > 50)
        {
            timer = millis();
            val = !val;

            for(int i=0; i<numberOfSimonElements; i++)
            {
                LedControllers::setLedState((LED)simonElements[i].getLedId(), val);
            }
        }
    }
}

void runSimonLevel()
{
    static bool hasWon = false;
    static bool hasLost = false;
    static uint32_t timer = 0;
    static int blinkCounter = 0;

    if(startIntroSequence)
    {
        introSequence();
    }
    else if(startSequenceDisplay)
    {
        hasWon = false;
        hasLost = false;
        timer = 0;
        blinkCounter = 0;
        playNewGameSequence();
    }
    else
    {
        playElementsWhenPressed();

        if(hasWon)
        {
            blinkAllButtons(false);
            if(timer == 0)
            {
                DEBUG_PRINTLN("WON");
                timer = millis();
            }
            else if(blinkCounter == 8)
            {
                // Start a new sequence
                blinkAllButtons(true);
                blinkCounter = 0;
                timer = 0;
                currentSequenceLength++;
                startIntroSequence = false;
                startSequenceDisplay = true;
                newSequence = true;
            }
            else if(millis() - timer > 250)
            {
                if(blinkCounter%2 == 0)
                {
                    displayGrid.setAllThroughTableRGB(definedDisplays::happyFace);
                    displayGrid.maintainCurrentBackground(250);
                }
                blinkCounter++;
                timer = millis();
            }
        }
        else if(hasLost)
        {
            if(timer == 0)
            {
                DEBUG_PRINTLN("LOST");
                timer = millis();
            }
            else if(blinkCounter == 8)
            {
                // Start a new sequence
                blinkCounter = 0;
                timer = 0;
                currentSequenceLength = initialSequenceLength;
                startIntroSequence = true;
                startSequenceDisplay = true;
                newSequence = true;
            }
            else if(millis() - timer > 250)
            {
                if(blinkCounter%2 == 0)
                {
                    displayGrid.setAllThroughTableRGB(definedDisplays::sadFace);
                    displayGrid.maintainCurrentBackground(250);
                }
                blinkCounter++;
                timer = millis();
            }
        }
        else
        {
            int gameStatus = playGame();

            if(gameStatus == 1)
            {
                // The sequence is won !
                hasWon = true;
            }
            else if(gameStatus == -1)
            {
                // The sequence is lost ! 
                hasLost = true;
            }
        }
    }
}
} // namespace SimonLevel
