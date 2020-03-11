/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2020 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <string>

#include <frc/TimedRobot.h>
#include <frc/smartdashboard/SendableChooser.h>

class Robot : public frc::TimedRobot {
 public:
  void RobotInit() override;
  void RobotPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void DisabledInit() override;
  void DisabledPeriodic() override;
  void TestInit() override;
  void TestPeriodic() override;
  WPI_VictorSPX RightMaster {0};
  WPI_VictorSPX RightFollower {1};
  WPI_VictorSPX LeftMaster {2};
  WPI_VictorSPX LeftFollower {3};
  frc::DifferentialDrive Chassis{RightMaster, LeftMaster};
	//frc::DifferentialDrive * Chassis = new DifferentialDrive(*LeftMaster, *RightMaster);
  
  frc::VictorSP Feeder{0};
  frc::VictorSP Shooter{1};
  frc::Victor   Banda{2};

  frc::DoubleSolenoid baseA{0, 0, 1};
  frc::DoubleSolenoid baseB{0, 2, 3};

  frc::DoubleSolenoid topeA{0, 4, 5};
  frc::DoubleSolenoid topeB{0, 6, 7};
  frc::DoubleSolenoid Intaker{1, 0, 1};
  
  frc::Compressor *COMPER;
  //m_Compressor = new frc::Compressor(1);


  frc::VictorSP Feeder{0};
  frc::VictorSP Shooter{1};
  frc::Victor   Banda{2};

	frc::Joystick HMController{0};
  frc::Joystick TController{1};

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
  frc::SendableChooser<std::string> MenuAutonomos;
  const std::string NoAuto = "No hacer nada, Default";
  const std::string AutoDerecha = "Autonomo Derecha"; //1111,2222,3333
  const std::string AutoCentral = "Autonomo Central";
  const std::string AutoIzquierda = "Autonomo Izquierda";



  std::string Autonomo_Seleccionado;
};

namespace DriveKO{
  constexpr int
  FrontRight = 3, FrontLeft = 1,
  BackRight = 0,  BackLeft = 2,
  bA1 = 0, bA2 = 1, bB1 = 2, bB2 = 3,
  tA1 = 4, tA2 = 5, tB1 = 6, tB2 = 7,
  tK1 = 0, tK2 = 2; 
  
  constexpr bool
  FRightB = false, FLeftB = false,
  BRightB = false,  BLeftB = false;
}