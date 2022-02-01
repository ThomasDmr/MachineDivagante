#pragma once

#include "../globalVariables.h"

#ifdef TEST_HARDWARE
namespace hardwareTest
{
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

void showBananaConnected()
{
    static uint32_t timer = 0;
    static int previousBananaState[5] = {0};

    if(millis() - timer > 500)
    {
        timer = millis();
        int currentBananaState[5];
        currentBananaState[0] = plug1Low.isActive();
        currentBananaState[1] = plug2Low.isActive();
        currentBananaState[2] = plug3Low.isActive();
        currentBananaState[3] = plug4Low.isActive();
        currentBananaState[4] = plug5Low.isActive();

        String output = "";
        for(int i=0; i < 5; i++)
        {
            if(currentBananaState[i] != previousBananaState[i])
            {
                previousBananaState[i] = currentBananaState[i];
                output += String(i) + ": " + String(currentBananaState[i]) + "\t";
            }
        }
        if(output.length() > 0)
            DEBUG_PRINTLN(output);
    }        

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
            rgb randomRGB = {random(255), random(255), random(255)};
            displayGrid.setAllToSingleColor(randomRGB);
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

void runFullHardwareTests()
{
    LedControllers::testLedsOneByOne();

    showBananaConnected();

    testBananaLedsOneByOne();

    showPotValues();

    

    ButtonControllers::displayButtonsAction();

    displayJoystickBehaviour(joystick1, "P1");

    displayJoystickBehaviour(joystick2, "P2");

    testDisplay();
}
} // namespace hardwareTest
#endif