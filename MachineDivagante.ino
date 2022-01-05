#include "config.h"
#include "globalVariables.h"
//#include "gameLevels/introLevel.h"

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
    
    LedControllers::testLedsOneByOne();

    testBananaLedsOneByOne();

    showPotValues();

    ButtonControllers::displayButtonsAction();

    displayJoystickBehaviour(joystick1, "P1");

    displayJoystickBehaviour(joystick2, "P2");

    testDisplay();

    //============== END OF MAIN CODE ====================

    //Update the WS leds at the end of the loop
    //====================================================
    displayGrid.updateDisplay();
    bananaLeds.updateLeds();
    //====================================================
}

void displayJoystickBehaviour(Joystick& joystick, String name)
{
    if(joystick.wentUp())
        DEBUG_PRINTLN(name + " Up");
    if(joystick.wentDown())
        DEBUG_PRINTLN(name + " Down");
    if(joystick.wentLeft())
        DEBUG_PRINTLN(name + " Left");
    if(joystick.wentRight())
        DEBUG_PRINTLN(name + " Right");
}

void showPotValues()
{
    static uint32_t timer = 0;
    static int previousPotValues[6] = {0};

    if(millis() - timer > 500)
    {
        timer = millis();
        int currentPotValues[6];
        currentPotValues[0] = pot1.getValueMapped(0, 255);
        currentPotValues[1] = pot2.getValueMapped(0, 255);
        currentPotValues[2] = pot3.getValueMapped(0, 255);
        currentPotValues[3] = pot4.getValueMapped(0, 255);
        currentPotValues[4] = pot5.getValueMapped(0, 255);
        currentPotValues[5] = pot6.getValueMapped(0, 255);

        String output = "";
        for(int i=0; i < 6; i++)
        {
            if(currentPotValues[i] != previousPotValues[i])
            {
                previousPotValues[i] = currentPotValues[i];
                output += String(i) + ": " + String(currentPotValues[i]) + "\t";
            }
        }
        if(output.length() > 0)
            DEBUG_PRINTLN(output);
    }
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

void testBananaLedsOneByOne()
{
    static uint32_t timer = 0;
    static int ledIndex = 0;

    if(millis() - timer > 1000)
    {
        timer = millis();
        bananaLeds.setAllLedsToSingleValue(0, 0, 0);
        switch (ledIndex)
        {
        case 0:
            bananaLeds.setSingleLed(Banana_Led::B1_1, random(255), random(255), random(255));
            break;
        case 1:
            bananaLeds.setSingleLed(Banana_Led::B1_2, random(255), random(255), random(255));
            break;
        case 2:
            bananaLeds.setSingleLed(Banana_Led::B1_3, random(255), random(255), random(255));
            break;
        case 3:
            bananaLeds.setSingleLed(Banana_Led::B1_4, random(255), random(255), random(255));
            break;
        case 4:
            bananaLeds.setSingleLed(Banana_Led::B1_5, random(255), random(255), random(255));
            break;
        case 5:
            bananaLeds.setSingleLed(Banana_Led::B2_1, random(255), random(255), random(255));
            break;
        case 6:
            bananaLeds.setSingleLed(Banana_Led::B2_2, random(255), random(255), random(255));
            break;
        case 7:
            bananaLeds.setSingleLed(Banana_Led::B2_3, random(255), random(255), random(255));
            break;
        case 8:
            bananaLeds.setSingleLed(Banana_Led::B2_4, random(255), random(255), random(255));
            break;
        case 9:
            bananaLeds.setSingleLed(Banana_Led::B2_5, random(255), random(255), random(255));
            break;
        default:
            bananaLeds.setAllLedsToSingleValue(0, 0, 0);
            break;
        }

        ledIndex++;

        if(ledIndex == 10)
            ledIndex = 0;
    }
}

void testDisplay()
{
    static uint32_t timer = 0;
    static int index = 0;

    if(millis() - timer > 1000)
    {
        timer = millis();
        if(index == 0)
        {
            tmpPixel.setRGB(random(255), random(255), random(255));
            displayGrid.setAllToSingleColor(tmpPixel.getRGB());
        }
        else
        {
            displayGrid.setAllThroughTableRGB(definedDisplays::simonGame[index-1]);
        }
        
        index++;

        if(index == 10)
            index = 0;
    }
}