#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include <functional>

#include "subsystems/DriveSubsytem.h"

class DriveUntilCommand : public frc2::CommandHelper<frc2::CommandBase, DriveUntilCommand> {
public:
    DriveUntilCommand(DriveSubsystem* system, bool forward, std::function<bool(void)> condition);

    void Execute();
    void End(bool);
    bool IsFinished();
private:
    DriveSubsystem* drive;
    bool forward;
    std::function<bool(void)> condition;
};