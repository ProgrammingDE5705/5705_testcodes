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