# ESP32 RoboDog Web Control

A web-controlled robotic dog built using an ESP32 and four SG90 servo motors. The ESP32 operates as a Wi-Fi Access Point and hosts a responsive control interface that can be opened from a phone or laptop without requiring an internet connection.

This project is a developed version of the original ESP32 web-controlled servo task. Instead of implementing the first task as a separate final project, its main concept was expanded and adapted to control a four-legged robotic dog.

The original task used one servo motor with `Open` and `Close` buttons. The developed system controls four servo motors, provides individual limb testing and calibration, and includes multiple programmed robotic movements.

## Video Link

https://lnkd.in/p/dxVHCGp7

## Project Overview

The project combines:

* ESP32 programming.
* Wi-Fi Access Point mode.
* Embedded web-server development.
* HTML, CSS, and JavaScript.
* Four SG90 servo motors.
* Manual servo calibration.
* Robotic movement programming.
* Mechanical alignment.
* Hardware testing and troubleshooting.
* A custom 3D-printed robotic-dog body.

The phone or laptop connects directly to the ESP32 network and opens the control interface using:

```text
http://192.168.4.1
```

The control interface sends HTTP commands to the ESP32. The ESP32 then generates PWM signals that control the four servo motors.

---

## Original Task Requirement

The original task required the ESP32 to:

* Operate as a Wi-Fi Access Point.
* Host a local web-control page.
* Provide `Open` and `Close` buttons.
* Control one servo motor.
* Turn on a green LED in the Open state.
* Turn on a red LED in the Close state.

### Original System Flow

```text
Phone / Laptop
      |
      | Wi-Fi connection
      v
ESP32 Access Point
      |
      | Local web page
      v
Open / Close buttons
      |
      +----> Servo motor
      +----> Green / Red LEDs
```

---

## Development of the Original Task

The original task was not implemented as a separate final project. It was developed and adapted to the robotic dog.

The following changes were made:

| Original task            | Developed RoboDog system                           |
| ------------------------ | -------------------------------------------------- |
| One servo motor          | Four SG90 servo motors                             |
| Open and Close buttons   | Movement and calibration controls                  |
| One servo position       | Independent control of four limbs                  |
| Green and red LED states | Live angle values and movement status              |
| Basic web page           | Responsive RoboDog control interface               |
| Simple servo movement    | Forward, backward, handshake and dance experiments |
| ESP32 Access Point       | ESP32 Access Point retained                        |
| Local browser control    | Phone and laptop control retained                  |

The final project therefore preserves the main objective of the original task while demonstrating it through a more advanced robotic application.

---

## Final RoboDog System

The final system includes:

* Four-servo control.
* Independent limb testing.
* Manual servo-angle sliders.
* A calibrated standing position.
* Forward movement.
* Backward movement.
* Handshake movement.
* Dance movement.
* Sit movement.
* Bow movement.
* Automatic return to the standing position.
* Direct control without internet access.
* A responsive web interface.

---

## System Architecture

```text
Phone / Laptop
      |
      | Wi-Fi connection
      v
ESP32 Access Point
192.168.4.1
      |
      | HTTP commands
      v
ESP32 Web Server
      |
      | LEDC PWM signals
      v
Four SG90 Servo Motors
      |
      v
Front and Rear Robot Limbs
```

---

## Hardware Components

| Component                          |    Quantity | Purpose                                |
| ---------------------------------- | ----------: | -------------------------------------- |
| ESP32                              |           1 | Main controller and Wi-Fi Access Point |
| Arduino Uno or regulated 5V supply |           1 | Servo power during testing             |
| SG90 servo motor                   |           4 | Controls the robot limbs               |
| Breadboard                         |           1 | Power and ground distribution          |
| Jumper wires                       | As required | Electrical connections                 |
| Electrolytic capacitor             |           1 | Helps reduce brief voltage drops       |
| USB cables                         |           2 | ESP32 programming and power            |
| 3D-printed RoboDog body            |           1 | Mechanical robot structure             |
| 3D-printed legs                    |           4 | Front and rear robot limbs             |

---

## Servo Pin Mapping

