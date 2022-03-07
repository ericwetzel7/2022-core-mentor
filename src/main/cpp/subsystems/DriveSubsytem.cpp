#include "subsystems/DriveSubsytem.h"

#include <cmath>
#include <frc/MathUtil.h>

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
    if(squareX) {
        xSpeed = abs(xSpeed) * xSpeed;
    }
    if(squareY) {
        ySpeed = abs(ySpeed) * ySpeed;
    }
    if(squareRot) {
        rotation = abs(rotation) * rotation;
    }
    // mecanum drive does not inerently apply deadband to rotation
    if(rotation < deadband) {
        frc::ApplyDeadband(rotation, deadband);
    }
    if(rotation > deadband || rotation < -deadband) {
        // reset the gyro if rotating to help eliminate noise.
        gyro.Reset();
        mecanumDrive.DriveCartesian(ySpeed, xSpeed, rotation * constants::drive::ROTARTION_REDUCTION);
    } else {
    //     mecanumDrive.DriveCartesian(ySpeed, xSpeed, rotation);
    // }
        // adjust rotation to compensate for hysteresis
        // Get angle, shift to [-180,180), normalize
        double rotOffset = (gyro.GetAngle() - (360 * (gyro.GetAngle() >= 180))) / 180;
        rotOffset *= -constants::drive::ROTATION_ADJUSTMENT_RATE;
        mecanumDrive.DriveCartesian(ySpeed, xSpeed, fmin(rotation + rotOffset, 1));
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
    // return true;
}