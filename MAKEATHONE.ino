#define trigPin 13
#define echoPin 12
#define red 11
#define green 10
#define white 5
int timer1;
int timer2;
float Time;
int ir_s1=3;
int ir_s2=6;
float distance = 14.0;
float speed;
int flag1 = 0;
int flag2 = 0;



void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(white, OUTPUT);
  pinMode(ir_s1, INPUT);
  pinMode(ir_s2, INPUT);
}

void loop() {
  if (digitalRead(ir_s1) == HIGH && flag1 == 0) {
    timer1 = millis();
    flag1 = 1;
  }

  if (digitalRead(ir_s2) == HIGH && flag2 == 0) {
    timer2 = millis();
    flag2 = 1;
  }

  if (flag1 == 1 && flag2 == 1) {
    if (timer1 > timer2) {
      Time = timer1 - timer2;
    } else if (timer2 > timer1) {
      Time = timer2 - timer1;
    }
    Time = Time / 1000; //convert millisecond to second
    speed = (distance / Time); //v=d/t
    speed = speed * 3600; //multiply by seconds per hr
    speed = speed / 100000; //division by centimeters per Km
  }

  if (speed == 0) {   
    //lcd.setCursor(0, 1);
    if (flag1 == 0 && flag2 == 0) {
      Serial.println("No car detected");
      digitalWrite(white,LOW);
    } else {
      Serial.println("Searching...");
      digitalWrite(white,LOW);
    }
  }else {
    Serial.flush();
    //lcd.setCursor(0, 0);
    Serial.print("Speed: ");
    Serial.print(speed);
    Serial.print(" Km/Hr: ");
    if (speed > 1) {
      Serial.println("Over Speeding");
      digitalWrite(white, HIGH);
    } else {
      Serial.println("Normal Speed");
      digitalWrite(white,LOW);
    }
    delay(1500);
    //digitalWrite(buzzer, LOW);
    speed = 0;
    flag1 = 0;
    flag2 = 0;
  }



  long duration, distance;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  if (distance < 20) {  // This is where the LED On/Off happens
    digitalWrite(red,HIGH); // When the Red condition is met, the Green LED should turn off
  digitalWrite(green,LOW);
}
  else {
    digitalWrite(red,LOW);
    digitalWrite(green,HIGH);
  }
  if (distance >= 200 || distance <= 0){
    Serial.println("Out of range");
  }
  else {
    Serial.print(distance);
    Serial.println(" cm");
  }
  delay(200);
}