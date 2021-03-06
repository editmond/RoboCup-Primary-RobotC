/*--------------------------------------------------------*\
|*	- Natural Language for VEX IQ	Virtual Worlds	 -			*|
\*--------------------------------------------------------*/
#pragma once
#pragma systemFile            	// eliminates warning for "unreferenced" functions

#include "JoystickDriver.c"

/*
--------------- Enumerations and Defines ----------------------
*/

#define VexIQClawbot 0
const tMotor noMotorOnPort     = (tMotor) -1;
const tMotor noMotor     = (tMotor) -1;
#define nMaxJoyScaleValue 100


// enum for units
typedef enum tMovementUnits
{
	degrees							= 0,
	rotations						= 1,
	milliseconds				= 2,
	seconds							= 3,
	minutes							= 4
} tMovementUnits;

typedef enum tIQLCDLine
{
	line1				= 0,
	line2				= 1,
	line3				= 2,
	line4				= 3,
	line5				= 4
} tIQLCDLine;

bool bPopulatedMotorDriveSides = false;
TMotorList internalLeftMotors;
TMotorList internalRightMotors;
short nGlobalJoyScaledValue = nMaxJoyScaleValue;

/*
------------------- Utility Commands --------------------------
*/

void setJoystickScale(short nScaledPercentage = nMaxJoyScaleValue)
{
	if(nScaledPercentage > nMaxJoyScaleValue)
	{
		nGlobalJoyScaledValue = nMaxJoyScaleValue;
	}
	else if(nScaledPercentage < 0)
	{
		nGlobalJoyScaledValue = 0;
	}
	else
	{
		nGlobalJoyScaledValue = nScaledPercentage;
	}
}

void updateMotorDriveTrain()
{
	if(!bPopulatedMotorDriveSides)
	{
		getMotorsWithDriveSideType(driveRight, internalRightMotors);
		getMotorsWithDriveSideType(driveLeft,	 internalLeftMotors);
		bPopulatedMotorDriveSides = true;
	}
}

//This command is here only for LEGACY reasons (to prevent compiler errors)
void setRobotType(short robotType)
{
	return;
}

void displayButtonValues(tIQLCDLine lineNumber = line1, const TJoystickButtons nJoystickValue = Btn1)
{
	getJoystickSettings(joystick);
	string sOutputString;
	string sJoystickTemp;
	switch(nJoystickValue)
	{
		case Btn1:	sJoystickTemp = "Btn 01:";
					break;
		case Btn2:	sJoystickTemp = "Btn 02:";
					break;
		case Btn3:	sJoystickTemp = "Btn 03:";
					break;
		case Btn4:	sJoystickTemp = "Btn 04:";
					break;
		case Btn5:	sJoystickTemp = "Btn 05:";
					break;
		case Btn6:	sJoystickTemp = "Btn 06:";
					break;
		case Btn7:	sJoystickTemp = "Btn 07:";
					break;
		case Btn8:	sJoystickTemp = "Btn 08:";
					break;
		case Btn9:	sJoystickTemp = "Btn 09:";
					break;
		case Btn10:	sJoystickTemp = "Btn 10:";
					break;
		case Pov0:	sJoystickTemp = "POV 00:";
					break;
		case Pov1:	sJoystickTemp = "POV 01:";
					break;
		case Pov2:	sJoystickTemp = "POV 02:";
					break;
		case Pov3:	sJoystickTemp = "POV 03:";
					break;
		case Pov4:	sJoystickTemp = "POV 04:";
					break;
		case Pov5:	sJoystickTemp = "POV 05:";
					break;
		case Pov6:	sJoystickTemp = "POV 06:";
					break;
		case Pov7:	sJoystickTemp = "POV 07:";
					break;
	}
	sprintf(sOutputString, "%s %d", sJoystickTemp, joy1Btn(nJoystickValue));
	int nLineNumber = lineNumber;
	displayTextLine(nLineNumber, sOutputString);
}

