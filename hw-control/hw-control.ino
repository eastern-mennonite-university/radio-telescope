#include <AccelStepper.h>
#include <string.h>

enum state {
  POWER_ON,
  CALIBRATE_CW,
  CALIBRATE_CCW,
  CALIBRATE_UP,
  CALIBRATE_DOWN,
  MOVE,
  WAIT
};

state current_state = POWER_ON;
const int X_STEP_PIN = 2;
const int Y_STEP_PIN = 3;

const int X_DIR_PIN = 5;
const int Y_DIR_PIN = 6;

const int X_LIMIT_PIN = 9;
const int Y_LIMIT_PIN = 10;

const int enable = 8;

// Notes to play the cello part of Canon in D (chosen because notes are equal length and form a cycle)
// Frequencies in Hz of D A B F# G D G A
const int bass[] = {587, 440, 494, 370, 392, 294, 392, 440};
// F# E D C# B A B C#
const int tenor[] = {740, 659, 587, 554, 494, 440, 494, 554};

AccelStepper x_stepper = AccelStepper(AccelStepper::DRIVER, X_STEP_PIN, X_DIR_PIN);
AccelStepper y_stepper = AccelStepper(AccelStepper::DRIVER, Y_STEP_PIN, Y_DIR_PIN);

int music = 0;

// Max and min altitude and azimuth are determined by the position of the box and limit switches
// Azimuth: 0deg=North, 90deg=East, etc.
int azimuth_steps = 0;
const float MAX_AZIMUTH_DEGREES = 175.0; //Change me after installation
const float MIN_AZIMUTH_DEGREES = -175.0; //Change me after installation
int max_azimuth_steps = 1000;
int min_azimuth_steps = -1000;
float azimuth_steps_per_degree = 1;

// Altitude: 0deg=Horizon, 90deg=Vertical
int altitude_steps = 0;
const float MAX_ALTITUDE_DEGREES = 90.0; // Change me after installation
const float MIN_ALTITUDE_DEGREES = 0.0; // Change me after installation
int max_altitude_steps = 1000;
int min_altitude_steps = -1000;
float altitude_steps_per_degree = 1;

char* command_args[10];
char* command_arg;

bool moving = false;

int target_altitude = 0;
int target_azimuth = 0;

void setup() {
  Serial.begin(9600);
  x_stepper.setMaxSpeed(1000);
  x_stepper.setAcceleration(600);
  x_stepper.setSpeed(0);
  y_stepper.setMaxSpeed(1000);
  y_stepper.setAcceleration(600);
  y_stepper.setSpeed(0);

  pinMode(X_LIMIT_PIN, INPUT_PULLUP);
  pinMode(Y_LIMIT_PIN, INPUT_PULLUP);

//  calibrate();
}

void loop() {
  // Regardless of state, check to see if we have received any commands

  int numBytes = Serial.available();
  char buff[512];
  if (readLine(Serial.read(), buff, 511) > 0){
    Serial.print("Echo: '");
    Serial.print(buff);
    Serial.println("'");

    // TODO: I'm pretty sure this is bad, unsafe code. Not sure how to fix it -Caleb
    command_arg = strtok(buff, " ");
    command_args[0] = command_arg;
    int i = 0;
    while (command_arg != NULL && i<10){
      command_args[i] = command_arg;
      command_arg = strtok(NULL, " ");
      i++;
    }

    if (strcmp(command_args[0], "set")==0){
      float input_altitude = atof(command_args[1]);
      float input_azimuth = atof(command_args[2]);
      if (input_altitude > MAX_ALTITUDE_DEGREES || input_altitude < MIN_ALTITUDE_DEGREES || input_azimuth > MAX_AZIMUTH_DEGREES || input_azimuth < MIN_AZIMUTH_DEGREES){
        Serial.print("set error: angle out of range");
      } else {
        target_altitude = int((input_altitude-MAX_ALTITUDE_DEGREES)*altitude_steps_per_degree + min_altitude_steps);
        target_azimuth = int((input_azimuth-MAX_AZIMUTH_DEGREES)*azimuth_steps_per_degree + min_azimuth_steps);
        current_state = MOVE;
        Serial.println("set OK");
      }
    } else if (strcmp(command_args[0], "calibrate")==0){
      Serial.println("calibrate OK");
      current_state = CALIBRATE_CW;
    } else if (strcmp(command_args[0], "pos")==0){
      Serial.print("pos (");
      Serial.print((altitude_steps-min_altitude_steps)/(altitude_steps_per_degree) + MIN_ALTITUDE_DEGREES);
      Serial.print(", ");
      Serial.print((azimuth_steps-min_azimuth_steps)/(azimuth_steps_per_degree) + MIN_AZIMUTH_DEGREES);
      Serial.println(")");
    }
  }

  // Regardless of whether a command was received, do our action
  doAction();
}

