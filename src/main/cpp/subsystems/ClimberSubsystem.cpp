#include "subsystems/ClimberSubsystem.h"

ClimberSubsystem::ClimberSubsystem() {
    upperFired = false;
    retractLower();
    retractUpper();
}

void ClimberSubsystem::extendLower() {
    lowerArms.Set(frc::DoubleSolenoid::Value::kForward);
}

void ClimberSubsystem::retractLower() {
    lowerArms.Set(frc::DoubleSolenoid::Value::kReverse);
}

void ClimberSubsystem::toggleLower() {
    lowerArms.Toggle();
}

bool ClimberSubsystem::isRetracted() {
    return liftSwitchRight.Get() && liftSwitchLeft.Get();
}

void ClimberSubsystem::extendUpper(bool requireSafe) {
    if(requireSafe && !isRetracted()) return;
    upperArms.Set(frc::DoubleSolenoid::Value::kForward);
    upperFired = true;
}

void ClimberSubsystem::retractUpper(bool requireSafe) {
    if(requireSafe && !isRetracted()) return;
    upperArms.Set(frc::DoubleSolenoid::Value::kReverse);
}

void ClimberSubsystem::toggleUpper(bool requireSafe) {
    if(requireSafe && !isRetracted()) return;
    upperArms.Toggle();
    upperFired = true;
}

bool ClimberSubsystem::isUpperFired() {
    return upperFired;
}

void ClimberSubsystem::resetFiring() {
    upperFired = false;
}