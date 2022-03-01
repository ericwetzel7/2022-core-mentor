#include "commands/InwardShiftCommand.h"

InwardShiftCommand::InwardShiftCommand(TransportSubsystem* system) : transport(system) {
    AddRequirements(system);
}

void InwardShiftCommand::Execute() {
    transport->enableOuterBelt();
    transport->enableInnerBelt();
}

void InwardShiftCommand::End(bool) {
    transport->disableOuterBelt();
    transport->disableInnerBelt();
}

bool InwardShiftCommand::IsFinished() {
    return transport->hasInnerBall();
}