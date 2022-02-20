// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

namespace constants {
    namespace drive {
        constexpr int FRONT_LEFT_MOTOR = 0;
        constexpr int REAR_LEFT_MOTOR = 1;
        constexpr int FRONT_RIGHT_MOTOR = 2;
        constexpr int REAR_RIGHT_MOTOR = 3;

        constexpr int LINE_SENSOR = 0;
        
        constexpr int MOTOR_COUNT = 4;

        constexpr double DEFAULT_DEADBAND = 0.02;
    }

    namespace intake {
        constexpr int FORWARD_SOLENOID = 0;
        constexpr int REVERSE_SOLENOID = 1;

        constexpr int ROLLER_MOTOR = 0;

        constexpr double DEFAULT_ROLLER_SPEED = 0.5;
    }
}