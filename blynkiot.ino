/*************************************************************

  This is a simple demo of sending and receiving some data.
  Be sure to check out other examples!
 *************************************************************/

// Template ID, Device Name and Auth Token are provided by the Blynk.Cloud
// See the Device Info tab, or Template settings
#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "write your template id"
#define BLYNK_DEVICE_NAME "write your device name"
#define BLYNK_AUTH_TOKEN "write your token"


// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial

#include <Wire.h>
#include "Adafruit_HTU21DF.h"
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.

char ssid[] = "write your wifi ssid";
char pass[] = "write your wifi password";

Adafruit_HTU21DF htu = Adafruit_HTU21DF();

float temperature = 0.0;
float humidity    = 0.0;

BlynkTimer timer;


// This function is called every time the device is connected to the Blynk.Cloud


void setup()
{ 
  Serial.begin(9600);
  WiFi.begin(ssid, pass);
  htu.begin();
  
  if (!htu.begin()) {
    Serial.println("Couldn't find sensor!");
  }
  
  temperature = htu.readTemperature();
  humidity    = htu.readHumidity();

  Serial.print("Temp: "); 
  Serial.print(temperature); 
  Serial.print("\n");
  delay(1000);
  Serial.print("Humidity: "); 
  Serial.print(humidity); 
  Serial.print("\n");
  delay(1000); 
  Blynk.begin(auth, ssid, pass);
  Blynk.connect();  
  // Setup a function to be called every second

  Blynk.virtualWrite(V1, humidity); // select your virtual pins accordingly
  Blynk.virtualWrite(V0, temperature); // select your virtual pins accordingly 

  Serial.println("Restarting");
  ESP.restart();

}
void loop()
{
  
  timer.run();
  Blynk.run();
  // You can inject your own code or combine it with other sketches.
  // Check other examples on how to communicate with Blynk. Remember
  // to avoid delay() function!
}