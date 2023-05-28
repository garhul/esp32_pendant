#ifndef __INPUTS__
#define __INPUTS__

#include <Wire.h>

#include "Arduino.h"
#include "PCF8575.h"

#define X_JOY_INPUT 12  // TODO:: verify this is correct
#define Y_JOY_INPUT 13
#define INTERRUPT_PIN 16
#define ENCODER_A 1
#define ENCODER_B 1

#define INPUT_ADDR 0x20
namespace __INPUTS {

union buttonsState {
  uint16_t intval;
  struct {
    uint16_t HOME : 1;
    uint16_t PROBE_AXIS : 1;
    uint16_t ZERO_AXIS : 1;
    uint16_t GO_TO_ORIGIN : 1;
    uint16_t MACRO_1 : 1;
    uint16_t MACRO_2 : 1;
    uint16_t CHANGE_AXIS : 1;
    uint16_t CHANGE_MULTIPLIER : 1;
    uint16_t HOLD : 1;
    uint16_t CYCLE : 1;
    uint16_t FEED_ADJ : 1;
    uint16_t AIR : 1;
    uint16_t MENU : 1;
    uint16_t OK : 1;
    uint16_t JOG : 1;
    uint16_t BYPASS : 1;
  } buttons;
};

struct encoderState {
  uint16_t position;
};

struct joyState {
  uint16_t x_axis;
  uint16_t y_axis;
};

struct inputsState {
  joyState joystick;
  buttonsState buttons;
  encoderState encoder;
};

void begin();

inputsState getState();

buttonsState getButtonsState();

joyState getJoystickState();

encoderState getEncoderState();

void poll();
}  // namespace __INPUTS
#endif