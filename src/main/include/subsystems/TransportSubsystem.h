#pragma once

#include "Constants.h"

#include <frc2/command/SubsystemBase.h>
#include <ctre/Phoenix.h>
#include <frc/DigitalInput.h>
#include <rev/ColorSensorV3.h>
#include <frc/I2C.h>
#include <frc/DriverStation.h>
#include <frc/util/Color.h>

using ctre::phoenix::motorcontrol::can::WPI_VictorSPX;


class TransportSubsystem : public frc2::SubsystemBase {
public:
    TransportSubsystem(frc::DriverStation::Alliance alliance);

    void changeAlliance(frc::DriverStation::Alliance alliance);

    void enableOuterBelt(bool requireSafety = true);
    void disableOuterBelt();
    void reverseOuterBelt(bool requireSafety = true);
    void enableInnerBelt(bool requireSafety = true);
    void disableInnerBelt();
    void reverseInnerBelt(bool requireSafety = true);

    bool hasOuterBall();
    bool hasInnerBall();
    
    frc::Color outerBallColor();
    bool outerBallMatchesAlliance();

private:
    enum class RGB {
        RED,
        BLUE,
        GREEN,
        INDETERMINATE,
    };

    frc::DriverStation::Alliance currentAlliance;

    frc::DigitalInput innerBallSwitch{constants::transport::INNER_BALL_SWITCH};
    frc::DigitalInput outerBallSwitch{constants::transport::OUTER_BALL_SWITCH};
    // rev::ColorSensorV3 outerColorSensor{frc::I2C::Port::kMXP};

    WPI_VictorSPX innerBelt{constants::transport::INNER_BELT_MOTOR};
    WPI_VictorSPX outerBelt{constants::transport::OUTER_BELT_MOTOR};

    RGB dominantColor(frc::Color color);
};

