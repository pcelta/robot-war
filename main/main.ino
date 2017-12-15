const int TRIGGER = 4; //12
const int ECHO = 7; //13
const int MAXIMUM_VALUE = 255;
const int MOTOR1_FORWARD = 13;
const int MOTOR1_BACKWARD = 12;
const int MOTOR1_VELOCITY = 11;
const int MOTOR2_FORWARD = 8;
const int MOTOR2_BACKWARD = 7;
const int MOTOR2_VELOCITY = 6;
const int RIGHT_SENSOR = A2;
const int MIDDLE_SENSOR = A1;
const int LEFT_SENSOR = A0;
const String STATE_AVOID_GOING_OUTSIDE = "stay_inside";
const String STATE_ENEMY_FIND = "find";
const String STATE_ENEMY_ATTACK = "attack";
String current_state = STATE_AVOID_GOING_OUTSIDE;

int current_right_sensor = 0;
int previous_right_sensor = 0;

int current_middle_sensor = 0;
int previous_middle_sensor = 0;

int current_left_sensor = 0;
int previous_left_sensor = 0;

const double SPEED_OF_SOUND = 0.034;

void setup() {
  Serial.begin(9600);
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);

  pinMode(MOTOR1_FORWARD, OUTPUT);
  pinMode(MOTOR1_BACKWARD, OUTPUT);
  pinMode(MOTOR1_VELOCITY, OUTPUT);
  pinMode(MOTOR2_FORWARD, OUTPUT);
  pinMode(MOTOR2_BACKWARD, OUTPUT);
  pinMode(MOTOR2_VELOCITY, OUTPUT);
}

bool enemy_detected() {
  return true;
}

int sensor_get_distance() {
  digitalWrite(TRIGGER, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER, LOW);
  int duration = pulseIn(ECHO, HIGH);
  int distance = (duration / 2) * SPEED_OF_SOUND;
  return distance;
}

void forward_wheel_left(){
  digitalWrite(MOTOR1_FORWARD, HIGH);
  digitalWrite(MOTOR1_BACKWARD, LOW);
  analogWrite(MOTOR1_VELOCITY, 50); //This value need to be from 0-255
}
void forward_wheel_right(){
  digitalWrite(MOTOR2_FORWARD, HIGH);
  digitalWrite(MOTOR2_BACKWARD, LOW);
  analogWrite(MOTOR2_VELOCITY, 50); //This value need to be from 0-255
}

void backward_wheel_left(){
  // Backward
  digitalWrite(MOTOR1_FORWARD, LOW);
  digitalWrite(MOTOR1_BACKWARD, HIGH);
  analogWrite(MOTOR1_VELOCITY, 200); //This value need to be from 0-255
}
  
void backward_wheel_right(){
  digitalWrite(MOTOR2_FORWARD, LOW);
  digitalWrite(MOTOR2_BACKWARD, HIGH);
  analogWrite(MOTOR2_VELOCITY, 200); //This value need to be from 0-255
  delay(1000);
}

void update_sensor_values() {
    previous_left_sensor = current_left_sensor;
    current_left_sensor = analogRead(LEFT_SENSOR);
    previous_middle_sensor = current_middle_sensor;
    current_middle_sensor = analogRead(MIDDLE_SENSOR);
    previous_right_sensor = current_right_sensor;
    current_right_sensor = analogRead(RIGHT_SENSOR);
}

void update_state() {
    current_state = STATE_AVOID_GOING_OUTSIDE;
    
    if (enemy_detected()) {
      current_state = STATE_ENEMY_ATTACK;
   }
}

void execute_strategy() {    
    if (current_state == STATE_ENEMY_FIND) {
        // find enemy
    }

    if (current_state == STATE_ENEMY_ATTACK) {
        // move forward
    }

    if (current_state == STATE_AVOID_GOING_OUTSIDE) {
        // move away from tape
    }
}

void loop() {
  update_sensor_values();
  update_state();
  execute_strategy();
//  int distance = sensor_get_distance();
//    Serial.println(distance);
//    Serial.println("LEFT_SENSOR");
//    Serial.println(analogRead(LEFT_SENSOR));
//
//    Serial.println("MIDDLE_SENSOR");
//    Serial.println(analogRead(MIDDLE_SENSOR));
//
//    Serial.println("RIGHT_SENSOR");
//    Serial.println(analogRead(RIGHT_SENSOR));
    
  


    
}
