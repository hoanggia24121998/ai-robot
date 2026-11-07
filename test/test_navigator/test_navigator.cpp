// =============================================================
//  Navigation logic tests — run on your PC, no hardware needed.
//      pio test -e native
//
//  TWO of these tests are written for you as worked examples.
//  SEVEN are left for you to write. Each one has the requirement
//  spelled out above it; your job is turning that sentence into
//  code.
//
//  Write the test FIRST, watch it fail, then make Navigator pass
//  it. That order matters: a test you write after the code tends
//  to just describe whatever the code already does, bugs included.
//
//  How to write one: see "Cach viet test" in docs/bai-tap.md.
// =============================================================

#include <unity.h>
#include "Navigator.h"

void setUp() {}
void tearDown() {}

// Shared configuration so every test starts from the same numbers.
// Thresholds: stop under 20cm, slow under 45cm, backup lasts 400ms,
// a turn lasts 350ms.
static NavConfig cfg() {
    NavConfig c;
    c.stopDistanceCm = 20;
    c.slowDistanceCm = 45;
    c.cruiseSpeed = 70;
    c.slowSpeed = 40;
    c.manoeuvreSpeed = 60;
    c.backupMs = 400;
    c.turnMs = 350;
    return c;
}

// =============================================================
//  WORKED EXAMPLE 1 — the simple shape of a test.
//
//  Requirement: before start() is called, the robot sits still.
//
//  Notice the three steps, in order:
//    arrange — build the object under test
//    act     — call the thing you want to check
//    assert  — state what must be true
// =============================================================
void test_idle_until_started() {
    Navigator n(cfg());                        // arrange

    NavDecision d = n.update(100, 1000);       // act

    TEST_ASSERT_FALSE(n.running());            // assert
    TEST_ASSERT_TRUE(d.command == DriveCommand::Stop);
    TEST_ASSERT_EQUAL_UINT8(0, d.speed);
}

// =============================================================
//  WORKED EXAMPLE 2 — testing something that depends on time.
//
//  Requirement: backing up lasts backupMs (400ms), and when that
//  window closes the robot starts turning.
//
//  Navigator never calls millis(). You hand it the time yourself,
//  which is exactly what lets you skip 400ms forward instantly
//  instead of waiting for it.
//
//  Note how the test checks BOTH sides of the boundary: still
//  backing up at t=300, already turning at t=600. Checking only
//  one side would miss an off-by-one error.
// =============================================================
void test_backup_is_followed_by_turn() {
    Navigator n(cfg());
    n.start(0);
    n.update(10, 100);                         // obstacle at t=100, backup begins

    NavDecision during = n.update(10, 300);    // t=300, still inside the window
    TEST_ASSERT_TRUE(during.command == DriveCommand::Backward);

    NavDecision after = n.update(10, 600);     // 100 + 400 = 500, window closed
    TEST_ASSERT_TRUE(after.command == DriveCommand::TurnLeft ||
                     after.command == DriveCommand::TurnRight);
    TEST_ASSERT_TRUE(n.state() == Navigator::State::Turn);
}

// =============================================================
//  YOUR TURN — seven tests to write.
//  Delete the TEST_ASSERT_TRUE(false) line once each one is real.
// =============================================================

// TODO [T1]: With a clear path ahead (say 200cm), the robot drives
//   Forward at cruiseSpeed (70).
void test_clear_path_runs_at_cruise_speed() {
    TEST_ASSERT_TRUE(false);  // delete this line and write the test
}

// TODO [T2]: With an obstacle in the middle distance (say 40cm:
//   inside slowDistanceCm but outside stopDistanceCm), the robot
//   keeps going Forward but drops to slowSpeed (40).
void test_nearby_obstacle_slows_down() {
    TEST_ASSERT_TRUE(false);
}

// TODO [T3]: A failed sensor read is reported as -1. The robot must
//   treat that as a clear path and keep cruising, NOT stop.
//
//   Why this test earns its place: without it, the obvious
//   implementation "distance <= 20 means blocked" makes -1 count as
//   an obstacle, and the robot freezes every time the sensor misses
//   a reading. That is a real bug and this test catches it.
void test_failed_read_counts_as_clear() {
    TEST_ASSERT_TRUE(false);
}

// TODO [T4]: An obstacle inside stopDistanceCm (say 10cm) makes the
//   robot reverse immediately, and its state becomes Backup.
//   Check both the returned command and n.state().
void test_blocked_backs_up_immediately() {
    TEST_ASSERT_TRUE(false);
}

// TODO [T5]: A turn lasts turnMs (350ms). Once that window closes
//   the robot returns to Cruise and drives Forward again.
//
//   Hint: to reach the Turn state you first have to go through
//   Backup, the same way worked example 2 does.
void test_turn_is_followed_by_cruise() {
    TEST_ASSERT_TRUE(false);
}

// TODO [T6]: Two obstacles in a row must produce turns in OPPOSITE
//   directions.
//
//   Why it matters: if the robot always turns the same way, a
//   corner traps it spinning in circles forever.
//
//   Hint: drive through the whole backup-turn-cruise cycle twice,
//   keep the command from each turn, and assert the two differ.
void test_turn_direction_alternates() {
    TEST_ASSERT_TRUE(false);
}

// TODO [T7]: halt() stops the robot from any state. After calling
//   it, update() returns Stop and running() is false.
void test_halt_stops_everything() {
    TEST_ASSERT_TRUE(false);
}

// TODO [T8] (optional, harder): write a test of your own for
//   something none of the above covers. Some ideas:
//     - exactly at the threshold: is 20cm blocked or not?
//     - calling start() twice in a row
//     - update() called with a time that goes backwards
//   A good test has a name that states the behaviour, and checks
//   one thing. If you need "and" in the name, split it in two.

int main(int, char**) {
    UNITY_BEGIN();
    RUN_TEST(test_idle_until_started);
    RUN_TEST(test_backup_is_followed_by_turn);
    RUN_TEST(test_clear_path_runs_at_cruise_speed);
    RUN_TEST(test_nearby_obstacle_slows_down);
    RUN_TEST(test_failed_read_counts_as_clear);
    RUN_TEST(test_blocked_backs_up_immediately);
    RUN_TEST(test_turn_is_followed_by_cruise);
    RUN_TEST(test_turn_direction_alternates);
    RUN_TEST(test_halt_stops_everything);
    return UNITY_END();
}
