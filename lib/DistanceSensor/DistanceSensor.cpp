#include "DistanceSensor.h"

// =============================================================
//  LEVEL 1 — EASY.  Assigned to: ___________
//
//  Read the HC-SR04 ultrasonic sensor.
//
//  How it works: drive the TRIG pin HIGH for 10 microseconds. The
//  sensor emits an ultrasonic burst and holds the ECHO pin HIGH
//  until it hears the echo return. The width of that ECHO pulse
//  is the round-trip travel time of the sound.
//
//  Step-by-step guide: docs/bai-tap.md
// =============================================================

void DistanceSensor::begin(int trigPin, int echoPin, unsigned long timeoutUs) {
    // TODO [D1]: Store all three arguments into the member variables.
    // TODO [D2]: pinMode TRIG as OUTPUT and ECHO as INPUT.
    // TODO [D3]: Drive TRIG LOW so we start from a clean state.
    (void)trigPin; (void)echoPin; (void)timeoutUs;
}

int DistanceSensor::readCm() {
    // TODO [D4]: Send the trigger pulse:
    //       TRIG LOW,  wait 2 microseconds   (delayMicroseconds(2))
    //       TRIG HIGH, wait 10 microseconds
    //       TRIG LOW
    //
    // TODO [D5]: Measure the ECHO pulse width:
    //       unsigned long us = pulseIn(echo_, HIGH, timeoutUs_);
    //       A return value of 0 means it timed out: nothing in range.
    //
    // TODO [D6]: Convert to centimetres.
    //       Sound travels roughly 343 m/s = 0.0343 cm per microsecond.
    //       Remember to divide by 2, because the sound goes out AND back.
    //
    // TODO [D7]: Reject nonsense readings. An HC-SR04 is only good
    //       for roughly 2..400 cm. Anything outside that: return -1.
    //
    //   IMPORTANT CONTRACT: return -1 when the read fails. Navigator
    //   relies on that to know when to ignore the reading. Do not
    //   return 0 — zero means "obstacle touching the sensor".
    return -1;
}

// -------------------------------------------------------------
//  NOTE for real hardware (phase 2):
//  pulseIn() blocks for up to tens of milliseconds. Harmless in
//  the simulation, but once this runs alongside audio processing
//  it will make speech stutter. At that point switch to a
//  non-blocking measurement. See the stretch goals in
//  docs/bai-tap.md.
// -------------------------------------------------------------
