#pragma once

#include "SFML/Graphics.h"


// Typedefs
typedef unsigned int    t_joyNum;
typedef unsigned short  t_buttonNum;

// Enums
enum {
    Count = 4       // Player 0-3
};

enum {
    DPAD_UP = 0x0001,
    DPAD_DOWN = 0x0002,
    DPAD_LEFT = 0x0004,
    DPAD_RIGHT = 0x0008,
    START = 0x0010,
    BACK = 0x0020,
    LEFT_THUMB = 0x0040,
    RIGHT_THUMB = 0x0080,
    LB = 0x0100,
    RB = 0x0200,
    A = 0x1000,
    B = 0x2000,
    X = 0x4000,
    Y = 0x8000,
};

sfBool isConnected(t_joyNum joyNum);
unsigned int getButtonCount(t_joyNum joyNum);
sfBool isButtonPressed(t_joyNum joyNum, t_buttonNum buttonNum);
sfBool isAnyXBox360ControllerConnected();
void getTriggers(t_joyNum joyNum, float* left, float* right);
void getSticksPosition(t_joyNum joyNum, sfVector2f* left, sfVector2f* right);
void setVibration(t_joyNum joyNum, float leftMotor, float rightMotor);