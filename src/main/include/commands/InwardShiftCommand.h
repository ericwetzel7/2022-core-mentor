#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include "subsystems/TransportSubsystem.h"

class InwardShiftCommand : public frc2::CommandHelper<frc2::CommandBase, InwardShiftCommand> {
public:
    InwardShiftCommand(TransportSubsystem* system);

    void Execute() override;
    void End(bool) override;
    bool IsFinished() override;
private:
    TransportSubsystem* transport;
};