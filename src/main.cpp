#include <M5StickCPlus.h>
#include <WiFiManager.h>
#include <ArduinoLog.h>

#include <ui.h>

#define AP_NAME "B5STICK"

static WiFiManager wifiManager;

void gen_passwd(char *out) {
  uint8_t raw[4];
  esp_fill_random(raw, 4);
  sprintf(out, "%x%x%x%x", raw[0], raw[1], raw[2], raw[3]);
}

void setup(){
  M5.begin(
    true /*LCDEnable*/,
    true /*PowerEnable*/, 
    true /*SerialEnable*/
  );

  Log.begin(LOG_LEVEL_VERBOSE, &Serial);
  Log.infoln("starts up");

  M5.IMU.Init();

  UI.Begin();

  char apPassword[9];
  gen_passwd(apPassword);
  wifiManager.setDebugOutput(true);
  wifiManager.setAPCallback([&apPassword](WiFiManager *myWiFiManager) {
    M5.Lcd.setCursor(0, 0, 4);
    M5.Lcd.println("Entered config mode");
    M5.Lcd.printf("\t- Name: %s\n", AP_NAME);
    M5.Lcd.printf("\t- Pass: %s\n", apPassword);
  });

  wifiManager.autoConnect(AP_NAME, apPassword);
}

void loop() {
  M5.update();
  UI.Update();

  delay(100);
}