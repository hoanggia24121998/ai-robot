// =============================================================
//  AI Robot — main program
//
//  This file is the wiring: it calls begin() on each library at
//  start-up, then on every tick runs the chain
//      read sensor  ->  Navigator decides  ->  motors execute
//
//  The wiring is already written, LEAVE IT ALONE. It is what lets
//  you finish DistanceSensor and immediately see readings on the
//  serial monitor, so you get feedback without waiting for anyone
//  else to finish their part.
//
//  The three TODOs in this file are a separate exercise: see
//  level 1C in docs/bai-tap.md.
// =============================================================

#include <Arduino.h>
#include "pinmap.h"
#include "Navigator.h"
#include "MotorController.h"
#include "DistanceSensor.h"
#if USE_DISPLAY
#include "RobotDisplay.h"
#endif

namespace {

Navigator        nav;
MotorController  motors;
DistanceSensor   sensor;
#if USE_DISPLAY
RobotDisplay     screen;
#endif

unsigned long nextTickMs    = 0;
unsigned long lastButtonMs  = 0;
int           lastButtonState = HIGH;

const char* commandName(DriveCommand c) {
    // TODO [P1] — easy: return a label for the serial log.
    //   Forward -> "FWD", Backward -> "BACK", TurnLeft -> "LEFT",
    //   TurnRight -> "RIGHT", Stop -> "STOP"
    //   Use a switch and include a default branch.
    (void)c;
    return "?";
}

void pollButton(unsigned long now) {
    // TODO [P2] — medium: read the button and debounce it.
    //
    //   The button is wired to GND with INPUT_PULLUP, so:
    //       digitalRead(PIN_BUTTON) == LOW  means PRESSED
    //       == HIGH means released
    //
    //   The problem: a mechanical contact bounces for a few
    //   milliseconds on each press. Reading it raw gives you dozens
    //   of press/release events from one finger tap, and the robot
    //   flickers on and off.
    //
    //   The fix: only accept a change if the previous change was
    //   more than 250ms ago. Use the lastButtonMs and
    //   lastButtonState variables already declared above.
    //
    //   On a confirmed press (HIGH transitioning to LOW):
    //       - if nav.running(), call nav.halt() and motors.stop()
    //       - otherwise call nav.start(now)
    //       - print a line to serial so you can see it registered
    //
    //   STRETCH GOAL: switch to push-to-talk, where holding the
    //   button starts and releasing it stops. That suits children
    //   better and stops the robot reacting to the television.
    (void)now;
}

}  // namespace

void setup() {
    Serial.begin(115200);
    delay(200);

    pinMode(PIN_BUTTON, INPUT_PULLUP);
    lastButtonState = digitalRead(PIN_BUTTON);

    motors.begin(PIN_MOTOR_L_FWD, PIN_MOTOR_L_BWD,
                 PIN_MOTOR_R_FWD, PIN_MOTOR_R_BWD,
                 PWM_FREQ_HZ, PWM_RESOLUTION);

    sensor.begin(PIN_TRIG, PIN_ECHO);

#if USE_DISPLAY
    if (!screen.begin(PIN_OLED_SDA, PIN_OLED_SCL)) {
        Serial.println(F("[WARN] No OLED display found, skipping"));
    }
#endif

    // CI waits for this exact line. Do not change the text unless
    // you also update .github/workflows/ci.yml.
    Serial.println(F("ROBOT READY"));
    Serial.println(F("Press the button to start. Drag the distance slider in Wokwi to test."));
}

void loop() {
    const unsigned long now = millis();

    pollButton(now);

    // TODO [P3] — medium: throttle the tick rate.
    //
    //   Right now the block below runs flat out, tens of thousands
    //   of times a second. Two consequences: the ultrasonic sensor
    //   gets re-triggered before it can hear its own echo, so the
    //   readings go haywire; and on real hardware it eats all the
    //   CPU time other work needs.
    //
    //   It should run exactly 20 times a second, that is once every
    //   LOOP_PERIOD_MS = 50ms.
    //
    //   Hint: use the nextTickMs variable already declared above.
    //       if now < nextTickMs  ->  return, do nothing this pass
    //       otherwise            ->  set nextTickMs = now + LOOP_PERIOD_MS
    //                                and carry on
    //
    //   Why not just delay(50): delay() blocks the whole program, so
    //   the button would be dead for those 50ms. The approach above
    //   blocks nothing.

    const int distance = sensor.readCm();
    const NavDecision decision = nav.update(distance, now);
    motors.apply(decision);

#if USE_DISPLAY
    screen.show(nav.stateName(), distance, nav.running());
#endif

    // Log sparingly so the output stays readable: one line per 500ms.
    static unsigned long lastLogMs = 0;
    if (now - lastLogMs >= 500) {
        lastLogMs = now;
        Serial.print(F("d="));
        if (distance < 0) Serial.print(F("--")); else Serial.print(distance);
        Serial.print(F("cm  state="));
        Serial.print(nav.stateName());
        Serial.print(F("  cmd="));
        Serial.print(commandName(decision.command));
        Serial.print(F(" "));
        Serial.println(decision.speed);
    }
}
