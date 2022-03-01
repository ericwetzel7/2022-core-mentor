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
#ifdef USE_XBOX_CONTROLS
  driveSubsystem.SetDefaultCommand(DriveCommand(&driveSubsystem, &controller));
#else
  driveSubsystem.SetDefaultCommand(DriveCommand(&driveSubsystem, &control1));
#endif
  shooterSubsystem.SetDefaultCommand(FlywheelCommand(&shooterSubsystem));

  // Configure the button bindings
  ConfigureButtonBindings();
}

void RobotContainer::ConfigureButtonBindings() {
  auto toggle_intake_arm = frc2::StartEndCommand(
    [this] {this->intakeSubsystem.extendArm();},
    [this] {this->intakeSubsystem.retractArm();},
    {&intakeSubsystem}
  );

  auto run_intake_roller = frc2::StartEndCommand(
    [this] {
#ifdef USE_XBOX_CONTROLS
      if(controller.GetRawButton(0)) {
#else
      if(control2.GetRawButton(10)) {
#endif
        intakeSubsystem.reverseRoller();
      } else {
        intakeSubsystem.startRoller();
      }
    },
    [this] {this->intakeSubsystem.stopRoller();},
    {&intakeSubsystem}
  );

  auto reverse_outer_transport = frc2::StartEndCommand(
    [this] {transportSubsystem.reverseOuterBelt();},
    [this] {transportSubsystem.disableOuterBelt();},
    {&transportSubsystem}
  );

  auto auto_shift_condition = [this]{
    return transportSubsystem.hasOuterBall() && !transportSubsystem.hasInnerBall();
  };
  
  auto transport_inward_shift = InwardShiftCommand(&transportSubsystem);
  
  auto shootCommand = frc2::SequentialCommandGroup(
    frc2::InstantCommand([this]{transportSubsystem.enableInnerBelt();}, {&transportSubsystem}),
    frc2::WaitCommand(0.5_s)
  );

#ifdef USE_XBOX_CONTROLS

#else
  frc2::JoystickButton(&control2, 2).ToggleWhenPressed(toggle_intake_arm);
  frc2::JoystickButton(&control2, 1).WhenHeld(run_intake_roller);
  frc2::JoystickButton(&control2, 5).WhenHeld(reverse_outer_transport);
  frc2::Trigger(auto_shift_condition).WhenActive(transport_inward_shift);
  frc2::JoystickButton(&control1, 1).WhenPressed(shootCommand);
#endif

  // TODO list
  // - enable outer belt while roller running until ball present - automatic behaviour or button?
}

