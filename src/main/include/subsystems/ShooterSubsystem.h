#pragma once

#include "Constants.h"

#include <frc2/command/SubsystemBase.h>
#include <rev/CANSparkMax.h>
#include <rev/SparkMaxPIDController.h>

class ShooterSubsystem : public frc2::SubsystemBase {
public:

    ShooterSubsystem();
    ShooterSubsystem(double rpm);
    ~ShooterSubsystem() noexcept {}

    void enableFlywheel();
    void disableFlywheel();

    void setSpeed(double rpm);
    void resetSpeed();
    double getSpeed();
    double getRealSpeed();

private:
    double flywheelRPM;

    rev::CANSparkMax flywheel {constants::shooter::SHOOTER_MOTOR, rev::CANSparkMax::MotorType::kBrushless};
    rev::SparkMaxPIDController flywheelPID{flywheel.GetPIDController()};
};