| Robot limb       | ESP32 GPIO | Standing angle | Direction |
| ---------------- | ---------: | -------------: | --------- |
| Front Left — FL  |      GPIO4 |     90 degrees | Normal    |
| Front Right — FR |     GPIO16 |     90 degrees | Mirrored  |
| Rear Left — RL   |     GPIO22 |     90 degrees | Normal    |
| Rear Right — RR  |     GPIO25 |     90 degrees | Mirrored  |

The right-side servos are installed as mirror images of the left-side servos. Their movement directions are therefore reversed in software.

The standing position remains 90 degrees for all four servos because:

```text
180 - 90 = 90
```

---

## Servo Wiring

Each SG90 servo contains three wires:

| Servo wire       | Connection          |
| ---------------- | ------------------- |
| Orange or yellow | Assigned ESP32 GPIO |
| Red              | Regulated 5V supply |
| Brown or black   | Common GND          |

### Power Connections

```text
Servo red wires       ---> 5V power rail
Servo brown wires     ---> GND rail
Arduino Uno 5V        ---> 5V power rail
Arduino Uno GND       ---> GND rail
ESP32 GND             ---> Same GND rail
Servo signal wires    ---> GPIO4, GPIO16, GPIO22 and GPIO25
```

A common ground between the ESP32 and the servo power supply is essential. Without a common ground, the PWM signal does not have a shared electrical reference.

> The four servo motors must not be powered from the ESP32 3.3V pin. A regulated external 5V supply with sufficient current is recommended.

---

## Wi-Fi Access Point

The ESP32 creates its own local Wi-Fi network.

| Setting         | Value                 |
| --------------- | --------------------- |
| Network name    | `RoboDog-Control`     |
| Password        | `12345678`            |
| Control address | `http://192.168.4.1`  |
| Wi-Fi mode      | Access Point / SoftAP |

### Connection Steps

1. Power the ESP32.
2. Power the servo motors.
3. Open Wi-Fi settings on the phone or laptop.
4. Connect to `RoboDog-Control`.
5. Enter `12345678`.
6. Open a web browser.
7. Visit `http://192.168.4.1`.
8. Press the Stand button first.
9. Test the manual sliders.
10. Test one programmed movement at a time.

---

## Web Control Interface

<img width="584" height="430" alt="RopotDogConorl" src="https://github.com/user-attachments/assets/9fd96afc-237d-4cf5-8bfe-0b84d358734a" />
<img width="646" height="417" alt="image" src="https://github.com/user-attachments/assets/113631a0-e93b-4fa7-bb53-29ee1440f7cc" />


The developed interface includes:

* Forward button.
* Backward button.
* Handshake button.
* Dance button.
* Sit button.
* Bow button.
* Stand button.
* Four independent servo sliders.
* Current-angle indicators.
* Movement-status messages.

The manual sliders were especially useful during development because they allowed every limb to be tested separately before attempting coordinated movements.

---

## Servo Control Method

The project uses the ESP32 LEDC peripheral to generate PWM signals.

```cpp
ledcAttach(pin, 50, 16);
ledcWrite(pin, duty);
```

The servo angle is converted into an approximate pulse width between 500 and 2500 microseconds.

The SG90 servo motors use a PWM frequency of approximately 50 Hz.

The project uses the newer ESP32 Core 3.x LEDC API instead of relying on the standard Arduino `Servo.h` implementation.

---

## Mechanical Calibration

Software angles alone cannot create a stable standing position if the servo horns are installed incorrectly.

### Calibration Procedure

1. Disconnect the servo power.
2. Remove or loosen the servo horns.
3. Upload a program that commands all servos to 90 degrees.
4. Reconnect the servo power.
5. Wait until every servo reaches its center position.
6. Disconnect the power again.
7. Install the four legs in a stable standing position.
8. Make the right-side legs mirror the left-side legs.
9. Tighten the screws gently.
10. Reconnect power.
11. Test the Stand command while supporting the robot body.

If a leg points upward when the software angle is 90 degrees, the problem is usually the mechanical horn position rather than the programmed angle.

---

## Standing Position

The final logical standing position is:

