/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2020 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "frc/smartdashboard/SendableChooser.h"
#include "frc/smartdashboard/SmartDashboard.h"
#include "frc/drive/DifferentialDrive.h"
#include "frc/DoubleSolenoid.h"
#include "frc/Compressor.h"
#include "frc/TimedRobot.h"
#include "frc/VictorSP.h"
#include "frc/Joystick.h"
#include "ctre/Phoenix.h"
#include "frc/Victor.h"
#include "iostream"
#include "Robot.h"
#include "string"

using namespace frc;
using namespace DriveKO;


void Robot::RobotInit() {

  MenuAutonomos.SetDefaultOption(NoAuto, NoAuto);
  MenuAutonomos.AddOption(AutoDerecha, AutoDerecha);
  MenuAutonomos.AddOption(AutoCentral, AutoCentral);
  MenuAutonomos.AddOption(AutoIzquierda, AutoIzquierda);
  frc::SmartDashboard::PutData("Autonomos Disponibles", &MenuAutonomos);

  		/* Factory default values */
		RightMaster.ConfigFactoryDefault();
		RightFollower.ConfigFactoryDefault();
		LeftMaster.ConfigFactoryDefault();
		LeftFollower.ConfigFactoryDefault();

		/* Set up followers */
		RightFollower.Follow(RightMaster);
		LeftFollower.Follow(LeftMaster);

		/* Set rotation clockwise or counter-clockwise according to your cable management*/
		RightMaster.SetInverted(FRightB);
		RightFollower.SetInverted(BRightB);
		LeftMaster.SetInverted(FLeftB);
		LeftFollower.SetInverted(BLeftB);
    
    baseA.Set(frc::DoubleSolenoid::kReverse);
    baseB.Set(frc::DoubleSolenoid::kReverse);

    topeA.Set(frc::DoubleSolenoid::kReverse);
    topeB.Set(frc::DoubleSolenoid::kReverse);

		Chassis.SetRightSideInverted(false);
}

void Robot::RobotPeriodic() {}

void Robot::AutonomousInit(){
  Autonomo_Seleccionado = MenuAutonomos.GetSelected();
/*
  if (Autonomo_Seleccionado == AutoDerecha){
    std::cout << "Auto de la derecha" << std::endl;
  }
  if (Autonomo_Seleccionado== AutoCentral){
    std::cout << "Auto del centro" << std::endl;
  }
  if(Autonomo_Seleccionado == AutoIzquierda){
    std::cout << "Auto de la izquierda" << std::endl;
  }
*/
}

void Robot::AutonomousPeriodic() {
  if (Autonomo_Seleccionado == AutoDerecha){
    std::cout << "Auto de la derecha" << std::endl;
  }
  if (Autonomo_Seleccionado== AutoCentral){
    std::cout << "Auto del centro" << std::endl;
  }
  if(Autonomo_Seleccionado == AutoIzquierda){
    std::cout << "Auto de la izquierda" << std::endl;
  }
}

void Robot::TeleopInit() {}

void Robot::TeleopPeriodic() {

		std::stringstream work;
    /* Drive robot */
		Chassis.ArcadeDrive(Rotation, Forward, false);	

    if(upBase == true){
          baseA.Set(frc::DoubleSolenoid::kForward);
    baseB.Set(frc::DoubleSolenoid::kForward);
}
    if(upTope == true){
            topeA.Set(frc::DoubleSolenoid::kForward);
    topeB.Set(frc::DoubleSolenoid::kForward);
}
    if(downBase == true){
          baseA.Set(frc::DoubleSolenoid::kReverse);
    baseB.Set(frc::DoubleSolenoid::kReverse);
}
    if(downTope == true){
            topeA.Set(frc::DoubleSolenoid::kReverse);
    topeB.Set(frc::DoubleSolenoid::kReverse);
}
    if(Shoot == true)
    {Shooter.Set(-1);}
    else{Shooter.Set(0);}

    if(Feed == true)
    {Feeder.Set(-1);}
    else{Feeder.Set(0);}

    if(Transport == true)
    {Banda.Set(1);}
    else{Banda.Set(0);}

}

void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() {}

void Robot::TestInit() {}

void Robot::TestPeriodic() {}


  
    
#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif