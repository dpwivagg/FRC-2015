#include "WPILib.h"
#include "RobotMap.h"

class Robot: public SampleRobot
{
	RobotDrive giantRobot;
	Joystick stick_left;
	Joystick stick_right;
	Joystick gamepad;
	CANTalon lift;
	Talon arm_left;
	Talon arm_right;
	DigitalInput top_limit;
	DigitalInput bottom_limit;

	int *autoLoopCounter;

	Command *autonomousCommand;
	LiveWindow *lw;

public:
	Robot() :
		giantRobot(1,2,3,4),

		stick_left(0),
		stick_right(1),
		gamepad(2),


		lift(9),
		arm_left(6),
		arm_right(5),

		top_limit(2),
		bottom_limit(3),


		autoLoopCounter(0)
	{
		giantRobot.SetExpiration(0.1);
	}

	/**
	 * Drive left & right motors for 2 seconds then stop
	 */
	void Autonomous()
	{
		giantRobot.SetSafetyEnabled(false);
		while (IsAutonomous() && IsEnabled()) {
			giantRobot.Drive(-0.5, -0.5); 	// drive forwards half speed
			Wait(2.0); 				//    for 2 seconds
			giantRobot.Drive(0.0, 0.0); 	// stop robot
		}
	}

	/**
	 * Runs the motors with arcade steering.
	 */
	void OperatorControl()
	{
		giantRobot.SetSafetyEnabled(true);
		while (IsOperatorControl() && IsEnabled())
		{
			while(1==1){
			giantRobot.TankDrive(stick_left, stick_right); //tank drive
			giantRobot.SetInvertedMotor(RobotDrive::kFrontRightMotor, true);
			giantRobot.SetInvertedMotor(RobotDrive::kRearRightMotor, true);
			giantRobot.SetInvertedMotor(RobotDrive::kFrontLeftMotor, true);
			giantRobot.SetInvertedMotor(RobotDrive::kRearLeftMotor, true);

			//arm_left.Set(gamepad.GetRawAxis(5));
			//arm_left.Set(gamepad.GetRawAxis(5));



				if(top_limit.Get() == 0){
					arm_left.Set(0.1);
					arm_right.Set(0.1);
					Wait(0.5);
					arm_left.Set(0);
					arm_right.Set(0);
				}

				if(bottom_limit.Get() == 1){
					arm_left.Set(0);
					arm_right.Set(0);
					Wait(0.3);
				}

				else{
					arm_left.Set(gamepad.GetRawAxis(5) / 2);
					arm_left.Set(gamepad.GetRawAxis(5) / 2);
				}
			}




			Wait(0.005);				// wait for a motor update time


		}

	}

	/**
	 * Runs during test mode
	 */
	void Test()
	{
	}
};

START_ROBOT_CLASS(Robot);
