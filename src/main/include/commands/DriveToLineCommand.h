#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include "subsystems/DriveSubsytem.h"

class DriveToLineCommand : public frc2::CommandHelper<frc2::CommandBase, DriveToLineCommand> {
public:
    DriveToLineCommand(DriveSubsystem* system);

    void Execute() override;
    bool IsFinished() override;
private:
    DriveSubsystem* drive;
};