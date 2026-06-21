/*
SNES -> Jamma/Neo Geo DB15
Robin Edwards 2018
based on the code found at https://github.com/burks10/Arduino-SNES-Controller

Changes by RetroCityRansom ->
1. Added Turbofire extension:
    L = Turbofire toggle for Button A
    R = Turbofire toggle for Button B
2. SELECT + UP cycles through three different Turbofire speeds
3. SELECT + DOWN swaps A and B buttons
4. SELECT + RIGHT saves all settings as default
*/

/* 

SNES Controller -> Arduino
  -----------------\
  | 1 2 3 4 | 5 6 7 |
  -----------------/
  
  Pin 1: +5V
  Pin 2: Clock -> Arduino A0
  Pin 3: Latch -> Arduino A1
  Pin 4: Serial -> Arduino A2
  Pin 7: GND
*/
#include <EEPROM.h>


int DATA_CLOCK    = A0;
int DATA_LATCH    = A1;
int DATA_SERIAL   = A2;

/* 

Arduino -> DB15
    1(=GND)        8(=5V)
  \-------------------/
   \ o o o o o o o o / [Viewed from front]
    \ o o o o o o o /
     --------------- 
      9          15

 DB15 Pin  ->  Arduino
 --------      -------
 1 (GND)       GND
 8 (+5V)       +5V
 3 (Sel)       D2
 11 (Start)    D3
 15 (Up)       D4
 7 (Down)      D5
 14 (Left)     D6
 6 (Right)     D7
 13 (A)        D8
 5 (B)         D9
 12 (C)        D10
 4 (D)         D11
*/

#define PIN_SELECT  2
#define PIN_START   3
#define PIN_UP      4
#define PIN_DOWN    5
#define PIN_LEFT    6
#define PIN_RIGHT   7
#define PIN_BUT1    8
#define PIN_BUT2    9
#define PIN_BUT3    10
#define PIN_BUT4    11

#define PIN_LED      13

int buttons_state[12];  // B,Y,Sel,Start,U,D,L,R,A,X,L,R
int output_pins[12] = {
  PIN_BUT2,    // B
  PIN_BUT3,    // Y
  PIN_SELECT,  // Select
  PIN_START,   // Start
  PIN_UP,      // Up
  PIN_DOWN,    // Down
  PIN_LEFT,    // Left
  PIN_RIGHT,   // Right
  PIN_BUT1,    // A
  PIN_BUT4,    // X
  0,           // L (Turbofire toggle A)
  0            // R (Turbofire toggle B)
};

// EEPROM stuff
bool lastDoSaveSettingsState = false;
const int ADDR_TURBO_SPEED = 0;
const int ADDR_AB_BUTTON_SWAP = 1;

// Turbofire variables
bool TurbofireA = false;
bool TurbofireB = false;
bool lastL = true;
bool lastR = true;
unsigned long lastLoopTime = 0;
// 2 = 15Hz, 3 = 10Hz, 1 = 30Hz
const int turbofireLimits[3] = {2, 3, 1};
const int turbofireModeCount = sizeof(turbofireLimits) / sizeof(turbofireLimits[0]);
int currentTurboSpeed = 0;
bool lastDoChangeTurbofireMode = false;
int frameCounter = 0;
bool TurbofirePulse = false;

// Button swap variables
bool buttonSwapEnabled = false;
bool lastDoChangeButtonMappingState = false;

void setup ()
{
    currentTurboSpeed = EEPROM.read(ADDR_TURBO_SPEED) % turbofireModeCount;
    buttonSwapEnabled = EEPROM.read(ADDR_AB_BUTTON_SWAP);

    pinMode(DATA_CLOCK, OUTPUT);
    digitalWrite (DATA_CLOCK, HIGH);
  
    pinMode(DATA_LATCH, OUTPUT);
    digitalWrite(DATA_LATCH, LOW);
    
    pinMode(DATA_SERIAL, INPUT_PULLUP);
    
    pinMode(PIN_LED, OUTPUT);
}

