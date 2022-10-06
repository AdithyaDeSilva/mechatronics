// Include the Arduino Stepper Library
#include <Stepper.h>

// Number of steps per output rotation
const int stepsPerRevolution = 100;

Stepper stepperXAxis(stepsPerRevolution,4,5,6,7);
Stepper stepperYAxis(stepsPerRevolution,8,9,10,11);

int nextPlace[2] = {0, 0};
int currentPlace[2] = {0, 0};

// int positions[3][3][2] = {
// 	{{1,1},{1,2},{1,3}},
// 	{{2,1},{2,2},{2,3}},
// 	{{3,1},{3,2},{3,3}}
// };



//Takes the destination box number and change the nextPlace array 
void boxNumber(int number){
	if (number>9 or number<= 0)
	{
		Serial.println("Invalid number please Enter between 1-9");
		return;
	}else {
    Serial.println(number);
		currentPlace[0] = nextPlace[0];
		currentPlace[1] = nextPlace[1];

		switch (number)
		{
		case 1:
			nextPlace[0] = 1;
			nextPlace[1] = 1;
			break;
		case 2:
			nextPlace[0] = 2;
			nextPlace[1] = 1;
			break;
		case 3:
			nextPlace[0] = 3;
			nextPlace[1] = 1;
			break;
		case 4:
			nextPlace[0] = 1;
			nextPlace[1] = 2;
			break;
		case 5:
			nextPlace[0] = 2;
			nextPlace[1] = 2;
			break;
		case 6:
			nextPlace[0] = 3;
			nextPlace[1] = 2;
			break;
		case 7:
			nextPlace[0] = 1;
			nextPlace[1] = 3;
			break;
		case 8:
			nextPlace[0] = 2;
			nextPlace[1] = 3;
			break;
		case 9:
			nextPlace[0] = 3;
			nextPlace[1] = 3;
			break;
		
		default:
			nextPlace[0] = 1;
			nextPlace[1] = 1;
			break;
		}
	}	
}


//This moves X axis stepper
// int xAxisMove(int nextPlaceX){
// 	int xAxisBlocks = nextPlaceX - currentPlace[0];
// 	if (nextPlaceX < currentPlace[0])
// 	{
// 		int distance = currentPlace[0] - nextPlaceX ;
// 		stepperXAxis.step(-stepsPerRevolution * distance );
// 	}else {
// 		int distance = nextPlaceX - currentPlace[0];
// 		stepperXAxis.step( stepsPerRevolution * distance );
// 	}

// }

// //This moves Y axis stepper
// int yAxisMove(int nextPlaceY){
// 	int yAxisBlocks = nextPlaceY - currentPlace[1]; 
// 	if (nextPlaceY >= currentPlace[1])
// 	{
// 		return yAxisBlocks;
// 	}else {
// 		return -yAxisBlocks;
// 	}
// }

// Calculate the distance 
int moveStepper(int nextPlace, int currentPosition) {
	return nextPlace - currentPosition;
}


void setup () {
	Serial.begin(9600);
	stepperXAxis.setSpeed(500);
	stepperYAxis.setSpeed(500);
}

void loop(){
	if (Serial.available()){
		Serial.print("Input Box Number:");
		String reading = Serial.readStringUntil("\n");
    int s=reading.toInt();
		
		Serial.println("");
		boxNumber(s);
		// xAxisMove(nextPlace[0]);
		// yAxisMove(nextPlace[1]);
		int xDistance = moveStepper(nextPlace[0], currentPlace[0]);
		int yDistance = moveStepper(nextPlace[1], currentPlace[1]);
    Serial.println(currentPlace[0]);
    Serial.println(currentPlace[1]);
		stepperXAxis.step(xDistance * 2000);
		stepperYAxis.step(yDistance * 2000);
	}
}














// // Number of steps per output rotation
// const int stepsPerRevolution = 200;

// // Create Instance of Stepper library
// Stepper myStepperX(stepsPerRevolution, 8, 9, 10, 11);
// Stepper myStepperY(stepsPerRevolution, 4, 5, 6, 7);

// void setup()
// {
// 	// set the speed at 60 rpm:
// 	myStepperX.setSpeed(100);
// 	myStepperY.setSpeed(100);
// 	// initialize the serial port:
// 	Serial.begin(9600);
// }

// void loop()
// {
// 	// step one revolution in one direction:
// 	Serial.println("clockwise");
// 	myStepperX.step(stepsPerRevolution);
// 	myStepperY.step(stepsPerRevolution);
// 	delay(500);

// 	// step one revolution in the other direction:
// 	Serial.println("counterclockwise");
// 	myStepperX.step(-stepsPerRevolution);
// 	myStepperY.step(-stepsPerRevolution);
// 	delay(500);
// }
