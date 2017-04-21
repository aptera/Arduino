#define TRIGGER_PIN 9
#define ECHO_PIN 10
#define LED_PIN 13

#define VCC 8
#define GND 11

#define THRESHOLD_DISTANCE 50
#define SPEED_OF_SOUND_IN_MICROSECONDS_PER_CENTIMETER 29.1

void setup() {
  Serial.begin (9600);
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(VCC, OUTPUT);
  pinMode(GND, OUTPUT);

  digitalWrite(VCC, HIGH);
  digitalWrite(GND, LOW);
}

void loop() {
  long distance = GetDistance();
  SetTheLEDStatus(distance);

  WriteDistanceToSerialPort(distance);

  delay(500);
}

long GetDistance(){
  long duration;
  long distance;

  SendThePulse();
  duration = GetDurationUntilReturnSignal();
  distance = ConvertDurationToDistance(duration);

  return distance;
}

void SendThePulse(){
  digitalWrite(TRIGGER_PIN, LOW);  
  delayMicroseconds(2); 
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10); 
  digitalWrite(TRIGGER_PIN, LOW);
}

long GetDurationUntilReturnSignal(){
  return pulseIn(ECHO_PIN, HIGH);
}

long ConvertDurationToDistance(long duration){
  // The ultrasonic ping will travel from the sensor to the object and back. 
  // So the distnace is half of the time it took the pink to travel. 
  // Then convert that time to a distnace in centimeters. 
  return (duration/2) / SPEED_OF_SOUND_IN_MICROSECONDS_PER_CENTIMETER;
}

void SetTheLEDStatus(long distance){
  if (distance < THRESHOLD_DISTANCE) { 
    digitalWrite(LED_PIN,HIGH); 
  }
  else {
    digitalWrite(LED_PIN,LOW);
  }
}

bool IsSomeoneInStall(long distnace){
  return distnace < THRESHOLD_DISTANCE;
}

void WriteDistanceToSerialPort(long distance){
 // Print the distance
  if (distance >= 200 || distance <= 0){
    Serial.println("Out of range");
  }
  else {
    Serial.print(distance);
    Serial.println(" cm");
  }
}




