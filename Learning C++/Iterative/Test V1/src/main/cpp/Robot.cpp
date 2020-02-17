/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019-2020 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <iostream>
#include <string>
#include <Robot_K.h>
// #include <frc/WPILib.h>  // uncomment to include everything

#include "frc/drive/DifferentialDrive.h"
#include "frc/TimedRobot.h"
#include "frc/Joystick.h"
#include "ctre/Phoenix.h"
//#include <Victor.h>
//#include <VictorSP.h>
using namespace frc;
using namespace DriveK;

class Robot: public TimedRobot {
public:
	/* ------ Update CAN ID's Where necessary ------*/

	WPI_VictorSPX * RightMaster = new WPI_VictorSPX(FrontRight);
	WPI_VictorSPX * RightFollower = new WPI_VictorSPX(BackRight);
	WPI_VictorSPX * LeftMaster = new WPI_VictorSPX(FrontLeft);
	WPI_VictorSPX * LeftFollower = new WPI_VictorSPX(BackLeft);

	DifferentialDrive * Chassis = new DifferentialDrive(*LeftMaster, *RightMaster);

	Joystick * HMController = new Joystick(0);

	void RobotInit() {
		/* Factory default values */
		RightMaster->ConfigFactoryDefault();
		RightFollower->ConfigFactoryDefault();
		LeftMaster->ConfigFactoryDefault();
		LeftFollower->ConfigFactoryDefault();

		/* Set up followers */
		RightFollower->Follow(*RightMaster);
		LeftFollower->Follow(*LeftMaster);

		/* Set rotation clockwise or counter-clockwise according to your cable management*/
		RightMaster->SetInverted(FRightB);
		RightFollower->SetInverted(BRightB);
		LeftMaster->SetInverted(FLeftB);
		LeftFollower->SetInverted(BLeftB);


		Chassis->SetRightSideInverted(false);
	}

	void TeleopPeriodic() { //Function where the robot is operated by some kid

		std::stringstream work;
		/* Get controller stick's values */
		double Forward = -1 * HMController->GetRawAxis(1); /* positive is Forwardard */
		double Rotation = +1 * HMController->GetRawAxis(4); /* positive is right */

		/* Drive robot */
		Chassis->ArcadeDrive(Forward, Rotation, false);	
	}

private:
};

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif