/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/SubsystemBase.h>

class Robot_K : public frc2::SubsystemBase {
 public:
  Robot_K();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic();

 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
};

namespace DriveK{
  constexpr int
  FrontRight = 1, FrontLeft = 2,
  BackRight = 3,  BackLeft = 4;
  
  constexpr bool
  FRightB = false, FLeftB = false,
  BRightB = false,  BLeftB = false;

}