#include <ESP8266WiFi.h>
#include <string.h>

const char* ssid = "Enter SSID";
const char* pass = "Enter password";
const char* host = "Enter Gateway/Thyme IP address";
const int port = 3105;

WiFiClient client;
const int trigPin = D0;
const int echoPin = D2;
long duration;
float distance;
void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, pass);  
 
  while (WiFi.status() != WL_CONNECTED) { 
 
    delay(500);
    Serial.println("Waiting for connection");
 
  }
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}
void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.0340 / 2;
  upd_dist(distance);
  delay(200);
  
}
void upd_dist(float distance){
 if (client.connect(host,port))
{
 char body[64];
 snprintf(body,sizeof(body),"{\"ctname\":\"ultraSonic\",\"con\":%f}<EOF>",distance);
 client.print(body);
}
else
{
  Serial.println("connection failed");
    client.stop();          
}
}
