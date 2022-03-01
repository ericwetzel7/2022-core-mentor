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
#include "commands/DriveToLineCommand.h"

RobotContainer::RobotContainer() : transportSubsystem(frc::DriverStation::GetAlliance()), autocmd(nullptr) {
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
      if(controller.GetLeftBumper()) {
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
    frc2::InstantCommand([this]{transportSubsystem.enableInnerBelt();}),
    frc2::WaitCommand(0.5_s)
  );
  shootCommand.AddRequirements(&transportSubsystem);

#ifdef USE_XBOX_CONTROLS
  frc2::JoystickButton(&controller, frc::XboxController::Button::kX).ToggleWhenPressed(toggle_intake_arm);
  frc2::JoystickButton(&controller, frc::XboxController::Button::kY).WhenHeld(run_intake_roller);
  // D-pad left
  frc2::Trigger([this]{return controller.GetPOV() == 270;}).WhileActiveOnce(reverse_outer_transport);
  // D-pad down - drive backwards to line
  frc2::Trigger([this]{return controller.GetPOV() == 180;}).ToggleWhenActive(DriveToLineCommand(&driveSubsystem, false));
  // D-pad down - drive forwards to line
  frc2::Trigger([this]{return controller.GetPOV() == 0;}).ToggleWhenActive(DriveToLineCommand(&driveSubsystem, true));
  frc2::JoystickButton(&controller, frc::XboxController::Button::kB).WhenPressed(shootCommand);
#else
  frc2::JoystickButton(&control2, 2).ToggleWhenPressed(toggle_intake_arm);
  frc2::JoystickButton(&control2, 1).WhenHeld(run_intake_roller);
  frc2::JoystickButton(&control2, 5).WhenHeld(reverse_outer_transport);
  frc2::JoystickButton(&control1, 1).WhenPressed(shootCommand);
  // drive backwards to line
  frc2::JoystickButton(&control1, 10).ToggleWhenPressed(DriveToLineCommand(&driveSubsystem, false));
  // drive forwards to line
  frc2::JoystickButton(&control1, 11).ToggleWhenPressed(DriveToLineCommand(&driveSubsystem, true));
#endif
  // controller independent triggers
  frc2::Trigger(auto_shift_condition).WhenActive(transport_inward_shift);
  
  // TODO list
  // - enable outer belt while roller running until ball present - automatic behaviour or button?
}

frc2::Command* RobotContainer::autonomousCommand() {
  *autocmd = frc2::SequentialCommandGroup(
    DriveToLineCommand(&driveSubsystem, false),
    frc2::InstantCommand([this] {
      transportSubsystem.enableInnerBelt();
      transportSubsystem.enableOuterBelt();
    }),
    frc2::WaitCommand(5.0_s),
    frc2::InstantCommand([this] {
      transportSubsystem.disableInnerBelt();
      transportSubsystem.disableOuterBelt();
    })
  );

  return autocmd;  
}

