#include "config.h"
#include "globalVariables.h"
#include "gameLevels/harwareTest.h"
#include "gameLevels/introLevel.h"
#include "gameLevels/snakeLevel.h"
#include "gameLevels/simonLevel.h"
#include "gameLevels/guitarLevel.h"
#include "gameLevels/senquencerLevel.h"

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
    rgb initRGB = {50, 50, 50};
    displayGrid.setAllToSingleColor(initRGB);

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
    plug1Low.update();
    plug2Low.update();
    plug3Low.update();
    plug4Low.update();
    plug5Low.update();
    //====================================================

    //================= MAIN CODE ========================
    
#ifdef TEST_HARDWARE
    hardwareTest::runFullHardwareTests();
#else
    rgb dark = {0, 0, 0};
    displayGrid.setAllToSingleColor(dark);
     
    if(!plug1Low.isActive() && !plug2Low.isActive() && !plug3Low.isActive() && !plug4Low.isActive() && !plug5Low.isActive())
    {
        introLevel::runIntroLevel();
    }
    else
    {
        introLevel::exitIntroLevel();
    }

    if(plug1Low.isActive())
    {
        GuitarLevel::runGuitarLevel();
    }

    if(plug2Low.isActive())
    {
        sequencerLevel::runSequencerLevel();
    }
    else
    {
        sequencerLevel::exitSequencerLevel();
    }

    if(plug3Low.isActive())
    {
        SimonLevel::runSimonLevel();
    }
    else
    {
        SimonLevel::exitSimonLevel();
    }

    if(plug4Low.isActive())
    {
        SnakeLevel::runSnakeLevel();
    }
    else
    {
        SnakeLevel::exitSnakeLevel();
    }

    if(plug5Low.isActive())
    {
        // video level
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
    plug1Left.init();
    plug2Left.init();
    plug3Left.init();
    plug4Left.init();
    plug5Left.init();
    plug1Low.init();
    plug2Low.init();
    plug3Low.init();
    plug4Low.init();
    plug5Low.init();
}