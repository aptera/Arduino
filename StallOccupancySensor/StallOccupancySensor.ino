#define TRIGGER_PIN 9
#define ECHO_PIN 10
#define LED_PIN 13

#define LED_COMMON_PIN 6
#define LED_R_PIN 7
#define LED_G_PIN 5
#define LED_B_PIN 4

#define VCC 8
#define GND 11

#define THRESHOLD_DISTANCE 130
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

  pinMode(LED_COMMON_PIN, OUTPUT);
  pinMode(LED_R_PIN, OUTPUT);
  pinMode(LED_G_PIN, OUTPUT);
  pinMode(LED_B_PIN, OUTPUT);

  digitalWrite(LED_COMMON_PIN, LOW);
  digitalWrite(LED_R_PIN, LOW);
  digitalWrite(LED_G_PIN, LOW);
  digitalWrite(LED_B_PIN, LOW);
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

long lastSightingTime = 0;
void SetTheLEDStatus(long distance){
  if (IsSomeoneInStall(distance)) { 
    digitalWrite(LED_PIN,HIGH); 
    digitalWrite(LED_R_PIN, HIGH);
    lastSightingTime = millis();
  }
  else if (HasSomeoneBeenInStallInLastTenSeconds()){
    digitalWrite(LED_PIN,HIGH); 
    digitalWrite(LED_R_PIN, HIGH);
  }
  else {
    digitalWrite(LED_PIN,LOW);
    digitalWrite(LED_R_PIN, LOW);
  }
}

bool HasSomeoneBeenInStallInLastTenSeconds(){
  long currentTime = millis();

  return (lastSightingTime + 10000) > currentTime;
}

bool IsSomeoneInStall(long distance){
  //return distnace < THRESHOLD_DISTANCE;
  if(146 < distance && distance < 152){
    return false;
  }
  return true;
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