```cpp
Front Left  = 90;
Front Right = 90;
Rear Left   = 90;
Rear Right  = 90;
```

Every programmed movement returns the robot to this position after completion.

The physical appearance of 90 degrees depends on how each servo horn is attached to the servo gear.

---

## Programmed Movements

### Stand

Returns all four logical servo angles to 90 degrees.

### Forward

Alternates the diagonal limb pairs:

```text
Front Left + Rear Right
then
Front Right + Rear Left
```

### Backward

Runs the diagonal movement sequence in the opposite direction.

### Handshake

Moves one front limb while the other three limbs support the robot body.

A small weight shift is used before moving the front limb.

### Dance

Alternates small mirrored angle changes between the left and right sides.

### Sit

Changes the relationship between the front and rear angles before returning to standing.

### Bow

Moves the front and rear limbs in opposite directions and then returns to the standing position.

---

## Testing Procedure

The project was tested in several stages.

### Stage 1: Upload Test

The ESP32 firmware was compiled and uploaded through Arduino IDE.

### Stage 2: Single-Servo Test

One SG90 servo was connected to GPIO4 and tested using several angles.

### Stage 3: Individual Limb Test

Every servo was tested independently:

```text
GPIO4  — Front Left
GPIO16 — Front Right
GPIO22 — Rear Left
GPIO25 — Rear Right
```

### Stage 4: Manual Web Control

The sliders were used to verify:

* Servo response.
* Movement direction.
* Safe angle limits.
* Right-side inversion.
* Standing-position calibration.

### Stage 5: Coordinated Movement Test

The programmed movements were tested one at a time while supporting the robot body.

### Stage 6: Final Demonstration

The following movements can be recorded for the final submission:

1. Forward movement.
2. Backward movement.
3. Handshake or dance movement.

---

## Problems Encountered and Solutions

### 1. ESP32 Failed to Upload on COM3

The following error appeared:

```text
Failed to connect to ESP32:
No serial data received.
```

#### Cause

COM3 belonged to the Arduino Uno rather than the ESP32.

#### Solution

The ESP32 was identified on COM4, and the firmware uploaded successfully.

Successful output included:

```text
Connected to ESP32 on COM4
Hash of data verified
Hard resetting via RTS pin
```

---

### 2. Servo Motors Did Not Move

The firmware uploaded successfully, but the servos did not move or produce any sound.

#### Possible Causes

* Incorrect 5V connection.
* Arduino power wire connected to the wrong pin.
* Missing common ground.
* Loose breadboard connection.
* Insufficient current.
* Incorrect signal GPIO.

#### Solution

The Arduino power wire was found to be connected incorrectly. After correcting the 5V and GND wiring, the servos began responding.

The corrected power connections were:

```text
Arduino 5V  ---> Breadboard positive rail
Arduino GND ---> Breadboard negative rail
ESP32 GND   ---> Same negative rail
```

---

### 3. Manual Sliders Worked but Movement Buttons Did Not

The servos responded through the manual sliders, but the programmed movement buttons did not produce an obvious response.

#### Possible Causes

* Cached web interface.
* Movement angles were too small.
* The HTTP response was sent before movement completion.
* The new firmware page was not refreshed.

#### Solution

* Cache-prevention headers were added.
* A timestamp was added to every HTTP request.
* The interface was opened with a version parameter:

```text
http://192.168.4.1/?v=3
```

* HTTP routes were changed to execute the movement before sending the completion response.
* Larger temporary test angles were used to confirm movement.

---

### 4. Right-Side Legs Moved in the Wrong Direction

The right-side servo motors were mounted as mirror images of the left-side motors.

#### Solution

GPIO16 and GPIO25 were reversed in software:

```cpp
if (pin == FR_PIN || pin == RR_PIN) {
  physicalAngle = 180 - logicalAngle;
}
```

---

### 5. Legs Pointed Upward at 90 Degrees

Some legs pointed upward while others pointed downward when all servo motors were commanded to 90 degrees.

#### Cause

The servo horns were installed at different positions on the servo gears.

Software inversion cannot change the 90-degree position because:

```text
180 - 90 = 90
```

#### Solution

The horns were removed and reinstalled after centering every servo at 90 degrees.

---

### 6. Robot Fell During the Handshake

The robot became unstable when one front leg was moved.

#### Causes

* Weight shifted toward the moving limb.
* Supporting limbs were not correctly calibrated.
* Handshake angle was too large.
* Robot feet had limited grip.
* Body weight was not centered.

#### Solution

* The handshake angle range was reduced.
* A small balance shift was added.
* Servo movement was slowed.
* The robot returned to 90 degrees after the movement.
* The body was supported during early tests.

---

### 7. Robot Fell During Walking or Dancing

#### Causes

* Sudden servo movement.
* Large angle differences.
* Incorrect mechanical centering.
* Uneven leg installation.
* Weak servo power supply.
* Smooth table surface.

#### Solution

A smooth four-servo movement function was implemented so all servos move gradually.

Movement angles were reduced, and every movement returns to:

```text
90, 90, 90, 90
```

Rubber grip can also be added to the robot feet.

---

### 8. Weak USB Power or ESP32 Restart

Running several servo motors from a weak USB source can cause:

* Servo jitter.
* ESP32 restart.
* Wi-Fi disconnection.
* Incomplete servo movement.
* Unstable movement.

#### Solution

A regulated external 5V supply with sufficient current should be used.

A capacitor may be connected across the servo 5V and GND rails to reduce brief voltage drops.

---

### 9. Servo Screws Were Too Tight

Overtightened screws can:

* Restrict movement.
* Increase servo load.
* Cause buzzing.
* Increase current consumption.
* Damage servo gears.

#### Solution

The screws should be secure but not excessively tight. The legs must move without mechanical obstruction.

---

### 10. Servo Buzzing or Heating

A servo may buzz if it is trying to reach a position blocked by the mechanical structure.

#### Solution

* Disconnect power.
* Check the servo-horn position.
* Check for mechanical obstruction.
* Reduce the movement range.
* Avoid forcing the servo by hand while it is powered.

---

### 11. Robot Slid Instead of Walking

#### Causes

* Limited grip on the feet.
* Smooth table surface.
* Small movement angles.
* One-servo-per-leg mechanical design.
* Diagonal walking sequence.

#### Solution

* Repeat the Forward command.
* Add rubber grip to the feet.
* Test on a non-slip surface.
* Tune movement angles gradually.
* Avoid sudden large angle changes.

---

### 12. Arabic Characters Caused Compilation Errors

The following error appeared:

```text
extended character is not valid in an identifier
```

The compiler identified Arabic text, arrows, emoji, and degree symbols as invalid identifiers.

#### Cause

The HTML content was outside the C++ raw string because multiple code versions had been pasted together or the raw-string delimiters were incomplete.

#### Solution

* A new Arduino sketch was created.
* All old code was deleted.
* Only one complete version was pasted.
* The HTML page was placed between:

```cpp
const char PAGE[] PROGMEM = R"rawliteral(
```

and:

```cpp
)rawliteral";
```

The interface text was also changed to English to reduce encoding problems.

---

### 13. Old Interface Continued to Appear

The browser sometimes displayed an older web interface after new firmware was uploaded.

#### Cause

Browser caching.

#### Solution

* Closed and reopened the page.
* Added cache-control headers.
* Used a version parameter:

```text
http://192.168.4.1/?v=3
```

---

### 14. Servo Was Easy to Move by Hand While Powered

A powered servo normally resists manual movement.

If it moves freely, it may not be receiving correct power.

#### Solution

Check:

* 5V supply.
* GND connection.
* Common ground.
* Breadboard continuity.
* Connector direction.
* Power-supply current.

A powered servo should not be forced manually.

---

## Repository Structure

```text
ESP32-RoboDog-Web-Control/
|
|-- README.md
|
|-- firmware/
|   |
|   |-- servo_test/
|   |   `-- servo_test.ino
|   |
|   `-- robodog_web_control/
|       `-- robodog_web_control.ino
|
|-- images/
|   |-- esp32-wiring.jpg
|   |-- robodog-standing.jpg
|   |-- servo-testing.jpg
|   `-- web-control-interface.jpg
|
`-- videos/
    `-- README.md
```

