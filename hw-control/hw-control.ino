#include <AccelStepper.h>
#include <string.h>

const int x_step_pin = 2;
const int y_step_pin = 3;

const int x_dir_pin = 5;
const int y_dir_pin = 6;

const int enable = 8;

// Notes to play the cello part of Canon in D (chosen because notes are equal length and form a cycle)
// Frequencies in Hz of D A B F# G D G A
const int bass[] = {587, 440, 494, 370, 392, 294, 392, 440};
// F# E D C# B A B C#
const int tenor[] = {740, 659, 587, 554, 494, 440, 494, 554};

AccelStepper x_stepper = AccelStepper(AccelStepper::DRIVER, x_step_pin, x_dir_pin);
AccelStepper y_stepper = AccelStepper(AccelStepper::DRIVER, y_step_pin, y_dir_pin);

int music = 0;

// Azimuth: 0deg=North, 90deg=East, etc.
float azimuth = 0;
// Altitude: 0deg=Horizon, 90deg=Vertical
float altitude = 0;

char* command_args[10];
char* command_arg;

bool moving = false;

void setup() {
  Serial.begin(9600);
  x_stepper.setMaxSpeed(1000);
  x_stepper.setAcceleration(600);
  x_stepper.setSpeed(0);
  y_stepper.setMaxSpeed(1000);
  y_stepper.setAcceleration(600);
  y_stepper.setSpeed(0);
}

void loop() {
  // Check to see if we have received any commands

  int numBytes = Serial.available();
  char buff[64];
  if (readLine(Serial.read(), buff, 63) > 0){
    Serial.print("Echo: '");
    Serial.print(buff);
    Serial.println("'");

    // TODO: I'm pretty sure this is bad, unsafe code. Not sure how to fix it -Caleb
    command_arg = strtok(buff, " ");
    command_args[0] = command_arg;
    int i = 0;
    while (command_arg != NULL && i<10){
      command_args[i] = command_arg;
//      Serial.println(command_arg);
      command_arg = strtok(NULL, " ");
      i++;
    }

    if (strcmp(command_args[0], "music")==0){
      music = 1;
    } else if (strcmp(command_args[0], "set")==0){
      float altitude = atof(command_args[1]);
      float azimuth = atof(command_args[2]);
      x_stepper.moveTo(int(altitude));
      y_stepper.moveTo(int(azimuth));
      moving = true;
      Serial.println("set OK");
    } else {
      int command_int = atoi(command_args[0]);
      x_stepper.setSpeed(command_int);
      y_stepper.setSpeed(int(command_int*.667));
      music = 0;
    }
  }

  doAction();
}

void doAction() {
  if(music){
    x_stepper.setSpeed(bass[int(millis()/1500)%8]);
    y_stepper.setSpeed(tenor[int(millis()/1500)%8]);
  }
  if (moving){
    if (x_stepper.distanceToGo()==0 && y_stepper.distanceToGo()==0){
      moving = false;
      Serial.println("set DONE");
    }
  }
  x_stepper.run();
  y_stepper.run();
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
