
const int x_step = 2;
const int y_step = 3;
const int z_step = 4;

const int x_dir = 5;
const int y_dir = 6;
const int z_dir = 7;

const int enable = 8;

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
  for(int x=0; x<200; x++){
    digitalWrite(x_step, HIGH);
    delay(1);
    digitalWrite(x_step, LOW);
    delay(1);
  }
  delay(1000);

  digitalWrite(x_dir, LOW);
  for(int x=0; x<200; x++){
    digitalWrite(x_step, HIGH);
    delay(1);
    digitalWrite(x_step, LOW);
    delay(1);
  }

  delay(1000);
  
}
