#include <Arduino.h>
#include <PRIZM_PRO.h>
#include <XboxSeriesXControllerESP32_asukiaaa.hpp>
#include "DriveMotors.h"

PRIZM prizm;
XboxSeriesXControllerESP32_asukiaaa::Core xbox;

namespace
{
constexpr int MAX_POWER = 80;
constexpr int DEAD_ZONE = 4000;
constexpr uint32_t CONTROL_INTERVAL_MS = 20;
bool armed = false;
bool wasReady = false;
uint32_t lastControlAt = 0;
int stickPercent(uint16_t value)
{
  const int centered = static_cast<int>(value) - 32768;
  const int magnitude = abs(centered);
  if (magnitude <= DEAD_ZONE) return 0;
  const int endpoint = centered < 0 ? 32768 : 32767;
  const int scaled = (magnitude - DEAD_ZONE) * 100 / (endpoint - DEAD_ZONE);
  return centered < 0 ? -scaled : scaled;
}

bool inputReady()
{
  // Keep the last stick position while BLE remains connected. A gap between
  // input reports is not a disconnect and must not disarm the drive.
  return xbox.isConnected() && !xbox.isWaitingForFirstNotification() &&
         xbox.getReceiveNotificationAt() != 0;
}
}

void setup()
{
  Serial.begin(115200);
  Serial.println("Press the PRIZM green Start button to enable the motor controller.");
  // Ініціалізація контролера й очікування зеленої кнопки Start
  prizm.PrizmBegin();
  DriveMotors::begin(prizm);
  xbox.begin();
  Serial.println("Xbox BLE: hold the controller Pair button until the logo flashes.");
}

void loop()
{
  // Stop before onLoop(): reconnect and service discovery can block.
  if (!inputReady())
  {
    DriveMotors::stop(prizm);
    armed = false;
  }
  xbox.onLoop();

  const uint32_t now = millis();
  if (now - lastControlAt < CONTROL_INTERVAL_MS)
  {
    delay(1);
    return;
  }
  lastControlAt = now;

  const bool ready = inputReady();
  if (ready != wasReady)
  {
    Serial.println(ready ? "Xbox input ready." : "Xbox input lost: motors stopped.");
    prizm.setGreenLED(ready);
    prizm.setRedLED(!ready);
    wasReady = ready;
  }
  if (!ready)
  {
    DriveMotors::stop(prizm);
    armed = false;
    return;
  }

  const int forward = -stickPercent(xbox.xboxNotif.joyLVert);
  const int strafe = stickPercent(xbox.xboxNotif.joyRHori);
  const int turn = stickPercent(xbox.xboxNotif.joyLHori);
  if (xbox.xboxNotif.btnB)
  {
    DriveMotors::stop(prizm);
    armed = false;
    return;
  }
  if (!armed && forward == 0 && strafe == 0 && turn == 0)
  {
    armed = true;
    Serial.println("Mecanum drive armed. Left stick: forward/reverse and turn. Right stick X: strafe (maximum 80%).");
  }
  if (!armed)
  {
    DriveMotors::stop(prizm);
    return;
  }

  DriveMotors::setMotion(prizm, forward, strafe, turn, MAX_POWER);
}
