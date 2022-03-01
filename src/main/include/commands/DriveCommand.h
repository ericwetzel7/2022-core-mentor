#pragma once

#include "Constants.h"

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include "subsystems/DriveSubsytem.h"
#ifdef USE_XBOX_CONTROLS
#include <frc/XboxController.h>
#else
#include <frc/Joystick.h>
#endif

class DriveCommand : public frc2::CommandHelper<frc2::CommandBase, DriveCommand> {
public:
#ifdef USE_XBOX_CONTROLS
    DriveCommand(DriveSubsystem* drive, frc::XboxController* stick);
#else
    DriveCommand(DriveSubsystem* drive, frc::Joystick* stick);
#endif

    void Execute() override;
private:
    DriveSubsystem* driveSubsystem;
#ifdef USE_XBOX_CONTROLS
    frc::XboxController* control;
#else
    frc::Joystick* control;
#endif
};