void displayControllerValues(tIQLCDLine lineNumber = line1, const TJoystickAxis nJoystickValue = JoyX1)
{
	string sOutputString;
	string sJoystickTemp;

	getJoystickSettings(joystick);
	switch(nJoystickValue)
	{
	case JoyX1:		sJoystickTemp = "Channel X1:";
					sprintf(sOutputString, "%s %d", sJoystickTemp, joystick.joy1_x1);
					break;
	case JoyY1:		sJoystickTemp = "Channel Y1:";
					sprintf(sOutputString, "%s %d", sJoystickTemp, joystick.joy1_y1);
					break;
	case JoyX2:		sJoystickTemp = "Channel X2:";
					sprintf(sOutputString, "%s %d", sJoystickTemp, joystick.joy1_x2);
					break;
	case JoyY2:		sJoystickTemp = "Channel Y2:";
					sprintf(sOutputString, "%s %d", sJoystickTemp, joystick.joy1_y2);
					break;
	}

	int nLineNumber = lineNumber;
	displayTextLine(nLineNumber, sOutputString);
}

void displayMotorValues(tIQLCDLine lineNumber = line1, const tMotor nDeviceIndex = motor1)
{
	TVexIQDeviceTypes nDeviceType;
	TDeviceStatus nDeviceStatus;
	short nDeviceVersion;

	getVexIqDeviceInfo(nDeviceIndex, nDeviceType, nDeviceStatus, nDeviceVersion);
	string sOutputString;

	//No device found.
	if (nDeviceType != vexIQ_SensorMOTOR)
		return;

	sprintf(sOutputString, "Motor(%d) %d deg", nDeviceIndex + 1 , getMotorEncoder((tMotor)nDeviceIndex));
	int nLineNumber = lineNumber;
	displayTextLine(nLineNumber, sOutputString);
}

void displaySensorValues(tIQLCDLine lineNumber = line1, const tSensors nDeviceIndex = port1)
{
	TVexIQDeviceTypes nDeviceType;
	TDeviceStatus nDeviceStatus;
	short nDeviceVersion = 0;
	string sOutputString;
	string sColorTemp;
	int tempValue = 0;

	getVexIqDeviceInfo(nDeviceIndex, nDeviceType, nDeviceStatus, nDeviceVersion);

	if (nDeviceType == vexIQ_SensorNone || nDeviceType == vexIQ_SensorMOTOR)
		return;

	switch (nDeviceType)
	{
	case vexIQ_SensorMOTOR:
		sprintf(sOutputString, "Motor(%d) %d deg", nDeviceIndex + 1 , getMotorEncoder((tMotor)nDeviceIndex));
		break;

	case vexIQ_SensorLED:
		sprintf(sOutputString, "LED(%d) %s", nDeviceIndex + 1, getTouchLEDValue(nDeviceIndex) ? "Pressed" : "Released");
		break;

	case vexIQ_SensorRGB:
		if(getColorMode(nDeviceIndex) == colorTypeGrayscale_Reflected)
		{
			tempValue = getColorGrayscale(nDeviceIndex);
			sprintf(sOutputString, "Color(%d) %d/%d", nDeviceIndex + 1, tempValue, getColorProximity(nDeviceIndex));
		}
		else if(getColorMode(nDeviceIndex) == colorTypeRGB_Hue_Ambient)
		{
			tempValue = getColorHue(nDeviceIndex);
			sprintf(sOutputString, "Color(%d) %d/%d", nDeviceIndex + 1, tempValue, getColorProximity(nDeviceIndex));
		}
		else if(getColorMode(nDeviceIndex) == colorTypeRGB_12Colors_Ambient)
		{
			switch(getColorName(nDeviceIndex))
			{
				case colorRedViolet:	sColorTemp = "RedViolet";	break;
				case colorRed:			sColorTemp = "Red";			break;
				case colorDarkOrange:	sColorTemp = "DarkOrange";	break;
				case colorOrange:		sColorTemp = "Orange";		break;
				case colorDarkYellow:	sColorTemp = "DarkYellow";	break;
				case colorYellow:		sColorTemp = "Yellow";		break;
				case colorLimeGreen:	sColorTemp = "LimeGreen";	break;
				case colorGreen:		sColorTemp = "Green";		break;
				case colorBlueGreen:	sColorTemp = "BlueGreen";	break;
				case colorBlue:			sColorTemp = "Blue";		break;
				case colorDarkBlue:		sColorTemp = "DarkBlue";	break;
				case colorViolet:		sColorTemp = "Violet";		break;

				case colorNone:
				default:				sColorTemp = "None";		break;
			}

			sprintf(sOutputString, "Color(%d) %s", nDeviceIndex + 1, sColorTemp);
		}
		else
		{
			sprintf(sOutputString, "Bad Color Mode (%d)", nDeviceIndex + 1);
		}
		break;

	case vexIQ_SensorGYRO:
		sprintf(sOutputString, "Gyro(%d) %d deg", nDeviceIndex + 1, getGyroDegrees(nDeviceIndex));
		break;

	case vexIQ_SensorSONAR:
			sprintf(sOutputString, "Dist(%d) %d mm", nDeviceIndex + 1, getDistanceValue(nDeviceIndex));
		break;

	case vexIQ_SensorBUMPER:
		sprintf(sOutputString, "Bumper(%d) %s", nDeviceIndex + 1, getBumperValue(nDeviceIndex) ? "Pressed" : "Released");
		break;
	}

	int nLineNumber = lineNumber;
	displayTextLine(nLineNumber, sOutputString);
}

/* 
------------------- display variables ------------------------
*/

// Special enum that allows "Select variable" drop down to be displayed
typedef enum _tSelectVariable {
	kSelectVariableNone = 0
} tSelectVariable;

// Function used in graphical only
void displayVariableValues(tIQLCDLine lineNumber = line1, const tSelectVariable value )
{
}

// We use a macro so the variable can be accessed by name and value
#define displayVariableValues( line, name ) _displayVariableValues( line, #name, name )

// Function that actually displays the value
void _displayVariableValues(tIQLCDLine lineNumber = line1, char *name, float floatValue = 0 )
{
	const int kMaxVariableNameLength = 10;
	char tmpName[kMaxVariableNameLength + 1];
	char sOutputString[kMaxVariableNameLength + 16];

	// name has pre and post " as in "value"
	// we need to strip those off
	if( strlen(name) > 2 ) {
		memset(tmpName, 0, sizeof(tmpName));
		strncpy(tmpName, &(name[1]), kMaxVariableNameLength);
		if( strlen(name)-2 < kMaxVariableNameLength )
			tmpName[strlen(tmpName)-1] = '\0';
		sprintf(sOutputString, "%s = %.2f", &(tmpName[0]), floatValue );
	}
	else
		strcpy(sOutputString, "No variable");

	int nLineNumber = lineNumber;
	displayTextLine(nLineNumber, sOutputString);
}

// Wrapper for displayTextLine to give menu for line number
void displayText(tIQLCDLine lineNumber = line1, const string sString )
{
		int nLineNumber = lineNumber;
		displayTextLine( nLineNumber, "%s", sString);
}

/*
------------------- Low Level Commands ------------------------
*/

void lowLevelMoveDistance(const float quantity, short nLeftSpeed, short nRightSpeed, const tMovementUnits nUnitType)
{
	long nConvertedUnitsLeft = 0;
	long nConvertedUnitsRight = 0;

	if(nUnitType == degrees)
	{
		nConvertedUnitsLeft = quantity;
		nConvertedUnitsRight = quantity;
	}
	else if(nUnitType == rotations)
	{
		nConvertedUnitsLeft = quantity * 360.0;
		nConvertedUnitsRight = quantity * 360.0;
	}
	else
	{
		return;
	}

	updateMotorDriveTrain();

	if(nLeftSpeed < 0)
	{
		nConvertedUnitsLeft *= -1;
		//nLeftSpeed *= -1;
	}

	if(nRightSpeed < 0)
	{
		nConvertedUnitsRight *= -1;
		//nRightSpeed *= -1;
	}

	if(internalLeftMotors[0] != noMotor)	moveMotorTarget(internalLeftMotors[0], nConvertedUnitsLeft, nLeftSpeed);
	if(internalLeftMotors[1] != noMotor)	moveMotorTarget(internalLeftMotors[1], nConvertedUnitsLeft, nLeftSpeed);
	if(internalLeftMotors[2] != noMotor)	moveMotorTarget(internalLeftMotors[2], nConvertedUnitsLeft, nLeftSpeed);
	if(internalLeftMotors[3] != noMotor)	moveMotorTarget(internalLeftMotors[3], nConvertedUnitsLeft, nLeftSpeed);

	if(internalRightMotors[0] != noMotor)	moveMotorTarget(internalRightMotors[0], nConvertedUnitsRight, nRightSpeed);
	if(internalRightMotors[1] != noMotor)	moveMotorTarget(internalRightMotors[1], nConvertedUnitsRight, nRightSpeed);
	if(internalRightMotors[2] != noMotor)	moveMotorTarget(internalRightMotors[2], nConvertedUnitsRight, nRightSpeed);
	if(internalRightMotors[3] != noMotor)	moveMotorTarget(internalRightMotors[3], nConvertedUnitsRight, nRightSpeed);

	sleep(100);

	while(getMotorDriveTrainMoving())
		sleep(5);

	sleep(25);
}

