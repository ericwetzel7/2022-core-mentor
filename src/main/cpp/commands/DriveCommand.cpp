#include "commands/DriveCommand.h"

DriveCommand::DriveCommand(DriveSubsystem* drive, frc::Joystick* stick) :
        driveSubsystem(drive), control(stick) {
    AddRequirements(driveSubsystem);
}

void DriveCommand::Execute() {
    driveSubsystem->drive(control->GetX(), control->GetY(), control->GetZ());
}