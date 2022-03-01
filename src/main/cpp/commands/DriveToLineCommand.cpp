#include "commands/DriveToLineCommand.h"

DriveToLineCommand::DriveToLineCommand(DriveSubsystem* system, bool forward) : drive(system), forward(forward) {
    AddRequirements(system);
}

void DriveToLineCommand::Execute() {
    if(forward) {
        drive->drive(0, 0.5, 0);
    } else {
        drive->drive(0, -0.5, 0);
    }
}

bool DriveToLineCommand::IsFinished() {
    return drive->seesLine();
}