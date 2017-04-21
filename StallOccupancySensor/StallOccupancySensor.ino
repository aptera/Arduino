

#define trigPin 9
#define echoPin 10
#define led 13

#define VCC 8
#define GND 11

#define THRESHOLD_DISTANCE 50

void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led, OUTPUT);
  pinMode(VCC, OUTPUT);
  pinMode(GND, OUTPUT);

  digitalWrite(VCC, HIGH);
  digitalWrite(GND, LOW);
}

void loop() {
  // Send the Pulse
  long duration, distance;
  digitalWrite(trigPin, LOW);  
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW);

  // Listen for the Pulse
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;

  // Set the LED status
  if (distance < THRESHOLD_DISTANCE) { 
    digitalWrite(led,HIGH); 
  }
  else {
    digitalWrite(led,LOW);
  }

  // Print the distance
  if (distance >= 200 || distance <= 0){
    Serial.println("Out of range");
  }
  else {
    Serial.print(distance);
    Serial.println(" cm");
  }
  delay(500);
}

