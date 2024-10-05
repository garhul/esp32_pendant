#include "pendant.h"

namespace __PENDANT {
  NeoPixelBus<NeoGrbFeature, NeoEsp8266AsyncUart1800KbpsMethod> leds(STRIP_LEN, LED_PIN);

  uint8_t _mode = MODES::IDLE;

  void setMode(uint8_t mode) {
    _mode = mode;
  }

  void init() {
    //Initialize display
    _DISPLAY::begin();
    _DISPLAY::test();

    _INPUTS::begin();

    leds.Begin();
    leds.Show();

    Serial.println("leds starting");

    leds.ClearTo(RgbColor(0, 0, 0));
    leds.Show();

    delay(1000);
    Serial.println("leds starting 2");
    for (uint8_t i = 0; i < STRIP_LEN; i++) {
      leds.SetPixelColor(i, HslColor(i * 0.0625, 0.4, 0.05f));
      delay(50);
      leds.Show();
    }
  }


  void pollMachine() {



  }

  void update() {
    pollMachine();
    pollControls();
    _INPUTS::inputsState state = _INPUTS::getState();

    Serial.printf(" status: " PRINTF_BINARY_PATTERN_INT16 " \n", PRINTF_BYTE_TO_BINARY_INT16(state.buttons.intval));
    Serial.printf("data: %d \n", state.buttons.buttons);

    if (!state.buttons.buttons.JOG) {
      Serial.println("JOG enabled");
    }

    // if (!state.buttons.buttons.OK) {
    //   Serial.println("OK button pressed");
    // }

    // if (!state.buttons.buttons.HOME) {
    //   Serial.println("Home button pressed");
    // }

    // if (!state.buttons.buttons.GO_TO_AXIS_ORIGIN) {
    //   Serial.println("Go to axis origin button pressed");
    // }

    // if (!state.buttons.buttons.CYCLE_START) {
    //   Serial.println("Cycle start button pressed");
    // }

    // if (!state.buttons.buttons.ZERO_AXIS) {
    //   Serial.println("Zero axis button pressed");
    // }

    // if (!state.buttons.buttons.HOLD) {
    //   Serial.println("Hold button pressed");
    // }
    delay(500);
  }

}  // namespace __PENDANT