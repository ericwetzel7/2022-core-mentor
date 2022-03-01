#include "commands/DriveToLineCommand.h"

DriveToLineCommand::DriveToLineCommand(DriveSubsystem* system) : drive(system) {
    AddRequirements(system);
}

void DriveToLineCommand::Execute() {
    drive->drive(0, -0.5, 0);
}

bool DriveToLineCommand::IsFinished() {
    return drive->seesLine();
}