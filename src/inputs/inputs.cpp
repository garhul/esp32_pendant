#include "./inputs.h"

namespace __INPUTS {
PCF8575 inputs(INPUT_ADDR);

inputsState state;
bool dirty = false;

void IRAM_ATTR _button_change_isr() {
  Serial.println("coso");
  dirty = true;
}

void begin() {
  inputs.begin();
  attachInterrupt(INTERRUPT_PIN, _button_change_isr, FALLING);
}

buttonsState getButtonsState() {
  buttonsState state = {.intval = 0};

  for (byte btnidx = 0; btnidx < 16; btnidx++) {
    inputs.pinMode(btnidx, OUTPUT);
    inputs.digitalWrite(btnidx, HIGH);
    delay(10);
    inputs.pinMode(btnidx, INPUT);
    Serial.print(btnidx);
    Serial.print(" - > ");
    Serial.println(inputs.digitalRead(btnidx));
    state.intval = state.intval | (inputs.digitalRead(btnidx) >> btnidx);
  }

  Serial.println(state.intval);
  return state;
}

joyState getJoystickState() {
  joyState state;
  state.x_axis = analogRead(X_JOY_INPUT);
  state.y_axis = analogRead(Y_JOY_INPUT);

  return state;
}

encoderState getEncoderState() {
  return {position : 100};
}

inputsState getState() {
  return state;
}

void poll() {
  inputsState state;
  Serial.println("Polling...");
  // if (dirty) {
  state.buttons = getButtonsState();

  // }

  state.encoder = getEncoderState();
  state.joystick = getJoystickState();
}

}  // namespace __INPUTS