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
#include <frc2/command/WaitUntilCommand.h>
#include <frc2/command/FunctionalCommand.h>
#include <frc2/command/RunCommand.h>
#include <frc2/command/button/Trigger.h>

#include <units/time.h>

#include "commands/DriveCommand.h"
#include "commands/FlywheelCommand.h"
#include "commands/InwardShiftCommand.h"
#include "commands/DriveToLineCommand.h"
#include "commands/DriveUntilCommand.h"

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
  // extends/retracts the roller arm of the intake
  auto toggle_intake_arm = frc2::StartEndCommand(
    [this] {this->intakeSubsystem.extendArm();},
    [this] {this->intakeSubsystem.retractArm();},
    {&intakeSubsystem}
  );

  // Run the intake roller. Run it in reverse if button 10 pressed on Joystick, 
  // or left bumper pressed on Xbox controller.
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

  // Runs the outer transport belt in reverse
  auto reverse_outer_transport = frc2::StartEndCommand(
    [this] {transportSubsystem.reverseOuterBelt();},
    [this] {transportSubsystem.disableOuterBelt();},
    {&transportSubsystem}
  );

  auto auto_shift_condition = [this]{
    // return transportSubsystem.hasOuterBall() && !transportSubsystem.hasInnerBall();
    return !transportSubsystem.hasInnerBall();
  };
  // Shifts balls from outer position to inner position  
  auto transport_inward_shift = InwardShiftCommand(&transportSubsystem);

  // Runs the outer belt until it has a ball in place.
  auto transport_outer_load = frc2::FunctionalCommand(
    [this] {transportSubsystem.enableOuterBelt();},
    [this] {},
    [this] (bool){transportSubsystem.disableOuterBelt();},
    [this] {return transportSubsystem.hasOuterBall();},
    {&transportSubsystem}
  );

  auto toggle_lower_arms = frc2::InstantCommand([this]{climberSubsystem.toggleLower();});
  auto upper_arms_release = frc2::StartEndCommand(
    [this]{climberSubsystem.extendUpper();},
    [this]{climberSubsystem.retractUpper();},
    {&climberSubsystem}
  );

  // Performs the climbing procedure. Robot in permanent altered state for rest of game.
  auto climb = frc2::SequentialCommandGroup(
    frc2::InstantCommand([this]{climberSubsystem.retractLower();}),
    frc2::WaitUntilCommand([this]{return climberSubsystem.isRetracted();}),
    frc2::WaitCommand(0.5_s),
    frc2::InstantCommand([this]{climberSubsystem.extendUpper();}),
    frc2::WaitCommand(3.0_s),
    frc2::InstantCommand([this]{climberSubsystem.extendLower();}),
    frc2::WaitCommand(3.0_s),
    frc2::InstantCommand([this]{climberSubsystem.retractLower();})
  );
  climb.AddRequirements(&climberSubsystem);

  // Shifts a ball from the inner position to the shooter.
  auto shootCommand = frc2::SequentialCommandGroup(
    frc2::InstantCommand([this]{transportSubsystem.enableInnerBelt();}),
    frc2::WaitCommand(0.5_s)
  );
  shootCommand.AddRequirements(&transportSubsystem);

  // Both sets of bindings have equivalant capabilities. 
  // The only difference is which control scheme is being used.
#ifdef USE_XBOX_CONTROLS
  // Button bindings for Xbox Controller
  frc2::JoystickButton(&controller, frc::XboxController::Button::kX).ToggleWhenPressed(toggle_intake_arm);
  frc2::JoystickButton(&controller, frc::XboxController::Button::kY).WhenHeld(run_intake_roller);
  // D-pad left
  frc2::Trigger([this]{return controller.GetPOV() == 270;}).WhileActiveOnce(reverse_outer_transport);
  // D-pad down - drive backwards to line
  frc2::Trigger([this]{return controller.GetPOV() == 180;}).ToggleWhenActive(DriveToLineCommand(&driveSubsystem, false));
  // D-pad down - drive forwards to line
  frc2::Trigger([this]{return controller.GetPOV() == 0;}).ToggleWhenActive(DriveToLineCommand(&driveSubsystem, true));
  frc2::JoystickButton(&controller, frc::XboxController::Button::kB).WhenPressed(&shootCommand);
  frc2::JoystickButton(&controller, frc::XboxController::Button::kStart).WhenPressed(&climb);
  
  frc2::JoystickButton(&controller, frc::XboxController::Button::kA).WhenPressed(toggle_lower_arms);
  frc2::JoystickButton(&controller, frc::XboxController::Button::kA) && 
    frc2::JoystickButton(&controller, frc::XboxController::Button::kRightBumper).ToggleWhenActive(upper_arms_release);
#else
  // Button bindings for Joysticks.
  frc2::JoystickButton(&control2, 2).ToggleWhenPressed(toggle_intake_arm);
  frc2::JoystickButton(&control2, 1).WhenHeld(run_intake_roller);
  frc2::JoystickButton(&control2, 5).WhenHeld(reverse_outer_transport);
  frc2::JoystickButton(&control1, 1).WhenPressed(&shootCommand);
  // drive backwards to line
  frc2::JoystickButton(&control1, 10).ToggleWhenPressed(DriveToLineCommand(&driveSubsystem, false));
  // drive forwards to line
  frc2::JoystickButton(&control1, 11).ToggleWhenPressed(DriveToLineCommand(&driveSubsystem, true));
  frc2::JoystickButton(&control2, 8).WhenPressed(&climb);

  frc2::JoystickButton(&control2, 6).WhenPressed(toggle_lower_arms);
  frc2::JoystickButton(&control2, 5).ToggleWhenPressed(upper_arms_release);
#endif
  // controller independent triggers
  // shift outer balls inward until there is an inner ball
  frc2::Trigger(auto_shift_condition).WhenActive(transport_inward_shift);
  // run outer belt until there is an outer ball.
  frc2::Trigger([this] {return !transportSubsystem.hasOuterBall();}).WhenActive(transport_outer_load);
  
  // TODO list
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
    }),
    DriveUntilCommand(&driveSubsystem, false, [this]{return driveSubsystem.distance() > 72;})
    // }).WithInterrupt([this] {return driveSubsystem.distance() > 72;})
  );

  return autocmd;  
}

