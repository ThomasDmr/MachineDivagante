#include "Arduino.h"

class Joystick
{
    public:
    Joystick(int upPin, int downPin, int leftPin, int rightPin);

    bool wentUp();
    bool wentDown();
    bool wentLeft();
    bool wentRight();

    void update();

    private:
};

class InputShiftRegister
{
    public: 
    InputShiftRegister(int latchPin, int dataPin, int clockPin, int dataSize = 16);

    void    init();
    int     getNewState();
    void    clearState(); 

    private:
    int m_latchPin;
    int m_dataPin;
    int m_clockPin;
    int m_dataSize;
    int m_registerState;

};

class BananaPlug
{
    public:
    BananaPlug(int bananaPin, int pinMode);

    void setToOutput(bool level);

    void setToInput();

    bool isActive();
};