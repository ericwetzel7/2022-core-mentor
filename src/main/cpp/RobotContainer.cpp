// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"

#include <frc/DriverStation.h>

#include <frc2/command/button/JoystickButton.h>
#include <frc2/command/StartEndCommand.h>
#include <frc2/command/SequentialCommandGroup.h>
#include <frc2/command/InstantCommand.h>
#include <frc2/command/WaitCommand.h>
#include <frc2/command/button/Trigger.h>

#include <units/time.h>

#include "commands/DriveCommand.h"
#include "commands/FlywheelCommand.h"
#include "commands/InwardShiftCommand.h"

RobotContainer::RobotContainer() : transportSubsystem(frc::DriverStation::GetAlliance()) {
  // Initialize all of your commands and subsystems here
  driveSubsystem.SetDefaultCommand(DriveCommand(&driveSubsystem, &control1));
  shooterSubsystem.SetDefaultCommand(FlywheelCommand(&shooterSubsystem));

  // Configure the button bindings
  ConfigureButtonBindings();
}

void RobotContainer::ConfigureButtonBindings() {
  // Configure your button bindings here
  frc2::JoystickButton(&control2, 2).ToggleWhenPressed(frc2::StartEndCommand(
    [this] {this->intakeSubsystem.extendArm();},
    [this] {this->intakeSubsystem.retractArm();},
    {&intakeSubsystem}
  ));
  
  frc2::JoystickButton(&control2, 1).WhenHeld(frc2::StartEndCommand(
    [this] {this->intakeSubsystem.startRoller();},
    [this] {this->intakeSubsystem.stopRoller();},
    {&intakeSubsystem}
  ));

  // frc2::Trigger()
  frc2::Trigger([this]{
    return transportSubsystem.hasOuterBall() && !transportSubsystem.hasInnerBall();
  }).WhenActive(InwardShiftCommand(&transportSubsystem));

  auto shootCommand = frc2::SequentialCommandGroup(
    frc2::InstantCommand([this]{transportSubsystem.enableInnerBelt();}, {&transportSubsystem}),
    frc2::WaitCommand(0.5_s)
  );
  frc2::JoystickButton(&control1, 1).WhenPressed(shootCommand);
}

