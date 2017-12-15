const int TRIGGER = 4; //12
const int ECHO = 7; //13

const double SPEED_OF_SOUND = 0.034;

void setup() {
  Serial.begin(9600);
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);
}

int get_distance() {
  digitalWrite(TRIGGER, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER, LOW);
  int duration = pulseIn(ECHO, HIGH);
  int distance = (duration / 2) * SPEED_OF_SOUND;
  return distance;
}

void loop() {
  int distance = get_distance();
  Serial.println(distance);
}
