const int TRIGGER = 4; //12
const int ECHO = 7; //13
const int MAXIMUM_VALUE = 255;
const int MOTOR2_FORWARD = 13;
const int MOTOR2_BACKWARD = 12;
const int MOTOR2_VELOCITY = 11;
const int MOTOR1_FORWARD = 8;
const int MOTOR1_BACKWARD = 9;
const int MOTOR1_VELOCITY = 10;
const int RIGHT_SENSOR = A2;
const int MIDDLE_SENSOR = A1;
const int LEFT_SENSOR = A0;
const String STATE_AVOID_GOING_OUTSIDE = "stay_inside";
const String STATE_ENEMY_FIND = "find";
const String STATE_ENEMY_ATTACK = "attack";
const String STRATEGY_BACK_LEFT = "avoid_back_left";
const String STRATEGY_BACK_RIGHT = "avoid_back_right";
String current_state = STATE_ENEMY_FIND;
String current_avoid_strategy = STRATEGY_BACK_LEFT;

int current_right_sensor = 0;
int previous_right_sensor = 0;

int current_middle_sensor = 0;
int previous_middle_sensor = 0;

int current_left_sensor = 0;
int previous_left_sensor = 0;

double distance_echo = 0.00;

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
  distance_echo = (duration / 2) * SPEED_OF_SOUND;
//  Serial.println("Distance:");
//  Serial.println(distance);
//  Serial.println("Duration:");
//  Serial.println(duration);
  return distance_echo;
}

void forward(){
  forward_wheel_left();
  forward_wheel_right();
}

void spinBackRight(){
  backRight();
  delay(350);
}

void spinBackLeft(){
  backLeft();
  delay(350);
}

void forwardRight(){
  digitalWrite(MOTOR1_FORWARD, HIGH);
  digitalWrite(MOTOR1_BACKWARD, LOW);
  analogWrite(MOTOR1_VELOCITY, 20); //This value need to be from 0-255
  digitalWrite(MOTOR2_FORWARD, HIGH);
  digitalWrite(MOTOR2_BACKWARD, LOW);
  analogWrite(MOTOR2_VELOCITY, 150); //This value need to be from 0-255
}

void backRight(){
  digitalWrite(MOTOR1_FORWARD, LOW);
  digitalWrite(MOTOR1_BACKWARD, HIGH);
  analogWrite(MOTOR1_VELOCITY, 230); //This value need to be from 0-255
  digitalWrite(MOTOR2_FORWARD, LOW);
  digitalWrite(MOTOR2_BACKWARD, HIGH);
  analogWrite(MOTOR2_VELOCITY, 50); //This value need to be from 0-255
}

void forwardLeft(){
  digitalWrite(MOTOR1_FORWARD, HIGH);
  digitalWrite(MOTOR1_BACKWARD, LOW);
  analogWrite(MOTOR1_VELOCITY, 150); //This value need to be from 0-255
  digitalWrite(MOTOR2_FORWARD, HIGH);
  digitalWrite(MOTOR2_BACKWARD, LOW);
  analogWrite(MOTOR2_VELOCITY, 20); //This value need to be from 0-255
}

void backLeft(){
  digitalWrite(MOTOR1_FORWARD, LOW);
  digitalWrite(MOTOR1_BACKWARD, HIGH);
  analogWrite(MOTOR1_VELOCITY, 50); //This value need to be from 0-255
  digitalWrite(MOTOR2_FORWARD, LOW);
  digitalWrite(MOTOR2_BACKWARD, HIGH);
  analogWrite(MOTOR2_VELOCITY, 230); //This value need to be from 0-255
}

void do_ramming_speed(){
  digitalWrite(MOTOR1_FORWARD, HIGH);
  digitalWrite(MOTOR1_BACKWARD, LOW);
  analogWrite(MOTOR1_VELOCITY, 140); //This value need to be from 0-255
  digitalWrite(MOTOR2_FORWARD, HIGH);
  digitalWrite(MOTOR2_BACKWARD, LOW);
  analogWrite(MOTOR2_VELOCITY, 140); //This value need to be from 0-255
}

