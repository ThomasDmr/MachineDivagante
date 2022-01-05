// LedDisplay.h
/**
 * © Thomas Demmer - 2021 | www.thomasdmr.com
 */

#pragma once

// PRJC Library to solve audio and WSled conflict 
// https://github.com/PaulStoffregen/WS2812Serial
#include "WS2812Serial.h"
#include "../../include/helperFunctions.h"
#include "../../config.h"

using namespace helper;

enum Banana_Led {B1_1, B1_2, B1_3, B1_4, B1_5, 
                B2_1, B2_2, B2_3, B2_4, B2_5};

class BananaLed
{
  public:
  BananaLed(int wsLedPin, int dimmer);

  void init();

  void setAllLedsToSingleValue(int r, int g, int b);
  void setSingleLed(int ledNumber, int r, int g, int b);
  void updateLeds();

  private:
  int           m_dimmer;
  WS2812Serial  m_leds;
};
