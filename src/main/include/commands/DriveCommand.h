#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include "subsystems/DriveSubsytem.h"
#include "frc/Joystick.h"

class DriveCommand : public frc2::CommandHelper<frc2::CommandBase, DriveCommand> {
public:
    DriveCommand(DriveSubsystem* drive, frc::Joystick* stick);

    void Execute() override;
private:
    DriveSubsystem* driveSubsystem;
    frc::Joystick* control;
};