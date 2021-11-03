// Suite de fonctions pour simplifier la gestion des boutons poussoirs

// On inclu la librairie de gestion du Shift Register des boutons
#include "ShiftRegisters/InputShiftRegister.h"
#include "../config.h"
#include "helperFunctions.h"
#include "Bounce2.h"

// On enveloppe tout ça dans un namespace pour éviter toutes confusions
namespace ButtonControllers
{
    InputShiftRegister switchRegister(SW_SH, SW_QH, SW_CLK);

    Bounce BRbouncer;
    Bounce BLbouncer;
    Bounce BMbouncer;

    // The Button enum will help us read the code in a more comprehensive way
    enum Button {SW_B1 = ADR_B1, SW_B2 = ADR_B2, SW_B3 = ADR_B3, 
                SW_B4 = ADR_B4, SW_B5 = ADR_B5, SW_B6 = ADR_B6, SW_BR, SW_BL, SW_BM};
    
    void initButtons()
    {
        switchRegister.init();
        
        pinMode(PIN_BR, INPUT_PULLUP);
        pinMode(PIN_BM, INPUT_PULLUP);
        pinMode(PIN_BL, INPUT_PULLUP);

        BRbouncer.attach(PIN_BR);
        BRbouncer.interval(5);
        BLbouncer.attach(PIN_BL);
        BLbouncer.interval(5);
        BMbouncer.attach(PIN_BM);
        BMbouncer.interval(5);
    }

    void updateButtonsStates()
    {
        switchRegister.updateState();
        BRbouncer.update();
        BLbouncer.update();
        BMbouncer.update();
    }

    bool isButtonActive(Button button)
    {
        switch (button)
        {
        case SW_BL:
            return (BLbouncer.read() == 0);
            break;
        case SW_BM:
            return (BMbouncer.read() == 0);
            break;
        case SW_BR:
            return (BRbouncer.read() == 0);
            break;
        default:
            return helper::getBit(switchRegister.getCurrentState(), button);
            break;
        }
    }

    bool wasButtonPressed(Button button)
    {
        switch (button)
        {
        case SW_BL:
            return BLbouncer.fell();
            break;
        case SW_BM:
            return BMbouncer.fell();
            break;
        case SW_BR:
            return BRbouncer.fell();
            break;
        default:
            return helper::getBit(switchRegister.getFallingEdgeState(), button);
            break;
        }
    }
}; // Namespace LedControllers