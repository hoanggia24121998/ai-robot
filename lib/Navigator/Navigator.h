#pragma once
#include <cstdint>

// =============================================================
//  Navigator — the robot's decision making brain.
//
//  IMPORTANT: this file must NEVER #include <Arduino.h> or any
//  other hardware library. Keeping it hardware-free means:
//    - tests run straight on your PC (pio test -e native)
//    - the code ports to ESP-IDF firmware later without edits
//
//  Navigator does not know motors exist. It takes a distance and
//  a timestamp, and returns ONE decision. Carrying that decision
//  out is somebody else's job.
// =============================================================

enum class DriveCommand : uint8_t {
    Stop,
    Forward,
    Backward,
    TurnLeft,
    TurnRight
};

struct NavDecision {
    DriveCommand command = DriveCommand::Stop;
    uint8_t speed = 0;  // percent, 0..100
};

struct NavConfig {
    int stopDistanceCm   = 20;  // closer than this: back away
    int slowDistanceCm   = 45;  // closer than this: slow down
    uint8_t cruiseSpeed  = 70;
    uint8_t slowSpeed    = 40;
    uint8_t manoeuvreSpeed = 60;  // speed while backing up and turning
    uint32_t backupMs    = 400;
    uint32_t turnMs      = 350;
    int stuckThreshold   = 3;     // blocks in a row before we count as stuck
    uint32_t stuckWindowMs = 3000;
};

class Navigator {
public:
    enum class State : uint8_t { Idle, Cruise, Backup, Turn };

    explicit Navigator(const NavConfig& cfg = NavConfig());

    void start(uint32_t nowMs);
    void halt();
    bool running() const { return state_ != State::Idle; }
    State state() const { return state_; }
    const char* stateName() const;

    // Call this on every tick.
    // distanceCm < 0 means the read failed: treat the path as clear.
    NavDecision update(int distanceCm, uint32_t nowMs);

private:
    void enter(State s, uint32_t nowMs, uint32_t durationMs);
    void registerBlock(uint32_t nowMs);
    uint32_t turnDuration() const;

    NavConfig cfg_;
    State state_ = State::Idle;
    uint32_t phaseEndMs_ = 0;
    bool turnLeft_ = true;
    int consecutiveBlocks_ = 0;
    uint32_t lastBlockMs_ = 0;
    bool hadBlock_ = false;
};