void doAction() {
  switch(current_state){
    case POWER_ON:
      current_state = CALIBRATE_CW;
      break;
    case CALIBRATE_CW:
      if (digitalRead(X_LIMIT_PIN)==0){
        current_state = CALIBRATE_CCW;
        max_azimuth_steps = azimuth_steps;
      } else {
        x_stepper.setSpeed(500);
        if (x_stepper.runSpeed()){
          azimuth_steps++;
        }
      }
      break;
    case CALIBRATE_CCW:
      if (digitalRead(X_LIMIT_PIN)==0 && max_azimuth_steps-azimuth_steps >= 500){
        current_state = CALIBRATE_UP;
        min_azimuth_steps = azimuth_steps;
        x_stepper.setSpeed(0);
      } else {
        x_stepper.setSpeed(-500);
        if (x_stepper.runSpeed()){
          azimuth_steps++;
        }
      }
      break;
    case CALIBRATE_UP:
      if (digitalRead(Y_LIMIT_PIN)==0){
        current_state = CALIBRATE_DOWN;
        max_altitude_steps = altitude_steps;
      } else {
        y_stepper.setSpeed(500);
        if (y_stepper.runSpeed()){
          altitude_steps++;
        }
      }
      break;
    case CALIBRATE_DOWN:
      if (digitalRead(Y_LIMIT_PIN)==0 && max_altitude_steps-altitude_steps >= 500){
        max_altitude_steps = altitude_steps;
        azimuth_steps_per_degree = (max_azimuth_steps - min_azimuth_steps) / (MAX_AZIMUTH_DEGREES - MIN_AZIMUTH_DEGREES);
        altitude_steps_per_degree = (max_altitude_steps - min_altitude_steps) / (MAX_ALTITUDE_DEGREES - MIN_ALTITUDE_DEGREES);
        target_altitude = 0;
        target_azimuth = 0;
        current_state = MOVE;
      } else {
        y_stepper.setSpeed(500);
        if (y_stepper.runSpeed()){
          altitude_steps++;
        }
      }
      break;
    case MOVE:
      x_stepper.moveTo(target_azimuth);
      y_stepper.moveTo(target_altitude);
      x_stepper.run();
      y_stepper.run();
      azimuth_steps = int(x_stepper.currentPosition());
      altitude_steps = int(y_stepper.currentPosition());
      if (x_stepper.distanceToGo() == 0 && y_stepper.distanceToGo() == 0){
        current_state = WAIT;
      }
      
      break;
    case WAIT:
      delay(100);
      break;
      
  }
}

int readLine(int readch, char *buffer, int len) {
  // https://hackingmajenkoblog.wordpress.com/2016/02/01/reading-serial-on-the-arduino/
    static int pos = 0;
    int rpos;

    if (readch > 0) {
        switch (readch) {
            case '\r': // Ignore CR
                break;
            case '\n': // Return on new-line
                rpos = pos;
                pos = 0;  // Reset position index ready for next time
                return rpos;
            default:
                if (pos < len-1) {
                    buffer[pos++] = readch;
                    buffer[pos] = 0;
                }
        }
    }
    return 0;
}