void loop ()
{
    if (millis() - lastLoopTime < 16) {
        return; 
    }
    lastLoopTime = millis();
    // Read from the SNES controller
    
    /* Latch for 12us */
    digitalWrite(DATA_LATCH, HIGH);
    delayMicroseconds(12);
    digitalWrite(DATA_LATCH, LOW);
    delayMicroseconds(6);
    
    /* Read data bit by bit from SR */
    for (int i = 0; i < 16; i++) {
        digitalWrite(DATA_CLOCK, LOW);
        delayMicroseconds(6);
        if (i <= 11)
            buttons_state[i] = digitalRead(DATA_SERIAL);
        digitalWrite(DATA_CLOCK, HIGH);
        delayMicroseconds(6);
    }

    // Hotkey detection
    bool selectPressed = !buttons_state[2];
    bool upPressed = !buttons_state[4];
    bool downPressed = !buttons_state[5];
    bool rightPressed = !buttons_state[7];

	// Hotkey to change Turbofire speed
    bool doChangeTurbofireMode = (selectPressed && upPressed);
    if (doChangeTurbofireMode && !lastDoChangeTurbofireMode)
    {
        currentTurboSpeed = (currentTurboSpeed + 1) % turbofireModeCount;
    }
    lastDoChangeTurbofireMode = doChangeTurbofireMode;

    // Hotkey to swap A and B
    bool doChangeButtonMapping = (selectPressed && downPressed);
    if (doChangeButtonMapping && !lastDoChangeButtonMappingState)
    {
        buttonSwapEnabled = !buttonSwapEnabled; 
    }
    lastDoChangeButtonMappingState = doChangeButtonMapping;

    // Hotkey to save settings for turbofire and button mapping
    bool doSaveSettings = (selectPressed && rightPressed);
    if (doSaveSettings && !lastDoSaveSettingsState)
    {
        EEPROM.update(ADDR_TURBO_SPEED, currentTurboSpeed);
        EEPROM.update(ADDR_AB_BUTTON_SWAP, buttonSwapEnabled);

        // flash after saving
        for (int b = 0; b < 6; b++) {
            digitalWrite(PIN_LED, HIGH);
            delay(150);
            digitalWrite(PIN_LED, LOW);
            delay(150);
        }
    }
    lastDoSaveSettingsState = doSaveSettings;

	// L / R Turbofire Toggle
    if (lastL && !buttons_state[10])   // L pressed
        TurbofireB = !TurbofireB;        
    lastL = buttons_state[10];

    if (lastR && !buttons_state[11])   // R pressed
        TurbofireA = !TurbofireA;
    lastR = buttons_state[11];

	// Turbofire timing
    frameCounter++;
    
    if (frameCounter >= turbofireLimits[currentTurboSpeed])
    {
        frameCounter = 0; 
        TurbofirePulse = !TurbofirePulse;
    }

    // Output the state on our DB15 output pins
    // pulling them low if the equivalent SNES button
    // is pushed
    for (int i = 0; i <= 11; i++)
    {
        if (output_pins[i] != 0)
        {
            int swapIndex = i;
            if (buttonSwapEnabled) {
                if (i == 0) swapIndex = 8;      
                else if (i == 8) swapIndex = 0; 
            }

            bool pressed = !buttons_state[swapIndex];
            // Turbofire override
            if (i == 8 && TurbofireA)   // SNES A -> PIN_BUT1
                pressed = pressed && TurbofirePulse;
            else if (i == 0 && TurbofireB)   // SNES B -> PIN_BUT2
                pressed = pressed && TurbofirePulse;
            if (pressed)
            {
                digitalWrite(output_pins[i], LOW);
                pinMode(output_pins[i], OUTPUT);
            }
            else
                pinMode(output_pins[i], INPUT);            
        }
    }

    if (!doSaveSettings) 
    {
        if (!buttons_state[2])
            digitalWrite(PIN_LED, HIGH);
        else
            digitalWrite(PIN_LED, LOW);
    }
    
    // delay(5);
}
