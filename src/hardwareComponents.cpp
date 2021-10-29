#include "include/MachineDivagante/hardwareComponents.h"

InputShiftRegister::InputShiftRegister(int latchPin, int dataPin, int clockPin, int dataSize = 16):
                        m_latchPin(latchPin), m_dataPin(dataPin), m_clockPin(clockPin), m_dataSize(dataSize)
{
    m_registerState = 0;
}

void InputShiftRegister::init()
{
    pinMode(m_latchPin, OUTPUT);
    pinMode(m_dataPin, INPUT);
    pinMode(m_clockPin, OUTPUT);
}

int     InputShiftRegister::getNewState()
{
    int bitVal;
  unsigned long bytesValControl = 0;
  unsigned long bytesValMatrix1 = 0;
  unsigned long bytesValMatrix2 = 0;
  // Trigger a parallel Load to latch the state of the data lines
  digitalWrite(PLOAD_PIN, LOW);
  digitalWrite(PLOAD_PIN, HIGH);
  // Loop to read each bit value from the serial out line of the SN74HC165N.
  for(int i = 31; i >=0; i--){
    bitVal = digitalReadFast(CONTROL_BUTTON_DATA_PIN);
    // Set the corresponding bit.
    bytesValControl |= bitVal << i;
    newPanelButtonStates[0] =bytesValControl;
    
    bitVal = digitalReadFast(MATRIX1_BUTTON_DATA_PIN);
    bytesValMatrix1 |= bitVal << i;
    newPanelButtonStates[1] =bytesValMatrix1;
    
    bitVal = digitalReadFast(MATRIX2_BUTTON_DATA_PIN);
    bytesValMatrix2 |= bitVal << i;
    newPanelButtonStates[2] =bytesValMatrix2;
    // Pulse the Clock (rising edge shifts the next bit).
    digitalWriteFast(CLOCK_PIN, HIGH);
    digitalWriteFast(CLOCK_PIN, LOW);

}

void    InputShiftRegister::clearState()
{

}