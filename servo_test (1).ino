// RoboDog four-servo diagnostic test.
// Disconnect the legs or support the robot before the first test.

const int FL_PIN = 4;   // Front Left
const int FR_PIN = 16;  // Front Right - mirrored
const int RL_PIN = 22;  // Rear Left
const int RR_PIN = 25;  // Rear Right - mirrored

uint32_t angleToDuty(int angle) {
  angle = constrain(angle, 0, 180);
  int pulseUs = map(angle, 0, 180, 500, 2500);
  return ((uint32_t)pulseUs * 65535UL) / 20000UL;
}

void writeLogicalAngle(int pin, int logicalAngle) {
  logicalAngle = constrain(logicalAngle, 40, 140);

  int physicalAngle = logicalAngle;
  if (pin == FR_PIN || pin == RR_PIN) {
    physicalAngle = 180 - logicalAngle;
  }

  ledcWrite(pin, angleToDuty(physicalAngle));
}

void standAll() {
  writeLogicalAngle(FL_PIN, 90);
  writeLogicalAngle(FR_PIN, 90);
  writeLogicalAngle(RL_PIN, 90);
  writeLogicalAngle(RR_PIN, 90);
}

void testOneServo(const char* name, int pin) {
  Serial.print("Testing: ");
  Serial.println(name);

  writeLogicalAngle(pin, 70);
  delay(1200);

  writeLogicalAngle(pin, 110);
  delay(1200);

  writeLogicalAngle(pin, 90);
  delay(1000);
}

void setup() {
  Serial.begin(115200);

  ledcAttach(FL_PIN, 50, 16);
  ledcAttach(FR_PIN, 50, 16);
  ledcAttach(RL_PIN, 50, 16);
  ledcAttach(RR_PIN, 50, 16);

  standAll();
  delay(2500);

  Serial.println("RoboDog servo test started");
}

void loop() {
  testOneServo("Front Left - GPIO4", FL_PIN);
  testOneServo("Front Right - GPIO16", FR_PIN);
  testOneServo("Rear Left - GPIO22", RL_PIN);
  testOneServo("Rear Right - GPIO25", RR_PIN);

  standAll();
  Serial.println("Test cycle complete");
  delay(3000);
}

