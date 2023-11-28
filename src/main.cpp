
//
//https://registry.platformio.org/libraries/axcap/Esp-GitHub-OTA
#define M_SIZE 0.99

#include <Arduino.h>
#include <TFT_eSPI.h>
#include <SPI.h>
#include "Wifi.h"
#include "HttpsOTAUpdate.h"
#include "WiFiManager.h" // https://github.com/tzapu/WiFiManager
#include <ezButton.h>

TFT_eSPI tft = TFT_eSPI(); // Invoke custom library

#define BUTTON1PIN 35
#define BUTTON2PIN 0

#define TFT_GREY 0x5AEB
#define TFT_ORANGE 0xFD20 /* 255, 165,   0 */

// setup buttons

ezButton buttonA(BUTTON1PIN);
ezButton buttonB(BUTTON2PIN);

float ltx = 0;                                   // Saved x coord of bottom of needle
uint16_t osx = M_SIZE * 120, osy = M_SIZE * 120; // Saved x & y coords
uint32_t updateTime = 0;                         // time for next update

int old_analog = -999; // Value last displayed

int value[6] = {0, 0, 0, 0, 0, 0};
int old_value[6] = {-1, -1, -1, -1, -1, -1};
int d = 0;

// signatures
 

void setup(void)
{
  Serial.begin(115200); // For debug

 // pinMode(buttonPin, INPUT_PULLUP);    // Set the switch pin as input
  pinMode(LED_BUILTIN, OUTPUT);

  buttonA.setDebounceTime(150);
  buttonB.setDebounceTime(150);

  tft.init();
  tft.setRotation(3);

  tft.fillScreen(TFT_BLACK);

   

  updateTime = millis(); // Next update time
                         // WiFiManager, Local intialization. Once its business is done, there is no need to keep it around
  WiFiManager wm;

  bool res;
  // res = wm.autoConnect(); // auto generated AP name from chipid
  // res = wm.autoConnect("AutoConnectAP"); // anonymous ap
  res = wm.autoConnect("TTGO_OTA", "password"); // password protected ap

  if (!res)
  {
    Serial.println("Failed to connect");
    // ESP.restart();
  }
  else
  {
    // if you get here you have connected to the WiFi
    Serial.println("connected...yeey :)");
    Serial.println(wm.getDefaultAPName());
    Serial.println(wm.getWiFiSSID());
  }
}
void toggleLED()
{

  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
 
}
void loop()
{
  buttonA.loop();
  buttonB.loop();
  

  if (buttonA.isPressed())
  {
    Serial.println("Toggle A");
    toggleLED();
  }

  if (buttonB.isPressed())
  {
    Serial.println("Toggle B");
    toggleLED();
  }

  if (updateTime <= millis())
  {
    updateTime = millis() + 35; // Update meter every 35 milliseconds

    
  }
}

 
void checkForUpdate()
{
}
