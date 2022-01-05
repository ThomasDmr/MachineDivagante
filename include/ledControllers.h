// Suite de fonctions pour simplifier la gestion des LEDs

// On inclu la librairie de gestion du Shift Register des LEDs
#include "../src/ShiftRegisters/OutputShiftRegister8Bit.h"
#include "../config.h"
// On enveloppe tout ça dans un namespace pour éviter toutes confusions
namespace LedControllers
{
OutputShiftRegister8Bit ledRegister(LED_STCP, LED_DS, LED_SHCP);

// The LED enum will help us read the code in a more comprehensive way
// WARNING : the adresses must be ordered from smallest to largest !
enum LED {LED_B5 = ADR_B5_LED, LED_B6 = ADR_B6_LED, LED_B4 = ADR_B4_LED, LED_B2 = ADR_B2_LED, 
            LED_B1 = ADR_B1_LED, LED_B3 = ADR_B3_LED, LED_BR, LED_BL, LED_BM};

void initLeds()
{
    ledRegister.init();
    pinMode(PIN_LED_BR, OUTPUT);
    pinMode(PIN_LED_BM, OUTPUT);
    pinMode(PIN_LED_BL, OUTPUT);

    digitalWrite(PIN_LED_BR, LOW);
    digitalWrite(PIN_LED_BL, LOW);
    digitalWrite(PIN_LED_BM, LOW);
}

void updateLedsStates()
{
    ledRegister.updateState();
}

void switchOffAllLeds()
{
    ledRegister.clearOutput();
    digitalWrite(PIN_LED_BR, LOW);
    digitalWrite(PIN_LED_BL, LOW);
    digitalWrite(PIN_LED_BM, LOW);
}

void setLedState(LED led, bool state)
{
    switch (led)
    {
    case LED_BR:
        digitalWrite(PIN_LED_BR, state);
        break;
    case LED_BL:
        digitalWrite(PIN_LED_BL, state);
        break;
    case LED_BM:
        digitalWrite(PIN_LED_BM, state);
        break;
    default:
        ledRegister.changeOneOutput(led, state);
        break;
    }
}

void turnOnLed(LED led)
{
    setLedState(led, 1);        
}

void turnOffLed(LED led)
{
    setLedState(led, 0);
}

void testLedsOneByOne()
{
    static uint32_t timer = 0;
    static int ledIndex = 0;

    if(millis() - timer > 1000)
    {
        timer = millis();
        switchOffAllLeds();
        switch (ledIndex)
        {
        case 0:
            turnOnLed(LED_B1);
            break;
        case 1:
            turnOnLed(LED_B2);
            break;
        case 2:
            turnOnLed(LED_B3);
            break;
        case 3:
            turnOnLed(LED_B4);
            break;
        case 4:
            turnOnLed(LED_B5);
            break;
        case 5:
            turnOnLed(LED_B6);
            break;
        case 6:
            turnOnLed(LED_BR);
            break;
        case 7:
            turnOnLed(LED_BL);
            break;
        case 8:
            turnOnLed(LED_BM);
            break;
        default:
            switchOffAllLeds();
            break;
        }

        ledIndex++;

        if(ledIndex == 9)
            ledIndex = 0;
    }
}

}; // Namespace LedControllers