#pragma once

#include "esphome.h"
#include <vector>
#include <string>

class CXARS232 : public Component, public UARTDevice {
 public:
  CXARS232(UARTComponent *parent) : UARTDevice(parent) {}

  void setup() override;
  void loop() override;

  // Commands
  void send_power(bool on);
  void send_mute(bool mute);
  void send_source(uint8_t src);
  void request_power();
  void request_source();
  void request_protocol_version();

  // Current states
  bool power_state = false;
  bool mute_state = false;
  uint8_t current_source = 0;

  // HA sensors
  Sensor *power_sensor = nullptr;
  Sensor *mute_sensor = nullptr;
  Sensor *source_sensor = nullptr;
};
