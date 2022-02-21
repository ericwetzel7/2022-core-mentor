#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include "subsystems/ShooterSubsystem.h"

class FlywheelCommand : public frc2::CommandHelper<frc2::CommandBase, FlywheelCommand> {
public:
    FlywheelCommand(ShooterSubsystem* shoot);

    void Execute() override;
private:
    ShooterSubsystem* shooter;
};