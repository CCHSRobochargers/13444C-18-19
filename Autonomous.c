#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_2,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_3,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_4,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_5,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_6,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port2,           rightMotor1,   tmotorVex393_MC29, PIDControl, reversed, encoderPort, I2C_4)
#pragma config(Motor,  port3,           liftMotor,     tmotorVex393_MC29, openLoop, encoderPort, I2C_2)
#pragma config(Motor,  port4,           rightMotor2,   tmotorVex393_MC29, openLoop, reversed, encoderPort, I2C_3)
#pragma config(Motor,  port5,            ,             tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           leftMotor1,    tmotorVex393_MC29, PIDControl, encoderPort, I2C_5)
#pragma config(Motor,  port7,           leftMotor2,    tmotorVex393_MC29, openLoop, encoderPort, I2C_6)
#pragma config(Motor,  port8,           flipMotor,     tmotorVex393_MC29, PIDControl, encoderPort, I2C_1)
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

void fliplow()
{

	setMotorTarget(flipMotor, (-115*627)/360, 70, false);

	while (!getMotorTargetCompleted(flipMotor))
		wait1Msec(10);

}

void flipball()
{

	setMotorTarget(flipMotor, (-90*627)/360, 70, false);

	while (!getMotorTargetCompleted(flipMotor))
		wait1Msec(10);
}

void flipup()
{

	setMotorTarget(flipMotor, 0, 127, false);
	//outline: moveMotorTarget(nMotor, nEncoderCountTarget, nMaxSpeedToUse, bHoldAtEnd);

	while (!getMotorTargetCompleted(flipMotor))
		wait1Msec(10);

}

