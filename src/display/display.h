#pragma once
#include <Arduino.h>
#include <TFT_eSPI.h>  // Hardware-specific library

namespace _DISPLAY {
  enum Status {
    ALARM,
    HOLD,
    IDLE,
    RUN
  };

  void begin();
  void test();

  void display();
  void printAxis(uint8_t startY, float value, uint16_t color, String label);
  void showSplashScreen();
  void drawStatusBox(uint8_t status);
  void drawCoordSystemBox(char* text);

}  // namespace __DISPLAY