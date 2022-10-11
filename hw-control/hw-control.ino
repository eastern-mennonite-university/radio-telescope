#include <AccelStepper.h>
const int x_step_pin = 2;
const int y_step_pin = 3;
const int z_step_pin = 4;

const int x_dir_pin = 5;
const int y_dir_pin = 6;
const int z_dir_pin = 7;

const int enable = 8;

int x_step = LOW;
int y_step = LOW;
int z_step = LOW;

int x_dir = 0;
int y_dir = LOW;
int z_dir = LOW;

// Experimentally, this has to be greater than 500 when on full step
const int step_microseconds = 500;
const int full_steps_per_revolution = floor(28.65 * 200);
// 1=full step, 2=half step, 4=quarter, etc.
const int pulses_per_step = 1;

int x_pos = 0;
int x_sp = 0;
int x_t = micros();

AccelStepper x_stepper = AccelStepper(AccelStepper::DRIVER, x_step_pin, x_dir_pin);

void setup() {
  pinMode(x_step_pin, OUTPUT);
  pinMode(y_step_pin, OUTPUT);
  pinMode(z_step_pin, OUTPUT);
  pinMode(x_dir_pin, OUTPUT);
  pinMode(y_dir_pin, OUTPUT);
  pinMode(z_dir_pin, OUTPUT);

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
    
    x_stepper.setSpeed(command.toInt());
  }
  x_stepper.runSpeed();
  
}