void flipdown()
{

	setMotorTarget(flipMotor, (-165*627)/360, 80, false);

	while (!getMotorTargetCompleted(flipMotor))
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


/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/


const short leftButton = 1;
const short centerButton = 2;
const short rightButton = 4;
int count = 0;

//Wait for Press--------------------------------------------------
void waitForPress()
{
	while(nLCDButtons == 0)
	{
		wait1Msec(5);
	}
}
//----------------------------------------------------------------

//Wait for Release------------------------------------------------
void waitForRelease()
{
	while(nLCDButtons != 0)
	{
		wait1Msec(5);
	}
}
//----------------------------------------------------------------


void pre_auton()
{
	// Set bStopTasksBetweenModes to false if you want to keep user created tasks
	// running between Autonomous and Driver controlled modes. You will need to
	// manage all user created tasks if set to false.

	bStopTasksBetweenModes = true;
	bLCDBacklight = true;
	resetMotorEncoder(flipMotor);

	// Set bDisplayCompetitionStatusOnLcd to false if you don't want the LCD
	// used by the competition include file, for example, you might want
	// to display your team name on the LCD in this function.
	// bDisplayCompetitionStatusOnLcd = false;

	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...
	//The Motors are slaved because we had to change to four motors from two and this was the easiest way to type it
	slaveMotor(leftMotor2, leftMotor1);
	slaveMotor(rightMotor2, rightMotor1);

	//Declare count variable to keep track of our choice


	//------------- Beginning of User Interface Code ---------------
	//Clear LCD
	clearLCDLine(0);
	clearLCDLine(1);

	//Loop while center button is not pressed

	while(nLCDButtons != centerButton)
	{

		//Switch case that allows the user to choose from 4 different options
		switch(count){
		case 0:
			//Display first choice
			displayLCDCenteredString(0, "Blue Flag");
			displayLCDCenteredString(1, "<		 Enter		>");
			waitForPress();
			//Increment or decrement "count" based on button press
			if(nLCDButtons == leftButton)
			{
				waitForRelease();
				count = 7;
			}
			else if(nLCDButtons == rightButton)
			{
				waitForRelease();
				count = 1;
			}
			break;
		case 1:
			//Display second choice
			displayLCDCenteredString(0, "Blue Platform");
			displayLCDCenteredString(1, "<		 Enter		>");
			waitForPress();
			//Increment or decrement "count" based on button press
			if(nLCDButtons == leftButton)
			{
				waitForRelease();
				count = 0;
			}
			else if(nLCDButtons == rightButton)
			{
				waitForRelease();
				count = 2;
			}
			break;
		case 2:
			//Display third choice
			displayLCDCenteredString(0, "Blue 2 Cap");
			displayLCDCenteredString(1, "<		 Enter		>");
			waitForPress();
			//Increment or decrement "count" based on button press
			if(nLCDButtons == leftButton)
			{
				waitForRelease();
				count = 1;
			}
			else if(nLCDButtons == rightButton)
			{
				waitForRelease();
				count = 3;
			}
			break;
		case 3:
			//Display fourth choice
			displayLCDCenteredString(0, "RedFlagSide");
			displayLCDCenteredString(1, "<		 Enter		>");
			waitForPress();
			//Increment or decrement "count" based on button press
			if(nLCDButtons == leftButton)
			{
				waitForRelease();
				count = 2;
			}
			else if(nLCDButtons == rightButton)
			{
				waitForRelease();
				count = 4;
			}
			break;
		case 4:
			//Display fifth choice
			displayLCDCenteredString(0, "Red Platform");
			displayLCDCenteredString(1, "<		 Enter		>");
			waitForPress();
			//Increment or decrement "count" based on button press
			if(nLCDButtons == leftButton)
			{
				waitForRelease();
				count = 3;
			}
			else if(nLCDButtons == rightButton)
			{
				waitForRelease();
				count = 5;
			}
			break;
		case 5:
		//Display sixth choice
			displayLCDCenteredString(0, "Red 2 Caps");
			displayLCDCenteredString(1, "<		 Enter		>");
			waitForPress();
			//Increment or decrement "count" based on button press
			if(nLCDButtons == leftButton)
			{
				waitForRelease();
				count = 4;
			}
			else if(nLCDButtons == rightButton)
			{
				waitForRelease();
				count = 6;
			}
			break;
		case 6:
			//Display seventh choice
			displayLCDCenteredString(0, "No Autonomous");
			displayLCDCenteredString(1, "<		Enter		>");
			waitForPress();
			//Increment or decrement "count" based on button press
			if(nLCDButtons == leftButton)
			{
				waitForRelease();
				count = 5;
			}
			else if(nLCDButtons == rightButton)
			{
				waitForRelease();
				count = 7;
			}
			break;
		case 7:
			//Display eigth choice
			displayLCDCenteredString(0, "Skillz");
			displayLCDCenteredString(1, "<		Enter		>");
			waitForPress();
			//Increment or decrement "count" based on button press
			if(nLCDButtons == leftButton)
			{
				waitForRelease();
				count = 6;
			}
			else if(nLCDButtons == rightButton)
			{
				waitForRelease();
				count = 0;
			}
			break;
		default:
			count = -1;
			break;
		}
	}
}

//------------- End of User Interface Code ---------------------
task autonomous()
{
	//------------- Beginning of Robot Movement Code ---------------
	//Clear LCD
	clearLCDLine(0);
	clearLCDLine(1);
	//Switch Case that actually runs the user choice


	switch(count){
		//this case is the autonomous for the blue side closest to flag
	case 0:
		//If count = 0, run the code correspoinding with choice 1
		displayLCDCenteredString(0, "Blue Flag");
		displayLCDCenteredString(1, "is running!");

		move(45, 127, false); //robot goes up to and turn flag

		move(-25, 127, false); //robot go backward

		spin(-100, 127, false); //robot turns right so the back is facing the cap

		move(6, 127, false); //robot moves forward 6 inches to provide space
		//for the flipper to come down

		flipdown(); //flipper goes down

		move(-12, 127, false); //robot goes in reverse and goes under the cap

		flipup(); //flipper goes up

		break;
		//this case is the autonomous for the blue side away from flag
	case 1:
		//If count = 1, run the code correspoinding with choice 2
		displayLCDCenteredString(0, "Blue Platform");
		displayLCDCenteredString(1, "is running!");

		fliplow();

		move(-38, 127, false); //goes forward to the cap

		flipball();

		move(4, 127, false); //goes backward 4 inches to avoid ball

		flipup(); //flipper comes up so it doesn't hook on platform

		move(-1, 127, false); //moves so that when the robot turns it is centered on the platform

		spin(-100, 127, false); //turns 90 degrees to the right

		move(10, 127, false); //robot moves back to build momentum

		move(-41, 127, false); //goes onto platform

		break;

		//this case is the autonomous for the red side near the flag
	case 2:
		//If count = 2, run the code correspoinding with choice 3
		displayLCDCenteredString(0, "Blue 2 Caps");
		displayLCDCenteredString(1, "is running!");

		fliplow();

		move(-38, 127, false); //goes forward to the cap

		flipball();

		move(9, 127, false); //goes backward 9 inches to avoid ball

		flipup(); //flipper comes up so it doesn't hook on platform

		spin(68, 127, false); //robot turns to line up with the other cap

		flipdown(); //flipper comes down

		move(-13, 127, false); //robot moves under the other cap

		flipup(); //flipper flips cap

		break;

		case 3:
		//If count = 3, run the code correspoinding with choice 4
		displayLCDCenteredString(0, "RedFlagSide");
		displayLCDCenteredString(1, "is running!");

		//robot goes forward 44 inches and turns the flag
		move(43, 127, false);

		//robot moves backward to score the flag and gete into position with the nearby cap
		move(-15, 127, false);

		//flipper comes down to flip cap
		flipdown();

		//turns left lining up the flipper with the cap
		spin(90, 127, false);

		move(-4, 100, false);

		flipup();

		break;

		//this case is the autonomous for the red side away from flag
	case 4:
		//If count = 4, run the code correspoinding with choice 5
		displayLCDCenteredString(0, "Red Platform");
		displayLCDCenteredString(1, "is running!");

		fliplow();

		move(-38, 110, false); //goes forward to the cap

		flipball();

		move(4, 127, false); //goes backward 4 inches to avoid ball

		flipup(); //flipper comes up so it doesn't hook on platform

		move(-2, 127, false); //moves so that when the robot turns it is centered on the platform

		spin(100, 127, false); //turns 90 degrees to the right

		move(10, 127, false); //robot moves back to build momentum

		move(-40, 127, false); //goes onto platform

		break;

		case 5:
		//If count = 5, run the code correspoinding with choice 6
		displayLCDCenteredString(0, "Red 2 Caps");
		displayLCDCenteredString(1, "is running!");

		fliplow();

		move(-38, 127, false); //goes forward to the cap

		flipball();

		move(9, 127, false); //goes backward 9 inches to avoid ball

		flipup(); //flipper comes up so it doesn't hook on platform

		spin(-60, 127, false); //robot turns to line up with the other cap

		flipdown(); //flipper comes down

		move(-13, 127, false); //robot moves under the other cap

		flipup(); //flipper flips cap

		break;

		//this case is for the potential instance where we would not want to run an autonomous
	case 6:
		//If count = 6, run the code correspoinding with choice 7
		displayLCDCenteredString(0, "NoAutonomous");
		displayLCDCenteredString(1, "is running!");

		break;

		//This is the auton for our skills run
		case 7:
		//If count = 7, run the code correspoinding with choice 8
		displayLCDCenteredString(0, "Skillz");
		displayLCDCenteredString(1, "is running!");

		//robot hits flag
		move(44, 127, false);

		//robot backs up from the flag
		move(-22, 127, false);

		//flipper comes down
		flipdown();

		//the robot turns to line up the flipper with the cap
		spin(45, 127, false);

		//

		break;

	default:
		displayLCDCenteredString(0, "You Idiot!");
		displayLCDCenteredString(1, "it broke");

		break;
	}
	//------------- End of Robot Autonomous Movement Code -----------------------
bLCDBacklight = false;
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

	nMotorPIDSpeedCtrl[leftMotor1] = RegIdle;
	nMotorPIDSpeedCtrl[rightMotor1] = RegIdle;
	nMotorPIDSpeedCtrl[flipMotor] = RegIdle;

	while(1 == 1)
	{

		//Lift Control
		if(vexRT[Btn6UXmtr2] == 1)
		{
			motor[liftMotor] = 127;
		}
		else if(vexRT[Btn6DXmtr2] == 1)
		{
			motor[liftMotor] = -40;
		}
		else
		{
			motor[liftMotor] = 0;
		}

		//Flipper Control
		if (vexRT[Btn5UXmtr2] == 1)
		{
			motor[flipMotor] = 127;
		}
		else if (vexRT[Btn5DXmtr2] == 1)
		{
			motor[flipMotor] = -50;
		}
		else
		{
			motor[flipMotor] = 0;
		}

		//this function defines the quarter speed button and the joystick controls
		if (vexRT[Btn5U] == 1)
		{
			//while the 5U button is pressed the motors will move at quarter speed
			motor[leftMotor1] = (vexRT[Ch3] / 2)/2;
			motor[rightMotor1] = (vexRT[Ch2] / 2)/2;
		}

		else
		{
			//Driving Motor Control
			motor[leftMotor1] = vexRT[Ch3];
			motor[rightMotor1] = vexRT[Ch2];
		}

		//delays so the computer doesn't overload trying to run the loop
		delay(10);
	}
}
