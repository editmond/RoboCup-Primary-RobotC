#pragma config(Sensor, S1,     MSLSA,          sensorEV3_GenericI2C)
#pragma config(Sensor, S2,     RightTouch,     sensorEV3_Touch)
#pragma config(Sensor, S3,     LeftTouch,      sensorEV3_Touch)
#pragma config(Sensor, S4,     EV3ultrasonic,  sensorEV3_Ultrasonic)
#pragma config(Motor,  motorB,          LeftM,         tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorC,          RightM,        tmotorEV3_Large, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "mindsensors-sumoeyes.h";
#include "mindsensors-lightsensorarray.h";
//==========================================================================================================
//Global varibles go here
int target = 0;
float turnmultiplyer = 0.255;
tByteArray signalstr;
//==========================================================================================================
//Subroutines go here
// hello
task lightSensorRefresh()
{
	while(true)
	{
		if (!MSLSAreadSensors(MSLSA, &signalstr[0]))
		{
			//eraseDisplay();
			playSound(soundException);
			//displayCenteredTextLine(4, "error!");
			//sleep(5000);
		}
	}
}
//====================================================================================================================================================================================
void rescue()
{
	setMotorSpeed(RightM, 0);
	setMotorSpeed(LeftM, 0);
	setMotorSpeed(RightM, 35);
	setMotorSpeed(LeftM, 35);
	wait1Msec(2000);
	setMotorSpeed(RightM, 0);
	setMotorSpeed(LeftM, 0);
	setMotorSpeed(RightM, 35);
	setMotorSpeed(LeftM, -35);
	wait1Msec(500);
	setMotorSpeed(RightM, 0);
	setMotorSpeed(LeftM, 0);
	wait1Msec(1000);
	while(signalstr[4] <= 20)
	{
		//writeDebugStreamLine("SumoZone: %d", SumoZone);
		while(SensorValue(EV3ultrasonic) <= 20 && signalstr[4] <= 20)
		{
			setMotorSpeed(RightM, 35);
			setMotorSpeed(LeftM, 35);
		}

		setMotorSpeed(RightM, 15);
		setMotorSpeed(LeftM, -15);

	}
	setMotorSpeed(RightM, 0);
	setMotorSpeed(LeftM, 0);
	wait1Msec(1000);
}
//==========================================================================================================
//Water tower.
//==========================================================================================================
void waterTower2()
{
	if (SensorValue(LeftTouch) == 1 && SensorValue(RightTouch) == 1)
	{
		setMotorSpeed(RightM, 0);
		setMotorSpeed(LeftM, 0);
		setMotorSpeed(RightM, -35);
		setMotorSpeed(LeftM, -35);
		wait1Msec(600);
		setMotorSpeed(RightM, 0);
		setMotorSpeed(LeftM, 0);
		wait1Msec(1000);
		setMotorSpeed(RightM, -35);
		setMotorSpeed(LeftM, 35);
		wait1Msec(500);
		// Stop all motors
		setMotorSpeed(RightM, 0);
		setMotorSpeed(LeftM, 0);
		// Move forward for 1 second
		setMotorSpeed(RightM, 35);
		setMotorSpeed(LeftM, 35);
		wait1Msec(1600);
		// Stop Motors
		setMotorSpeed(RightM, 0);
		setMotorSpeed(LeftM, 0);
		// Turn left
		setMotorSpeed(RightM, 35);
		setMotorSpeed(LeftM, -35);
		wait1Msec(500);
		// Stop
		setMotorSpeed(RightM, 0);
		setMotorSpeed(LeftM, 0);
		// Go forward
		setMotorSpeed(RightM, 35);
		setMotorSpeed(LeftM, 35);
		wait1Msec(1600);
		// Stop
		setMotorSpeed(RightM, 0);
		setMotorSpeed(LeftM, 0);
		// Turn Left
		setMotorSpeed(RightM, 35);
		setMotorSpeed(LeftM, -35);
		wait1Msec(500);
		setMotorSpeed(RightM, 0);
		setMotorSpeed(LeftM, 0);
		while(signalstr[4] >= 20)
		{
			setMotorSpeed(RightM, 35);
			setMotorSpeed(LeftM, 35);
		}
	}
}
//==========================================================================================================
//Line Follow
task main()
{
	startTask(lightSensorRefresh, 4);
	MSLSAinit(MSLSA);
	while(true)
	{
		int leftSideMSLSA = signalstr[0]*4 + signalstr[1]*3 + signalstr[2]*2 + signalstr[3]*1;
		int rightSideMSLSA = signalstr[4]*1 + signalstr[5]*2 + signalstr[6]*3 + signalstr[7]*4;
		int steering = (leftSideMSLSA - rightSideMSLSA - target)*turnmultiplyer;
		setMotorSync(LeftM, RightM, steering, 40);
		waterTower2();
		if(signalstr[0] <= 25 && signalstr[1] <= 25 && signalstr[2] <= 25 && signalstr[3] <= 25 && signalstr[4] <= 25 && signalstr[5] <= 25 && signalstr[6] <= 25 && signalstr[7] <= 25)
		{
			//playTone(400, 10);
			setMotorSpeed(RightM, 0);
			setMotorSpeed(LeftM, 0);
			setMotorSpeed(RightM, 35);
			setMotorSpeed(LeftM, 35);
			wait1Msec(500);
			setMotorSpeed(RightM, 0);
			setMotorSpeed(LeftM, 0);
			if (!MSLSAreadSensors(MSLSA, &signalstr[0]))
			{
				//eraseDisplay();
				playSound(soundException);
				//displayCenteredTextLine(4, "error!");
				//sleep(5000);
			}
			if(signalstr[0] <= 25 && signalstr[1] <= 25 && signalstr[2] <= 25 && signalstr[3] <= 25 && signalstr[4] <= 25 && signalstr[5] <= 25 && signalstr[6] <= 25 && signalstr[7] <= 25)
			{
				rescue();
			}
			else
			{
				//search
				setMotorSpeed(RightM, 0);
				setMotorSpeed(LeftM, 0);
				setMotorSpeed(RightM, -35);
				setMotorSpeed(LeftM, -35);
				wait1Msec(200);
			}
			//writeDebugStreamLine("Data: %d", signalstr[4]);
		}
	}
}
