#include "commands/FlywheelCommand.h"

FlywheelCommand::FlywheelCommand(ShooterSubsystem* shoot) : shooter(shoot) {
    AddRequirements(shoot);
}

void FlywheelCommand::Execute() {
    shooter->enableFlywheel();
}