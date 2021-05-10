#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>    

#define FIREBASE_HOST "add host id"              
#define FIREBASE_AUTH "add secret key"  

#define trigPin 13 //d7
#define echoPin 15 //d6
char* ssid = "name";
char* password = "password";

long int data;
long duration;
long inches;

void setup() {
  pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);
 WiFi.begin(ssid,password);
  Serial.begin(115200);
  while(WiFi.status()!=WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

   Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
   Firebase.setString("notification/status", "no");    

}

void loop() {
  visitoralert();

}

void visitoralert(){
  digitalWrite(trigPin, LOW);
 delayMicroseconds(1);
  digitalWrite(trigPin, HIGH);
 delayMicroseconds(10);
 digitalWrite(trigPin, LOW);
 pinMode(echoPin, INPUT);
 duration = pulseIn(echoPin, HIGH);
 inches = (duration / 2) / 74;
 
  if (inches < 5) {
    Firebase.setString("notification/status", "yes"); 
    delay(2000);
  }
  else{
    Firebase.setString("notification/status", "no"); 
  }
}
