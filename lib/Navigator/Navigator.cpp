#include "Navigator.h"

// =============================================================
//  LEVEL 3 — HARD.  Assigned to: ___________
//
//  This is the robot's brain. Right now it knows nothing: every
//  function returns an empty result, so 7 of the 9 tests are RED.
//
//  Your job: turn all 9 tests green.
//      pio test -e native
//
//  Do not guess. Read test/test_navigator/test_navigator.cpp
//  first — that file IS the specification, written as code. Each
//  test describes one situation and the expected outcome.
//
//  Work one test at a time: run the tests, pick a red one, make it
//  green, run again. Do not write everything before running once.
//
//  Step-by-step guide: docs/bai-tap.md
//
//  HARD RULE: this file must not #include <Arduino.h>, must not
//  call millis(), must not call digitalWrite(). The current time
//  is already handed to you through the nowMs parameter. Break
//  this rule and the tests stop running on a PC, and the code
//  stops being portable to the real firmware.
// =============================================================

Navigator::Navigator(const NavConfig& cfg) : cfg_(cfg) {}

void Navigator::start(uint32_t nowMs) {
    // TODO [N1]: Start driving.
    //   - move state_ into Cruise
    //   - reset consecutiveBlocks_ and hadBlock_
    //   Hint: use the enter() helper below.
    (void)nowMs;
}

void Navigator::halt() {
    // TODO [N2]: Stop for good. Move state_ back to Idle.
}

const char* Navigator::stateName() const {
    // TODO [N3]: Return a short label for the current state, used
    //   on the display and in the serial log.
    //   Idle -> "IDLE", Cruise -> "CRUISE",
    //   Backup -> "BACKUP", Turn -> "TURN"
    //   Hint: switch on state_.
    return "?";
}

void Navigator::enter(State s, uint32_t nowMs, uint32_t durationMs) {
    // TODO [N4]: Move into a new state.
    //   - assign state_ = s
    //   - compute phaseEndMs_ = nowMs + durationMs
    //   durationMs == 0 means the state has no deadline: it runs
    //   until some other event moves us out of it (Cruise works
    //   that way).
    (void)s; (void)nowMs; (void)durationMs;
}

void Navigator::registerBlock(uint32_t nowMs) {
    // TODO [N5]: Record that we just hit an obstacle.
    //   If the previous block happened less than cfg_.stuckWindowMs
    //   milliseconds ago, increment consecutiveBlocks_. Otherwise
    //   reset it to 1.
    //   Remember to update lastBlockMs_ and hadBlock_.
    //
    //   This counter is how we notice the robot is wedged in a
    //   corner: many blocks in a short span.
    (void)nowMs;
}

uint32_t Navigator::turnDuration() const {
    // TODO [N6]: Return how long to keep turning.
    //   Normally: cfg_.turnMs
    //   If consecutiveBlocks_ >= cfg_.stuckThreshold (we look
    //   wedged): turn noticeably longer, say three times as long,
    //   so the robot actually escapes instead of oscillating in
    //   the same spot.
    return cfg_.turnMs;
}

NavDecision Navigator::update(int distanceCm, uint32_t nowMs) {
    // TODO [N7]: The main function. These two helpers get you started:
    //
    //   const bool blocked = (distanceCm >= 0 && distanceCm <= cfg_.stopDistanceCm);
    //   const bool nearby  = (distanceCm >= 0 && distanceCm <= cfg_.slowDistanceCm);
    //
    //   Note distanceCm < 0 means the sensor read failed. Treat
    //   that as a clear path, NOT as an obstacle — otherwise the
    //   robot freezes every time the sensor misses a reading.
    //
    //   States to handle:
    //
    //   Idle   -> always return { Stop, 0 }
    //
    //   Cruise -> blocked: call registerBlock(), enter Backup for
    //             cfg_.backupMs, return Backward
    //          -> nearby: still Forward but at cfg_.slowSpeed
    //          -> clear: Forward at cfg_.cruiseSpeed
    //
    //   Backup -> deadline not reached (nowMs < phaseEndMs_):
    //             keep going Backward
    //          -> deadline reached: enter Turn for turnDuration(),
    //             return TurnLeft or TurnRight based on turnLeft_
    //
    //   Turn   -> deadline not reached: keep turning
    //          -> deadline reached: FLIP turnLeft_ for next time,
    //             go back to Cruise, return Forward
    //
    //   Why flip the turn direction: if the robot always turns the
    //   same way, a corner makes it spin in circles forever.
    //
    //   Use cfg_.manoeuvreSpeed while backing up and turning.

    (void)distanceCm; (void)nowMs;
    return { DriveCommand::Stop, 0 };
}

// -------------------------------------------------------------
//  Once all 9 tests pass, move on to the stretch goals in
//  docs/bai-tap.md.
// -------------------------------------------------------------