void setMotorSpeeds(short nRightSideSpeed, short nLeftSideSpeed)
{
	if(internalRightMotors[0] != noMotor)	setMotorSpeed(internalRightMotors[0], nRightSideSpeed);
	if(internalRightMotors[1] != noMotor)	setMotorSpeed(internalRightMotors[1], nRightSideSpeed);
	if(internalRightMotors[2] != noMotor)	setMotorSpeed(internalRightMotors[2], nRightSideSpeed);
	if(internalRightMotors[3] != noMotor)	setMotorSpeed(internalRightMotors[3], nRightSideSpeed);

	if(internalLeftMotors[0] != noMotor)	setMotorSpeed(internalLeftMotors[0], nLeftSideSpeed);
	if(internalLeftMotors[1] != noMotor)	setMotorSpeed(internalLeftMotors[1], nLeftSideSpeed);
	if(internalLeftMotors[2] != noMotor)	setMotorSpeed(internalLeftMotors[2], nLeftSideSpeed);
	if(internalLeftMotors[3] != noMotor)	setMotorSpeed(internalLeftMotors[3], nLeftSideSpeed);
}

void lowLevelMoveTiming(float quantity, const short nLeftSpeed, const short nRightSpeed, const tMovementUnits nUnitType)
{
	updateMotorDriveTrain();

	setMotorSpeeds(nRightSpeed, nLeftSpeed);

	if(nUnitType == milliseconds)
		sleep(quantity);
	else if(nUnitType == seconds)
		sleep(quantity * 1000);
	else if(nUnitType == minutes)
		sleep(quantity * 1000 * 60);
	else
		sleep(5);

	setMotorSpeeds(0, 0);

	sleep(25);
}

/*
------------------- Wait Commands -------------------------
*/
void wait(const float quantity = 1.0, const tMovementUnits unitType = seconds)
{
	if(unitType == seconds)
		sleep(quantity * 1000.0);
	else if(unitType == minutes)
		sleep(quantity * 1000.0 * 60.0);
	else if(unitType == milliseconds)
		sleep(quantity);
}



/*
------------------- Discrete Movement -------------------------
*/

void forward(const float quantity = 1.0, const tMovementUnits unitType = rotations, const short speed = 50)
{
	short adjustedSpeed = abs(speed);
	float adjustedQuantity = abs(quantity);

	switch(unitType)
	{
	case rotations:
	case degrees:
		lowLevelMoveDistance(adjustedQuantity, adjustedSpeed, adjustedSpeed, unitType);
		break;

	case milliseconds:
	case seconds:
	case minutes:
		lowLevelMoveTiming(adjustedQuantity, adjustedSpeed, adjustedSpeed, unitType);
		break;
	}
}

void backward(const float quantity = 1.0, const tMovementUnits unitType = rotations, const short speed = 50)
{
	short adjustedSpeed = abs(speed) * -1;
	float adjustedQuantity = abs(quantity);

	switch(unitType)
	{
	case rotations:
	case degrees:
		lowLevelMoveDistance(adjustedQuantity, adjustedSpeed, adjustedSpeed, unitType);
		break;

	case milliseconds:
	case seconds:
	case minutes:
		lowLevelMoveTiming(adjustedQuantity, adjustedSpeed, adjustedSpeed, unitType);
		break;
	}
}

