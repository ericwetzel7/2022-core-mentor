// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"

#include <frc/DriverStation.h>

#include "commands/DriveCommand.h"
#include "commands/FlywheelCommand.h"


RobotContainer::RobotContainer() : transportSubsystem(frc::DriverStation::GetAlliance()) {
  // Initialize all of your commands and subsystems here
  driveSubsystem.SetDefaultCommand(DriveCommand(&driveSubsystem, &control1));
  shooterSubsystem.SetDefaultCommand(FlywheelCommand(&shooterSubsystem));

  // Configure the button bindings
  ConfigureButtonBindings();
}

void RobotContainer::ConfigureButtonBindings() {
  // Configure your button bindings here
}

