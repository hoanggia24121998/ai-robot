#include "MotorController.h"

// =============================================================
//  LEVEL 2 — MEDIUM.  Assigned to: ___________
//
//  Drives two motors through an H-bridge (DRV8833 / TB6612).
//  Each side has two pins: one for forward, one for backward.
//  To run at a given speed you send PWM on the matching pin and
//  hold the other one at zero.
//
//  In Wokwi these four pins are wired to four LEDs. LED brightness
//  is the duty cycle, so you can see exactly what the motors would
//  be doing without owning a motor.
//
//  Step-by-step guide: docs/bai-tap.md
// =============================================================

// Arduino-ESP32 changed the LEDC API in version 3.x. This block
// is already written for you — just call LEDC_ATTACH and
// LEDC_WRITE and it works on either version.
#if ESP_ARDUINO_VERSION_MAJOR >= 3
  #define LEDC_ATTACH(pin, freq, res) ledcAttach((pin), (freq), (res))
  #define LEDC_WRITE(pin, idx, duty)  ledcWrite((pin), (duty))
#else
  #define LEDC_ATTACH(pin, freq, res) do {} while (0)
  #define LEDC_WRITE(pin, idx, duty)  ledcWrite((idx), (duty))
#endif

void MotorController::begin(int pinLeftFwd, int pinLeftBwd,
                            int pinRightFwd, int pinRightBwd,
                            int pwmFreqHz, int pwmResolution) {
    // TODO [M1]: Store the four pins into the member variables
    //   pinLF_, pinLB_, pinRF_, pinRB_. Store resolution_ and
    //   compute maxDuty_.
    //
    //   maxDuty_ = (1 << pwmResolution) - 1
    //   With 8 bits that gives 255.
    //
    // TODO [M2]: Set up PWM on all four pins.
    //   On Arduino-ESP32 3.x and newer:
    //       LEDC_ATTACH(pin, pwmFreqHz, pwmResolution);
    //   On older versions you need ledcSetup(channel, ...) followed
    //   by ledcAttachPin(pin, channel). The #if block above already
    //   handles that difference — just call LEDC_ATTACH.
    //
    // TODO [M3]: Call stop() at the end, so the motors do not spin
    //   on power-up.

    (void)pinLeftFwd; (void)pinLeftBwd; (void)pinRightFwd; (void)pinRightBwd;
    (void)pwmFreqHz; (void)pwmResolution;
}

void MotorController::writeDuty(int pin, uint8_t percent) {
    // TODO [M4]: Convert a percentage (0..100) into a duty value
    //   (0..maxDuty_) and write it to the pin.
    //
    //   Watch out for integer overflow: maxDuty_ * percent can
    //   overflow a 16-bit int. Use (long)maxDuty_ * percent / 100.
    //
    //   Clamp percent to 100 in case a caller passes 150.
    //
    //   Older Arduino versions address a CHANNEL, not a pin. That
    //   is what the idx argument of LEDC_WRITE is for: compare pin
    //   against pinLF_ / pinLB_ / pinRF_ / pinRB_ to work out
    //   whether it is channel 0, 1, 2 or 3.
    (void)pin; (void)percent;
}

void MotorController::setSide(int pinFwd, int pinBwd, int signedSpeed) {
    // TODO [M5]: Positive signedSpeed = forward, negative =
    //   backward, zero = stop.
    //
    //   When going forward, drop the backward pin to zero FIRST,
    //   then drive the forward pin. Driving both pins at once
    //   shorts the H-bridge — on real hardware that destroys the
    //   driver chip.
    (void)pinFwd; (void)pinBwd; (void)signedSpeed;
}

// TODO [M6]: The five functions below are just different ways of
//   calling setSide().
//     forward   : both sides forward
//     backward  : both sides backward
//     turnLeft  : left side backward, right side forward (spin in place)
//     turnRight : left side forward, right side backward
//     stop      : both sides to zero
//
//   One line each is enough.

void MotorController::forward(uint8_t s)   { (void)s; }
void MotorController::backward(uint8_t s)  { (void)s; }
void MotorController::turnLeft(uint8_t s)  { (void)s; }
void MotorController::turnRight(uint8_t s) { (void)s; }
void MotorController::stop()               { }

void MotorController::apply(const NavDecision& d) {
    // TODO [M7]: Read d.command and call the matching function
    //   above with d.speed. Use a switch, and include a default
    //   branch that calls stop().
    (void)d;
}
