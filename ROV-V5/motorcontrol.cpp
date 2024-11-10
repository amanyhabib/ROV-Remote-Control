#include <Arduino.h>
#include "motorcontrol.h"

// Constructor to initialize the motor pins
MotorControl::MotorControl() 
    : frontLeftMotorPin(3), frontRightMotorPin(5), 
      backLeftMotorPin(6), backRightMotorPin(9),
      frontLeftDirectionPin(2), frontRightDirectionPin(4), 
      backLeftDirectionPin(7), backRightDirectionPin(8) {

    // Set all motor pins as OUTPUT
    pinMode(frontLeftMotorPin, OUTPUT);
    pinMode(frontRightMotorPin, OUTPUT);
    pinMode(backLeftMotorPin, OUTPUT);
    pinMode(backRightMotorPin, OUTPUT);
    
    // Set all direction pins as OUTPUT
    pinMode(frontLeftDirectionPin, OUTPUT);
    pinMode(frontRightDirectionPin, OUTPUT);
    pinMode(backLeftDirectionPin, OUTPUT);
    pinMode(backRightDirectionPin, OUTPUT);
}

// Initialize motor control
void MotorControl::initialize() {
    // Any additional initialization code can go here if needed
}

// Move forward at a specified speed
void MotorControl::moveForward(int speed) {
    controlDC(1, speed, HIGH);  // Front left forward
    controlDC(2, speed, HIGH);  // Front right forward
    controlDC(3, speed, HIGH);  // Back left forward
    controlDC(4, speed, HIGH);  // Back right forward
}

// Move backward at a specified speed
void MotorControl::moveBackward(int speed) {
    controlDC(1, speed, LOW);  // Front left backward
    controlDC(2, speed, LOW);  // Front right backward
    controlDC(3, speed, LOW);  // Back left backward
    controlDC(4, speed, LOW);  // Back right backward
}

// Turn left at a specified speed
void MotorControl::turnLeft(int speed) {
    controlDC(1, 0, LOW);  // Stop front left
    controlDC(2, speed, HIGH);  // Front right forward
    controlDC(3, speed, HIGH);  // Back left forward
    controlDC(4, 0, LOW);  // Stop back right
}

// Turn right at a specified speed
void MotorControl::turnRight(int speed) {
    controlDC(1, speed, HIGH);  // Front left forward
    controlDC(2, 0, LOW);  // Stop front right
    controlDC(3, 0, LOW);  // Stop back left
    controlDC(4, speed, HIGH);  // Back right forward
}

// Stop all motors
void MotorControl::stop() {
    stopAllMotors();
}

// Control individual DC motors
void MotorControl::controlDC(unsigned char motor, unsigned char speedValue, unsigned char direction) {
    unsigned char pin;
    unsigned char dirPin;

    // Determine motor pins based on the motor number
    switch (motor) {
        case 1: pin = frontLeftMotorPin; dirPin = frontLeftDirectionPin; break;
        case 2: pin = frontRightMotorPin; dirPin = frontRightDirectionPin; break;
        case 3: pin = backLeftMotorPin; dirPin = backLeftDirectionPin; break;
        case 4: pin = backRightMotorPin; dirPin = backRightDirectionPin; break;
        default: return;  // Invalid motor
    }

    // Ensure speed is within the PWM range
    speedValue = constrain(speedValue, 0, 255);

    // Set direction and speed
    digitalWrite(dirPin, direction);
    analogWrite(pin, speedValue);
}

// Stop all motors
void MotorControl::stopAllMotors() {
    analogWrite(frontLeftMotorPin, 0);
    analogWrite(frontRightMotorPin, 0);
    analogWrite(backLeftMotorPin, 0);
    analogWrite(backRightMotorPin, 0);
}