void turnLeft(const float quantity = 1.0, const tMovementUnits unitType = rotations, const short speed = 50)
{
	short adjustedSpeed = abs(speed);
	float adjustedQuantity = abs(quantity);

	switch(unitType)
	{
	case rotations:
	case degrees:
		lowLevelMoveDistance(adjustedQuantity, -adjustedSpeed, adjustedSpeed, unitType);
		break;

	case milliseconds:
	case seconds:
	case minutes:
		lowLevelMoveTiming(adjustedQuantity, -adjustedSpeed, adjustedSpeed, unitType);
		break;
	}
}

void turnRight(const float quantity = 1.0, const tMovementUnits unitType = rotations, const short speed = 50)
{
	short adjustedSpeed = abs(speed);
	float adjustedQuantity = abs(quantity);

	switch(unitType)
	{
	case rotations:
	case degrees:
		lowLevelMoveDistance(adjustedQuantity, adjustedSpeed, -adjustedSpeed, unitType);
		break;

	case milliseconds:
	case seconds:
	case minutes:
		lowLevelMoveTiming(adjustedQuantity, adjustedSpeed, -adjustedSpeed, unitType);
		break;
	}
}

void moveMotor(const tMotor motorPort = motor10, const float quantity = 1.0, const tMovementUnits unitType = rotations, const short speed = 50)
{
	short adjustedSpeed = abs(speed);
	float adjustedQuantity = abs(quantity);

	switch(unitType)
	{
	//Rotations - moves in reverse if speed and/or quantity are set negative
	case rotations:
		if(speed < 0 || quantity < 0)
			moveMotorTarget(motorPort, -(adjustedQuantity * 360.0), -adjustedSpeed);
		else
			moveMotorTarget(motorPort, (adjustedQuantity * 360.0), adjustedSpeed);
		waitUntilMotorStop(motorPort);
		break;

	//Degrees - moves in reverse if speed and/or quantity are set negative
	case degrees:
		if(speed < 0 || quantity < 0)
			moveMotorTarget(motorPort, -adjustedQuantity, -adjustedSpeed);
		else
			moveMotorTarget(motorPort, adjustedQuantity, adjustedSpeed);
		waitUntilMotorStop(motorPort);
		break;

	//Milliseconds
	case milliseconds:
		setMotorSpeed(motorPort, speed);
		sleep(adjustedQuantity);
		setMotorSpeed(motorPort, 0);
		break;

	//Seconds
	case seconds:
		setMotorSpeed(motorPort, speed);
		sleep(adjustedQuantity * 1000.0);
		setMotorSpeed(motorPort, 0);
		break;

	//Minutes
	case minutes:
		setMotorSpeed(motorPort, speed);
		sleep(adjustedQuantity * 1000.0 * 60.0);
		setMotorSpeed(motorPort, 0);
		break;
	}

	sleep(25);
}

/*
------------------- Constant Movements -------------------------
*/

void setMotor(const tMotor motorPort = motor1, const short speed = 50)
{
	setMotorSpeed(motorPort, speed);
}

void stopMotor(const tMotor motorPort = motor1)
{
	setMotorSpeed(motorPort, 0);
}

void stopAllMotors()
{
	TVexIQDeviceTypes nDeviceType;
	TDeviceStatus nDeviceStatus;
	short nDeviceVersion;

	for (short nPortIndex = 0; nPortIndex < 12; ++nPortIndex)
	{
		getVexIqDeviceInfo(nPortIndex, nDeviceType, nDeviceStatus, nDeviceVersion);

		if (nDeviceType != vexIQ_SensorMOTOR)
			continue;

		setMotorSpeed(nPortIndex, 0);
	}
}

void setMultipleMotors(const short speed = 50, const tMotor firstMotor = port1, const tMotor secondMotor = noMotor, const tMotor thirdMotor = noMotor, const tMotor fourthMotor = noMotor)
{
	if(firstMotor != noMotor) 		setMotorSpeed(firstMotor, speed);
	if(secondMotor != noMotor) 	setMotorSpeed(secondMotor, speed);
	if(thirdMotor != noMotor) 		setMotorSpeed(thirdMotor, speed);
	if(fourthMotor != noMotor) 	setMotorSpeed(fourthMotor, speed);
}