The repository does not include a separate final implementation of the original single-servo task because that task was developed directly into the RoboDog system.

---

## How to Run

### Arduino IDE

1. Install Arduino IDE.
2. Install the ESP32 board package.
3. Select the correct ESP32 board.
4. Select COM4 or the port assigned to the ESP32.
5. Open `robodog_web_control.ino`.
6. Verify the code.
7. Upload the firmware.
8. Wait for:

```text
Hard resetting via RTS pin
```

### Robot Control

1. Power the ESP32.
2. Power the servo motors.
3. Connect the phone to `RoboDog-Control`.
4. Open `http://192.168.4.1`.
5. Press Stand first.
6. Test each slider.
7. Test one programmed movement at a time.

---

## Safety Notes

* Support the robot during the first test.
* Disconnect power before adjusting servo horns.
* Do not power the servos from the ESP32 3.3V pin.
* Always connect a common ground.
* Do not force powered servos manually.
* Stop testing if a servo becomes hot.
* Avoid overtightening the screws.
* Confirm the standing position before testing movements.
* Begin with small angle changes.

---

## Project Images

### Hardware Wiring

<img width="753" height="667" alt="ESP32 and servo wiring" src="https://github.com/user-attachments/assets/d2ff6305-4389-40c3-94dd-d5497d725223" />

### Servo Testing

<img width="1206" height="966" alt="Servo Testing" src="https://github.com/user-attachments/assets/527ab240-4a89-4778-ac26-616c55c1329f" />

### Standing Position
<img width="1206" height="1098" alt="Standing Position" src="https://github.com/user-attachments/assets/41bbae40-2b0c-4c5e-b014-54b2e14fc261" />


## Skills Developed

* ESP32 programming.
* Arduino IDE configuration.
* Wi-Fi Access Point configuration.
* Embedded web-server development.
* HTML, CSS, and JavaScript.
* HTTP command handling.
* SG90 servo control.
* PWM generation using LEDC.
* Servo calibration.
* Hardware wiring.
* Power-distribution testing.
* Mechanical alignment.
* Troubleshooting.
* Integration of software, electronics, and mechanical design.

---

## Results

The original web-controlled servo task was successfully developed and adapted into a robotic-dog control and testing system rather than being implemented as a separate final project.

The ESP32 preserves the original requirement by operating as a Wi-Fi Access Point and hosting a local web interface. The original single-servo Open/Close concept was expanded into four-servo control for the robot's front and rear limbs.

The developed interface supports individual limb testing, servo calibration, a 90-degree standing position, and multiple programmed movement experiments.

The project demonstrates how a basic embedded-systems task can be expanded into a practical robotic application integrating:

* Mechanical design.
* 3D printing.
* Embedded programming.
* Servo control.
* Wireless communication.
* Web development.
* Hardware testing and troubleshooting.

The most important lesson from this project was that stable robotic movement depends on both software and mechanical calibration. Correct software angles cannot compensate for incorrectly installed servo horns, insufficient power, uneven weight distribution, or limited foot grip.

---

## Future Improvements

* Use a dedicated regulated 5V power supply.
* Add a PCA9685 servo driver.
* Add rubber grip to the robot feet.
* Improve the walking gait.
* Implement non-blocking movements.
* Add a real emergency-stop function.
* Add battery operation.
* Add an ultrasonic sensor.
* Add Bluetooth or MQTT control.
* Add voice-command support.
* Add an IMU for balance monitoring.
* Save calibration values permanently.
* Improve body weight distribution.

---

## References

* [Arduino ESP32 Wi-Fi API — Espressif](https://docs.espressif.com/projects/arduino-esp32/en/latest/api/wifi.html)
* [Arduino ESP32 LEDC API — Espressif](https://docs.espressif.com/projects/arduino-esp32/en/latest/api/ledc.html)
* [Arduino IDE](https://www.arduino.cc/en/software)
* [Wokwi ESP32 Simulator](https://wokwi.com/)

---

## Author

**Wafaa Abdullah Al-Luhaidan**
Information Technology Student
Qassim University

