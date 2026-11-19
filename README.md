# TETRIX PRIZM PRO Xbox drive

PlatformIO project for the ESP32-S3 PRIZM PRO. Uses a BLE Xbox Series X/S
controller (model 1914). Other models have not been verified. Older controllers
using Bluetooth Classic cannot connect directly to the ESP32-S3.

## Motors

| Channel | Wheel | Inverted |
| --- | --- | --- |
| 1 | Right back | No |
| 2 | Right front | No |
| 3 | Left front | Yes |
| 4 | Left back | Yes |

Direction assumes mirrored mounting. Check with wheels raised and change the
individual inversion constants in `include/DriveMotors.h` if needed.

## Mecanum wheels

The mixer assumes standard mecanum wheels with roller axes forming an X when
viewed from above. Motor direction settings remain independent of roller layout.
Commands are relative to the robot: forward, sideways right, and clockwise turn.
Each wheel gets a separate command; combined commands are normalized together
to keep every motor within 100% while preserving their ratios.

| Motion | Ch1 right back | Ch2 right front | Ch3 left front | Ch4 left back |
| --- | --- | --- | --- | --- |
| Forward | + | + | + | + |
| Right sideways | + | - | + | - |
| Clockwise turn | - | - | + | + |

Signs are logical wheel commands before configured motor inversion.
Reference: https://github.wpilib.org/allwpilib/docs/release/cpp/classfrc_1_1_mecanum_drive.html

## Connect and drive

1. Build and upload with PlatformIO (`pio run -t upload`).
2. Open the serial monitor at 115200 baud (`pio device monitor`).
3. Press the PRIZM green Start button. Initialization waits for this button before
   starting Bluetooth, and all motors start stopped.
4. Turn on the Xbox controller. Hold its Pair button until the Xbox logo flashes.
   The robot scans automatically; no phone, USB cable, or Xbox receiver is needed.
   Disconnect the controller from a nearby console or computer if it reconnects there.
5. Wait for `Xbox input ready.` Center both sticks to arm.
6. Left stick up/down drives forward/reverse; left/right turns the robot.
   Diagonal left-stick positions combine forward/reverse motion and turning.
   Right stick left/right moves sideways; its vertical axis is unused. Translation and
   rotation can be combined. No RB button is required. Center both sticks to
   stop. B also stops and requires centering both sticks before driving resumes.

Maximum power is 80%, set by `MAX_POWER` in `src/main.cpp`. Stick travel controls
power proportionally. Holding the stick keeps the current command active without
requiring repeated input reports. A BLE disconnect stops the motors when reported
by the Bluetooth stack and requires centering both sticks again after reconnecting.
There is no 500 ms input-report timeout: report silence alone does not indicate
a lost connection. Each wheel brakes whenever its calculated power is zero,
including stops and disconnects, using the PRIZM brake command (125).
The green pixel indicates
a connected controller with input received; red indicates input was lost.
A successful build does not verify physical pairing or motor direction.

## Libraries

- Bundled TETRIX PRIZM PRO 1.15.
- XboxSeriesXControllerESP32_asukiaaa 1.1.3 and NimBLE-Arduino 2.5.2.
- Xbox parser and HID report builder are installed as transitive dependencies.

Controller library: https://github.com/asukiaaa/arduino-XboxSeriesXControllerESP32

ESP32-S3/controller protocol compatibility:
https://bluepad32.readthedocs.io/en/latest/FAQ/
