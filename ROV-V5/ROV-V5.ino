#include <Arduino.h>
#include <Servo.h>
#include "motorcontrol.h"

// Enumeration for directions (place this before any functions use it)
enum Direction {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN,
    STOP,
    UNKNOWN
};

// Function prototypes
Direction getCommand();
void controlROV(Direction command);
void printCurrentStatus(Direction command);
void controlVerticalMotors(int pwmValue);

// Pin definitions
const int potPin = A0;  // Potentiometer for speed control

// Speed variable
int speed = 0;

// Create a MotorControl object for DC motors and Servo objects for T100 motors
MotorControl rov;
Servo t100Motor1;
Servo t100Motor2;

// T100 motor PWM range (Blue Robotics ESC standard is 1100 to 1900 microseconds)
const int t100MinPWM = 1100;
const int t100MaxPWM = 1900;
const int t100Motor1Pin = 10;  // Pin for T100 motor 1
const int t100Motor2Pin = 11;  // Pin for T100 motor 2

void setup() {
    Serial.begin(9600);   // Initialize serial communication
    rov.initialize();     // Initialize motor control
    t100Motor1.attach(t100Motor1Pin); // Attach the servo objects to their pins
    t100Motor2.attach(t100Motor2Pin);
    pinMode(potPin, INPUT);
}

void loop() {
    // Read speed from potentiometer
    speed = analogRead(potPin) / 4;  // Scale to 0-255 range

    // Get command from serial input
    Direction command = getCommand();

    // Control the ROV based on command
    controlROV(command);

    // Print the current status
    printCurrentStatus(command);

    delay(100);  // Small delay for stability
}

// Function to get command from serial
Direction getCommand() {
    if (Serial.available()) {
        char input = Serial.read();  // Read the command from serial
        Serial.print("Command received: ");
        Serial.println(input);  // Echo the command back

        switch (input) {
            case 'w': case 'W': return FORWARD;
            case 's': case 'S': return BACKWARD;
            case 'a': case 'A': return LEFT;
            case 'd': case 'D': return RIGHT;
            case 'u': case 'U': return UP;
            case 'q': case 'Q': return DOWN;
            case 'x': case 'X': return STOP;
            default: return UNKNOWN;  // Unrecognized command
        }
    }
    return UNKNOWN;  // No input received
}

// Function to control the T100 motors for vertical movement
void controlVerticalMotors(int pwmValue) {
    t100Motor1.writeMicroseconds(pwmValue);
    t100Motor2.writeMicroseconds(pwmValue);
}

// Function to control the ROV based on the command
void controlROV(Direction command) {
    switch (command) {
        case FORWARD:
            rov.moveForward(speed);  // Move forward at speed
            break;
        case BACKWARD:
            rov.moveBackward(speed);  // Move backward at speed
            break;
        case LEFT:
            rov.turnLeft(speed);  // Turn left at speed
            break;
        case RIGHT:
            rov.turnRight(speed);  // Turn right at speed
            break;
        case UP:
            controlVerticalMotors(map(speed, 0, 255, t100MinPWM, t100MaxPWM));  // Move up at speed
            break;
        case DOWN:
            controlVerticalMotors(map(speed, 0, 255, t100MaxPWM, t100MinPWM));  // Move down at speed
            break;
        case STOP:
        case UNKNOWN:
        default:
            rov.stop();                   // Stop DC motors
            controlVerticalMotors(1500);  // Neutral position for T100 motors (1500 us is neutral for ESCs)
            break;
    }
}

// Function to print the current status of the ROV
void printCurrentStatus(Direction command) {
    switch (command) {
        case FORWARD: Serial.print("Moving Forward at Speed: "); break;
        case BACKWARD: Serial.print("Moving Backward at Speed: "); break;
        case LEFT: Serial.print("Turning Left at Speed: "); break;
        case RIGHT: Serial.print("Turning Right at Speed: "); break;
        case UP: Serial.print("Moving Up at Speed: "); break;
        case DOWN: Serial.print("Moving Down at Speed: "); break;
        case STOP: Serial.print("Stopping"); break;
        case UNKNOWN: Serial.print("Unknown Command"); break;
    }
    Serial.println(speed);
}
