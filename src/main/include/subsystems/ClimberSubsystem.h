#pragma once

#include "Constants.h"

#include <frc2/command/SubsystemBase.h>
#include <frc/DoubleSolenoid.h>
#include <frc/DigitalInput.h>

class ClimberSubsystem : public frc2::SubsystemBase {
public:
    ClimberSubsystem();
    ~ClimberSubsystem() noexcept {}

    void extendLower();
    void retractLower();
    void toggleLower();
    bool isRetracted();

    void extendUpper(bool requireSafe = false);
    void retractUpper(bool requireSafe = false);
    void toggleUpper(bool requireSafe = false);

private:
    frc::DigitalInput liftSwitch{constants::climber::LIFT_SWITCH};

    frc::DoubleSolenoid lowerArms{frc::PneumaticsModuleType::CTREPCM,
                                  constants::climber::LOWER_FORWARD_SOLENOID,
                                  constants::climber::LOWER_REVERSE_SOLENOID};
    frc::DoubleSolenoid upperArms{frc::PneumaticsModuleType::CTREPCM,
                                  constants::climber::UPPER_FORWARD_SOLENOID,
                                  constants::climber::UPPER_REVERSE_SOLENOID};
};
