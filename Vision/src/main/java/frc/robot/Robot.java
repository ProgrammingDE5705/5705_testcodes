/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

package frc.robot;

import java.awt.Color;

import org.opencv.core.Mat;
import org.opencv.core.Point;
import org.opencv.core.Rect;
import org.opencv.core.Scalar;
import org.opencv.imgproc.Imgproc;
import org.w3c.dom.css.RGBColor;

import edu.wpi.cscore.UsbCamera;
import edu.wpi.first.cameraserver.CameraServer;
import edu.wpi.first.wpilibj.Spark;
import edu.wpi.first.wpilibj.TimedRobot;
import edu.wpi.first.wpilibj.buttons.NetworkButton;
import edu.wpi.first.wpilibj.drive.DifferentialDrive;
import edu.wpi.first.wpilibj.livewindow.LiveWindow;
import edu.wpi.first.wpilibj.networktables.NetworkTable;
import edu.wpi.first.wpilibj.smartdashboard.SendableChooser;
import edu.wpi.first.wpilibj.smartdashboard.SmartDashboard;
import edu.wpi.first.wpilibj.vision.VisionThread;

/**
 * The VM is configured to automatically run this class, and to call the
 * functions corresponding to each mode, as described in the TimedRobot
 * documentation. If you change the name of this class or the package after
 * creating this project, you must also update the build.gradle file in the
 * project.
 */
public class Robot extends TimedRobot {
  private static final String kDefaultAuto = "Default";
  private static final String kCustomAuto = "My Auto";
  private String m_autoSelected;
  private final SendableChooser<String> m_chooser = new SendableChooser<>();

  private double centerX, centerY;
  private double width_img;
  private double heigth_img;
  public Scalar colo;
  private final Object imgLock = new Object();
  VisionThread visionThread;

  boolean matched;
 
  public int IMG_WIDTH = 640;
  public int IMG_HEIGHT = 480;

  public Spark _One;
  public Spark _Two;
  public DifferentialDrive robotDrive;


  /**
   * This function is run when the robot is first started up and should be
   * used for any initialization code.
   */
  @Override
  public void robotInit() {
    UsbCamera cam0 = CameraServer.getInstance().startAutomaticCapture(0);
    m_chooser.setDefaultOption("Default Auto", kDefaultAuto);
    m_chooser.addOption("My Auto", kCustomAuto);
    SmartDashboard.putData("Auto choices", m_chooser);
    cam0.setBrightness(31);
    cam0.setResolution(IMG_WIDTH, IMG_HEIGHT);
    colo = new Scalar(255,255,255);
    // cam0.setExposureManual(55);

    

    visionThread = new VisionThread(cam0, new Pipeline(), pipeline->{
      if (!pipeline.filterContoursOutput().isEmpty()){
          Rect r = Imgproc.boundingRect(pipeline.filterContoursOutput().get(0));
        
          synchronized (imgLock) {
            centerX = r.x + (r.width / 2);
            centerY = r.y + (r.height / 2);
            width_img = r.x;
            heigth_img = r.y;
          }
         
      }
    });
    visionThread.start();

    _One = new Spark(5);
    LiveWindow.addActuator("DriveTrain", 5, _One);
    _Two = new Spark(4);
    
    robotDrive = new DifferentialDrive(_One, _Two);
  }

  /**
   * This function is called every robot packet, no matter the mode. Use
   * this for items like diagnostics that you want ran during disabled,
   * autonomous, teleoperated and test.
   *
   * <p>This runs after the mode specific periodic functions, but before
   * LiveWindow and SmartDashboard integrated updating.
   */
  @Override
  public void robotPeriodic() {
  }

  /**
   * This autonomous (along with the chooser code above) shows how to select
   * between different autonomous modes using the dashboard. The sendable
   * chooser code works with the Java SmartDashboard. If you prefer the
   * LabVIEW Dashboard, remove all of the chooser code and uncomment the
   * getString line to get the auto name from the text box below the Gyro
   *
   * <p>You can add additional auto modes by adding additional comparisons to
   * the switch structure below with additional strings. If using the
   * SendableChooser make sure to add them to the chooser code above as well.
   */
  @Override
  public void autonomousInit() {

    m_autoSelected = m_chooser.getSelected();
    // m_autoSelected = SmartDashboard.getString("Auto Selector", kDefaultAuto);
    System.out.println("Auto selected: " + m_autoSelected);
  }

  /**
   * This function is called periodically during autonomous.
   */
  @Override
  public void autonomousPeriodic() {
    
    double centerX, centerY;
    double width_img;
    
    synchronized(imgLock){
      centerX = this.centerX;
      centerY = this.centerY;
      width_img = this.width_img;
    }

    double turn = centerX - (IMG_WIDTH / 2);

    // ((turn * 0.005) / 2));
    
    if((centerX > 310) && (centerX < 330)){
      if((centerY > 230) && (centerY < 240)){
        matched = true;
      }
    }
    else {
      matched = false;
    }

    SmartDashboard.putNumber("Center X", centerX);
    SmartDashboard.putNumber("Center Y", centerY);
    SmartDashboard.putBoolean("Match", matched);

    SmartDashboard.putNumber("Width", width_img);


    robotDrive.arcadeDrive(-0.6, (turn * 0.005) / 2);

  }

  /**
   * This function is called periodically during operator control.
   */
  @Override
  public void teleopPeriodic() {
    
  }

  /**
   * This function is called periodically during test mode.
   */
  @Override
  public void testPeriodic() {
    LiveWindow.run();
  }
}
