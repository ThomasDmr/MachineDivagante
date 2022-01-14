#include "config.h"
#include "globalVariables.h"
#include "gameLevels/harwareTest.h"
#include "gameLevels/introLevel.h"
#include "gameLevels/snakeLevel.h"
#include "gameLevels/simonLevel.h"
#include "gameLevels/guitarLevel.h"
#include "gameLevels/senquencerLevel.h"


// DEBUG
bool snakeLevelActivated = 0;
bool introLevelActivated = 0;
bool simonLevelActivated = 0;
bool guitarLevelActivated = 0;
bool sequencerLevelActivated = 1;

void setup()
{
    // A19 is an unconnected analog pin that allows us to generate different random seeds 
    randomSeed(analogRead(A19));
    
    // Initializing Hardware components
    LedControllers::initLeds();         // initialize all the button leds
    LedControllers::switchOffAllLeds(); 
    ButtonControllers::initButtons();   // initialize all the buttons and joysticks
    bananaLeds.init();                  // initializes the banana ws leds
    initBananaPlugs();                  // initializes the states of the banana plugs

    // initializes the display and sets all the leds to a unique color
    displayGrid.init();
    tmpPixel.setRGB(50, 50, 50);
    displayGrid.setAllToSingleColor(tmpPixel.getRGB());

#ifdef AUDIO_ENABLED
    AudioController::initAudioControllers();
#endif
}

void loop()
{
    // Reading and updating the hardware input and output variables at the beginning of the loop
    //====================================================
    LedControllers::updateLedsStates();
    ButtonControllers::updateButtonsStates();
    joystick1.getLastFallingEdgeState(ButtonControllers::switchRegister.getFallingEdgeState());
    joystick2.getLastFallingEdgeState(ButtonControllers::switchRegister.getFallingEdgeState());   
    greenPlugLow.update();
    redPlugLow.update();
    blackPlugLow.update();
    bluePlugLow.update();
    yellowPlugLow.update();
    //====================================================

    //================= MAIN CODE ========================
    
#ifdef TEST_HARDWARE
    hardwareTest::runFullHardwareTests();
#else
    rgb dark = {0, 0, 0};
    displayGrid.setAllToSingleColor(dark);
    
    if(introLevelActivated)
    {
        introLevel::runIntroLevel();
    }
    else
    {
        introLevel::exitIntroLevel();
    }

    if(guitarLevelActivated)
    {
        GuitarLevel::runGuitarLevel();
    }

    if(sequencerLevelActivated)
    {
        sequencerLevel::runSequencerLevel();
    }
    else
    {
        sequencerLevel::exitSequencerLevel();
    }

    if(simonLevelActivated)
    {
        SimonLevel::runSimonLevel();
    }

    if(snakeLevelActivated)
    {
        SnakeLevel::runSnakeLevel();
    }
    else
    {
        SnakeLevel::exitSnakeLevel();
    }

#endif
    //============== END OF MAIN CODE ====================

    //Update the WS leds at the end of the loop
    //====================================================
    displayGrid.updateDisplay();
    bananaLeds.updateLeds();
    //====================================================
}

void initBananaPlugs()
{
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
}