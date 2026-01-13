#include "cxa_rs232.h"

void CXARS232::setup() {
  this->set_update_interval(0);  // folyamatos poll
  request_power();
  request_source();
}

void CXARS232::loop() {
  while (this->available()) {
    std::string line;
    while (this->available()) {
      char c = this->read();
      if (c == '\r') break;
      line.push_back(c);
    }
    if (line.empty() || line[0] != '#') continue;

    // Parse: #gg,nn,dd
    std::vector<std::string> parts;
    std::string token;

    for (size_t i = 1; i < line.size(); i++) {
      if (line[i] == ',') {
        parts.push_back(token);
        token.clear();
      } else {
        token.push_back(line[i]);
      }
    }
    if (!token.empty()) parts.push_back(token);

    if (parts.size() < 2) continue;

    std::string gg = parts[0];
    std::string nn = parts[1];
    std::string dd = (parts.size() > 2) ? parts[2] : "";

    // Power status
    if (gg == "02" && nn == "01") {
      power_state = (dd == "1");
      if (power_sensor) power_sensor->publish_state(power_state);
    }

    // Mute status
    if (gg == "02" && nn == "03") {
      mute_state = (dd == "1");
      if (mute_sensor) mute_sensor->publish_state(mute_state);
    }

    // Source status
    if (gg == "04" && nn == "01") {
      current_source = atoi(dd.c_str());
      if (source_sensor) source_sensor->publish_state(current_source);
    }
  }
}

// Commands
void CXARS232::send_power(bool on) {
  char buf[16];
  snprintf(buf, sizeof(buf), "#01,02,%d\r", on ? 1 : 0);
  this->write_str(buf);
}

void CXARS232::send_mute(bool mute) {
  char buf[16];
  snprintf(buf, sizeof(buf), "#01,04,%d\r", mute ? 1 : 0);
  this->write_str(buf);
}

void CXARS232::send_source(uint8_t src) {
  char buf[16];
  snprintf(buf, sizeof(buf), "#03,04,%02d\r", src);
  this->write_str(buf);
}

void CXARS232::request_power() { this->write_str("#01,01\r"); }
void CXARS232::request_source() { this->write_str("#03,01\r"); }
void CXARS232::request_protocol_version() { this->write_str("#13,01\r"); }
