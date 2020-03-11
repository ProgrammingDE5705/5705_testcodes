/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
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
#include "RobotC.h"
#include "string"

using namespace frc;
using namespace DriveKO;

class Robot : public frc::TimedRobot {
 public:
  RobotInit() {
    Chassis.SetSafetyEnabled(true);
    TEMPO.Start();
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

  void AutonomousInit() override {
    TEMPO.Reset();
    TEMPO.Start();
    
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

  void AutonomousPeriodic() override {    
  if (Autonomo_Seleccionado == AutoDerecha){
    std::cout << "Auto de la derecha" << std::endl;
  }
  if (Autonomo_Seleccionado== AutoCentral){
    std::cout << "Auto del centro" << std::endl;
        // Drive for 2 seconds
    if (TEMPO.Get() < 2.0) {
      // Drive forwards half speed
      Chassis.ArcadeDrive(-0.5, 0.0);
    } else {
      // Stop robot
      Chassis.ArcadeDrive(0.0, 0.0);
    }
 
  }
  if(Autonomo_Seleccionado == AutoIzquierda){
    std::cout << "Auto de la izquierda" << std::endl;
  }
}

  void TeleopInit() override {}

  void TeleopPeriodic() override {

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

  void TestPeriodic() override {}
  void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() {}

void Robot::TestInit() {}

void Robot::TestPeriodic() {}


		/* Get controller stick's values */
		double Forward = -1 * HMController.GetRawAxis(1); /* positive is Forwardard */
		double Rotation = 1 * HMController.GetRawAxis(2); /* positive is right */
    bool Shoot = TController.GetRawButton(1);
    bool Transport = TController.GetRawButton(2);
    bool Feed = TController.GetRawButton(6);
    //
    bool upBase = HMController.GetRawButtonPressed(3);        // B
    bool downBase = HMController.GetRawButtonPressed(4);      // 
    bool upTope = HMController.GetRawButtonPressed(1);        //
    bool downTope = HMController.GetRawButtonPressed(2);      //
    bool COMPEROn = HMController.GetRawButtonPressed(5);  //
    bool COMPEROff = HMController.GetRawButtonPressed(6); //

 private:
  //All the shit
  WPI_VictorSPX RightMaster {FrontRight};
  WPI_VictorSPX RightFollower {BackRight};
  WPI_VictorSPX LeftMaster {FrontLeft};
  WPI_VictorSPX LeftFollower {BackLeft};
  frc::DifferentialDrive Chassis{RightMaster, LeftMaster};
	//frc::DifferentialDrive * Chassis = new DifferentialDrive(*LeftMaster, *RightMaster);
  
  frc::VictorSP Feeder{0};
  frc::VictorSP Shooter{1};
  frc::Victor   Banda{2};

  frc::DoubleSolenoid baseA{0, bA1, bA2};
  frc::DoubleSolenoid baseB{0, bB1, bB2};

  frc::DoubleSolenoid topeA{0, tA1, tA2};
  frc::DoubleSolenoid topeB{0, tB1, tB2};
  frc::DoubleSolenoid Intaker{1, 0, 1};
  
  frc::Compressor *COMPER;
  //m_Compressor = new frc::Compressor(1);


  frc::VictorSP Feeder{0};
  frc::VictorSP Shooter{1};
  frc::Victor   Banda{2};

	frc::Joystick HMController{0};
  frc::Joystick TController{1};

  frc::LiveWindow& m_lw = *frc::LiveWindow::GetInstance();
  frc::Timer TEMPO;
};

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
