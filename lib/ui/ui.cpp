#include "ui.h"

#include <WiFiManager.h>
#include <ArduinoLog.h>

namespace {
    const unsigned int kBackgroundColor = M5.Lcd.color565(0, 0, 4);
    const unsigned int kHeaderColor = M5.Lcd.color565(99, 202, 202);
    const unsigned int kFooterColor = M5.Lcd.color565(128, 230, 230);
    const unsigned long kScreenTimeout = 5000;
    const int32_t kHeaderH = 20;
    const int32_t kFooterH = 20;

    float accX = 0;
    float accY = 0;
    float accZ = 0;

} // anonymous namespace

StickUI::StickUI() : screenState(screenState::unknown) {}

void StickUI::Begin() {
    M5.Lcd.fillScreen(kBackgroundColor);
    M5.Lcd.setTextColor(TFT_BLACK);
    M5.Lcd.setTextSize(2);

    turnOnDisplay();
}

void StickUI::Update() {
    if (M5.BtnB.wasReleased()) {
        if (screenState == screenState::off) {
            turnOnDisplay();
        } else {
            turnOffDisplay();
        }
    }

    if (screenState == screenState::off) {
        return;
    }

    drawHeader();
    drawFooter();
}

void StickUI::turnOffDisplay() {
    if (screenState == screenState::off) {
        return;
    }

    // LDO2 is LCD Backlight
    // LDO3 is LCD Power
    M5.Axp.Write1Byte(0x12, M5.Axp.Read8bit(0x12) & 0x4B);
    screenState = screenState::off;
}

void StickUI::turnOnDisplay() {
    if (screenState == screenState::on) {
        return;
    }

    // LDO2 is LCD Backlight
    // LDO3 is LCD Power
    M5.Axp.Write1Byte(0x12, M5.Axp.Read8bit(0x12) | 0x4D);
    screenState = screenState::on;
}

void StickUI::drawHeader() {
    M5.Lcd.fillRect(0, 0, TFTW, kHeaderH, kHeaderColor);
    M5.Lcd.setCursor(2, 2);
    M5.Lcd.printf("%.1fv", M5.Axp.GetBatVoltage());
}

void StickUI::drawFooter() {
    M5.Lcd.fillRect(0, TFTH - kFooterH, TFTW, kFooterH, kFooterColor);
    M5.Lcd.setCursor(2, TFTH - kFooterH + 2);
    M5.Lcd.println(WiFi.localIP());
}

StickUI UI;