void stopMultipleMotors(const tMotor firstMotor = port1, const tMotor secondMotor = noMotor, const tMotor thirdMotor = noMotor, const tMotor fourthMotor = noMotor)
{
	if(firstMotor != noMotor) 		setMotorSpeed(firstMotor, 0);
	if(secondMotor != noMotor) 	setMotorSpeed(secondMotor, 0);
	if(thirdMotor != noMotor) 		setMotorSpeed(thirdMotor, 0);
	if(fourthMotor != noMotor) 	setMotorSpeed(fourthMotor, 0);
}

/*
------------------- Line Tracking Movements -------------------------
*/

void lineTrackLeft(const tSensors sensorName = port1, const short threshold = 50, const short speedPrimary = 50, const short speedSecondary = 0)
{
	if(getColorMode(sensorName) != colorTypeGrayscale_Reflected)
		setColorMode(sensorName, colorTypeGrayscale_Reflected);

	updateMotorDriveTrain();

	if(getColorGrayscale(sensorName) > threshold)
		setMotorSpeeds(speedSecondary, speedPrimary);
	else
		setMotorSpeeds(speedPrimary, speedSecondary);
}

void lineTrackRight(const tSensors sensorName = port1, const short threshold = 50, const short speedPrimary = 50, const short speedSecondary = 0)
{
	if(getColorMode(sensorName) != colorTypeGrayscale_Reflected)
		setColorMode(sensorName, colorTypeGrayscale_Reflected);

	updateMotorDriveTrain();

	if(getColorGrayscale(sensorName) < threshold)
		setMotorSpeeds(speedSecondary, speedPrimary);
	else
		setMotorSpeeds(speedPrimary, speedSecondary);
}

/*
------------------- Timer Commands -------------------------
*/

void resetTimer(TTimers currentTimer = T1)
{
	clearTimer(currentTimer);
}

float getTimer(TTimers currentTimer = T1, const tMovementUnits unitType = seconds)
{
	if(unitType == milliseconds)
		return (time1[currentTimer]);
	else if(unitType == seconds)
		return ((float)time1[currentTimer]/1000.0);
	else if(unitType == minutes)
		return (((float)time1[currentTimer] / 1000.0) / 60.0);

	return 0.0;
}

/*
------------------- Remote Control Movements -------------------------
*/

void tankControl(TJoystickAxis rightJoystick = JoyY2, TJoystickAxis leftJoystick = JoyY1, short threshold = 10)
{
	short nVirtualRightJoystick = 0;
	short nVirtualLeftJoystick = 0;
	getJoystickSettings(joystick);
	updateMotorDriveTrain();

	switch(rightJoystick)
	{
	case JoyX1:    nVirtualRightJoystick = (joystick.joy1_x1 * 100) / 127;     break;
	case JoyY1:    nVirtualRightJoystick = (joystick.joy1_y1 * 100) / 127;     break;
    case JoyX2:    nVirtualRightJoystick = (joystick.joy1_x2 * 100) / 127;     break;
    case JoyY2:    nVirtualRightJoystick = (joystick.joy1_y2 * 100) / 127;     break;
	default:       nVirtualRightJoystick = 0;
	}

	switch(leftJoystick)
	{
	case JoyX1:    nVirtualLeftJoystick = (joystick.joy1_x1 * 100) / 127;      break;
	case JoyY1:    nVirtualLeftJoystick = (joystick.joy1_y1 * 100) / 127;      break;
    case JoyX2:    nVirtualLeftJoystick = (joystick.joy1_x2 * 100) / 127;      break;
    case JoyY2:    nVirtualLeftJoystick = (joystick.joy1_y2 * 100) / 127;      break;
	default:	   nVirtualLeftJoystick = 0;
	}

	if(nGlobalJoyScaledValue != nMaxJoyScaleValue)
	{
		nVirtualRightJoystick = nVirtualRightJoystick * (nGlobalJoyScaledValue / 100.0);
		nVirtualLeftJoystick  = nVirtualLeftJoystick * (nGlobalJoyScaledValue / 100.0);
	}

	short nRightSpeed;
	short nLeftSpeed;
	
	if(abs(nVirtualRightJoystick) <= abs(threshold))
		nRightSpeed = 0;
	else
		nRightSpeed = nVirtualRightJoystick;

	if (abs(nVirtualLeftJoystick) <= abs(threshold))
		nLeftSpeed = 0;
	else
		nLeftSpeed = nVirtualLeftJoystick;

	setMotorSpeeds(nRightSpeed, nLeftSpeed);
}

