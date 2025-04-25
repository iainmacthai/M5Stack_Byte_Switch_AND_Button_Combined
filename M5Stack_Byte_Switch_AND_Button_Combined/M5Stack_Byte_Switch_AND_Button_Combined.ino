/*  M5Stack_Byte_Switch_AND_Button_Combined.ino
* ESP32-CYD (ESP32 Dev Module)
*
* M5Unified V0.2.5
* Arduino IDE 2.3.2
* Boards Manager - ESP32 by Espressif V3.1.0
* Iain MacMillan
* 26/04/2025
*/

#include "unit_byte.hpp"
#include <M5Unified.h>
#include <Wire.h>

UnitByte deviceSwitch;  // ByteSwitch at 0x46
UnitByte deviceButton;  // ByteButton at 0x47

const uint8_t switchId = 0x46;
const uint8_t buttonId = 0x47;

void setup() {
    Serial.begin(115200);
    Wire.begin(27, 22);

    deviceSwitch.begin(&Wire, switchId, 27, 22, 400000);
    deviceSwitch.setLEDShowMode(BYTE_LED_MODE_DEFAULT);
    for (int i = 0; i < 8; i++) {
        deviceSwitch.setSwitchOffRGB888(i, 0xFF0000);
        deviceSwitch.setSwitchOnRGB888(i, 0x00FF00);
    }
    deviceSwitch.setFlashWriteBack();


    deviceButton.begin(&Wire, buttonId, 27, 22, 400000);
    deviceButton.setLEDShowMode(BYTE_LED_MODE_DEFAULT);
    for (int i = 0; i < 8; i++) {
        deviceButton.setSwitchOffRGB888(i, 0xFF0000);
        deviceButton.setSwitchOnRGB888(i, 0x0000FF);
    }
    deviceButton.setFlashWriteBack();
}

void loop() {
    // Read Switch statuses (include I2C address)
    Serial.printf("Switch Statuses (I2C 0x%02X): 0=Off, 1=On:\n", switchId);
    for (uint8_t i = 0; i < 8; i++) {
        uint8_t status = deviceSwitch.getSwitchStatus(i);
        Serial.printf("SW%d: %d\t", i, status);
    }
    Serial.println();

    // Read Button statuses (include I2C address)
    Serial.printf("Button Statuses (I2C 0x%02X, INVERTED): 1=Pressed, 0=Released:\n", buttonId);
    for (uint8_t i = 0; i < 8; i++) {
        uint8_t rawStatus = deviceButton.getSwitchStatus(i);
        uint8_t invertedStatus = 1 - rawStatus;
        Serial.printf("BTN%d: %d\t", i, invertedStatus);
    }
    Serial.println("\n-----------------------");
    delay(1000);
}