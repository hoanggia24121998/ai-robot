#pragma once
// =============================================================
//  Pin map — ESP32-S3-DevKitC-1
// =============================================================
//  Rules before changing any pin here:
//    - AVOID GPIO 0, 45, 46 : strapping pins, they decide boot mode
//    - AVOID GPIO 19, 20    : native USB on the chip
//    - AVOID GPIO 26..32    : wired to flash / PSRAM
//    - AVOID GPIO 35, 36, 37: octal PSRAM on N16R8 modules
//    - AVOID GPIO 43, 44    : UART0, used by the serial monitor
//  If you change a pin here, change diagram.json to match.
// =============================================================

// --- Motors (H-bridge: DRV8833 / TB6612) ----------------------
// Each side uses two PWM pins: one for forward, one for backward.
constexpr int PIN_MOTOR_L_FWD = 4;
constexpr int PIN_MOTOR_L_BWD = 5;
constexpr int PIN_MOTOR_R_FWD = 6;
constexpr int PIN_MOTOR_R_BWD = 7;

// --- HC-SR04 ultrasonic distance sensor -----------------------
constexpr int PIN_TRIG = 15;
constexpr int PIN_ECHO = 16;

// --- Push button (wired to GND, use INPUT_PULLUP) -------------
constexpr int PIN_BUTTON = 17;

// --- SSD1306 OLED display over I2C ----------------------------
constexpr int PIN_OLED_SDA = 8;
constexpr int PIN_OLED_SCL = 9;

// --- PWM settings ---------------------------------------------
constexpr int PWM_FREQ_HZ = 20000;  // 20kHz: above hearing range, motors stay quiet
constexpr int PWM_RESOLUTION = 8;   // 8 bits -> duty range 0..255

// --- Main loop rate -------------------------------------------
constexpr unsigned long LOOP_PERIOD_MS = 50;  // 20 ticks per second

// --- Display toggle -------------------------------------------
// Set to 0 if no OLED is wired up, or to get a smaller build.
#define USE_DISPLAY 1
