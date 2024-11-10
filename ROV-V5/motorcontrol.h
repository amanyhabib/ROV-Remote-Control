#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H

// MotorControl class for managing DC motor directions and speed control
class MotorControl {
public:
    MotorControl(); // Constructor

    // Motor control methods
    void initialize();           // Initialize the motor control
    void moveForward(int speed);  // Move forward at speed
    void moveBackward(int speed); // Move backward at speed
    void turnLeft(int speed);     // Turn left at speed
    void turnRight(int speed);    // Turn right at speed
    void stop();                  // Stop all motors

private:
    // Motor pin definitions
    const int frontLeftMotorPin;
    const int frontRightMotorPin;
    const int backLeftMotorPin;
    const int backRightMotorPin;

    // Direction pin definitions
    const int frontLeftDirectionPin;
    const int frontRightDirectionPin;
    const int backLeftDirectionPin;
    const int backRightDirectionPin;

    // Control DC motors
    void controlDC(unsigned char motor, unsigned char speedValue, unsigned char direction);
    void stopAllMotors(); // Stop all motors
};

#endif // MOTORCONTROL_H
