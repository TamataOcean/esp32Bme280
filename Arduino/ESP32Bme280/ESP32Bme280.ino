/*
* Description:
* This sample code is mainly used to monitor sensorHub and sending through Mqtt Json data
* temperature, dissolved oxygen, ec and orp,etc.
*
* Software Environment: Arduino IDE 1.8.9
* Software download link: https://www.arduino.cc/en/Main/Software
*
* Install the library file：
* Copy the files from the github repository folder libraries to the libraries
* in the Arduino IDE 1.8.9 installation directory
*
* Hardware platform   : ESP32
*
* author  :  Rominco(rtourte@yahoo.fr)
* version :  V1.0
* date    :  2019-09-23
**********************************************************************
 */

#include <WiFi.h>
#include <PubSubClient.h>
#include "SparkFunBME280.h"
BME280 mySensor;

const char* ssid     = "WifiRaspi";
const char* password = "password";
const char* mqtt_server = "10.3.141.1";
const char* mqtt_user = "BME280-Station1";
const char* mqtt_output = "bme280/update";
const char* mqtt_input = "bme280/input";
const char* mqtt_log = "esp32/log";

const int ledPin = 4;
int timeInterval = 30000;

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

/* ------------------------
 *  MAIN SETUP 
 *  -----------------------
 */
void setup()
{
    Serial.begin(115200);
    delay(10);

    setup_wifi();
    client.setServer(mqtt_server, 1883);
    client.setCallback(callback);

    Serial.println("BME280 begin");
    
    // I2C device found at address 0x76
    Wire.begin();
    if (mySensor.beginI2C() == false) //Begin communication over I2C
    {
      Serial.println("The sensor did not respond. Please check wiring.");
      while(1); //Freeze
    }
    else
    {
      Serial.println("BME280 started & configured");

    }
}

/* ------------------------
 *  MQTT CALLBACK
 *  -----------------------
 */
void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();

  // Feel free to add more if statements to control more GPIOs with MQTT

  // If a message is received on the topic esp32/input, you check if the message is either "on" or "off". 
  // Changes the output state according to the message
  if (String(topic) == mqtt_input ) {
    Serial.print("Changing output to ");
    if(messageTemp == "on"){
      Serial.println("on");
      client.publish(mqtt_log, "changing to ON" );
      digitalWrite(ledPin, HIGH);
    }
    else if(messageTemp == "off"){
      Serial.println("off");
      client.publish(mqtt_log, "changing to OFF" );
      digitalWrite(ledPin, LOW);
    }
    else if(messageTemp == "timeInterval_1000") {
      Serial.println("Time Interval order received");
      timeInterval = 1000;
      client.publish(mqtt_log, "Interval set to 1000" );
    }
    else if(messageTemp == "timeInterval_5000") {
      Serial.println("Time Interval order received");
      timeInterval = 5000;
      client.publish(mqtt_log, "Interval set to 5000" );
    }
  }
}

/* ----------------------
 *  WIFI SETUP 
 *  ---------------------
 */
void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

/* 
 *  ------------------
 *  RECONNECT MQTT
 *  ------------------
 */
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
      // Subscribe
      client.subscribe(mqtt_input);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

/* 
 *  ------------------
 *  MAIN LOOP
 *  ------------------
 */
void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  long now = millis();
  if (now - lastMsg > timeInterval ) {
    lastMsg = now;
    Serial.print("Humidity: ");
    Serial.print(mySensor.readFloatHumidity(), 0);
    
    Serial.print(" Pressure: ");
    Serial.print(mySensor.readFloatPressure(), 0);
    
    Serial.print(" Alt: ");
    //Serial.print(mySensor.readFloatAltitudeMeters(), 1);
    Serial.print(mySensor.readFloatAltitudeFeet(), 1);
    
    Serial.print(" Temp: ");
    //Serial.print(mySensor.readTempC(), 2);
    Serial.print(mySensor.readTempC(), 2);
    
    Serial.println();

    String json = "{\"user\":\""+ (String) mqtt_user +"\",\"Humidity\":\""+(String)mySensor.readFloatHumidity()+"\",\"Pressure\":\""+(String)mySensor.readFloatPressure()+"\",\"Altitude\":\""+(String)mySensor.readFloatAltitudeMeters()+"\",\"Temperature\":\""+(String)mySensor.readTempC()+"\"}";
    client.publish(mqtt_output, json.c_str() );
    Serial.println("publishing on " + (String)mqtt_output);
    Serial.println(json);
    }
  delay(500);

  }
