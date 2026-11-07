#pragma once
#include <Arduino.h>

// =============================================================
//  DistanceSensor — HC-SR04 ultrasonic rangefinder.
//
//  How it works: fire an ultrasonic pulse, then time how long it
//  takes for the echo to come back. Halve that time (the sound
//  travels out and back) and multiply by the speed of sound.
//
//  NOTE: pulseIn() blocks until it sees a pulse or times out. Do
//  not call this from an audio task once the project moves to the
//  real firmware — give it a task of its own.
// =============================================================

class DistanceSensor {
public:
    void begin(int trigPin, int echoPin, unsigned long timeoutUs = 25000);

    // Returns the distance in centimetres, or -1 if the read failed.
    int readCm();

private:
    int trig_ = -1;
    int echo_ = -1;
    unsigned long timeoutUs_ = 25000;
};