void arcadeControl(TJoystickAxis verticalJoystick = JoyY2, TJoystickAxis horizontalJoystick = JoyX2, short threshold = 10)
{
	short nVirtualVerticalJoystick = 0;
	short nVirtualHorizontalJoystick = 0;
	short nRightSideSpeed = 0;
	short nLeftSideSpeed = 0;

	updateMotorDriveTrain();
	getJoystickSettings(joystick);

	switch(verticalJoystick)
	{
	case JoyX1:    nVirtualVerticalJoystick = (joystick.joy1_x1 * 100) / 127;     break;
	case JoyY1:    nVirtualVerticalJoystick = (joystick.joy1_y1 * 100) / 127;	    break;
  case JoyX2:    nVirtualVerticalJoystick = (joystick.joy1_x2 * 100) / 127;     break;
  case JoyY2:    nVirtualVerticalJoystick = (joystick.joy1_y2 * 100) / 127;     break;
	default:       nVirtualVerticalJoystick = 0;
	}

	switch(horizontalJoystick)
	{
	case JoyX1:    nVirtualHorizontalJoystick = (joystick.joy1_x1 * 100) / 127;   break;
	case JoyY1:    nVirtualHorizontalJoystick = (joystick.joy1_y1 * 100) / 127;   break;
  case JoyX2:    nVirtualHorizontalJoystick = (joystick.joy1_x2 * 100) / 127;   break;
  case JoyY2:    nVirtualHorizontalJoystick = (joystick.joy1_y2 * 100) / 127;   break;
	default:       nVirtualHorizontalJoystick = 0;
	}

	if(abs(nVirtualVerticalJoystick) <= abs(threshold) && abs(nVirtualHorizontalJoystick) <= abs(threshold))
	{
		nRightSideSpeed = 0;
		nLeftSideSpeed  = 0;
	}
	else
	{
		nRightSideSpeed = ((nVirtualVerticalJoystick - nVirtualHorizontalJoystick)/2);
 		nLeftSideSpeed = ((nVirtualVerticalJoystick + nVirtualHorizontalJoystick)/2);

 		if(nGlobalJoyScaledValue != nMaxJoyScaleValue)
		{
			nRightSideSpeed = nRightSideSpeed * (nGlobalJoyScaledValue / 100.0);
			nLeftSideSpeed 	= nLeftSideSpeed * (nGlobalJoyScaledValue / 100.0);
		}
	}
	setMotorSpeeds(nRightSideSpeed, nLeftSideSpeed);
}

