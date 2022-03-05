#pragma once

#include "Constants.h"

#include <frc2/command/SubsystemBase.h>
#include <frc/DoubleSolenoid.h>
#include <ctre/Phoenix.h>

using ctre::phoenix::motorcontrol::can::WPI_TalonSRX;

class IntakeSubsystem : public frc2::SubsystemBase {
public:
    IntakeSubsystem();
    IntakeSubsystem(double defaultSpeed);

    void extendArm();
    void retractArm();
    void toggleArm();

    void startRoller();
    void stopRoller();
    void reverseRoller();
    void resetRollerSpeed();
    void setRollerSpeed(double speed);
    double getRollerSpeed();
    double getDefaultRollerSpeed();
private:
    double defaultSpeed;
    double rollerSpeed;

    frc::DoubleSolenoid arm{frc::PneumaticsModuleType::CTREPCM,
                            constants::intake::FORWARD_SOLENOID,
                            constants::intake::REVERSE_SOLENOID};

    ctre::phoenix::motorcontrol::can::WPI_VictorSPX roller{constants::intake::ROLLER_MOTOR};
    // WPI_TalonSRX roller{constants::intake::ROLLER_MOTOR};
};