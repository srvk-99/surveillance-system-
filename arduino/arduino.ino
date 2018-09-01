 #include <FirebaseArduino.h>
#include <ESP8266WiFi.h>

#define WIFI_SSID "****"
#define WIFI_PASSWORD "****"

//this firebase project was deleted
//you'll need to enter your own firebase info
#define FIREBASE_HOST "***********.firebaseio.com"
  
int trigPin=4;
int echoPin=2;
int ledPower = 13;
long duration;
float distance;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST);
  pinMode(ledPower, OUTPUT);
}

int calculateDistance(){ 
  
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); 
  distance= duration/0.034/2;
  return distance;
}

void loop() {
  String LEDSTATUS1 = Firebase.getString("LEDSTATUS");
  
  if(LEDSTATUS1 == "1")
  {
    digitalWrite(ledPower, HIGH);
    int distance= calculateDistance();
    Serial.println(distance);
    Firebase.setFloat ("distance of object",distance);
  } 
  
  else {
    digitalWrite(ledPower, LOW);
    int distance= calculateDistance();
     Serial.println(distance);
    Firebase.setFloat ("distance of object",distance);
  }

  
}
