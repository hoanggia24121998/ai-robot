#pragma once
#include <Arduino.h>

// =============================================================
//  RobotDisplay — SSD1306 128x64 OLED over I2C.
//  Shows the current state and distance. Later this becomes the
//  robot's animated face.
// =============================================================

class RobotDisplay {
public:
    bool begin(int sdaPin, int sclPin, uint8_t i2cAddress = 0x3C);
    void show(const char* stateName, int distanceCm, bool running);
    bool ready() const { return ready_; }

private:
    bool ready_ = false;
};
