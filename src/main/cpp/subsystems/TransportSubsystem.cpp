#include "subsystems/TransportSubsystem.h"

#include <stdexcept>

TransportSubsystem::TransportSubsystem(frc::DriverStation::Alliance alliance) {
    changeAlliance(alliance);
}

void TransportSubsystem::changeAlliance(frc::DriverStation::Alliance alliance) {
    if(alliance == frc::DriverStation::Alliance::kInvalid) {
        // yes, this is terrible, but you absolutely deserve what you get
        throw std::domain_error("Can't have an invalid alliance");
    }
    currentAlliance = alliance;
}

void TransportSubsystem::enableOuterBelt(bool requireSafety) {
    outerBelt.Set(constants::transport::OUTER_BELT_SPEED);
}

void TransportSubsystem::disableOuterBelt() {
    outerBelt.Set(0);
}

void TransportSubsystem::reverseOuterBelt(bool requireSafety) {
    outerBelt.Set(-constants::transport::OUTER_BELT_SPEED);
}

void TransportSubsystem::enableInnerBelt(bool requireSafety) {
    innerBelt.Set(constants::transport::INNER_BELT_SPEED);
}

void TransportSubsystem::disableInnerBelt() {
    innerBelt.Set(0);
}

void TransportSubsystem::reverseInnerBelt(bool requireSafety) {
    innerBelt.Set(-constants::transport::INNER_BELT_SPEED);
}

bool TransportSubsystem::hasOuterBall() {
    // return outerColorSensor.GetProximity() > 2000; // ?
    return outerBallSwitch.Get();
}

bool TransportSubsystem::hasInnerBall() {
    return innerBallSwitch.Get();
}

frc::Color TransportSubsystem::outerBallColor() {
    return frc::Color::kWhite;
    // return outerColorSensor.GetColor();
}

bool TransportSubsystem::outerBallMatchesAlliance() {
    frc::Color ball = outerBallColor();
    switch(currentAlliance) {
    case frc::DriverStation::Alliance::kBlue:
        return dominantColor(ball) == RGB::BLUE;
    case frc::DriverStation::Alliance::kRed:
        return dominantColor(ball) == RGB::RED;
    default:
        // Will never happen. Just shuts up the "unahndled cases" compiler warning
        return false;
    }
}

TransportSubsystem::RGB TransportSubsystem::dominantColor(frc::Color color) {
    // 0.2 picked semi-randomly. Mostly meant to act as a noise filter.
    if(color.red >= color.blue + 0.2 && color.red >= color.green + 0.2) {
        return RGB::RED;
    } else if (color.green >= color.red + 0.2 && color.green >= color.blue + 0.2) {
        return RGB::GREEN;
    } else if (color.blue >= color.red + 0.2 && color.blue >= color.green + 0.2) {
        return RGB::BLUE;
    } else {
        return RGB::INDETERMINATE;
    }
}