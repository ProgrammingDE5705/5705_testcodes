/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

package frc.robot.subsystems;

import com.ctre.phoenix.motorcontrol.FeedbackDevice;
import com.ctre.phoenix.motorcontrol.StatusFrame;
import com.ctre.phoenix.motorcontrol.can.WPI_TalonSRX;

import edu.wpi.first.wpilibj.ADXRS450_Gyro;
import edu.wpi.first.wpilibj.Spark;
import edu.wpi.first.wpilibj.SPI.Port;
import edu.wpi.first.wpilibj.command.Subsystem;
import edu.wpi.first.wpilibj.drive.DifferentialDrive;
import frc.robot.commands.Drive;

/**
 * Add your docs here.
 */
public class Chassis extends Subsystem {
  // Put methods for controlling this subsystem
  // here. Call these from Commands.
  WPI_TalonSRX _left = null;
  Spark _right = null;

  ADXRS450_Gyro _gyro = null;

  DifferentialDrive m = null;
  
  public Chassis(){
    _left = new WPI_TalonSRX(2);
    _right = new Spark(6);
    _gyro = new ADXRS450_Gyro(Port.kOnboardCS0);
    m = new DifferentialDrive(_left, _right);

    _left.setInverted(false);
    _right.setInverted(true);

    _left.configFactoryDefault();
    _left.setStatusFramePeriod(StatusFrame.Status_2_Feedback0, 1);
    _left.configSelectedFeedbackSensor(FeedbackDevice.CTRE_MagEncoder_Relative);

    _gyro.reset();
    _gyro.calibrate();
    
  }

  public void arcadeDrive(double xSpeed, double zSpeed){
    m.arcadeDrive(xSpeed, zSpeed);
  }

  public double angle(){
    double angle = (_gyro.getAngle() % 360);

    if (angle == 0){
      return angle;
    }else{
      if ((angle * 360) < 0){
        return 360 + (angle * 360);
      }else{
      return angle * 360;
      }
    }
  }
  
 public double angleFinal(){
    return _gyro.getAngle();
  }

  public int position(){
    return _left.getSelectedSensorPosition(0);
  }

  public void resetEncoder(){
    _left.configSelectedFeedbackSensor(FeedbackDevice.CTRE_MagEncoder_Relative, 0, 0); /* PIDLoop=0,timeoutMs=0 */
		_left.setSelectedSensorPosition(0, 0, 10);
  }

  public void resetGyro(){
    _gyro.reset();
  }

  @Override
  public void initDefaultCommand() {
    setDefaultCommand(new Drive());
  }
}
