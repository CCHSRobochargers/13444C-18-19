#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, dgtl11, nearflag,       sensorDigitalIn)
#pragma config(Sensor, dgtl12, blue,           sensorDigitalIn)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_2,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port2,           rightMotor1,   tmotorVex393_MC29, openLoop, reversed, encoderPort, I2C_1)
#pragma config(Motor,  port3,           leftMotor1,    tmotorVex393_MC29, openLoop, encoderPort, I2C_2)
#pragma config(Motor,  port4,           rightMotor2,   tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           leftMotor2,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           liftMotor,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           wristMotor,    tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*        Description: Competition template for VEX EDR                      */
/*                                                                           */
/*---------------------------------------------------------------------------*/

static const float ticksPerInch = 0.95 * (627.2 / (4.0 * PI));
//adjust to compensate for wheel slip
static const float ticksPerDeg = 1.02 * (ticksPerInch * 12.0 * PI) / 360.0;

// This code is for the VEX cortex platform
#pragma platform(VEX2)

// Select Download method as "competition"
#pragma competitionControl(Competition)

// Select Download method as "competition"
#pragma competitionControl(OFF)
#pragma autonomousDuration(15)
#pragma userControlDuration(105)

//Main competition background code...do not modify!
#include "Vex_Competition_Includes.c"

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void move(float dist, int speed, bool hold)
{
	resetMotorEncoder(rightMotor1);
	resetMotorEncoder(leftMotor1);

	setMotorTarget(rightMotor1, dist*ticksPerInch, speed, hold);
	setMotorTarget(leftMotor1, dist*ticksPerInch, speed, hold);
	// printf("%f", dist*ticksPerInch);

	while (!getMotorTargetCompleted(rightMotor1) && !getMotorTargetCompleted(leftMotor1))
		wait1Msec(10);
}

void spin(float deg, int speed, bool hold)
{
	resetMotorEncoder(rightMotor1);
	resetMotorEncoder(leftMotor1);

	setMotorTarget(rightMotor1, deg*ticksPerDeg, speed, hold);
	setMotorTarget(leftMotor1, -deg*ticksPerDeg, speed, hold);

	while (!getMotorTargetCompleted(rightMotor1) && !getMotorTargetCompleted(leftMotor1))
		wait1Msec(10);
}



void pre_auton()
{
	// Set bStopTasksBetweenModes to false if you want to keep user created tasks
	// running between Autonomous and Driver controlled modes. You will need to
	// manage all user created tasks if set to false.
	bStopTasksBetweenModes = true;

	// Set bDisplayCompetitionStatusOnLcd to false if you don't want the LCD
	// used by the competition include file, for example, you might want
	// to display your team name on the LCD in this function.
	// bDisplayCompetitionStatusOnLcd = false;

	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...
	//The Motors are slaved because we had to change to
	slaveMotor(leftMotor2, leftMotor1);
	slaveMotor(rightMotor2, rightMotor1);
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

task autonomous()
{
		//moves even with cap
		move(12, 127, false); //moves 12 inches forward
		spin(-90, 127, false); //turns 90 degrees left

		move(6, 127, false); //robot moves up to the cap and lifts it, flips it, lowers cascade
		motor[liftMotor] =-50;
		wait1Msec(1000);
		motor[liftMotor] =0;

		move(-12, 127, false); //robot moves backward
		spin(90, 127, false); //turns right
		move(36, 127, false); //moves forward 3 feet and turns flag

		move(-6, 127, false); //robot moves back
		motor[liftMotor] =-50;
		wait1Msec(900);
		motor[liftMotor] =0; //the lift is lowered
}
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

task usercontrol()
{
	// User control code here, inside the loop

	while(1 == 1)
	{
		//Driving Motor Control
		motor[leftMotor1] = vexRT[Ch3] / 2;
		motor[rightMotor1] = vexRT[Ch2] / 2;

		//Lift Control (2nd controller)
		if(vexRT[Btn6U] == 1)
		{
			motor[liftMotor] = 200;
		}
		else if(vexRT[Btn6D] == 1)
		{
			motor[liftMotor] = -40;
		}
		else
		{
			motor[liftMotor] = 0;
		}

		//claw control
		//if(vexRT[Btn5U] == 1)       	//If Button 6U is pressed...
		//{
		//motor[wristMotor] = 127;  		//...close the gripper.
		//}
		//else if(vexRT[Btn5D] == 1)  	//Else, if button 6D is pressed...
		//{
		//motor[wristMotor] = -127; 		//...open the gripper.
		//}
		//else                      		//Else (neither button is pressed)...
		//{
		//motor[wristMotor] = 0;    		//...stop the gripper.
		//}
		//delay(10);
	}
}
