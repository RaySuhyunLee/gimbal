#include <Servo.h>
#include "imu.h"
#include "pid.h"

#define ROLL_PIN 2
#define PITCH_PIN 3

#define P_GAIN 0.05
#define I_GAIN 0.00
#define D_GAIN 0.03

#define INTERVAL 10

Servo rollServo;
Servo pitchServo;

PIDController pidRoll(P_GAIN, I_GAIN, D_GAIN, INTERVAL);
PIDController pidPitch(P_GAIN, I_GAIN, D_GAIN, INTERVAL);

void setup() {
  initIMU();
  rollServo.attach(ROLL_PIN);
  pitchServo.attach(PITCH_PIN);
  Serial.begin(9600);
}

void loop() {
  static double roll, pitch, yaw;
  static double roll_diff, pitch_diff, yaw_diff;
  if (millis() % INTERVAL == 0) {
    readIMU();
    getGyro(&roll, &pitch, &yaw);

    roll_diff += pidRoll.pid(roll - 0);
    pitch_diff += pidRoll.pid(pitch - 0);

    Serial.println(roll_diff);

    rollServo.writeMicroseconds(1500 + roll_diff * 10);
    pitchServo.writeMicroseconds(1500 + pitch_diff * 10); 
  }
}
