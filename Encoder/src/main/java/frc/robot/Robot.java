/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

package frc.robot;

import edu.wpi.first.wpilibj.TimedRobot;
import edu.wpi.first.wpilibj.drive.DifferentialDrive;
import edu.wpi.first.wpilibj.Joystick;
import edu.wpi.first.wpilibj.Solenoid;
import edu.wpi.first.wpilibj.Spark;
import edu.wpi.first.wpilibj.smartdashboard.SmartDashboard;

import com.ctre.phoenix.motorcontrol.ControlMode;
import com.ctre.phoenix.motorcontrol.FeedbackDevice;
import com.ctre.phoenix.motorcontrol.StatusFrameEnhanced;
import com.ctre.phoenix.motorcontrol.can.*;

public class Robot extends TimedRobot {
	private double position;
	private final Object imgLock = new Object();
	/** Hardware */
	// VictorSPX _vic = new VictorSPX(1);		// Follower MC, Could be a victor
	WPI_TalonSRX _tal = new WPI_TalonSRX(2);		// Master MC, Talon SRX for Mag Encoder
	Spark mot = new Spark(6);
	Joystick _joystick = new Joystick(0);	// Joystick for project control
	DifferentialDrive m = new DifferentialDrive(_tal, mot);
	/* Simple thread to plot sensor velocity */
	PlotThread _plotThread;

	public void teleopInit() {
		/* Factory default hardware to prevent unexpected behavior */
		// _vic.configFactoryDefault();
		_tal.configFactoryDefault();
		_tal.setInverted(true);

		/* Victor will follow Talon */
		//_vic.follow(_tal);

		/* New frame every 1ms, since this is a test project use up as much
		 * bandwidth as possible for the purpose of this test.
		 */
		_tal.setStatusFramePeriod(StatusFrameEnhanced.Status_2_Feedback0, 1);
		_tal.configSelectedFeedbackSensor(FeedbackDevice.CTRE_MagEncoder_Relative);

		/* Fire the plotter */
		_plotThread = new PlotThread(this);
		new Thread(_plotThread).start();
	}

	public void teleopPeriodic() {
		/**
		 * If there is mechanical deflection, eccentricity, or damage in the
		 * sensor it should be revealed in the plot.
		 * 
		 * For example, an optical encoder with a partially damaged ring will
		 * reveal a periodic dip in the sensed velocity synchronous with each
		 * rotation.
		 * 
		 * This can also be wired to a gamepad to test velocity sweeping.
		 */
		boolean bo = SmartDashboard.getBoolean("ResetEncoder", false);
			  double distance = 9000;
			  double kProportional = 0.0001;
			  double SpeedY = -((distance - this.position)*kProportional);
		if (_joystick.getRawButton(1)){
			//public void resetEncoders() {
				
				System.out.println("Encoders reset!");
				//}
			}
			else {
				_tal.set(ControlMode.PercentOutput, 0.0);	// 0% Output
			}
			if (bo) {
				_tal.configSelectedFeedbackSensor(FeedbackDevice.CTRE_MagEncoder_Relative, 0, 0); /* PIDLoop=0,timeoutMs=0 */
				_tal.setSelectedSensorPosition(0, 0, 10);
			}
		SmartDashboard.putNumber("Speed", SpeedY);

		m.arcadeDrive(velocity(SpeedY, 0.7), 0);
		
		synchronized (imgLock){
			position = this.position;
		}
	}
	
  public double velocity(double speed, double maxSpeed){
	if (speed >= maxSpeed) speed = maxSpeed;
	else if (speed <= -maxSpeed) speed = -maxSpeed;
	return speed;
  }

  @Override
  public void disabledPeriodic(){
	  m.arcadeDrive(0, 0);
  }

	/** 
	 * Quick and dirty threaded plotter class
	 */
	class PlotThread implements Runnable {
		Robot robot;
		
		public PlotThread(Robot robot) {
			this.robot = robot;
		}

		public void run() {
			/**
			 * Speed up network tables, this is a test project so eat up all of
			 * the network possible for the purpose of this test.
			 */

			while (true) {
				/* Yield for a Ms or so - this is not meant to be accurate */
				try {
					Thread.sleep(1);
				} catch (Exception e) {
					/* Do Nothing */
				}

				/* Grab the latest signal update from our 1ms frame update */
				double velocity = this.robot._tal.getSelectedSensorVelocity(0);
				synchronized (imgLock){
				position = -this.robot._tal.getSelectedSensorPosition(0);
				}
		
			
        	SmartDashboard.putNumber("vel", velocity);
        	SmartDashboard.putNumber("pos", position);
			}
		}
	}
}