#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include "subsystems/DriveSubsytem.h"

class DriveToLineCommand : public frc2::CommandHelper<frc2::CommandBase, DriveToLineCommand> {
public:
    DriveToLineCommand(DriveSubsystem* system, bool forward);

    void Execute() override;
    bool IsFinished() override;
private:
    DriveSubsystem* drive;
    bool forward;
};