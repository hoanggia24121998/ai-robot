#pragma once
#include <Arduino.h>
#include "Navigator.h"

// =============================================================
//  MotorController — carries out the Navigator's decisions.
//  Drives an H-bridge (DRV8833 / TB6612): two PWM pins per side.
//  In the Wokwi simulation those four pins drive four LEDs, so
//  LED brightness shows you the duty cycle directly.
// =============================================================

class MotorController {
public:
    void begin(int pinLeftFwd, int pinLeftBwd,
               int pinRightFwd, int pinRightBwd,
               int pwmFreqHz = 20000, int pwmResolution = 8);

    void apply(const NavDecision& d);

    void forward(uint8_t speed);
    void backward(uint8_t speed);
    void turnLeft(uint8_t speed);
    void turnRight(uint8_t speed);
    void stop();

private:
    // Negative speed = backward, positive = forward, 0 = stop.
    // Unit is percent.
    void setSide(int pinFwd, int pinBwd, int signedSpeed);
    void writeDuty(int pin, uint8_t percent);

    int pinLF_ = -1, pinLB_ = -1, pinRF_ = -1, pinRB_ = -1;
    int resolution_ = 8;
    int maxDuty_ = 255;
};
