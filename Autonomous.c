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

//Wait for Press--------------------------------------------------
void waitForPress()
{
	while(nLCDButtons == 0){}
	wait1Msec(5);
}
//----------------------------------------------------------------

//Wait for Release------------------------------------------------
void waitForRelease()
{
	while(nLCDButtons != 0){}
	wait1Msec(5);
}
//----------------------------------------------------------------

task main()
{
	//Declare count variable to keep track of our choice
	int count = 0;

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
			displayLCDCenteredString(0, "Autonomous 1");
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
				count++;
			}
			break;
		case 1:
			//Display second choice
			displayLCDCenteredString(0, "Autonomous 2");
			displayLCDCenteredString(1, "<		 Enter		>");
			waitForPress();
			//Increment or decrement "count" based on button press
			if(nLCDButtons == leftButton)
			{
				waitForRelease();
				count--;
			}
			else if(nLCDButtons == rightButton)
			{
				waitForRelease();
				count++;
			}
			break;
		case 2:
			//Display third choice
			displayLCDCenteredString(0, "Autonomous 3");
			displayLCDCenteredString(1, "<		 Enter		>");
			waitForPress();
			//Increment or decrement "count" based on button press
			if(nLCDButtons == leftButton)
			{
				waitForRelease();
				count--;
			}
			else if(nLCDButtons == rightButton)
			{
				waitForRelease();
				count++;
			}
			break;
		case 3:
			//Display fourth choice
			displayLCDCenteredString(0, "Autonomous 4");
			displayLCDCenteredString(1, "<		 Enter		>");
			waitForPress();
			//Increment or decrement "count" based on button press
			if(nLCDButtons == leftButton)
			{
				waitForRelease();
				count--;
			}
			else if(nLCDButtons == rightButton)
			{
				waitForRelease();
				count = 0;
			}
			break;
		default:
			count = 0;
			break;
		}
	}
	//------------- End of User Interface Code ---------------------

	//------------- Beginning of Robot Movement Code ---------------
	//Clear LCD
	clearLCDLine(0);
	clearLCDLine(1);
	//Switch Case that actually runs the user choice
	switch(count){
	case 0:
		//If count = 0, run the code correspoinding with choice 1
		displayLCDCenteredString(0, "BlueFlag");
		displayLCDCenteredString(1, "is running!");
		wait1Msec(2000);						// Robot waits for 2000 milliseconds

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
		task autonomous()
		{
			// Move reverse at full power for 3 seconds
			motor[rightMotor] = -127;			// Motor on port2 is run at full (-127) power reverse
			motor[leftMotor]	= -127;			// Motor on port3 is run at full (-127) power reverse
			wait1Msec(3000);							// Robot runs previous code for 3000 milliseconds before moving on
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

		//Lift Control
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
		break;
	case 1:
		//If count = 1, run the code correspoinding with choice 2
		displayLCDCenteredString(0, "BlueNoFlag");
		displayLCDCenteredString(1, "is running!");
		wait1Msec(2000);						// Robot waits for 2000 milliseconds

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
		task autonomous()
		{
			// Move reverse at full power for 3 seconds
			motor[rightMotor] = -127;			// Motor on port2 is run at full (-127) power reverse
			motor[leftMotor]	= -127;			// Motor on port3 is run at full (-127) power reverse
			wait1Msec(3000);							// Robot runs previous code for 3000 milliseconds before moving on
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

		//Lift Control
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

		break;
	case 2:
		//If count = 2, run the code correspoinding with choice 3
		displayLCDCenteredString(0, "RedFlag");
		displayLCDCenteredString(1, "is running!");
		wait1Msec(2000);						// Robot waits for 2000 milliseconds

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
		task autonomous()
		{
		//Turn right for 3 seconds
		motor[rightMotor] = -63;			// Motor on port2 is run at half power reverse
		motor[leftMotor]	= 63;				// Motor on port3 is run at half power forward
		wait1Msec(3000);							// Robot runs previous code for 3000 milliseconds before moving on
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

		//Lift Control
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

		break;
	case 3:
		//If count = 3, run the code correspoinding with choice 4
		displayLCDCenteredString(0, "RedNoFlag");
		displayLCDCenteredString(1, "is running!");
		wait1Msec(2000);						// Robot waits for 2000 milliseconds

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
		task autonomous()
		{

		//Turn left for 3 seconds
		motor[rightMotor] = 63;				// Motor on port2 is run at half power forward
		motor[leftMotor]	= -63;			// Motor on port3 is run at half power reverse
		wait1Msec(3000);							// Robot runs previous code for 3000 milliseconds before moving on
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

		//Lift Control
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
		break;
	default:
		displayLCDCenteredString(0, "You Idiot!");
		displayLCDCenteredString(1, "it broke");
		break;
	}
	//------------- End of Robot Movement Code -----------------------
}

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

		//Lift Control
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
