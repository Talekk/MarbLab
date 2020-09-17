/*
   September 17, 2020
   Labyrinth Control Program
   Gareth Koch

   This program allows for one joystick to control the attitude
   of the marble labyrinth via a pair of servos mounted with
   perpendicular axes

   The neutral position and maximum deviation from it can
   be adjusted in the "Servo parameters" section below
*/

#include <Servo.h>

// Define servo pins
#define servoX 4
#define servoY 5

// Define joystick pins
#define readX A0
#define readY A1
#define readZ A2

// Create servos
Servo axisX;
Servo axisY;

// Servo parameters
int neutralX = 90;
int neutralY = 90;
int posX;
int posY;
int posZ;
int maxDevX = neutralX + 14;
int minDevX = neutralX - 14;
int maxDevY = neutralY + 14;
int minDevY = neutralY - 14;

// Joystick parameters
int neutralJ = 512;
int joystickX = neutralJ;
int joystickY = neutralJ;
int joystickZ = 0;


void setup() {
  Serial.begin(9600);
  // Attach servos to their respective pins
  axisX.attach(servoX);
  axisY.attach(servoY);
  Serial.println("Servos attached");

  // Set servos to neutral position
  posX = neutralX;
  posY = neutralY;
  axisX.write(posX);
  axisY.write(posY);
  Serial.println("Positions neutral");
}

void loop() {
  // Read joystick poisition information
  joystickX = analogRead(readX);
  joystickY = analogRead(readY);
  joystickZ = analogRead(readZ);

  // When joystick is pushed down, reset axes to neutral position
  if (joystickZ < 512) {
    reset();
  }

  // Change servo poition based on joystick deflection
  posX = servoControl(joystickX, posX, maxDevX, minDevX);
  posY = servoControl(joystickY, posY, maxDevY, minDevY);
  axisX.write(posX);
  axisY.write(posY);

  // Prints above values to serial monitor to aid in troubleshooting
  debug();
}

// General function to translate joystick deflection into change in servo angle
int servoControl (int dJoystick, int pos, int maxDev, int minDev) {
  if (dJoystick > 544 && pos < maxDev) {
    pos++;
  } else if (dJoystick < 480 && pos > minDev) {
    pos--;
  }
  return pos;
}

// Sets both axes to their neutral position
void reset() {
  if (posX > neutralX) {
    posX --;
    axisX.write(posX);
    delay(10);
  } else if (posX < neutralX) {
    posX ++;
    axisX.write(posX);
    delay(10);
  }

  if (posY > neutralY) {
    posY --;
    axisY.write(posY);
    delay(10);
  } else if (posY < neutralY) {
    posY ++;
    axisY.write(posY);
    delay(10);
  }
}

// Prints the read/write values to serial monitor
void debug() {
  Serial.print("| X: ");
  Serial.print(joystickX);
  Serial.print("| Y: ");
  Serial.print(joystickY);
  Serial.print("| Z: ");
  Serial.print(joystickZ);
  Serial.print(" | Axis X: ");
  Serial.print(posX);
  Serial.print(" | Axis Y: ");
  Serial.print(posY);
  Serial.println(" | ");
}
