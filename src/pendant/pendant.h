#pragma once
#include <Arduino.h>
#include <NeoPixelBus.h>
#include <Wire.h>

#include "../display/display.h"
#include "../inputs/inputs.h"

#define LED_PIN 2
#define STRIP_LEN 15
#define REL 0.003921569f


namespace __PENDANT {

  enum MODES {
    IDLE,
    JOG,
    MDI,
    AUTO,
    REFERENCE,
    SETTINGS
  };

  void init();
  void setMode(uint8_t mode);
  void update();

}  // namespace __PENDANT