#include "subsystems/DriveSubsytem.h"

#include <cmath>

DriveSubsystem::DriveSubsystem() : DriveSubsystem(constants::drive::DEFAULT_DEADBAND) {}

DriveSubsystem::DriveSubsystem(double deadband) : DriveSubsystem(deadband, true, true, true) {}

DriveSubsystem::DriveSubsystem(double deadband, bool squareXInput, bool squareYInput, bool squareRotInput) 
        : deadband(deadband), squareX(squareXInput), squareY(squareYInput), squareRot(squareRotInput) {
    mecanumDrive.SetDeadband(deadband);

    frontRight.SetInverted(true);
    rearRight.SetInverted(true);
    resetDistance();
    resetGyro();
}

void DriveSubsystem::drive(double xSpeed, double ySpeed, double rotation, bool correctRotation) {
    xSpeed = pow(xSpeed, 1 + squareX * 0.5);
    ySpeed = pow(ySpeed, 1 + squareY * 0.5);
    rotation = pow(rotation, 1 + squareRot * 0.5);
    if(rotation > deadband || rotation < -deadband) {
        gyro.Reset();
        mecanumDrive.DriveCartesian(ySpeed, xSpeed, rotation);
    } else {
        // Get angle, shift to [-180,180), normalize
        double rotOffset = (gyro.GetAngle() - (360 * (rotOffset >= 180))) / 180;
        rotOffset *= constants::drive::ROTATION_ADJUSTMENT_RATE;
        mecanumDrive.DriveCartesian(ySpeed, xSpeed, rotation + rotOffset);
    }
}

void DriveSubsystem::freeTurn(double speed) {
    speed = pow(speed, 1 + squareRot * 0.5);
    mecanumDrive.DriveCartesian(0, 0, speed);
}

double DriveSubsystem::distance() {
    double total = 0;
    eachMotor([&total](rev::CANSparkMax& m){
       total += m.GetEncoder().GetPosition();
    });
    return total / constants::drive::MOTOR_COUNT;
}

void DriveSubsystem::resetDistance() {
    eachMotor([](rev::CANSparkMax& m) {
        m.GetEncoder().SetPosition(0);
    });
}

void DriveSubsystem::resetGyro() {
    gyro.Reset();
}

double DriveSubsystem::orientation() {
    return gyro.GetYaw();
}

bool DriveSubsystem::seesLine() {
    return lineSensor.Get();
}