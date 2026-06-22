// ----------------- IR SENSOR ARRAY -----------------
const int sensorPins[6] = {A0, A1, A2, A3, A4, A5};   // Left → Right
int sensorValues[6];

// ----------------- MOTOR DRIVER (L298N) -----------------
#define ENA 5    // Left Motor PWM
#define IN1 6
#define IN2 7

#define IN3 8
#define IN4 9
#define ENB 10   // Right Motor PWM

// ----------------- ULTRASONIC SENSOR -----------------
#define TRIG 3
#define ECHO 4

// ----------------- PID PARAMETERS -----------------
float Kp = 0.04;
float Ki = 0.00;
float Kd = 0.01;

long error = 0, lastError = 0;
float P, I, D;

// ----------------- SPEED SETTINGS -----------------
int baseSpeed = 98;
int leftSpeed, rightSpeed;

// ==================================================
void setup() {

  Serial.begin(9600);

  // IR Sensor Pins
  for (int i = 0; i < 6; i++) {
    pinMode(sensorPins[i], INPUT);
  }
  pinMode(A6, INPUT_PULLUP);

  // Motor Pins
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Ultrasonic Pins
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  Serial.println("Line Follower with Obstacle Avoidance Ready...");
}

// ==================================================
// Ultrasonic Distance Function
long getDistance() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  long duration = pulseIn(ECHO, HIGH, 30000); // timeout 30ms
  long distance = duration * 0.034 / 2;       // convert to cm

  return distance;
}

// ==================================================
void loop() {
  // // -------- ULTRASONIC SAFETY STOP --------
  long distance = getDistance();
  if (distance > 0 && distance < 15) {
    motor_stop();
    motor_drive(-10, 10); 
    Serial.print("Obstacle detected: ");
    Serial.print(distance);
    Serial.println(" cm | Stopping...");
    delay(1000);
    return;
  }

  long position = 0;
  int activeCount = 0;

  // // -------- READ 8 IR SENSORS WITH WEIGHTS --------
  for (int i = 0; i < 6; i++) sensorValues[i] = digitalRead(sensorPins[i]);
  for (int i = 0; i < 6; i++) {
    if (sensorValues[i] == 1) {  // 0 = BLACK line
      long weight = (i * 2000 - 5000);  // -7000 to +7000
      position += weight;
      if(i==0||i==6)position += weight;
      activeCount++;
      //Serial.print(i);
    }
  }
   //Serial.println(".");
   //delay(2000);

  // -------- IF LINE LOST, RECOVER --------
  if (activeCount == 0) {
    if (lastError > 0)
      motor_drive(-80, 80);   // turn right
    else
      motor_drive(80, -80);   // turn left

    Serial.println("Line lost! Recovering...");
    return;
  }

  // // -------- CALCULATE ERROR --------
  error = position / activeCount;

  // // -------- PID CONTROL --------
   P = error;
   I += error;
   I = constrain(I, -1000, 1000);
   D = error - lastError;

  float correction = Kp * P + Ki * I + Kd * D;

  leftSpeed  = baseSpeed - correction;
  rightSpeed = baseSpeed + correction;

  leftSpeed  = constrain(leftSpeed,  -255, 255);
  rightSpeed = constrain(rightSpeed, -255, 255);


 //-------- DRIVE MOTORS --------
  motor_drive(leftSpeed, rightSpeed);

  lastError = error;


}

// ==================================================
// MOTOR CONTROL FOR L298N
void motor_drive(int left, int right) {

  // LEFT MOTOR
  if (left >= 0) {
    analogWrite(ENA, left);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
  } else {
    analogWrite(ENA, -left);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
  }

  // RIGHT MOTOR
  if (right >= 0) {
    analogWrite(ENB, right);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  } else {
    analogWrite(ENB, -right);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
  }
}

// ==================================================
void motor_stop() {
  analogWrite(ENA, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  analogWrite(ENB, 0);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}