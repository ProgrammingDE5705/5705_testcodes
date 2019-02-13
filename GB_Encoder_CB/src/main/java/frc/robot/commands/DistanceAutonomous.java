/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

package frc.robot.commands;

import edu.wpi.first.wpilibj.command.Command;
import edu.wpi.first.wpilibj.smartdashboard.SmartDashboard;
import frc.robot.Robot;

public class DistanceAutonomous extends Command {
  double distance;
  int position;
  double angleRef;
  double angle;

  private final double kProportional = 0.0005;

  public DistanceAutonomous(double distanceUnits, double angleRef) {
    requires(Robot.chassis);
    distance = distanceUnits;
    this.angleRef = angleRef;
  }

  @Override
  protected void initialize() {
    Robot.chassis.resetEncoder();
  }

  // Called repeatedly when this Command is scheduled to run
  @Override
  protected void execute() {
    
    double xSpeed = ((distance - position)*kProportional);
    double zSpeed = ((angleRef - angle)*0.03);
    
    Robot.chassis.arcadeDrive(-velocity(xSpeed, 0.7, 0.4), 0);
    
    SmartDashboard.putNumber("Position", position);
    SmartDashboard.putNumber("SpeedX", xSpeed);
    SmartDashboard.putNumber("SpeedZ", zSpeed);
    SmartDashboard.putNumber("Gyro", angle);
  }
  
  // Make this return true when this Command no longer needs to run execute()
  @Override
  protected boolean isFinished() {
    angle = Robot.chassis.angleFinal();
    position = Robot.chassis.position();
    return Math.abs(position) >= Math.abs(distance-110);
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

  double velocity(double speed, double maxSpeed, double minSpeed){
    if (speed >= maxSpeed) speed = maxSpeed;
    else if (speed <= -maxSpeed) speed = -maxSpeed;
    else if(speed <= minSpeed && speed > 0) speed = minSpeed;
    else if(speed >= -minSpeed && speed < 0) speed = -minSpeed;
    return speed;
  }
}
