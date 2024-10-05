#pragma once

#include <Arduino.h>
#include <Wire.h>

#include "PCF8575.h"
#include "ADS1X15.h"

// BUttons masks
#define MASK_CHANGE_MULTIPLIER 0b1
#define MASK_CHANGE_AXIS       0b10
#define MASK_OK                0b100
#define MASK_GO_TO_ZERO        0b1000
#define MASK_CYCLE_START       0b10000
#define MASK_MENU              0b100000
#define MASK_HOME              0b1000000
#define MASK_ZERO_AXIS         0b10000000
#define MASK_JOG_B             0b100000000
#define MASK_JOG_A             0b1000000000
#define MASK_MACRO_1           0b10000000000
#define MASK_AIR               0b100000000000
#define MASK_PROBE_AXIS        0b1000000000000
#define MASK_HOLD              0b10000000000000
#define MASK_MACRO_3           0b100000000000000
#define MASK_MACRO_2           0b1000000000000000

/* --- PRINTF_BYTE_TO_BINARY macro's --- */
#define PRINTF_BINARY_PATTERN_INT8 "%c%c%c%c%c%c%c%c"
#define PRINTF_BYTE_TO_BINARY_INT8(i)                             \
  (((i) & 0x80ll) ? '1' : '0'), (((i) & 0x40ll) ? '1' : '0'),     \
      (((i) & 0x20ll) ? '1' : '0'), (((i) & 0x10ll) ? '1' : '0'), \
      (((i) & 0x08ll) ? '1' : '0'), (((i) & 0x04ll) ? '1' : '0'), \
      (((i) & 0x02ll) ? '1' : '0'), (((i) & 0x01ll) ? '1' : '0')

#define PRINTF_BINARY_PATTERN_INT16 \
  PRINTF_BINARY_PATTERN_INT8 PRINTF_BINARY_PATTERN_INT8
#define PRINTF_BYTE_TO_BINARY_INT16(i) \
  PRINTF_BYTE_TO_BINARY_INT8((i) >> 8), PRINTF_BYTE_TO_BINARY_INT8(i)
#define PRINTF_BINARY_PATTERN_INT32 \
  PRINTF_BINARY_PATTERN_INT16 PRINTF_BINARY_PATTERN_INT16
#define PRINTF_BYTE_TO_BINARY_INT32(i) \
  PRINTF_BYTE_TO_BINARY_INT16((i) >> 16), PRINTF_BYTE_TO_BINARY_INT16(i)
#define PRINTF_BINARY_PATTERN_INT64 \
  PRINTF_BINARY_PATTERN_INT32 PRINTF_BINARY_PATTERN_INT32
#define PRINTF_BYTE_TO_BINARY_INT64(i) \
  PRINTF_BYTE_TO_BINARY_INT32((i) >> 32), PRINTF_BYTE_TO_BINARY_INT32(i)
/* --- end macros --- */

#define INTERRUPT_PIN 12  // D6
#define JOG_EN_PIN A0
#define PCF8575_ADDR 0x20
#define ADC_ADDR 0x48

namespace _INPUTS {

  union buttonsState {
    uint16_t intval;
    struct {
      uint16_t MENU : 1;
      uint16_t OK : 1;
      uint16_t HOME : 1;
      uint16_t GO_TO_AXIS_ORIGIN : 1;
      uint16_t CYCLE_START : 1;
      uint16_t ZERO_AXIS : 1;
      uint16_t HOLD : 1;
      uint16_t PROBE_AXIS : 1;
      uint16_t AIR : 1;
      uint16_t MACRO_3 : 1;
      uint16_t MACRO_1 : 1;
      uint16_t MACRO_2 : 1;
      uint16_t CHANGE_AXIS : 1;
      uint16_t CHANGE_MULTIPLIER : 1;
      uint16_t JOG : 1;

      uint16_t A : 1;
      uint16_t B : 1;
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
    joyState     joystick;
    buttonsState buttons;
    encoderState encoder;
  };

  void begin();

  void scan();

  inputsState getState();

  buttonsState getButtonsState();

  joyState getJoystickState();

  encoderState getEncoderState();

}  // namespace __INPUTS
