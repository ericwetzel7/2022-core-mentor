// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

namespace constants {
    constexpr int CONTROL1 = 0;

    namespace drive {
        constexpr int FRONT_LEFT_MOTOR = 0;
        constexpr int REAR_LEFT_MOTOR = 1;
        constexpr int FRONT_RIGHT_MOTOR = 2;
        constexpr int REAR_RIGHT_MOTOR = 3;
        constexpr int LINE_SENSOR = 0;

        constexpr int MOTOR_COUNT = 4;

        constexpr double DEFAULT_DEADBAND = 0.02;
        constexpr double ROTATION_ADJUSTMENT_RATE = 0.05;

        constexpr double SELF_ROTATION_SPEED = 0.6;
    }

    namespace intake {
        constexpr int FORWARD_SOLENOID = 0;
        constexpr int REVERSE_SOLENOID = 1;

        constexpr int ROLLER_MOTOR = 0;

        constexpr double DEFAULT_ROLLER_SPEED = 0.5;
    }

    namespace shooter {
        constexpr int SHOOTER_MOTOR = 0;
    
        constexpr double FLYWHEEL_RPM = 2700;
        namespace pid {
            constexpr double P = 0.01;
            constexpr double I = 0.01;
            constexpr double D = 0.01;
        }
    }

    namespace climber {
        constexpr int LOWER_FORWARD_SOLENOID = 2;
        constexpr int LOWER_REVERSE_SOLENOID = 3;
        constexpr int UPPER_FORWARD_SOLENOID = 4;
        constexpr int UPPER_REVERSE_SOLENOID = 5;

        constexpr int LIFT_SWITCH = 0;
    }

    namespace transport {
        constexpr int INNER_BALL_SWITCH = 0;
        // constexpr int OUTER_COLOR_SENSOR = 0;

        constexpr int INNER_BELT_MOTOR = 0;
        constexpr int OUTER_BELT_MOTOR = 1;

        constexpr double INNER_BELT_SPEED = 0.5;
        constexpr double OUTER_BELT_SPEED = 0.5;
    }
}