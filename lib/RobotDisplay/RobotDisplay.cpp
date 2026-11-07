#include "RobotDisplay.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// =============================================================
//  LEVEL 1 — EASY.  Assigned to: ___________
//
//  SSD1306 128x64 OLED over I2C. The Adafruit library handles the
//  protocol, so your job is calling the right functions.
//
//  Reference: File > Examples > Adafruit SSD1306 in the Arduino
//  IDE, or read Adafruit_GFX.h directly.
//
//  Step-by-step guide: docs/bai-tap.md
// =============================================================

namespace {
constexpr int kWidth = 128;
constexpr int kHeight = 64;
Adafruit_SSD1306 oled(kWidth, kHeight, &Wire, -1);
}

bool RobotDisplay::begin(int sdaPin, int sclPin, uint8_t i2cAddress) {
    // TODO [R1]: Start I2C on the two pins passed in:
    //       Wire.begin(sdaPin, sclPin);
    //
    // TODO [R2]: Start the display:
    //       ready_ = oled.begin(SSD1306_SWITCHCAPVCC, i2cAddress);
    //       Return false straight away if it fails.
    //
    // TODO [R3]: Draw a splash screen, for example the robot name:
    //       oled.clearDisplay();
    //       oled.setTextColor(SSD1306_WHITE);
    //       oled.setTextSize(1);
    //       oled.setCursor(0, 0);
    //       oled.println(F("AI ROBOT"));
    //       oled.display();     <- without this the screen stays blank
    //
    //   Note: nothing appears until you call oled.display(). Forgetting
    //   that line is the single most common mistake with this library.

    (void)sdaPin; (void)sclPin; (void)i2cAddress;
    ready_ = false;
    return false;
}

void RobotDisplay::show(const char* stateName, int distanceCm, bool running) {
    // TODO [R4]: If the display never started (ready_ == false),
    //   return immediately and do nothing. Otherwise the program
    //   hangs when no display is connected.
    //
    // TODO [R5]: Draw the screen:
    //       - top line: "RUNNING" or "PAUSED", based on running
    //       - middle: the state name in large text (setTextSize(2))
    //       - bottom: the distance, showing "--" when distanceCm < 0
    //
    //   Call clearDisplay() before drawing and display() after.
    //
    // TODO [R6] (optional): draw a horizontal bar that gets shorter
    //   as the obstacle gets closer.
    //       oled.drawRect(x, y, w, h, SSD1306_WHITE);   // outline
    //       oled.fillRect(x, y, w, h, SSD1306_WHITE);   // filled

    (void)stateName; (void)distanceCm; (void)running;
}

// -------------------------------------------------------------
//  STRETCH GOAL: replace the text with an expressive robot face.
//  Happy, startled, thinking. drawCircle and fillCircle are all
//  you need. This is what decides whether a child likes the robot,
//  so it is worth the effort.
// -------------------------------------------------------------