void do_ramming_speed_plus(){
  digitalWrite(MOTOR1_FORWARD, HIGH);
  digitalWrite(MOTOR1_BACKWARD, LOW);
  analogWrite(MOTOR1_VELOCITY, 255); //This value need to be from 0-255
  digitalWrite(MOTOR2_FORWARD, HIGH);
  digitalWrite(MOTOR2_BACKWARD, LOW);
  analogWrite(MOTOR2_VELOCITY, 255); //This value need to be from 0-255
}

void do_stop(){
  forward_wheel_left_stop();
  forward_wheel_right_stop();
}

void back(){
  backward_wheel_left();
  backward_wheel_right();
}
  
void forward_wheel_right(){
  digitalWrite(MOTOR1_FORWARD, HIGH);
  digitalWrite(MOTOR1_BACKWARD, LOW);
  analogWrite(MOTOR1_VELOCITY, 40); //This value need to be from 0-255
}

void forward_wheel_left(){
  digitalWrite(MOTOR2_FORWARD, HIGH);
  digitalWrite(MOTOR2_BACKWARD, LOW);
  analogWrite(MOTOR2_VELOCITY, 40); //This value need to be from 0-255
}

void forward_wheel_right_stop(){
  digitalWrite(MOTOR1_FORWARD, LOW);
  digitalWrite(MOTOR1_BACKWARD, LOW);
  analogWrite(MOTOR1_VELOCITY, 0); //This value need to be from 0-255
}

void forward_wheel_left_stop(){
  digitalWrite(MOTOR2_FORWARD, LOW);
  digitalWrite(MOTOR2_BACKWARD, LOW);
  analogWrite(MOTOR2_VELOCITY, 0); //This value need to be from 0-255
}

void backward_wheel_right(){
  digitalWrite(MOTOR1_FORWARD, LOW);
  digitalWrite(MOTOR1_BACKWARD, HIGH);
  analogWrite(MOTOR1_VELOCITY, 100); //This value need to be from 0-255
}
  
void backward_wheel_left(){
  digitalWrite(MOTOR2_FORWARD, LOW);
  digitalWrite(MOTOR2_BACKWARD, HIGH);
  analogWrite(MOTOR2_VELOCITY, 100); //This value need to be from 0-255
}

void update_sensor_values() {
    sensor_get_distance();
    previous_left_sensor = current_left_sensor;
    current_left_sensor = analogRead(LEFT_SENSOR);
    previous_middle_sensor = current_middle_sensor;
    current_middle_sensor = analogRead(MIDDLE_SENSOR);
    previous_right_sensor = current_right_sensor;
    current_right_sensor = analogRead(RIGHT_SENSOR);
    Serial.println("PREVIOUS_LEFT:");
    Serial.println(previous_left_sensor);
    Serial.println("CURRENT_LEFT:");
    Serial.println(current_left_sensor);
}

void update_state() {
    if (distance_echo <= 60) {
      current_state = STATE_ENEMY_ATTACK;
    }

    if (distance_echo > 60) {
      current_state = STATE_ENEMY_FIND;
    }

    if (current_left_sensor < 100 || current_right_sensor < 100) {
      current_state = STATE_AVOID_GOING_OUTSIDE;
      
      if (current_left_sensor < 100) {
          current_avoid_strategy = STRATEGY_BACK_RIGHT;
      }

      if (current_right_sensor < 100) {
          current_avoid_strategy = STRATEGY_BACK_LEFT;
      }
      
    }
}

void execute_strategy() {    
    if (current_state == STATE_ENEMY_FIND) {
        // find enemy
       forwardRight();
    }

    if (current_state == STATE_ENEMY_ATTACK) {
        // move forward
       if (distance_echo < 30) {
          do_ramming_speed_plus();
       } else {
          do_ramming_speed();
       } 
    }

    if (current_state == STATE_AVOID_GOING_OUTSIDE) {
        // move away from tape
        do_stop();
        if (current_avoid_strategy == STRATEGY_BACK_RIGHT) {
            spinBackRight();
        }
        if (current_avoid_strategy == STRATEGY_BACK_LEFT) {
            spinBackLeft();
        }
    }
}

void loop() {
  update_sensor_values();
  update_state();
  execute_strategy();
  Serial.println(current_state);
}
