#include <AccelStepper.h>
const int x_step_pin = 2;
const int y_step_pin = 3;
const int z_step_pin = 4;

const int x_dir_pin = 5;
const int y_dir_pin = 6;
const int z_dir_pin = 7;

const int enable = 8;

// Notes to play the cello part of Canon in D (chosen because notes are equal length and form a cycle)
// Frequencies in Hz of D A B F# G D G A
const int bass[] = {587, 440, 494, 370, 392, 294, 392, 440};
// F# E D C# B A B C#
const int tenor[] = {740, 659, 587, 554, 494, 440, 494, 554};

AccelStepper x_stepper = AccelStepper(AccelStepper::DRIVER, x_step_pin, x_dir_pin);
AccelStepper y_stepper = AccelStepper(AccelStepper::DRIVER, y_step_pin, y_dir_pin);
AccelStepper z_stepper = AccelStepper(AccelStepper::DRIVER, z_step_pin, z_dir_pin);

void setup() {
  Serial.begin(9600);
  x_stepper.setMaxSpeed(1000);
  x_stepper.setSpeed(800);
}

void loop() {
  // Check to see if we have received any commands
  
  if (Serial.available() > 0){
    String command = Serial.readString();
    command.trim();
    Serial.print("Echo: '");
    Serial.print(command);
    Serial.println("'");

    int command_int = command.toInt();
    if (command_int >= 0){
      x_stepper.setSpeed(command.toInt());
    } else {
      
    }
  }
  x_stepper.setSpeed(bass[int(millis()/1500)%8]);
  x_stepper.runSpeed();
}
