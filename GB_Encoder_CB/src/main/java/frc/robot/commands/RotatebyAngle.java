/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

package frc.robot.commands;

import edu.wpi.first.wpilibj.command.Command;
import frc.robot.Robot;

public class RotatebyAngle extends Command {
  double angle;
  double angleRef;

  private final double kPropportional = 0.03;

  public RotatebyAngle(double angleRef) {
    requires(Robot.chassis);
    this.angleRef = angleRef;
  }

  // Called just before this Command runs the first time
  @Override
  protected void initialize() {
  }

  // Called repeatedly when this Command is scheduled to run
  @Override
  protected void execute() {
    angle = Robot.chassis.angleFinal();

    double zSpeed = ((angleRef - angle)*kPropportional);

    Robot.chassis.arcadeDrive(0, 0.6);//velocity(zSpeed, 0.7));
  }

  // Make this return true when this Command no longer needs to run execute()
  @Override
  protected boolean isFinished() {
    return angle == (angleRef);
  }

  // Called once after isFinished returns true
  @Override
  protected void end() {
    Robot.chassis.arcadeDrive(0, 0);
  }

  // Called when another command which requires one or more of the same
  // subsystems is scheduled to run
  @Override
  protected void interrupted() {
    end();
  }

  double velocity(double speed, double maxSpeed){
    if (speed >= maxSpeed) speed = maxSpeed;
    else if (speed <= -maxSpeed) speed = -maxSpeed;
    return speed;
  }
}
