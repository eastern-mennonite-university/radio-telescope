
const int x_step = 2;
const int y_step = 3;
const int z_step = 4;

const int x_dir = 5;
const int y_dir = 6;
const int z_dir = 7;

const int enable = 8;

// Experimentally, this has to be greater than 500 when on full step
const int step_microseconds = 500;
const int full_steps_per_revolution = floor(28.65 * 200);
// 1=full step, 2=half step, 4=quarter, etc.
const int pulses_per_step = 1;

void setup() {
  pinMode(x_step, OUTPUT);
  pinMode(y_step, OUTPUT);
  pinMode(z_step, OUTPUT);
  pinMode(x_dir, OUTPUT);
  pinMode(y_dir, OUTPUT);
  pinMode(z_dir, OUTPUT);
}

void loop() {
  digitalWrite(x_dir, HIGH);
  for(int x=0; x<full_steps_per_revolution*pulses_per_step; x++){
    digitalWrite(x_step, HIGH);
    delayMicroseconds(step_microseconds);
    digitalWrite(x_step, LOW);
    delayMicroseconds(step_microseconds);
  }
  delay(1000);

  digitalWrite(x_dir, LOW);
  for(int x=0; x<full_steps_per_revolution*pulses_per_step; x++){
    digitalWrite(x_step, HIGH);
    delayMicroseconds(step_microseconds);
    digitalWrite(x_step, LOW);
    delayMicroseconds(step_microseconds);
  }

  delay(1000);
  
}
