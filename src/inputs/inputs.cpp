#include "inputs.h"

namespace _INPUTS {
  PCF8575 inputs(PCF8575_ADDR);
  ADS1115 ADS(ADC_ADDR);

  inputsState state;
  inputsState prevState;
  // bool dirty = false;

  void IRAM_ATTR _button_change_isr() {
    prevState = state;
    state.buttons = { .intval = inputs.readButton16() };
    // dirty = true;
    Serial.printf(" status: " PRINTF_BINARY_PATTERN_INT16 " \n", PRINTF_BYTE_TO_BINARY_INT16(state.buttons.intval));
  }  // namespace __INPUTS

  void begin() {
    inputs.begin();
    ADS.begin();
    inputs.setButtonMask(0x0000);
    pinMode(INTERRUPT_PIN, INPUT_PULLUP);
    attachInterrupt(INTERRUPT_PIN, _button_change_isr, FALLING);
  }

  buttonsState getButtonsState() {
    buttonsState state = { .intval = inputs.read16() };

    Serial.println(state.intval);
    return state;
  }  // namespace __INPUTS

  joyState getJoystickState() {
    joyState state;
    ADS.setGain(0);
    state.x_axis = map(ADS.readADC(0), 0, 16383, 0, 100);
    state.y_axis = map(ADS.readADC(1), 0, 16383, 0, 100);

    return state;
  }

  encoderState getEncoderState() {
    return { position: 100 };
  }

  inputsState getState() {
    state.joystick = getJoystickState();
    state.encoder = getEncoderState();
    state.buttons.buttons.JOG = (ADS.readADC(2) > 1000) ? 1 : 0;

    return state;
  }

}  // namespace __INPUTS