#include <ESP8266WiFi.h>
#include <Adafruit_MQTT_Client.h>

#define network "type_your_network_name"
#define password "type_your_network_password"

#define server "io.adafruit.com"
#define port 1883
#define username "type_your_adafruit_username"
#define key "copy_the_adfruit_key_here"

WiFiClient esp;

Adafruit_MQTT_Client mqtt(&esp,server,port,username,key);
Adafruit_MQTT_Publish feed (&mqtt,username "/feed/your_feed_name" );

void setup(){
     Serial.begin(115200);
    wifi.begin(network,password);
    Serial.println("connecting to: ");
    Serial.print(network);
    while(WiFi.status()!=WL_CONNECTED)
    {
      delay(500);
      Serial.print(".");
    }
    while(mqtt.connect())
    {
      Serial.print(".");
    }
}

void loop(){
  if(mqtt.connected()){
    int data = analogRead(A0);
    Serial.println(data);
    if(feed.publish(data)){
      Serial.print("success");
    }
    else{
      Serial.println("failed");
    }
  }
  delay(2500);
}
