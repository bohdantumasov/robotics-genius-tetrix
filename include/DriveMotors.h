#ifndef DRIVE_MOTORS_H
#define DRIVE_MOTORS_H

#include <PRIZM_PRO.h>

namespace DriveMotors
{
constexpr uint8_t RIGHT_BACK = 1;
constexpr uint8_t RIGHT_FRONT = 2;
constexpr uint8_t LEFT_FRONT = 3;
constexpr uint8_t LEFT_BACK = 4;

// Assumes mirrored motor mounting and matching wire polarity on each side.
// Toggle an individual value if that wheel runs backward during a forward test.
constexpr bool RIGHT_BACK_INVERTED = false;
constexpr bool RIGHT_FRONT_INVERTED = false;
constexpr bool LEFT_FRONT_INVERTED = true;
constexpr bool LEFT_BACK_INVERTED = true;

constexpr int16_t BRAKE_POWER = 125;

inline int16_t brakeWhenStopped(int16_t power)
{
  return power == 0 ? BRAKE_POWER : power;
}

// Standard X roller layout. Positive commands: forward, right, clockwise.
// All inputs are percentages. Normalize together to preserve wheel ratios.
inline void setMotion(PRIZM &prizm, int16_t forward, int16_t strafe,
                      int16_t turn, int16_t maxPower = 100)
{
  forward = constrain(forward, -100, 100);
  strafe = constrain(strafe, -100, 100);
  turn = constrain(turn, -100, 100);
  maxPower = constrain(maxPower, 0, 100);

  const int rightBack = forward + strafe - turn;
  const int rightFront = forward - strafe - turn;
  const int leftFront = forward + strafe + turn;
  const int leftBack = forward - strafe + turn;
  const int scale = max(100, max(max(abs(rightBack), abs(rightFront)),
                                 max(abs(leftFront), abs(leftBack))));
  // PRIZM channel order: right back, right front, left front, left back.
  prizm.setMotorPowers(brakeWhenStopped(rightBack * maxPower / scale),
                       brakeWhenStopped(rightFront * maxPower / scale),
                       brakeWhenStopped(leftFront * maxPower / scale),
                       brakeWhenStopped(leftBack * maxPower / scale));
}

inline void stop(PRIZM &prizm)
{
  prizm.setMotorPowers(BRAKE_POWER, BRAKE_POWER, BRAKE_POWER, BRAKE_POWER);
}

// Call after PrizmBegin(), which resets the motor controller.
inline void begin(PRIZM &prizm)
{
  stop(prizm);
  prizm.setMotorInvert(RIGHT_BACK, RIGHT_BACK_INVERTED);
  prizm.setMotorInvert(RIGHT_FRONT, RIGHT_FRONT_INVERTED);
  prizm.setMotorInvert(LEFT_FRONT, LEFT_FRONT_INVERTED);
  prizm.setMotorInvert(LEFT_BACK, LEFT_BACK_INVERTED);
}
} // namespace DriveMotors

#endif
