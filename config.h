#pragma once

// Uncomment the next line to run the hardware test routine
// #define TEST_HARDWARE

// Uncomment the next line to add all the audio elements
#define AUDIO_ENABLED

// Switch Input register (sn74hc165) pins 
const int SW_CLK    = 2; // clock 
const int SW_SH     = 3; // latch pin
const int SW_QH     = 4; // data pin

// Input register parallel input adresses (position in the register)
const int ADR_B1        = 0;
const int ADR_B2        = 1;
const int ADR_B3        = 4;
const int ADR_B4        = 2;
const int ADR_B5        = 5;
const int ADR_B6        = 3;
const int ADR_J1_UP     = 11;
const int ADR_J1_DOWN   = 10;
const int ADR_J1_LEFT   = 8;
const int ADR_J1_RIGHT  = 9;
// WARNING : the J2 controller is mounted upside-down, so up-down and left-right are inverted
const int ADR_J2_UP     = 14;
const int ADR_J2_DOWN   = 15;
const int ADR_J2_LEFT   = 13;
const int ADR_J2_RIGHT  = 12;


// LED output register (74hc565) pins 
const int LED_DS    = 5; // data pin 
const int LED_STCP  = 6; // latch pin
const int LED_SHCP  = 7; // clock pin 

// Output register parallel output adresses (position in the register)
const int ADR_B1_LED    = 4;
const int ADR_B2_LED    = 3;
const int ADR_B3_LED    = 5;
const int ADR_B4_LED    = 2;
const int ADR_B5_LED    = 0;
const int ADR_B6_LED    = 1;

// Potentiometers
const int PIN_POT1  = A16;
const int PIN_POT2  = A15;
const int PIN_POT3  = A3;
const int PIN_POT4  = A4;
const int PIN_POT5  = A12;
const int PIN_POT6  = A13;

// Banana Plugs
const int BANANA_1_1  = 16;
const int BANANA_1_2  = 15;
const int BANANA_1_3  = 14;
const int BANANA_1_4  = 13;
const int BANANA_1_5  = 39;

const int BANANA_2_1  = 19;
const int BANANA_2_2  = 20;
const int BANANA_2_3  = 21;
const int BANANA_2_4  = 22;
const int BANANA_2_5  = 23;

// Pins des leds des boutons centraux
const int PIN_LED_BR    = 33;
const int PIN_LED_BL    = 36;
const int PIN_LED_BM    = 24;

// Pins des boutons centraux
const int PIN_BR    = 30;
const int PIN_BL    = 37;
const int PIN_BM    = 25;

// WS led pins
const int PIN_WS_SCREEN = 10;
const int PIN_WS_BANANA = 26;

// display size
const int       DISPLAY_WIDTH = 8;
const int       DISPLAY_HEIGHT = 6;

