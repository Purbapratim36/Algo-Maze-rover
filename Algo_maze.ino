const int leftTrig  = 13;
const int leftEcho  = 12;

const int frontTrig = 11;
const int frontEcho = 10;

const int rightTrig = 9;
const int rightEcho = 8;

// ================= MOTOR PINS ==================
const int motorLeftForward   = 7;
const int motorLeftBackward  = 5;
const int motorRightForward  = 4;
const int motorRightBackward = 2;

const int enableLeft  = 6;   // PWM
const int enableRight = 3;   // PWM

// ================= THRESHOLDS ==================
const int OPEN_LEFT_CM  = 15;
const int OPEN_FRONT_CM = 15;
const int OPEN_RIGHT_CM = 15;

// ================= SPEED =======================
const int SPEED = 150;  // 0–255

// =================================================

void setup() {
  pinMode(leftTrig, OUTPUT);
  pinMode(leftEcho, INPUT);

  pinMode(frontTrig, OUTPUT);
  pinMode(frontEcho, INPUT);

  pinMode(rightTrig, OUTPUT);
  pinMode(rightEcho, INPUT);

  pinMode(motorLeftForward, OUTPUT);
  pinMode(motorLeftBackward, OUTPUT);
  pinMode(motorRightForward, OUTPUT);
  pinMode(motorRightBackward, OUTPUT);

  pinMode(enableLeft, OUTPUT);
  pinMode(enableRight, OUTPUT);

  analogWrite(enableLeft, SPEED);
  analogWrite(enableRight, SPEED);

  Serial.begin(9600);
}

// ================= MAIN LOOP ====================
void loop() {
  int dLeft  = getDistance(leftTrig, leftEcho);
  int dFront = getDistance(frontTrig, frontEcho);
  int dRight = getDistance(rightTrig, rightEcho);

  Serial.print("L="); Serial.print(dLeft);
  Serial.print(" F="); Serial.print(dFront);
  Serial.print(" R="); Serial.println(dRight);

  if (dLeft > OPEN_LEFT_CM) {
    turnLeft();
  }
  else if (dFront > OPEN_FRONT_CM) {
    moveForward();
  }
  else if (dRight > OPEN_RIGHT_CM) {
    turnRight();
  }
  else {
    turnAround();
  }
}

// ================= DISTANCE FUNCTION =============
int getDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000); // 30 ms timeout

  if (duration == 0) return 999; // no echo

  return duration * 0.034 / 2;
}

// ================= MOVEMENTS =====================
void moveForward() {
  digitalWrite(motorLeftForward, HIGH);
  digitalWrite(motorLeftBackward, LOW);
  digitalWrite(motorRightForward, HIGH);
  digitalWrite(motorRightBackward, LOW);
}

void turnLeft() {
  digitalWrite(motorLeftForward, LOW);
  digitalWrite(motorLeftBackward, LOW);
  digitalWrite(motorRightForward, HIGH);
  digitalWrite(motorRightBackward, LOW);
  delay(450);
  stopMotors();
}

void turnRight() {
  digitalWrite(motorLeftForward, HIGH);
  digitalWrite(motorLeftBackward, LOW);
  digitalWrite(motorRightForward, LOW);
  digitalWrite(motorRightBackward, LOW);
  delay(450);
  stopMotors();
}

void turnAround() {
  turnRight();
  delay(100);
  turnRight();
}

void stopMotors() {
  digitalWrite(motorLeftForward, LOW);
  digitalWrite(motorLeftBackward, LOW);
  digitalWrite(motorRightForward, LOW);
  digitalWrite(motorRightBackward, LOW);
}