void armControl(tMotor armMotorPort = motor10, TJoystickButtons upButton = Btn5, TJoystickButtons downButton = Btn7, short armSpeed = 75)
{
	bool bVirtualUpButton = false;
	bool bVirtualDownButton = false;
	getJoystickSettings(joystick);

	switch (upButton)
	{
		case Btn1:     bVirtualUpButton = joy1Btn(1);     break;
		case Btn2:     bVirtualUpButton = joy1Btn(2);     break;
		case Btn3:     bVirtualUpButton = joy1Btn(3);     break;
		case Btn4:     bVirtualUpButton = joy1Btn(4);     break;
		case Btn5:     bVirtualUpButton = joy1Btn(5);     break;
		case Btn6:     bVirtualUpButton = joy1Btn(6);     break;
		case Btn7:     bVirtualUpButton = joy1Btn(7);     break;
		case Btn8:     bVirtualUpButton = joy1Btn(8);     break;
		case Btn9:     bVirtualUpButton = joy1Btn(9);     break;
		case Btn10:    bVirtualUpButton = joy1Btn(10);   break;

		case Pov0:	   if(joystick.joy1_TopHat == 0)	bVirtualUpButton = true;  	break;
		case Pov1:     if(joystick.joy1_TopHat == 1)	bVirtualUpButton = true;  	break;
		case Pov2:     if(joystick.joy1_TopHat == 2)	bVirtualUpButton = true;  	break;
		case Pov3:     if(joystick.joy1_TopHat == 3)	bVirtualUpButton = true;  	break;
		case Pov4:     if(joystick.joy1_TopHat == 4)	bVirtualUpButton = true;  	break;
		case Pov5:     if(joystick.joy1_TopHat == 5)	bVirtualUpButton = true;	  break;
		case Pov6:     if(joystick.joy1_TopHat == 6)	bVirtualUpButton = true;    break;
		case Pov7:     if(joystick.joy1_TopHat == 7)	bVirtualUpButton = true;    break;
		default:       bVirtualUpButton = false;                                  break;
	}

	switch (downButton)
	{
		case Btn1:     bVirtualDownButton = joy1Btn(1);     break;
		case Btn2:     bVirtualDownButton = joy1Btn(2);     break;
		case Btn3:     bVirtualDownButton = joy1Btn(3);     break;
		case Btn4:     bVirtualDownButton = joy1Btn(4);     break;
		case Btn5:     bVirtualDownButton = joy1Btn(5);     break;
		case Btn6:     bVirtualDownButton = joy1Btn(6);     break;
		case Btn7:     bVirtualDownButton = joy1Btn(7);     break;
		case Btn8:     bVirtualDownButton = joy1Btn(8);     break;
		case Btn9:     bVirtualDownButton = joy1Btn(9);     break;
		case Btn10:     bVirtualDownButton = joy1Btn(10);   break;

		case Pov0:		 if(joystick.joy1_TopHat == 0)	bVirtualDownButton = true;  break;
		case Pov1:     if(joystick.joy1_TopHat == 1)	bVirtualDownButton = true;  break;
		case Pov2:     if(joystick.joy1_TopHat == 2)	bVirtualDownButton = true;  break;
		case Pov3:     if(joystick.joy1_TopHat == 3)	bVirtualDownButton = true;  break;
		case Pov4:     if(joystick.joy1_TopHat == 4)	bVirtualDownButton = true;  break;
		case Pov5:     if(joystick.joy1_TopHat == 5)	bVirtualDownButton = true;	break;
		case Pov6:     if(joystick.joy1_TopHat == 6)	bVirtualDownButton = true;  break;
		case Pov7:     if(joystick.joy1_TopHat == 7)	bVirtualDownButton = true;  break;
		default:       bVirtualDownButton = false;                                break;
	}

	if (bVirtualUpButton)
	{
		setMotorSpeed(armMotorPort, armSpeed);
	}
	else if (bVirtualDownButton)
	{
		setMotorSpeed(armMotorPort, -armSpeed);
	}
	else
	{
		setMotorSpeed(armMotorPort, 0);
	}
}

/*
------------------- Datalog wrappers -------------------------
*/

// These globals are used by a task included in the NatLang_Datalog.c
// file
static long								  _datalogUpdateInterval = 50;
static long 								_datalogUpdatePeriod   = 0;

void
datalogRate( const float quantity = 50.0, const tMovementUnits unitType = milliseconds)
{
	long	tmpPeriod;
	
	if(unitType == seconds)
		tmpPeriod = quantity * 1000.0;
	else if(unitType == minutes)
		tmpPeriod = quantity * 1000.0 * 60.0;
	else if(unitType == milliseconds)
		tmpPeriod = quantity;
		
	if( tmpPeriod >= 10 )
		_datalogUpdateInterval = tmpPeriod;
	else
		_datalogUpdateInterval = 10;
}

void 
datalogStart(const float quantity = 5.0, const tMovementUnits unitType = seconds)
{
	if(unitType == seconds)
		_datalogUpdatePeriod = quantity * 1000.0;
	else if(unitType == minutes)
		_datalogUpdatePeriod = quantity * 1000.0 * 60.0;
	else if(unitType == milliseconds)
		_datalogUpdatePeriod = quantity;
}

void
datalogStop()
{
	_datalogUpdatePeriod = 0;
}
