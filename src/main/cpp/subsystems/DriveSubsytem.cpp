#include "subsystems/DriveSubsytem.h"

DriveSubsystem::DriveSubsystem() : DriveSubsystem(constants::drive::DEFAULT_DEADBAND) {}

DriveSubsystem::DriveSubsystem(double deadband) {
    mecanumDrive.SetDeadband(deadband);
    resetDistance();
    resetGyro();
}

void DriveSubsystem::drive(double xSpeed, double ySpeed, double rotation) {
    mecanumDrive.DriveCartesian(ySpeed, xSpeed, rotation);
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