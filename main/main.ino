const int TRIGGER = 4; //12
const int ECHO = 7; //13
const int MAXIMUM_VALUE = 255;
const int MOTOR2_FORWARD = 12;
const int MOTOR2_BACKWARD = 13;
const int MOTOR2_VELOCITY = 11;
const int MOTOR1_FORWARD = 9;
const int MOTOR1_BACKWARD = 8;
const int MOTOR1_VELOCITY = 10;
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
  double distance = (duration / 2) * SPEED_OF_SOUND;
  Serial.println("Distance:");
  Serial.println(distance);
  Serial.println("Duration:");
  Serial.println(duration);
  return distance;
}

void forward(){
  forward_wheel_left();
  forward_wheel_right();
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
  analogWrite(MOTOR1_VELOCITY, 100); //This value need to be from 0-255
}

void forward_wheel_left(){
  digitalWrite(MOTOR2_FORWARD, HIGH);
  digitalWrite(MOTOR2_BACKWARD, LOW);
  analogWrite(MOTOR2_VELOCITY, 100); //This value need to be from 0-255
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
//    previous_left_sensor = current_left_sensor;
//    current_left_sensor = analogRead(LEFT_SENSOR);
//    previous_middle_sensor = current_middle_sensor;
//    current_middle_sensor = analogRead(MIDDLE_SENSOR);
//    previous_right_sensor = current_right_sensor;
//    current_right_sensor = analogRead(RIGHT_SENSOR);
}

void update_state() {
    current_state = STATE_AVOID_GOING_OUTSIDE;
    
    if (enemy_detected()) {
      current_state = STATE_ENEMY_ATTACK;
    }
}

void execute_strategy() {    
    Serial.println(current_state);
    if (current_state == STATE_ENEMY_FIND) {
        // find enemy
       delay(1000);
    }

    if (current_state == STATE_ENEMY_ATTACK) {
        // move forward
       forward();
       
       delay(1000);
    }

    if (current_state == STATE_AVOID_GOING_OUTSIDE) {
        // move away from tape
        back();
        forward();
        delay(300);
        do_stop();
        back();
        delay(300);
        do_stop();
    }
}

void loop() {
  update_sensor_values();
//  update_state();
//  execute_strategy();
//  Serial.println(current_state);
}
