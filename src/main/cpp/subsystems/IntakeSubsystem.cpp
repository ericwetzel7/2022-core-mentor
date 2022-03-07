#include "subsystems/IntakeSubsystem.h"
#include <frc/DoubleSolenoid.h>

IntakeSubsystem::IntakeSubsystem() : IntakeSubsystem(constants::intake::DEFAULT_ROLLER_SPEED) {}

IntakeSubsystem::IntakeSubsystem(double defSpeed) : defaultSpeed(defSpeed), rollerSpeed(defSpeed) {
    retractArm();
}

void IntakeSubsystem::extendArm() {
    arm.Set(frc::DoubleSolenoid::Value::kForward);
}

void IntakeSubsystem::retractArm() {
    arm.Set(frc::DoubleSolenoid::Value::kReverse);
}

void IntakeSubsystem::toggleArm() {
    arm.Toggle();
}

void IntakeSubsystem::startRoller() {
    roller.Set(rollerSpeed);
}

void IntakeSubsystem::stopRoller() {
    roller.Set(0);
}

void IntakeSubsystem::reverseRoller() {
    roller.Set(-rollerSpeed);
}

void IntakeSubsystem::resetRollerSpeed() {
    setRollerSpeed(defaultSpeed);
}

void IntakeSubsystem::setRollerSpeed(double speed) {
    rollerSpeed = speed;
    double currentSpeed = roller.Get();
    if(currentSpeed > 0.001) {
        startRoller();
    } else if(currentSpeed < -0.001) {
        reverseRoller();
    } // else stopped
}

double IntakeSubsystem::getRollerSpeed() {
    return rollerSpeed;
}

double IntakeSubsystem::getDefaultRollerSpeed() {
    return defaultSpeed;
}