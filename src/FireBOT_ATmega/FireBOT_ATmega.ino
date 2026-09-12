#include <Servo.h>
#define LM1 4
#define LM2 5
#define RM1 9
#define RM2 10
#define ENA 6
#define ENB 11
#define PUMP 12
#define NOZZLE_SERVO 3
#define BUZZER 8
#define FLAME_LEFT A0
#define FLAME_CENTER A1
#define FLAME_RIGHT A2
#define SMOKE_SENSOR A3
#define FIRE_DETECTED_THRESHOLD 800
#define FIRE_ALIGN_THRESHOLD 800
#define FIRE_STOP_THRESHOLD 400
#define SERVO_LEFT_LIMIT 60
#define SERVO_RIGHT_LIMIT 120
#define MOTOR_SPEED_SLOW 120
#define MOTOR_SPEED_NORMAL 200
Servo nozzle;
String rx = "";
bool autoMode = false;
bool pumpOn = false;
bool servoDirection = true;
int servoPos = 90;
void setup() {
  Serial.begin(9600);
  pinMode(LM1, OUTPUT); pinMode(LM2, OUTPUT);
  pinMode(RM1, OUTPUT); pinMode(RM2, OUTPUT);
  pinMode(ENA, OUTPUT); pinMode(ENB, OUTPUT);
  pinMode(PUMP, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  digitalWrite(PUMP, HIGH);       // Pump OFF
  digitalWrite(BUZZER, LOW);
 nozzle.attach(NOZZLE_SERVO);
  nozzle.write(servoPos);
  Serial.println("STATUS:System Ready");
}
void stopBot() {
  digitalWrite(LM1, LOW); digitalWrite(LM2, LOW);


 digitalWrite(RM1, LOW); digitalWrite(RM2, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}
void moveForwardNormal() {
  analogWrite(ENA, MOTOR_SPEED_NORMAL);
  digitalWrite(LM1, HIGH); digitalWrite(LM2, LOW);
  analogWrite(ENB, MOTOR_SPEED_NORMAL);
  digitalWrite(RM1, HIGH); digitalWrite(RM2, LOW);
}
void moveBackwardSlow() {
  analogWrite(ENA, MOTOR_SPEED_SLOW);
  digitalWrite(LM1, LOW); digitalWrite(LM2, HIGH);
  analogWrite(ENB, MOTOR_SPEED_SLOW);
  digitalWrite(RM1, LOW); digitalWrite(RM2, HIGH);
}
void turnLeftSlow() {
  analogWrite(ENA, MOTOR_SPEED_SLOW);
  digitalWrite(LM1, HIGH); digitalWrite(LM2, LOW);
  analogWrite(ENB, MOTOR_SPEED_SLOW);
  digitalWrite(RM1, LOW); digitalWrite(RM2, HIGH);
}
void turnRightSlow() {
  analogWrite(ENA, MOTOR_SPEED_SLOW);
  digitalWrite(LM1, LOW); digitalWrite(LM2, HIGH);
 analogWrite(ENB, MOTOR_SPEED_SLOW);
  digitalWrite(RM1, HIGH); digitalWrite(RM2, LOW);
}
void sweepServo() {
  if (servoDirection) {

    
servoPos += 5;
  if (servoPos >= SERVO_RIGHT_LIMIT) servoDirection = false;
  } else {
    servoPos -= 5;
    if (servoPos <= SERVO_LEFT_LIMIT) servoDirection = true;
  }
  nozzle.write(servoPos);
}
void handleCommand(String cmd) {
  cmd.trim();
  if (cmd == "FORWARD") moveForwardNormal();
  else if (cmd == "BACKWARD") moveBackwardSlow();
  else if (cmd == "LEFT") turnLeftSlow();
  else if (cmd == "RIGHT") turnRightSlow();
  else if (cmd == "STOP") stopBot();
  else if (cmd.startsWith("MODE:")) {
    autoMode = cmd.substring(5).toInt();
    stopBot();
    Serial.println(autoMode ? "MODE:AUTO" : "MODE:MANUAL");
  }
  else if (cmd == "PUMPON") {
    digitalWrite(PUMP, LOW);
    pumpOn = true;
    Serial.println("STATUS:Pump ON");
  }
  else if (cmd == "PUMPOFF") {
    digitalWrite(PUMP, HIGH);
    pumpOn = false;
Serial.println("STATUS:Pump OFF");

 

}
}
void autoFireControl() {
  int L = analogRead(FLAME_LEFT);
int C = analogRead(FLAME_CENTER);
  int R = analogRead(FLAME_RIGHT);
  Serial.println("SMOKE:" + String(analogRead(SMOKE_SENSOR)));
  if (L > FIRE_DETECTED_THRESHOLD &&
      C > FIRE_DETECTED_THRESHOLD &&
      R > FIRE_DETECTED_THRESHOLD) {
    stopBot();
    digitalWrite(PUMP, HIGH);
    pumpOn = false;
    digitalWrite(BUZZER, LOW);
    Serial.println("FIRE:0");
  }
  else if (L < C && L < R) {
    turnLeftSlow();
    digitalWrite(PUMP, HIGH);
    pumpOn = true;
    Serial.println("FIRE:Detected");
  }
  else if (R < C && R < L) {
    turnRightSlow();
    digitalWrite(PUMP, HIGH);
    pumpOn = true;
    Serial.println("FIRE:Detected");
  }
  else if (C < FIRE_ALIGN_THRESHOLD && C > FIRE_STOP_THRESHOLD) {
    moveForwardNormal();
  

digitalWrite(PUMP, HIGH);
  pumpOn = true;
    Serial.println("FIRE:Detected");
  }
  else if (C <= FIRE_STOP_THRESHOLD) {
    stopBot();
    digitalWrite(PUMP, LOW);
    pumpOn = true;
    digitalWrite(BUZZER, HIGH);
    Serial.println("FIRE:Extinguishing");
  }
}
void loop() {
  while (Serial.available()) {
    char c = Serial.read();
    if (c == '\n') {
      handleCommand(rx);
      rx = "";
    } else if (c != '\r') {
      rx += c;
    }
  }
  if (autoMode) {
    autoFireControl();
  }
  //  Servo moves ONLY when pump is ON
  if (pumpOn) {
    sweepServo();
    delay(40);
}
