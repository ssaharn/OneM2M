#include <ESP8266WiFi.h>
#include<Servo.h> 
#include<ArduinoJson.h> 


const char* ssid = "Enter SSID";
const char* pass = "Enter password";
const char* host = "Enter Gateway/Thyme IP address";
const int port = 3105;

Servo myservo;
int servoPin = D7;

WiFiClient client;

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, pass); 
  //client.setTimeout(5000);
   
  while (WiFi.status() != WL_CONNECTED) { 
  delay(500);
  Serial.println("Waiting for connection");
 }
  Serial.println("Connecting to the gateway...");
  if (client.connect(host,3105)){
    client.print("{\"ctname\":\"servoM\",\"con\":\"hello\"}<EOF>");
    client.readStringUntil('\n');
     } else{
    Serial.println("Connection failed");
  }
  Serial.println("Connected!");
}

void loop() {
String line; 
if (client.available()){
      line = client.readStringUntil('<');
      client.readStringUntil('\n');
      StaticJsonBuffer<200> jsonBuffer;
      JsonObject& abc = jsonBuffer.parseObject(line);
      const char* angle = abc["con"];
      myservo.write(atoi(angle));
      delay(1000);
      Serial.print("Angle = ");
      Serial.print(angle);
      Serial.println(" degrees");
      Serial.println("Rotated!");
      
}
if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();
    for(;;);
}
}
